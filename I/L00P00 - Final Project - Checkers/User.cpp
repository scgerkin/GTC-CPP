#include "User.h"

// See header for full information of class methods

// mutator to create a human user
void User::createHuman(char cName[], int playerNum, int numWin, int numLoss, int numDraw, int CPUWIN, int CPULOSS, int CPUDRAW) {
    name = cName;
    playerNumber = playerNum;
    humanWins = numWin;
    humanLosses = numLoss;
    humanDraws = numDraw;
    userCPUWins = CPUWIN;
    userCPULoss = CPULOSS;
    userCPUDraw = CPUDRAW;
    computerPlayer = false;
}
// mutator to create AI user
void User::createAI(int playerNum) {
    name = "Computer";
    playerNumber = playerNum;
    humanWins = 0;
    humanLosses = 0;
    humanDraws = 0;
    computerPlayer = true;
}

bool User::isAI() {
    return computerPlayer;
}

std::string User::getName() {
    return name;
}

int User::getNum() {
    return playerNumber;
}

int User::getWins(bool human) {
    if (human)
        return humanWins;
    else
        return userCPUWins;
}

int User::getLoss(bool human) {
    if (human)
        return humanLosses;
    else
        return userCPULoss;
}

int User::getDraw(bool human) {
    if (human)
        return humanDraws;
    else
        return userCPUDraw;
}

void User::addWin(bool human) {
    if (human)
        humanWins++;
    else
        userCPUWins++;
}

void User::addLoss(bool human) {
    if (human)
        humanLosses++;
    else
        userCPULoss++;
}

void User::addDraw(bool human) {
    if (human)
        humanDraws++;
    else
        userCPUDraw++;
}

// copy constructor
User::User(const User &obj) {
    name = obj.name;
    playerNumber = obj.playerNumber;
    humanWins = obj.humanWins;
    humanLosses = obj.humanLosses;
    humanDraws = obj.humanDraws;
    userCPUWins = obj.userCPUWins;
    userCPULoss = obj.userCPULoss;
    userCPUDraw = obj.userCPUDraw;
    computerPlayer = obj.computerPlayer;

}


// default empty constructor not used
User::User()
{
}
User::~User()
{
    
}

// debugging method to print user information
void User::printUser() {
    std::cout
        << "Name: " << name << std::endl
        << "Player #: " << playerNumber << std::endl
        << "Wins: " << humanWins << std::endl
        << "Losses: " << humanLosses << std::endl
        << "Draws: " << humanLosses << std::endl
        << "AI: " << computerPlayer << std::endl << std::endl;
}