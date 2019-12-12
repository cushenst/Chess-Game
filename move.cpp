//
// Created by Stephen Cushen on 13/11/2019.
//
#include <iostream>
#include "move.h"

move::move() {
    this->next = nullptr;
}

move::~move() {
    std::cout << counter << std::endl;
}

int move::addMove(char pos[2], char posNext[2]) {
    currentPosition[0] = posNext[0];
    currentPosition[1] = posNext[1];
    previousPosition[0] = pos[0];
    previousPosition[1] = pos[1];
}
