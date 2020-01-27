/*******************************************************************************
game.h
Stores the functions for handling game functions
*******************************************************************************/
#include <cstdlib>      // for getting random #
#include <ctime>        // for seeding random
#include <thread>       // for AI "think" display
#include <chrono>       // for AI "think" display
#include "validate.h"
#include "Tile.h"
#include "User.h"
// global constants:
const int MAX_ROWS = 8;             // max rows for board
const int MAX_COLS = 8;             // max columns for board
const int MAX_PIECES = 12;          // maximum pieces on the board per player
const int MOVES_BEFORE_DRAW = 40;   // max moves allowed before a draw is forced
const int THINKING_SECONDS = 3;     // constant for seconds the AI "thinks"

struct Move {           // Move Structure for the bulk of the program decisions
    int player;         //  Player # making move
    int row_start;      //  Row start coordinate
    int col_start;      //  Column start coordinate
    int row_end;        //  Row end start coordinate
    int col_end;        //  Column end coordinate
    bool possibleStart; //  Boolean flag for possible start point
    bool jumpingMove;   //  Boolean flag for jumping moves
    Direction movement; //  Directional movement

    ~Move() {};         // Default destructor
};


void playTheGame(User[]);                       // main game function
void initBoard(Tile[][MAX_COLS]);               // inits new game board

int getMoveList(int, Move[], Tile[][MAX_COLS]); // creates list of Moves
Move makeEmptyMove(Move);                       // makes a Move empty
Move getPlayerMove(int, Move[], Tile[][MAX_COLS]);  // gets player Move
Move getStart(Move[]);                          // gets player start coords
void getUserSelection(int[], bool);             // converts input to coords
bool checkStart(Move, Tile[][MAX_COLS]);        // checks start is good
bool checkStart(Move, Tile[][MAX_COLS], bool);  // overload to force check jumps
bool validateStart(Move, Move);                 // validates start
Move getTarget(Move, Tile[][MAX_COLS]);         // gets player target
bool checkTarget(Move, Tile[][MAX_COLS]);       // checks target is good


void updateBoard(Move, Tile[][MAX_COLS]);       // updates board with move
bool promotePawn(int, int);                 // determines if pawn should be king

void printBoard(Tile[][MAX_COLS]);              // prints board
void thinkAI();                                 // displays AI "think" pause
void printEnd(User[], int, Tile[][MAX_COLS]);   // prints end game msg
string centerOutput(int, string);             // centers string output to screen


Move getAImove(int, Move[], Tile[][MAX_COLS]);  // gets AI move
Move getAImove(int, Move, Tile[][MAX_COLS], bool);  // gets AI move forcing jump
                                                
void makeBlankBoard(Tile[][MAX_COLS]);          // debugging boards for testing
void makeTestBoard1(bool, Tile[][MAX_COLS]);    // see accompanying excel file
void makeTestBoard2(bool, Tile[][MAX_COLS]);    // to view board layouts
void makeTestBoard3(bool, Tile[][MAX_COLS]);
void makeTestBoard4(Tile[][MAX_COLS]);  
void makeTestBoard5(Tile[][MAX_COLS]);
void makeTestBoard6(Tile[][MAX_COLS]);
void makeTestBoard7(Tile[][MAX_COLS]);
void makeTestBoard8(Tile[][MAX_COLS]);
void makeTestBoard9(Tile[][MAX_COLS]);
void printMove(Move);                   // prints values of a move for debugging

/*
* Name:
*   playTheGame
* Parameters:
*   players[]   array of Users for this game
* Return:
*   None
* Description:
*   Wrangles all the game functions
*/
void playTheGame(User players[]) {
    // declare an array of tiles for the board
    auto board = new Tile[MAX_ROWS][MAX_COLS];

    // init the board
    initBoard(board);

    /*put debug boards here */
    /************************/
    /************************/

    // initialize current player as player 1
    User currentPlayer = players[0];
    User enemyPlayer = players[1];

    // initialize moves since last jump occured as 0
    int moveSinceLastJump = 0;

    bool firstIteration = true; // bool flag for first iteration of game loop

    do {
        if (firstIteration) {
            system("cls");
            printBoard(board);
            cout << currentPlayer.getName() << " will go first." << endl;
        }
        else {
            cout << enemyPlayer.getName() << " made their choice..." << endl;
        }

        Move moveList[MAX_PIECES];  // storing possible start points for player
        Move playerMove;            // storing a player's selected move

        int currentPlayerMovablePieces; // storing number of viable start
                                        // positions

        int playerNum = currentPlayer.getNum();

        // make sure the current player has start positions available
        // update the list of possible start points
        currentPlayerMovablePieces = getMoveList(playerNum, moveList, board);

        // if no moves available, end the game loop
        if (currentPlayerMovablePieces == 0) {
            break;
        }

        cout << currentPlayer.getName() << "'s turn!" << endl << endl;

        // get player move
        if (currentPlayer.isAI()) {
            playerMove = getAImove(playerNum, moveList, board);
        }
        else {
            playerMove = getPlayerMove(playerNum, moveList, board);
        }

        // update the board with the move
        updateBoard(playerMove, board);

        // increment move since last jump
        moveSinceLastJump++;

        // determine if a jump happened
        bool jumpHappened = playerMove.jumpingMove;

        // checks if another jump is possible after one occured
        while (jumpHappened) {
            cout << currentPlayer.getName() << " just jumped one of "
                << enemyPlayer.getName() << "'s pieces!" << endl;

            // set the start point of move to the previous end point
            playerMove.row_start = playerMove.row_end;
            playerMove.col_start = playerMove.col_end;

            // determine if another jump is possible
            if (checkStart(playerMove, board)) {

                // alert player to another jump and get the destination
                cout << "There is another jump available for "
                    << currentPlayer.getName() << "!" << endl;
                if (currentPlayer.isAI()) {
                    playerMove = getAImove(playerNum, playerMove, board, jumpHappened);
                }
                else {
                    playerMove = getTarget(playerMove, board);
                }

                // update the board with the move                
                updateBoard(playerMove, board);
            }
            else {  // if no additional jump is possible, set flag to false
                jumpHappened = false;
            }

            // set moves since last jump to 0
            moveSinceLastJump = 0;
        } // end jump while loop

        // change current player
        if (currentPlayer.getNum() == 1) {
            currentPlayer = players[1];
            enemyPlayer = players[0];
        }
        else {
            currentPlayer = players[0];
            enemyPlayer = players[1];
        }

        firstIteration = false; // change first iteration flag

        // repeat until a draw has been determined or loop gets broken from no
        // pieces left/no moves available
    } while (moveSinceLastJump < MOVES_BEFORE_DRAW);

    // updates statistics for User structure
    if (moveSinceLastJump < MOVES_BEFORE_DRAW) {
        printEnd(players, currentPlayer.getNum(), board);
        if (currentPlayer.isAI()) {
            if (currentPlayer.getNum() == 1) {
                players[0].addLoss(false);
            }
            else {
                players[0].addWin(false);
            }
        }
        else {
            if (currentPlayer.getNum() == 2) {
                players[0].addWin(true);
                players[1].addLoss(true);
            }
            else {
                players[0].addLoss(true);
                players[1].addWin(true);
            }
        }
    }
    else {
        if (currentPlayer.isAI()) {
            printEnd(players, 3, board);
            players[0].addDraw(false);
        }
        else {
            printEnd(players, 3, board);
            players[0].addDraw(true);
            players[1].addDraw(true);
        }
    }

    // free up the memory from the array
    delete[] board;
}
/*
* Name:
*   initBoard
* Parameters:
*   board
* Return:
*   none
* Description:
*   Initializes board as brand new
*/
void initBoard(Tile board[][MAX_COLS]) {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            board[row][col].initTile(row, col);
        }
    }
}
/*
* Name:
*   getMoveList
* Parameters:
*   playerNum   integer value of current player
*   list[]      List of Move structure to update with valid start points
*   board
* Return:
*   int     number of valid starting points
* Description:
*   Checks every tile of the board and adds the coordinates for coordinates
*   owned by the current player to a list. Then works through the list
*   to see if those coordinates are jumping start moves
*   If no jumping start moves are found, it works through the list again looking
*   for non-jumping start points. Returns the number of moves player is able
*   to make
*/
int getMoveList(int playerNum, Move list[], Tile board[][MAX_COLS]) {
    int playerPieces = 0;           // for counting how pieces are on the board
    int playerMovesAvailable = 0;   // for counting moves
    bool jumpableTile = false;      // flag for ending after finding jump starts
    bool jumping;                   // flag for checking jump moves
    int row;                        // row that will be checked for valid move
    int col;                        // col that will be checked for valid move


    // make sure the list array is initialized as empty to avoid stale/bad data
    for (int i = 0; i < MAX_PIECES; i++) {
        list[i] = makeEmptyMove(list[i]);
    }

    // work through the board adding coordinates owned by player to the list
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            if (board[row][col].getOwner() == playerNum) {
                list[playerPieces].player = playerNum;
                list[playerPieces].row_start = row;
                list[playerPieces].col_start = col;
                list[playerPieces].movement = board[row][col].getMovement();
                playerPieces++;
            }
        }
    }

    // work through pieces adding any that can jump
    jumping = true;
    for (int i = 0; i < playerPieces; i++) {
        row = list[i].row_start;
        col = list[i].col_start;

        // here is problem
        if (checkStart(list[i], board, jumping)) {
            list[i].possibleStart = true;
            list[i].jumpingMove = true;
            playerMovesAvailable++;
            jumpableTile = true;
        }
    }

    // if a jumpable tile found, end function
    if (jumpableTile) {
        return playerMovesAvailable;
    }

    // if no jumpable tile was found, find regular movement start points
    jumping = false;
    for (int i = 0; i < playerPieces; i++) {
        if (checkStart(list[i], board)) {
            list[i].possibleStart = true;
            playerMovesAvailable++;
        }
    }

    return playerMovesAvailable;
}
/*
* Name:
*   makeEmptyMove
* Parameters:
*   move    move to make empty
* Return:
*   Move    an "emtpy" move
* Description:
*   Makes a move structure "empty"
*/
Move makeEmptyMove(Move move) {
    move.player = -1;
    move.jumpingMove = false;
    move.possibleStart = false;
    move.movement = NONE;
    move.row_start = -1;
    move.col_start = -1;
    move.row_end = -1;
    move.col_end = -1;

    return move;
}
/*
* Name:
*   getPlayerMove
* Parameters:
*   playerNum   integer value of current player
*   list[]      list of Moves with good start points
*   board
* Return:
*   Move    complete move structure of a player move
* Description:
*   Wrangles all the functions to get a player move
*/
Move getPlayerMove(int playerNum, Move list[], Tile board[][MAX_COLS]) {

    Move playerMove;
    playerMove.player = playerNum;

    // get start move
    playerMove = getStart(list);

    // get target move
    playerMove = getTarget(playerMove, board);

    return playerMove;
}
/*
* Name:
*   getStart
* Parameters:
*   list[] list of moves with start coordinates known to be good starting points
* Return:
*   Move    a Move structure with start coordinates that are valid
* Description:
*   Checks user input against known good start points from the Move list
*   If the user selected a known good start point, it returns a Move structure
*   with those start coordinates
*/
Move getStart(Move list[]) {
    Move attemptStart;

    int selection[2]; // temp array for storing selection
                      // index 0 is row, index 1 is column

    getUserSelection(selection, true);

    attemptStart.row_start = selection[0];
    attemptStart.col_start = selection[1];

    // validates user input as good
    bool goodStart = false;
    for (int i = 0; i < MAX_PIECES; i++) {
        goodStart = validateStart(list[i], attemptStart);
        if (goodStart) {
            attemptStart = list[i];
            break;
        }
    }

    // recur if not valid input
    if (!goodStart) {
        cout << "That was not a valid start position." << endl;
        return getStart(list);
    }

    return attemptStart;
}
/*
* Name:
*   getUserSelection
* Parameters:
*   selection[] array for storing input after conversion to integers
*   starting    flag for displaying "start" or "target" is what to get
* Return:
*   none -> however this does update the selection array with values
* Description:
*   Gets user input as string of a character and number
*   Converts input to integer values of board indices and stores them in the
*   selection array
*/
void getUserSelection(int selection[], bool starting) {
    string input;
    string startOrTarget;

    int row = 0;
    int col = 1;

    if (starting) {
        startOrTarget = "starting";
    }
    else {
        startOrTarget = "target";
    }

    // get the input
    cout << "Enter your " << startOrTarget << " coordinates: ";
    getline(cin, input);

    // validate
    if (!regex_checkers_coord(input)) {
        cout << "\aInvalid Input!" << endl;
        return getUserSelection(selection, starting);
    }

    // decision structure below converts user input to row/col values as index
    // by converting the ASCII value of the entry to an integer and subtracting
    // the ASCII value of 1 (50) or A (65)

    // if the user entered "1A", use 1 as row number, A as column letter
    if (isdigit(input.at(0))) {
        selection[row] = static_cast<int>(input.at(0));
        selection[row] -= 49;
        selection[col] = static_cast<int>(input.at(1));
        selection[col] -= 65;
    }
    else { // else the user entered "A1"
        selection[row] = static_cast<int>(input.at(1));
        selection[row] -= 49;
        selection[col] = static_cast<int>(input.at(0));
        selection[col] -= 65;
    }

    // if the letter for column selection was lower case, subtract 32
    if (selection[col] >= 8) {
        selection[col] -= 32;
    }
}
/*
* Name:
*   checkStart
* Parameters:
*   startPoint  Move structure with start coordinates
*   board
* Return:
*   true if starting coordinates are good for starting position
* Description:
*   Checks that piece at starting point coordinates is able to move
*/
bool checkStart(Move startPoint, Tile board[][MAX_COLS]) {
    int modifier;
    bool checkNorth = false;
    bool checkSouth = false;

    Move temporary = startPoint;

    if (temporary.jumpingMove) {
        modifier = 2;
    }
    else {
        modifier = 1;
    }

    if (temporary.movement == NORTH || temporary.movement == ALL) {
        checkNorth = true;
    }

    if (temporary.movement == SOUTH || temporary.movement == ALL) {
        checkSouth = true;
    }

    if (checkNorth) {
        // NW
        temporary.row_end = temporary.row_start - modifier;
        temporary.col_end = temporary.col_start - modifier;
        if (checkTarget(temporary, board)) {
            return true;
        }

        // NE
        temporary.col_end += (modifier * 2);
        if (checkTarget(temporary, board)) {
            return true;
        }
    }

    if (checkSouth) {
        // SE
        temporary.row_end = temporary.row_start + modifier;
        temporary.col_end = temporary.col_start + modifier;
        if (checkTarget(temporary, board)) {
            return true;
        }

        // SW
        temporary.col_end -= (modifier * 2);
        if (checkTarget(temporary, board)) {
            return true;
        }
    }

    // if it gets here, bad starting point
    return false;
}
/*
* Name:
*   checkStart (OVERLOAD)
* Parameters:
*   startPoint  Move structure with start coordinates
*   board
*   forceCheck  flag for forcing check of Jump
* Return:
*   true if starting coordinates are good for starting position
* Description:
*   Checks that piece at starting point coordinates is able to move
*   Forces checking of jump if forceCheck is true
*   Overload of above
*/
bool checkStart(Move startPoint, Tile board[][MAX_COLS], bool forceCheck) {
    int modifier = 2;
    bool checkNorth = false;
    bool checkSouth = false;

    Move temporary = startPoint;
    temporary.jumpingMove = forceCheck;

    if (temporary.movement == NORTH || temporary.movement == ALL) {
        checkNorth = true;
    }

    if (temporary.movement == SOUTH || temporary.movement == ALL) {
        checkSouth = true;
    }

    if (checkNorth) {
        // NW
        temporary.row_end = temporary.row_start - modifier;
        temporary.col_end = temporary.col_start - modifier;
        if (checkTarget(temporary, board)) {
            return true;
        }

        // NE
        temporary.col_end += (modifier * 2);
        if (checkTarget(temporary, board)) {
            return true;
        }
    }

    if (checkSouth) {
        // SE
        temporary.row_end = temporary.row_start + modifier;
        temporary.col_end = temporary.col_start + modifier;
        if (checkTarget(temporary, board)) {
            return true;
        }

        // SW
        temporary.col_end -= (modifier * 2);
        if (checkTarget(temporary, board)) {
            return true;
        }
    }

    // if it gets here, bad starting point
    return false;
}
/*
* Name:
*   validateStart
* Parameters:
*   knownGood   Move structure with known good start coordinates from Move list
*   attempt     Attempted start coordinates that need to be verified
* Return:
*   true if attempted start is the same as a known good start
* Description:
*   Validates an input move against a known good Move for starting coordinates
*/
bool validateStart(Move knownGood, Move attempt) {
    return (
        (knownGood.row_start == attempt.row_start)
        && (knownGood.col_start == attempt.col_start)
        && (knownGood.possibleStart)
        );
}
/*
* Name:
*   getTarget
* Parameters:
*   attemptTarget   beginning Move structure with start coordinates
* Return:
*   attemptTarget   Move structure with attempted target coordinates
* Description:
*   Takes input from getUserSelection function and checks the coordinates for
*   validity
*/
Move getTarget(Move attemptTarget, Tile board[][MAX_COLS]) {

    int selection[2]; // temp array for storing selection
                      // index 0 is row, index 1 is column

    // get user input
    getUserSelection(selection, false);

    attemptTarget.row_end = selection[0];
    attemptTarget.col_end = selection[1];

    // make sure move is good
    bool goodMove = checkTarget(attemptTarget, board);

    // if not a good target, recur
    if (!goodMove) {
        cout << "\aThat was not a valid target position." << endl;
        return getTarget(attemptTarget, board);
    }

    return attemptTarget;
}
/*
* Name:
*   checkTarget
* Parameters:
*   attempt     attempted move
*   board
* Return:
*   true if target coordinates good
* Description:
*   Checks if coordinates for a target location are valid, returns false if bad
*   coordinates entered for any reason
*/
bool checkTarget(Move attempt, Tile board[][MAX_COLS]) {
    int enemy = (attempt.player % 2) + 1;
    int rowDiff = attempt.row_start - attempt.row_end;
    int colDiff = attempt.col_start - attempt.col_end;

    // make sure destination coordinates are not out of bounds
    bool outOfBounds = attempt.row_end < 0
        || attempt.row_end > MAX_ROWS - 1
        || attempt.col_end < 0
        || attempt.col_end > MAX_COLS - 1;

    if (outOfBounds)
        return false;

    // this bounces a choice that is only horizontal, only vertical, or no move
    bool notDiagonal = rowDiff == 0 || colDiff == 0;

    if (notDiagonal)
        return false;

    // check that destination is empty
    bool empty = board[attempt.row_end][attempt.col_end].isEmpty();

    if (!empty)
        return false;

    // check that the user isn't trying to move too many spaces
    bool tooFar = (abs(rowDiff) > 2) || (abs(colDiff) > 2);

    if (tooFar)
        return false;

    // make sure not attempting north movement when only south is allowed
    // and vice-versa
    bool badDirection = (attempt.movement == NORTH && rowDiff < 0)
        || (attempt.movement == SOUTH && rowDiff > 0);

    if (badDirection)
        return false;

    // make sure a jump was taken if available
    if (attempt.jumpingMove) {
        // not a move of 2 for jump, return false
        bool jumpNotTaken = ((abs(attempt.row_start - attempt.row_end)) != 2)
            && ((abs(attempt.col_start - attempt.col_end)) != 2);
        if (jumpNotTaken) {
            cout << "\aJump moves must be made!" << endl;
            return false;
        }

        // jumped tile not belonging to enemy
        int jumpedRow = (attempt.row_start + attempt.row_end) / 2;
        int jumpedCol = (attempt.col_start + attempt.col_end) / 2;

        bool badJump = board[jumpedRow][jumpedCol].getOwner() != enemy;

        if (badJump)
            return false;
    }

    // if all of that passes -> move attempt is good
    return true;
}
/*
* Name:
*   updateBoard
* Parameters:
*   move    move to update board with
*   board
* Return:
*   none
* Description:
*   Updates board with a move and reprints it
*/
void updateBoard(Move move, Tile board[][MAX_COLS]) {
    bool jumpHappened;

    // determine if a jump happened
    jumpHappened = abs(move.row_start - move.row_end) == 2
        && abs(move.col_start - move.col_end) == 2;

    // determine if piece moved was king and update board with king
    if (board[move.row_start][move.col_start].isKing()) {
        board[move.row_end][move.col_end].makeKing(move.player);
    }
    else { // else determine if a pawn piece should become a king and update
        if (promotePawn(move.row_end, move.player)) {
            board[move.row_end][move.col_end].makeKing(move.player);
        }
        else { // otherwise update board with pawn
            board[move.row_end][move.col_end].makePawn(move.player);
        }
    }

    // make the start coordinates empty
    board[move.row_start][move.col_start].makeEmpty();

    // if a jump happened, make jumped tile empty
    if (jumpHappened) {
        int jumpedRow = (move.row_start + move.row_end) / 2;
        int jumpedCol = (move.col_start + move.col_end) / 2;

        board[jumpedRow][jumpedCol].makeEmpty();
    }

    // clear screen and reprint board
    system("cls");
    printBoard(board);
}
/*
* Name:
*   promotePawn
* Parameters:
*   row         int value of pawn location
*   playerNum   int value of current player
* Return:
*   true if pawn should become king
* Description:
*   Decides if a pawn has reached a square where it should be promoted to king
*/
bool promotePawn(int row, int playerNum) {
    return (playerNum == 1 && row == (MAX_ROWS - 1))
        || (playerNum == 2 && row == (MAX_ROWS - MAX_ROWS));
}
/*
* Name:
*   printBoard
* Parameters:
*   board
* Return:
*   none
* Description:
*   Prints the game board
*   Uses 3 loops nested inside a loop for board rows
*   The board display is a system of 2 rows and 2 columns
*   The big row is the actual rows of the board
*   The small row is the row of display characters
*   The big column is the actual columns of the board
*   The small column is the column of display characters
*/
void printBoard(Tile board[][MAX_COLS]) {
    char colLetter = 'A';

    cout << endl;
    cout << "  ";

    // print top col letter display
    for (int i = 1; i < (MAX_ROWS + 1)*(DISP_ROW + 1); i++) {
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
    for (int i = 0; i <= (MAX_ROWS)*(DISP_ROW + 1); i++) {
        if (i % 4 == 0) {
            cout << "+";
        }
        else {
            cout << "-";
        }
    }

    cout << endl;

    // print the board 
    for (int big_row = 0; big_row < MAX_ROWS; big_row++) {
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
            for (int big_col = 0; big_col < MAX_COLS; big_col++) {
                for (int small_col = 0; small_col < DISP_COL; small_col++) {
                    cout << board[big_row][big_col].dispTile(small_row, small_col);
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
        for (int i = 0; i <= (MAX_ROWS)*(DISP_ROW + 1); i++) {
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
    for (int i = 1; i < (MAX_ROWS + 1)*(DISP_ROW + 1); i++) {
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
*   thinkAI
* Parameters:
*   none
* Return:
*   none
* Description:
*   Pauses game for AI decisions so that the board doesn't update instantly
*   after a player makes a move against the AI
*/
void thinkAI() {
    cout << "The computer is thinking";
    for (int i = 0; i < THINKING_SECONDS; i++) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << ".";
    }
}
/*
* Name:
*   printEnd
* Parameters:
*   players[]   List of Users from game
*   loser       integer value of the loser (3 if draw)
*   board
* Return:
*   none
* Description:
*   Prints end of game information
*/
void printEnd(User players[], int loser, Tile board[][MAX_COLS]) {
    int winner;
    int dispWidth = 50;
    string endMsg;

    // if not a draw build message for winner
    if (loser != 3) {
        winner = (loser % 2) + 1;
        endMsg = players[winner - 1].getName();
        endMsg += " won the game!";
    }
    else {
        endMsg = "The game was a draw!";
    }

    for (int i = 0; i < dispWidth; i++) {
        cout << "*";
    }

    cout << endl << centerOutput(dispWidth, "GAME OVER") << endl;

    cout << centerOutput(dispWidth, endMsg) << endl;

    for (int i = 0; i < dispWidth; i++) {
        cout << "*";
    }

    cout << endl << endl;
}
/*
* Name:
*   centerOutput
* Parameters:
*   width   width of display for centering
*   str     string that needs centering
* Return:
*   string  
* Description:
*   Takes in a string and desired width of print out
*   Then determines padding to add on each side of string for centering output
*   display
*/
string centerOutput(int width, string str) {
    int length = static_cast<int>(str.length());
    if (width < length) {
        return str;
    }

    int diff = width - length;
    int pad1 = diff / 2;
    int pad2 = diff - pad1;
    return string(pad1, ' ') + str + string(pad2, ' ');
}
/*******************************************************************************
                            AI FUNCTIONS
*******************************************************************************/
/*
* Name:
*   getAImove
* Parameters:
*   playerNum   current player number
*   list[]      List of valid move starting points
*   board
* Return:
*   Move    AI selected move
* Description:
*   AI function to get a move
*   Works determining what moves in the Move list are valid start points
*   Adds the index # of valid start moves to a temporary array and increments
*   number of moves possible by one for each valid move
*   Random number from 0 to number of possible moves selected and used to find
*   index of the Move in the Move list
*   Directional movement is then checked and chosen at random
*   The methodology of this is explained in more detailed commenting inside
*/
Move getAImove(int playerNum, Move list[], Tile board[][MAX_COLS]) {
    thinkAI();

    srand(static_cast<int>(time(0)));
    int moveIndex[MAX_PIECES];
    int arrIndex = 0;
    int numDirections = 0;
    Move aiSelection;
    Move temp[4];
    int randomSelection;
    bool checkNorth = false;
    bool checkSouth = false;
    bool jump = false;
    int modifier = 1;

    // determine which starts are possible from the list and add the index to the list
    for (int i = 0; i < MAX_PIECES; i++) {
        if (list[i].possibleStart) {
            moveIndex[arrIndex] = i;
            arrIndex++;
        }
    }

    // get a random number from 0 to arrIndex
    randomSelection = rand() % (arrIndex);
    
    // select the random start from the list
    aiSelection = list[moveIndex[randomSelection]];

    // create a temporary array for determining what directions movement can be 
    for (int i = 0; i < 4; i++) {
        temp[i] = aiSelection;
    }

    // set jump to start move jump flag
    jump = aiSelection.jumpingMove;

    // determine which directions are valid
    /***************************************************************************
    Starts off by setting temp[0] to NW. If NW is good, the number of
    directions is incremented
    It then sets temp[1] to NE. If that is good, number of directions is not
    incremented
    So temp[1] is then set to SE. If that is good, then number of directions is
    incremented and then temp[2] is set to SW. If that is good, numDirections is
    incremented again so the first 3 values in the array are good, and only
    those 3 are used for selection.
    ***************************************************************************/
    if (aiSelection.movement == NORTH || aiSelection.movement == ALL) {
        checkNorth = true;
    }
    if (aiSelection.movement == SOUTH || aiSelection.movement == ALL) {
        checkSouth = true;
    }

    // if it's a jump, add 1 to the modifier
    if (jump) {
        modifier++;
    }

    // now check each direction
    if (checkNorth) {
        // NW
        temp[numDirections].row_end = temp[numDirections].row_start - modifier;
        temp[numDirections].col_end = temp[numDirections].col_start - modifier;
        if (checkTarget(temp[numDirections], board)) {
            numDirections++;
        }
        // NE
        temp[numDirections].col_end += (modifier * 2);
        if (checkTarget(temp[numDirections], board)) {
            numDirections++;
        }
    }

    if (checkSouth) {
        // SE
        temp[numDirections].row_end = temp[numDirections].row_start + modifier;
        temp[numDirections].col_end = temp[numDirections].col_start + modifier;
        if (checkTarget(temp[numDirections], board)) {
            numDirections++;
        }
        // SW
        temp[numDirections].col_end -= (modifier * 2);
        if (checkTarget(temp[numDirections], board)) {
            numDirections++;
        }
    }

    // make a random valid selection and return the move
    randomSelection = rand() % (numDirections);

    aiSelection = temp[randomSelection];

    return aiSelection;
}
/*
* Name:
*   getAImove (OVERLOAD)
* Parameters:
*   playerNum   current player number
*   start       Move with start coordinates
*   board
*   doubleJump  bool flag to force check jumps
* Return:
*   Move    AI selected move
* Description:
*   Overload of above function to force checking jump moves
*/
Move getAImove(int playerNum, Move start, Tile board[][MAX_COLS], bool doubleJump) {
    thinkAI();

    srand(static_cast<int>(time(0)));
    int numDirections = 0;
    Move aiSelection = start;
    Move temp[4];
    int randomSelection;
    bool checkNorth = false;
    bool checkSouth = false;
    int modifier = 2;

    for (int i = 0; i < 4; i++) {
        temp[i] = aiSelection;
    }

    // determine which directions are valid based on movement
    if (aiSelection.movement == NORTH || aiSelection.movement == ALL) {
        checkNorth = true;
    }
    if (aiSelection.movement == SOUTH || aiSelection.movement == ALL) {
        checkSouth = true;
    }

    // now check each direction and add to total number of directions
    if (checkNorth) {
        // NW
        temp[numDirections].row_end = temp[numDirections].row_start - modifier;
        temp[numDirections].col_end = temp[numDirections].col_start - modifier;
        if (checkTarget(temp[numDirections], board)) {
            numDirections++;
        }
        // NE
        temp[numDirections].col_end += (modifier * 2);
        if (checkTarget(temp[numDirections], board)) {
            numDirections++;
        }
    }

    if (checkSouth) {
        // SE
        temp[numDirections].row_end = temp[numDirections].row_start + modifier;
        temp[numDirections].col_end = temp[numDirections].col_start + modifier;
        if (checkTarget(temp[numDirections], board)) {
            numDirections++;
        }
        // SW
        temp[numDirections].col_end -= (modifier * 2);
        if (checkTarget(temp[numDirections], board)) {
            numDirections++;
        }
    }

    randomSelection = rand() % (numDirections);

    aiSelection = temp[randomSelection];

    return aiSelection;
}
/*******************************************************************************
                         DEBUGGING BOARDS
See accompanying excel file for display of each board
*******************************************************************************/
/*
* Name:
*   makeBlankBoard
* Parameters:
*   board
* Return:
*   none
* Description:
*   makes a completely blank board with no pieces
*/
void makeBlankBoard(Tile board[][MAX_COLS]) {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            board[row][col].makeEmpty();
        }
    }
}
/*
* Name:
*   makeTestBoard1
* Parameters:
*   board
*   king    true if piece to test should be king
* Return:
*   none
* Description:
*   For testing general movement of pawn or piece
*/
void makeTestBoard1(bool king, Tile board[][MAX_COLS]) {
    makeBlankBoard(board);
    if (king)
        board[3][3].makeKing(1);
    else
        board[3][3].makePawn(1);
}
/*
* Name:
*   makeTestBoard2
* Parameters:
*   board
*   king    true if piece to test should be king
* Return:
*   none
* Description:
*   For testing jumps of pieces
*/
void makeTestBoard2(bool king, Tile board[][MAX_COLS]) {
    makeTestBoard1(king, board);
    board[2][2].makePawn(2);
    board[2][4].makePawn(2);
    board[4][2].makePawn(2);
    board[4][4].makePawn(2);
}
/*
* Name:
*   makeTestBoard3
* Parameters:
*   board
*   king    true if piece to test should be king
* Return:
*   none
* Description:
*   for testing jump trigger doesn't become true if no jumps available
*/
void makeTestBoard3(bool king, Tile board[][MAX_COLS]) {
    makeTestBoard2(king, board);
    board[1][1].makePawn(2);
    board[1][5].makePawn(2);
    board[5][1].makePawn(2);
    board[5][5].makePawn(2);
}
/*
* Name:
*   makeTestBoard4
* Parameters:
*   board
* Return:
*   none
* Description:
*   For testing no more moves but all pieces on board triggers loss for player 2
*/
void makeTestBoard4(Tile board[][MAX_COLS]) {
    makeBlankBoard(board);
    board[0][0].makePawn(1);

    board[1][3].makePawn(1);
    board[1][5].makePawn(1);
    board[1][7].makePawn(1);

    board[2][0].makePawn(1);
    board[2][2].makePawn(1);
    board[2][4].makePawn(1);
    board[2][6].makePawn(1);

    board[3][1].makePawn(1);
    board[3][3].makePawn(1);
    board[3][5].makePawn(2);
    board[3][7].makePawn(1);

    board[4][0].makePawn(2);
    board[4][2].makePawn(1);
    board[4][4].makePawn(2);
    board[4][6].makePawn(2);

    for (int i = 1; i < MAX_COLS; i += 2) {
        board[5][i].makePawn(2);
    }

    for (int i = 0; i < MAX_COLS; i += 2) {
        board[6][i].makePawn(2);
    }

}
/*
* Name:
*   makeTestBoard5
* Parameters:
*   none
* Return:
*   none
* Description:
*   For testing king movement, redundancy with 6
*/
void makeTestBoard5(Tile board[][MAX_COLS]) {
    makeBlankBoard(board);
    board[1][1].makePawn(1);
    board[1][3].makePawn(1);
    board[1][5].makePawn(1);
    board[1][7].makePawn(1);
    board[2][2].makePawn(2);
    board[2][4].makePawn(2);
    board[2][6].makePawn(2);
    board[6][2].makePawn(2);
    board[6][4].makePawn(2);
    board[6][6].makePawn(2);
    board[7][1].makeKing(1);
    board[7][3].makeKing(1);
    board[7][5].makeKing(1);
    board[7][7].makeKing(1);
}
/*
* Name:
*   makeTestBoard6
* Parameters:
*   board
* Return:
*   none
* Description:
*   For testing king movement and force jumps, redundancy with 5
*/
void makeTestBoard6(Tile board[][MAX_COLS]) {
    makeBlankBoard(board);
    for (int i = 0; i < MAX_COLS; i = i + 2) {
        board[2][i].makeKing(1);
        board[3][i + 1].makePawn(2);
        board[4][i].makeKing(1);
    }

}
/*
* Name:
*   makeTestBoard7
* Parameters:
*   board
* Return:
*   none
* Description:
*   For testing multi-directional southern multi-jumps
*/
void makeTestBoard7(Tile board[][MAX_COLS]) {
    makeBlankBoard(board);
    board[1][3].makePawn(1);
    board[2][2].makePawn(2);
    board[4][2].makePawn(2);
    board[6][2].makePawn(2);
}
/*
* Name:
*   makeTestBoard8
* Parameters:
*   board
* Return:
*   none
* Description:
*   Tests bounds checking to make sure piece cannot move outside board
*/
void makeTestBoard8(Tile board[][MAX_COLS]) {
    makeBlankBoard(board);
    board[4][4].makePawn(1);
    board[5][5].makePawn(2);
    board[7][7].makePawn(2);
}
/*
* Name:
*   makeTestBoard9
* Parameters:
*   board
* Return:
*   none
* Description:
*   Tests double jump functionality
*/
void makeTestBoard9(Tile board[][MAX_COLS]) {
    makeBlankBoard(board);
    board[1][1].makePawn(1);
    board[2][2].makePawn(2);
    board[4][4].makePawn(2);
    board[6][6].makePawn(2);
    board[6][0].makePawn(2);
}
/*
* Name:
*   printMove
* Parameters:
*   move    Move structure to print
* Return:
*   none
* Description:
*   Prints a move structure to screen for debugging purposes
*/
void printMove(Move move) {
    cout << "Player: " << move.player << endl
        << "row_start: " << move.row_start << endl
        << "col_start: " << move.col_start << endl
        << "row_end: " << move.row_end << endl
        << "col_end: " << move.col_end << endl
        << "TRUE: " << true << " FALSE: " << false << endl
        << "possibleStart: " << move.possibleStart << endl
        << "jumpingMove: " << move.jumpingMove << endl
        << "Direction: NORTH: " << NORTH << " SOUTH: " << SOUTH << " ALL: "
        << ALL << " NONE: " << NONE << endl
        << "movement: " << move.movement << endl << endl;
}