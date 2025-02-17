#pragma once
#include "KingTest.h"
#include "PawnTest.h"
#include "RookTest.h"
#include "BishopTest.h"
#include "QueenTest.h"
#include "KnightTest.h"
#include "KingTest.h"
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

        // Run Queen tests
        QueenTest queenTest;
        queenTest.runAllTests();

        // Run Knight tests
        KnightTest knightTest;
        knightTest.runAllTests();

        // Run King tests
        KingTest kingTest;
        kingTest.runAllTests();
        
        cout<<"All tests done"<<endl;
    }
};