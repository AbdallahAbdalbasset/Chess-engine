#pragma once
#include "PawnTest.h"
#include "RookTest.h"
#include <iostream>

class AllTests{
    public:
    AllTests(){
        // Run Pawn tests
        PawnTest pawnTest;
        pawnTest.runAllTests();

        // Run Rook tests
        RookTest rookTest;
        rookTest.runAllTests();

        cout<<"All tests done"<<endl;
    }
};