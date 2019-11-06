//
// Created by Stephen Cushen on 29/10/2019.
//

#include "board.h"
#include "chess_piece.h"
#include <iostream>
#include <iomanip>

using namespace std;

board::board() {
    chess_piece *piecePointers[32];
    generatePieces();
}

board::~board() {

}

void board::generatePieces() {
    char location[2];
    int positionCounter = 0;
    for (int i = 1; i <= 4; i++) {
        location[0] = "1278"[i - 1];
        for (int a = 0; a < 8; a++) {
            location[1] = "abcdefgh"[a];
            chess_piece *newPiece = new chess_piece(location);
            piecePointers[positionCounter] = newPiece;
            positionCounter++;
        }
    }
}

void board::printBoard() {
    cout << setw(34) << "||A||B||C||D||E||F||G||H|\n"
         << setw(34) << "#########################\n";
    char location[2];
    for (int i = 1; i <= 8; i++) {
        cout << i << "|" << setw(8);
        for (int a = 0; a < 8; a++) {
            location[0] = "12345678"[i - 1];
            location[1] = "abcdefgh"[a];
            int pos = isSquareOccupied(location);
            if (pos < 33)
                if (piecePointers[pos]->colour == 'b')
                    cout << "||" << "\033[1;31m" << piecePointers[pos]->type << "\033[0m";
                else
                    cout << "||" << piecePointers[pos]->type;
            else
                cout << "||" << "_";

        }
        cout << "|\n";
    }
    cout << setw(34) << "#########################\n"
         << setw(34) << "||A||B||C||D||E||F||G||H|\n";
}

int board::isSquareOccupied(char location[2]) {
    for (int i = 0; i < 32; i++) {
        if (piecePointers[i]->pos[0] == location[0] and piecePointers[i]->pos[1] == location[1])
            return i;
    }
    return 33;
}

int board::movePiece(char pieceLocation[2], char moveLocation[2]) {
    char reverseMoveLocation[2];
    reverseMoveLocation[0] = moveLocation[1];
    reverseMoveLocation[1] = moveLocation[0];
    int takePiece = isSquareOccupied(reverseMoveLocation);
    int location = isSquareOccupied(pieceLocation);
    if ((int) moveLocation[0] - 97 > 7 or (int) moveLocation[1] - 48 > 8)
        return 1;
    if (takePiece != 33 and (piecePointers[location]->type == 'p' or piecePointers[location]->type == 'n' or
                             piecePointers[location]->type == 'k')) {
        int isMoved = piecePointers[location]->move(moveLocation);
        if (isMoved == 0 and piecePointers[takePiece]->colour != piecePointers[location]->colour and
            (piecePointers[location]->type == 'p' and
             ((moveLocation[0] == pieceLocation[1] + 1 or moveLocation[0] == pieceLocation[1] - 1) and
              (pieceLocation[1] == moveLocation[0] - 1 or pieceLocation[1] == moveLocation[0] + 1)))) {
            piecePointers[location]->pos[0] = moveLocation[1];
            piecePointers[location]->pos[1] = moveLocation[0];
            piecePointers[takePiece]->pos[0] = '9';
            piecePointers[takePiece]->pos[1] = 'j';
            delete piecePointers[takePiece];
            return 0;
        } else if (isMoved == 0 and piecePointers[takePiece]->colour != piecePointers[location]->colour and
                   (piecePointers[location]->type != 'p')) {
            piecePointers[location]->pos[0] = moveLocation[1];
            piecePointers[location]->pos[1] = moveLocation[0];
            piecePointers[takePiece]->pos[0] = '9';
            piecePointers[takePiece]->pos[1] = 'j';
            delete piecePointers[takePiece];
            return 0;
        }
        return 1;
    } else if (pieceLocation[1] == moveLocation[0] and piecePointers[location]->type == 'p') {
        int isMoved = piecePointers[location]->move(moveLocation);
        if (isMoved == 0) {
            piecePointers[location]->pos[0] = moveLocation[1];
            piecePointers[location]->pos[1] = moveLocation[0];
            return 0;
        } else {
            return 1;
        }
    } else if (piecePointers[location]->type == 'r') {
        int isValid = squareMove(pieceLocation, moveLocation);
        if (isValid == 0) {
            piecePointers[location]->pos[0] = moveLocation[1];
            piecePointers[location]->pos[1] = moveLocation[0];
            return 0;
        } else {
            return 1;
        }

    } else if (piecePointers[location]->type == 'n') {
        int isMoved = piecePointers[location]->move(moveLocation);
        if (isMoved == 0) {
            piecePointers[location]->pos[0] = moveLocation[1];
            piecePointers[location]->pos[1] = moveLocation[0];
            return 0;
        } else {
            return 1;
        }
    } else if (piecePointers[location]->type == 'b') {
        int isValid = diagonalMove(pieceLocation, moveLocation);
        if (isValid == 0) {
            piecePointers[location]->pos[0] = moveLocation[1];
            piecePointers[location]->pos[1] = moveLocation[0];
            return 0;
        } else {
            return 1;
        }
    } else if (piecePointers[location]->type == 'k') {
        int isMoved = piecePointers[location]->move(moveLocation);
        if (isMoved == 0) {

            piecePointers[location]->pos[0] = moveLocation[1];
            piecePointers[location]->pos[1] = moveLocation[0];
            return 0;
        } else
            return 1;
    } else if (piecePointers[location]->type == 'q') {
        int isValid = 1;
        isValid = squareMove(pieceLocation, moveLocation);
        if (isValid != 0)
            isValid = diagonalMove(pieceLocation, moveLocation);
        if (isValid == 0) {
            piecePointers[location]->pos[0] = moveLocation[1];
            piecePointers[location]->pos[1] = moveLocation[0];
            return 0;
        } else {
            return 1;
        }

    } else
        return 1;
}

int board::diagonalMove(char pieceLocation[2], char moveLocation[2]) {
    char reverseMoveLocation[2];
    reverseMoveLocation[0] = moveLocation[1];
    reverseMoveLocation[1] = moveLocation[0];
    int location = isSquareOccupied(pieceLocation);
    int positiveUpDown = 0;
    int positiveLeftRight = 0;
    char leftRight = piecePointers[location]->pos[1];

    if (piecePointers[location]->pos[0] > moveLocation[1])
        positiveUpDown--;
    else
        positiveUpDown++;

    if (piecePointers[location]->pos[1] > moveLocation[0]) {
        positiveLeftRight--;
    } else
        positiveLeftRight++;

    for (int i = (int) piecePointers[location]->pos[0] - 48; i != (int) moveLocation[1] - 48; i = i + positiveUpDown) {
        leftRight = static_cast<char>(leftRight + positiveLeftRight);
        char testLocation[2];
        if (positiveUpDown == 1)
            testLocation[0] = "12345678"[i];
        else
            testLocation[0] = "12345678"[i - 2];
        testLocation[1] = leftRight;
        if (isSquareOccupied(testLocation) != 33 and
            (testLocation[0] != moveLocation[1] or testLocation[1] != moveLocation[0]))
            return 1;
        else if (isSquareOccupied(testLocation) != 33 and
                 piecePointers[location]->colour != piecePointers[isSquareOccupied(testLocation)]->colour and
                 (testLocation[0] == moveLocation[1] or testLocation[1] == moveLocation[0])) {
            int takePiece = isSquareOccupied(testLocation);
            piecePointers[takePiece]->pos[0] = '9';
            piecePointers[takePiece]->pos[1] = 'j';
            piecePointers[location]->pos[0] = moveLocation[1];
            piecePointers[location]->pos[1] = moveLocation[0];
            return 0;
        }

    }
    if (leftRight != moveLocation[0])
        return 1;
    return 0;
}

int board::squareMove(char pieceLocation[2], char moveLocation[2]) {
    int location = isSquareOccupied(pieceLocation);
    int positive = 0;
    if (pieceLocation[0] == moveLocation[1]) {
        //same number;
        if ((int) piecePointers[location]->pos[1] - 97 > (int) moveLocation[0] - 97)
            positive--;
        else
            positive++;
        for (int i = (int) piecePointers[location]->pos[1] - 97;
             i != (int) moveLocation[0] - 97; i = i + positive) {
            char testLocation[2];
            testLocation[1] = "abcedfgh"[i + positive];
            testLocation[0] = moveLocation[1];
            if (isSquareOccupied(testLocation) != 33 and testLocation[1] != moveLocation[0]) {
                return 1;
            } else if (piecePointers[location]->colour != piecePointers[isSquareOccupied(testLocation)]->colour and
                       testLocation[1] == moveLocation[0]) {
                int takePiece = isSquareOccupied(testLocation);
                piecePointers[takePiece]->pos[0] = '9';
                piecePointers[takePiece]->pos[1] = 'j';
                piecePointers[location]->pos[0] = moveLocation[1];
                piecePointers[location]->pos[1] = moveLocation[0];
                return 0;
            }

        }
        piecePointers[location]->pos[0] = moveLocation[1];
        piecePointers[location]->pos[1] = moveLocation[0];
        return 0;
    } else if (pieceLocation[1] == moveLocation[0]) {
        //Letters the same
        if ((int) piecePointers[location]->pos[0] - 48 > (int) moveLocation[1] - 48)
            positive = -1;
        else
            positive = 1;
        for (int i = (int) piecePointers[location]->pos[0] - 48;
             i != (int) moveLocation[1] - 48; i = i + positive) {
            char testLocation[2];
            if (positive == 1)
                testLocation[0] = "12345678"[i];
            else
                testLocation[0] = "12345678"[i - 2];
            testLocation[1] = moveLocation[0];
            if (isSquareOccupied(testLocation) != 33 and testLocation[0] != moveLocation[1]) {
                return 1;
            } else if (piecePointers[location]->colour != piecePointers[isSquareOccupied(testLocation)]->colour and
                       testLocation[0] == moveLocation[1]) {
                int takePiece = isSquareOccupied(testLocation);
                piecePointers[takePiece]->pos[0] = '9';
                piecePointers[takePiece]->pos[1] = 'j';
                piecePointers[location]->pos[0] = moveLocation[1];
                piecePointers[location]->pos[1] = moveLocation[0];
                return 0;
            }
        }
        piecePointers[location]->pos[0] = moveLocation[1];
        piecePointers[location]->pos[1] = moveLocation[0];
        return 0;
    }
    return 1;
}

