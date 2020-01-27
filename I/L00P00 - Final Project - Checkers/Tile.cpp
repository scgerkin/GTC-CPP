#include "Tile.h"

// see Tile header for information about individual class methods

// default constructor makes every tile invalid
// tiles need to be individually initialized with the init function
Tile::Tile() {

    empty = false;
    invalid = true;
    owner = -1;
    king = false;
    movement = NONE;
    for (int row = 0; row < DISP_ROW; row++) {
        for (int col = 0; col < DISP_COL; col++) {
            disp[row][col] = '#';
        }
    }
}

void Tile::initTile(int row, int col) {

    // tiles that are going to be invalid remain invalid
    invalid = (
        (col % 2 != 0 && row % 2 == 0)      // odd col even row
        ||                                  // or
        (row % 2 != 0 && col % 2 == 0)      // odd row even col
        );

    // *** this structure initializes valid tiles
    //todo this will need to be changed for sending in bigger boards
    if (!invalid) {
        if (row < 3) {        // top 3 rows of board
            makePawn(1);
        }
        else if (row > 4) {   // bottom 3 rows of board
            makePawn(2);
        }
        else {              // middle of board
            makeEmpty();
        }
    }

    king = false;
}

// getters
int Tile::getOwner() {
    return owner;
}
bool Tile::isEmpty() {
    return empty;
}
bool Tile::isInvalid() {
    return invalid;
}
char Tile::dispTile(int row, int col) {
    return disp[row][col];
}
Direction Tile::getMovement() {
    return movement;
}
bool Tile::isKing() {
    return king;
}


// tile changing functions (mutators)
void Tile::makeEmpty() {
    if (!invalid) {
        empty = true;
        owner = 0;
        movement = NONE;
        king = false;
        for (int row = 0; row < DISP_ROW; row++) {
            for (int col = 0; col < DISP_COL; col++) {
                disp[row][col] = ' ';
            }
        }
    }
}
void Tile::makePawn(int playerNum) {
    empty = false;
    owner = playerNum;

    if (playerNum == 1) {
        movement = SOUTH;
        for (int row = 0; row < DISP_ROW; row++) {
            for (int col = 0; col < DISP_COL; col++) {
                if (row == 1 && col == 1) {
                    disp[row][col] = 'X';
                }
                else {
                    disp[row][col] = ' ';
                }
            }
        }
    }
    else {
        movement = NORTH;
        for (int row = 0; row < DISP_ROW; row++) {
            for (int col = 0; col < DISP_COL; col++) {
                if (row == 1 && col == 1) {
                    disp[row][col] = 'O';
                }
                else {
                    disp[row][col] = ' ';
                }
            }
        }
    }
}
void Tile::makeKing(int playerNum) {
    empty = false;
    owner = playerNum;
    movement = ALL;
    king = true;

    if (playerNum == 1) {
        int iteration = 0;
        for (int row = 0; row < DISP_ROW; row++) {
            for (int col = 0; col < DISP_COL; col++) {
                if (iteration % 2 == 0) {
                    disp[row][col] = ' ';
                }
                else {
                    disp[row][col] = 'X';
                }
                iteration++;
            }
        }
    }
    else {
        int iteration = 0;
        for (int row = 0; row < DISP_ROW; row++) {
            for (int col = 0; col < DISP_COL; col++) {
                if (iteration % 2 == 0) {
                    disp[row][col] = ' ';
                }
                else {
                    disp[row][col] = 'O';
                }
                iteration++;
            }
        }
    }
}

Tile::Tile(const Tile &obj) {
    empty = obj.empty;
    invalid = obj.invalid;
    owner = obj.invalid;
    king = obj.king;
    movement = obj.movement;
    for (int row = 0; row < DISP_ROW; row++) {
        for (int col = 0; col < DISP_COL; col++) {
            disp[row][col] = obj.disp[row][col];
        }
    }
}

// destructor
Tile::~Tile() {
    
}
