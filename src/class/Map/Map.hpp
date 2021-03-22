#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <string>
#include <map>
#include <iterator> 
#include <iomanip>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random> // A better random number generator
#include "../Exception/Exception.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Elements/Elements.hpp"

using namespace std;

/*--- CLASS MAP ---*/
class Map{
    private :
        /*--- CLASS MapElem ---*/
        class MapElem{
            private :
                int x; /* Tiles Abscissa Coordinate */
                int y; /* Tiles Ordinate Coordinate */
                char symbol; /* Tiles Symbol on Map that represents Tiles Type / Engimon / Active Engimon/ Player */
                bool engimonExist; /* Boolean Status For The Existance of a Wild Engimon in this Tiles */
                Engimon* engimon; /* Pointer to Engimon in this Tiles*/
                string type; /* Tiles type either grassland or sea*/
            public :
                // 4 Sekawan
                MapElem(); // default ctor
                MapElem(int, int, char, bool, Engimon*, string); //ctor
                //cctor tidak perlu
                //assignment operator tidak perlu;
                ~MapElem(); // dtor

                // Getter and Setter
                void set_x(int);
                int get_x() const;
                void set_y(int);
                int get_y() const;
                void set_symbol(char);
                char get_symbol() const;
                void set_type(string);
                string get_type() const;

                // Engimon Managers 
                void set_engimon(Engimon*);
                Engimon* get_engimon() const;
                void set_engimon_exist(bool);
                bool isEngimonExist() const;
        };
        /* Map Attributes */
        int length; // Map Length
        int width; // Map Width
        MapElem** mapelem; // Array of MapElem
        int* player_pos; // Array of Integer with size 2 for Player Position
        int* active_engimon_pos; // Array of Integer with size 2 for Active Engimon Position
        string active_engimon_species;  // Current Active Engimon Species
        int total_engimon; // Total Wild Engimon that exist on Map
        const int max_engimon = 20; // Maximum Engimon Exist on Map
    public :
        // 4 Sekawan
        Map(); // Default ctor
        Map(int, int, string); // ctor
        // cctor tdk perlu
        ~Map(); // dtor

        // boolean method
        bool isValidPosition(int, int, bool);
        bool isValidEngimonPosition(int, int, string, bool);
        bool isAnyActiveEngimon() const;
        bool isPlayerPosition(int, int) const;

        // getter;
        int get_total_engimon() const;
        int get_max_engimon() const;

        // Map Manipulation Functions 
        void printMap();
        void updateMap();

        // Engimon Handlers
        map<string, vector<int>> getEngimonPosition();
        void addEngimon(int, int, string);
        void removeEngimon(int, int);
        void moveEngimon(int, int, int, int, string);
        void randomMoveAllEngimon();
        void spawnRandomEngimon();
        Engimon* getNearbyEnemyEngimon(int* X, int* Y);
        
        // Player Handlers 
        void move(char);
        void set_player_pos(int, int);
        int* get_player_pos() const;
        void set_active_engimon_pos(int, int);
        int* get_active_engimon_pos()const;
        void set_active_engimon_species(string);
        string get_active_engimon_species()const;    
};
#endif
