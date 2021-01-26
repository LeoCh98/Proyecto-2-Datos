//
// Created by leoch on 25/01/2021.
//

#ifndef PROYECTO_2_DATOS_MENU_H
#define PROYECTO_2_DATOS_MENU_H
#include "TwoFour.h"
class Menu{
public:
    void menu();
};

void Menu::menu() {
    TwoFour* theTree = new TwoFour();
    int n;
    Random random = new Random();
    while (true) {
        try {
            cout<<"1. Insert n random Integers\n"
                << "2. Perform 2n operations with probability\n3. Print In Order"
                << "\n4. View Tree level by level\n5. Insert an element\n6. Delete an element"
                << "\n7. find an element\n8. Quit";
            char choice = getChar();
            switch (choice) {
                case '1':
                    cout<<"Enter the value of n";
                    n = getInt();
                    for (int a = 1; a < n+1; a++) {
                        Node present = theTree.find(a);
                        if (present != null){
                            //System.out.println("Data Already present!!");
                        }else{
                            theTree.insert(a);
                        }
                    }
                    break;
                case '2':
                    cout<<"Enter the value of n";
                    n = getInt();
                    long startTime, endTime;
                    int operation = 0;
                    int searchCount = 0;
                    int insertCount = 0;
                    int deleteCount = 0;
                    startTime = System.nanoTime();
                    while (operation < (2 * n)) {
                        double rand = random.nextDouble();
                        if (rand < 0.4) {
                            // Making sure insert operation runs at 0.4
                            // probability
                            int x = random.nextInt(n);
                            Node present = theTree.find(x);
                            if (present != null) {
                                //System.out.println("Data Already present!!");
                            } else {
                                theTree.insert(x);
                            }
                            operation++;
                            insertCount++;

                        }
                        rand = random.nextDouble();
                        if (rand < 0.25) { // Making sure delete operation runs at 0.25 //
                            // probability
                            int x = random.nextInt(n);
                            Node del = theTree.find(x);
                            if (del != null) {
                                if (theTree.delete(del, x) != null)
                                {//System.out.println("Deleted" + x);
                                }else {
                                    //System.err.println("Not Deleted!!!");
                                }
                            } else
                                //System.out.println("Could not find " + x);
                                operation++;
                            deleteCount++;

                        }
                        rand = random.nextDouble();
                        if (rand < 0.35) { // Making sure search operation runs at 0.35 //
                            // probability
                            theTree.find(random.nextInt(n));
                            operation++;
                            searchCount++;

                        }
                    }
                    endTime = System.nanoTime() - startTime;

                    cout<<"Total No. of search operations performed :"
                        << searchCount;
                    cout<<"Total No. of delete operations performed :"
                        << deleteCount;
                    cout<<"Total No. of insert operations performed :"
                        << insertCount;
                    cout<<"Total Time Taken:" << endTime << " nanoseconds";
                    break;
                case '3':
                    cout<<"In Order: ";
                    theTree.displayTree(1);
                    break;
                case '4':
                    cout<<"Tree:";
                    theTree.displayTree(0);
                    break;
                case '5':
                    cout<<"Enter value to insert: ";
                    int value = getInt();
                    Node present = theTree.find(value);
                    if (present != null){
                        cout<<"Data Already present!!";
                    }else{
                        theTree.insert(value);
                    }
                    break;
                case '6':
                    cout<<"Enter value to delete: ";
                    value = getInt();
                    Node del = theTree.find(value);
                    if (del != null)
                    {
                        if(theTree.delete(del,value)!=null)
                        cout<<"Deleted" <<value;
                        else{
                            cout<<"Not Deleted!!!";
                        }
                    }
                    else
                        cout<<"Could not find " << value;
                    break;
                case '7':
                    cout<<"Enter value to find: ";
                    value = getInt();
                    Node found = theTree.find(value);
                    if (found != null)
                        cout<<"Found " + value;
                    else
                        cout<<"Could not find " + value;
                    break;
                case '8':
                    cout<<"Thank you!!!";
                    exit(0);

                default:
                    cout<<"Invalid entry\n";
            }
        } catch (Exception e) {
            System.err.println("Please enter valid input");
        }
    }

}

string getString() throws IOException {
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        String s = br.readLine();
        return s;
}

char getChar() throws IOException {
        String s = getString();
        return s.charAt(0);
}

int getInt() throws IOException {
        String s = getString();
        return Integer.parseInt(s);
}

}
}
#endif //PROYECTO_2_DATOS_MENU_H
