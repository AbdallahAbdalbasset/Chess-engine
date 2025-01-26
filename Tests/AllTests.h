#pragma once
#include "PawnTest.h"
#include "RookTest.h"
#include "BishopTest.h"
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

        // Run Bishop tests
        BishopTest bishopTest;
        bishopTest.runAllTests();

        cout<<"All tests done"<<endl;
    }
};