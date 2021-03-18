#ifndef _Battle_HPP_
#define _Battle_HPP_

#include "Engimon.hpp"
#include "../Elements/Elements.hpp"
#include "../Skill/Skill.hpp"
#include "../Skill_Item/Skill_Item.hpp"
#include <vector>
#include <random>
#include <set>
#include <algorithm>

using std::vector;
using std::set;

bool playerEngimonWin(Engimon& player, Engimon& enemy);
int sumOfSkillPower(Engimon& player);
Skill_Item getRandomSkillItem(vector<Skill>& listOfSkill, Engimon& enemy);

#endif