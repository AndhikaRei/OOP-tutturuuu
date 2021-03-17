#ifndef _EXCEPTION_H
#define _EXCEPTION_H

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
        return("Andat tidak bisa bergerak ke sana");
    }
};

class InvalidElement : public WriteException{
public:
    const char* what(){
        return("Elemen tidak tersedia");
    }
};


#endif
