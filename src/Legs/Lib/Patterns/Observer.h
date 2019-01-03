#pragma once
//
#include "arduino.h"
#include "Observable.h"

template <class T> class Observable;

template <class T>class Observer {
public:
  Observer() {}
  virtual ~Observer() {}
  virtual void update(T *observable) = 0;
};
