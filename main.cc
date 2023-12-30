#include <bits/stdc++.h>
#include "client.h"
using namespace std;


int main(int argc, char *argv[]){
    Client client{};
    for(int i = 1; i < argc; ++i){
        if(string(argv[i]) == "-space"){ // to play space invaders game
            client.initializeSpaceInvaders();
        }else if(string(argv[i]) == "-coin"){ // to play coin collecting game
            client.initializeCoinCollectGame();
        }
        client.go();
    }
}
