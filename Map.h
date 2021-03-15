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
                string type; //grassland or sea
            public :
                MapElem();
                MapElem(int, int, char, string, string);
                //cctor tidak perlu
                //assignment operator tidak perlu;
                //dtor tidak perlu;
                void set_x(int);
                int get_x() const;
                void set_y(int);
                int get_y() const;
                void set_symbol(char);
                char get_symbol() const;
                void set_type(string);
                string get_type() const;
                void set_pokemon(string);
                string get_pokemon() const;
        };
        int length;
        int width;
        MapElem** mapelem;
        int* player_pos;
    public :
        Map();
        Map(int, int, string);
        Map(const Map&);
        ~Map();
        
        void printMap();
        void move(char);
        void set_player_pos(int, int);
        int* get_player_pos()const;
};


#endif
