#ifndef _ELEMENTS_HPP_
#define _ELEMENTS_HPP_

#include <string>
#include "../Exception/Exception.hpp"

#define Elements int
#define Fire 0
#define Water 1
#define Electric 2
#define Ground 3
#define Ice 4

// Database element Advantage
extern const float ElementAdvantage[5][5];

// element to string name
std::string elementName(Elements el);
int elementId(std::string el);



// #include <string>


// class Elements
// {
// private:
//     int ID;
//     Elements Weakness;
//     Elements Strength;
// public:
//     // Constructor
//     Elements(int ID, Elements Weakness, Elements Strength);
    
//     // Tidak perlu dtor

//     bool operator==(Elements a, Elements b) const;

//     // Getter
//     Elements getID() const;
//     Elements getWeakness() const;
//     Elements getStrength() const;
// };

// extern const Elements Fire;
// extern const Elements Water;
// extern const Elements Electric;
// extern const Elements Ground;
// extern const Elements Ice;




#endif