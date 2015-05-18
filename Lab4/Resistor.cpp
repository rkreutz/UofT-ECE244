#include "Resistor.h"
#include "Node.h"

Resistor::Resistor(string name_, double resistance_, int endpoints_[2]) {
    if ( name_.size() > MAX_RESISTOR_NAME_LEN )
        name_.resize( MAX_RESISTOR_NAME_LEN );
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    next = NULL;
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

Resistor* Resistor::getNext(){
    return next;
}

void Resistor::setNext(Resistor* pNext){
    next = pNext;
}

int Resistor::get_last_endpoint(){
    if(endpointNodeIDs[0] > endpointNodeIDs[1])
        return endpointNodeIDs[0];
    else
        return endpointNodeIDs[1];
}

int Resistor::get_first_endpoint(){
    if(endpointNodeIDs[0] > endpointNodeIDs[1])
        return endpointNodeIDs[1];
    else
        return endpointNodeIDs[0];
}
