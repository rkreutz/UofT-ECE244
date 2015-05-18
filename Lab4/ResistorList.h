/*
 * File:   ResistorList.h
 * Author: noronh29
 *
 * Created on November 6, 2012, 3:04 PM
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H

#include "Resistor.h"


class ResistorList
{
private:
    Resistor* head;
public:
    ResistorList();
    ~ResistorList();
    Resistor* find(string name_);
    Resistor* getHead();
    void add(string name_, double resistance_ , int endPoint1 , int endPoint2);
    void remove(string name_);
};

#endif	/* RESISTORLIST_H */

