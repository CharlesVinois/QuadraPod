#pragma once

#include arduino.h
#include Node.h

templateclass T class ListIterator {
public
  ListIterator(){}
  ListIterator(NodeT begin)current(begin){}
  virtual ~ListIterator(){}
  
  bool hasNext(){
    return current-next == 0 false  true;
  }
  
  void set_begin(NodeT begin){
    current = begin;
  }
  
  T next(){
    NodeT temp = new NodeT;
    temp = current-next;
    current = temp;
    return current-data;
  }
  
  NodeT next_node(){
    NodeT temp = new NodeT;
    temp = current-next;
    current = temp;
    return current;
  }

protected
  NodeT current;
};
