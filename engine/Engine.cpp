#pragma once
#include "Board.h"
#include "Engine.h"
#include "Pieces/Headers/Pawn.h"
#include "Pieces/Headers/Rook.h"
#include "Pieces/Headers/Knight.h"
#include "Pieces/Headers/Bishop.h"
#include "Pieces/Headers/Queen.h"
#include "Pieces/Headers/King.h"
#include "../../../Helper/Helper.h"
#include <iomanip>
#include <iostream>
using namespace std;
pair<pair<int,int>,pair<pair<int,int>,int>> Engine::getMove(Board &board,Color color,int depth){
    // pair<pair<int,int>,pair<pair<int,int>,int>> mxTargetPoint;
    // int mxScore=0;
    int score=getScore(board);
    for(int row=0;row<8;row++)
    {
        for(int col=0;col<8;col++) {
            if (!isEmptySquare(board,row,col)&&
            !haveOpponentPiece(board,color,row,col))
            {
                for(auto po:board.board[row][col]->moves)
                {

                    // edit
                    Piece *targetPiece=board.board[po.first][po.second];
                    vector<pair<int,int>> previousMoves=board.board[row][col]->moves;
                    board.board[po.first][po.second] = board.board[row][col];
                    board.board[row][col] = nullptr;
                    board.board[po.first][po.second]->position=po;
                    board.board[po.first][po.second]->prepareMoves();
                    int score=getScore(board);
                    if(color==Color::WHITE)
                        score=max(score,getMove(board,color==Color::WHITE?Color::BLACK:Color::WHITE).second.second);
                    else 
                        score=min(score,getMove(board,color==Color::WHITE?Color::BLACK:Color::WHITE).second.second);
                    // return to intial state
                    board.board[row][col]=board.board[po.first][po.second];
                    board.board[po.first][po.second] = targetPiece;
                    board.board[row][col]->moves=previousMoves;
                    board.board[row][col]->position={row,col};
                }
            }
        }
    }
}
int Engine::getScore(Board &board){
    int score=0;
    for(int row=0;row<8;row++)
    {
        for(int col=0;col<8;col++) {
            if(board.board[row][col]==nullptr)continue;
            score+=(board.board[row][col]->color==Color::WHITE?board.board[row][col]->value:-board.board[row][col]->value)
        }
    }
    return score;
}