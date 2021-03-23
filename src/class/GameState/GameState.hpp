#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include "../Map/Map.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Elements/Elements.hpp"
#include "../ShortInput/ShortInputWindows.hpp"
#include "../Breed/Breeding.hpp"
// #include "../ShortInput/ShortInputLinux.hpp"
#include "../Exception/Exception.hpp"
#include "../Skill/Skill.hpp"
#include "../Player/Player.hpp"
#include "../Battle/Battle.hpp"
#include <string>
#include <iostream>
using namespace std;

#define UI_FreeRoam 1
#define UI_EngimonDanItemSkill 2
#define UI_EngimonDimiliki 3
#define UI_ItemSkillDimiliki 4
#define UI_DetailEngimon 5
#define Menu_Breeding 7
#define Menu_ChangeActiveEngimon 8
#define Losing 99

class GameState
{
private:
    // Map dari player
    Map map; 
    // Parser adalah class yang menangi input sejumlah satu huruf
    ShortInput parser; 
    // Input panjang yang ditangani dengan cin
    string arg1, arg2; 
    // State dari game, akan menentukan apa yang harus diinput dan apa yang harus di print
    int state, helpstate; 
    // Giliran sekarang
    int turn; 
    // Player yang bermaind
    Player player;
    

public:
    // 4 sekawan
    GameState();
    ~GameState();

    //getter,setter
    int get_state();
    ShortInput get_parser();
    

    // Kelompok Method UI CLI
    void visualize();
    void print_available_command();
    void print_logo();
    void print_lose_Game();
    void print_start_guidance();

    //Kelompok Method Aksi
    void get_user_input();
    int value_user_input();
    void execute_user_input();
    void evaluate_this_turn();

    // Dan seterusnya
};
#endif