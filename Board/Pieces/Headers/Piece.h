#pragma once
#include<iostream>
#include<vector>
#include "../../../Helper/enum.h"
using namespace std;

class Board;
class Piece {
    public:
    string name;
    pair<int, int> position;
    int value;
    Color color;
    vector<pair<int, int> > moves;
    virtual void prepareMoves(Board&)=0;
};
