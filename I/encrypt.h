/*
Name: encrypt.h
Description: co-dependent functions for encryption/decryption program
*/
#pragma once
#include <string>
using namespace std;

// prototypes
unsigned long getSeedFromPassword(string);  // creates seed value from password
unsigned long findNextPrime(int);           // finds next prime number
bool isPrime(unsigned long);                // checks if a number is prime
char encrypt(char, unsigned long);          // encrypts a character
char decrypt(char, unsigned long);          // decrypts a character

/*
* Name:
*   encrypt
* Parameters:
*   chToEncrypt     character that needs to be encrypted
*   key             integer value to add to unencrypted character for encryption
* Description:
*   As above
*/
char encrypt(char chToEncrypt, unsigned long key) {
    return chToEncrypt + static_cast<char>(key);
}


/*
* Name:
*   decrypt
* Parameters:
*   chToDecrypt   character that needs to be decrypted
*   key             integer value that was added to unencrypted character for
*                   encryption
* Descripton:
*   As above
*/
char decrypt(char chToDecrypt, unsigned long key) {
    return chToDecrypt - static_cast<char>(key);
}

/*
* Name:
*   getSeedFromPassword
* Parameters:
*   userPassword    string user entered as the password
* Return:
*   ulong           seed value for encryption/decryption
* Description:
*   Function takes password input parameter, adds up the integer value of each
*   character, then finds the next prime number after that number to use as a
*   seed value
*/
unsigned long getSeedFromPassword(string userPassword) {
    int strLen;
    unsigned long seed = 0;

    // determine string length
    strLen = userPassword.length();

    // add up the integer values of each character in the string
    for (int i = 0; i < strLen; i++) {
        seed += static_cast<int>(userPassword[i]);
    }

    // find the next prime number and return that
    return (findNextPrime(seed));
}

/*
* Name:
*   findNextPrime
* Parameters:
*   start       start point for finding next prime number
* Return:
*   ulong       next prime number found
* Description:
*   Function takes a starting value and finds the next prime number after it
*/
unsigned long findNextPrime(int start) {
    unsigned long nextPrime = 0;

    // if start is even, make it odd
    if (start % 2 == 0) {
        start++;
    }
    // otherwise go to next odd number
    else {
        start += 2;
    }

    // iterate every odd number from start to square of start until prime found
    for (int i = start; i < start * start; i+=2) {
        if (isPrime(i)) {
            nextPrime = i;
            break;
        }
    }

    // return prime found
    return nextPrime;
}

/*
* Name:
*   isPrime
* Parameters:
*   num     number to check if prime
* Return:
*   bool    true if number is prime, false if not
* Description:
*   Function takes a number and checks it against a list of prime numbers
*   If the number is not in the list, it also checks if it is divisible by any
*   numbers in the list. Then iterates from end of list to square root of number
*   checking for composites until it either finds one or finishes iterating
*/
bool isPrime(unsigned long num) {
    // array to hold first 46 prime numbers to speed up algorithm a bit
    const int PRIME_LIST_SIZE = 46;
    int primeList[PRIME_LIST_SIZE] =
    { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
    67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
    149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199 };

    // if less than 2, not prime
    if (num < 2) {
        return false;
    }

    // if in list return true, if divisible by anything in list, return false
    for (int i = 0; i < PRIME_LIST_SIZE; i++) {
        if (num == primeList[i])
            return true;
        else if (num % primeList[i] == 0)
            return false;
    }

    // check for other composits starting with end range of list to root of num
    // return false if a composite is found
    for (int i = primeList[PRIME_LIST_SIZE - 1]; i <= sqrt(num); i += 2) {
        if (num % i == 0)
            return false;
    }

    // if function gets here, number is prime
    return true;
}