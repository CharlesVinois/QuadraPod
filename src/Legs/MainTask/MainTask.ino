#include <definitions.h>
#include <ServoControler.h>
#include <LegController.h>
#include <BluetoothCom.h>
#include <Wire.h>


unsigned char G_aSpeedReduction[nb_servo] = {8, 8, 8};
unsigned char G_aLims[nb_servo][2] = {{40, 90}, {40, 90}, {40, 90}};
unsigned char G_aPinServo[nb_servo] = {0, 1, 2};
unsigned char G_aPinBlue[2] = {2, 3};
unsigned char G_aIsreversed[nb_servo] = {false, true, false};
unsigned char aDest[nb_servo] = {0, 0, 0};
G_eCommand cmd = G_eCommand::Unkown;
Leg* leg;
BluetoothCom btc;
SoftwareSerial* soSerial;
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  unsigned char id = 1;
  
  btc = BluetoothCom(id, G_aPinBlue);
  btc.get_cSoSerial(*soSerial);
  pwm = Adafruit_PWMServoDriver();
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates
  leg = new Leg(id, pwm, G_aPinServo, G_aLims);
  delay(10);
}
void loop() {
    btc.recieve(cmd, aDest);
    leg->moveP(G_aSpeedReduction);
    //TODO Move these lines into manger
    if (cmd == G_eCommand::Move) {
        leg->set_aDest(aDest);
    }
    else if (cmd == G_eCommand::Infos) {
        leg->printInfos(*soSerial);
        cmd = G_eCommand::Unkown;
    }
}
