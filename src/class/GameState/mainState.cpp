#include <iostream>
using namespace std;
#include "GameState.hpp"
int main(){
    GameState gameState;
    gameState.print_start_guidance();
    gameState.get_parser().clear();
    while(gameState.get_state() != Losing){
        try{
            gameState.print_logo();
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
    gameState.print_lose_Game();
    return 0;
}