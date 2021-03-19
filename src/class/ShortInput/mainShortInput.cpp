#include <iostream>
#include <cstdlib>
#include "ShortInputWindows.hpp"
using namespace std;
int main(){
    ShortInput p;
    for (int i = 0; i < 5; i++)
    {
        p.getInputFromUser();
        if(p.getCommand()==KEY_w){
            cout << "W ditekan" << endl;
        } else if(p.getCommand()==KEY_k){
            cout << "A ditekan" << endl;
        } else {
            cout << "yanglain ditekan" << endl;
        }
    }
    p.clear();
    p.getInputFromUser();
    
}