#include "../Board/Board.h"
#include "Engine.h"
#include "../Helper/Helper.h"
#include <thread>
#include <memory>
#include <iostream>

using namespace std;
int Engine::maxDepth = 6;
int Engine::threadsCount = 4;
int Engine::maxValidMovesInChess = 1046;

pair<pair<int, int>, pair<pair<int, int>, int>> Engine::searchTakesOnly(Board board, Color color, int alpha, int beta, int depth){
    if(Helper::isCheck(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE)){
        return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? INT_MAX : INT_MIN}};
    }

    if(Helper::isCheckMate(board, color)){
        return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? INT_MIN+depth : INT_MAX-depth}};
    }

    pair<pair<int, int>, pair<pair<int, int>, int>> ret = {{-1,-1}, {{-1, -1}, getScore(board)}};

    int size = 0;
    vector<pair<int, pair<pair<int, int>, pair<int, int>>>> moves(maxValidMovesInChess);
    Helper::generateMoves(board, color, moves, size, threadsCount, depth, true); 

    if(color == Color::WHITE) alpha = max(alpha, ret.second.second);
    else beta = min(beta, ret.second.second);
    if(size == 0) return ret;

    // Divide the moves among threads
    int start = 0;
    int increment = 1;

    for(int i = start;i<size;i+=increment){
        int row = moves[i].second.first.first;
        int col = moves[i].second.first.second;
        pair<int, int> newPosition = moves[i].second.second;

        // Try this move
        shared_ptr<Piece> fromPiece = board.board[row][col];
        shared_ptr<Piece> toPiece = board.board[newPosition.first][newPosition.second];
        Helper::playMove(board, {row, col}, newPosition, fromPiece, nullptr);

        // Recursively call getMove for the opponent's turn
        auto tempRes = searchTakesOnly(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE, alpha, beta, depth+1);
                
        // Min-Max with Alpha-Beta pruning
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
        Helper::playMove(board, newPosition, {row, col}, fromPiece, toPiece);

        if(beta <= alpha) return ret;
    }
    
    return ret;

}
pair<pair<int, int>, pair<pair<int, int>, int>> Engine::search(Board board, Color color, int depth, int alpha, int beta, int threadId){

    if(Helper::isCheck(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE)){
        return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? INT_MAX : INT_MIN}};
    }

    if(Helper::isCheckMate(board, color)){
        return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? INT_MIN+depth : INT_MAX-depth}};
    }

    if(depth == maxDepth){
        return searchTakesOnly(board, color, alpha, beta, depth+1);
    }

    pair<pair<int, int>, pair<pair<int, int>, int>> ret = {{-1,-1}, {{-1, -1}, INT_MAX}};
    if(color == Color::WHITE) ret.second.second = INT_MIN;
    
    int size = 0;
    vector<pair<int, pair<pair<int, int>, pair<int, int>>>> moves(maxValidMovesInChess);
    Helper::generateMoves(board, color, moves, size, threadsCount, depth, false); 

    // Divide the moves among threads
    int start = 0;
    int increment = 1;
    
    if(depth == 0){
        start = threadId;
        increment = threadsCount;
    }

    for(int i = start;i<size;i+=increment){
        int row = moves[i].second.first.first;
        int col = moves[i].second.first.second;
        pair<int, int> newPosition = moves[i].second.second;

        // Try this move
        shared_ptr<Piece> fromPiece = board.board[row][col];
        shared_ptr<Piece> toPiece = board.board[newPosition.first][newPosition.second];
        Helper::playMove(board, {row, col}, newPosition, fromPiece, nullptr);

        // Recursively call getMove for the opponent's turn
        auto tempRes = search(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE, depth + 1, alpha, beta, threadId);
                
        // Min-Max with Alpha-Beta pruning
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
        Helper::playMove(board, newPosition, {row, col}, fromPiece, toPiece);

        if(beta <= alpha) return ret;
    }
    

    // If no legal moves, return stalemate
    if(ret.first.first == -1) ret.second.second = 0;
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

void Engine::prepareThreadMoves(int threadId, Board board, Color color, pair<pair<int, int>, pair<pair<int, int>, int>>& move){
    move = search(board, color, 0, INT_MIN, INT_MAX, threadId);
}

pair<pair<int, int>, pair<pair<int, int>, int>> Engine::getMove(Board board, Color color){
    //threadsCount = 1; // Single thread search

    // Multi-threaded search
    vector<unique_ptr<thread>> threads(threadsCount);
    vector<pair<pair<int, int>, pair<pair<int, int>, int>>> moves(threadsCount);
    for(int i=0;i<threadsCount;i++) {
        threads[i] = make_unique<thread>(prepareThreadMoves, i, Helper::copyBoard(board), color, ref(moves[i]));
    }

    for(int i = 0;i<threadsCount;i++){
        threads[i]->join();
    }
    
    pair<pair<int, int>, pair<pair<int, int>, int>> bestMove = {{-1, -1}, {{-1, -1}, INT_MIN}};
    if(color == Color::BLACK) bestMove.second.second = INT_MAX;

    if(Helper::isStalemate(moves))return bestMove;

    for(int i = 0;i<threadsCount;i++){
        if(moves[i].first.first == -1) continue;

        if(color == Color::WHITE && bestMove.second.second < moves[i].second.second){
            bestMove = moves[i];
        }
        if(color == Color::BLACK && bestMove.second.second > moves[i].second.second){
            bestMove = moves[i];
        }
    }
    
    return bestMove;
}