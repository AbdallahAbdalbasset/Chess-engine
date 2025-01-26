#pragma once
#include "PawnTest.h"
#include <iostream>

class AllTests{
    public:
    AllTests(){
        // Run Pawn tests
        PawnTest pt;
        pt.runAllTests();

        cout<<"All tests done"<<endl;
    }
};