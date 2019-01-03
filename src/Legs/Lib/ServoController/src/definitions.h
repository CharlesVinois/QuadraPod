#ifndef DEF_H_
#define DEF_H_

#include <stdio.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

#define nullptr NULL
#define max_string 50
#define nb_servo 4

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


#endif /* DEF_H_ */