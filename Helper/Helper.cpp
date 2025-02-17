#include "Helper.h"
#include "../Board/Board.h"
#include <iostream>
#include "../Board/Pieces/Headers/Piece.h"
#include "../Board/Pieces/Headers/Pawn.h"
#include "../Board/Pieces/Headers/Rook.h"
#include "../Board/Pieces/Headers/Knight.h"
#include "../Board/Pieces/Headers/Bishop.h"
#include "../Board/Pieces/Headers/Queen.h"
#include "../Board/Pieces/Headers/King.h"
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
                shared_ptr<Piece> fromPiece = board.board[row][col];
                shared_ptr<Piece> toPiece = board.board[newPosition.first][newPosition.second];
                Helper::playMove(board, {row, col}, newPosition, fromPiece, nullptr);

                if(!isCheck(board, color)) isNotcheckMate = true;

                // Undo this move
                Helper::playMove(board, newPosition, {row, col}, fromPiece, toPiece);

                if(isNotcheckMate) return false;
            }
        }
    }
    return true;
}

void Helper::playMove(Board& board, pair<int, int> from, pair<int, int> to, shared_ptr<Piece> fromPiece, shared_ptr<Piece> toPiece){    
    assert(isInBoard(from.first, from.second));
    assert(isInBoard(to.first, to.second));
    assert(board.board[from.first][from.second]!=nullptr);

    if(fromPiece) fromPiece->position = to;
    board.board[to.first][to.second] = fromPiece;
    
    if(toPiece) toPiece->position = from;
    board.board[from.first][from.second] = toPiece;

    if(fromPiece && (to.second == 0 || to.second == 7) && fromPiece->name == "P"){// Promotion
        board.board[to.first][to.second] = createQueen(fromPiece->color, fromPiece->position);
    }
    board.prepareMoves();
}

bool Helper::isValidMove(Board board, pair<int, int> to, Color color){
    // We should not take our own pieces
    if(board.board[to.first][to.second] != nullptr
    && board.board[to.first][to.second]->color == color)return false;

    return true;
}

shared_ptr<Piece> Helper::createPawn(Color color, pair<int, int> position){
    shared_ptr<Piece> pawn = make_shared<Pawn>();
    pawn->position = position;
    pawn->name = "P";
    pawn->value = 100;
    pawn->color = color;
    return pawn;
}  

shared_ptr<Piece> Helper::createRook(Color color, pair<int, int> position){
    shared_ptr<Piece> rook = make_shared<Rook>();
    rook->position = position;
    rook->name = "R";
    rook->value = 500;
    rook->color = color;
    return rook;
}

shared_ptr<Piece> Helper::createKnight(Color color, pair<int, int> position){
    shared_ptr<Piece> knight = make_shared<Knight>();
    knight->position = position;
    knight->name = "N";
    knight->value = 300;
    knight->color = color;
    return knight;
}

shared_ptr<Piece> Helper::createBishop(Color color, pair<int, int> position){
    shared_ptr<Piece> bishop = make_shared<Bishop>();
    bishop->position = position;
    bishop->name = "B";
    bishop->value = 300;
    bishop->color = color;
    return bishop;
}

shared_ptr<Piece> Helper::createQueen(Color color, pair<int, int> position){
    shared_ptr<Piece> queen = make_shared<Queen>();
    queen->position = position;
    queen->name = "Q";
    queen->value = 900;
    queen->color = color;
    return queen;
}

shared_ptr<Piece> Helper::createKing(Color color, pair<int, int> position){
    shared_ptr<Piece> king = make_shared<King>();
    king->position = position;
    king->name = "K";
    king->value = 0;
    king->color = color;
    return king;
}

Board Helper::copyBoard(Board board){
    Board copy;
    
    for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
            if(board.board[i][j]== nullptr) continue;

            string name = board.board[i][j]->name;  
            if(name == "P") copy.board[i][j] = Helper::createPawn(board.board[i][j]->color, {i, j});
            else if(name == "R") copy.board[i][j] = Helper::createRook(board.board[i][j]->color, {i, j});
            else if(name == "N") copy.board[i][j] = Helper::createKnight(board.board[i][j]->color, {i, j});
            else if(name == "B") copy.board[i][j] = Helper::createBishop(board.board[i][j]->color, {i, j});
            else if(name == "Q") copy.board[i][j] = Helper::createQueen(board.board[i][j]->color, {i, j});
            else if(name == "K") copy.board[i][j] = Helper::createKing(board.board[i][j]->color, {i, j});
        }
    }

    copy.prepareMoves();
    return copy;
}

bool Helper::isDraw(Board& board){
    for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
            if(board.board[i][j] == nullptr)continue;
            if(board.board[i][j]->name != "K")return false;
        }
    }

    return true;
}

bool Helper::isStalemate(vector<pair<pair<int, int>, pair<pair<int, int>, int>>> moves){
    moves.resize(unique(moves.begin(), moves.end()) - moves.begin());
    
    if(moves.size()!=1)return false;
    if(moves.front().first.first == -1)return true;
    return false;
}

void Helper::generateMoves(Board board, Color color, vector<pair<int, pair<pair<int, int>, pair<int, int>>>>& moves, int& size, int threadsCount, int depth, bool onlyTakes){
    pair<int, pair<pair<int, int>, pair<int, int>>> maxMove;
    maxMove.first = INT_MIN;

    if(isCheck(board, color)) onlyTakes = false;

    for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
            if(board.board[i][j] == nullptr) continue;
            if(board.board[i][j]->color != color) continue;

            for(auto newPosition : board.board[i][j]->moves){
                if(!Helper::isValidMove(board, newPosition, color)) continue;
                if(onlyTakes && board.board[newPosition.first][newPosition.second] == nullptr) continue;

                moves[size++] = {0, {{i, j}, newPosition}};

                if(board.board[newPosition.first][newPosition.second] == nullptr) continue;
                moves[size-1].first = max(1, board.board[newPosition.first][newPosition.second]->value + 1 - board.board[i][j]->value);
                maxMove = max(maxMove, moves[size - 1]);
            }
        }
    }

    int temp = threadsCount - 1;
    while(!depth&&temp--&&maxMove.first !=  INT_MIN){
        moves[size++] = maxMove;
    }

    sort(moves.begin(), moves.begin()+size, greater<pair<int, pair<pair<int, int>, pair<int, int>>>>());
}