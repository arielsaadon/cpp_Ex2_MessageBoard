#pragma once
#include "Direction.hpp"
#include <string>
#include <limits>
#include <map>

namespace ariel {
    class Board{
        std::map<unsigned int,std::map<unsigned int,char>> board;
        unsigned int maxRow, maxCol ,minCol;

        static void addLines(unsigned int first, unsigned int maxPos);
    public:
        Board(): board(),maxRow(0),maxCol(0),minCol(std::numeric_limits<unsigned int>::max()){}
        ~Board()= default;
        void post(unsigned int row,unsigned int col, Direction direction, const std::string& massage);
        std::string read(unsigned int row,unsigned int col, Direction direction,unsigned int len);
        void show();
    };
}