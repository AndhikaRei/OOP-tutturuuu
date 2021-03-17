#include "Engimon.hpp"

int main(int argc, char const *argv[])
{
    Parent par("Papa","Laki-laki","Mama","Perempuan");
    Engimon *a1 = new Pyro("Andrew");
    Engimon *b1 = new Pyro("Andrew",par);
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
    return 0;
}
