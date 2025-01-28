#include "Tests/AllTests.h"
#include "Board/Board.cpp"
#include <iostream>
using namespace std;


int main(){
    AllTests allTests;

    Board board;
    board.initializeBoard();
    board.printBoard();
    return 0;
}