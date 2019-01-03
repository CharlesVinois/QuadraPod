#pragma once

#include <ServoControler.h>

class Leg
{
  public:
    Leg();
    Leg(unsigned char& id, 
        unsigned char (&pins)[nb_servo], 
        unsigned char (&lims)[nb_servo][2],
        const bool (&isReversed)[nb_servo] = {false, false, false});
    ~Leg();
    bool setupP(unsigned char (&pins)[nb_servo],
                const bool (&isReversed)[nb_servo] = {false, false, false});
    bool moveP(const unsigned char (&speedReduction)[nb_servo]);
    void printInfos(SoftwareSerial& soSer);
    void get_aPin(unsigned char (&aPin)[nb_servo]);
    void get_aPos(unsigned char (&aPos)[nb_servo]);
    void get_aDest(unsigned char (&aDest)[nb_servo]);
    void set_aDest(unsigned char (&aDest)[nb_servo]);
    void set_aLims(unsigned char (&aLims)[nb_servo][2]);
    void get_aPosState(unsigned char& aPosState);
    void get_aClockWise(bool (&aClockW)[nb_servo]);
    void get_aIsStatic(bool (&aIsStatic)[nb_servo]);
    void get_aIsReversed(bool (&aIsReversed)[nb_servo]);
    void get_aExecState(G_eExecutionState eState[]);
  private:
    Serv m_aServs[nb_servo];
    unsigned char m_iId;
    unsigned char m_aPin[nb_servo];
    unsigned char m_aPos[nb_servo];
    unsigned char m_aDest[nb_servo];
    unsigned char m_aLims[nb_servo][2];
    bool m_aClockwise[nb_servo];
    bool m_aIsStatic[nb_servo];
    bool m_aIsReversed[nb_servo];
    bool m_aExecutionState[nb_servo];
    bool m_bClockwise = true;
    bool m_bIsStatic = true;
    G_eExecutionState m_eState = Off;
};