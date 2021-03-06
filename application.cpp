//
// Created by Stephen Cushen on 29/10/2019.
//

#include "application.h"
#include "board.h"
#include "move.h"
#include <iostream>
#include <string>

application::application() {

}

application::~application() {

}

//sample Game = a2a4b7b5a4b5g8f6e2e4f6e4f2f3a7a6f3e4a6b5a1a3a8a3e4e5a3f3g2f3h7h6f1b5h8h7b5a6c8a6b2b3e7e6b3b4d8h4f3f4h4h3g1h3

void application::run() {
    board playingBoard;
    playingBoard.printBoard();
    char pieceSelect[2];
    char pieceMove[2];
    char turn = 'w';
    int counter = 0;
    move *firstMove = new move;
    move *lastMove = firstMove;
    std::cout << "\nIt is now " << turn << "'s turn.";
    std::cout << "\nPlease select a piece: \t";
    std::cin >> pieceSelect[1];
    while (pieceSelect[1] != 'q' and pieceSelect[1] != 'Q') {
        if (pieceSelect[1] == 'l' or pieceSelect[1] == 'L') {
            while (pieceSelect[1] == 'L' or pieceSelect[1] == 'l') {
                printMoves(firstMove);
                std::cout << "\nPlease select a piece: \t";
                std::cin >> pieceSelect[1];
            }
        }
        if (pieceSelect[1] == 'r' or pieceSelect[1] == 'R') {
            deleteList(firstMove);
            run();
        }
        if (pieceSelect[1] == 'q' or pieceSelect[1] == 'Q') {
            exit(0);
        }
        std::cin >> pieceSelect[0];
        int pieceLocation = playingBoard.isSquareOccupied(pieceSelect);
        if (pieceLocation < 33 and playingBoard.piecePointers[pieceLocation]->colour == turn) {
            std::cout << "\nWhere do you want to move this piece to?\t";
            std::cin >> pieceMove[0] >> pieceMove[1];
            if (playingBoard.movePiece(pieceSelect, pieceMove) == 0) {
                turn = application::nextTurn(turn);
                move *nextMove = new move;
                nextMove->addMove(pieceSelect, pieceMove);
                nextMove->colour = turn;
                counter++;
                nextMove->counter = counter;
                lastMove->next = nextMove;
                lastMove = nextMove;
                std::cout << "\nIt is now " << turn << "'s Turn\n";
                playingBoard.printBoard();
            } else {
                std::cout << "\nIt is " << turn << "'s Turn\n Invalid Move\n";
                playingBoard.printBoard();
            }
        } else {
            std::cout << "\nPlease select a valid piece";
            std::cout << "\nIt is " << turn << "'s Turn\n";
            playingBoard.printBoard();
        }
        std::cout << "\nPlease select a piece: \t";
        std::cin >> pieceSelect[1];
    }
    exit(0);
}

char application::nextTurn(char turn) {
    if (turn == 'w')
        return 'b';
    else
        return 'w';
}

int application::test() {
    board playingBoard;
    char movePiece[2];
    char selectPiece[2];
    std::string moves = "a2a4b7b5a4b5g8f6e2e4f6e4f2f3a7a6f3e4a6b5a1a3a8a3e4e5a3f3g2f3h7h6f1b5h8h7b5a6c8a6b2b3e7e6b3b4d8h4f3f4h4h3g1h3";
    for (int i = 0; i < 108; i++) {
        selectPiece[1] = moves[i];
        i++;
        selectPiece[0] = moves[i];
        i++;
        movePiece[0] = moves[i];
        i++;
        movePiece[1] = moves[i];

        int error = playingBoard.movePiece(selectPiece, movePiece);
        if (error != 0) {
            std::cout << "Quitting...";
            return 1;
        }
    }
    return 0;
}


void application::printMoves(move *firstMove) {
    move *print = firstMove;
    if (print != nullptr) {
        print = print->next;
        std::cout << "\nThe first move was " << print->previousPosition[1] << print->previousPosition[0] << " to "
                  << print->currentPosition << std::endl;
        print = print->next;
    }
    while (print != nullptr) {
        std::cout << "The next move was " << print->previousPosition[1] << print->previousPosition[0] << " to "
                  << print->currentPosition << std::endl;
        print = print->next;
    }
}

void application::deleteList(move *firstMove) {
    move *currentElement = firstMove;
    while (currentElement != nullptr) {
        move *previousElement = currentElement;
        currentElement = currentElement->next;
        delete previousElement;
    }
}
