#include <Servo.h>
#include <SoftwareSerial.h>
#include <stdio.h>
#define nullptr NULL
enum G_eExecutionState {
  Off = 0,
  Setup = 1,
  Idle = 2,
  Run = 3,
  Stop = 4
};
enum G_ePositionV {
  Up = 0,
  UMi = 1,
  MidleV = 2,
  BoMi = 3,
  Bottom = 4
};
enum G_ePositionH {
  Left = 0,
  LeMi = 1,
  MidleH = 2,
  RiMi = 3,
  Right = 4
};
class Serv
{
  public:
    Serv(const unsigned char& pin);
    Serv();
    ~Serv();
    void setupP(const unsigned char& pin);
    void moveP(const unsigned char& speedReduction = 1);
    void printInfos();
    void getPin(unsigned char& pin);
    void getPos(unsigned char& pos);
    void getDest(unsigned char& dest);
    void setDest(unsigned char& dest);
    void get_aLim(unsigned char (&aLim)[2]);
    void set_aLim(unsigned char (&aLim)[2]);
    void getSpeedReduction(unsigned char& sr);
    void setSpeedReduction(unsigned char& sr);
    void getPosState(unsigned char& posState);
    void getClockWise(bool& clockW);
    void getIsStatic(bool& isStatic);
    void getExecState(G_eExecutionState& eState);
  private:
    Servo* m_cServo;
    unsigned char m_iPin;
    unsigned char m_iPos = 90;
    unsigned char m_iDest = 90;
    unsigned char m_aLim[2];
    bool m_bClockwise = true;
    bool m_bIsStatic = true;
    unsigned char m_ePosState = 0;//associate to enum pos
    unsigned char m_iSpeedReduction = 1;
    G_eExecutionState m_eState = Off;
};
Serv::Serv() {
}
Serv::Serv(const unsigned char& pin) {
  setupP(pin);
}
Serv::~Serv() {
}
void Serv::getPin(unsigned char& pin) {
  pin = m_iPin;
}
void Serv::getPos(unsigned char& pos) {
  pos = m_iPos;
}
void Serv::getDest(unsigned char& dest) {
  dest = m_iDest;
}
void Serv::setDest(unsigned char& dest)
{
  if ((dest >= m_aLim[0]) && (dest <= m_aLim[1]))
  {
    m_iDest = dest;
  }
}
void Serv::get_aLim(unsigned char (&aLim)[2]) {
  aLim[0] = m_aLim[0];
  aLim[1] = m_aLim[1];
}
void Serv::set_aLim(unsigned char (&aLim)[2])
{
  m_aLim[0] = aLim[0];
  m_aLim[1] = aLim[1];
}
void Serv::getSpeedReduction(unsigned char& sr) {
  sr = m_iSpeedReduction;
}
void Serv::setSpeedReduction(unsigned char& sr) {
  m_iSpeedReduction = sr;
}
void Serv::getPosState(unsigned char& posState) {
  posState = m_ePosState;
}
void Serv::getClockWise(bool& clockW) {
  clockW = m_bClockwise;
}
void Serv::getExecState(G_eExecutionState& eState) {
  eState = m_eState;
}
void Serv::getIsStatic(bool& isStatic) {
  isStatic = m_bIsStatic;
}
void Serv::setupP(const unsigned char& pin) {
  m_iPin = pin;
  m_cServo = new Servo();
  m_aLim[0] = 40;
  m_aLim[1] = 100;
  if (m_cServo != 0)
  {
    m_cServo->attach(m_iPin);
    /*bool i = */m_cServo->attached();
    delay(600);
    m_iPos = m_cServo->read();
    m_eState = Idle;
    return;
  }
  m_eState = Stop;
}
void Serv::moveP(const unsigned char& speedReduction) {
  if (m_iPos != m_iDest && m_eState == Idle)
  {
    m_eState = Run;
    if (m_iPos < m_iDest)
    {
      m_cServo->write(m_iPos + 1);
      m_bClockwise = true;
      m_bIsStatic = false;
    }
    else if(m_iPos > m_iDest)
    {
      m_cServo->write(m_iPos - 1);
      m_bClockwise = false;
      m_bIsStatic = false;
    }
    else
    {
      m_bIsStatic = true;
    }
    delay(1 * speedReduction);
    m_iPos = m_cServo->read();
    //printInfos();
    m_eState = Idle;
  }
}
void Serv::printInfos() {
  m_iPos = m_cServo->read();
  Serial.println();
  Serial.println(int(m_iPin));
  Serial.println(int(m_iDest) - int(m_iPos));
}
class Leg
{
  public:
    Leg();
    Leg(unsigned char& id, unsigned char (&pins)[3], unsigned char (&lims)[3][2]);
    ~Leg();
    bool setupP(unsigned char (&pins)[3]);
    bool moveP(const unsigned char (&speedReduction)[3]);
    void printPos();
    void get_aPin(unsigned char (&aPin)[3]);
    void get_aPos(unsigned char (&aPos)[3]);
    void get_aDest(unsigned char (&aDest)[3]);
    void set_aDest(unsigned char (&aDest)[3]);
    void set_aLims(unsigned char (&aLims)[3][2]);
    void get_aPosState(unsigned char& aPosState);
    void get_aClockWise(bool& aClockW);
    void get_aIsStatic(bool& aIsStatic);
    void get_aExecState(G_eExecutionState eState[]);
    void readSerial(unsigned char (&reply)[50]);
    void printInfos();
  private:
    Serv m_aServs[3];
    unsigned char m_iId;
    unsigned char m_aPin[3];
    unsigned char m_aPos[3];
    unsigned char m_aDest[3];
    unsigned char m_aLims[3][2];
    bool m_bClockwise = true;
    bool m_bIsStatic = true;
    G_eExecutionState m_eState = Off;
};
Leg::Leg() {
}
Leg::Leg(unsigned char& id, unsigned char (&pins)[3], unsigned char (&lims)[3][2]) {
  if (&id != nullptr && &pins != nullptr && &lims != nullptr)
  {
    m_iId = id;
    //m_aServs = new Serv[3];
    setupP(pins);
    get_aPos(m_aPos);
    //unsigned char k = *(m_aPos);
    //unsigned char k1 = *(m_aPos + 1);
    //unsigned char k2 = *(m_aPos + 2);
    //m_aLims = new unsigned char*[3];
    set_aLims(lims);
    m_eState = Idle;
  }
}
Leg::~Leg() {
}
void Leg::get_aDest(unsigned char (&aDest)[3]) {
  for(unsigned char i = 0;i <= 2;i++)
  {
    m_aServs[i].getDest(m_aDest[i]);
    aDest[i] = m_aDest[i];
  }
}
void Leg::get_aPos(unsigned char (&aPos)[3]) {
  for(unsigned char i = 0;i <= 2;i++)
  {
    m_aServs[i].getPos(m_aPos[i]);
    aPos[i] = m_aPos[i];
  }
}
void Leg::set_aDest(unsigned char (&dest)[3]) {
  if (&dest != NULL)
  {
    for(unsigned char i = 0;i <= 2;i++)
    {
      if(m_aDest[i] != dest[i])
      {
        m_aDest[i] = dest[i];
        m_aServs[i].setDest(m_aDest[i]);
        Serial.println("new dest");
        Serial.println(*dest);
      }
    }
  }
}
void Leg::set_aLims(unsigned char (&lims)[3][2]) {
  if (&lims != NULL)
  {
    for(unsigned char i = 0;i <= 2;i++)
    {
        m_aLims[i][0] = lims[i][0];
      m_aLims[i][1] = lims[i][1];
        m_aServs[i].set_aLim(m_aLims[i]);
    }
  }
}
void Leg::get_aIsStatic(bool& aIsStatic) {
  aIsStatic = m_bIsStatic;
}
bool Leg::setupP(unsigned char (&aPins)[3]) {
  if (&aPins != NULL)
  {
    for(unsigned char i = 0;i <= 2;i++)
    {
      m_aPin[i] = aPins[i];
      m_aServs[i].setupP(m_aPin[i]);
    }
    return true;
  }
  return false;
}
bool Leg::moveP(const unsigned char (&speedReduction)[3]) {
  m_eState = Run;
  for(unsigned char i = 0;i <= 2;i++)
  {
    m_aServs[i].moveP(speedReduction[i]);
  }
  get_aPos(m_aPos);
  m_eState = Idle;
  return true;
}
SoftwareSerial mySerial(A3, A2); // RX, TX
void sendCommand(const char * command){
  Serial.print("Command send :");
  Serial.println(command);
  mySerial.println(command);
  //wait some time
  delay(100);
  char reply[100];
  int i = 0;
  while (mySerial.available()) {
    reply[i] = mySerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  Serial.print(reply);
  Serial.println("Reply end");
}
void setupBLE() {
  sendCommand("AT");
  sendCommand("AT+ROLE0");
  sendCommand("AT+UUID0xFFE0");
  sendCommand("AT+CHAR0xFFE1");
  sendCommand("AT+NAMEbluino");
}
void Leg::readSerial(unsigned char (&reply)[50]){
  if(strlen((const char *)reply) > 0 && strlen((const char *)reply) >= 4){
    //Serial.print((char*)reply);
    Serial.println("We have just read some data");
    Serial.println(reply[0]);
    Serial.println(reply[1]);
    if (reply[0] == 77 && reply[1] == 86)
    {
      unsigned char a;
      int tmp = atoi((const char*) &reply[2]);
      Serial.println("convert");
      Serial.println(tmp);
      a = tmp;
      Serial.println(a);
      unsigned char aDest[3] = {a, a, a};
      Serial.println(*aDest);
      set_aDest(aDest);
    }
  }
}
void writeToBLE(char value) {
  Serial.print("Writing hex :");
  Serial.println(value, HEX);
  mySerial.write(value);
}
unsigned char G_aSpeedReduction[3] = {8, 4, 1};
unsigned char G_aLims[3][2] = {{40, 100}, {40, 100}, {40, 100}};
unsigned char G_aPins[3] = {2, 3, 4};
unsigned char G_aPos[3] = {0, 0, 0};
unsigned char aDest[3] = {40, 40, 40};
unsigned char aReply[50];
Leg leg;
int i;
// the setup routine runs once when you press reset:
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  i = 0;
  unsigned char id = 1;
  leg = Leg(id, G_aPins, G_aLims);
  //leg.set_aDest(aDest);
  setupBLE();
}
void loop() {;
  if (mySerial.available() && i < 50) {
    delay(10);
    aReply[i] = mySerial.read();
    i += 1;
  }
  else
  {
    //end the string
    aReply[i] = '\0';
    i = 0;
    leg.readSerial(aReply);
  }
  leg.moveP(G_aSpeedReduction);
  //leg.get_aDest(aDest);
  //leg.get_aPos(G_aPos);
}
