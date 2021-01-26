//
// Created by leoch on 25/01/2021.
//

#ifndef PROYECTO_2_DATOS_NODE_H
#define PROYECTO_2_DATOS_NODE_H
#include "NodeData.h"
#include <vector>
#include<iomanip>
#include<iostream>
using namespace std;

class Node {
private:
    int ORDER = 4;
    int numItems{};
    Node* parent{};
    vector<Node*> childArray;
    vector<NodeData*> itemArray;
public:
    Node();
    void connectChild(int childNum, Node* child); // connect child to this node
    Node* disconnectChild(int childNum); // disconnect child from this node, return it
    Node* getChild(int childNum);
    Node* getParent();
    bool isLeaf();
    int getNumItems();
    NodeData* getItem(int index); // get NodeData at index
    NodeData* setItem(int index, NodeData* theValue); // get NodeData at index
    void setNumItems(int theValue);
    bool isFull();
    int insertItem(NodeData* newItem);
    void insertatfront(NodeData* newItem);
    NodeData* removeItem(); // remove largest item
    void displayNode();
    void displayvalue(int j);
    void deletenodevalue(int theValue);
    void deletevalue(int theValue, string side);
    Node* getsibiling(int theValue);
};

Node::Node(){
    for(int i=0; i < ORDER ; i++){
        childArray[i]=NULL;
    }
    for(int i=0; i < ORDER-1 ; i++){
        itemArray[i]=NULL;
    }
}

void Node::connectChild(int childNum, Node* child) {
    childArray[childNum] = child;
    if (child!=NULL)
        child->parent = this;
}

Node* Node::disconnectChild(int childNum) {
    Node* tempNode = childArray[childNum];
    childArray[childNum] = NULL;
    return tempNode;
}

Node* Node::getChild(int childNum) {
    return childArray[childNum];
}

Node* Node::getParent() {
    return parent;
}

bool Node::isLeaf() {
    return (childArray[0] == NULL) ? true : false;
}

int Node::getNumItems() {
    return numItems;
}

void Node::setNumItems(int theValue) {
    numItems = theValue;
    return;
}

NodeData* Node::getItem(int index)
{
    return itemArray[index];
}

NodeData* Node::setItem(int index, NodeData* theValue)
{
    itemArray[index] = theValue;
    return itemArray[index];
}

bool Node::isFull() {
    return (numItems == ORDER - 1) ? true : false;
}

int Node::insertItem(NodeData* newItem) {
    // assumes node is not full
    numItems++; // will add new item
    int newKey = newItem->dData; // key of new item

    // Should start this for loop at numItems-1, rather than ORDER -2

    for (int j = ORDER - 2; j >= 0; j--) // start on right,
    { // examine items
        if (itemArray[j] == NULL) // if item null,
            continue; // go left one cell
        else // not null,
        { // get its key
            int itsKey = itemArray[j]->dData;
            if (newKey < itsKey) // if it's bigger
                itemArray[j + 1] = itemArray[j]; // shift it right
            else {
                itemArray[j + 1] = newItem; // insert new item
                return j + 1; // return index to
            } // new item
        } // end else (not null)
    } // end for // shifted all items,
    itemArray[0] = newItem; // insert new item
    return 0;
} // end insertItem()

void Node::insertatfront(NodeData* newItem) {

    int newKey = newItem->dData; // key of new item
    numItems++;
    for (int j = numItems - 1; j > 0; j--) {
        itemArray[j] = itemArray[j - 1];
        connectChild(j + 1, disconnectChild(j));
    }
    connectChild(1, disconnectChild(0));
    itemArray[0] = newItem;
    connectChild(0, NULL);

    return;
}

NodeData* Node::removeItem() {
    // assumes node not empty
    NodeData* temp = itemArray[numItems - 1]; // save item
    itemArray[numItems - 1] = NULL; // disconnect it
    numItems--; // one less item
    return temp; // return item
}

void Node::displayNode() // format "/24/56/74/"
{
    for (int j = 0; j < numItems; j++)
        itemArray[j]->displayItem(); // "56,"
    // System.out.println();
}

void Node::displayvalue(int j) // format "/24/56/74/"
{
    itemArray[j]->displayItem(); // "/56"
    cout<<"/"; // final "/"
}

void Node::deletenodevalue(int theValue) {
    // Only valid for leafs
    int flag = -1;
    // just delete the value and decrease node size
    for (int i = 0; i < numItems; i++) {
        if (theValue == itemArray[i]->dData) {
            flag = i;
        }
        if (flag != -1 && i + 1 < numItems) {
            itemArray[i]->dData = itemArray[i + 1]->dData;
        }
    }
    itemArray[numItems - 1] = NULL; // disconnect it
    numItems--; // one less item

}

void Node::deletevalue(int theValue, string side) {
    // Only valid for leafs
    int flag = -1;
    // just delete the value and decrease node size
    for (int i = 0; i < numItems; i++) {
        if (theValue == itemArray[i]->dData) {
            flag = i;
        }
        if (flag != -1 && i + 1 < numItems) {
            itemArray[i]->dData = itemArray[i + 1]->dData;
        }
    }
    itemArray[numItems - 1] = NULL; // disconnect it
    numItems--; // one less item

}

Node* Node::getsibiling(int theValue) {
    // get the sibling
    Node * x;
    Node* p = getParent();
    if (numItems != 0) {
        for (int i = 0; i <= p->numItems; i++) {
            if (p->childArray[i]->itemArray[0]->dData < theValue) {
                x = p->childArray[i];
            }
        }
    } else if (numItems == 0) {
        for (int i = 0; i <= p->numItems; i++) {
            if (p->childArray[i]->itemArray[0] == NULL) {
                if (i != 0) {
                    x = p->childArray[i - 1];
                }
            }
        }
    }
    return x;
}

#endif //PROYECTO_2_DATOS_NODE_H
