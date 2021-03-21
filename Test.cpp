#include "doctest.h"
#include "Board.hpp"

using namespace ariel;
using namespace std;

TEST_CASE("Read Before Post"){
    Board board;
            CHECK(board.read(0, 0, Direction::Horizontal, 0) == "");
            CHECK(board.read(0, 0, Direction::Vertical, 0) == "");
            CHECK(board.read(5, 7, Direction::Horizontal, 1) == "_");
            CHECK(board.read(10, 20, Direction::Horizontal, 6) == "______");
            CHECK(board.read(10, 20, Direction::Vertical, 6) == "______");
}

TEST_CASE("Post and Read"){
    Board board;
    /**
     * 4:______
     * 5:abcd__
     * 6:______
     */
    board.post(5,5,Direction::Horizontal,"abcd");
    //Horizontal
            CHECK(board.read(5, 5, Direction::Horizontal, 4) == "abcd");
            CHECK(board.read(5, 4, Direction::Horizontal, 4) == "_abc");
            CHECK(board.read(5, 3, Direction::Horizontal, 4) == "__ab");
            CHECK(board.read(5, 2, Direction::Horizontal, 4) == "___a");
            CHECK(board.read(5, 1, Direction::Horizontal, 4) == "____");
    //Vertical
            CHECK(board.read(5, 5, Direction::Vertical, 4) == "a___");
            CHECK(board.read(4, 5, Direction::Vertical, 4) == "_a__");
            CHECK(board.read(3, 5, Direction::Vertical, 4) == "__a_");
            CHECK(board.read(2, 5, Direction::Vertical, 4) == "___a");
            CHECK(board.read(5, 6, Direction::Vertical, 4) == "b___");
            CHECK(board.read(5, 7, Direction::Vertical, 4) == "c___");
            CHECK(board.read(5, 8, Direction::Vertical, 4) == "d___");
}

TEST_CASE("Post on Post"){
    Board board;
    /**
     * 4:____  4:_b__  4:_:__  4:_:y_  4:_:y_
     * 5:abcd->5:accd->5:agcd->5:agjd->5:hfgk
     * 6:____  6:_i__  6:_h__  6:_h<_  6:_h<_
     */
    board.post(5,5,Direction::Horizontal,"abcd");
            CHECK(board.read(5, 5, Direction::Horizontal, 4) == "abcd");
    board.post(4,6,Direction::Vertical,"bci");
            CHECK(board.read(4, 6, Direction::Vertical, 3) == "bci");
            CHECK(board.read(4, 6, Direction::Vertical, 5) == "bci__");
    board.post(4,6,Direction::Vertical,":gh");
            CHECK(board.read(4, 6, Direction::Vertical, 3) == ":gh");
    board.post(4,7,Direction::Vertical,"yj<");
            CHECK(board.read(4, 7, Direction::Vertical, 3) == "yj<");
            CHECK(board.read(4, 5, Direction::Horizontal, 4) == "_:y_");
            CHECK(board.read(5, 5, Direction::Horizontal, 4) == "agjd");
            CHECK(board.read(6, 5, Direction::Horizontal, 4) == "_h<_");
    board.post(5,5,Direction::Horizontal,"hfgk");
            CHECK(board.read(5, 5, Direction::Horizontal, 4) == "hfgk");
            CHECK(board.read(4, 5, Direction::Vertical, 3) == "_h_");
            CHECK(board.read(4, 6, Direction::Vertical, 3) == ":fh");
            CHECK(board.read(4, 7, Direction::Vertical, 3) == "yg<");
            CHECK(board.read(4, 8, Direction::Vertical, 3) == "_k_");
}

TEST_CASE("Special Characters") {
    Board board;
    /**
    * 9:__________
    *10:abbc ddt__
    *11:*bbc ddt__
    *12:*@!# $%^&
    *13:(bn& {+|?=
    *14:0506984634
    */
    //Horizontal
    board.post(10,20,Direction::Horizontal,"abbc ddt");
            CHECK(board.read(10, 20, Direction::Horizontal, 8) != "abbc_ddt");
            CHECK(board.read(10, 20, Direction::Horizontal, 8) == "abbc ddt");
    board.post(11,20,Direction::Horizontal,"*bbc ddt");
            CHECK(board.read(11, 20, Direction::Horizontal, 8) == "*bbc ddt");
    board.post(12,20,Direction::Horizontal,"*@!# $%^&");
            CHECK(board.read(12, 20, Direction::Horizontal, 9) == "*@!# $%^&");
            CHECK(board.read(12, 19, Direction::Horizontal, 9) == "_*@!# $%^");
    board.post(13,20,Direction::Horizontal,"(bn& {+|?=");
            CHECK(board.read(13, 20, Direction::Horizontal, 10) == "(bn& {+|?=");
    board.post(14,20,Direction::Horizontal,"0506984634");
            CHECK(board.read(14, 20, Direction::Horizontal, 10) == "0506984634");

    //Vertical
            CHECK(board.read(9, 20, Direction::Vertical, 6) == "_a**(0");
            CHECK(board.read(9, 21, Direction::Vertical, 6) == "_bb@b5");
            CHECK(board.read(10, 22, Direction::Vertical, 6) == "bb!n0_");
            CHECK(board.read(9, 24, Direction::Vertical, 6) == "_    9");
            CHECK(board.read(10, 24, Direction::Vertical, 6) == "    9_");
}

TEST_CASE("Post and Read in big numbers"){
    Board board;
    Board board1;
     //index one million +-
    board.post(999999, 1000000, Direction::Vertical, "abcd");
            CHECK(board.read(999999, 1000000, Direction::Vertical, 4) == "abcd");
            CHECK(board.read(999999, 1000001, Direction::Vertical, 4) == "____");
    board.post(1000000, 1000000, Direction::Horizontal, "kht jkl");
    board.post(1000001, 1000000, Direction::Horizontal, "cc;fr");
            CHECK(board.read(999999, 1000000, Direction::Vertical, 4) == "akcd");
            CHECK(board.read(999999, 1000001, Direction::Vertical, 4) == "_hc_");
            CHECK(board.read(999999, 1000003, Direction::Vertical, 5) == "_ f__");
            CHECK(board.read(1000000, 1000002, Direction::Horizontal, 5) == "t jkl");
            CHECK(board.read(1000001, 1000001, Direction::Horizontal, 5) == "c;fr_");
    //maximum value for a 32-bit unsigned integer
    board1.post(4294967290, 4294967288, Direction::Horizontal, "abgty");
            CHECK(board1.read(4294967290, 4294967288, Direction::Horizontal, 7) == "abgty__");
    board1.post(4294967290, 4294967275, Direction::Horizontal, "xybbz");
            CHECK(board1.read(4294967290, 4294967275, Direction::Horizontal, 6) == "xybbz_");
            CHECK(board1.read(4294967290, 4294967274, Direction::Horizontal, 6) == "_xybbz");
            CHECK(board1.read(4294967288, 4294967276, Direction::Vertical, 6) == "__y___");
}