#ifndef BLUETO_H_
#define BLUETO_H_

#include <definitions.h>

class BluetoothCom
{
    public:
        BluetoothCom();
        BluetoothCom(unsigned char& id, unsigned char (&pins)[2]);
        ~BluetoothCom();
        bool setupP(unsigned char (&pins)[2]);
        void setupBLE();
        void recieve(G_eCommand& eCmd, unsigned char (&value)[nb_servo]);
        void get_cSoSerial(SoftwareSerial& soSerial);
        void get_aPin(unsigned char (&aPin)[2]);
        void get_aExecState(G_eExecutionState eState);
        void readSerial(G_eCommand& eCmd, unsigned char (&value)[nb_servo]);
        void sendCommand(const char* command);
        void writeToBLE(char value);
        void printInfos();
    private:
        SoftwareSerial* m_cSerial;
        unsigned char m_aReply[50];
        unsigned char m_iCountReply;
        unsigned char m_iId;
        unsigned char m_aPin[2];
        G_eExecutionState m_eState = Off;
};

#endif /* BLUETO_H_ */