/*
Name: Stephen Gerkin
Date: 03/27/2019
Lesson 12 Program (ENCRYPTION)
Program Title:
    Text Encryptor
Program Description:
    This program takes a file and encrypts it
    It performs encryption by getting a password from the user
    The integer values of each character in the string entered by the user are
    then added up and the program finds the next prime number following that
    This is the first seed used for creating a key

    The program then finds the size of the file, finds the next prime number
    following that, and uses it as the second seed

    The key is created by multiplying the two seeds together

    The program then adds the value of the key to each character of the plain
    text file and writes each character to an output file

    The decryption requires the uses of the same password entered during runtime
    of the encryption program

    The common functions between the program are stored in the encrypt.h header
    file
*/

#include <fstream>
#include <iostream>
#include "encrypt.h"
using namespace std;

// globals for file names
string IN_FILE = "plainText.txt";
string OUT_FILE = "encryptedFile.dat";

// prototypes
void dispStartMsg();        // displays start msg
void errorOpeningFile();    // displays error if file not found, exits program
string getPassword();       // gets password from user
void dispEndMsg();          // displays end msg

/*
* Main function body for encrypting a file
*/
int main() {
    // vars for encrypting the file
    unsigned long userSeed = 0;
    unsigned long fileSeed = 0;
    unsigned long key;
    
    string password;    // var for user password to be used encrypting
    char temp;          // temp var for characters to be read/written

    // start msg
    dispStartMsg();
          
    // open file for input
    fstream fileToEncrypt(IN_FILE, ios::in);
    
    // make sure file exists
    if (fileToEncrypt.fail()) {
        errorOpeningFile();
    }

    // get password
    password = getPassword();

    // find seed value for password
    userSeed = getSeedFromPassword(password);

    // get file seed
    fileSeed = findNextPrime(sizeof(fileToEncrypt));

    // set key
    key = userSeed * fileSeed;

    // open file for output
    fstream encryptedFile(OUT_FILE, ios::out);

    cout << "Encrypting file...";

    // read file in, encrypt by character, and write to file
    while (fileToEncrypt) {
        fileToEncrypt.get(temp);

        if (!fileToEncrypt.eof()) {
            temp = encrypt(temp, key);
            encryptedFile.write(reinterpret_cast<char *>(&temp), sizeof(temp));
        }
    }

    // close files
    fileToEncrypt.close();
    encryptedFile.close();
        
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
*   Starting message for program, explains how the program will work and
*   displays file names for the program.
*/
void dispStartMsg() {
    cout << "Welcome to the File Encryption Program!" << endl
        << "This program will encrypt the file named: " << IN_FILE << endl
        << "Make sure you remember your password! You will need it for "
        << "decryption!" << endl << endl;
}

/*
* Name:
*   errorOpeningFile
* Parameters:
*   none
* Return:
*   none
* Description:
*   Displays error message and exits program if file to be encrypted not found
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

    cout << "Enter a password to use for encrypting and decrypting your file: ";
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
*   Displays exit message and name of encrypted file
*/
void dispEndMsg() {
    cout << "Encryption complete!" << endl
        << "The file has been saved to: " << OUT_FILE << endl
        << "Run the decryption program on the file using the password you "
        << "entered to decrypt the file." << endl << endl;
}