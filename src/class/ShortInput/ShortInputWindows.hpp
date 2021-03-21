#ifndef _SHORTINPUT_H
#define _SHORTINPUT_H


#include <conio.h>
#include <cstdlib>
#include <string>
using namespace std;

#define KEY_b 98
#define KEY_w 119
#define KEY_a 97
#define KEY_s 115
#define KEY_d 100
#define KEY_e 101
#define KEY_l 108
#define KEY_k 107
#define KEY_j 106
#define KEY_i 105
#define KEY_v 118
#define KEY_x 120
#define KEY_q 113
#define KEY_t 116
#define clrscr() system("CLS")

class ShortInput
{
private:
    // Command dalam ascii
    int command;
public:
    ShortInput(/* args */);
    // dtor tidak perlu
    void getInputFromUser();
    // clearscreen
    void clear();
    // dapatkan command panjang
    int getCommand();
};



#endif

