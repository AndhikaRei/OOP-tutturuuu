#include "Elements.hpp"

// Element advantages
const float ElementAdvantage[5][5] = 
{{1,0,1,0.5,2},
{2,1,0,1,1},
{1,2,1,0,1.5},
{1.5,1,2,1,0},
{0,1,0.5,2,1}};


std::string elementName(Elements el) {
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

int elementId(std::string el) {
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


// const Elements Fire(0,Water,Electric);
// const Elements Water(1,Electric,Fire);
// const Elements Electric(2,)


// int main(int argc, char const *argv[])
// {
//     std::cout << ElementAdvantage[Water][Ground] << std::endl;
    
//     return 0;
// }
