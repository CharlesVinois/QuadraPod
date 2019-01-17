#pragma once
//
#include "arduino.h"
#include "Node.h"
#include "ListIterator.h"

template<class T> class LinkedList {
public:
  //Constructor
  LinkedList():root(new Node<T>) {
    root->next = 0;
   }
   //Destructor
   virtual ~LinkedList() {}
   //
   //Method for Push some Data at the End of the list
   void push_last(T data) {
     Node<T>* temp = new Node<T>;
     temp = root;
     //The Iterating Part
     while (temp->next != 0) {
       	temp = temp->next;
     }
     //Pushing Part
     _last = new Node<T>(0, data);
     temp->next = _last; //new Node<T>(0, data);
    }
    
    void remove_last(){
      int rsize = get_list_size() - 2;
      int counter = 0;
      ListIterator<T>* riterator = new ListIterator<T>(root);
      while(riterator->hasNext()){
        Node<T>* ntemp = riterator->next_node();
        if(counter == rsize){
          ntemp->next = NULL;
          break;
         }
         counter++;
	}
	delete riterator;
     }

    //Get The List Size
    int get_list_size() {
      int counter = 0;
      Node<T>* temp; //= new ListNode;
      temp = root;
      while (temp->next != NULL) {
        temp = temp->next;
        counter++;
      }
      //
      return counter;
    }

    //Verify the Emptiness of the list
    boolean isEmpty(){
      return get_list_size() == 0? true : false;
    }
    
    void remove_index(int index){
      if (index > 0) {
        int counter = 0;
        ListIterator<T>* riterator = new ListIterator<T>(root);
        Node<T>* temp;
        while (riterator->hasNext()) {
          temp = riterator->next_node();
          if (counter == index - 1)
            break;
            counter++;
          }
          temp->next = temp->next->next;
          delete riterator;
	}
    }

  //Get Selected Index
  T get_index(int index){
    int counter = 0;
    T temp;
    ListIterator<T>* iterator = new ListIterator<T>(root);
    while(iterator->hasNext()){
      temp = iterator->next();
      	if(counter == index)break;
      counter++;
     }
     //
     delete iterator;
     return temp;
  }

  //Get the First Node;
  Node<T>* begin() {
    return root;
  }

  //Get the Last Node;
  Node<T>* last() {
    return _last;
  }

protected:
  Node<T>* root;
  Node<T>* _last;
};