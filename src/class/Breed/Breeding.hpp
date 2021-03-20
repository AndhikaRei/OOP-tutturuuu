#ifndef _BREEDING_HPP_
#define _BREEDING_HPP_

#include "../Engimon/Engimon.hpp"
#include <vector>
#include <map>

using std::vector;
using std::map;
using std::pair;

vector<Skill> sortingSkill(Engimon& parent_a, Engimon& parent_b);

void addSkillAnak(Engimon& child, vector<Skill> calonSkill);
bool isElementSimilar(Engimon& parent_a, Engimon& parent_b, vector<Elements>* similiarEle);
vector<Elements> sortElementAdvantage(Engimon& parent_a, Engimon& parent_b);
Engimon& breeding(Engimon& parent_a, Engimon& parent_b);


#endif