#include <definitions.h>
#include <ServoControler.h>

#include <LegController.h>
#include <BluetoothCom.h>

unsigned char G_aSpeedReduction[3] = {8, 4, 1};
unsigned char G_aLims[3][2] = {{40, 100}, {40, 100}, {40, 100}};
unsigned char G_aPinServo[3] = {2, 3, 4};
unsigned char G_aPinBlue[2] = {2, 3};
unsigned char G_aPos[3] = {0, 0, 0};
unsigned char aDest[3] = {40, 40, 40};
G_eCommand cmd;
unsigned char value[3] = {90, 90, 90};
Leg leg;
BluetoothCom btc;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  unsigned char id = 1;
  leg = Leg(id, G_aPinServo, G_aLims);
  btc = BluetoothCom(id, G_aPinBlue);
}
void loop() {
    btc.recieve(cmd, value);
    //leg.get_aDest(aDest);
    //leg.get_aPos(G_aPos);
    //
    if (cmd == G_eCommand::Move) {
        aDest[0] = value[0];
        aDest[1] = value[1];
        aDest[2] = value[2];
        leg.set_aDest(aDest);
        leg.moveP(G_aSpeedReduction);
    }
}
