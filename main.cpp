#include "Tests/AllTests.h"
#include "Board/Board.cpp"
#include "Engine/Engine.cpp"
#include <iostream>
using namespace std;


int main(){
    Board board;
    board.initializeBoard();
    board.board[3][1] = nullptr;
    board.board[3][6] = nullptr;
    board.board[3][4] = board.board[3][7];
    board.board[3][7] = nullptr;

    board.prepareMoves();

    board.printBoard();

    auto ret = Engine::getMove(board, Color::WHITE, 0);
    board.board[ret.second.first.first][ret.second.first.second] = board.board[ret.first.first][ret.first.second];
    board.board[ret.first.first][ret.first.second] = nullptr;

    board.printBoard();

    cout<< "From " << ret.first.first << " " << ret.first.second << endl;
    cout<< "To " << ret.second.first.first << " " << ret.second.first.second << endl;
    cout<< "Score " << ret.second.second << endl;

    return 0;
}