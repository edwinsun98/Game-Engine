#include <iostream>
#include "client.h"
using namespace std;

Client::Client(): eng{} {}

void Client::initializeSpaceInvaders(){
    // Initialize border
    eng.addBorder(0, BorderCollisionType::Solid, -1, 1000, 100, 0);

    // Initialize player
    int player = eng.addBasicObject(0, 0, 100, 10, 0, 20, 37, 'P');
    int playerProjectile = eng.addBasicObject(1, 1, 100, 10, 0, 0, 0, 'o');
    eng.addAttribute(player, "health", 200);
    eng.addAttribute(playerProjectile, "damage", 2);
    eng.addStraightMovement(playerProjectile, 1, -1, 0);
    eng.addSpawnerMovement(player, 10, vector<int>{playerProjectile}, 1);
    eng.addWASDMovement(player, 1, 0);
    eng.addStopCollision(0, -1);

    // Initialize small enemies
    int smallEnemyCount = 4;
    vector<int> smallEnemies(smallEnemyCount);
    for(int i = 0; i < smallEnemyCount; ++i){
        smallEnemies[i] = eng.addBitmapObject(0, 2, 100, 10, 0, vector<tuple<int,int,char>>{{2, 4+i*22, 'V'},
                            {3, 4+i*22, 'H'}, {3, 5+i*22, 'X'}, {3, 6+i*22, 'H'},
                             {4, 5+i*22, 'V'}, {2, 6+i*22, 'V'}});
        if(i%2)eng.addStraightMovement(smallEnemies[i], 30, 0, -1);
        else eng.addStraightMovement(smallEnemies[i], 30, 0, 1);
        eng.addBorderMovement(smallEnemies[i], 40, BorderType::DownEdge);
        eng.addAttribute(smallEnemies[i], "health", 30);
        eng.addAttribute(smallEnemies[i], "damage", 1);
        eng.addOneWayDamageCollision(1, 2, "health", "damage");
        eng.addOneWayDamageCollision(2, 0, "health", "damage");
        eng.addEndGameCollision(-1, 2, 0);
    }

    // Initialize meteors (two rectangles bouncing across the board)
    int meteorCount = 2;
    vector<int> meteors(meteorCount);
    meteors[0] = eng.addRectangleObject(0, 3, 100, 10, 0, 2, 2, 2, 3, 'M');
    eng.addStraightMovement(meteors[0], 10, 1, 4);
    eng.addAttribute(meteors[0], "damage", 1);
    eng.addStopCollision(-1, 3);
    eng.addBounceCollision(-1, 3);
    meteors[1] = eng.addRectangleObject(0, 3, 100, 10, 0, 2, 75, 2, 3, 'M');
    eng.addStraightMovement(meteors[1], 10, 1, -4);
    eng.addAttribute(meteors[1], "damage", 1);
    eng.addOneWayDamageCollision(3, 0, "health", "damage");
    eng.addBounceCollision(0, 3);

    // Initialize boss (largest bitmap object on the board)
    int refRow = 4, refCol = 30;
    int boss = eng.addBitmapObject(0, 4, 100, 10, 0, 
                    vector<tuple<int,int,char>>{{refRow, refCol+2, 'V'}, {refRow+1, refCol+1, 'T'},
                    {refRow+1, refCol+2, 'X'}, {refRow+1, refCol+3, 'T'}, {refRow+2, refCol, 'Y'},
                    {refRow+2, refCol+2, 'W'}, {refRow+2, refCol+4, 'Y'}, {refRow+3, refCol+1, 'A'},
                    {refRow+3, refCol+3, 'A'}, {refRow+4, refCol+2, 'M'}, {refRow+2, refCol-3, 'O'},
                    {refRow+2, refCol+7, 'O'}});

    vector<vector<tuple<int,int,char>>> bossCyclicMovements;
    vector<tuple<int,int,char>> cycle1{{refRow, refCol+2, 'V'}, {refRow+1, refCol+1, 'T'},
                    {refRow+1, refCol+2, 'X'}, {refRow+1, refCol+3, 'T'}, {refRow+2, refCol, 'Y'},
                    {refRow+2, refCol+2, 'W'}, {refRow+2, refCol+4, 'Y'}, {refRow+3, refCol+1, 'A'},
                    {refRow+3, refCol+3, 'A'}, {refRow+4, refCol+2, 'M'}, {refRow+2, refCol-3, 'O'},
                    {refRow+2, refCol+7, 'O'}};
    vector<tuple<int,int,char>> cycle2{{refRow, refCol+2, 'V'}, {refRow+1, refCol+1, 'T'},
                    {refRow+1, refCol+2, 'X'}, {refRow+1, refCol+3, 'T'}, {refRow+2, refCol, 'Y'},
                    {refRow+2, refCol+2, 'W'}, {refRow+2, refCol+4, 'Y'}, {refRow+3, refCol+1, 'A'},
                    {refRow+3, refCol+3, 'A'}, {refRow+4, refCol+2, 'M'}, {refRow-1, refCol-1, 'O'},
                    {refRow+5, refCol+5, 'O'}};
    vector<tuple<int,int,char>> cycle3{{refRow, refCol+2, 'V'}, {refRow+1, refCol+1, 'T'},
                    {refRow+1, refCol+2, 'X'}, {refRow+1, refCol+3, 'T'}, {refRow+2, refCol, 'Y'},
                    {refRow+2, refCol+2, 'W'}, {refRow+2, refCol+4, 'Y'}, {refRow+3, refCol+1, 'A'},
                    {refRow+3, refCol+3, 'A'}, {refRow+4, refCol+2, 'M'}, {refRow-2, refCol+2, 'O'},
                    {refRow+6, refCol+2, 'O'}};
    vector<tuple<int,int,char>> cycle4{{refRow, refCol+2, 'V'}, {refRow+1, refCol+1, 'T'},
                    {refRow+1, refCol+2, 'X'}, {refRow+1, refCol+3, 'T'}, {refRow+2, refCol, 'Y'},
                    {refRow+2, refCol+2, 'W'}, {refRow+2, refCol+4, 'Y'}, {refRow+3, refCol+1, 'A'},
                    {refRow+3, refCol+3, 'A'}, {refRow+4, refCol+2, 'M'}, {refRow-1, refCol+5, 'O'},
                    {refRow+5, refCol-1, 'O'}};
    bossCyclicMovements.push_back(cycle1);
    bossCyclicMovements.push_back(cycle2);
    bossCyclicMovements.push_back(cycle3);
    bossCyclicMovements.push_back(cycle4);
    eng.addCyclicMovement(boss, 20, bossCyclicMovements);
    eng.addBorderMovement(boss, 50, BorderType::DownEdge);
    eng.addEndGameCollision(-1, 4, 0);
    eng.addAttribute(boss, "health", 100);
    eng.addAttribute(boss, "damage", 10);
    eng.addOneWayDamageCollision(1, 4, "health", "damage");
    eng.addOneWayDamageCollision(4, 0, "health", "damage");

    // Add customized status lines
    eng.addGameStatusLine();
    eng.addAttributeStatusLine(player, "health", "Your Health: ");
    eng.addAttributeStatusLine(boss, "health", "Boss Health: ");

    // Add win lose conditions
    eng.addAttributeWinLose(0, vector<tuple<int,int,string>>{{0, player, "health"}});
    eng.addTypeCountWinLose(1, vector<pair<int,int>>{{0, 4}, {0, 2}});
}

void Client::initializeCoinCollectGame(){
    // Initialize border
    eng.addBorder(0, BorderCollisionType::View, -1, 1000, 100, 0);

    // Initialize player
    int player = eng.addBasicObject(0, 0, 100, 10, 0, 1, 1, 'P');
    eng.addWASDMovement(player, 1, 0);
    eng.addStopCollision(0, -1);
    eng.addAttribute(player, "coins", 0);
    eng.addAttribute(player, "damage", 1);

    // Initialize walls
    int wallCount = 3;
    vector<int> walls(wallCount);
    walls[0] = eng.addRectangleObject(0, 1, 100, 10, 0, 1, 20, 17, 1, 'X');
    walls[1] = eng.addRectangleObject(0, 1, 100, 10, 0, 4, 40, 17, 1, 'X');
    walls[1] = eng.addRectangleObject(0, 1, 100, 10, 0, 1, 60, 17, 1, 'X');
    eng.addStopCollision(0, 1);

    // Initialize coins
    int coinCount = 11;
    vector<int> coins(coinCount);
    coins[0] = eng.addBasicObject(0, 2, 100, 10, 0, 7, 10, 'C');
    coins[1] = eng.addBasicObject(0, 2, 100, 10, 0, 12, 10, 'C');
    coins[2] = eng.addBasicObject(0, 2, 100, 10, 0, 17, 10, 'C');
    coins[3] = eng.addBasicObject(0, 2, 100, 10, 0, 15, 23, 'C');
    coins[4] = eng.addBasicObject(0, 2, 100, 10, 0, 19, 28, 'C');
    coins[5] = eng.addBasicObject(0, 2, 100, 10, 0, 6, 35, 'C');
    coins[6] = eng.addBasicObject(0, 2, 100, 10, 0, 19, 28, 'C');
    coins[7] = eng.addBasicObject(0, 2, 100, 10, 0, 3, 49, 'C');
    coins[8] = eng.addBasicObject(0, 2, 100, 10, 0, 8, 56, 'C');
    coins[9] = eng.addBasicObject(0, 2, 100, 10, 0, 20, 47, 'C');
    coins[10] = eng.addBasicObject(0, 2, 100, 10, 0, 4, 70, 'C');
    for(int i = 0; i < coinCount; ++i){
        eng.addAttribute(coins[i], "net gain", -1);
        eng.addAttribute(coins[i], "health", 1);
    }
    eng.addOneWayDamageCollision(2, 0, "coins", "net gain");
    eng.addOneWayDamageCollision(0, 2, "health", "damage");
    
    // Initialize roadblock
    int roadBlockCount = 2;
    vector<int> roadBlocks(roadBlockCount);
    roadBlocks[0] = eng.addRectangleObject(0, 3, 100, 10, 0, 8, 61, 2, 18, 'B');
    roadBlocks[1] = eng.addRectangleObject(0, 3, 100, 10, 0, 10, 61, 2, 18, 'B');
    for(int i = 0; i < 2; ++i){
        eng.addAttribute(roadBlocks[i], "health", 200);
        eng.addAttribute(roadBlocks[i], "damage", 1);
    }
    eng.addStopCollision(0, 3);

    // Initialize bushes (cosmetic)
    int bushCount = 3;
    vector<int> bushes(bushCount);
    bushes[0] = eng.addRectangleObject(0, 4, 200, 10, 0, 10, 3, 3, 3, 'W');
    bushes[1] = eng.addRectangleObject(0, 4, 200, 10, 0, 12, 33, 4, 5, 'W');
    bushes[2] = eng.addRectangleObject(0, 4, 200, 10, 0, 14, 50, 2, 2, 'W');

    // Initialize blaster
    int refRow = 17, refCol = 65;
    int blaster = eng.addBitmapObject(0, 5, 100, 10, 0, vector<tuple<int,int,char>>{
        {refRow, refCol, '^'}, {refRow, refCol+2, '^'}, {refRow+1, refCol+1, '$'},
        {refRow+2, refCol, '#'}, {refRow+2, refCol+1, '#'}, {refRow+2, refCol+2, '#'}});
    vector<vector<tuple<int,int,char>>> cycles;
    vector<pair<int,int>> changes = {{-3, 0}, {0, 8}, {3, 0}, {0, -8}};
    for(int i = 0; i < 4; i++){
        vector<tuple<int,int,char>> cycle{
            {refRow, refCol, '^'}, {refRow, refCol+2, '^'}, {refRow+1, refCol+1, '$'},
            {refRow+2, refCol, '#'}, {refRow+2, refCol+1, '#'}, {refRow+2, refCol+2, '#'}};
        cycles.push_back(cycle);
        refRow += changes[i].first;
        refCol += changes[i].second;
    }
    eng.addCyclicMovement(blaster, 50, cycles);

    // Initialize blaster projectile
    int projectile = eng.addBasicObject(1, 6, 100, 10, 0, 0, 0, '+');
    eng.addStraightMovement(projectile, 5, -1, 0);
    eng.addAttribute(projectile, "damage", 5);
    eng.addAttribute(projectile, "health", 1);
    eng.addOneWayDamageCollision(6, 3, "health", "damage");
    eng.addOneWayDamageCollision(3, 6, "health", "damage");
    eng.addSpawnerCollision(0, 5, vector<int>{projectile}, 1);

    // Add customized status lines
    eng.addGameStatusLine();
    eng.addAttributeStatusLine(player, "coins", "Coins collected: ");
    eng.addTypeCountStatusLine(3, "Uncleared roadblocks: ");

    // Add win/lose conditions
    eng.addTypeCountWinLose(1, vector<pair<int,int>>{{0, 2}});
}

void Client::go(){
    eng.go();
}

Client::~Client(){}
