#include "../Skill.hpp"

int main()
{
    databaseSkillInitialization();

    

    Skill s0 = databaseSkill.at(10);
    s0.showSkill();

    Skill s1 = s0;


    if (s1.isElementCompatible(Fire)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}
