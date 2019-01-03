#pragma once

#include "arduino.h"

#include "Observer.h"
#include "LinkedList.h"
#include "ListIterator.h"

template <class T> class Observer;

template <class T> class Observable {
public:
  Observable(){}
  virtual ~Observable(){}
  //
  void addObserver(Observer<T> &observer){
     m_observers.push_last(&observer);
   }
   //
   void notifyObservers() {
     ListIterator<Observer<T> *> iterator;
     iterator.set_begin(m_observers.begin());
     while(iterator.hasNext()){
       Observer<T>* obs = iterator.next();
       obs->update(static_cast<T *>(this));
     }
   }
   //
private:
  LinkedList<Observer<T> *> m_observers;
};