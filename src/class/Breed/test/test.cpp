#include "../../Elements/Elements.hpp"
#include "../../Engimon/Engimon.hpp"
#include "../Breeding.hpp"
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;


int main()
{
    initEngidex();
    cout << "t1" << endl;

    vector<Engimon *> parent_a;
    vector<Engimon *> parent_b;
    parent_a = EngimonFinder("Hydro");
    parent_b = EngimonFinder("Electro");
    
    cout << "t2" << endl;

    Engimon* a = parent_a.at(0)->clone();
    a->showEngimon();
    cout << "t9" << endl;
    Engimon* b = parent_b.at(0)->clone();
    b->showEngimon();
    cout << "t10" << endl;

    a->addExp(3100);
    b->addExp(3100);

    cout << "t3" << endl;

    Engimon* child;
    {
        child = &breeding(*a, *b);
    }
    cout << "t4" << endl;

    string name;
    cout << "Berikan nama untuk engimon yang baru dilahirkan" << endl;
    cout <<"Masukkan nama: "; std::cin >> name;
    child->rename(name);
    
    child->showEngimon();
    vector<Skill> skillAnak = child->getSkill();
    vector<Skill>::iterator it;
    for (it = skillAnak.begin(); it < skillAnak.end(); it++) 
    cout << *it << " ";


    //         // anak->setParent(ortu);
    

    // // el1.getSkill().at(0).showSkill();
    // // // el2.getSkill().at(0).levelUp();
    // // el2.getSkill().at(0).showSkill();

    // cout << endl;

    // sortedSkill = sortingSkill(*calonAnak_a.at(0),*calonAnak_b.at(0));

    // for (it = sortedSkill.begin(); it < sortedSkill.end(); it++) 
    // it->showSkill();

    // cout << "t3" << endl;
    // el1.showEngimon();
    // el2.showEngimon();
    // vector<Elements> elSorted = sortElementAdvantage(el1,el2);
    
    // for (it = elSorted.begin(); it < elSorted.end(); it++) 
    // cout << elementName(*it) << " ";

    // vector<Elements> similiarEl;
    // cout << isElementSimilar(el1,el2,&similiarEl) << endl;;
    // for (it = similiarEl.begin(); it < similiarEl.end(); it++) 
    // cout << elementName(*it) << " ";

    return 0;
}
