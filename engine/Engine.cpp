#include "../Board/Board.h"
#include "Engine.h"
#include "../Helper/Helper.h"
#include <iostream>

using namespace std;

pair<pair<int, int>, pair<pair<int, int>, int>> Engine::getMove(Board board, Color color, int depth, int alpha, int beta){

    if(Helper::isCheck(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE)){
        return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? INT_MAX : INT_MIN}};
    }

    if(Helper::isCheckMate(board, color)){
        return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? INT_MIN+depth : INT_MAX-depth}};
    }

    if(depth == 4){
        int score = getScore(board);
        return {{-1, -1}, {{-1, -1}, score}};
    }

    pair<pair<int, int>, pair<pair<int, int>, int>> ret = {{-1,-1}, {{-1, -1}, INT_MAX}};
    if(color == Color::WHITE) ret.second.second = INT_MIN;

    for(int row=0;row<8;row++) {
        for(int col=0;col<8;col++) {
            if(board.board[row][col] == nullptr) continue;
            if(board.board[row][col]->color != color) continue;

            auto moves = board.board[row][col]->moves;
            for(pair<int, int> newPosition : moves) {
                if(!Helper::isValidMove(board, newPosition, color)) continue;

                // Try this move
                Piece* targetPiece = board.board[newPosition.first][newPosition.second];
                Helper::playMove(board, {row, col}, newPosition, nullptr);

                // Recursively call getMove for the opponent's turn
                auto tempRes = getMove(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE, depth + 1, alpha, beta);
                
                // Min-Max with alpha-beta pruning
                if(color == Color::WHITE){
                    if(tempRes.second.second > ret.second.second) {
                        ret = tempRes;
                        ret.first = {row, col};
                        ret.second.first = newPosition;
                        alpha = max(alpha, ret.second.second);
                    }
                    
                }else {
                    if(tempRes.second.second < ret.second.second) {
                        ret = tempRes;
                        ret.first = {row, col};
                        ret.second.first = newPosition;
                        beta = min(beta, ret.second.second);
                    }
                }
                
                // Undo this move
                Helper::playMove(board, newPosition, {row, col}, targetPiece);

                if(beta < alpha) return ret;
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