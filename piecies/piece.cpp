#include<iostream>
#include<vector>
#include "Board"
using namespace std;
class Piece{
    int value;
    pair<int,int> postion;
    vector<pair<int,int>> moves(Board board);
}