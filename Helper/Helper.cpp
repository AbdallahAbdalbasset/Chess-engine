#include "Helper.h"
#include "../Board/Board.h"
#include <iostream>
#include "../Board/Pieces/Headers/Piece.h"
#include "enum.h"

using namespace std;
bool Helper::isInBoard(int i, int j){
    return (i>=0 && i<8 && j>=0 && j<8);
}

bool Helper::isEmptySquare(Board& board, int i, int j){
    if(!isInBoard(i, j)) return false;
    return board.board[i][j] == nullptr;
}

bool Helper::haveOpponentPiece(Board& board, Color color, int i, int j){
    if(!isInBoard(i, j) || isEmptySquare(board, i, j)) return false;
    return board.board[i][j]->color != color;
}

bool Helper::isCheck(Board& board, Color color){
    for(int row=0;row<8;row++){
        for(int col=0;col<8;col++) {
            if(board.board[row][col] == nullptr) continue;
            if(board.board[row][col]->color == color) continue;
            for(auto newPositoin:board.board[row][col]->moves){
                if(!Helper::isInBoard(newPositoin.first, newPositoin.second))continue;
                if(board.board[newPositoin.first][newPositoin.second] == nullptr) continue;
                if(board.board[newPositoin.first][newPositoin.second]->color != color) continue;
                if(board.board[newPositoin.first][newPositoin.second]->name=="K") return true;
            }
        }
    }
    return false;
}
bool Helper::isCheckMate(Board board, Color color){
    // first get all pieces attack the king 
    // then for each attack looking for piece being set as a block
    if(!isCheck(board, color))return false;
    
    bool isNotcheckMate = false;
    for(int row=0;row<8;row++){
        for(int col=0;col<8;col++) {
            if(board.board[row][col] == nullptr) continue;
            if(board.board[row][col]->color != color) continue;
            
            auto moves = board.board[row][col]->moves;
            for(pair<int, int> newPosition:moves) {

                if(!isValidMove(board, newPosition, color))continue;

                // Try this move
                Piece* targetPiece = board.board[newPosition.first][newPosition.second];
                playMove(board, {row, col}, newPosition, targetPiece);

                if(!isCheck(board, color)) isNotcheckMate = true;

                // Undo this move
                playMove(board, newPosition, {row, col}, targetPiece);

                if(isNotcheckMate) return false;
            }
        }
    }
    return true;
}

void Helper::playMove(Board& board, pair<int, int> from, pair<int, int> to, Piece* targetPiece){    
    assert(isInBoard(from.first, from.second));
    assert(isInBoard(to.first, to.second));
    assert(board.board[from.first][from.second]!=nullptr);

    board.board[to.first][to.second] = board.board[from.first][from.second];
    board.board[from.first][from.second] = nullptr;

    board.board[to.first][to.second]->position = to;
    board.board[from.first][from.second] = targetPiece;
    board.prepareMoves();
}

bool Helper::isValidMove(Board board, pair<int, int> to, Color color){
    // We chould not take our own pieces
    if(board.board[to.first][to.second] != nullptr
    && board.board[to.first][to.second]->color == color)return false;

    // We chould not take the king
    if(board.board[to.first][to.second]!=nullptr
    && board.board[to.first][to.second]->name == "K")return false;

    return true;
}