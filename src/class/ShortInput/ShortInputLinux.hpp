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
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch() 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}


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

