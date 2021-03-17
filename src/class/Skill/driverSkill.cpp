#include "Skill.hpp"

int main()
{
    Elements el[] = {Fire,Water};
    Skill s1 = Skill("Naughtius Maximus","Nakal bangett!",10,2,el);

    s1.printAll();
    Skill s2 = s1;
    cout << s2;

    Elements el1[1] = {Ground};
    if (s1.isElementCompatible(1,el1)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}
