#include "Pattern.h"
void setup(){
  Serial.begin(9600);
  Model *model = new Model;
  model->set_id(5036);
  model->set_name("Jhon Doe");
  //
  ModelObserver *m_observer = new ModelObserver;
  model->addObserver(*m_observer);
  
  model->set_name("Another Guy from other Place");
  model->set_name("This is ia fake Name!!");
  model->set_name("Back to the Future!!!");
}

void loop(){
}
