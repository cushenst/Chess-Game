//
// Created by Stephen Cushen on 29/10/2019.
//

#include "application.h"
#include "board.h"
#include <iostream>

application::application() {

}

application::~application() {

}

//sample Game = a2a4b7b5a4b5g8f6e2e4f6e4f2f3a7a6f3e4a6b5a1a3a8a3e4e5a3f3g2f3h7h6f1b5h8h7b5a6c8a6b2b3e7e6b3b4d8h4f3f4h4h3

void application::run() {
    board playingBoard;
    playingBoard.printBoard();
    char pieceSelect[2];
    char pieceMove[2];
    char turn = 'w';
    std::cout << "\nIt is now " << turn << "'s turn.";
    std::cout << "\nPlease select a piece: \t";
    std::cin >> pieceSelect[1];
    while (pieceSelect[1] != 'q' and pieceSelect[1] != 'Q') {
        if (pieceSelect[1] == 'r' or pieceSelect[1] == 'R') {
            run();
        }
        std::cin >> pieceSelect[0];
        int pieceLocation = playingBoard.isSquareOccupied(pieceSelect);
        if (pieceLocation < 33 and playingBoard.piecePointers[pieceLocation]->colour == turn) {
            std::cout << "\nWhere do you want to move this piece to?\t";
            std::cin >> pieceMove[0] >> pieceMove[1];
            if (playingBoard.movePiece(pieceSelect, pieceMove) == 0) {
                turn = application::nextTurn(turn);
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
}

char application::nextTurn(char turn) {
    if (turn == 'w')
        return 'b';
    else
        return 'w';
}