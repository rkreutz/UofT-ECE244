/*
 * File:   Node.h
 * Author: JC and VB
 *
 * Created on October 5, 2012, 12:58 PM
 */

#ifndef NODE_H
#define	NODE_H

#define MAX_RESISTOR_NAME_LEN 20
#define GOOD 0
#define BAD 1
#include "ResistorList.h"



class Node
{
private:
   int key;
   int numRes; // number of resistors currently connected
   Node* next;
   ResistorList resLIST;
public:
   Node();
   Node(int nodeID);
   ~Node();
   int getKey () const;
   void addRes();
   void setNext (Node* pNext);
   Node* getNext () const;
   void print ();
   ResistorList* get_res_list();
   void removeRes(string name_);
   int getNumRes();

   //Clear all information of the Node.
   void clear ();

};


#endif	/* NODE_H */

