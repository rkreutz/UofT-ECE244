/*
 * File:   NodeList.h
 * Author: noronh29
 *
 * Created on November 6, 2012, 3:04 PM
 */

#ifndef NODELIST_H
#define	NODELIST_H
#include "Node.h"
#include "Resistor.h"

class NodeList
{
private:
    Node* head;
public:
    NodeList();
    ~NodeList();
    Node* find (int nodeID);
    Node* create (int nodeID);
    void organize (Node* lastADD);
    Resistor* find_res(string name_);
    void delete_res(string name_);
    void print();
    void clear();
    Node* getHead();
};




#endif	/* NODELIST_H */

