//
// Created by Stephen Cushen on 13/11/2019.
//

#ifndef LAB4_MOVES_H
#define LAB4_MOVES_H

class move {
public:
    move();

    ~move();

    char previousPosition[2];
    char currentPosition[2];
    char type;
    char colour;
    move *next;

    int addMove(char pos[2], char nextPos[2]);

    int counter;

};

#endif //LAB4_MOVES_H
