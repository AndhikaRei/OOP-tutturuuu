#include "Elements.hpp"

// Element advantages
const float ElementAdvantage[5][5] = 
{{1,0,1,0.5,2},
{2,1,0,1,1},
{1,2,1,0,1.5},
{1.5,1,2,1,0},
{0,1,0.5,2,1}};


string elementName(Elements el) {
    switch (el)
    {
    case 0:
        return "Fire";
    case 1:
        return "Water";
    case 2:
        return "Electric";
    case 3:
        return "Ground";
    case 4:
        return "Ice";
    default:
        throw InvalidElementNotExist();
    } 
}

int elementId(string el) {
    // agak khawatir pake switch
    if (el == "Fire") {
        return 0;
    } else if (el == "Water") {
        return 1;
    } else if (el == "Electric") {
        return 2;
    } else if (el == "Ground") {
        return 3;
    } else if (el == "Ice") {
        return 4;
    } else {
        throw InvalidElementNotExist();
    }
    
}


float elementAdvantage(Elements eleAlly, Elements eleEnemy) {
    return ElementAdvantage[eleAlly][eleEnemy];
}

// float elementAdvantage(std::string eleAlly, std::string eleEnemy) {
//     return elementAdvantage(elementId(eleAlly),elementId(eleEnemy));
// }
float totalElementAdvantage(vector<Elements> eleAlly, vector<Elements> eleEnemy) {
    float eleAdv = 0;
    for (int i = 0; i < eleAlly.size(); i++)
    {
        for (int j = 0; j < eleEnemy.size(); j++)
        {
            if (eleAdv < elementAdvantage(eleAlly[i],eleEnemy[j])) {
                eleAdv = elementAdvantage(eleAlly[i],eleEnemy[j]);
            }
        }   
    }
    return eleAdv;
}





