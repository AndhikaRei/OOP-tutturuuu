#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

class WriteException{
    // Exception yang bisa disolve hanya dengan nulis sesuatu ke layar   
public:
    virtual const char* what()=0;
};

class InvalidStateException : public WriteException{
public:
    const char* what(){
        return("State tidak valid");
    }
};
class InvalidBattleException : public WriteException{
public:
    const char* what(){
        return("Tidak ada yang bisa anda battle di sekitar anda");
    }
};
class InvalidCommandException : public WriteException{
public:
    const char* what(){
        return("Tombol yang anda pencet tidak valid brow");
    }
};
class InvalidBreeding : public WriteException{
public:
    const char* what(){
        return("Anda tidak bisa melakukan breeding dengan engimon itu");
    }
};
class InvalidBreedingInsufficientLevel  : public WriteException{
public:
    const char* what(){
        return("Level Engimon anda tidak memenuhi syarat untuk breeding");
    }
};
class UnexpectedErrorWhileBreeding : public WriteException{
public:
    const char* what(){
        return("Terjadi error saat breeding");
    }
};
class InvalidChangeActiveEngimon : public WriteException{
public:
    const char* what(){
        return("Anda tidak mempunyai engimon tersebut");
    }
};
class InvalidUsingItemToEngimon : public WriteException{
public:
    const char* what(){
        return("Item atau engimon yang anda pilih tidak valid ");
    }
};
class InvalidMoveException : public WriteException{
public:
    const char* what(){
        return("Anda tidak bisa bergerak ke sana");
    }
};

class InvalidElementNotCompatible : public WriteException{
public:
    const char* what(){
        return("Elemen tidak cocok");
    }
};

class InvalidElementNotExist : public WriteException{
public:
    const char* what(){
        return("Elemen tidak ada");
    }
};

class InvalidNotEnoughItemAmount : public WriteException{
public:
    const char* what(){
        return("Jumlah skill item tidak cukup");
    }
};

class InvalidFullSkill : public WriteException{
public:
    const char* what(){
        return("Skill Engimon sudah penuh");
    }
};

class EngimonExist : public WriteException{
public:
    const char* what(){
        return("Sudah ada engimon di tiles ini");
    }
};

class InvalidEngimonPositionGrassland : public WriteException{
public:
    const char* what(){
        return("Engimonmu tidak bisa berada di darat");
    }
};

class InvalidEngimonPositionSea : public WriteException{
public:
    const char* what(){
        return("Engimonmu tidak bisa berada di air");
    }
};

class InvalidEngimonMove : public WriteException{
public:
    const char* what(){
        return("Engimon tidak bisa berpindah tempat");
    }
};

class InvalidPlayerMove : public WriteException{
public:
    const char* what(){
        return("Ada engimon liar disana");
    }
};

class MaximumEngimonReached : public WriteException{
public:
    const char* what(){
        return("Jumlah Engimon pada Peta terlalu banyak");
    }
};

class NoEngimonFound : public WriteException{
public:
    const char* what(){
        return("Tidak ada engimon disini");
    }
};
class noActiveEngimon : public WriteException{
public:
    const char* what(){
        return("Belum ada Active Engimon");
    }
};

class InventoryFull : public WriteException{
public:
    const char* what(){
        return("Inventory penuh");
    }
};
class InvalidSpeciesEngidex : public WriteException{
public:
    const char* what(){
        return("Tidak ada pokemon dengan spesies tersebut");
    }
};


#endif
