#include "Exception.hpp"

const char* InvalidStateException::what(){
    return("State tidak valid");
} 

const char* InvalidBattleException::what(){
    return("Tidak ada yang bisa anda battle di sekitar anda");
}

const char* InvalidCommandException::what(){
    return("Tombol yang anda pencet tidak valid brow");
}

const char* InvalidEngimonNotExist::what(){
    return("Engimon yang anda cari tidak tersedia");
}

const char* InvalidBreedingInsufficientLevel:: what(){
    return("Level Engimon anda tidak memenuhi syarat untuk breeding");
}
        
const char* UnexpectedErrorWhileBreeding::what(){
    return("Terjadi error saat breeding");
}

const char* InvalidMoveException::what(){
    return("Anda tidak bisa bergerak ke sana");
}

const char* InvalidElementNotCompatible::what(){
    return("Elemen tidak cocok");
}

const char* InvalidElementNotExist::what(){
    return("Elemen tidak ada");
}

const char* InvalidNotEnoughItemAmount::what(){
     return("Jumlah skill item tidak cukup");
}


const char* InvalidSkillAlreadyLearned::what() {
    return("Skill sudah dipelajari oleh Engimon");
};

const char* EngimonExist::what(){
    return("Sudah ada engimon di tiles ini");
}

const char* InvalidEngimonMoveToPlayer::what(){
    return("Engimon liar tidak bisa bergerak ke posisi Player. Melakukan reposisi engimon liar.");
}

const char* InvalidPlayerMove::what(){
    return("Ada engimon liar disana");
}

const char* InventoryFull::what(){
    return("Inventory penuh");
}

const char* InvalidIndex::what(){
    return("Index salah");
}



