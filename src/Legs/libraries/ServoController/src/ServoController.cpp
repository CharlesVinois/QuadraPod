#include <ServoControler.h>

int pulseWidth(char angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  Serial.println(analog_value);
  return analog_value;
}
Serv::Serv() {
}
Serv::Serv(const unsigned char& pin,
          Adafruit_PWMServoDriver* pwm) {
  m_cPwm = pwm;
    m_iPin = pin;
  m_aLim[0] = 40;
  m_aLim[1] = 100;
  m_eState = Stop;
  //setupP(pin, pwm);
}
Serv::~Serv() {
}
void Serv::get_iPin(unsigned char& pin) {
  pin = m_iPin;
}
void Serv::get_iPos(unsigned char& pos) {
  pos = m_iPos;
}
void Serv::get_iDest(unsigned char& dest) {
  dest = m_iDest;
}
void Serv::set_iDest(unsigned char& dest)
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
void Serv::get_iSpeedReduction(unsigned char& sr) {
  sr = m_iSpeedReduction;
}
void Serv::set_iSpeedReduction(unsigned char& sr) {
  m_iSpeedReduction = sr;
}
void Serv::get_ePosState(unsigned char& posState) {
  posState = m_ePosState;
}
void Serv::get_bClockWise(bool& clockW) {
  clockW = m_bIsClockwise;
}
void Serv::get_eExecState(G_eExecutionState& eState) {
  eState = m_eState;
}
void Serv::get_bIsStatic(bool& isStatic) {
  isStatic = m_bIsStatic;
}
 void Serv::get_bIsReversed(bool& isReversed) {
  isReversed = m_bIsReversed;
 }
// void Serv::setupP(const unsigned char& pin,
//                  Adafruit_PWMServoDriver& pwm) {
//   m_cPwm = &pwm;
//   m_iPin = pin;
//   m_aLim[0] = 40;
//   m_aLim[1] = 100;
//   m_eState = Stop;
// }
void Serv::moveP(const unsigned char& speedReduction) {
  if (m_iPos != m_iDest && m_eState == Idle)
  {
    m_eState = Run;
    if (m_iPos < m_iDest)
    {
      if (m_cPwm != 0)
      {
        m_cPwm->setPWM(m_iPin, 0, pulseWidth(m_iPos++));
      }
      m_bIsClockwise = true;
      m_bIsStatic = false;
    }
    else if(m_iPos > m_iDest)
    {
      if (m_cPwm != nullptr)
      {
        m_cPwm->setPWM(m_iPin, 0, pulseWidth(m_iPos--));
      }
      m_bIsClockwise = false;
      m_bIsStatic = false;
    }
    else
    {
      m_bIsStatic = true;
    }
    delay(1 * speedReduction);
    m_eState = Idle;
  }
}
void Serv::printInfos(SoftwareSerial* soSer) {  //TODO: Implement reflexivity
  Serial.println();
  Serial.println("servo : ");
  Serial.print("  pin : ");
  Serial.println(int(m_iPin));
  // Serial.print("  pos : ");
  // Serial.println(int(m_iPos));
  // Serial.print("  dest : ");
  // Serial.println(int(m_iDest));
  // Serial.print("  dist : ");
  // Serial.println(int(m_iDest) - int(m_iPos));
  // Serial.print("  lim : ");
  // Serial.print(int(m_aLim[0]));
  // Serial.print(", ");
  // Serial.println(int(m_aLim[1]));
  // Serial.print("  cloc : ");
  // Serial.println(m_bIsClockwise);
  // Serial.print("  static : ");
  // Serial.println(m_bIsStatic);
  // Serial.print("  spred : ");
  // Serial.println(int(m_iSpeedReduction));
  // Serial.print("  state : ");
  // Serial.println(int(m_eState));
  // Serial.print("  rever : ");
  // Serial.println(int(m_bIsReversed));

  // soSer->println();
  // soSer->println("servo : ");
  // soSer->print("  pin : ");
  // soSer->println(int(m_iPin));
  // soSer->print("  pos : ");
  // soSer->println(int(m_iPos));
  // soSer->print("  dest : ");
  // soSer->println(int(m_iDest));
  // soSer->print("  dist : ");
  // soSer->println(int(m_iDest) - int(m_iPos));
  // soSer->print("  lim : ");
  // soSer->print(int(m_aLim[0]));
  // soSer->print(", ");
  // soSer->println(int(m_aLim[1]));
  // soSer->print("  cloc : ");
  // soSer->println(m_bIsClockwise);
  // soSer->print("  static : ");
  // soSer->println(m_bIsStatic);
  // soSer->print("  rever : ");
  // soSer->println(int(m_bIsReversed));
  // soSer->print("  spred : ");
  // soSer->println(int(m_iSpeedReduction));
  // soSer.print("  state : ");
  // soSer.println(int(m_eState));
}