//
// Created by leoch on 25/01/2021.
//

#ifndef PROYECTO_2_DATOS_MENU_H
#define PROYECTO_2_DATOS_MENU_H
#include "TwoFour.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
class Menu{
public:
    void menu();
    double Random();
};

double Menu::Random() {
        double f = (double)rand() / RAND_MAX;
        return 0,0 + f * (0,1 - 0,0);
}

void Menu::menu() {
    string choice;
    TwoFour *theTree = new TwoFour();
    int n;
    while (true) {
        try {
            cout << "1. Insert n random Integers\n"
                 << "2. Perform 2n operations with probability\n3. Print In Order"
                 << "\n4. View Tree level by level\n5. Insert an element\n6. Delete an element"
                 << "\n7. find an element\n8. Quit"
                 << "\t Option: ";
            cin >> choice;
            switch (atoi(choice.c_str())) {
                case 1: {
                    cout << "\nEnter the value of n";
                    cin >> n;
                    for (int a = 1; a < n + 1; a++) {
                        Node *present = theTree->find(a);
                        if (present != NULL) {
                            cout << "Data Already present!!\n";
                        } else {
                            theTree->insert(a);
                        }
                    }
                    break;
                }
                case 2: {
                    cout << "\nEnter the value of n";
                    cin >> n;
                    long startTime, endTime;
                    int operation = 0;
                    int searchCount = 0;
                    int insertCount = 0;
                    int deleteCount = 0;
                    //startTime = System.nanoTime();
                    while (operation < (2 * n)) {
                        double randDouble = Random();
                        if (randDouble < 0.4) {
                            // Making sure insert operation runs at 0.4
                            // probability
                            int x = rand() % n;
                            Node *present = theTree->find(x);
                            if (present != NULL) {
                                cout << "Data Already present!!\n";
                            } else {
                                theTree->insert(x);
                            }
                            operation++;
                            insertCount++;

                        }
                        randDouble = Random();
                        if (randDouble < 0.25) { // Making sure delete operation runs at 0.25 //
                            // probability
                            int x = rand() % n;
                            Node *del = theTree->find(x);
                            if (del != NULL) {
                                if (theTree->deleteNode(del, x) != NULL) {
                                    cout << "Deleted" << x << endl;
                                } else {
                                    cout << "Not Deleted!!!" << endl;
                                }
                            } else
                                cout << "Could not find. " << x << endl;
                            operation++;
                            deleteCount++;

                        }
                        randDouble = Random();
                        if (randDouble < 0.35) { // Making sure search operation runs at 0.35 //
                            // probability
                            theTree->find(rand() % n);
                            operation++;
                            searchCount++;

                        }
                    }
                    //endTime = System.nanoTime() - startTime;

                    cout << "Total No. of search operations performed :"
                         << searchCount << endl;
                    cout << "Total No. of delete operations performed :"
                         << deleteCount << endl;
                    cout << "Total No. of insert operations performed :"
                         << insertCount << endl;
                    //cout<<"Total Time Taken:" << endTime << " nanoseconds";
                    break;
                }
                case 3: {
                    cout << "In Order: ";
                    theTree->displayTree(1);
                    break;
                }
                case 4: {
                    cout << "Tree:";
                    theTree->displayTree(0);
                    break;
                }
                case 5: {
                    int value;
                    cout << "Enter value to insert: ";
                    cin >> value;
                    Node *present = theTree->find(value);
                    if (present != NULL) {
                        cout << "Data Already present!!";
                    } else {
                        theTree->insert(value);
                    }
                    break;
                }
                case 6: {
                    int value;
                    cout << "Enter value to delete: ";
                    cin >> value;
                    Node *del = theTree->find(value);
                    if (del != NULL) {
                        if (theTree->deleteNode(del, value) != NULL)
                            cout << "Deleted " << value << endl;
                        else {
                            cout << "Not Deleted!!!" << endl;
                        }
                    } else
                        cout << "Could not find " << value << endl;
                    break;
                }
                case 7: {
                    int value;
                    cout << "Enter value to find: ";
                    cin >> value;
                    Node *found = theTree->find(value);
                    if (found != NULL)
                        cout << "Found " + value;
                    else
                        cout << "Could not find " + value;
                    break;
                }
                case 8: {
                    cout << "Thank you!!!";
                    exit(0);
                }
                default: {
                    cout << "Invalid entry\n";
                    break;
                }
            }
        } catch (exception e) {
            cout << "Please enter valid input" << endl;
        }
    }
}

#endif //PROYECTO_2_DATOS_MENU_H
