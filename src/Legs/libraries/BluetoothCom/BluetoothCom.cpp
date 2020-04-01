#include <BluetoothCom.h>

BluetoothCom::BluetoothCom() {
}
BluetoothCom::BluetoothCom(unsigned char& id, unsigned char (&pins)[2]) {
    m_iId = id;
    m_iCountReply = 0;
    setupP(pins);
    m_eState = Idle;
}
BluetoothCom::~BluetoothCom() {
}
void BluetoothCom::registerObserver(Observer<BluetoothCom>* obs) {
    m_pObserver = obs; //we will only allow one observer
}

void BluetoothCom::unregisterObserver() {
    m_pObserver = nullptr;
}

void BluetoothCom::_notifyObserver() {
    if (m_pObserver != nullptr) {
        m_pObserver->onReceivedData(this); 
    }
}
void BluetoothCom::sendCommand(const char* command){
  Serial.print("Command send :");
  Serial.println(command);
  m_cSerial->println(command);
}
SoftwareSerial* BluetoothCom::get_cSoSerial() {
  return m_cSerial;
}
void BluetoothCom::setupBLE() {
  sendCommand("AT");
  sendCommand("AT+ROLE0");
  sendCommand("AT+UUID0xFFE0");
  sendCommand("AT+CHAR0xFFE1");
  sendCommand("AT+NAMEbluino");
}
bool BluetoothCom::setupP(unsigned char (&aPins)[2]) {
    m_aPin[0] = aPins[0];
    m_aPin[1] = aPins[1];
    m_cSerial = new SoftwareSerial(A3, A2, false); // RX, TX / A for Analogue Pin prefix
    m_cSerial->begin(74880); //74880
    setupBLE();
    Serial.println("Setup BT : Done");
    return true;
}
void BluetoothCom::readSerial(G_eCommand& eCmd, unsigned char (&value)[nb_servo_per_leg]){
  Serial.println("Reading data");
  if(strlen((char*)m_aReply) > 0 && strlen((char*)m_aReply) >= 4) {
    if (m_aReply[0] == 77 && m_aReply[1] == 86) { // M : 77 / V : 86 e.g : MV100
      eCmd = G_eCommand::Move;
      value[0] = atoi((const char*) &m_aReply[2]); // Angular motion value
      value[1] = atoi((const char*) &m_aReply[6]);
      value[2] = atoi((const char*) &m_aReply[10]);
      Serial.print("converted");
      Serial.println(value[0]);
      Serial.println();
      Serial.println(value[1]);
      Serial.println(value[2]);
      return;
    }
    else if(m_aReply[0] == 73 && m_aReply[1] == 78 && m_aReply[2] == 70) {
      eCmd = G_eCommand::Infos;
      Serial.print("infos :");
      return;
    }
  }
  eCmd = G_eCommand::Unkown;
}
void BluetoothCom::recieve(G_eCommand& eCmd, unsigned char (&value)[nb_servo_per_leg]) {
    m_iCountReply = 0;
    while (m_cSerial->available() > 0) {
        m_aReply[m_iCountReply] = m_cSerial->read();
        //FOR DEBUG ONLY
        // m_cSerial->write(m_aReply[m_iCountReply]);
        // Serial.print("INT: ");
        // Serial.println((int)m_aReply[m_iCountReply]);
        // Serial.print("CHAR: ");
        // Serial.println(m_aReply[m_iCountReply], DEC);
        // Serial.print("DEC: ");
        // Serial.println(m_aReply[m_iCountReply], DEC);
        // Serial.print("HEX: ");
        // Serial.println(m_aReply[m_iCountReply], HEX);
        // Serial.print("BIN: ");
        // Serial.println(m_aReply[m_iCountReply], BIN);
        m_iCountReply += 1;
    }
    //end the string
    m_aReply[m_iCountReply] = '\0';
    if(m_iCountReply > 0){
      // Serial.print("Count read : ");
      // Serial.println(m_iCountReply);
      // Serial.println((char*)m_aReply);
      readSerial(eCmd, value);
    }
}
void BluetoothCom::writeToBLE(char value) {
  Serial.print("Writing hex :");
  Serial.println(value, HEX);
  m_cSerial->write(value);
}