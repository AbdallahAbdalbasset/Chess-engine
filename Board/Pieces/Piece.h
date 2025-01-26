#pragma once
#include <iostream>
#include "../../Helper/enum.h"
class Board;

using namespace std;
class Piece {
    public:
    string name;
    pair<int, int> position;
    int value;
    Color color;
    vector<pair<int, int> > moves;

    virtual void prepareMoves(Board&)=0;

};
