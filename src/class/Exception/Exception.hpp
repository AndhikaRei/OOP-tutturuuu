#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

class WriteException{
    // Exception yang bisa disolve hanya dengan nulis sesuatu ke layar   
public:
    virtual const char* what()=0;
};

class InvalidStateException : public WriteException{
public:
    const char* what();
};
class InvalidBattleException : public WriteException{
public:
    const char* what();
};
class InvalidCommandException : public WriteException{
public:
    const char* what();
};

class InvalidEngimonNotExist : public WriteException{
public:
    const char* what();
};

class InvalidBreeding : public WriteException{
public:
    const char* what();
};
class InvalidBreedingInsufficientLevel  : public WriteException{
public:
    const char* what();
};
class UnexpectedErrorWhileBreeding : public WriteException{
public:
    const char* what();
};

class InvalidMoveException : public WriteException{
public:
    const char* what();
};

class InvalidElementNotCompatible : public WriteException{
public:
    const char* what();
};

class InvalidElementNotExist : public WriteException{
public:
    const char* what();
};

class InvalidNotEnoughItemAmount : public WriteException{
public:
    const char* what();
};


class InvalidSkillAlreadyLearned : public WriteException{
public:
    const char* what();
};

class EngimonExist : public WriteException{
public:
    const char* what();
};

class InvalidEngimonPositionGrassland : public WriteException{
public:
    const char* what();
};

class InvalidEngimonPositionSea : public WriteException{
public:
    const char* what();
};

class InvalidEngimonMoveToPlayer : public WriteException{
public:
    const char* what();
};

class InvalidPlayerMove : public WriteException{
public:
    const char* what();
};


class InventoryFull : public WriteException{
public:
    const char* what();
};

class InvalidIndex: public WriteException{
public:
    const char* what();
};

#endif
