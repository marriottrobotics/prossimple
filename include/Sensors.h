/**The Sensor Handling in it's entirty
Please call imeInitalizeAll() first.*/

//TODO Implement in Pid_Core

//FIXME prevent duplication
#include "main.h"

#define IME 0
#define QENC 1
#define POT 2

struct Sensor{
    int sensorType;
    int port; //If a quadrature encoder is used this will be the Encoder[] slot
};

int sensor_count;
struct Sensor *sensors[10];

int encoder_count;
Encoder qencoders[5];

int readValue(Sensor *input){
    int value = 0;
    if(input->sensorType == IME){
        imeGet(input->port, &value);
    }else if(input->sensorType == QENC){
        value = encoderGet(qencoders[input->port]);
    }else if(input->sensorType == POT){
        value = analogRead(input->port);
    }

    return value;
}

//TODO Generation and init methods for ime, qenc, and pot
