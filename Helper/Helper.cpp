#include "Helper.h"
#include "../Board/Board.h"

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
                if(board.board[newPositoin.first][newPositoin.second] == nullptr) continue;
                if(board.board[newPositoin.first][newPositoin.second]->color == color) continue;
                if(board.board[newPositoin.first][newPositoin.second]->name=="K")
                    return true;
            }
        }
    }
    return false;
}
bool Helper::isCheckMate(Board board, Color color){
    // first get all pieces attack the king 
    // then for each attack looking for piece being set as a block
    if(!isCheck(board, color))return false;

    for(int row=0;row<8;row++){
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

                if(!isCheck(board, color))return false;

                // Undo this move
                board.board[row][col] = board.board[newPositoin.first][newPositoin.second];
                board.board[newPositoin.first][newPositoin.second] = targetPiece;

                board.board[row][col]->position = {row, col};
                board.prepareMoves();
            }
        }
    }
    return true;
}

void Helper::playMove(Board& board, pair<int, int> from, pair<int, int> to){    
    board.board[to.first][to.second] = board.board[from.first][from.second];
    board.board[from.first][from.second] = nullptr;

    board.board[to.first][to.second]->position = to;
    board.prepareMoves();
}