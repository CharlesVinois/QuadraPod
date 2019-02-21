#include <LegController.h>
class Legs : public Observer
{
    public:
        Legs();
        Legs(unsigned char (&id)[nb_leg][nb_servo_per_leg],
            Adafruit_PWMServoDriver& pwm,
            unsigned char (&pins)[nb_leg][nb_servo_per_leg],
            unsigned char (&lims)[nb_leg][nb_servo_per_leg][2],
            const bool (&isReversed)[nb_leg][nb_servo_per_leg] = nullptr);
        ~Legs();
        bool setupP(unsigned char (&pins)[nb_leg][nb_servo_per_leg],
                    Adafruit_PWMServoDriver& pwm,
                    const bool (&isReversed)[nb_leg][nb_servo_per_leg] = nullptr);
        bool moveP();
        void onReceivedData(const Leg*) override;

        void get_iPin(unsigned char& pin);
    void get_tPos(unsigned char& pos);
    void get_tDest(unsigned char& dest);
    void set_tDest(unsigned char& dest);
    void get_tLim(unsigned char (&aLim)[2]);
    void set_tLim(unsigned char (&aLim)[2]);
    void get_tSpeedReduction(unsigned char& sr);
    void set_tSpeedReduction(unsigned char& sr);
    void get_tPosState(unsigned char& posState);
    void get_tClockWise(bool& clockW);
    void get_tIsStatic(bool& isStatic);
    void get_tIsReversed(bool& isReversed);
    void get_tExecState(G_eExecutionState& eState);

    void printInfos(SoftwareSerial& soSer);
    private:
        Leg m_aServs[nb_leg];
        unsigned char m_aId[nb_leg];
        unsigned char m_tPin[nb_leg][nb_servo_per_leg];
        unsigned char m_tPos[nb_leg][nb_servo_per_leg];
        unsigned char m_tDest[nb_leg][nb_servo_per_leg];
        unsigned char m_tLims[nb_leg][nb_servo_per_leg][2];
        bool m_tClockwise[nb_leg][nb_servo_per_leg];
        bool m_tIsStatic[nb_leg][nb_servo_per_leg];
        bool m_tIsReversed[nb_leg][nb_servo_per_leg];
        bool m_tExecutionState[nb_leg][nb_servo_per_leg];
        bool m_bClockwise[nb_leg] = nullptr;
        bool m_bIsStatic[nb_leg] = nullptr;
        G_eExecutionState m_eState = Off;
}