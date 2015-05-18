#include "Node.h"

Node::Node () {
    numRes = 0;
    key = 0;
    next = NULL;
}

Node::Node(int nodeID) {
    numRes = 0;
    key = nodeID;
    next = NULL;
}

void Node::print() {
    if(numRes > 0){
        cout << "Connections at node " << key << ": " << numRes << " resistor(s)\n";
        ResistorList* p_Res_List;
        p_Res_List = get_res_list();
        Resistor* pRes;
        for (pRes = p_Res_List ->getHead() ; pRes != NULL ; pRes = pRes ->getNext()){
            cout << "  ";
            pRes ->print();
        }
    }
}

Node::~Node() {

}

void Node::clear() {
    numRes = 0;
}

int Node::getKey() const{
    return key;
}

void Node::setNext(Node* pNext){
    next = pNext;
}

Node* Node::getNext() const{
    return next;
}

ResistorList* Node::get_res_list(){
    return (&resLIST);
}

void Node::addRes(){
    numRes += 1;
}

void Node::removeRes(string name_){
    numRes -= 1;
    resLIST.remove(name_);
}

int Node::getNumRes()
{
    return numRes;
}
