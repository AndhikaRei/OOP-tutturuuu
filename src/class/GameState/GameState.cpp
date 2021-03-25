#include "GameState.hpp"
GameState::GameState():map(20, 10, "map.txt"),parser(),player(){
    // Default constructor
    this->state = UI_FreeRoam;
    this->helpstate = 0;
    this->turn = 0;
    this->arg1 = ""; this->arg2 = "";
    initEngidex();
    databaseSkillInitialization();
}

GameState::~GameState()
{
    // Dtor
}
ShortInput GameState::get_parser(){
    // Mengambil objek parser dari game state
    return this->parser;
}
void GameState::print_start_guidance(){
    // Menuliskan penjelasan awal pada saat bermain game
    cout << "====================================================================================" <<'\n';
    cout << "Selamat datang di dunia engimon, Willy Wangky. Kamu akan berpetualang untuk menangkap dan" <<'\n';
    cout << "menaikkan level engimonmu. Kamu juga bisa melakukan breeding antar engimon yang kamu punya." << '\n'; 
    cout << "Kamu akan dibekali tiga engimon starter yaitu" << '\n';
    cout << "1) Pyro" <<'\n';
    cout << "2) Hydro" <<'\n';
    cout << "3) Electro" <<'\n';
    cout << "Ada dua kondisi dimana kamu bisa mengalami kekalahan, yaitu:" <<'\n';
    cout << "1) Kamu tidak mempunyai engimon lagi sehingga tidak ada active engimon yang menemani perjalananmu" <<'\n';
    cout << "2) Kamu melakukan exception 15 kali berturut-turut" <<'\n';
    cout << "Pastikan kamu menghindari dua kejadian diatas, selamat bermain!!!" <<'\n';
    cout << "====================================================================================" <<'\n';
    cout << "Akhir dari penjelasan, Klik apapun untuk bermain!"; getch();

}

void GameState::print_lose_Game(){
    // Menuliskan kalimat kekalahan
    cout << "====================================================================================" <<endl;
    cout <<"Anda telah kalah, Willy Wangky, pastikan di game selanjutnya anda bermain lebih baik"<<'\n';
    cout << "====================================================================================" <<'\n'; 
    cout <<"Tekan apapun untuk mengakhiri game!!"; getch();
}

void GameState::print_logo(){
    // Menuliskan logo game
    cout << "====================================================================================" <<endl;
    cout <<"                       _______    _   _                    _                     "<< endl;
    cout <<"      ______          |__   __|  | | | |                  | |             ______ "<< endl;
    cout <<"     |______|_____ ______| |_   _| |_| |_ _   _ _ __ _   _| |______ _____|______|"<< endl;
    cout <<"      _____|______|______| | | | | __| __| | | | '__| | | | |______|______|_____ "<< endl;
    cout <<"     |______|            | | |_| | |_| |_| |_| | |  | |_| |_|            |______|"<< endl;
    cout <<"                         |_|\\__,_|\\__|\\__|\\__,_|_|   \\__,_(_)                    "<< endl;                               
}
int GameState::value_user_input(){
    // Mendapatkan nilai ascii dari command player
    return this->parser.getCommand();
}
void GameState::visualize(){
    // Melakukan visualisasi tampilan Utama pada CLI
    // Visualisasi dilakukan berdasarkan state dari game sekarang
    cout << "====================================================================================" <<endl;
    cout << "                                   Halo "<< this->player.getName() <<endl;
    cout << "                                       Turn "<< to_string(this->turn) << endl;
    switch (this->state){
    case UI_FreeRoam:
        this->map.printMap();
        break;
    case UI_EngimonDimiliki:
        cout << "index | nama | spesies | [elemen] | [parent] | level | exp | cumulative exp | [Skill]" << endl;
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
        cout << "index | nama | spesies | [elemen] | [parent] | level | exp | cumulative exp | [Skill]" << endl;
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
    // Menampilkan tombol yang bisa ditekan apabila ada di tampilan map + Menampilkan legenda engimon
        cout << "                            Tampilan Free Roam "<< endl;
        cout << "w: maju      a: kiri      s: mundur      d: kanan      k: battle" << endl;
        cout << "l: tampilkan skill item yang dipunya       i: tampilkan engimon yang dipunya " << endl;
        cout << "j: cari engimon di ensiklopedia      b: breeding      e: pakai skill item" << endl;
        cout << "v: ganti active engimon      q: exit program     t: interact and examine active engimon " << endl;
        cout << "====================================================================================" <<endl;
        cout << "                            Engimon Legend "<< endl;
        cout << "f/F: pyro      w/W: hydro      e/E: electro      g/G: geo       i/I: cryo" << endl;
        cout << "a/A: vaporyze      l/L: overload      b/B: pyrocrystallize      d/D: electrocharged      c/C: melt" << endl;
        cout << "n/N: hydroCrystallize      s/S: frozen      h/H: electrocrystallize      j/J: superconductor     k/K: cryoCrystallize" << endl;
        break;
    case UI_EngimonDimiliki:
    // Menampilkan input/command yang harus dimasukkan apabila ada di layar engimon yang dimiliki
        if (this->helpstate==Menu_ChangeActiveEngimon){
            cout << "                            Change Active Engimon "<< endl;
            cout <<"Masukkan nomor index engimon di argumen satu, argumen dua bebas diisi apapun"<< endl;
        } else if (this->helpstate==Menu_Breeding){
            cout << "                            Tampilan Breeding "<< endl;
            cout <<"Masukkan nomor index parent di argumen satu dan dua"<< endl;
        } else {
            cout << "                            Daftar Engimon Yang Dimiliki "<< endl;
        }
        cout <<"Masukkan x di argumen satu dan dua untuk keluar dari menu ini" << endl;
        break;
    case UI_DetailEngimon:
    // Menampilkan input/command yang harus dimasukkan apabila ada di layar tampilan engidex
        cout << "                            Detail Engimon "<< endl;
        cout <<"Masukkan spesies engimon di argumen satu untuk mencari tahu" << endl;
        cout <<"Masukkan x di argumen satu untuk keluar dari menu ini" << endl;
        break;
    case UI_ItemSkillDimiliki:
    // Menampilkan input/command yang harus dimasukkan apabila ada di layar skill item yang dipunya
        cout << "                            Tampilan Item Skill "<< endl;
        cout <<"Tekan x untuk keluar dari menu ini"<< endl;
        break;
    case UI_EngimonDanItemSkill:
    // Menampilkan input/command yang harus dimasukkan apabila ada di layar pakai skill item
        cout <<"                            Tampilan Memilih Item Skill "<< endl;
        cout <<"Masukkan index engimon di argumen satu dan index item di argumen dua"<< endl;
        cout <<"Masukkan x di argumen satu dan dua untuk keluar dari menu ini"<< endl;
        break;
    default:
        throw InvalidStateException();
        break;
    }
    cout << "====================================================================================" <<endl;
}

int GameState::get_state(){
    // Mendapatkan state dari game sekarang
    return this->state;
}

void GameState::get_user_input(){
    // Mengambil user input secara cepat(bergantung pada state dari game)
    if(this->state == UI_FreeRoam ||this->state == UI_ItemSkillDimiliki ){
        // Input satu huruf
        cout << "Masukkan Input: "; this->parser.getInputFromUser();
    } else if(this->state == UI_DetailEngimon){
        // Input satu baris
        cout << "Masukkan argumen pertama: "; cin >> this->arg1;
    } else{
        // Input dua baris
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
            // Melakukan algoritma battle
            int xEnemy, yEnemy;
            // Mencari musuh di sekitar, apabila tidak ketemu, throw exception
            Engimon* enemy = map.getNearbyEnemyEngimon(&xEnemy,&yEnemy); 
            // Jika engimon kita menang maka, tambahkan engimon musuh ke inventory dan dapatkan skill item
            if (playerEngimonWin(*(player.getActiveEngimon()) , *enemy)){
                string name;
                cout << "Your engimon wins the battle" << endl;
                cout << "Berikan nama untuk engimon yang baru kamu kalahkan" << endl;
                cout <<"Masukkan nama: "; cin >> name;
                enemy->setName(name);
                player.addEngimon(enemy);
                Skill_Item* newSkill = new Skill_Item(getRandomSkillItem(databaseSkill,*enemy));
                player.addItem(newSkill);
                player.getActiveEngimon()->addExp(1500);
                this->map.removeEngimon(xEnemy,yEnemy);
                cout << "Pertarungan berakhir, tekan apapun!"<<endl; getch();
            } else {
            // Jika engimon kita kalah maka bunuh engimon aktiv sekarang dan cari engimon aktiv lain
                cout << "Your engimon lose the battle" << endl;
                player.killActiveEngimon();
                this->map.set_active_engimon_species(this->player.getActiveEngimon()->getSpecies());
                cout << "Pertarungan berakhir, tekan apapun!"<<endl; getch();
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
            cout << "Berhasil berinteraksi dan melihat status active engimon, Tekan apapun untuk melanjutkan" << getch();
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
            // Change active engimon, mengganti active engimon dan mengganti spesies engimon active di peta
            this->player.changeActiveEngimon(stoi(this->arg1));  
            this->map.set_active_engimon_species(this->player.getActiveEngimon()->getSpecies());  
            cout <<'\n'<<"Berhasil merubah active engimon, tekan apapun untuk melanjutkan" << '\n'; getch();
            this->state = UI_FreeRoam;
        } else if (this->helpstate==Menu_Breeding){
            // Melakukan breeding antara dua engimon lalu menambahkan anaknya ke dalam inventory
            string name;
            Engimon& a = *(player.getEngimon(stoi(this->arg1)));
            Engimon& b = *(player.getEngimon(stoi(this->arg2)));
            Engimon* c = &(breeding((*(player.getEngimon(stoi(this->arg1)))),(*(player.getEngimon(stoi(this->arg2))))));
            cout << "Berikan nama untuk engimon yang baru dilahirkan" << endl;
            cout <<"Masukkan nama: "; cin >> name;
            c->setName(name);
            player.addEngimon(c);
            cout <<'\n'<<"Berhasil melakukan breeding, tekan apapun untuk melanjutkan" << '\n'; getch();
        } else {
            throw InvalidStateException();
        break;
    case UI_DetailEngimon:{
        // Melihat detail engimon di engidex
        if (this->arg1 == "x"){
            this->state = UI_FreeRoam;
        }else{
            // Cari engimon sesuai spesies dan print detail engimonnya
            Engimon* searchedEngimon = EngimonFinderWithException(this->arg1);
            searchedEngimon->showEngimonEngidex();
            cout <<'\n'<<"Tekan apapun untuk melanjutkan" << '\n'; getch();
        } 
        
    }break;
    case UI_ItemSkillDimiliki:{
        // Ke layar ini cuma buat nampilin item skill yang dimiliki, commandnya hanya kembali ke tampilan map
        int command = this->parser.getCommand();
        if (command==KEY_x ){
            this->state =UI_FreeRoam;
        } else {
            throw InvalidCommandException();
        }
    }break;
    case UI_EngimonDanItemSkill:
        // Layar ini muncul apabila ingin memakaikan item skill ke engimon, commandnya hanya kembali ke tampilan map
         if (this->arg1 == "x" && this->arg2=="x"){
            this->state = UI_FreeRoam;
        } else {
            // Ambil item dan engimonnya yang diinginkan dan tambahkan skillnya ke engimon
            Engimon& a = *(player.getEngimon(stoi(this->arg1)));
            Skill_Item& b = *(player.getItem(stoi(this->arg2)));
            a.addSkill(b);
            cout <<'\n'<<"Berhasil menambahkan skill, tekan apapun untuk melanjutkan" << '\n'; getch();
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
    // Tambah turn, kosongkan argumen, bunuh semua engimon yang levelnya maksimum, dan hapus layar
    this->turn++;
    this->arg1 = ""; this->arg2 ="";

    // Lakukan Randomisasi spawn engimon tiap 3 turn
    srand(time(0));
    if(this->turn % 3 == 0){
        if(map.get_total_engimon() != map.get_max_engimon()){
            map.spawnRandomEngimon();
        }
    }

    // Cek apakah player masih mempunyai engimon tersisa atau tidak
    if (this->player.getEngimons().size()!=0){
        if(this->player.getActiveEngimon()->getLevel()>100){
            cout << "Engimon telah mencapai batas level maksimum" << endl;
            this->player.killActiveEngimon();
            this->map.set_active_engimon_species(this->player.getActiveEngimon()->getSpecies());  
            cout <<'\n'<<"Engimon telah dihapus, tekan apapun untuk melanjutkan" << '\n'; getch();
        }
    } else {
        this->state = Losing;
    }
    this->parser.clear();
}
