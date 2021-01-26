//
// Created by leoch on 25/01/2021.
//

#ifndef PROYECTO_2_DATOS_NODEDATA_H
#define PROYECTO_2_DATOS_NODEDATA_H
#include<iomanip>
#include<iostream>
using namespace std;
class NodeData{
private:
    int dData; // one data item
public:
    int getData() const;
    void setData(int _data);
    NodeData(int dd); // constructor
    void displayItem(); // display item, format "27,"
};

int NodeData::getData() const {
    return this->dData;
}

void NodeData::setData(int _data){
    dData = _data;
}

NodeData::NodeData(int dd) {
    this->dData = dd;
}

void NodeData::displayItem() {
    cout<<dData<<" ";
}

#endif //PROYECTO_2_DATOS_NODEDATA_H