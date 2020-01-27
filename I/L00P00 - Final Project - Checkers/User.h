#ifndef USER_H
#define USER_H
#pragma once
#include <string>
#include <iostream>

/*Note: A lot of this is redundant with Account struct because I had a lot of
  issues getting updating stats to work with file writing while using
  inheritance so I decided to just be redundant
*/
class User
{
private:
    std::string name;       // for user name
    int playerNumber;       // for player number
    int humanWins;          // for number of wins vs human
    int humanLosses;        // for number of losses vs human
    int humanDraws;         // for number of draws vs human
    int userCPUWins;        // for number wins vs computer
    int userCPULoss;        // for number losses vs computer
    int userCPUDraw;        // for number draws vs computer
    bool computerPlayer;    // boolean flag for AI

public:
    void createHuman(char[], int, int, int, int, int, int, int); // create user

    void createAI(int);     // creates an AI user
    bool isAI();            // returns true if user is AI
    std::string getName();  // returns user name
    int getNum();       // returns player number for user
    int getWins(bool);  // returns number of wins for user      T: Human F: AI
    int getLoss(bool);  // returns number of losses for user    T: Human F: AI
    int getDraw(bool);  // returns number of draws for user     T: Human F: AI
    void addWin(bool);  // adds wins for user                   T: Human F: AI
    void addLoss(bool); // adds losses for user                 T: Human F: AI
    void addDraw(bool); // adds draws for user                  T: Human F: AI
    
    User(const User&);  // copy constructor
    User();             // default empty constructor
    ~User();            // destructor
private:
    //debugging
    void printUser();
};

#endif // !USER_H