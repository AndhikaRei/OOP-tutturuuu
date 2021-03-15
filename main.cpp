#include <iostream>
#include "Map.h"
using namespace std;


int main() {
    Map m(20, 10, "map.txt");
    m.printMap();
    return 0;
}