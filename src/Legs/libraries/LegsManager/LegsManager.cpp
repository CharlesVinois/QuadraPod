#include <LegsController.h>

Legs::Legs() {
}
Legs::Legs(unsigned char (&id)[nb_leg],
         Adafruit_PWMServoDriver& pwm,
         unsigned char (&pins)[nb_leg][nb_servo_per_Leg],
         unsigned char (&lims)[nb_leg][nb_servo_per_Leg][2],
         const bool (&isReversed)[nb_leg][nb_servo_per_Leg]) {
    m_iId = id;
    setupP(pins, pwm, isReversed);
    get_aPos(m_aPos);
    set_aLims(lims);
    m_eState = Idle;
}
Legs::~Legs() {
}
void Legs::onReceivedData(const Leg *sub) {
    Serial.print("Value is "); Serial.println(sub->getValue());
}
void Legs::get_aDest(unsigned char (&aDest)[nb_leg][nb_servo_per_Leg]) {
  for(unsigned char i = 0;i <= 2;i++)
  {
    m_aServs[i].get_iDest(m_aDest[i]);
    aDest[i] = m_aDest[i];
  }
}
void Legs::get_aPos(unsigned char (&aPos)[nb_leg][nb_servo_per_Leg]) {
  for(unsigned char i = 0;i <= 2;i++)
  {
    m_aServs[i].get_iPos(m_aPos[i]);
    aPos[i] = m_aPos[i];
  }
}
void Legs::set_aDest(unsigned char (&dest)[nb_leg][nb_servo_per_Leg]) {
  if (&dest != NULL)
  {
    for(unsigned char i = 0;i <= 2;i++)
    {
      if(m_aDest[i] != dest[i])
      {
        m_aDest[i] = dest[i];
        m_aServs[i].set_iDest(m_aDest[i]);
      }
    }
  }
}
void Legs::set_aLims(unsigned char (&lims)[nb_leg][nb_servo_per_Leg][2]) {
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
void Legs::get_aIsStatic(bool (&aIsStatic)[nb_leg][nb_servo_per_Leg]) {
  for(auto i = 0;i <= 2;i++)
  {
    m_aServs[i].get_bIsStatic(m_aIsStatic[i]);
    aIsStatic[i] = m_aIsStatic[i];
    m_bIsStatic = m_bIsStatic && m_aIsStatic[i];
  }
}
bool Legs::setupP(unsigned char (&aPins)[nb_leg][nb_servo_per_Leg],
                 const bool (&isReversed)[nb_leg][nb_servo_per_Leg]) {
    for(unsigned char i = 0;i <= 2;i++)
    {
      m_aIsReversed[i] = isReversed[i];
      m_aPin[i] = aPins[i];
      m_aServs[i].setupP(m_aPin[i], isReversed[i]);
    }
    Serial.println("Setup LEG : Done");
    return true;
}
bool Legs::moveP(const unsigned char (&speedReduction)[nb_leg][nb_servo_per_Leg]) {
  m_eState = Run;
  for(unsigned char i = 0;i <= 2;i++)
  {
    m_aServs[i].moveP(speedReduction[i]);
  }
  get_aIsStatic(m_aIsStatic);
  get_aPos(m_aPos);
  m_eState = Idle;
  return true;
}
void Legs::printInfos(SoftwareSerial& soSer) {
  Serial.println();
  Serial.println("Legs : ");
  Serial.print("  id : ");
  Serial.println(int(m_iId));

  soSer.println();
  soSer.println("Legs : ");
  soSer.print("  id : ");
  soSer.println(int(m_iId));
  for(int i = 0;i <= 2;i++) {
    m_aServs[i].printInfos(soSer);
  }
}