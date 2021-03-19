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

    // Menghitung sekaligus membandingkan total power menggunakan rumus yang telah disediakan
    return ((player.getLevel()*playerElAdvantage +playerSkillDamage) >= (enemy.getLevel()*enemyElAdvantage +enemySkillDamage));
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
    std::random_device rands; 
    std::mt19937 gen(rands()); 
    std::uniform_int_distribution<> distr(0, filteredSkill.size()); 
    return (Skill_Item(filteredSkill.at(distr(gen)),1));
}