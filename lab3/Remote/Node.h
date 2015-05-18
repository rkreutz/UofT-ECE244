/* 
 * File:   Node.h
 * Author: JC and VB
 *
 * Created on October 5, 2012, 12:58 PM
 */

#ifndef NODE_H
#define	NODE_H

#define MAX_RESISTORS_PER_NODE 5
#define MAX_RESISTORS 20
#define MAX_NODE_NUMBER 9
#define MIN_NODE_NUMBER 0
#define MAX_RESISTOR_NAME_LEN 20
#define GOOD 0
#define BAD 1

#include "Resistor.h"





class Node
{
private:
    
   int numRes; // number of resistors currently connected
   int resIDArray[MAX_RESISTORS_PER_NODE]; // stores the index of each resistor connected

public:
   Node();
   ~Node();

   // Updates resIDArray to show the resistor in position rIndex in
   // the resistor array is now connected to this node.
   // Returns true if successful
   bool addResistor (int rIndex); 
   
   void delResistor (int rIndex);   //will delete the last resistor stored in the node.

   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   void print (int nodeIndex); 
   
   //Clear all information of the Node.
   void clear ();

};


#endif	/* NODE_H */

