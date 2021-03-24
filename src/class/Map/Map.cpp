#include "Map.hpp"

using namespace std;

// Map Elements Class Methods

// Default ctor
Map::MapElem::MapElem():MapElem(0,0,'x', false, new Pyro("Pyro sp."),"xxx"){};

// Ctor
Map::MapElem:: MapElem(int x, int y, char symbol, bool exist, Engimon* engi, string type){
    this->x = x;
    this->y = y;
    this->symbol = symbol;
    this->engimonExist = exist;
    this->engimon = engi->clone();
    this->type = type;
};        

// Dtor
Map::MapElem::~MapElem(){
    delete engimon;
};

// Getters and Setters 
void Map::MapElem::set_x(int x){
    // I.S. atribut x pada MapElem terdefinisi
    // F.S. atribut x pada MapElem telah diubah menjadi x
    this->x = x;
};

int Map::MapElem::get_x() const{
    // I.S. atribut x pada MapElem terdefinisi
    // F.S. mengembalikan nilai atribut x pada MapElem
    return this->x;
};

void Map::MapElem::set_y(int y){
    // I.S. atribut y pada MapElem terdefinisi
    // F.S. atribut y pada MapElem telah diubah menjadi y
    this->y = y;
};

int Map::MapElem::get_y() const{
    // I.S. atribut y pada MapElem terdefinisi
    // F.S. mengembalikan nilai atribut y pada MapElem
    return this->y;
};

void Map::MapElem::set_symbol(char sym){
    // I.S. atribut symbol pada MapElem terdefinisi
    // F.S. atribut symbol pada MapElem telah diubah menjadi sym
    this->symbol = sym;
};

char Map::MapElem::get_symbol() const{
    // I.S. atribut symbol pada MapElem terdefinisi
    // F.S. mengembalikan nilai atribut symbol pada MapElem
    return this->symbol;
};

void Map::MapElem::set_type(string type){
    // I.S. atribut type pada MapElem terdefinisi
    // F.S. atribut type pada MapElem telah diubah menjadi type
    this->type = type;
};

string Map::MapElem::get_type() const{
    // I.S. atribut type pada MapElem terdefinisi
    // F.S. mengembalikan nilai atribut type pada MapElem
    return this->type;
};

// Engimon Managers 
void Map::MapElem::set_engimon(Engimon* engimon){
    // I.S. atribut engimon pada MapElem terdefinisi
    // F.S. atribut engimon pada MapElem merujuk ke engimon
    this->engimon = engimon->clone();
};

Engimon* Map::MapElem::get_engimon() const{
     // I.S. atribut engimon pada MapElem terdefinisi
    // F.S. mengembalikan nilai pointer to engimon dari atribut engimon pada MapElem
    return this->engimon->clone();
};

void Map::MapElem::set_engimon_exist(bool status){
    // I.S. atribut engimonExist pada MapElem terdefinisi
    // F.S. atribut engimonExist pada MapElem telah diubah menjadi status
    this->engimonExist = status;
};

bool Map::MapElem::isEngimonExist() const{
     // I.S. atribut engimonExist pada MapElem terdefinisi
    // F.S. mengembalikan nilai atribut engimonExist pada MapElem
    return this->engimonExist;
};


// Map Class Methods
// Default ctor 
Map::Map(){
    this->length = 0;
    this->width = 0;
    this->total_engimon = 0;
};

// ctor
Map::Map(int m, int n, string txt){
    // I.S. m dan n terdefinisi untuk length dan width peta
    int i, j;
    this->length = m;
    this->width = n;
    // Inisialisasi Array of MapElem
    this->mapelem = new MapElem*[width];
    for(i = 0; i<width; i++){
        mapelem[i] = new MapElem[length];
    }
    char ch;
    // Read file txt per character
    // File txt only contains basic map symbol 'o' for sea and '-' for grassland
    ifstream infile(txt);
    i = 0;
    j = 0;
    // Set x, y, symbol, and type for each MapElem
    while(infile.get(ch)){
        if(ch != '\n'){
            mapelem[i][j].set_x(i);
            mapelem[i][j].set_y(j);
            mapelem[i][j].set_symbol(ch);
            if(ch == 'o'){
                mapelem[i][j].set_type("sea");
            } else{
                mapelem[i][j].set_type("grassland");
            }
            j++;
        } else{
            i++;
            j = 0;
        }
    }
    // Initialize Player Position
    this->player_pos = new int[2];
    this->player_pos[0] = 0;
    this->player_pos[1] = 1;
    // Initialize Active Engimon Position
    this->active_engimon_pos = new int[2];
    this->active_engimon_pos[0] = 0;
    this->active_engimon_pos[1] = 0;
    // Initialize default active engimon species
    this->active_engimon_species = "Pyro";
    this->mapelem[player_pos[0]][player_pos[1]].set_symbol('P');
    // set total wild engimon on map = 0 at the beginning
    this->total_engimon = 0;
};

// dtor
Map::~Map(){
    for(int i = 0; i<width; i++){
        delete[] mapelem[i];
    }
    delete[] mapelem;
    delete[] player_pos;
    delete[] active_engimon_pos;
};

// Checking if a position is valid for a pokemon based on the world boundaries and current symbol on the map
bool Map::isValidPosition(int x, int y, bool isActive){
    // I.S. Koordinat x dan y terdefinisi, isActive terdefinisi (false untuk wild engimon dan true untuk active engimon)
    // F.S. Mengembalikan true jika posisi valid, false jika tidak
    if(isActive){
        return ((x<this->width && x>=0 && y >=0 && y<this->length));
    } else{
        return ((x<this->width && x>=0 && y >=0 && y<this->length) && (this->mapelem[x][y].get_symbol()=='-' || this->mapelem[x][y].get_symbol()=='o'));
    }
    
};

bool Map::isValidEngimonPosition(int x, int y, string species, bool isActive){
    // I.S. Koordinat x dan y terdefinisi, jenis species engimon, isActive terdefinisi (false untuk wild engimon dan true untuk active engimon)
    // F.S. Mengembalikan true jika posisi valid, false jika tidak
    
    // Cek apakah ada engimon di tiles tersebut dan apakah x,y adalah posisi yang valid
    if(!this->mapelem[x][y].isEngimonExist() && isValidPosition(x, y, isActive)){
        // Cek kesesuaian species engimon dengan tipe tiles x,y
        if(species=="Pyro" || species=="Geo" || species=="Electro" || species=="Overload" || species=="PyroCrystallize" || species=="ElectroCrystallize" ){
            return(this->mapelem[x][y].get_type() == "grassland");
        } else if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
            return(this->mapelem[x][y].get_type() == "sea");
        } else{
            return true;
        }
    }
    return false;
};

// Check if there is any active engimon for player
bool Map::isAnyActiveEngimon() const{
    // I.S. Map terdefinisi
    // F.S. Mengembalikan true jika species selain undefined
    return this->active_engimon_species != "undefined";
};

// Check if x, y is position of player
bool Map::isPlayerPosition(int x, int y) const{
    // I.S. Map, posisi player, dan x, y terdefinisi
    // F.S. Mengembalikan true jika
    return (this->player_pos[0]==x) && (this->player_pos[1]==y);
};

int Map::get_total_engimon() const{
    // I.S. Map terdefinisi
    // F.S. Mengembalikan jumlah wild engimon yang ada di Map
    return this->total_engimon;
};

int Map::get_max_engimon() const{
    // I.S. Map terdefinisi
    // F.S. Mengembalikan jumlah maksimal wild engimon yang ada di Map
    return this->max_engimon;
};

// Map Manipulation Functions
void Map::printMap(){
    // I.S. Map dengan setiap MapElem terdefinisi
    // F.S. Map ditampilkan ke layar dengan symbol yang merepresentasikan Tipe Tiles/ Engimon/ Active Engimon/ Player

    // Update Map untuk mendapatkan symbol terbaru untuk setiap tiles
    this->updateMap();
    for(int i = 0; i<width; i++){
        // Print blank spaces
        cout <<"                                ";
        for(int j= 0; j<length ; j++){
            // Print symbol per tiles
           cout<<this->mapelem[i][j].get_symbol();
        }
        // Print newline
        cout<<endl;
    }
};

void Map::updateMap(){
    // I.S. Map terdefinisi
    // F.S. Symbol untuk setiap tiles telah diubah ke kondisi terbaru
    
    // Cek posisi engimon liar
    for(int i = 0; i<width; i++){
        for(int j= 0; j<length ; j++){
            if(this->mapelem[i][j].isEngimonExist() && !(this->player_pos[0] == i && this->player_pos[1] ==j)){
                this->mapelem[i][j].set_symbol(this->mapelem[i][j].get_engimon()->getEngimonSymbol());
            }
        }
    }
    // Cek posisi active engimon
    if(this->isAnyActiveEngimon()){
        this->mapelem[active_engimon_pos[0]][active_engimon_pos[1]].set_symbol('X');
    }
    // Cek posisi player
    this->mapelem[player_pos[0]][player_pos[1]].set_symbol('P');
};

// Engimon Handlers
map<string, vector<int>> Map::getEngimonPosition(){
    // I.S. Map terdefinisi dan keberadaan engimon liar di Map juga terdefinisi
    // F.S. Mengembalikan sebuah tipe data map dengan key species dan value nya adalah 
    // array of interger yang merepresentasikan posisi engimon liar pada map
    
    // Inisialisasi map untuk hasil
    map<string, vector<int>> result;
    // Untuk setiap tiles cek keberadaan engimon
    for(int i = 0; i<width; i++){
        for(int j= 0; j<length ; j++){    
            // Jika terdapat engimon liar pada tiles x,y
            if(this->mapelem[i][j].isEngimonExist()){
                // Tambahkan species engimon beserta posisinya ke map hasil
                result.insert(pair<string, vector<int>>(this->mapelem[i][j].get_engimon()->getSpecies(), {i, j}));
            }
       }
    }
    return result;
};

void Map::addEngimon(int x, int y, string species){
    // I.S. x, y, dan species engimon terdefinisi
    // F.S. Jika total engimon < max engimon dan di tiles x, y belum ada engimon maka engimon species di tambahkan ke tiles
    // Jumlah total engimon di map ditambah jika penambahan engimon berhasil
    // Jika salah satu kondisi tidak terpenuhi, throw exception sesuai dengan kondisinya

    // Cek apakah total engimon < max engimon
    if(total_engimon < max_engimon){
        // Cek apakah terdapat engimon liar pada tiles x, y
        if(this->mapelem[x][y].isEngimonExist()){
            throw(EngimonExist());
        } 
        // Cek apakah  species yang ingin ditambahkan cocok dengan type tiles x, y 
        else if(!isValidEngimonPosition(x, y, species, false)){
            // do nothing
        } 
        // Jika melewati kedua cek diatas maka tambahkan engimon ke tiles x, y
        else { 
            Engimon* newEngimon = EngimonFinder(species).front()->clone();
            this->mapelem[x][y].set_engimon_exist(true);
            this->mapelem[x][y].set_engimon(newEngimon);
            this->mapelem[x][y].set_symbol(newEngimon->getEngimonSymbol());
            this->total_engimon++; 
        }
    } 

};

void Map::removeEngimon(int x, int y){
    // I.S. x, y terdefinisi
    // F.S. Jika pada tiles x, y terdapat engimon, maka hilangkan engimon dari tiles itu 
    // dan ubah symbol dari tiles itu sesuai dengan tipe tiles serta kurangi jumlah engimon liar pada map
    

    // Cek apakah ada engimon liar pada tiles x, y
    if(this->mapelem[x][y].isEngimonExist()){
        this->mapelem[x][y].set_engimon_exist(false);
        this->mapelem[x][y].set_symbol(this->mapelem[x][y].get_type()=="grassland"?'-': 'o');
        this->total_engimon--; 
    }
};

void Map::moveEngimon(int x1, int y1, int x2, int y2, string species){
    // I.S. x1, y1 merupakan posisi awal engimon liar. x2, y2 merupakan posisi akhir engimon liar. 
    // F.S. Jika x2, y2 merupakan tiles yang valid untuk engimon species maka pindahkan engimon tersebut ke tiles itu
    
    // Cek kevalidan posisi x2, y2 untuk engimon
    if(this->isValidEngimonPosition(x2, y2, species, false)){
            removeEngimon(x1, y1);
            addEngimon(x2, y2, species);
    }
};

void Map::randomMoveAllEngimon(){
    // I.S. Engimon liar terdefinisi di map
    // F.S. Engimon bergerak random dengan jarak maksimal 1 dari posisi awal (ke atas, ke bawah, ke kanan, ke kiri, atau diam)
    // Jika tiles yang dituju valid maka engimon bergerak ke tiles itu, jika engimon bergerak ke tiles player maka throw exception InvalidEngimonMoveToPlayer
    
    // Ambil semua posisi pengimon beserta speciesnya dari map
    map<string, vector<int>> EngimonPos = this->getEngimonPosition();

    // Panggil modul srand untuk mereset angka yang dirandom
    srand (time(NULL));

    // Move setiap engimon di map
    for (map<string, vector<int>>::iterator it=EngimonPos.begin(); it!=EngimonPos.end(); ++it){
        int number =rand() % 5;
        int i = it->second[0];
        int j = it->second[1];
        
        if(number==1){
            // Engimon bergerak ke atas
            // Cek apakah tiles valid atau tiles yang dituju adalah tiles player
            if(isValidPosition(i-1, j, false)){
                this->moveEngimon(i, j, i-1, j, this->mapelem[i][j].get_engimon()->getSpecies());
            } else if(this->isPlayerPosition(i-1, j)){
                throw(InvalidEngimonMoveToPlayer());
            }
        }else if(number==2){
            // Engimon bergerak ke kiri
            // Cek apakah tiles valid atau tiles yang dituju adalah tiles player
            if(isValidPosition(i, j-1, false)){
                this->moveEngimon(i, j, i, j-1, this->mapelem[i][j].get_engimon()->getSpecies());
            }else if(this->isPlayerPosition(i, j-1)){
                throw(InvalidEngimonMoveToPlayer());
            }
        }else if(number==3){
            // Engimon bergerak ke bawah
            // Cek apakah tiles valid atau tiles yang dituju adalah tiles player
            if(isValidPosition(i+1, j, false)){
                this->moveEngimon(i, j, i+1, j, this->mapelem[i][j].get_engimon()->getSpecies());
            }else if(this->isPlayerPosition(i+1, j)){
                throw(InvalidEngimonMoveToPlayer());
            }
        } else if(number==4){
            // Engimon bergerak ke kanan
            // Cek apakah tiles valid atau tiles yang dituju adalah tiles player
            if(isValidPosition(i, j+1, false)){
                this->moveEngimon(i, j, i, j+1, this->mapelem[i][j].get_engimon()->getSpecies());
            }else if(this->isPlayerPosition(i, j+1)){
                throw(InvalidEngimonMoveToPlayer());
            }
        } else{
            // Engimon tidak bergerak
        }
    }      

};


void Map::spawnRandomEngimon(){
    // Fungsi ini digunakan untuk menambahkan pokemon liar ke permainan
    // Bekerja dengan memanfaatkan posisi random yang digenerate menggunakan fungsi rand() dari library standard C 
    // Fungsi ini bekerja secara pseudo random, sehingga apabila terlalu banyak engimon yang sudah ada di map ( > 100 )
    // Fungsi akan memaksa keluar dan menghasilkan exception "Engimon Exist"
    // I.S. Map dengan setiap MapElem terdefinisi
    // F.S. Memunculkan Engimon liar baru di map. 


    // Bekerja untuk menambahkan engimon liar baru dengan maksimal 120 pokemon 
    // Tidak ada level handling. Seluruh Engimon baru akan di spawn pada level 0. 
    // Berikut himpunan untuk meningkatkan probabilitas munculnya engimon dengan satu elemen. 
    vector<string> Pokemons{
        "Pyro", 
        "Pyro", 
        "Pyro", 
        "Hydro",
        "Hydro",
        "Hydro", 
        "Vaporize", 
        "Overload", 
        "PyroCrystallize", 
        "Melt", 
        "Electro",
        "Electro", 
        "Electro", 
        "ElectroCharged", 
        "HydroCrystallize",
        "Frozen", 
        "Geo",
        "Geo",
        "Geo",
        "ElectroCrystallize", 
        "Superconductor",
        "Cryo",
        "Cryo",
        "Cryo", 
        "CryoCrystallize"
    };

    // Random Number Generator membutuhkan seed dari program global 
    int randomNumber = rand() % Pokemons.size();
    Engimon* newEngimon = EngimonFinderWithException(Pokemons[randomNumber]);
    string species = newEngimon->getSpecies();

    // Logika program hanya bekerja sesuai map.txt setidaknya sampai tanggal 22/03/2021
    // Batasan Area Air 
    const int waterStartX = 10;
    const int waterEndX = 19;
    const int waterStartY = 0;
    const int waterEndY = 5;
    int x;
    int y;
    
    // Generate posisi engimon liar baru 
    if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
        // Cek untuk Engimon yang hanya dapat bergerak di area air
        x = (rand() % (this->length - waterStartX)) + waterStartX;
        y = rand() % (this->width - waterEndY + 1);
    } else {
        y = rand() % (this->width);
        if(y <= waterEndY){
            x = rand() % (this->length - waterStartX);
        } else { 
            x = rand() % (this->length);
        } 
    }   

    // Membatasi runtime 
    int i = 0;

    // Mencoba posisi lain apabila terbentur dengan sebuah exeception. 
    while ((this->mapelem[y][x].get_symbol()!='-') && (this->mapelem[y][x].get_symbol()!='o')) {
        if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
            x = (rand() % (this->length - waterStartX - 1)) + waterStartX;
            y = rand() % (this->width - waterEndY);
        } else {
            y = rand() % (this->width - 1);
            if(y <= waterEndY){
                x = rand() % (this->length - waterStartX - 1);
            } else { 
                x = rand() % (this->length - 1);
            } 
        }    

        // This is a safe valve if we would ever use the application to spawn more than 100 Engimons 
        if ( i == 100){
            // Try to find a slot for the new Engimon 
            break;
        }
        i++;
    }

    // Menambahkan engimon baru 
    // Exception handling sudah ditangani oleh fungsi addEngimon
    this->addEngimon(y, x, Pokemons[randomNumber]);
}

Engimon* Map::getNearbyEnemyEngimon(int* X, int* Y){
    // Fungsi ini digunakan untuk battle dengan engimon liar
    // I.S. Posisi player terdeifinisi di map
    // F.S. Jika terdapat engimon disekitar player (diatas/dibawah/dikanan/dikiri) 
    // maka X dan Y adalah posisi diketemukannya engimon pertama kali di sekitar player
    // Jika tidak ada engimon liar disekitar player maka throw exception

    // Cek apakah diatas posisi player sekarang terdapat engimon liar
    if(isValidPosition(this->player_pos[0]-1, this->player_pos[1], true)){
        if (this->mapelem[this->player_pos[0]-1][this->player_pos[1]].isEngimonExist()){
            *X = this->player_pos[0]-1; *Y =this->player_pos[1];
            return this->mapelem[this->player_pos[0]-1][this->player_pos[1]].get_engimon();
        }
    } 

    // Cek apakah di kiri posisi player sekarang terdapat engimon liar
    if(isValidPosition(this->player_pos[0], this->player_pos[1]-1, true)){
        if (this->mapelem[this->player_pos[0]][this->player_pos[1]-1].isEngimonExist()){
            *X = this->player_pos[0]; *Y =this->player_pos[1]-1;
            return this->mapelem[this->player_pos[0]][this->player_pos[1]-1].get_engimon();
        }
    }

    // Cek apakah di bawah posisi player sekarang terdapat engimon liar 
    if(isValidPosition(this->player_pos[0]+1, this->player_pos[1], true)){
        if (this->mapelem[this->player_pos[0]+1][this->player_pos[1]].isEngimonExist()){
            *X = this->player_pos[0]+1; *Y =this->player_pos[1];
            return this->mapelem[this->player_pos[0]+1][this->player_pos[1]].get_engimon();
        }
    }

    // Cek apakah di kanan posisi player sekarang terdapat engimon liar  
    if(isValidPosition(this->player_pos[0], this->player_pos[1]+1, true)){
        if (this->mapelem[this->player_pos[0]][this->player_pos[1]+1].isEngimonExist()){
            *X = this->player_pos[0]; *Y =this->player_pos[1]+1;
            return this->mapelem[this->player_pos[0]][this->player_pos[1]+1].get_engimon();
        }
    }

    // Jika tidak diketemukan engimon liar disekitar player, throw exception
    throw InvalidBattleException();
}

// Player Handlers 
void Map::move(char c){
    // I.S. Command c terdefinisi antara w, a, s, d
    // F.S. Jika tiles yang dituju valid untuk engimon dan active engimon, 
    // pindahkah engimon dan active engimonnya sesuai command
    // Jika tidak throw exception sesuai kondisi

    // Cek apakah player memiliki active engimon dan apakah posisi player yang sekarang adalah posisi yang valid untuk ditempati active engimon jika player bergerak
    if(isAnyActiveEngimon() && isValidEngimonPosition(player_pos[0], player_pos[1], get_active_engimon_species(), true) ){
        if(c == 'w'){
            // Player ingin bergerak ke atas
            if(isValidPosition(player_pos[0]-1, player_pos[1], true) && mapelem[player_pos[0]-1][player_pos[1]].isEngimonExist()){
                // Cek apakah player bergerak ke tiles yang diisi oleh engimon liar
                throw(InvalidPlayerMove());
            }else if(!isValidPosition(player_pos[0]-1, player_pos[1], true)){
                // Cek apakah player bergerak ke posisi yang valid (tidak keluar map)
                throw(InvalidMoveException());
            }else{
                // Pindahkan player dan active engimon ke atas
                set_player_pos(this->player_pos[0]-1, this->player_pos[1]);
                set_active_engimon_pos(this->player_pos[0]+1, this->player_pos[1]);
            }
        }else if(c == 'a'){
            // Player ingin bergerak ke kiri
            if(isValidPosition(player_pos[0], player_pos[1]-1, true) && mapelem[player_pos[0]][player_pos[1]-1].isEngimonExist()){
                // Cek apakah player bergerak ke tiles yang diisi oleh engimon liar
                throw(InvalidPlayerMove());
            }else if(!isValidPosition(player_pos[0], player_pos[1]-1, true)){
                // Cek apakah player bergerak ke posisi yang valid (tidak keluar map)
                throw(InvalidMoveException());
            }else{
                // Pindahkan player dan active engimon ke kiri
                set_player_pos(this->player_pos[0], this->player_pos[1]-1);
                set_active_engimon_pos(this->player_pos[0], this->player_pos[1]+1);
            }
        }else if(c == 's'){
            // Player ingin bergerak ke bawah
            if(isValidPosition(player_pos[0]+1, player_pos[1], true) && mapelem[player_pos[0]+1][player_pos[1]].isEngimonExist()){
                // Cek apakah player bergerak ke tiles yang diisi oleh engimon liar
                throw(InvalidPlayerMove());
            }else if(!isValidPosition(player_pos[0]+1, player_pos[1], true)){
                // Cek apakah player bergerak ke posisi yang valid (tidak keluar map)
                throw(InvalidMoveException());
            }else{
                // Pindahkan player dan active engimon ke bawah
                set_player_pos(this->player_pos[0]+1, this->player_pos[1]);
                set_active_engimon_pos(this->player_pos[0]-1, this->player_pos[1]);
            }
        }else if(c == 'd'){
            // Player ingin bergerak ke kanan
             if(isValidPosition(player_pos[0], player_pos[1]+1, true) && mapelem[player_pos[0]][player_pos[1]+1].isEngimonExist()){
                // Cek apakah player bergerak ke tiles yang diisi oleh engimon liar
                throw(InvalidPlayerMove());
            }else if(!isValidPosition(player_pos[0], player_pos[1]+1, true)){
                // Cek apakah player bergerak ke posisi yang valid (tidak keluar map)
                throw(InvalidMoveException());
            }else{
                // Pindahkan player dan active engimon ke kanan
                set_player_pos(this->player_pos[0], this->player_pos[1]+1);
                set_active_engimon_pos(this->player_pos[0], this->player_pos[1]-1);
            }
        }
    } else if(isAnyActiveEngimon()){
        // Cek species active engimon yang menyebabkan player tidak bisa bergerak
        // Throw exception sesuai species active engimon
        string species = this->get_active_engimon_species();
        if(species=="Pyro" || species=="Geo" || species=="Electro" || species=="Overload" || species=="PyroCrystallize" || species=="ElectroCrystallize" ){
            throw(InvalidEngimonPositionSea());
        } else if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
            throw(InvalidEngimonPositionGrassland());
        }
    }else{
        // Player tidak memiliki active engimon
        if(c == 'w'){
            // Player bergerak ke atas
            set_player_pos(this->player_pos[0]-1, this->player_pos[1]);
        }else if(c == 'a'){
            // Player bergerak ke kiri
            set_player_pos(this->player_pos[0], this->player_pos[1]-1);
        }else if(c == 's'){
            // Player bergerak ke bawah
            set_player_pos(this->player_pos[0]+1, this->player_pos[1]);
        }else if(c == 'd'){
            // Player bergerak ke kanan
            set_player_pos(this->player_pos[0], this->player_pos[1]+1);
        }
    }
    int x, y;

    // Setelah player memberikan command w,a,s,d maka turn akan bertambah
    // Lakukan randomisasi gerakan untuk setiap engimon liar yang ada di map
    this->randomMoveAllEngimon();
    // Print kondisi map terbaru
    this->printMap();
};

void Map::set_player_pos(int x, int y){
    // I.S. x dan y adalah posisi baru dari player
    // F.S. pindahkan player jika x, y adalah tiles yang valid dan ubah symbol tiles posisi player sebelumnya sesuai type tiles
    if(x>=0 && x<10 && y>=0 && y<20){
        if(this->mapelem[player_pos[0]][player_pos[1]].get_type() == "grassland"){
            this->mapelem[player_pos[0]][player_pos[1]].set_symbol('-');
        } else{
            this->mapelem[player_pos[0]][player_pos[1]].set_symbol('o');
        }
        this->player_pos[0] = x;
        this->player_pos[1] = y;
        this->mapelem[x][y].set_symbol('P');
    } else{
        // Jika tiles x, y tidak valid throw exception InvalidMoveException
        throw InvalidMoveException();
    }
};

int* Map::get_player_pos() const{
    // I.S. Map dan posisi player pada map terdefinisi
    // F.S. Mengembalikan posisi player pada map dalam array of integer dengan size 2
    return this->player_pos;
};

void Map::set_active_engimon_pos(int x, int y){
    // I.S. x dan y adalah posisi baru dari active engimon
    // F.S. pindahkan active engimon jika x, y adalah tiles yang valid sesuai species active engimon 
    // dan ubah symbol tiles posisi active engimon sebelumnya sesuai type tiles

    string species = this->active_engimon_species;
    // Cek apakah tiles x, y valid untuk active engimon
    if(isValidEngimonPosition(x, y, species, true)){
        if(this->mapelem[active_engimon_pos[0]][active_engimon_pos[1]].get_type() == "grassland"){
            this->mapelem[active_engimon_pos[0]][active_engimon_pos[1]].set_symbol('-');
        } else{
            this->mapelem[active_engimon_pos[0]][active_engimon_pos[1]].set_symbol('o');
        }
        this->active_engimon_pos[0] = x;
        this->active_engimon_pos[1] = y;
        this->mapelem[x][y].set_symbol('X');
    }else{
        // Jika tiles tidak valid untuk current active engimon, throw exception sesuai typenya
        if(species=="Pyro" || species=="Geo" || species=="Electro" || species=="Overload" || species=="PyroCrystallize" || species=="ElectroCrystallize" ){
            throw(InvalidEngimonPositionSea());
        } else if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
            throw(InvalidEngimonPositionGrassland());
        }
    }
};

int* Map::get_active_engimon_pos()const{
    // I.S. Map dan posisi active engimon pada map terdefinisi
    // F.S. Mengembalikan posisi active engimon pada map dalam array of integer dengan size 2
    return this->active_engimon_pos;
};

void Map::set_active_engimon_species(string species){
    // I.S. map terdefinisi dan spesies active engimon terdefinisi atau "undefined"
    // F.S. mengubah nilai atribut active engimon species pada map menjadi species
    this->active_engimon_species = species;
};

string Map::get_active_engimon_species()const{
    // I.S. map terdefinisi dan spesies active engimon terdefinisi atau "undefined"
    // F.S. mengembalikan nilai dari atribut active engimon species
    return this->active_engimon_species;
};