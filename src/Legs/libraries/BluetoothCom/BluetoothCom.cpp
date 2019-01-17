#include <BluetoothCom.h>

BluetoothCom::BluetoothCom() {
}
BluetoothCom::BluetoothCom(unsigned char& id, unsigned char (&pins)[2]) {
  if (&id != nullptr && &pins != nullptr) {
    m_iId = id;
    m_iCountReply = 0;
    setupP(pins);
    m_eState = Idle;
  }
}
BluetoothCom::~BluetoothCom() {
}
void BluetoothCom::sendCommand(const char * command){
  Serial.print("Command send :");
  Serial.println(command);
  m_cSerial->println(command);
  delay(300);
}
void BluetoothCom::get_cSoSerial(SoftwareSerial& soSerial) {
  soSerial = *m_cSerial;
}
void BluetoothCom::setupBLE() {
  sendCommand("AT");
  sendCommand("AT+ROLE0");
  sendCommand("AT+UUID0xFFE0");
  sendCommand("AT+CHAR0xFFE1");
  sendCommand("AT+NAMEbluino");
}
bool BluetoothCom::setupP(unsigned char (&aPins)[2]) {
  if (&aPins != NULL) {
    m_aPin[0] = aPins[0];
    m_aPin[1] = aPins[1];
    m_cSerial = new SoftwareSerial(A3, A2, false); // RX, TX / A for Analogue Pin prefix
    m_cSerial->begin(9600);
    setupBLE();
    return true;
  }
  return false;
}
void BluetoothCom::readSerial(G_eCommand& eCmd, unsigned char (&value)[nb_servo]){
  if(strlen((const char *)m_aReply) > 0 && strlen((const char *)m_aReply) >= 4) {
    Serial.println("We have just read some data");
    Serial.println(m_aReply[0]);
    Serial.println(m_aReply[1]);
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
void BluetoothCom::recieve(G_eCommand& eCmd, unsigned char (&value)[nb_servo]) {
    if (m_cSerial->available() && m_iCountReply < max_string) {
        delay(200);
        m_aReply[m_iCountReply] = m_cSerial->read();
        m_iCountReply += 1;
    }
    else {
        //end the string
        m_aReply[m_iCountReply] = '\0';
        m_iCountReply = 0;
        readSerial(eCmd, value);
    }
}
void BluetoothCom::writeToBLE(char value) {
  Serial.print("Writing hex :");
  Serial.println(value, HEX);
  m_cSerial->write(value);
}