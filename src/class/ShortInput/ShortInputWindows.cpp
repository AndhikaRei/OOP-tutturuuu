#include "ShortInputWindows.hpp"
ShortInput::ShortInput()
{
    this->command = 0;
    
}
void ShortInput::getInputFromUser(){
    int c;
    c = getch();
    this->command = c;
}
void ShortInput::clear(){
    clrscr();
}
int ShortInput::getCommand(){
    return this->command;
}



