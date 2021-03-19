#include "Battle.hpp"
using std::cout;
using std::endl;
int main (){
    databaseSkillInitialization();
    Engimon* a1 = new Pyro("Api");
    Engimon *a2 = new Hydro("Air");
    if (playerEngimonWin(*a2, *a1)){
        cout << "Air lah bro yang menang"<< endl;
        Skill_Item dapetItem = getRandomSkillItem(databaseSkill,*a1);
        dapetItem.showItem();
    } else {
        cout << "Lah kok api wkwkkw"<< endl;
    }
    

}