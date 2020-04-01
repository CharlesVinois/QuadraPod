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
        void recieve(G_eCommand& eCmd, unsigned char (&value)[nb_servo_per_leg]);

        SoftwareSerial* get_cSoSerial();
        void get_aPin(unsigned char (&aPin)[2]);
        void get_aExecState(G_eExecutionState eState);

        void registerObserver(Observer<BluetoothCom>*); 
        void unregisterObserver();

        void printInfos();
    private:
        void readSerial(G_eCommand& eCmd, unsigned char (&value)[nb_servo_per_leg]);
        void sendCommand(const char* command);
        void writeToBLE(char value);

        void _notifyObserver();

        G_eExecutionState m_eState = Off;

        SoftwareSerial* m_cSerial;
        Observer<BluetoothCom>* m_pObserver;

        unsigned char m_aReply[50];
        unsigned char m_iCountReply;
        unsigned char m_iId;
        unsigned char m_aPin[2];
};

#endif /* BLUETO_H_ */