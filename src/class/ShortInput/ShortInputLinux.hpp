/*  
  Diambil dari https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux
  Mohon maaf kak saya bukan user linux jadi nggatau cara getch di linux sehingga ambil kodingannya dari
  stackoverfllow 
*/

#ifndef _SHORTINPUTLINUX_H
#define _SHORTINPUTLINUX_H

#include <cstdlib>
#include <string>
#include <termios.h>
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
#define clrscr() printf("\033c")

/* Initialize new terminal i/o settings */
static struct termios old, current;

void initTermios(int echo);
void resetTermios(void);
char getch_(int echo);
char getch();
char getche(void);

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

