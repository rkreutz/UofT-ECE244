#include "NodeList.h"

NodeList::NodeList(){
    head = NULL;
}

NodeList::~NodeList(){
    Node* curr;
    Node* next2go;
    for(curr = head ; curr != NULL ; curr = next2go ){
        next2go = curr -> getNext();
        delete curr;
    }
    head = NULL;
}

Node* NodeList::find(int nodeID){
    Node* pNode;
    for(pNode = head; pNode != NULL ; pNode = pNode -> getNext() ){
        if (pNode -> getKey() == nodeID)
            return pNode;
    }
    return NULL;
}

Node* NodeList::create(int nodeID){
    Node* pNode;
    pNode = new Node(nodeID);
    return pNode;
}

void NodeList::organize(Node* lastADD){
    Node* prev;
    Node* curr;
    int x = BAD;
    prev = NULL;
    for(curr = head; curr != NULL && x != GOOD ; curr = curr -> getNext() ){
        if (curr -> getKey() > lastADD -> getKey()){
            if(prev == NULL){
                head = lastADD;
                lastADD -> setNext(curr);
                x = GOOD;
            }
            else {
                prev -> setNext(lastADD);
                lastADD -> setNext(curr);
                x = GOOD;
            }
        }
        prev = curr;
    }
    if (x == BAD){
        if (prev == NULL)
            head = lastADD;
        else
            prev -> setNext(lastADD);
    }
}

Resistor* NodeList::find_res(string name_){
    Resistor* pRes = NULL;
    Node* pNode;
    ResistorList* pRes_List;
    for(pNode = head ; pNode != NULL && pRes == NULL; pNode = pNode ->getNext()){
        pRes_List = pNode ->get_res_list();
        pRes = pRes_List ->find(name_);
    }
    return pRes;
}

void NodeList::delete_res(string name_){

}

void NodeList::print(){
    Node* pNode;
    for(pNode = head ; pNode != NULL ; pNode = pNode ->getNext()){
        pNode ->print();
    }
}

void NodeList::clear(){
    Node* curr;
    Node* next2go;
    for(curr = head ; curr != NULL; curr = next2go){
        next2go = curr->getNext();
        delete curr;
    }
}

Node* NodeList::getHead(){
    return head;
}
