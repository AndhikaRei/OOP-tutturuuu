#include "../Skill_Item.hpp"

int main()
{
    Elements el[] = {Fire,Water};
    Skill s1 = Skill("Naughtius Maximus","Nakal bangett!",10,2,el);

    Skill_Item sk1 = Skill_Item(s1);

    sk1.showItem();

    sk1.addAmount();

    

    Skill_Item sk2(sk1);
    sk2.showItem();
    Skill s2 = sk1.learn(Water);
    s2.levelUp();
    cout << s2.getMasteryLevel() << endl;
    sk1.showItem();
    sk1 = sk2;
    cout << sk1 << endl;
    cout << "hehe";
}
