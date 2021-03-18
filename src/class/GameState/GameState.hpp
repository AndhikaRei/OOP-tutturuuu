#ifndef _GAMESTATE_H
#define _GAMESTATE_H
#include "../Map/Map.h"
#include "../Engimon/Engimon.hpp"
#include "../Elements/Elements.hpp"
#include "../ShortInput/ShortInputWindows.hpp"
// #include "../ShortInput/ShortInputLinux.hpp"
#include "../Exception/Exception.hpp"
#include "../Skill/Skill.hpp"
#include <string>
#include <iostream>
using namespace std;

#define UI_FreeRoam 1
#define UI_EngimonDanItemSkill 2
#define UI_EngimonDimiliki 3
#define UI_ItemSkillDimiliki 4
#define UI_DetailEngimon 5
#define UI_Battle 6
#define Menu_Breeding 7
#define Menu_ChangeActiveEngimon 8


class GameState
{
private:
    Map map; // Map dari player
    ShortInput parser; // Parser adalah class yang menangi input sejumlah satu huruf
    string arg1, arg2; // Input panjang yang ditangani dengan cin
    int state, helpstate; // State dari game, akan menentukan apa yang harus diinput dan apa yang harus di print
    int turn; // Giliran sekarang
    // Player
    // List of Monster mungkin
    // Dan seterusnya

public:
    GameState();
    ~GameState();

    // Kelompok Method UI CLI
    void visualize();
    void print_available_command();

    //Kelompok Method Aksi
    void get_user_input();
    int value_user_input();
    void execute_user_input();
    void evaluate_this_turn();

    // Dan seterusnya
};

GameState::GameState():map(20, 10, "map.txt"),parser(){
    this->state = UI_FreeRoam;
    this->helpstate = 0;
    this->turn = 0;
    this->arg1 = ""; this->arg2 = "";
}
GameState::~GameState()
{
}
int GameState::value_user_input(){
    return this->parser.getCommand();
}
void GameState::visualize(){
    // Melakukan visualisasi tampilan Utama pada CLI
    // Visualisasi dilakukan berdasarkan state dari game sekarang
    cout << "====================================================================================" <<endl;
    cout << "                            Turn "<< to_string(this->turn) << endl;
    switch (this->state){
    case UI_FreeRoam:
        this->map.printMap();
        break;
    case UI_EngimonDimiliki:
        cout <<"Nantinya akan berisi tampilan list engimon yang dimiliki"<< endl;
        cout <<"Semestinya player/inventory punya method ini, CMIIW kalo gue salah" << endl;
        break;
    case UI_DetailEngimon:
        cout <<"Menampilkan detail dari suatu engimon, kaya ensiklopedia, nampilin skill ama parent"<< endl;
        cout <<"Semestinya engimon/turunannya punya method ini, CMIIW kalo gue salah" << endl;
        break;
    case UI_ItemSkillDimiliki:
        cout <<"Menampilkan item skill dan jumlahnya di inventory"<< endl;
        cout <<"Semestinya player/iventory punya method ini, CMIIW kalo gue salah" << endl;
        break;
    case UI_EngimonDanItemSkill:
        cout <<"Menampilkan item skill, jumlahnya dan Engimon di inventory"<< endl;
        cout <<"Semestinya player/inventory punya method ini, CMIIW kalo gue salah" << endl;
        break;
    case UI_Battle:
        cout <<"Menampilkan stat musuh yang dibattle dan ascii artnya WKWK"<< endl;
        cout <<"Semestinya engimon/turunannya punya method ini, CMIIW kalo gue salah" << endl;
        break;
    default:
        throw InvalidStateException();
        break;
    }
    cout << "====================================================================================" <<endl;
}

void GameState::print_available_command(){
    // Melakukan visualisasi tampilan bantuan berisikan tombol/intruksi yang bisa dilakukan
    // Visualisasi dilakukan berdasarkan state dari game sekarang
    switch (this->state){
    case UI_FreeRoam:
        cout << "                            Tampilan Free Roam "<< endl;
        cout << "w: maju      a: kiri      s: mundur      d: kanan      k: battle" << endl;
        cout << "l : tampilkan skill item yang dipunya       i: tampilkan engimon yang dipunya " << endl;
        cout << "j: cari engimon di ensiklopedia      b : breeding      e : pakai skill item" << endl;
        cout << "v: ganti active engimon      q: exit program" << endl;
        break;
    case UI_EngimonDimiliki:
        if (this->helpstate==Menu_ChangeActiveEngimon){
            cout << "                            Change Active Engimon "<< endl;
            cout <<"Masukkan nama engimon di argumen satu, kosongkan argumen dua"<< endl;
        } else if (this->helpstate==Menu_Breeding){
            cout << "                            Tampilan Breeding "<< endl;
            cout <<"Masukkan nama parent di argumen satu dan dua"<< endl;
        } else {
            cout << "                            Daftar Engimon Yang Dimiliki "<< endl;
        }
        cout <<"Masukkan x di argumen satu dan dua untuk keluar dari menu ini" << endl;
        break;
    case UI_DetailEngimon:
        cout << "                            Detail Engimon "<< endl;
        cout <<"Tekan x untuk keluar dari menu ini" << endl;
        break;
    case UI_ItemSkillDimiliki:
        cout << "                            Tampilan Item Skill "<< endl;
        cout <<"Tekan x untuk keluar dari menu ini"<< endl;
        break;
    case UI_EngimonDanItemSkill:
        cout <<"                            Tampilan Memilih Item Skill "<< endl;
        cout <<"Masukkan nama item di argumen satu dan nama engimon di argumen dua"<< endl;
        cout <<"Masukkan x di argumen satu dan dua untuk keluar dari menu ini"<< endl;
        break;
    default:
        throw InvalidStateException();
        break;
    }
    cout << "====================================================================================" <<endl;
}

void GameState::get_user_input(){
    // Mengambil user input secara cepat, input panjang akan ditangani dengan cin
    if(this->state == UI_FreeRoam || this->state == UI_DetailEngimon ||this->state == UI_ItemSkillDimiliki ){
        cout << "Masukkan Input: "; this->parser.getInputFromUser();
    } else{
        cout << "Masukkan argumen pertama: "; cin >> this->arg1;
        cout << "Masukkan argumen kedua: "; cin >> this->arg2;
    }
}

void GameState::execute_user_input(){
    // Mengeksekusi input yang telah dimasukkan user
    // Eksekusi dilakukan berdasarkan state dari game sekarang
switch (this->state){
    case UI_FreeRoam:{
        int command = this->parser.getCommand();
        if (command==KEY_w || command==KEY_a|| command==KEY_s|| command==KEY_d){
            this->map.move((char)command);
        } else if (command==KEY_k){
            /* Prototype dan Prediksi Fungsi
            Engimon& enemy = map.findAdjacentEnemy(); // Throw aja kalo ga ketemu
            if playerEngimonWin(Engimon& player, Engimon& enemy){
                Player.addEngimon(Engimon& enemy);
                Player.addSkillItem(getRandomSkillItem(vector<Skill> listOfSkill, Engimon& enemy))
                Player.addSelectedEngimonEXP(30)
            } else {
                Player.killActiveEngimon()
                Player.changeActiveEngimon()
            }
            */
            throw InvalidBattleException();
        } else if(command == KEY_l){
            /*
            Player.ShowItemSkill()
            */
            this->state = UI_ItemSkillDimiliki;
        } else if(command == KEY_i){
            /*
            Player.ShowAllEngimon()
            */
            this->state = UI_EngimonDimiliki;
        } else if(command == KEY_j ){
            // Nama Engimon yang dicek harus divalidasi pada implementasi aslinya
            cout<<"Masukkan nama species engimon yang ingin dicek "; cin >> this->arg1;
            this->state = UI_DetailEngimon; 
        } else if(command ==KEY_b){
            this->state = UI_EngimonDimiliki;
            this->helpstate = Menu_Breeding;
        } else if (command == KEY_e){
            this->state = UI_EngimonDanItemSkill;
        } else if(command == KEY_v){
            this->state = UI_EngimonDimiliki;
            this->helpstate = Menu_ChangeActiveEngimon;
        } else if(command == KEY_q){
            exit(0);
        } else {
            throw InvalidCommandException();
        }
        }break;
    case UI_EngimonDimiliki:
        if (this->arg1 == "x" && this->arg2=="x"){
            this->state = UI_FreeRoam;
            this->helpstate = 0;
        } else {
            throw InvalidBreeding();
            //throw InvalidChangeActiveEngimon();
        } 
        break;
    case UI_DetailEngimon:{
        int command = this->parser.getCommand();
        if (command==KEY_x ){
            this->state =UI_FreeRoam;
        } else {
            throw InvalidCommandException();
        }
    }break;
    case UI_ItemSkillDimiliki:{
        int command = this->parser.getCommand();
        if (command==KEY_x ){
            this->state =UI_FreeRoam;
        } else {
            throw InvalidCommandException();
        }
    }break;
    case UI_EngimonDanItemSkill:
         if (this->arg1 == "x" && this->arg2=="x"){
            this->state = UI_FreeRoam;
        } else {
            throw InvalidUsingItemToEngimon();
        }
        break;
    default:
        throw InvalidStateException();
        break;
    }
}
void GameState::evaluate_this_turn(){
    // Method yang harus dilakukan setiap akhir giliran
    this->turn++;
    this->arg1 = ""; this->arg2 ="";
    // Lakukan randomisasi gerakan monster yang ada di map
    // Lakukan level up jika monster sudah mencapai kelipatan exp
    // Bunuh semua engimon yang levelnya sudah max
    // clearscreen
    this->parser.clear();
}



#endif