#include <iostream>
#include <vector>
#include <stack>
#include "../Board/Board.h"
#include <assert.h>

using namespace std;

class DataStore{
    private:
    vector<stack<vector<pair<pair<int, int>, vector<pair<int, int>>>>>> Data;
    
    public:
    DataStore(int threadsCount){
        Data.resize(threadsCount);
    }

    void push(Board& board, int threadId){
        if(threadId == 100) return;// Real move - can not be undo

        vector<pair<pair<int, int>, vector<pair<int, int>>>> boardMoves;
        for(int i = 0;i<8;i++){
            for(int j = 0;j<8;j++){
                if(board.board[i][j] == nullptr) continue;
                boardMoves.push_back({{i, j}, board.board[i][j]->moves});
            }
        }

        Data[threadId].push(boardMoves);
    }

    void pop(Board& board, int threadId){

        for(auto& i: Data[threadId].top()){
            assert(board.board[i.first.first][i.first.second] != nullptr);
            board.board[i.first.first][i.first.second]->moves = i.second;
        }

        Data[threadId].pop();

    }
};