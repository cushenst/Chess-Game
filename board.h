//
// Created by Stephen Cushen on 29/10/2019.
//

#ifndef LAB4_BOARD_H
#define LAB4_BOARD_H

#include "chess_piece.h"

class board {
public:
    board();

    ~board();

    void generatePieces();

    void printBoard();

    chess_piece *piecePointers[32];

    int isSquareOccupied(char location[2]);

    int movePiece(char pieceLocation[2], char moveLocation[2]);

private:
    int diagonalMove(char pieceLocation[2], char moveLocation[2]);

    int squareMove(char pieceLocation[2], char moveLocation[2]);
};


#endif //LAB4_BOARD_H
