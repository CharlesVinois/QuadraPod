#ifndef DEF_H_
#define DEF_H_

#include <stdio.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>

#define max_string 50
#define nb_servo_per_leg   3
#define nb_leg  4

#define FREQUENCY             60
#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached

enum G_eExecutionState{
 Off = 0,
 Setup = 1,
 Idle = 2,
 Run = 3,
 Stop = 4
};
enum G_ePositionV{
 Up = 0,
 UMi = 1,
 MidleV = 2,
 BoMi = 3,
 Bottom = 4
};
enum G_ePositionH{
 Left = 0,
 LeMi = 1,
 MidleH = 2,
 RiMi = 3,
 Right = 4
};
enum G_eCommand{
 Move = 0,
 Infos = 1,
 Unkown = 2
};
template<typename T>
class Observer {
public:
    void attach(T *bc) {
        bc->registerObserver(this);
    }
    virtual void onReceivedData(const T*) = 0;
};

#endif /* DEF_H_ */