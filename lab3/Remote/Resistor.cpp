#include "Resistor.h"

extern Node nodes[MAX_NODE_NUMBER+1];
extern int resID;
//extern Resistor resArray[MAX_RESISTORS];

Resistor::Resistor(int rIndex_, string name_, double resistance_, int endpoints_[2]) {
    if ( name_.size() > MAX_RESISTOR_NAME_LEN )
        name_.resize( MAX_RESISTOR_NAME_LEN );
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    rIndex = rIndex_;
}

Resistor::~Resistor() {
    
}

Resistor::Resistor() {
    
}

Resistor &Resistor::operator=(Resistor r) {
    name = r.name;
    resistance = r.resistance;
    endpointNodeIDs[0] = r.endpointNodeIDs[0];
    endpointNodeIDs[1] = r.endpointNodeIDs[1];
    rIndex = r.rIndex;
}

string Resistor::getName() const{
    return name;
}

double Resistor::getResistance() const{
    return resistance;
}

void Resistor::setResistance(double resistance_) {
    resistance = resistance_;
}

void Resistor::print() {
    cout.precision(1);
    cout.setf(ios_base::left,ios_base::adjustfield);
    cout << setw( MAX_RESISTOR_NAME_LEN ) << name;
    cout.setf(ios_base::right,ios_base::adjustfield);
    cout << setw(7) << fixed << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}

int Resistor::getIndex() const{
    return rIndex;
}
