#include "ResistorList.h"


ResistorList::ResistorList(){
    head = NULL;
}

ResistorList::~ResistorList(){
    Resistor* curr;
    Resistor* next2go;
    for(curr = head ; curr != NULL ; curr = next2go){
        next2go = curr ->getNext();
        delete curr;
    }
}

Resistor* ResistorList::find(string name_){
    Resistor* pRes;
    for(pRes = head ; pRes != NULL ; pRes = pRes -> getNext()){
        if (name_ == pRes -> getName()){
            return pRes;
        }
    }
    return pRes;
}

void ResistorList::add(string name_, double resistance_ , int endPoint1 , int endPoint2){
    int endPoints_[2] = {endPoint1 , endPoint2};
    Resistor* pADD = new Resistor (name_ , resistance_ , endPoints_);
    Resistor* curr;
    Resistor* prev;
    prev = NULL;
    for(curr = head ; curr != NULL ; curr = curr -> getNext()){
        prev = curr;
    }
    if (prev == NULL){
        head = pADD;
    }
    else{
        prev -> setNext(pADD);
    }
}

Resistor* ResistorList::getHead(){
    return head;
}

void ResistorList::remove(string name_){
    Resistor* prev;
    Resistor* curr;
    Resistor* next_one;
    prev = NULL;
    next_one = NULL;
    for(curr = head ; curr != NULL ; curr = next_one){
        next_one = curr->getNext();
        if(curr->getName() == name_)
            break;
        prev = curr;
    }
    delete curr;
    if(prev == NULL)
        head = next_one;
    else{
        prev->setNext(next_one);
    }
}
