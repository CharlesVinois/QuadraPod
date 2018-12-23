#include <BluetoothCom.h>
#include <LegController.h>

unsigned char G_aSpeedReduction[3] = {8, 4, 1};
unsigned char G_aLims[3][2] = {{40, 100}, {40, 100}, {40, 100}};
unsigned char G_aPinServo[3] = {2, 3, 4};
unsigned char G_aPinBlue[2] = {2, 3};
unsigned char G_aPos[3] = {0, 0, 0};
unsigned char aDest[3] = {40, 40, 40};
G_eCommand cmd = G_eCommand::Unkwown;
unsigned char* value;
Leg leg;
BluetoothCom btc;
int i;
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  i = 0;
  unsigned char id = 1;
  leg = Leg(id, G_aPinServo, G_aLims);
  btc = BluetoothCom(id, G_aPinBlue);
  setupBLE();
}
void loop() {
    btc.recieve(cmd, value);
    //leg.get_aDest(aDest);
    //leg.get_aPos(G_aPos);
    //
    if (cmd == G_eCommand::Move) {
        aDest[0] = value;
        aDest[1] = value;
        aDest[2] = value;
        leg.set_aDest(aDest);
        leg.moveP(G_aSpeedReduction);
    }
}
