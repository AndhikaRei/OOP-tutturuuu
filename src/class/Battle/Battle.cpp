/* Implementasi Method Battle */

#include "Battle.hpp"

// Menghitung damage total  dari skill suatu engimon
int sumOfSkillPower(Engimon& player){
    int playerSkillDamage = 0;
    // Dapatkan vector yang berisikan skill engimon
    vector<Skill> skillPlayer = player.getSkill();

    // Loop untuk hitung total damage nya
    for (int i = 0; i < skillPlayer.size(); i++){
        playerSkillDamage+= skillPlayer.at(i).totalDamage();
    }
    return playerSkillDamage;
}

// Mencari tahun apakah engimon "player" bisa menang melawan engimon "enemy"
bool playerEngimonWin(Engimon& player, Engimon& enemy){
    

    // Menghitung elemenAdvantage setiap engimon
    float playerElAdvantage = totalElementAdvantage(player.getElements(), enemy.getElements());
    float enemyElAdvantage = totalElementAdvantage(enemy.getElements(), player.getElements());

    // Menghitung damage total dari skill setiap engimon
    int playerSkillDamage= sumOfSkillPower(player);
    int enemySkillDamage= sumOfSkillPower(enemy);

    float playerPower = player.getLevel()*playerElAdvantage +playerSkillDamage;
    float enemyPower = enemy.getLevel()*enemyElAdvantage +enemySkillDamage;

    std::cout << "(player)"<< player.getSpecies()  << " VS " << enemy.getSpecies() << "(enemy)" << std::endl;
    // GUI ENGIMON BATTLE
    std::cout << '\n' << "Engimon is Battling" << std::endl;
    std::cout << "Player Engimon Battle Stat"<< std::endl <<"LV "<<player.getLevel()<<" Element Advantage: "<< playerElAdvantage<< " Skill Damage: " << playerSkillDamage << " Total Power: " << playerPower<<std::endl;
    std::cout << "Enemy Engimon Battle Stat"<< std::endl <<"LV "<<enemy.getLevel()<<" Element Advantage: "<< enemyElAdvantage<< " Skill Damage: " << enemySkillDamage << " Total Power: " << enemyPower<<std::endl;

    // Menghitung sekaligus membandingkan total power menggunakan rumus yang telah disediakan
    return (playerPower >= enemyPower);
}

// Mendapatkan random Skill Item yang kompatibel dengan elemen engimon musuh.
Skill_Item getRandomSkillItem(vector<Skill> listOfSkill, Engimon& enemy){
    // Filter kumpulan vector of skill menjadi vector of skill yang kompatibel
    vector<Skill> filteredSkill = vector<Skill>(); 
    for (Skill skill : listOfSkill){
        if(skill.isElementCompatible(enemy.getElements())){
            filteredSkill.push_back(skill);
        }
    }

    // Dapatkan skill kompatibel secara random
    srand (time(NULL));
    int number =rand() % filteredSkill.size() ;
    return (Skill_Item(filteredSkill.at(number)));
}