/**The Sensor Handling in it's entirty
Please call imeInitalizeAll() first.*/

//TODO Implement in Pid_Core

//FIXME prevent duplication
//#include "main.h"
#include <API.h>

#define IME 0
#define QENC 1
#define POT 2

struct Sensor{
    int sensorType;
    int port; //If a quadrature encoder is used this will be the Encoder[] slot
};

int sensor_count;
struct Sensor sensors[10];

int encoder_count;
Encoder qencoders[5];

int readValue(struct Sensor *input){
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
    sensors[sensor_count++]=ns;
    return &sensors[sensor_count-1];
}

struct Sensor *qenc(unsigned char portTop, unsigned char portBottom){
    qencoders[encoder_count++] = encoderInit(portTop, portBottom, false);
    struct Sensor ns;
    ns.port = encoder_count-1;
    ns.sensorType =QENC;
    sensors[sensor_count++]=ns;
    return &sensors[sensor_count-1];
}
