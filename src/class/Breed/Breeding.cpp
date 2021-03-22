/* Implementasi Method Breeding */

#include "Breeding.hpp"
#include <cstdlib>
#include <ctime>

Engimon& breeding(Engimon& parent_a, Engimon& parent_b) 
{
    // Random generator
    srand((unsigned) time(0));
    
    if (parent_a.level < 30 || parent_b.level < 30) {
        throw InvalidBreedingInsufficientLevel();
    }
    
    vector<Engimon *> calonAnak_a = EngimonFinder(parent_a.getSpecies());
    vector<Engimon *> calonAnak_b = EngimonFinder(parent_b.getSpecies());


    if (calonAnak_a.size() < 1 || calonAnak_b.size() < 1) {
        throw UnexpectedErrorWhileBreeding();
    }

    parent_a.level -= 30;
    parent_b.level -= 30;

    // Bikin object parent dulu
    Parent ortu = Parent(parent_a.getName(), parent_a.getSpecies(), parent_b.getName(), parent_b.getSpecies());
    Engimon* anak; 

    // Cari skill yang mungkin bisa diambil
    vector<Skill> calonSkill = sortingSkill(parent_a,parent_b);

    // std::default_random_engine generator;
    vector<Elements> similiarEle;
    if (isElementSimilar(parent_a, parent_b, &similiarEle)) {
        // Definisi similiar : ada element yang sama
        /* Jika elemen kedua parent sama, anak akan memiliki elemen yang sama dengan kedua parent. 
        Spesies anak dipilih dari parent A atau parent B secara bebas (boleh random atau aturan 
        spesifik tertentu). */
        // std::uniform_int_distribution<int> distribution(0,100);
        // int choice = distribution(generator);
        int choice = rand() % similiarEle.size();
        vector<Engimon *> calonAnak = EngimonFinder(similiarEle.at(choice));
        choice = rand() % 3;

        if (choice == 0) {
            /* Pake spesies parent a */
            anak = calonAnak_a.at(0)->clone();
            anak->setParent(ortu);
            addSkillAnak(*anak, calonSkill);
            return *anak;
        } else if (choice == 1) {
            /* Pake spesies parent b */
            anak = calonAnak_b.at(0)->clone();
            anak->setParent(ortu);
            addSkillAnak(*anak, calonSkill);
            return *anak;
        } else {
            anak = calonAnak.at(0)->clone();
            anak->setParent(ortu);
            addSkillAnak(*anak, calonSkill);
            return *anak;
        }

    } else {
        /* Jika elemen kedua parent berbeda maka anak akan memiliki elemen dan spesies dari elemen 
        yang memiliki element advantage yang lebih tinggi. */
        float eleAdv_a = totalElementAdvantage(parent_a.getElements(), parent_b.getElements());
        float eleAdv_b = totalElementAdvantage(parent_b.getElements(), parent_a.getElements());
        if (eleAdv_a != eleAdv_b) {
            if (eleAdv_a > eleAdv_b) {
                /* Pake spesies parent a */
                anak = calonAnak_a.at(0)->clone();
                anak->setParent(ortu);
                addSkillAnak(*anak, calonSkill);
                return *anak;
            } else {
                /* Pake spesies parent b */
                anak = calonAnak_b.at(0)->clone();
                anak->setParent(ortu);
                addSkillAnak(*anak, calonSkill);
                return *anak;
            }
        } else {
            /* eleAdv_a == eleAdv_b */
            /* Jika elemen kedua parent berbeda dan kedua elemen memiliki element advantage yang sama, 
            maka anak akan memiliki spesies berbeda dari kedua parent yang memiliki kedua elemen parent 
            (boleh dipilih random atau hardcoded). */
            vector<Elements> listElement = sortElementAdvantage(parent_a,parent_b);
             // udah pasti dual element, ambil 2 terbesar dari sortElementAdvantage
            
            vector<Engimon *> calonAnak = EngimonFinder(listElement.at(0),listElement.at(1));
            
            // std::uniform_int_distribution<int> distribution(0,calonAnak.size()-1);
            int choice = rand() % calonAnak.size();
            
            // Spesies baru, tidak boleh sama dengan parentnya (kalau ada spesies lain)
            while ((calonAnak.at(choice)->getSpecies() == parent_a.getSpecies() || calonAnak.at(choice)->getSpecies() == parent_b.getSpecies()) && (calonAnak.size() > 1))
            {
                choice = rand() % calonAnak.size();
            }

            anak = calonAnak.at(choice)->clone();
            anak->setParent(ortu);
            addSkillAnak(*anak, calonSkill);
            return *anak;
        
        }    
    }  
}

void addSkillAnak(Engimon& child, vector<Skill> calonSkill) {
    int i = 0;
    vector<Skill> childSkill = child.getSkill();
    vector<Skill>::iterator it;
    while (child.getSkill().size() <= 4 && i < calonSkill.size()) {
        it = std::find(childSkill.begin(), childSkill.end(), calonSkill.at(i));
        if (it == childSkill.end())
        {
            if (calonSkill.at(i).isElementCompatible(child.getElements())) {
                try
                {
                    child.addSkill(calonSkill.at(i));
                }
                catch(WriteException& e)
                {
                    // Unexpected Behavior
                }  
            }
        } else {
            if (it->getMasteryLevel() < calonSkill.at(i).getMasteryLevel()) {
                child.skillLevelUp(*it, calonSkill.at(i).getMasteryLevel() - it->getMasteryLevel());
            }
        }
        i++;
    }
}

bool masteryLevelGreater(Skill a,Skill b) { 
    return (a.getMasteryLevel() > b.getMasteryLevel()); 
}

/* Inherit Skill Child */
vector<Skill> sortingSkill(Engimon& parent_a, Engimon& parent_b) {
    vector<Skill> skillParent_a = parent_a.getSkill();
    vector<Skill> skillParent_b = parent_b.getSkill();

    vector<Skill> sortedSkill;
    vector<Skill>::iterator it;

    int i;
    for (i = 0; i < skillParent_a.size(); i++)
    {
        sortedSkill.push_back(skillParent_a.at(i));
    }

    for (i = 0; i < skillParent_b.size(); i++)
    {
        // Find duplicate
        it = std::find(sortedSkill.begin(), sortedSkill.end(), skillParent_b.at(i));
        if (it == sortedSkill.end()) {    // Tidak ditemukan duplikat
            sortedSkill.push_back(skillParent_b.at(i));
        } else {    // Ditemukan duplikat
            if (it->getMasteryLevel() == skillParent_b.at(i).getMasteryLevel()) {
                // Mastery level sama
                it->levelUp();
            } else if (it->getMasteryLevel() < skillParent_b.at(i).getMasteryLevel()) {
                // Mastery level beda
                *it = skillParent_b.at(i);
            }
            
            
        }
    }

    std::sort(sortedSkill.begin(),sortedSkill.end(), masteryLevelGreater);

    return sortedSkill;
}

/* Element Child */
bool isElementSimilar(Engimon& parent_a, Engimon& parent_b, vector<Elements>* similiarEle) {
    /* Mengecek apakah element suatu parent memiliki kesamaan */
    vector<Elements> eleParent_a = parent_a.getElements();
    vector<Elements> eleParent_b = parent_b.getElements();

    bool isSimiliar = false;
    int i, j;
    for (i = 0; i < eleParent_a.size(); i++) {
        for (j = 0; j < eleParent_b.size(); j++) {
            if (eleParent_a.at(i) == eleParent_b.at(j)) {
                isSimiliar = true;
                similiarEle->push_back(eleParent_a.at(i));
            } 
        } 
    }

    return isSimiliar;
    
    
}

vector<Elements> sortElementAdvantage(Engimon& parent_a, Engimon& parent_b) {
    /* Mengembalikan vector of element yang berisi urutan element Advantage dari kedua buah parent */
    vector<Elements> eleParent_a = parent_a.getElements();
    vector<Elements> eleParent_b = parent_b.getElements();
    vector<Elements> elementVector;

    vector<Elements>::iterator it1;
    vector<Elements>::iterator it2;

    multimap<float, Elements, std::greater <float>> el; 
    multimap<float, Elements, std::greater <float>>::iterator it;

    float elAdv;

    for (it1 = eleParent_a.begin(); it1 < eleParent_a.end(); it1++) {
        elAdv = 0;
        
        for (it2 = eleParent_b.begin(); it2 < eleParent_b.end(); it2++) {
            if (elAdv < elementAdvantage(*it1,*it2)) {
                elAdv = elementAdvantage(*it1,*it2);
            }
        }

        el.insert(pair<float,Elements>(elAdv,*it1)); 
    }

    for (it2 = eleParent_b.begin(); it2 < eleParent_b.end(); it2++) {
        elAdv = 0;
        for (it1 = eleParent_a.begin(); it1 < eleParent_a.end(); it1++) {
            if (elAdv < elementAdvantage(*it2,*it1)) {
                elAdv = elementAdvantage(*it2,*it1);
            }
        }
        el.insert(pair<float,Elements>(elAdv,*it2));
    }

    for (it = el.begin(); it != el.end(); it++) {
        if (std::find(elementVector.begin(),elementVector.end(),it->second) == elementVector.end()) {
            elementVector.push_back(it->second);
        }
        
    }

    // vector<Elements>::iterator it3;
    // for (it3 =  elementVector.begin(); it3 <  elementVector.end(); it3++) 
    // cout << elementName(*it3) << " ";


    return elementVector; 
}