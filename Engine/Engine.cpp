#include "../Board/Board.h"
#include "Engine.h"
#include "../Helper/Helper.h"
#include <thread>
#include <memory>
#include "../Helper/enum.h"
#include <iostream>

using namespace std;
int Engine::maxDepth = 4;
int Engine::threadsCount = 4;
int Engine::maxValidMovesInChess = 1046;

pair<pair<int, int>, pair<pair<int, int>, int>> Engine::searchTakesOnly(Board board, Color color, int alpha, int beta, int depth, int threadId){
     if(Helper::isCheck(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE)){
         return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? INT_MAX : INT_MIN}};
     }

     if(Helper::isCheckMate(board, color, threadId)){
         return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? INT_MIN+depth : INT_MAX-depth}};
     }

    pair<pair<int, int>, pair<pair<int, int>, int>> ret = {{-1,-1}, {{-1, -1}, getScore(board)}};

    int size = 0;
    vector<pair<int, pair<pair<int, int>, pair<int, int>>>> moves(maxValidMovesInChess);
    Helper::generateMoves(board, color, moves, size, threadsCount, depth, true); 

    if(Helper::isCheck(board, color)){
        if(color == Color::WHITE) ret.second.second = INT_MIN;
        else ret.second.second = INT_MAX;
    }

    if(color == Color::WHITE) alpha = max(alpha, ret.second.second);
    else beta = min(beta, ret.second.second);
    if(size == 0) return ret;

    int start = 0;
    int increment = 1;
    for(int i = start;i<size;i+=increment){
        int row = moves[i].second.first.first;
        int col = moves[i].second.first.second;
        pair<int, int> newPosition = moves[i].second.second;

        // Try this move
        shared_ptr<Piece> fromPiece = board.board[row][col];
        shared_ptr<Piece> toPiece = board.board[newPosition.first][newPosition.second];
        vector<bool> casleData = {board.whiteKingSideCasle, board.whiteQueenSideCasle, board.blackKingSideCasle, board.blackQueenSideCasle};
        Helper::playMove(board, color, {row, col}, newPosition, fromPiece, nullptr, threadId);
        
        // Recursively call getMove for the opponent's turn
        auto tempRes = searchTakesOnly(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE, alpha, beta, depth+1, threadId);
                
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
        Helper::unPlayMove(board, color, newPosition, {row, col}, fromPiece, toPiece, casleData, threadId);

        if(beta <= alpha) return ret;
    }
    
    return ret;

}
pair<pair<int, int>, pair<pair<int, int>, int>> Engine::search(Board board, Color color, int depth, int alpha, int beta, int threadId){

    if(Helper::isCheck(board, (color == Color::WHITE) ? Color::BLACK : Color::WHITE)){
        return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? INT_MAX : INT_MIN}};
    }

    if(Helper::isCheckMate(board, color, threadId)){
        return {{-1, -1}, {{-1, -1}, color == Color::WHITE ? INT_MIN+depth : INT_MAX-depth}};
    }

    if(depth == maxDepth){
        return searchTakesOnly(board, color, alpha, beta, depth+1, threadId);
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
        
        bool isPawn = false;
        shared_ptr<Piece> fromPiece;
        shared_ptr<Piece> toPiece;
        vector<bool> casleData = {board.whiteKingSideCasle, board.whiteQueenSideCasle, board.blackKingSideCasle, board.blackQueenSideCasle};
        if(Helper::isInBoard(row, col)&&board.board[row][col]!=nullptr){
            isPawn = board.board[row][col]->name == "P"?true:false;
            fromPiece = board.board[row][col];
            toPiece = board.board[newPosition.first][newPosition.second];
        }
        
        // Try this move
        Helper::playMove(board, color, {row, col}, newPosition, fromPiece, nullptr, threadId);

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
                
        // Pawn promotion in nearset move
        if(tempRes.second.second == ret.second.second){            
            if(((color == Color::WHITE && col == 6) || (color == Color::BLACK && col == 1)
                )&& isPawn){
                ret = tempRes;
                ret.first = {row, col};
                ret.second.first = newPosition;
            }
        }

        // Undo this move
        Helper::unPlayMove(board, color, newPosition, {row, col}, fromPiece, toPiece, casleData, threadId);

        if(beta <= alpha) return ret;
    }
    

    // If no legal moves, return stalemate
    if(ret.second.first.first == -1) ret.second.second = 0;
    return ret;
}

int Engine::getScore(Board &board){
    int score=0;

    int whiteMaterial = 0;
    int blackMaterial = 0;
    pair<int, int> whiteKingPosition, blackKingPosition;
    for(int row=0;row<8;row++) {
        for(int col=0;col<8;col++) {
            if(board.board[row][col]==nullptr)continue;

            int value = board.board[row][col]->getValue();
            if(board.board[row][col]->color == Color::BLACK) {
                value *= -1;
                blackMaterial += board.board[row][col]->value;
                if(board.board[row][col]->name == "K") blackKingPosition = {row, col};
            }else{
                whiteMaterial += board.board[row][col]->value;
                if(board.board[row][col]->name == "K") whiteKingPosition = {row, col};
            }
            score += value;


        }
    }

    if(blackMaterial-whiteMaterial > 500){
        int kingValue = min(7 - whiteKingPosition.first, whiteKingPosition.first);
        kingValue += min(7 - whiteKingPosition.second, whiteKingPosition.second);
        int dist = abs(whiteKingPosition.first - blackKingPosition.first);
        dist += abs(whiteKingPosition.second - blackKingPosition.second);
        kingValue += dist;
        kingValue = kingValue*800/28;

        if(whiteKingPosition.first == blackKingPosition.first) kingValue += 50;
        if(whiteKingPosition.second == blackKingPosition.second) kingValue += 50;

        score += kingValue;
    }
    if(whiteMaterial-blackMaterial > 500){
        int kingValue = min(7 - blackKingPosition.first, blackKingPosition.first);
        kingValue += min(7 - blackKingPosition.second, blackKingPosition.second);
        int dist = abs(whiteKingPosition.first - blackKingPosition.first);
        dist += abs(whiteKingPosition.second - blackKingPosition.second);
    
        kingValue += dist;
        kingValue = kingValue*800/28;
        if(whiteKingPosition.first == blackKingPosition.first) kingValue += 50;
        if(whiteKingPosition.second == blackKingPosition.second) kingValue += 50;
        
        kingValue = -kingValue;
        score += kingValue;
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
        
        if(moves[i].second.first.first == -1) continue;

        if(color == Color::WHITE && bestMove.second.second < moves[i].second.second){
            bestMove = moves[i];
        }
        if(color == Color::BLACK && bestMove.second.second > moves[i].second.second){
            bestMove = moves[i];
        }

        if(moves[i].second.first.first != -1 && moves[i] != bestMove && moves[i].second.second == bestMove.second.second){
            if(((color == Color::WHITE && moves[i].first.second == 6) || (color == Color::BLACK && moves[i].first.second == 1)) && board.board[moves[i].first.first][moves[i].first.second]->name == "P")
                bestMove = moves[i];
        }
    }
    
    return bestMove;
}
