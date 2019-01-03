#include <string.h>

#include "Observer.h"
#include "Observable.h"

class Model : public Observable<Model> {
public:
  Model(){}
  virtual ~Model(){}
  //Getters and Setters
  void set_id(int id){ 
    this->id = id;	
  }	
  //
  void set_name(String name){
    this->name = name;
    notifyObservers();
  }
  //
  int get_id(){
    return id;
  }
  
  String get_name(){
    return name;
   }
   //
protected:
  int id;
  String name;
};

class ModelObserver : public Observer<Model> {
public:
  ModelObserver(){}
  virtual ~ModelObserver(){}
  void update(Model *observable){
    Serial.println("Model was Changed to:");
    Serial.print(observable->get_name());
    Serial.println("");
  }
};