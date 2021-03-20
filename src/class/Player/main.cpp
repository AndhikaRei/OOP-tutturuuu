//main.cpp

#include "player.hpp"
//#include "player.cpp"
#include "../Engimon/Engimon.hpp"
//#include "../Engimon/Engimon.cpp"
#include "../Skill_Item/Skill_Item.hpp"
//#include "../Skill_Item/Skill_Item.cpp"
#include "../Skill/Skill.hpp"
//#include "../skill/Skill.cpp"
using namespace std;

int main(){
    player* X;
    string Name;
    cout << "Type your Name: ";
    cin >> Name;
    int temp = Name == "asd"; 
    cout << temp <<endl<<endl<<endl ;
    X = new player(Name);

    Hydro* childe;
    Pyro* WhoTao;
    childe = new Hydro("childe");
    WhoTao = new Pyro("WhoTao");
    //childe->showEngimon();
    X->addEngimon(childe);
    X->changeActiveEngimon(0);
    cout << "ACTIVE ENGIMON :" << endl;
    X->getActiveEngimon()->showEngimon();
    X ->addEngimon(WhoTao);
    cout << "ACTIVE ENGIMON :" << endl;
    X->getActiveEngimon()->showEngimon();
    Skill* Obliteration;
    Obliteration = new Skill("Havoc : Obliteration" , "Elemental Burst", 9001, Water);
    Skill_Item* ObliterationBook;
    ObliterationBook = new Skill_Item(*Obliteration);
    X->addItem(ObliterationBook);
    X->addItem(ObliterationBook);
    Skill* SpiritSoother;
    SpiritSoother = new Skill("SpiritSootherBook", "Elemental Burst", 9003, Fire);
    Skill_Item* SpiritSootherBook;
    SpiritSootherBook = new Skill_Item(*SpiritSoother);
    X->addItem(SpiritSootherBook);
    
    X->printProfile();
    


    return 0;
}
