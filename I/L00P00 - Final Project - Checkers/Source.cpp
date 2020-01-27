/*
Name: Stephen Gerkin
Date: 04/09/19
Final Project
Program Title:
    Checkers for C++
Program Description:
    This program is a Checkers game. It allows creation of user accounts and can
    track statistics over multiple plays. It allows a user to play against the
    computer or against another human opponent.

    I learned a great deal putting all of this together. Things that I thought
    would be complicated before starting ended up being simple and things I
    thought would be simple ended up extremely complicated. I also learned the
    value and importance of properly planning and designing a program before
    starting. If I had to do it all over again, I would write this completely
    differently; however, I am proud of the work here.

    While the code itself may not be the best I could have created, the lessons
    learned while spending hours (HOURS!) debugging things I previously thought
    were working just fine was an invaluable lesson in patience and methodical
    thinking. I also have a much better idea of what all is involved in creating
    a project of this magnitude and can apply it to future projects. Perhaps
    most importantly, I learned the value of version control. I've put off
    learning Git because I have not really needed to use it for projects in the
    past. After trying to add a new thing to the program and basically breaking
    literally everything all at once and not knowing what caused the problem,
    I will never forget to push periodic commits to my personal repo ever again.

    This was definitely a humbling experience.
*/
#include <iomanip>
#include "accounts.h"

const int SELECTIONS = 6;           // constant for menu selections

//prototypes
void printWelcome();
int getMenuSelection();
void printRanks(bool);
void printInstructions();
void printInstructionHeader();
void printSmallBoard(Tile[][MAX_COLS]);
bool playAgain();
void printExit();
/*
* Name:
*   main
* Parameters:
*   none
* Return:
*   none
* Description:
*   Main function body. Starts program and welcomes user to the program.
*   Handles menu selections and starts the actual game
*/
int main() {
    // make sure rank file is up to date
    updateRanks();

    // declare User objects for 2 players
    User players[2];
    int menuSelection;

    printWelcome();

    // get user 1 info
    players[0] = getUser(1);

    cout << endl << endl << "Welcome " << players[0].getName() << "!" << endl;

    // menu selection decisions
    do {
        menuSelection = getMenuSelection();

        switch (menuSelection) {
        case 1: // print human ranks
            printRanks(true);
            break;
        case 2: // print cpu ranks
            printRanks(false);
            break;
        case 3: // start game with human opponent
            cout << "Getting player 2 info...";
            players[1] = getUser(2);
            do {
                playTheGame(players);
                writeUserToDB(players[0]);  // update account file with stats
                writeUserToDB(players[1]);  // for players
                updateRanks();              // update rank file
            } while (playAgain());          // loop while play again = yes
            break;
        case 4: // start game with cpu opponent
            players[1].createAI(2);
            do {
                playTheGame(players);
                writeUserToDB(players[0]);
                updateRanks();
            } while (playAgain());
            break;
        case 5: // print instructions
            printInstructions();
            break;
        case 6: // quit
            printExit();
            break;
        }
    } while (menuSelection != 6);

    return 0;
}
/*
* Name:
*   printWelcome
* Parameters:
*   none
* Return:
*   none
* Description:
*   Prints welcome msg
*/
void printWelcome() {
    int dispWidth = 50;

    for (int i = 0; i < dispWidth; i++) {
        cout << "*";
    }

    cout << endl << "*"
        << centerOutput(dispWidth - 2, "WELCOME TO CHECKERS FOR C++")
        << "*" << endl << "*"
        << centerOutput(dispWidth - 2, "Created by: Stephen Gerkin")
        << "*" << endl;

    for (int i = 0; i < dispWidth; i++) {
        cout << "*";
    }
    cout << endl << endl;
}
/*
* Name:
*   getMenuSelection
* Parameters:
*   none
* Return:
*   int     menu selection as integer
* Description:
*   Displays menu items to user and gets selection
*/
int getMenuSelection() {
    string input;

    cout << endl << endl << "Please make a selection: " << endl
        << "1. View current rankings against other humans" << endl
        << "2. View current rankings against the computer" << endl
        << "3. Play against another person" << endl
        << "4. Play against the computer" << endl
        << "5. View instructions on how to play the game" << endl
        << "6. Exit" << endl
        << endl
        << "Make a selection: ";

    getline(cin, input);

    if (!regex_u_int(input) || stoi(input) > SELECTIONS) {
        cout << "\aInvalid Selection" << endl;
        return getMenuSelection();
    }

    return stoi(input);
}
/*
* Name:
*   printRanks
* Parameters:
*   human       boolean flag to print human ranks
* Return:
*   none
* Description:
*   Prints top 10 lists to screen.
*   Prints Vs. Human if human is true
*   Prints AI ranks if human is false
*/
void printRanks(bool human) {
    system("cls");
    fstream rankFile;
    string humanOrAI;
    string pos;
    string name;
    string rankVal;
    int dispWidth = 50;

    if (human) {
        rankFile.open(HUMAN_RANK_FILE, ios::in);
        humanOrAI = "(vs. Humans)";
    }
    else {
        rankFile.open(AI_RANK_FILE, ios::in);
        humanOrAI = "(vs. Computer)";
    }

    for (int i = 0; i < dispWidth; i++) {
        cout << "*";
    }
    cout << endl;

    cout << centerOutput(dispWidth, "CURRENT RANKINGS") << endl;

    cout << centerOutput(dispWidth, humanOrAI) << endl;


    for (int i = 0; i < dispWidth; i++) {
        cout << "*";
    }
    cout << endl << centerOutput((dispWidth - 5), "NAME") << "SCORE" << endl;

    for (int i = 0; i < DISP_RANKS; i++) {
        getline(rankFile, pos, ',');
        getline(rankFile, name, ',');
        getline(rankFile, rankVal, '\n');

        cout << setw(2) << right << pos << ". " << setw(40) << left << name
            << " " << fixed << setprecision(1) << stod(rankVal) << endl;
    }

    rankFile.close();
}
/*
* Name:
*   printInstructions
* Parameters:
*   none
* Return:
*   none
* Description:
*   Prints instructions for user on how to play game
*/
void printInstructions() {

    Tile demo[MAX_ROWS][MAX_COLS];
    initBoard(demo);
    makeBlankBoard(demo);
    string outMsg;

    int dispWidth = 70;
    system("cls");

    printInstructionHeader();

    outMsg = "At the beginning of the game";

    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "The screen will display a regular checker board pattern";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "Like this ...";
    cout << centerOutput(dispWidth, outMsg) << endl << endl;

    printSmallBoard(demo);

    cout << endl << endl;

    system("pause");
    system("cls");
    printInstructionHeader();

    outMsg = "On the board will be player Pawns.";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "The piece at the top left is an example of Player 1's Pawn.";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "The piece at the bottom right is an example of Player 2's Pawn";
    cout << centerOutput(dispWidth, outMsg) << endl << endl;

    demo[0][0].makePawn(1);
    demo[2][2].makePawn(2);

    printSmallBoard(demo);

    cout << endl << endl;

    system("pause");
    system("cls");
    printInstructionHeader();

    outMsg = "The game will ask you to enter coordinates for a starting point.";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "You can enter 'A1' or '1A' to select Player 1's Pawn";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "It will then ask you for target coordinates.";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "Enter those the same way (B2 is where we're going to move next)";
    cout << centerOutput(dispWidth, outMsg) << endl;

    demo[0][0].makeEmpty();
    demo[1][1].makePawn(1);
    printSmallBoard(demo);

    system("pause");
    system("cls");
    printInstructionHeader();

    outMsg = "A valid move is diagonal and only one square at a time...";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "Unless you're jumping another player's piece like Player 2 here.";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "If you have a jump available, you have to take it!";
    cout << centerOutput(dispWidth, outMsg) << endl;

    demo[0][0].makePawn(2);
    demo[1][1].makeEmpty();
    demo[2][2].makeEmpty();
    printSmallBoard(demo);

    system("pause");
    system("cls");
    printInstructionHeader();

    outMsg = "When you reach the other player's starting row, your piece";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "will become a king. The piece in A1 is a Player 2 King!";
    cout << centerOutput(dispWidth, outMsg) << endl;

    demo[0][0].makeKing(2);
    printSmallBoard(demo);

    system("pause");
    system("cls");
    printInstructionHeader();

    outMsg = "Here's a Player 1 king piece in the center for reference.";
    cout << centerOutput(dispWidth, outMsg) << endl;

    demo[0][0].makeEmpty();
    demo[1][1].makeKing(1);
    printSmallBoard(demo);

    system("pause");
    system("cls");
    printInstructionHeader();

    outMsg = "The game is played until either:";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "1. One player has no more pieces left on the board.";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "2. The current player has no moves available to make.";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "3. No jumps have been made in 40 turns.";
    cout << centerOutput(dispWidth, outMsg) << endl;
    cout << endl << endl << endl;

    outMsg = "That covers everything!";
    cout << centerOutput(dispWidth, outMsg) << endl;
    outMsg = "HAVE FUN!!!";
    cout << centerOutput(dispWidth, outMsg) << endl;

    system("pause");
    system("cls");
}
/*
* Name:
*   printInstructionHeader
* Parameters:
*   none
* Return:
*   none
* Description:
*   Prints instruction header for instructions display
*/
void printInstructionHeader() {
    int dispWidth = 70;
    for (int i = 0; i < dispWidth; i++) {
        cout << "*";
    }
    cout << endl;

    cout << centerOutput(dispWidth, "INSTRUCTIONS") << endl;

    for (int i = 0; i < dispWidth; i++) {
        cout << "*";
    }
    cout << endl;
}
/*
* Name:
*   printSmallBoard
* Parameters:
*   Array of Tiles for a sample board
* Return:
*   none
* Description:
*   Prints small checkerboard for instruction sample
*/
void printSmallBoard(Tile demo[][MAX_COLS]) {
    char colLetter = 'A';

    cout << endl;
    cout << "  ";

    // print top col letter display
    for (int i = 1; i < 13; i++) {
        if (i % 4 == 0) {
            cout << colLetter;
            colLetter++;
        }
        else {
            cout << " ";
        }
    }

    cout << endl << "   ";

    // print row seperator
    for (int i = 0; i <= 12; i++) {
        if (i % 4 == 0) {
            cout << "+";
        }
        else {
            cout << "-";
        }
    }

    cout << endl;

    // print the board 
    for (int big_row = 0; big_row < 3; big_row++) {
        for (int small_row = 0; small_row < DISP_ROW; small_row++) {

            cout << " ";
            // print row number in middle of entire row
            if (small_row == 1) {
                cout << big_row + 1;
                cout << " ";
            }
            else {
                cout << "  ";
            }

            // print column separator
            cout << "|";

            // print each column display
            for (int big_col = 0; big_col < 3; big_col++) {
                for (int small_col = 0; small_col < DISP_COL; small_col++) {
                    cout << demo[big_row][big_col].dispTile(small_row, small_col);
                }// end display col

                // print a separator at the end of each column
                cout << "|";
            }// end full col

            // print number row number display 
            if (small_row == 1) {
                cout << " ";
                cout << big_row + 1;
            }
            cout << endl;
        }// end small row

        cout << "   ";

        // print row sepearator
        for (int i = 0; i <= (3)*(DISP_ROW + 1); i++) {
            if (i % 4 == 0) {
                cout << "+";
            }
            else {
                cout << "-";
            }
        }
        cout << "  ";
        cout << endl;
    }// end board

    // print bottom col letter display
    cout << "  ";
    colLetter = 'A';
    for (int i = 1; i < (3 + 1)*(DISP_ROW + 1); i++) {
        if (i % 4 == 0) {
            cout << colLetter;
            colLetter++;
        }
        else {
            cout << " ";
        }
    }
    cout << endl << endl;
}
/*
* Name:
*   playAgain
* Parameters:
*   none
* Return:
*   boolean true = yes, false = no
* Description:
*   Checks if user wants to play again
*   Returns true if yes
*/
bool playAgain() {
    cout << "Do you want to play again? (y/n): ";

    return yesNo();
}
/*
    
*/
/*
* Name:
*   printExit
* Parameters:
*   none
* Return:
*   none
* Description:
*   Prints exit message before termination
*/
void printExit() {
    system("cls");
    int dispWidth = 70;

    for (int i = 0; i < dispWidth; i++) {
        cout << "*";
    }

    cout << endl;

    cout << centerOutput(dispWidth, "Thanks for playing!") << endl << endl;

    cout << centerOutput(dispWidth, "I hope you enjoyed it!") << endl << endl;

    for (int i = 0; i < dispWidth; i++) {
        cout << "*";
    }

    cout << endl << endl;

    system("pause");
}