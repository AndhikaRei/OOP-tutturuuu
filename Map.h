#ifndef _MAP_H
#define _MAP_H
#include <iostream>
#include <string>
using namespace std;

class Map{
    private :
        class MapElem{
            private :
                int x;
                int y;
                char symbol;
                string pokemon;
            public :
                MapElem();
                MapElem(int, int, char, string);
                //cctor tidak perlu
                //assignment operator tidak perlu;
                //dtor tidak perlu;
                void set_x(int);
                int get_x() const;
                void set_y(int);
                int get_y() const;
                void set_symbol(char);
                char get_symbol() const;
                void set_string(string);
                string get_pokemon() const;
        };
        int length;
        int width;
        MapElem** mapelem;
    public :
        Map();
        Map(int, int, string);
        Map(const Map&);
        ~Map();
        
        void printMap();
};


#endif
