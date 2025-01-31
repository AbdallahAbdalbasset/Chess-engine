#include "../Board/Board.h"
#include "Engine.h"
#include "../Helper/Helper.h"
#include <iostream>

using namespace std;

pair<pair<int,int>,pair<pair<int,int>,int>> Engine::getMove(Board board, Color color, int depth){

    if(Helper::isCheck(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE)){
        return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? 2e9 : -2e9}};
    }

    if(Helper::isCheckMate(board, color)){
        return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? (-1e9)+depth : 1e9-depth}};
    }
    
    if(depth == 4){
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

            for(pair<int, int> newPosition:moves) {
                // We chould not take our own pieces
                if(board.board[newPosition.first][newPosition.second]!=nullptr
                && board.board[newPosition.first][newPosition.second]->color == color)continue;

                // We chould not take the king
                if(board.board[newPosition.first][newPosition.second]!=nullptr
                && board.board[newPosition.first][newPosition.second]->name == "K")continue;

                // Try this move
                Piece* targetPiece = board.board[newPosition.first][newPosition.second];
                board.board[newPosition.first][newPosition.second] = board.board[row][col];
                board.board[row][col] = nullptr;

                board.board[newPosition.first][newPosition.second]->position = newPosition;
                board.prepareMoves();

                // Recursively call getMove for the opponent's turn
                auto tempRes = getMove(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE, depth + 1);
                

                if(color == Color::WHITE){
                    if(tempRes.second.second >= ret.second.second) {
                        ret = tempRes;
                        ret.first = {row, col};
                        ret.second.first = newPosition;
                    }
                }else {
                    if(tempRes.second.second <= ret.second.second) {
                        ret = tempRes;
                        ret.first = {row, col};
                        ret.second.first = newPosition;
                    }
                }

                if(ret.first.first == -1){
                    ret.first = {row, col};
                    ret.second.first = newPosition;
                }

                board.board[row][col] = board.board[newPosition.first][newPosition.second];
                board.board[newPosition.first][newPosition.second] = targetPiece;

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