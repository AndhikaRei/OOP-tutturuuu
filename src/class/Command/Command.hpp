#ifndef _COMMAND_H
#define _COMMAND_H
#include <iostream>
#include <string>
#include "../Map/Map.h"
using namespace std;

class Command{
// Abstract base class untuk command
public :
    virtual void execute() = 0;
    // Setiap command bisa di execute 
     
};

class MoveCommand: public Command{
private :
    int newPosX,newPosY;
public :
    void execute();
     
};


#endif