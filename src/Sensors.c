/**The Sensor Handling in it's entirty
Please call imeInitalizeAll() first.*/

//TODO Implement in Pid_Core

//FIXME prevent duplication

//#include "main.h"
#include <API.h>
#include "Sensors.h"

int sensor_count = 0;
struct Sensor sensors[10];

int encoder_count = 0;
Encoder qencoders[5];

int readValue(struct Sensor *input){
    int value = 0;
    if(input->sensorType == IME){
        imeGet(input->port, &value);
        value*=-1;
    }else if(input->sensorType == QENC){
        value = encoderGet(qencoders[input->port]);
        value*=-1;
    }else if(input->sensorType == POT){
        value = analogRead(input->port);
    }

    return value;
}

//TODO Generation and init methods for ime, qenc, and pot
struct Sensor *pot(int port){
    struct Sensor ns;
    ns.port = port;
    ns.sensorType = POT;
    sensors[sensor_count++]=ns;
    return &sensors[sensor_count-1];
}

struct Sensor *ime(int addr){
    struct Sensor ns;
    ns.port = addr;
    ns.sensorType = IME;
    imeReset(ns.port);
    sensors[sensor_count++]=ns;
    return &sensors[sensor_count-1];
}

struct Sensor *qenc(unsigned char portTop, unsigned char portBottom){
    qencoders[encoder_count++] = encoderInit(portTop, portBottom, false);
    struct Sensor ns;
    ns.port = encoder_count-1;
    ns.sensorType = QENC;
    encoderReset(qencoders[ns.port]);
    sensors[sensor_count++]=ns;
    return &sensors[sensor_count-1];
}
