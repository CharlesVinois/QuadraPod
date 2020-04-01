#ifndef LEG_H_
#define LEG_H_
#include <ServoControler.h>

class Leg
{
  public:
    Leg();
    Leg(unsigned char& id,
        Adafruit_PWMServoDriver* pwm,
        unsigned char (&pins)[nb_servo_per_leg],
        unsigned char (&lims)[nb_servo_per_leg][2]);
    ~Leg();

    // bool setupP(unsigned char (&pins)[nb_servo_per_leg],
    //             Adafruit_PWMServoDriver& pwm);
    bool moveP(const unsigned char (&speedReduction)[nb_servo_per_leg]);

    void get_aPin(unsigned char (&aPin)[nb_servo_per_leg]);
    void get_aPos(unsigned char (&aPos)[nb_servo_per_leg]);
    void get_aDest(unsigned char (&aDest)[nb_servo_per_leg]);
    void set_aDest(unsigned char (&aDest)[nb_servo_per_leg]);
    void set_aLims(unsigned char (&aLims)[nb_servo_per_leg][2]);
    void get_aPosState(unsigned char& aPosState);
    void get_aClockWise(bool (&aClockW)[nb_servo_per_leg]);
    void get_aIsStatic(bool (&aIsStatic)[nb_servo_per_leg]);
    void get_aIsReversed(bool (&aIsReversed)[nb_servo_per_leg]);
    void get_aExecState(G_eExecutionState eState[]);
    
    void printInfos(SoftwareSerial* soSer);
  private:
    Serv* m_aServs[nb_servo_per_leg];
    unsigned char m_iId;
    unsigned char m_aPin[nb_servo_per_leg];
    unsigned char m_aPos[nb_servo_per_leg];
    unsigned char m_aDest[nb_servo_per_leg];
    unsigned char m_aLims[nb_servo_per_leg][2];
    bool m_aClockwise[nb_servo_per_leg];
    bool m_aIsStatic[nb_servo_per_leg];
    bool m_aIsReversed[nb_servo_per_leg];
    bool m_aExecutionState[nb_servo_per_leg];
    bool m_bClockwise = true;
    bool m_bIsStatic = true;
    G_eExecutionState m_eState = Off;
};

#endif /* LEG_H_ */