/**This should be a rough port of the RobotC code.*/

//#include "main.h"
#include "Sensors.h"
#include "PidCore.h"
#include "Math.h"

TaskHandle pid_loop;

//Internal handeling of potentiometers
void handlePot(struct pid *p);

//Initalizes basic variables for the pid struct provided.
void pid_init(struct pid *p) {
//	nMotorEncoder[p->mport] = 0;
    //imeReset(p->ime_port);
    //TODO SensorReset
	p->mtarget = 0;
	p->pgain = 0.70;
	p->corrcap = 30;
	p->enable = true;
	p->min = 0;
	p->max = 0;
	p->igain = 0.001;
	p->isum = 0;
	p->ilimit = 1000;
	p->lastpos = 0;
	p->dgain = 0;
}

//Checks if the pid motor is close enough to it's target to be within an acceptable range.
bool pid_ontarget(struct pid *p)
{
	//return ABS(p->mtarget - nMotorEncoder[p->mport]) < 64;
    int ime = readValue(p->sensor);
    //imeGet(p->ime_port, &ime);
    return ABS(p->mtarget - ime) < 64;
}

//Updates the pid loop to include the latest information from this tick.
void pid_update(struct pid *p) {
	//Limit the pid loop
	if (p->min != 0 || p->max != 0) {
		p->mtarget = LIMIT(p->mtarget, p->min, p->max);
	}

	//Calculate initial values
	//int enc = nMotorEncoder[p->mport];
    int enc = readValue(p->sensor);
	//printf("ENC: %d", enc);
	//printf("enc %d", enc);

	//Calculate err using the modified enc value and the target.
	long err = p->mtarget - enc;

	//P Component
#ifdef P_COMPONENT
	float corr = err * p->pgain;
#endif

#ifdef I_COMPONENT
	//I Component
	p->isum+=err;
	if(p->isum >= p->ilimit){
		p->isum = p->ilimit;
	}else if(p->isum < 0){
		if(p->ilimit < 0 && p->isum < p->ilimit){
			p->isum = p->ilimit;
		}else if(p->ilimit > 0 && p->isum < 0){
			p->isum = -p->ilimit;
		}
	}

	corr += p->isum * p->igain;
#endif

#ifdef D_COMPONENT
	float dAvg = p->lastpos - enc;
	corr += dAvg * p->dgain;

	p->lastpos = enc;
#endif
	//printf("\n Corr %f mtarget: %ld", corr, p->mtarget);
	//printf("\n Pid at update with %e power Sensor at %ld target at %ld", corr, enc, p->mtarget);
	//writeDebugStreamLine("Powering motor at %d", corr);
	//motor[p->mport] = corr;
    motorSet(p->mport, corr);
	//writeDebugStreamLine("Motor had power at %d", corr);
}

//The array of pid loops to be used in the update task.
struct pid *pid_arr[10];
//The amount of currently registered pid loops.
int pid_count = 0;

//Convenience method calls pid_init for all pid loops in pid_arr.
void pid_init_all()
{
	for (int i = 0; i < pid_count; ++i) {
		pid_init(pid_arr[i]);
		if(pid_arr[i]->sensor->sensorType == POT){
			if(pid_arr[i]->min == 0){
				pid_arr[i]->min = 0;
			}else if(pid_arr[i]->max == 0){
				pid_arr[i]->max = 4095;
			}
			pid_arr[i]->igain = 0;
			pid_arr[i]->pgain = 0.3;
		}
	}

	printf("Pid system init with %d pid loops.", pid_count);
}

//A task to be run on the scheduler
void pid_run_loops() {
	//print(" \n Run Loops");
//	while(1) {
	for (int i = 0; i < pid_count; ++i) {
		if(pid_arr[i]->enable) {
			pid_update(pid_arr[i]);
		}
	}
    //    delay(10);
	//}
};

//A lowpass to handle a short input with negative values.
short lowpassS(short input, short minimum){
	if(input <= -minimum || input >= minimum){
		return input;
	}else{
		return 0;
	}
}

//Loops until pid_ontarget is true for the supplied loop.
void wait_ontarget(struct pid *p)
{
	//writeDebugStreamLine("Waiting for pid to finish");
	//long orig_pos = p->mtarget; Also only if we need it.
	//int last_pos = orig_pos; //This exists if we want to use it for somthing later.

	// kills the wait if we exceed a timer
	//unsigned long start_time = nPgmTime;
    unsigned long start_time = millis();
	const unsigned long wait_time = 2500;

	while (!pid_ontarget(p)) {
		//writeDebugStreamLine("In loop with orig_pos %d and last_pos %d", orig_pos, last_pos);

		//last_pos = nMotorEncoder[p->mport];
        //last_pos = readValue(p->sensor); Part of the above last_pos defenition.
        delay(25);

		// if we get stuck, stop waiting
		if (millis()-start_time > wait_time)
			break;
	}
	//writeDebugStreamLine("Ended waiting");
}
