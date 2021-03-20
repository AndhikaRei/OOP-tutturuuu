/* Implementasi Method Breeding */

#include "Breeding.hpp"


Engimon& breeding(Engimon& parent_a, Engimon& parent_b) 
{
    
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

    std::default_random_engine generator;
    vector<Elements> similiarEle;
    if (isElementSimilar(parent_a, parent_b, &similiarEle)) {
        // Definisi similiar : ada element yang sama
        /* Jika elemen kedua parent sama, anak akan memiliki elemen yang sama dengan kedua parent. 
        Spesies anak dipilih dari parent A atau parent B secara bebas (boleh random atau aturan 
        spesifik tertentu). */
        std::uniform_int_distribution<int> distribution(0,1);
        int choice = distribution(generator);

        if (choice == 0) {
            /* Pake spesies parent a */
            *anak = *calonAnak_a.at(0);
            anak->setParent(ortu);
            addSkillAnak(*anak, calonSkill);
            return *anak;
        } else {
            /* Pake spesies parent b */
            *anak = *calonAnak_b.at(0);
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
                *anak = *calonAnak_a.at(0);
                anak->setParent(ortu);
                addSkillAnak(*anak, calonSkill);
                return *anak;
            } else {
                /* Pake spesies parent b */
                *anak = *calonAnak_b.at(0);
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

            std::uniform_int_distribution<int> distribution(0,calonAnak.size()-1);
            int choice = distribution(generator);
            
            // Spesies baru, tidak boleh sama dengan parentnya
            while (calonAnak.at(choice)->getSpecies() == parent_a.getSpecies() || calonAnak.at(choice)->getSpecies() == parent_b.getSpecies())
            {
                choice = distribution(generator);
            }

            *anak = *calonAnak.at(choice);
            anak->setParent(ortu);
            addSkillAnak(*anak, calonSkill);
            return *anak;
        
        }    
    }  
}

void addSkillAnak(Engimon& child, vector<Skill> calonSkill) {
    int i = 0;
    while (child.getSkill().size() <= 4 && i < calonSkill.size()) {
        if (calonSkill.at(i).isElementCompatible(child.getElements())) {
            child.addSkill(calonSkill.at(i));
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
    vector<float> elementAdvantageVector;
    vector<Elements>::iterator it1;
    vector<float>::iterator it2;
    float elAdv;
    bool found;
    

    for (int i = 0; i < eleParent_a.size(); i++)
    {
        
        elAdv = 0;
        for (int j = 0; j < eleParent_b.size(); j++)
        {
            if (elAdv < elementAdvantage(eleParent_a[i],eleParent_b[j])) {
                elAdv = elementAdvantage(eleParent_a[i],eleParent_b[j]);
            }
        }

        it1 = elementVector.begin();
        it2 = elementAdvantageVector.begin();
        found = false;
        while (it2 != elementAdvantageVector.end() && !found)
        {
            if ((*it2) <= elAdv) {
                found = true;
            } else {
                it1++;
                it2++;
            }
        }

        
        elementAdvantageVector.insert(it2,elAdv);
        elementVector.insert(it1,eleParent_a.at(i));     
    }



    for (int i = 0; i < eleParent_b.size(); i++)
    {
        elAdv = 0;
        for (int j = 0; j < eleParent_a.size(); j++)
        {
            if (elAdv < elementAdvantage(eleParent_b[i],eleParent_a[j])) {
                elAdv = elementAdvantage(eleParent_b[i],eleParent_a[j]);
            }
        }
        it1 = elementVector.begin();
        it2 = elementAdvantageVector.begin();
        found = false;
        while (it2 != elementAdvantageVector.end() && !found)
        {
            if ((*it2) <= elAdv) {
                found = true;
            } else {
                it1++;
                it2++; 
            }
        }

        elementAdvantageVector.insert(it2,elAdv);
        elementVector.insert(it1,eleParent_b.at(i)); 
        
    }

    // Remove Duplicate
    set<Elements> s(elementVector.begin(), elementVector.end());
    elementVector.assign(s.begin(), s.end());

    return elementVector; 
}