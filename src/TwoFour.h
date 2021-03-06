//
// Created by leoch on 25/01/2021.
//

#ifndef PROYECTO_2_DATOS_TWOFOUR_H
#define PROYECTO_2_DATOS_TWOFOUR_H
#include "Node.h"
#include "NodeData.h"
#include<iomanip>
#include<iostream>
using namespace std;
class TwoFour {

private:
    Node* root = new Node(); // make root node
public:
    void insert( int dValue); // insert a NodeData
    void split(Node* thisNode); // split the node
    Node* getNextChild(Node* theNode, int theValue);
    void displayTree(int i);
    void recDisplayTree(Node* thisNode, int level, int childNumber);
    void inorderdisplay(Node* thisNode, int level, int childNumber);
    Node* find(int theValue);
    Node* findvalue(Node* theNode, int theValue);
    Node* deleteNode(Node* currnode, int theValue);
    Node* deleteleaf_cases(Node* thisNode, int theValue);
    Node* balancetree(Node* currnode);
    Node* getinordernode(Node* thisNode);
};

// Performs the splits
// in a top-down (root -----> leaf) fashion.
void TwoFour::insert( int dValue) {
    Node* curNode = root;
    auto* tempItem = new NodeData(dValue);
    while (true) {
        if (curNode->isFull()) // if node full,
        {
            split(curNode); // split it
            curNode = curNode->getParent(); // back up
            // search once
            curNode = getNextChild(curNode, dValue);
        } // end if(node is full)

        else if (curNode->isLeaf()) // if node is leaf,
            break; // go insert
            // node is not full, not a leaf; so go to lower level
        else
            curNode = getNextChild(curNode, dValue);
    } // end while

    curNode->insertItem(tempItem); // insert new NodeData
} // end insert()

void TwoFour::split(Node* thisNode) {
    // assumes node is full
    NodeData * itemB, * itemC;
    Node * parent, * child2, * child3;
    int itemIndex;

    itemC = thisNode->removeItem(); // remove items from
    itemB = thisNode->removeItem(); // this node
    child2 = thisNode->disconnectChild(2); // remove children
    child3 = thisNode->disconnectChild(3); // from this node

    Node* newRight = new Node(); // make new node

    if (thisNode == root) // if this is the root,
    {
        root = new Node(); // make new root
        parent = root; // root is our parent
        root->connectChild(0, thisNode); // connect to parent
    } else
        // this node not the root
        parent = thisNode->getParent(); // get parent

    // deal with parent
    itemIndex = parent->insertItem(itemB); // item B to parent
    int n = parent->getNumItems(); // total items?

    for (int j = n - 1; j > itemIndex; j--) // move parent's
    { // connections
        Node* temp = parent->disconnectChild(j); // one child
        parent->connectChild(j + 1, temp); // to the right
    }
    // connect newRight to parent
    parent->connectChild(itemIndex + 1, newRight);

    // deal with newRight
    newRight->insertItem(itemC); // item C to newRight
    newRight->connectChild(0, child2); // connect to 0 and 1
    newRight->connectChild(1, child3); // on newRight
} // end split()

// gets appropriate child of node during search for value
Node* TwoFour::getNextChild(Node* theNode, int theValue) {
    // Should be able to do this w/o a loop, since we should know
    // index of correct child already
    int j;
    // assumes node is not empty, not full, not a leaf
    int numItems = theNode->getNumItems();
    for (j = 0; j < numItems; j++) // for each item in node
    { // are we less?
        if (theValue < theNode->getItem(j)->getData())
            return theNode->getChild(j); // return left child
    } // end for // we're greater, so
    return theNode->getChild(j); // return right child
}

void TwoFour::displayTree(int i) {
    if (i == 0) {
        recDisplayTree(root, 0, 0);
    } else
        inorderdisplay(root, 0, 0);
    //System.out.println();
}

void TwoFour::recDisplayTree(Node* thisNode, int level, int childNumber) {
    cout<<"level=" << level << " child=" << childNumber + " ";
    thisNode->displayNode(); // display this node
        //System.out.println();
    // call ourselves for each child of this node
    int numItems = thisNode->getNumItems();
    for (int j = 0; j < numItems + 1; j++) {
        Node* nextNode = thisNode->getChild(j);
        if (nextNode != NULL)
            recDisplayTree(nextNode, level + 1, j);
        else
            return;
    }
} // end recDisplayTree()

void TwoFour::inorderdisplay(Node* thisNode, int level, int childNumber) {
    int numItems = thisNode->getNumItems();
    for (int j = 0; j < numItems + 1; j++) {
        Node* nextNode = thisNode->getChild(j);
        if (nextNode != NULL)
            inorderdisplay(nextNode, level + 1, j);
        else {
            thisNode->displayNode();
            return;
        }
        if (j < thisNode->getNumItems())
            thisNode->displayvalue(j);
    }
}

Node* TwoFour::find(int theValue) {
    return findvalue(root, theValue);
}

Node* TwoFour::findvalue(Node* theNode, int theValue) {

    // Should be able to do this w/o a loop, since we should know
    // index of correct child already
    Node* l = NULL;
    // assumes node is not empty, not full, not a leaf
    int numItems = theNode->getNumItems();
    for (int j = 0; j < numItems; j++) // for each item in node
    { // are we less?
        // System.out.println(theNode.getItem(j).dData);
        if (theValue == theNode->getItem(j)->getData()) {
            l = theNode;
            break;
        } else if (theValue < theNode->getItem(j)->getData() && !theNode->isLeaf()) {
            l = findvalue(theNode->getChild(j), theValue); // return left
            // child
            break;
        } else if (theValue > theNode->getItem(j)->getData() && !theNode->isLeaf()) {
            l = findvalue(theNode->getChild(j + 1), theValue); // return
            // right
            // child

        }
    } // end for // we're greater, so
    return l;
}

// public Node delete(int theValue){
// return deletevalue(find(theValue),theValue);
// }
//
Node* TwoFour::deleteNode(Node* currnode, int theValue) {
    Node* y = NULL;

    if (currnode->isLeaf()) {
        if (currnode->getNumItems() > 1) {
            currnode->deletenodevalue(theValue);
            return currnode;
        } else {
            y = deleteleaf_cases(currnode, theValue);
            return y;
        }
    } else {
        // delete interior nodes
        //boolean x = false;

        Node* n = getNextChild(currnode, theValue);
        Node* c = getinordernode(n);
        NodeData* d = c->getItem(0);
        int k = d->getData();
        deleteNode(c, d->getData());

        Node* found = find(theValue);
        for(int i = 0; i < found->getNumItems();i++){
            if(found->getItem(i)->getData()==theValue){
                found->getItem(i)->setData(k);
            }
        }
        return found;
    }
}
Node* TwoFour::deleteleaf_cases(Node* thisNode, int theValue) {
    string sibling_side = "l";
    Node *p = thisNode->getParent();
    Node *sibling = thisNode->getsibiling(theValue);
    if (sibling == NULL) {
        sibling_side = "r";
        sibling = p->getChild(1);
    }
    if (sibling->getNumItems() == 1) {
        for (int i = 0; i <= p->getNumItems(); i++) {
            if (p->getChild(i) == sibling && sibling_side == "l") {
                thisNode->setItem(thisNode->getNumItems() - 1, NULL);
                thisNode->setNumItems(thisNode->getNumItems() - 1);
                NodeData *d = p->getItem(i);
                sibling->insertItem(d);
                p->disconnectChild(i + 1);
                for (int j = i; j < p->getNumItems(); j++) {
                    if (j + 1 < p->getNumItems()) {
                        p->setItem(j, p->getItem(j + 1));
                        if (j + 2 <= p->getNumItems()) {
                            p->connectChild(j + 1, p->disconnectChild(j + 2));
                        }
                    }
                }
                p->setItem(p->getNumItems() - 1, NULL);
                p->setNumItems(p->getNumItems() - 1);
                // Check if parent is null
                if (p->getNumItems() == 0) {
                    if (p != root) {
                        p = balancetree(p);
                    } else {
                        root = sibling;
                    }
                }
                return p;
            } else if (p->getChild(i) == sibling && sibling_side == "r") {
                thisNode->setItem(thisNode->getNumItems() - 1, NULL);
                thisNode->setNumItems(thisNode->getNumItems() - 1);
                NodeData *d = p->getItem(i - 1);
                sibling->insertItem(d);
                p->disconnectChild(0);
                p->connectChild(0, p->disconnectChild(1));

                for (int j = i; j < p->getNumItems(); j++) {
                    p->setItem(j - 1, p->getItem(j));
                    if (j + 1 <= p->getNumItems()) {
                        p->connectChild(j, p->disconnectChild(j + 1));
                    }
                }
                p->setItem(p->getNumItems() - 1, NULL);
                p->setNumItems(p->getNumItems() - 1);

                // Check if parent is null
                if (p->getNumItems() == 0) {    //System.out.println("Parent became null; Now Tree is Re-Balancing");
                    if (p != root) {
                        p = balancetree(p);
                    } else {
                        root = sibling;
                    }
                }
                return p;
            }
        }
    } else if (sibling->getNumItems() > 1) {
        int f = 0;
        if (sibling_side == "r") {
            f = 0;
        } else {
            f = sibling->getNumItems() - 1;
        }
        for (int i = 0; i <= p->getNumItems(); i++) {
            if (p->getChild(i) == sibling && sibling_side == "l") {
                thisNode->getItem(0)->setData( p->getItem(i)->getData());
                p->getItem(i)->setData( sibling->getItem(f)->getData() );
                sibling->deletenodevalue( sibling->getItem(f)->getData() );
                return p;
            }

            if (p->getChild(i) == sibling && sibling_side == "r") {
                thisNode->getItem(0)->setData( p->getItem(i - 1)->getData());
                p->getItem(i - 1)->setData( sibling->getItem(f)->getData());
                sibling->deletenodevalue(sibling->getItem(f)->getData());
                return p;
            }
        }
    }
    return NULL;
}
Node* TwoFour::balancetree(Node* currnode) { // Argument is empty node.
    string sibling_side = "l";
    Node *p = currnode->getParent();
    Node *sibling = currnode->getsibiling(-1);
    if (sibling == NULL) {
        sibling_side = "r";
        sibling = p->getChild(1);
    }
    if (sibling->getNumItems() == 1) {
        for (int i = 0; i <= p->getNumItems(); i++) {
            if (p->getChild(i) == sibling && sibling_side == "l") {
                // merge parent and child and remove parent
                NodeData *d = p->getItem(i);
                sibling->insertItem(d);
                sibling->connectChild(sibling->getNumItems(),
                                      currnode->disconnectChild(0));
                p->disconnectChild(i + 1);
                for (int j = i; j < p->getNumItems(); j++) {
                    if (j + 1 < p->getNumItems()) {
                        p->setItem(j, p->getItem(j + 1));
                        if (j + 2 <= p->getNumItems()) {
                            p->connectChild(j + 1, p->disconnectChild(j + 2));
                        }
                    }
                }
                p->setItem(p->getNumItems() - 1, NULL);
                p->setNumItems(p->getNumItems() - 1);

                // Check if parent is null
                if (p->getNumItems() == 0) {
                    if (p != root) {
                        p = balancetree(p);
                    } else {
                        root = sibling;
                    }
                }
                return p;
            } else if (p->getChild(i) == sibling && sibling_side == "r") {
                NodeData *d = p->getItem(i - 1);
                sibling->insertatfront(d);
                sibling->connectChild(0, currnode->disconnectChild(0));
                p->disconnectChild(0);
                p->connectChild(0, p->disconnectChild(1));

                for (int j = i; j < p->getNumItems(); j++) {
                    p->setItem(j - 1, p->getItem(j));
                    if (j + 1 <= p->getNumItems()) {
                        p->connectChild(j, p->disconnectChild(j + 1));
                    }
                }
                p->setItem(p->getNumItems() - 1, NULL);
                p->setNumItems(p->getNumItems() - 1);

                // Check if parent is null
                if (p->getNumItems() == 0) {
                    if (p != root) {
                        p = balancetree(p);
                    } else {
                        root = sibling;
                    }
                }
                return p;
            }

        }

    } else if (sibling->getNumItems() > 1) {
        int f = 0;
        if (sibling_side == "r") {
            f = 0;
        } else {
            f = sibling->getNumItems() - 1;
        }
        for (int i = 0; i <= p->getNumItems(); i++) {
            if (p->getChild(i) == sibling && sibling_side == "l") {
                currnode->setNumItems(currnode->getNumItems() + 1);
                currnode->connectChild(1, currnode->disconnectChild(0));
                currnode->connectChild(0,
                                       sibling->disconnectChild(sibling->getNumItems()));
                currnode->setItem(0, p->getItem(i));
                p->setItem(i, sibling->getItem(f));
                sibling->setItem(sibling->getNumItems() - 1, NULL);
                sibling->setNumItems(sibling->getNumItems() - 1);
                return p;
            }

            if (p->getChild(i) == sibling && sibling_side == "r") {
                currnode->setNumItems(currnode->getNumItems() + 1);
                currnode->setItem(0, p->getItem(i - 1));
                p->setItem(i - 1, sibling->getItem(f));
                currnode->connectChild(1, sibling->disconnectChild(f));

                for (int j = 0; j < sibling->getNumItems(); j++) {
                    if (j + 1 < sibling->getNumItems()) {
                        sibling->setItem(j, sibling->getItem(j + 1));
                    }
                    sibling->connectChild(j, sibling->disconnectChild(j + 1));
                }
                sibling->setItem(sibling->getNumItems() - 1, NULL);
                sibling->setNumItems(sibling->getNumItems() - 1);
                return p;
            }
        }
    }
    return NULL;
}

Node* TwoFour::getinordernode(Node* thisNode) {
    Node *c = NULL;
    if (thisNode->isLeaf()) {
        c = thisNode;
    } else {
        c = getinordernode(thisNode->getChild(0));
    }
    return c;
}

#endif //PROYECTO_2_DATOS_TWOFOUR_H
