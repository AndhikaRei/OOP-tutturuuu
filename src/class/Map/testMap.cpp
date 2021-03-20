#include <iostream>
#include <string>
#include "Map.hpp"
using namespace std;

// compile
// g++ -o testMap testMap.cpp ../Engimon/Engimon.cpp Map.cpp ../Skill/Skill.cpp ../Elements/Elements.cpp ../Skill_Item/Skill_Item.cpp
int main() {
    Map map(20, 10, "map.txt");
    initEngidex();
    int i = 0;
    cout << "Test" << endl;
    while(i < 20){
        map.spawnRandomPokemon();
        map.printMap();
        i++;
    }
    // initEngidex();
    // try{
    //     m.addEngimon(9, 16, "Electro");
    //     m.addEngimon(4, 10, "Hydro");
    //     m.addEngimon(2, 2, "ElectroCharged");
    //     m.addEngimon(3, 3, "CryoCrystallize");
    // }catch(WriteException &e){
    //     cout <<e.what() << endl;
    // }
    // m.printMap();
    // string command;
    // cin >> command;
    // while(command != "exit"){
    //     try{
    //         if(command == "w"){
    //             m.move('w');
    //         }else if(command == "a"){
    //             m.move('a');
    //         }else if(command == "s"){
    //             m.move('s');
    //         }else if(command == "d"){
    //             m.move('d');
    //         }else{
    //             cout << "Command tidak tersedia" <<endl;
    //         }
    //     } catch(WriteException &e){
    //         cout <<e.what() << endl;
    //         m.printMap();
    //     }
    //     cin>>command;
    // }
    return 0;
}