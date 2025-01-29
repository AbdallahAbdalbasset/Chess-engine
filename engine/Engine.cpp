#pragma once
#include "../Board/Board.cpp"
#include "Engine.h"
#include "../Helper/Helper.h"
#include <iostream>
using namespace std;

pair<pair<int,int>,pair<pair<int,int>,int>> Engine::getMove(Board board, Color color, int depth){

    if(depth == 2){
        int score = getScore(board);
        return {{-1,-1}, {{-1, -1}, score}};
    }

    pair<pair<int, int>, pair<pair<int, int>, int>> ret = {{-1,-1}, {{-1, -1}, 1e5}};
    if(color == Color::WHITE) ret.second.second = -1e5;

    for(int row=0;row<8;row++) {
        for(int col=0;col<8;col++) {
            if(board.board[row][col] == nullptr) continue;
            if(board.board[row][col]->color != color) continue;

            auto moves = board.board[row][col]->moves;

            for(pair<int, int> newPositoin:moves) {
                // Try this move
                Piece* targetPiece = board.board[newPositoin.first][newPositoin.second];
                board.board[newPositoin.first][newPositoin.second] = board.board[row][col];
                board.board[row][col] = nullptr;

                board.board[newPositoin.first][newPositoin.second]->position = newPositoin;
                board.prepareMoves();

                // Recursively call getMove for the opponent's turn
                auto tempRes = getMove(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE, depth + 1);
                

                if(color == Color::WHITE){
                    if(tempRes.second.second > ret.second.second) {
                        ret = tempRes;
                        ret.first = {row, col};
                        ret.second.first = newPositoin;
                    }
                }else {
                    if(tempRes.second.second < ret.second.second) {
                        ret = tempRes;
                        ret.first = {row, col};
                        ret.second.first = newPositoin;
                    }
                }

                if(ret.first.first == -1){
                    ret.first = {row, col};
                    ret.second.first = newPositoin;
                }

                board.board[row][col] = board.board[newPositoin.first][newPositoin.second];
                board.board[newPositoin.first][newPositoin.second] = targetPiece;

                board.board[row][col]->position = {row, col};
                board.prepareMoves();
            }
        }
    }

    return ret;
}

    
int Engine::getScore(Board &board){
    int score=0;
    for(int row=0;row<8;row++) {
        for(int col=0;col<8;col++) {
            if(board.board[row][col]==nullptr)continue;

            int value = board.board[row][col]->value;
            if(board.board[row][col]->color == Color::BLACK) value *= -1;
            score += value;
        }
    }

    return score;
}