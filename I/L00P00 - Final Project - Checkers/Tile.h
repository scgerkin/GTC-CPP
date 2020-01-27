#ifndef TILE_H
#define TILE_H
#pragma once

// globals for output display row/columns
const int DISP_ROW = 3;
const int DISP_COL = 3;

// enum for directional movement
enum Direction { NORTH, SOUTH, ALL, NONE };

class Tile {
private:
    bool empty;         // flag for empty tile
    bool invalid;       // flag for invalid tile
    int owner;          // int value of current player owning a tile
    bool king;          // flag for king (default false)
    Direction movement; // piece movement ability
    char disp[3][3];    // output display for board

public:
    // constructors
    Tile();                   // default constructor sets all tiles as false
    Tile(const Tile&);        // copy constructor
    void initTile(int, int);  // all tiles must be initialized with this
    char dispTile(int, int);  // returns display, params: row & column
    bool isInvalid();         // returns true if a tile is invalid
    bool isEmpty();           // returns true if a tile is empty
    int getOwner();           // returns the int value of the current owner
    Direction getMovement();  // returns directional movement for piece on tile
    bool isKing();            // returns false if tile is not a king
    void makeEmpty();         // make a tile empty
    void makePawn(int);       // make a tile a pawn, param: player #
    void makeKing(int);       // make a tile a king, param: player #
    ~Tile();                  // destructor
};

#endif // !TILE_H