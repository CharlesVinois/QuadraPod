#include <LegController.h>

Leg::Leg() {
}
Leg::Leg(unsigned char& id,
         unsigned char (&pins)[nb_servo],
         unsigned char (&lims)[nb_servo][2],
         const bool (&isReversed)[nb_servo]) {
  if (&id != nullptr && &pins != nullptr && &lims != nullptr)
  {
    m_iId = id;
    setupP(pins, isReversed);
    get_aPos(m_aPos);
    set_aLims(lims);
    m_eState = Idle;
  }
}
Leg::~Leg() {
}
void Leg::get_aDest(unsigned char (&aDest)[nb_servo]) {
  for(unsigned char i = 0;i <= 2;i++)
  {
    m_aServs[i].get_iDest(m_aDest[i]);
    aDest[i] = m_aDest[i];
  }
}
void Leg::get_aPos(unsigned char (&aPos)[nb_servo]) {
  for(unsigned char i = 0;i <= 2;i++)
  {
    m_aServs[i].get_iPos(m_aPos[i]);
    aPos[i] = m_aPos[i];
  }
}
void Leg::set_aDest(unsigned char (&dest)[nb_servo]) {
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
void Leg::set_aLims(unsigned char (&lims)[nb_servo][2]) {
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
void Leg::get_aIsStatic(bool (&aIsStatic)[nb_servo]) {
  for(auto i = 0;i <= 2;i++)
  {
    m_aServs[i].get_bIsStatic(m_aIsStatic[i]);
    aIsStatic[i] = m_aIsStatic[i];
    m_bIsStatic = m_bIsStatic && m_aIsStatic[i];
  }
}
bool Leg::setupP(unsigned char (&aPins)[nb_servo],
                 const bool (&isReversed)[nb_servo]) {
  if (&aPins != NULL)
  {
    for(unsigned char i = 0;i <= 2;i++)
    {
      m_aIsReversed[i] = isReversed[i];
      m_aPin[i] = aPins[i];
      m_aServs[i].setupP(m_aPin[i], isReversed[i]);
    }
    return true;
  }
  return false;
}
bool Leg::moveP(const unsigned char (&speedReduction)[nb_servo]) {
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
void Leg::printInfos(SoftwareSerial& soSer) {
  Serial.println();
  Serial.println("leg : ");
  Serial.print("  id : ");
  Serial.println(int(m_iId));

  soSer.println();
  soSer.println("leg : ");
  soSer.print("  id : ");
  soSer.println(int(m_iId));
  for(int i = 0;i <= 2;i++) {
    m_aServs[i].printInfos(soSer);
  }
}