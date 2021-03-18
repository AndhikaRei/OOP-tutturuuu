#ifndef _ELEMENTS_HPP_
#define _ELEMENTS_HPP_

#include <string>
#include <vector>
#include "../Exception/Exception.hpp"

using std::string;
using std::vector;

#define Elements int
#define Fire 0
#define Water 1
#define Electric 2
#define Ground 3
#define Ice 4
#define NONE -1

// Database element Advantage
extern const float ElementAdvantage[5][5];

// element id to string name
string elementName(Elements el);
// element name to element id
int elementId(string el);


float elementAdvantage(Elements eleAlly, Elements eleEnemy);
// float elementAdvantage(std::string eleAlly, std::string eleEnemy);
float totalElementAdvantage(vector<Elements> eleAlly, vector<Elements> eleEnemy);





#endif