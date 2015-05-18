#include "DBentry.h"
DBentry::DBentry(){
    name = "\0";
    IPaddress = 0;
    active = false;
}

DBentry::DBentry(string _name , unsigned int _IPaddress , bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

DBentry::~DBentry(){

}

void DBentry::setName(string _name){
    name = _name;
}

void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}

void DBentry::setActive(bool _active){
    active = _active;
}

string DBentry::getName() const{
    return name;
}

unsigned int DBentry::getIPaddress() const{
    return IPaddress;
}

bool DBentry::getActive() const{
    return active;
}

ostream& operator<< (ostream& out , const DBentry& rhs){
    out << rhs.name;
    out << " : ";
    out << rhs.IPaddress;
    out << " : ";
    if (rhs.active == true)
        out << "active\n";
    else
        out << "inactive\n";
    return (out);
}
