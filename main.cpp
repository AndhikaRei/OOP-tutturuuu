#include <iostream>
#include "Map.h"
using namespace std;


int main() {
    Map m(20, 10, "map.txt");
    m.printMap();
    string command;
    cin >> command;
    while(command != "exit"){
        if(command == "w"){
            m.move('w');
        }else if(command == "a"){
            m.move('a');
        }else if(command == "s"){
            m.move('s');
        }else if(command == "d"){
            m.move('d');
        }else{
            cout << "Command tidak tersedia" <<endl;
        }
        cin>>command;
    }
    return 0;
}