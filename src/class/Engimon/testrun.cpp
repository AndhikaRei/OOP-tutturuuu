#include "Engimon.hpp"
using std::cout;
using std::endl;
using std::string;

// void printTesting(int x)
// {
//     string testName[] = {
//         "showEngimon without parent test",
//         "showEngimon with parent test",
//         "interact test",
//         "addExp test",
//         "showSkill test",
//         "cctor (clone) test",
//         "addSkill test"};
//     if (x != 1)
//     {
//         cout << "\n\n\n"
//              << endl;
//     }
//     cout << "=-=-=-=-=-=-=-= Test Run " << x << " : " << testName[x - 1] << " =-=-=-=-=-=-=-=" << endl;
// }
int main(int argc, char const *argv[])
{
    // Parent ortu("Papa", "Laki-laki", "Mama", "Perempuan");
    // Engimon *a1 = new Pyro("Andrew");
    // Engimon *a2 = new Hydro("Andrew");
    // Engimon *a3 = new Electro("Andrew");
    // Engimon *a4 = new Geo("Andrew");
    // Engimon *a5 = new Cryo("Andrew");
    // Engimon *a6 = new Vaporize("Andrew");
    // Engimon *a7 = new Overload("Andrew");
    // Engimon *a8 = new PyroCrystallize("Andrew");
    // Engimon *a9 = new Melt("Andrew");
    // Engimon *a10 = new ElectroCharged("Andrew");
    // Engimon *a11 = new HydroCrystallize("Andrew");
    // Engimon *a12 = new Frozen("Andrew");
    // Engimon *a13 = new ElectroCrystallize("Andrew");
    // Engimon *a14 = new Superconductor("Andrew");
    // Engimon *a15 = new CryoCrystallize("Andrew");
    // Engimon *b1 = new Pyro("Andrew", ortu);
    // Engimon *b2 = new Hydro("Andrew", ortu);
    // Engimon *b3 = new Electro("Andrew", ortu);
    // Engimon *b4 = new Geo("Andrew", ortu);
    // Engimon *b5 = new Cryo("Andrew", ortu);
    // Engimon *b6 = new Vaporize("Andrew", ortu);
    // Engimon *b7 = new Overload("Andrew", ortu);
    // Engimon *b8 = new PyroCrystallize("Andrew", ortu);
    // Engimon *b9 = new Melt("Andrew", ortu);
    // Engimon *b10 = new ElectroCharged("Andrew", ortu);
    // Engimon *b11 = new HydroCrystallize("Andrew", ortu);
    // Engimon *b12 = new Frozen("Andrew", ortu);
    // Engimon *b13 = new ElectroCrystallize("Andrew", ortu);
    // Engimon *b14 = new Superconductor("Andrew", ortu);
    // Engimon *b15 = new CryoCrystallize("Andrew", ortu);
    // printTesting(1);
    // a1->showEngimon();
    // a2->showEngimon();
    // a3->showEngimon();
    // a4->showEngimon();
    // a5->showEngimon();
    // a6->showEngimon();
    // a7->showEngimon();
    // a8->showEngimon();
    // a9->showEngimon();
    // a10->showEngimon();
    // a11->showEngimon();
    // a12->showEngimon();
    // a13->showEngimon();
    // a14->showEngimon();
    // a15->showEngimon();

    // printTesting(2);
    // b1->showEngimon();
    // b2->showEngimon();
    // b3->showEngimon();
    // b4->showEngimon();
    // b5->showEngimon();
    // b6->showEngimon();
    // b7->showEngimon();
    // b8->showEngimon();
    // b9->showEngimon();
    // b10->showEngimon();
    // b11->showEngimon();
    // b12->showEngimon();
    // b13->showEngimon();
    // b14->showEngimon();
    // b15->showEngimon();

    // printTesting(3);
    // a1->interact();
    // a2->interact();
    // a3->interact();
    // a4->interact();
    // a5->interact();
    // a6->interact();
    // a7->interact();
    // a8->interact();
    // a9->interact();
    // a10->interact();
    // a11->interact();
    // a12->interact();
    // a13->interact();
    // a14->interact();
    // a15->interact();
    // b1->interact();
    // b2->interact();
    // b3->interact();
    // b4->interact();
    // b5->interact();
    // b6->interact();
    // b7->interact();
    // b8->interact();
    // b9->interact();
    // b10->interact();
    // b11->interact();
    // b12->interact();
    // b13->interact();
    // b14->interact();
    // b15->interact();

    // printTesting(4);
    // a1->addExp(5);
    // a1->showEngimon();
    // a1->addExp(95);
    // a1->showEngimon();
    // a1->addExp(13519);
    // a1->showEngimon();

    // printTesting(5);
    // a1->getSkill()[0].showSkill();

    // printTesting(6);
    // Engimon *test = a1->clone();
    // test->showEngimon();
    // test->interact();
    // test->getSkill()[0].showSkill();
    // delete test;
    // Engimon *test2 = b10->clone();
    // test2->showEngimon();
    // test2->interact();
    // test2->getSkill()[0].showSkill();
    // delete test2;

    // printTesting(7);
    // Skill_Item skit(Skill("Explosion!", "Megumin approved.", 20, Fire));
    // Skill_Item skit2(Skill("Explosion2!", "Megumin approved.", 20, Fire), 3);
    // a1->addSkill(skit);
    // a1->addSkill(skit2);
    // a1->getSkill()[0].showSkill();
    // a1->getSkill()[1].showSkill();
    // a1->addSkill(skit2, 2);
    // a1->getSkill()[1].showSkill();
    // Parent ortu("Papa", "Laki-laki", "Mama", "Perempuan");
    // Parent ortu2("P","LK","M","PR");
    // Parent a(ortu);
    // a.showParent();

    // Engimon *a1 = new Pyro("a");
    // Engimon *a2 = new Pyro("a",ortu);
    // a1->showEngimon();
    // a2->showEngimon();

    Engimon *a1;
    if (1)
    {
        Parent ortu("Papa", "Laki-laki", "Mama", "Perempuan");
        a1 = new Melt("a", ortu);
    }
    a1->showEngimon();
    if (1)
    {
        Parent ortu2("P", "LK", "M", "PR");
        a1->setParent(ortu2);
    }
    a1->showEngimon();
    return 0;
}
