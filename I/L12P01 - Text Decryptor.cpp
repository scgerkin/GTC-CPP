/*
Name: Stephen Gerkin
Date: 03/27/2019
Lesson 12 Program (DECRYPTION)
Program Title:
    Text Decryptor
Program Description:
    This is the companion program to the encryption program.

    It finds the key with the same method as the encryption program then
    subtracts the key from each individual character before writing to file
*/

#include <fstream>
#include <iostream>
#include "encrypt.h"
using namespace std;

// globals for file names
string IN_FILE = "encryptedFile.dat";
string OUT_FILE = "unencryptedFile.txt";

// prototypes
void dispStartMsg();        // displays start msg
void errorOpeningFile();    // displays error if file not found, exits program
string getPassword();       // gets password from user
void dispEndMsg();          // displays end msg

/*
* Main function body for decrypting a file
*/
int main() {
    unsigned long userSeed = 0;
    unsigned long fileSeed = 0;
    unsigned long key;
    string password;
    char temp;

    // entrance msg
    dispStartMsg();

    // open file for input
    fstream fileToDecrypt(IN_FILE, ios::in | ios::binary);

    // make sure file exists
    if (fileToDecrypt.fail()) {
        errorOpeningFile();
    }

    // get password
    password = getPassword();

    // find seed value for password
    userSeed = getSeedFromPassword(password);

    // get file seed
    fileSeed = findNextPrime(sizeof(fileToDecrypt));

    // set key
    key = userSeed * fileSeed;

    // open file for output
    fstream unencryptedFile(OUT_FILE, ios::out);


    cout << "If incorrect password entered, file will not be decrypted properly."
        << endl << endl;


    cout << "Decrypting file...";

    // read file in, decrypt by character, and write to file
    while (fileToDecrypt) {
        fileToDecrypt.get(temp);

        if (!fileToDecrypt.eof()) {
            temp = decrypt(temp, key);
            unencryptedFile.write(reinterpret_cast<char *>(&temp), sizeof(temp));
        }
    }

    // close files
    fileToDecrypt.close();
    unencryptedFile.close();

    // exit msg
    dispEndMsg();

    // terminate
    system("pause");
    return 0;
}

/*
* Name:
*   dispStartMsg()
* Parameters:
*   none
* Return:
*   none
* Description:
*   Starting message for program, explains how the program will work
*/
void dispStartMsg() {
    cout << "Welcome to the File Decryption Program!" << endl
        << "This program will decrypt your file if you provide the correct "
        << "password." << endl << endl;
}

/*
* Name:
*   errorOpeningFile
* Parameters:
*   none
* Return:
*   none
* Description:
*   Displays error message and exits program if file to be decrypted not found
*/
void errorOpeningFile() {
    cout << "The file \"" << IN_FILE << "\" was not found." << endl
        << "Please exit the program and make sure the file is in the "
        << "correct folder." << endl << endl;

    system("pause");
    exit(0);
}

/*
* Name:
*   getPassword
* Parameters:
*   none
* Return:
*   string      user input for password as string
* Description:
*   Gets password from user
*/
string getPassword() {
    string input;

    cout << "Enter your password: ";
    getline(cin, input);
    cout << endl;

    return input;
}

/*
* Name:
*   dispEndMsg
* Parameters:
*   none
* Return:
*   none
* Description:
*   Displays exit message and name of decrypted file
*/
void dispEndMsg() {
    cout << "Decryption complete!" << endl
        << "The file has been decrypted using your password and saved to: "
        << OUT_FILE << endl
        << "If the file is a bunch of gibberish, you did not enter the correct "
        << "password!" << endl << endl;
}
