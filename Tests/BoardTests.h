#pragma once
#include "../Board/Board.h"
#include "../Helper/enum.h"
#include <iostream>

class BoardTest {
    public:
    void runAllTests(){
        void allKingMoves();
        void noKingMoves();
        void noUpRightMove();

        cout<<"Board tests done"<<endl;
    }

    void allKingMoves();
    void noKingMoves();
    void noUpRightMove();
};

void BoardTest::allKingMoves(){    
}

void BoardTest::noKingMoves(){
}

void BoardTest::noUpRightMove(){
}