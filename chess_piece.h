//
// Created by Stephen Cushen on 29/10/2019.
//

#ifndef LAB4_CHESS_PIECE_H
#define LAB4_CHESS_PIECE_H


class chess_piece {
public:
    chess_piece(char location[2]);

    ~chess_piece();

    char type;
    char pos[2];
    char colour;

    int move(char location[2]);

private:
    int pawnMove(char location[2]);

    int knightMove(char location[2]);

    int rookMove(char location[2]);
};

#endif //LAB4_CHESS_PIECE_H
