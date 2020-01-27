/*******************************************************************************
accounts.h
Stores the functions for handling account files
*******************************************************************************/
#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#pragma once

#include <fstream>
#include "game.h"
#include "User.h"
#include "validate.h"
using namespace std;

const int MAX_NAME = 32;
const int MAX_PASS = 32;
const int MAX_EMAIL = 64;
const int DISP_RANKS = 10;
const string DATABASE_FILE = "userAccounts.bin";
const string HUMAN_RANK_FILE = "rankingsHuman.csv";
const string AI_RANK_FILE = "rankingsAI.csv";

struct Account {                // Account structure for handling account files
    char username[MAX_NAME];
    char password[MAX_PASS];
    char email[MAX_EMAIL];
    int humanWins;
    int humanLosses;
    int humanDraws;
    int cpuWins;
    int cpuLosses;
    int cpuDraws;
    int dbLoc;                  // database location in file for account
    ~Account() {};
};
struct Rank {                 // rank structure for handling rankings
    string name;
    double againstHumanRank; // determined by # of wins * win ratio
    double againstAIRank;
    ~Rank() {};
};

// functions for getting input from user
User getUser(int);
Account getUsername();
Account checkForUsername(char[]);
bool checkCreateNewAccount();
Account createNewAcct(Account);
Account getNewEmail(Account);
Account getNewPassword(Account);
bool getPassword(Account);
bool checkPassword(Account, char[]);
bool checkPassword(char[], char[]);    // overload
bool yesNo();

// account file specific functions
void writeToDatabase(Account);
Account readFromDatabase(int);
void writeUserToDB(User);
long byteNum(int);
long int getNumRecordsInDB();

// rank file specific functions
void updateRanks();
void sortRankList(Rank[], bool);

// debugging
void cleanDatabase();
void writeNewDB();
void printAccount(Account);
User createDummyUser(int);

/*
* Name:
*   getUser
* Parameters:
*   playerNum   player number to create user for
* Return:
*   User    user created from either new creation or from database
* Description:
*   Wrangles functions to get an account from the database for creating a user
*/
User getUser(int playerNum) {
    Account userAcct;
    User userConstructor;
    bool newAcct = false;

    // get user name and check account files for user name
    userAcct = getUsername();

    // if acount not found, make a new account
    if (userAcct.dbLoc <= -1) {
        // construct new user
        newAcct = true;
        if (!checkCreateNewAccount()) {
            return getUser(playerNum);
        }
    }

    if (newAcct) {
        userAcct = createNewAcct(userAcct);
    }

    // if not a new account, get account password
    if (!newAcct) {
        if (!getPassword(userAcct)) {
            return getUser(playerNum);
        }
    }

    // constructs user from account
    // this could have been a lot simpler if I could have figured out what went
    // wrong when I tried to use inheritance
    userConstructor.createHuman(userAcct.username, playerNum, userAcct.humanWins,
        userAcct.humanLosses, userAcct.humanDraws, userAcct.cpuWins,
        userAcct.cpuLosses, userAcct.cpuDraws);

    return userConstructor;
}
/*
* Name:
*   getUserName
* Parameters:
*   none
* Return:
*   Account     Account structure from input, returns blank if none found
* Description:
*   Gets user input for username
*/
Account getUsername() {
    char userIn[MAX_NAME];

    cout << "Please enter your username: ";
    cin.getline(userIn, MAX_NAME);

    string input(userIn);

    if (!regex_username(input)) {
        cout << "\aInvalid Entry: Username must be between 4 and 32 characters"
            << " and cannot contain special characters." << endl;
        return getUsername();
    }

    return checkForUsername(userIn);
}
/*
* Name:
*   checkForUsername
* Parameters:
*   input       input from User
* Return:
*   Account     Account structure with account information if found
* Description:
*   Checks user input against the database for existence of record
*   If record is not found, the input is used to create a new account with that
*   username and sets database location to -1 for correct addition to file
*/
Account checkForUsername(char input[]) {
    // create a temporary account
    Account temp;

    // get size of database
    long int dbSize = getNumRecordsInDB();

    if (dbSize <= 0) {
        for (int i = 0; i < MAX_NAME; i++) {
            temp.username[i] = input[i];
        }
        temp.dbLoc = -1;
        return temp;
    }

    for (int i = 0; i < dbSize; i++) {
        // search records
        temp = readFromDatabase(i);

        // if the user name is found, break search
        if (strcmp(temp.username, input) == 0) {
            break;
        }
        else {
            // set username to entry
            for (int i = 0; i < MAX_NAME; i++) {
                temp.username[i] = input[i];
            }
            temp.dbLoc = -1;
        }
    }

    // return the account constructed
    return temp;
}
/*
* Name:
*   checkCreateNewAccount
* Parameters:
*   none
* Return:
*   true    if yes
* Description:
*   Checks if user wants to create a new account
*/
bool checkCreateNewAccount() {
    cout << "That username was not found. Would you like to create an account?"
        << " (y/n): ";

    return yesNo();
}
/*
* Name:
*   createNewAccount
* Parameters:
*   acct    Account object to use for entry
* Return:
*   New account with user entry
* Description:
*   Creates a new account and wrangles all other new account functions
*/
Account createNewAcct(Account acct) {
    acct.humanWins = 0;
    acct.humanLosses = 0;
    acct.humanDraws = 0;
    acct.cpuWins = 0;
    acct.cpuLosses = 0;
    acct.cpuDraws = 0;
    acct.dbLoc = -1;

    // get password
    acct = getNewPassword(acct);

    // get email
    acct = getNewEmail(acct);

    writeToDatabase(acct);

    // update database location by running a check for the username again
    acct = checkForUsername(acct.username);

    return acct;
}
/*
* Name:
*   getNewEmail
* Parameters:
*   acct    Account structure to get new email for
* Return:
*   Account     structure with new email entry
* Description:
*   Gets an email from a user for new account creation
*/
Account getNewEmail(Account acct) {
    string userInput;

    cout << "Please enter your email address: ";
    getline(cin, userInput);

    if (!regex_email(userInput) || (userInput.length() > MAX_EMAIL)) {
        cout << "\aInvalid email." << endl;
        return getNewEmail(acct);
    }

    for (unsigned int i = 0; i < userInput.length(); i++) {
        acct.email[i] = userInput[i];
    }

    return acct;
}
/*
* Name:
*   getNewPassword
* Parameters:
*   acct    Account structure of new account
* Return:
*   Account structure with password input
* Description:
*   Gets a password from the user for a new Account
*   Asks for entry twice and verifies both inputs are the same
*/
Account getNewPassword(Account acct) {
    char firstIn[MAX_PASS];
    char secondIn[MAX_PASS];

    cout << "Please enter a password for the new account: ";
    cin.getline(firstIn, MAX_PASS);

    string input(firstIn);

    if (!regex_password(input)) {
        cout << "\aInvalid Entry. Passwords must be between 4 and 32"
            << " characters and contain at least 1 number." << endl;
        return getNewPassword(acct);
    }

    cout << "Re-enter the password to confirm: ";
    cin.getline(secondIn, MAX_PASS);

    if (!checkPassword(firstIn, secondIn)) {
        cout << "\aThose entries do not match!" << endl;
        return getNewPassword(acct);
    }

    for (int i = 0; i < MAX_PASS; i++) {
        acct.password[i] = firstIn[i];
    }

    return acct;
}
/*
* Name:
*   getPassword
* Parameters:
*   acct        Account user is trying to login to
* Return:
*   true        if good password entered
* Description:
*   Gets password entry from user and checks for validity
*/
bool getPassword(Account acct) {
    char secondIn[MAX_PASS];

    cout << "Please enter the password: ";
    cin.getline(secondIn, MAX_PASS);

    // check entry against account file password
    if (checkPassword(acct, secondIn)) {
        return true;
    }
    else {
        cout << "\aIncorrect password!" << endl;
    }

    // if function gets here, bad password
    return false;
}
/*
* Name:
*   checkPassword
* Parameters:
*   acct    Account to check against
*   input   string input from user
* Return:
*   true     if account password and entry are the same
* Description:
*   Compares Account password with input from user
*/
bool checkPassword(Account acct, char input[]) {
    return (strcmp(acct.password, input) == 0);
}
/*
* Name:
*   checkPassword (OVERLOAD)
* Parameters:
*   in1     c-string 1 to compare
*   in2     c-string 2 to compare
* Return:
*   true    if both strings are the same
* Description:
*   Compares strings for new password entry to verify both entries are the same
*/
bool checkPassword(char in1[], char in2[]) {
    return (strcmp(in1, in2) == 0);
}
/*
* Name:
*   yesNo
* Parameters:
*   none
* Return:
*   true    if yes
* Description:
*   Gets Y/N input from user and validates
*/
bool yesNo() {
    string input;
    getline(cin, input);
    if (!regex_yn(input)) {
        cout << "\aInvalid input. Please enter only 'y' or 'n': ";
        return yesNo();
    }

    return input == "Y" || input == "y";
}
/*******************************************************************************
                          Account file specific functions
*******************************************************************************/
/*
* Name:
*   writeToDatabase
* Parameters:
*   writeAccount    Account to write to database
* Return:
*   none
* Description:
*   Writes an Account structure to the DB file. Updates DB location of the acct
*   structure
*/
void writeToDatabase(Account writeAccount) {
    fstream database(DATABASE_FILE, ios::out | ios::in | ios::binary);

    // if the database location for the account is -1, append to end of file
    if (writeAccount.dbLoc != -1) {
        database.clear();
        database.seekp(byteNum(writeAccount.dbLoc), ios::beg);
    }
    // else, go to the record in the file and overwrite it
    else {
        database.seekp(0, ios::end);
        // change the DB location of the Account before writing to the position
        // this is mostly used to make sure new Accounts get correct DB loc
        writeAccount.dbLoc = (long)database.tellp() / byteNum(1);
    }

    database.write(reinterpret_cast<char *>(&writeAccount), sizeof(writeAccount));

    database.close();
}
/*
* Name:
*   readFromDatabase
* Parameters:
*   loc         Location value of Account to get
* Return:
*   Account     Account structure read from db file
* Description:
*   Reads an account structure from the database file and returns it
*/
Account readFromDatabase(int loc) {
    fstream database(DATABASE_FILE, ios::in | ios::binary);
    Account readAccount;

    database.seekg(byteNum(loc), ios::beg);
    database.read(reinterpret_cast<char *>(&readAccount), sizeof(readAccount));

    database.close();

    return readAccount;
}
/*
* Name:
*   writeUserToDB
* Parameters:
*   userObj     User object with updated values that should be written to DB
* Return:
*   none
* Description:
*   Updates statistics from a finished game to the corresponding account file
*/
void writeUserToDB(User userObj) {
    string tempName = userObj.getName();
    char charTempName[MAX_NAME];

    for (int i = 0; i < tempName.length(); i++) {
        charTempName[i] = tempName[i];
    }

    // null terminate the rest of the user name or problems arise
    for (int i = tempName.length(); i < MAX_NAME; i++) {
        charTempName[i] = '\0';
    }

    // check to make sure the account exists and goes to the right DB location
    Account tempAcct = checkForUsername(charTempName);

    // update statistics
    tempAcct.humanWins = userObj.getWins(true);
    tempAcct.humanLosses = userObj.getLoss(true);
    tempAcct.humanDraws = userObj.getDraw(true);
    tempAcct.cpuWins = userObj.getWins(false);
    tempAcct.cpuLosses = userObj.getLoss(false);
    tempAcct.cpuDraws = userObj.getDraw(false);

    // write Account to file with updated statistics
    writeToDatabase(tempAcct);
}
/*
* Name:
*   byteNum
* Parameters:
*   recNum  record number to get
* Return:
*   long    Returns the start byte value for a record
* Description:
*   Takes a record number and multiplies by size of Account
*/
long byteNum(int recNum) {
    return sizeof(Account) * recNum;
}
/*
* Name:
*   Calcs the number of records in the database file
* Parameters:
*   none
* Return:
*   long int    number of records in db file
* Description:
*   Returns number of Accounts in the database file
*/
long int getNumRecordsInDB() {
    long int totalRecords;
    fstream database(DATABASE_FILE, ios::in | ios::binary);

    // go to the end of the database
    database.seekg(0, ios::end);

    // number of records = end position of (database / size of 1 record)
    totalRecords = (long)database.tellg();
    totalRecords /= byteNum(1);

    // close the file
    database.close();

    // return the number of records
    return totalRecords;
}
/*******************************************************************************
                        Rank file specific functions
*******************************************************************************/
/*
* Name:
*   updateRanks
* Parameters:
*   none
* Return:
*   none
* Description:
*   Updates the rank file list files by first deleting them
*   Then works through Account file and determines score
*   If the score determined is higher than any of the others already in the list
*   This is added to the bottom of the list
*   The list is then sorted
*/
void updateRanks() {
    // open the rank files for output
    fstream humanRankFile(HUMAN_RANK_FILE, ios::out);
    fstream aiRankFile(AI_RANK_FILE, ios::out);

    // create temporary Account and Rank for storing information read
    Account tempAccount;
    Rank tempRank;

    double tempWins;
    double tempLosses;
    double tempDraws;
    double tempTotalGames;
    double tempWinRatio;

    // create an array of ranks for temp storage before writing and init empty
    Rank top10Human[DISP_RANKS];
    Rank top10AI[DISP_RANKS];

    for (int i = 0; i < DISP_RANKS; i++) {
        top10Human[i] = { "",0,0 };
        top10AI[i] = { "",0,0 };
    }

    // get the number of records in the database
    long int numRecords = getNumRecordsInDB();

    // build the rankings
    for (int i = 0; i < numRecords; i++) {
        tempAccount = readFromDatabase(i);
        tempRank.name = tempAccount.username;

        // determine the rank value for human plays
        tempWins = (double)tempAccount.humanWins;
        tempLosses = (double)tempAccount.humanLosses;
        tempDraws = (double)tempAccount.humanDraws;
        tempTotalGames = tempWins + tempLosses + tempDraws;
        tempWinRatio = tempWins / tempTotalGames;
        // rank value = wins * win ratio
        tempRank.againstHumanRank = tempWins * tempWinRatio;

        // determine the rank value for computer plays
        tempWins = (double)tempAccount.cpuWins;
        tempLosses = (double)tempAccount.cpuLosses;
        tempDraws = (double)tempAccount.cpuDraws;
        tempTotalGames = tempWins + tempLosses + tempDraws;
        tempWinRatio = tempWins / tempTotalGames;
        // rank value = wins * win ratio
        tempRank.againstAIRank = tempWins * tempWinRatio;


        // determine if the temporary value read in is higher than any in list
        // and put it at the bottom of the list if so
        for (int rankPos = 0; rankPos < DISP_RANKS; rankPos++) {
            if (tempRank.againstHumanRank > top10Human[rankPos].againstHumanRank) {
                top10Human[DISP_RANKS - 1] = tempRank;
                break;
            }
        }

        for (int rankPos = 0; rankPos < DISP_RANKS; rankPos++) {
            if (tempRank.againstAIRank > top10AI[rankPos].againstAIRank) {
                top10AI[DISP_RANKS - 1] = tempRank;
                break;
            }
        }

        // sort the lists
        sortRankList(top10Human, true);
        sortRankList(top10AI, false);
    }

    // write the list to the file
    for (int i = 0; i < DISP_RANKS; i++) {
        humanRankFile << i + 1 << ",";
        humanRankFile << top10Human[i].name << ",";
        humanRankFile << top10Human[i].againstHumanRank << endl;
        aiRankFile << i + 1 << ",";
        aiRankFile << top10AI[i].name << ",";
        aiRankFile << top10AI[i].againstAIRank << endl;
    }

    // close file and end function
    humanRankFile.close();
    aiRankFile.close();
}
/*
* Name:
*   sortRankList
* Parameters:
*   human   if human true, sort human rank list, else sort ai rank list
* Return:
*   sorted list
* Description:
*   Bubble sort for Rank structure list
*/
void sortRankList(Rank list[], bool human) {
    int tempIndex;
    Rank tempRank;
    if (human) {
        for (int i = 0; i < DISP_RANKS - 1; i++) {
            tempIndex = i;
            tempRank = list[i];

            for (int j = i + 1; j < DISP_RANKS; j++) {
                if (list[j].againstHumanRank > tempRank.againstHumanRank) {
                    tempRank = list[j];
                    tempIndex = j;
                }
            }

            list[tempIndex] = list[i];
            list[i] = tempRank;
        }
    }
    else {
        for (int i = 0; i < DISP_RANKS - 1; i++) {
            tempIndex = i;
            tempRank = list[i];

            for (int j = i + 1; j < DISP_RANKS; j++) {
                if (list[j].againstAIRank > tempRank.againstAIRank) {
                    tempRank = list[j];
                    tempIndex = j;
                }
            }

            list[tempIndex] = list[i];
            list[i] = tempRank;
        }
    }
}
/*******************************************************************************
                            DEBUGGING FUNCTIONS
*******************************************************************************/
/*
* Name:
*   cleanDatabase
* Parameters:
*   none
* Return:
*   none
* Description:
*   deletes existing account database file
*/
void cleanDatabase() {
    fstream record("userAccounts.bin", ios::out | ios::binary);

    record.close();
}
/*
* Name:
*   writeNewDB
* Parameters:
*   none
* Return:
*   none
* Description:
*   Deletes existing account database file and populates a new one with fluff
*/
void writeNewDB() {
    cleanDatabase();

    Account writeRecords[14]{
        {"sgerkin","sgerkin","stephen.gerkin@gmail.com",100,0,0,100,0,0,0},
        {"veronicat","veronicat","imacat@catcatcat.cat",47,39,2,34,5,0,1},
        {"booturnip","booturnip","inedible@yahoo.com",87,59,5,69,32,5,2},
        {"edgarmoose","edgarmoose","edgarmoose@fakemail.com",4,22,5,39,29,19,3},
        {"harleygadabouts","harleygadabouts","harley@gatabouts.com",0,5,0,0,3,0,4},
        {"maxjiggle","maxjiggle","maxjiggle@maxwiggle.edu",33,43,59,19,20,0,5},
        {"romeoskedaddle","romeoskedaddle","romeo@skedaddle.org",12,12,12,12,12,12,6},
        {"buddyquagga","buddyquagga","buddy@quagga.net",6,4,10,8,9,10,7},
        {"roquefort","roquefort","roque@fort.de",1,2,3,4,5,6,8},
        {"murphy","murphy","murphy@rhubarb.ru",0,0,0,0,0,0,9},
        {"elliot","elliot","f.society@e-corp.com",15,0,2,15,0,2,10},
        {"muphasa","muphasa","oooohmuphasha@lionking.dis",2,4,6,8,10,12,11},
        {"test1","test1","test1@position12.com",0,0,0,0,0,0,12},
        {"test2","test2","test2@position13.com",0,0,0,0,0,0,13}
    };


    for (int i = 0; i < 14; i++) {
        writeToDatabase(writeRecords[i]);
    }
}
/*
* Name:
*   printAccount
* Parameters:
*   acct    Account to print
* Return:
*   none
* Description:
*   prints Account structure to screen for debugging
*/
void printAccount(Account acct) {
    cout << "Username: " << acct.username << endl
        << "Password: " << acct.password << endl
        << "Email: " << acct.email << endl
        << "Wins: " << acct.humanWins << endl
        << "Losses: " << acct.humanLosses << endl
        << "Draws: " << acct.humanDraws << endl
        << "DB LOC: " << acct.dbLoc << endl << endl;
    system("pause");
}
/*
* Name:
*   createDummyUser
* Parameters:
*   num     player number to use
* Return:
*   User    dummy user
* Description:
*   creates a dummy user for testing
*/
User createDummyUser(int num) {
    User dummy;
    char name[3]{ 'd', '0' + num, '\0' };

    dummy.createHuman(name, num, 0, 0, 0, 0, 0, 0);
    return dummy;
}

#endif // !ACCOUNTS_H