#ifndef _GAMESTATE_H
#define _GAMESTATE_H
#include "../Map/Map.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Elements/Elements.hpp"
#include "../ShortInput/ShortInputWindows.hpp"
// #include "../ShortInput/ShortInputLinux.hpp"
#include "../Exception/Exception.hpp"
#include "../Skill/Skill.hpp"
#include "../Player/player.hpp"
#include "../Engimon/Battle.hpp"
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


// compile
// g++ -o main mainState.cpp ../Engimon/Engimon.cpp ../Engimon/Battle.cpp ../Map/Map.cpp ../Skill/Skill.cpp ../Elements/Elements.cpp ../Skill_Item/Skill_Item.cpp ../Player/player.cpp
class GameState
{
private:
    Map map; // Map dari player
    ShortInput parser; // Parser adalah class yang menangi input sejumlah satu huruf
    string arg1, arg2; // Input panjang yang ditangani dengan cin
    int state, helpstate; // State dari game, akan menentukan apa yang harus diinput dan apa yang harus di print
    int turn; // Giliran sekarang
    Player player;
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

GameState::GameState():map(20, 10, "map.txt"),parser(),player(){
    this->state = UI_FreeRoam;
    this->helpstate = 0;
    this->turn = 0;
    this->arg1 = ""; this->arg2 = "";
    initEngidex();
    databaseSkillInitialization();

    // Coba coba tambahin engimon
    this->map.addEngimon(9, 16, "Pyro");
    this->map.addEngimon(4, 10, "Hydro");
    this->map.addEngimon(2, 2, "Pyro");
    this->map.addEngimon(3, 3, "CryoCrystallize");
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
    cout << "Halo "<< this->player.name <<endl;
    cout << "                            Turn "<< to_string(this->turn) << endl;
    switch (this->state){
    case UI_FreeRoam:
        this->map.printMap();
        break;
    case UI_EngimonDimiliki:
        cout << "index | nama | spesies | elemen | parent | level | exp | cumulative exp" << endl;
        this->player.printEngimon();
        break;
    case UI_DetailEngimon:
        printEngidex();
        break;
    case UI_ItemSkillDimiliki:
        this->player.printInventory();
        break;
    case UI_EngimonDanItemSkill:
        cout << "Engimon" << endl;
        cout << "index | nama | spesies | elemen | parent | level | exp | cumulative exp" << endl;
        this->player.printEngimon();
        cout << "Inventory" << endl;
        this->player.printInventory();
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
        cout << "l: tampilkan skill item yang dipunya       i: tampilkan engimon yang dipunya " << endl;
        cout << "j: cari engimon di ensiklopedia      b: breeding      e: pakai skill item" << endl;
        cout << "v: ganti active engimon      q: exit program     t: interact " << endl;
        cout << "====================================================================================" <<endl;
        cout << "                            Engimon Legend "<< endl;
        cout << "f/F: pyro      w/W: hydro      e/E: electro      g/G: geo       i/I: cryo" << endl;
        cout << "a/A: vaporyze      l/L: overload      b/B: pyrocrystallize      d/D: electrocharged      c/C: melt" << endl;
        cout << "n/N: hydroCrystallize      s/S: frozen      h/H: electrocrystallize      j/J: superconductor     k/K: cryoCrystallize" << endl;
        break;
    case UI_EngimonDimiliki:
        if (this->helpstate==Menu_ChangeActiveEngimon){
            cout << "                            Change Active Engimon "<< endl;
            cout <<"Masukkan nomor index engimon di argumen satu, kosongkan argumen dua"<< endl;
        } else if (this->helpstate==Menu_Breeding){
            cout << "                            Tampilan Breeding "<< endl;
            cout <<"Masukkan nomor index parent di argumen satu dan dua"<< endl;
        } else {
            cout << "                            Daftar Engimon Yang Dimiliki "<< endl;
        }
        cout <<"Masukkan x di argumen satu dan dua untuk keluar dari menu ini" << endl;
        break;
    case UI_DetailEngimon:
        cout << "                            Detail Engimon "<< endl;
        cout <<"Masukkan spesies engimon di argumen satu untuk mencari tahu" << endl;
        cout <<"Masukkan x di argumen satu untuk keluar dari menu ini" << endl;
        break;
    case UI_ItemSkillDimiliki:
        cout << "                            Tampilan Item Skill "<< endl;
        cout <<"Tekan x untuk keluar dari menu ini"<< endl;
        break;
    case UI_EngimonDanItemSkill:
        cout <<"                            Tampilan Memilih Item Skill "<< endl;
        cout <<"Masukkan nomor item di argumen satu dan nomor engimon di argumen dua"<< endl;
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
    if(this->state == UI_FreeRoam ||this->state == UI_ItemSkillDimiliki ){
        cout << "Masukkan Input: "; this->parser.getInputFromUser();
    } else if(this->state == UI_DetailEngimon){
        cout << "Masukkan argumen pertama: "; cin >> this->arg1;
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
        // Dibawah adalah kemungkinan tombol saat UI nya sedang menampilkan peta
        int command = this->parser.getCommand();
        if (command==KEY_w || command==KEY_a|| command==KEY_s|| command==KEY_d){
            this->map.move((char)command);
        } else if (command==KEY_k){
            // Prototype dan Prediksi Fungsi detailnya diserahkan ke player
            Engimon* enemy = map.getNearbyEnemyEngimon(); // Throw aja kalo ga ketemu
        
            if (playerEngimonWin(*(player.getActiveEngimon()) , *enemy)){
                cout << "Your engimon wins the battle" << endl;
                player.addEngimon(enemy);
                //player.addItem(getRandomSkillItem(vector<Skill> listOfSkill, Engimon& enemy)); //eventually pake ini sementara aku bikin skil baru aja dulu 
                Skill* SpiritSoother;
                SpiritSoother = new Skill("SpiritSoother", "Elemental Burst", 9003, Fire);
                Skill_Item* BookOfFreedom;
                BookOfFreedom = new Skill_Item(*SpiritSoother);
                player.addItem(BookOfFreedom);
                
                player.getActiveEngimon()->addExp(30);
                cout << "Debugging battle"<<endl; getch();
            } else {
                player.killActiveEngimon();
                cout << "Debugging battle"<<endl; getch();
                //player.changeActiveEngimon();
            }
        } else if(command == KEY_l){
            // Pindah ke layar yang menampilkan list item skill yang dipunyai
            this->state = UI_ItemSkillDimiliki;
        } else if(command == KEY_i){
            // Pindah ke layar yang menampilkan list engimon yang dipunya
            this->state = UI_EngimonDimiliki;
        } else if(command == KEY_j ){
            // Pindah ke layar yang menampilkan detail engimon (kayak engidex)
            this->state = UI_DetailEngimon; 
        } else if(command ==KEY_b){
            // Pindah ke layar list engimon dengan keinginan untuk melakukan breeding
            this->state = UI_EngimonDimiliki;
            this->helpstate = Menu_Breeding;
        } else if (command == KEY_e){
            // Pindah ke layar yang menampilkan item skill dan engimon yang dipunya dengan niatan mau pake item skill ke engimon
            this->state = UI_EngimonDanItemSkill;
        } else if(command == KEY_v){
            // Pindah ke layar yang menampilkan list engimon yang dipunya dengan niatan mengganti active engimon
            this->state = UI_EngimonDimiliki;
            this->helpstate = Menu_ChangeActiveEngimon;
        } else if(command == KEY_q){
            // Exit program
            exit(0);
        } else if (command == KEY_t){
            // Interact dengan active engimon
             
            player.interactWithActiveEngimon();
            
        } else {
            throw InvalidCommandException();
        }
        }break;
    case UI_EngimonDimiliki:
        // Dibawah adalah kemungkinan input saat UI nya sedang menampilkan list engimon
        // Input untuk exit 
        if (this->arg1 == "x" && this->arg2=="x"){
            this->state = UI_FreeRoam;
            this->helpstate = 0;
        } else if(this->helpstate == Menu_ChangeActiveEngimon){
            // Jika niatan pindah kesini adalah untuk change active engimon, fungsinya cuma blueprint aja, detil implementasi terserah kamu
            // Engimon& a = Player.FindEngimonWithVectorIndex(String.toInt(this->arg1))
            player.changeActiveEngimon();
        } else if (this->helpstate==Menu_Breeding){
            // Jika niatan pindah kesini adalah untuk breeding engimon, fungsinya cuma blueprint aja
            // Validasi slot masi cukup ga
            // Engimon& a = Player.FindEngimonWithVectorIndex(String.toInt(this->arg1))
            // Engimon& b = Player.FindEngimonWithVectorIndex(String.toInt(this->arg2))
            // Engimon& c = breeding(a,b)
            // Player.addEngimon(c)
        } else {
            throw InvalidStateException();
        break;
    case UI_DetailEngimon:{
        // Ke layar ini cuma buat lihat engimon dari engidex
        if (this->arg1 == "x"){
            this->state = UI_FreeRoam;
        }else{
            Engimon* searchedEngimon = EngimonFinderWithException(this->arg1);
            searchedEngimon->showEngimonEngidex();
            cout <<'\n'<<"Tekan Enter untuk melanjutkan" << '\n'; getch();
        } 
        
    }break;
    case UI_ItemSkillDimiliki:{
        // Ke layar ini cuma buat nampilin item skill yang dimiliki
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
            // Engimon& a = Player.FindEngimonWithVectorIndex(String.toInt(this->arg1))
            // Item b = Player.FindItemWithVectorIndex(String.toInt(this->arg2))
            // Detilnya nunggu dari player aja deh
            player.printInventory();
            throw InvalidUsingItemToEngimon();
        }
        break;
    default:
        throw InvalidStateException();
        break;
    }
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