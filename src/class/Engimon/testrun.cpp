#include "Engimon.hpp"
using std::cout;
using std::endl;
int main(int argc, char const *argv[])
{
    Engimon *a1 = new Pyro("Andrew");
    Engimon *a2 = new Hydro("Andrew");
    Engimon *a3 = new Electro("Andrew");
    Engimon *a4 = new Geo("Andrew");
    Engimon *a5 = new Cryo("Andrew");
    Engimon *a6 = new Vaporize("Andrew");
    Engimon *a7 = new Overload("Andrew");
    Engimon *a8 = new PyroCrystallize("Andrew");
    Engimon *a9 = new Melt("Andrew");
    Engimon *a10 = new ElectroCharged("Andrew");
    Engimon *a11 = new HydroCrystallize("Andrew");
    Engimon *a12 = new Frozen("Andrew");
    Engimon *a13 = new ElectroCrystallize("Andrew");
    Engimon *a14 = new Superconductor("Andrew");
    Engimon *a15 = new CryoCrystallize("Andrew");
    a1->interact();
    a2->interact();
    a3->interact();
    a4->interact();
    a5->interact();
    a6->interact();
    a7->interact();
    a8->interact();
    a9->interact();
    a10->interact();
    a11->interact();
    a12->interact();
    a13->interact();
    a14->interact();
    a15->interact();
    // a1->addExp(7);
    // a1->showEngimon();
    // a1->addExp(99);
    // a1->showEngimon();
    // a1->addExp(225);
    // a1->showEngimon();
    return 0;
}
