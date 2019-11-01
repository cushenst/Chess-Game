//
// Created by Stephen Cushen on 29/10/2019.
//
#pragma once
#ifndef LAB4_APPLICATION_H
#define LAB4_APPLICATION_H

#include "board.h"

class application {
public:
    application();

    ~application();

    void run();

private:
    char nextTurn(char turn);
};


#endif //LAB4_APPLICATION_H
