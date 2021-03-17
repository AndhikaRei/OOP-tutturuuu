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
        throw InvalidElement();
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
