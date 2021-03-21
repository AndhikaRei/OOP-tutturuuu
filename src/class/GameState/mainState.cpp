#include <iostream>
using namespace std;
#include "GameState.hpp"
int main(){
    GameState gameState;
    string pauser;
    while(true){
        try{
            gameState.visualize();
            gameState.print_available_command();
            gameState.get_user_input();
            gameState.execute_user_input();
            gameState.evaluate_this_turn();
        }
        catch(WriteException& e){
            cout << endl << "==================================Exception Detected=============================" <<endl;
            cout << endl << e.what() << endl;
            cout <<"Tekan enter apapun melanjutkan"; getch();
            gameState.evaluate_this_turn();
        }
        catch(...){
            cout <<"Keanehan terdeteksi, pastikan input anda tidak ngawur banget, tekan apapun untuk melanjutkan"; getch();
            gameState.evaluate_this_turn();
        }
        
    }
    return 0;
}