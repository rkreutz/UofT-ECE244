/*
 * File:   Resistor.h
 * Author: JC and VB
 *
 * Created on October 5, 2012, 1:01 PM
 */

#ifndef RESISTOR_H
#define	RESISTOR_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;


class Resistor
{
private:
   double resistance; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to
   Resistor* next;

public:
   Resistor(string name_,double resistance_,int endpoints_[2]);
   // rIndex_ is the index of this resistor in the resistor array
   // endpoints_ holds the node indices to which this resistor connects

   ~Resistor();
   Resistor();  //default constructor and destructor

   Resistor &operator= ( Resistor r ); //Function to use '=' for variables of class 'Resistor'.

   string getName() const; // returns the name
   double getResistance() const; // returns the resistance
   int get_last_endpoint();
   int get_first_endpoint();

   void setResistance (double resistance_);

   Resistor* getNext();
   void setNext(Resistor* pNext);


   // you *may* create either of the below to print your resistor
   void print ();
};





#endif	/* RESISTOR_H */

