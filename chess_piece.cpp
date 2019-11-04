//
// Created by Stephen Cushen on 29/10/2019.
//

#include "chess_piece.h"
#include <iostream>

using namespace std;

chess_piece::chess_piece(char location[2]) {
    pos[0] = location[0];
    pos[1] = location[1];
    if ((int) pos[0] - 48 < 3)
        colour = 'w';
    else if ((int) pos[0] - 48 > 6)
        colour = 'b';
    if (pos[0] == '2' | pos[0] == '7') {
        type = 'p';
    } else if (pos[0] == '1' | pos[0] == '8') {
        if (pos[1] == 'a' | pos[1] == 'h') {
            type = 'r';
        } else if (pos[1] == 'b' | pos[1] == 'g') {
            type = 'n';
        } else if (pos[1] == 'c' | pos[1] == 'f') {
            type = 'b';
        } else if (pos[1] == 'd') {
            type = 'q';
        } else if (pos[1] == 'e') {
            type = 'k';
        }
    } else if (pos[0] == '3' | pos[0] == '4' | pos[0] == '5' | pos[0] == '6') {
        type = 45;
    }
}

chess_piece::~chess_piece() {

}

int chess_piece::move(char location[2]) {
    int returnValue = 0;
    if (type == 'p') {
        returnValue = pawnMove(location);
    } else if (type == 'n') {
        returnValue = knightMove(location);
    } else if (type == 'r') {
        returnValue = rookMove(location);
    }
    return returnValue;
}

int chess_piece::pawnMove(char location[2]) {
    int rowToMove = (int) location[1] - 48;
    if (pos[0] == '2' or pos[0] == '7') {
        if (((rowToMove == 4 or rowToMove == 3) and colour == 'w') or
            ((rowToMove == 5 or rowToMove == 6) and colour == 'b')) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if (((int) pos[0] - 47 == rowToMove and colour == 'w') or ((int) pos[0] - 49 == rowToMove and colour == 'b')) {
            return 0;
        } else {
            return 1;
        }
    }

}


int chess_piece::knightMove(char location[2]) {
    if (((int) pos[1] - 97 + 2 == (int) location[0] - 97 or (int) pos[1] - 97 - 2 == (int) location[0] - 97) and
        ((int) pos[0] - 48 + 1 == (int) location[1] - 48 or (int) pos[0] - 48 - 1 == (int) location[1] - 48)) {
        return 0;
    } else if (((int) pos[1] - 97 + 1 == (int) location[0] - 97 or (int) pos[1] - 97 - 1 == (int) location[0] - 97) and
               ((int) pos[0] - 48 + 2 == (int) location[1] - 48 or (int) pos[0] - 48 - 2 == (int) location[1] - 48))
        return 0;
    else
        return 1;
}

//pos[0] = number
//pos[1] = letter
//location[0] = letter
//location[1] = number

int chess_piece::rookMove(char location[2]) {
    if (pos[0] == location[1] or pos[1] == location[0]) {
        return 0;
    } else
        return 1;
}





