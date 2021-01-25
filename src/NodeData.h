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

    NodeData(int dd) // constructor
    {
        this->dData = dd;
    }

    void displayItem() // display item, format "27,"
    {
        cout<<dData<<+",";
    }
};
#endif //PROYECTO_2_DATOS_NODEDATA_H
