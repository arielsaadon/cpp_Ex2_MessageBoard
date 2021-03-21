#include "Board.hpp"

#include <iostream>
#include <string>

using namespace std;
using namespace ariel;

void Board::post(unsigned int row, unsigned int col, Direction direction, const string &massage){
    unsigned int tCol = col;
    unsigned int tRow = row;
    if (tCol < minCol){
        minCol = tCol;
    }
    for (unsigned int i = 0; i < massage.size(); i++){
        if (direction == Direction::Horizontal){
            board[row][col + i] = massage[i];
            tCol = col + i;
        }
        else if (direction == Direction::Vertical){
            board[row + i][col] = massage[i];
            tRow = row + i;
        }
    }
    if (tRow > maxRow){
        maxRow = tRow;
    }
    if (tCol > maxCol){
        maxCol = tCol;
    }
}

string Board::read(unsigned int row, unsigned int col, Direction direction, unsigned int len){
    string readOnBoard;
    if (direction == Direction::Horizontal){
        for (unsigned int i = col; i < col + len; i++){
            if (board.count(row) != 0 && board[row].count(i) != 0){
                readOnBoard += board[row][i];
            }
            else{
                readOnBoard += '_';
            }
        }
    }
    else{
        for (unsigned int i = row; i < row + len; i++){
            if (board.count(i) != 0 && board[i].count(col) != 0){
                readOnBoard += board[i][col];
            }
            else{
                readOnBoard += '_';
            }
        }
    }
    return readOnBoard;
}

void Board::show(){
    for (int i = 0; i <= to_string(maxRow).size() + 1; i++){
        cout << " ";
    }
    addLines(minCol, maxCol + 1);
    cout << endl;

    unsigned int tempCol = 0;
    unsigned int tempRow = 0;
    for (auto &i : board){
        tempCol = minCol;
        tempRow = i.first;
        for (int k = 0; k < to_string(maxRow).size() - to_string(tempRow).size(); k++){
            cout << " ";
        }
        cout << tempRow << ":"
             << "|";
        for (auto &j : i.second){
            if (j.first > tempCol){
                addLines(tempCol, j.first);
                tempCol = j.first + 1;
            }
            else if (j.first < tempCol){
                addLines(j.first, tempCol);
            }
            else{
                tempCol++;
            }
            cout << j.second;
        }
        if (tempCol != maxCol + 1){
            addLines(tempCol - 1, maxCol);
        }
        cout << "|" << endl;
    }
}

void Board::addLines(unsigned int first, unsigned int maxPos){
    for (unsigned int i = first; i < maxPos; i++){
        cout << "_";
    }
}