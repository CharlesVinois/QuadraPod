#include <Servo.h>
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
    void move(const unsigned char& speedReduction = 1);
    void printInfos();
    void getPin(unsigned char& pin);
    void getPos(unsigned char& pos);
    void getDest(unsigned char& dest);
    void setDest(unsigned char& dest);
    void get_aLim(unsigned char& lim);
    void set_aLim(unsigned char& lim);
    void getSpeedReduction(unsigned char& sr);
    void setSpeedReduction(unsigned char& sr);
    void getPosState(unsigned char& posState);
    void getClockWise(bool& clockW);
    void getExecState(G_eExecutionState& eState);
  private:
    Servo* m_cServo;
    unsigned char m_iPin;
    unsigned char m_iPos = 90;
    unsigned char m_iDest = 90;
    unsigned char *m_aLim;
    bool m_bClockwise = true;
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
void Serv::get_aLim(unsigned char& aLim) {
  aLim = *m_aLim;
}
void Serv::set_aLim(unsigned char& aLim)
{
  m_aLim = &aLim;
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
void Serv::setupP(const unsigned char& pin) {
  m_iPin = pin;
  m_cServo = new Servo();
  m_aLim = new unsigned char(2);
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
void Serv::move(const unsigned char& speedReduction) {
  if (m_iPos != m_iDest && m_eState == Idle)
  {
    m_eState = Run;
    if (m_iPos < m_iDest)
    {
      m_cServo->write(m_iPos + 1);
      m_bClockwise = true;
    }
    else
    {
      m_cServo->write(m_iPos - 1);
      m_bClockwise = false;
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
    Leg(unsigned char& id, unsigned char& pins, unsigned char& lims);
    ~Leg();
    bool move(const unsigned char& speedReduction);
    void printPos();
    void get_aPin(unsigned char& pin);
    void get_aPos(unsigned char& pos);
    void get_aDest(unsigned char& dest);
    void set_aDest(unsigned char& dest);
    void set_aLims(unsigned char& lims);
    void get_aPosState(unsigned char& posState);
    void get_aClockWise(bool& clockW);
    void get_aExecState(G_eExecutionState eState[]);
    void printInfos();
  private:
    Serv* m_aServs;
    unsigned char m_iId;
    unsigned char* m_aPin;
    unsigned char* m_aPos;
    unsigned char* m_aDest;
    unsigned char** m_aLims;
    bool m_bClockwise = true;
    G_eExecutionState m_eState = Off;
};
Leg::Leg() {
}
Leg::Leg(unsigned char& id, unsigned char& pins, unsigned char& lims) {
  if (&id != nullptr && &pins != nullptr && &lims != nullptr)
  {
    m_iId = id;
    m_aPin = &pins;
    m_aServs = new Serv[3];
    m_aServs[0].setupP(m_aPin[0]);
    m_aServs[1].setupP(m_aPin[1]);
    m_aServs[2].setupP(m_aPin[2]);
    m_aPos = new unsigned char(3);
    m_aServs[0].getPos(m_aPos[0]);
    m_aServs[1].getPos(m_aPos[1]);
    m_aServs[2].getPos(m_aPos[2]);
    *m_aLims = &lims;
    set_aDest(*m_aLims);
    m_eState = Idle;
  }
}
Leg::~Leg() {
}
void Leg::get_aDest(unsigned char& aDest) {
  aDest = *m_aDest;
}
void Leg::get_aPos(unsigned char& pos) {
  m_aServs[0].getPos(m_aPos[0]);
  m_aServs[1].getPos(m_aPos[1]);
  m_aServs[2].getPos(m_aPos[2]);
  pos = *m_aPos;
}
void Leg::set_aDest(unsigned char& dest) {
  if (&dest != NULL)
  {
    m_aDest = &dest;
    m_aServs[0].setDest(m_aDest[0]);
    m_aServs[1].setDest(m_aDest[1]);
    m_aServs[2].setDest(m_aDest[2]);
  }
}
void Leg::set_aLims(unsigned char& lims) {
  if (&lims != NULL)
  {
    *m_aLims = &lims;
    m_aServs[0].set_aLim(&m_aLims[0]);
    m_aServs[1].set_aLim(&m_aLims[1]);
    m_aServs[2].set_aLim(&m_aLims[2]);
  }
}
bool Leg::move(const unsigned char& speedReduction) {
  m_eState = Run;
  m_aServs[0].move(speedReduction);
  m_aServs[1].move(speedReduction + 1);
  m_aServs[2].move(speedReduction + 2);
  m_eState = Idle;
  return true;
}
unsigned char G_aSpeedReduction[3] = {3, 3, 3};
unsigned char G_aLims[3][2] = {{40, 100}, {40, 100}, {40, 100}};
unsigned char G_aPins[3] = {2, 3, 4};
//unsigned char G_aPos[3] = {90, 90, 90};
unsigned char aDest[3] = {40, 40, 40};
Leg leg;
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  unsigned char id = 1;
  leg = Leg(id, *G_aPins, *G_aLims);
  leg.set_aDest(*aDest);
}
// the loop routine runs over and over again forever:
void loop() {
//Serial.println(serv->read());
 leg.move(*G_aSpeedReduction);
    leg.get_aDest(*aDest);

    leg.get_aPos(*G_aPos);
    char t = *G_aPos;
    if (*G_aPos == aDest[0]
        && *(G_aPos+1) == aDest[1] 
        && *(G_aPos+2) == aDest[2])
    {
        unsigned char a = random(40, 140);
        aDest[0] = a;
        aDest[1] = a;
        aDest[2] = a;
        leg.set_aDest(*aDest);
    }
}
