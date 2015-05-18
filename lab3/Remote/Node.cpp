#include "Node.h"

extern Node nodes[MAX_NODE_NUMBER+1];
extern int resID;
extern Resistor resArray[MAX_RESISTORS];

Node::Node () {
    numRes = 0;
}

bool Node::addResistor(int rIndex) {
    if ( numRes >= MAX_RESISTORS_PER_NODE ) {
        cout << "Error: node is full\n";
        return false;
    }
    
    else {
        resIDArray[numRes] = rIndex;
        numRes += 1;
        return true;
    }
}

void Node::delResistor(int rIndex) {
    numRes -= 1;
}

void Node::print(int nodeIndex) {
    cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)\n";
    int x,z;
    for (x=0;x<numRes;x++){
	cout << "  ";
        resArray[resIDArray[x]].print();
    }
}

Node::~Node() {
    
}
    
void Node::clear() {
    numRes = 0;
}
    
    
    
    
    
    
    
    
    
    
    
