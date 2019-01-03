#ifndef SERV_H_
#define SERV_H_

#include <Servo.h>
#include <definitions.h>

class Serv
{
  public:
    Serv();
    Serv(const unsigned char& pin, const bool& isReversed = false);
    ~Serv();
    void setupP(const unsigned char& pin, const bool& isReversed = false);
    void moveP(const unsigned char& speedReduction = 1);
    void printInfos(SoftwareSerial& soSer);
    void get_iPin(unsigned char& pin);
    void get_iPos(unsigned char& pos);
    void get_iDest(unsigned char& dest);
    void set_iDest(unsigned char& dest);
    void get_aLim(unsigned char (&aLim)[2]);
    void set_aLim(unsigned char (&aLim)[2]);
    void get_iSpeedReduction(unsigned char& sr);
    void set_iSpeedReduction(unsigned char& sr);
    void get_ePosState(unsigned char& posState);
    void get_bClockWise(bool& clockW);
    void get_bIsStatic(bool& isStatic);
    void get_bIsReversed(bool& isReversed);
    void get_eExecState(G_eExecutionState& eState);
  private:
    Servo* m_cServo;
    unsigned char m_iPin;
    unsigned char m_iPos = 90;
    unsigned char m_iDest = 90;
    unsigned char m_aLim[2];
    bool m_bIsClockwise = true;
    bool m_bIsStatic = true;
    bool m_bIsReversed = false;
    unsigned char m_ePosState = 0;//associate to enum pos
    unsigned char m_iSpeedReduction = 1;
    G_eExecutionState m_eState = Off;
};


#endif /* SERV_H_ */