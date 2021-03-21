# Dynamic MessageBoard :newspaper:
This exercise hes been done for assignment([git assignment](https://github.com/cpp-exercises/messageboard-a))  in course c++ in Ariel university.

### Details on the functions:

- `post` - Gets a position (row and column), direction (horizontal or vertical), and a string that represents an ad, and pastes the string on the board in the appropriate place.
- `read` - Gets position (row and column), direction (horizontal or vertical), and number of characters, reads what is written on the board at the given position and length, and returns a string. The letter in each slot on the board is the last letter pasted there.
- `show` - Displays the current message-board for easy reading

#### Emphasis:

- The rows and column numbers and character numbers are non-negative integers (unsigned int).
- The top row is 0 and the left column is 0.
- In each slot on which nothing is pasted, there is an underline ('_').
- The board size is not limited in advance, but it can be assumed that all the ads will be concentrated in the same area - the distances between ads will not be very large.

## Simple example :
You can change the main in Demo.cpp, and use the the command `make` in terminal
```c++
#include "Board.hpp"
#include <iostream>

using ariel::Direction;
using namespace std;

int main() {
  board.post(100, 200, Direction::Horizontal, "abcd"); 
  //post in the board in row:100 and column:200 in direction:horizontal the string "abcd"
  cout << board.read(99, 201, Direction::Vertical, 3) << endl;  
  //prints "_b_" starts at row 99 which is empty, then at row 100 there is "b", then row 101 is empty again, reader in length 3

  board.post(99, 202, Direction::Vertical, "xyz"); 
  board.show();
  //prints the current message-board:
  //     ____
  // 99:|__x_|
  //100:|abyd|
  //101:|__z_|
}
```
