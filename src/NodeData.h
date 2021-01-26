//
// Created by leoch on 25/01/2021.
//

#ifndef PROYECTO_2_DATOS_NODEDATA_H
#define PROYECTO_2_DATOS_NODEDATA_H
#include<iomanip>
#include<iostream>
using namespace std;
class NodeData{
public:
    int dData; // one data item
    NodeData(int dd); // constructor
    void displayItem(); // display item, format "27,"
};

NodeData::NodeData(int dd) {
    dData = dd;
}

void NodeData::displayItem() {
    cout<<dData<<" ";
}

#endif //PROYECTO_2_DATOS_NODEDATA_H