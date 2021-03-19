#include "Battle.hpp"
using std::cout;
using std::endl;
int main (){
    databaseSkillInitialization();
    cout << "Pyro vs Hydro"<< endl;
    Engimon* a1 = new Pyro("Api");
    Engimon *a2 = new Hydro("Air");
    if (playerEngimonWin(*a2, *a1)){
        cout << "Air lah bro yang menang"<< endl;
        Skill_Item dapetItem = getRandomSkillItem(databaseSkill,*a1);
        dapetItem.showItem();
    } else {
        cout << "Lah kok api wkwkkw"<< endl;
    }
    cout << "Melt vs ElectroCharged"<< endl;
    Engimon *a9 = new Melt("Melt");
    Engimon *a10 = new ElectroCharged("ElectroCharged");
    if (playerEngimonWin(*a9, *a10)){
        cout << "Melt lah bro yang menang"<< endl;
        Skill_Item dapetItem2 = getRandomSkillItem(databaseSkill,*a10);
        dapetItem2.showItem();
    } else {
        cout << "ElectroCharged lah bro yang menang"<< endl;
        Skill_Item dapetItem2 = getRandomSkillItem(databaseSkill,*a9);
        dapetItem2.showItem();
    }
    cout << "Superconductor vs CryoCrystallize"<< endl;
    Engimon *a14 = new Superconductor("Superconductor");
    Engimon *a15 = new CryoCrystallize("CryoCrystallize");
    if (playerEngimonWin(*a14, *a15)){
        cout << "Superconductor lah bro yang menang"<< endl;
        Skill_Item dapetItem3 = getRandomSkillItem(databaseSkill,*a15);
        dapetItem3.showItem();
    } else {
        cout << "CryoCrystallize lah bro yang menang"<< endl;
        Skill_Item dapetItem3 = getRandomSkillItem(databaseSkill,*a14);
        dapetItem3.showItem();
    }

}