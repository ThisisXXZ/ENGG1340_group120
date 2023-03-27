#include <iostream>
#include <cstring>
#include <iomanip>
#include "chessboard.h"

using namespace std;

chessboard::chessboard() {
    for (int i = 1; i <= 15; ++i)
        for (int j = 1; j <= 15; ++j)   b[i][j] = ' ';
}

void chessboard::print() {
    cout << "     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15" << endl;
    cout << "   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;
    for (int i = 1; i <= 15; ++i) {
        cout << setw(3) << i;
        for (int j = 1; j <= 15; ++j) {
            cout << "| ";
            cout << b[i][j];
            cout << " ";
        }
        cout << "|" << endl;
        cout << "   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|" << endl;
    }
}

int chessboard::setPiece(int x, int y, int p) {
    if (x > 15 || x < 1 || y > 15 || y < 1) 
        return 1;
    if (b[x][y] != ' ')
        return 1;
    b[x][y] = (p == 0) ? 'X' : 'O'; 
}

int chessboard::chkSuccess() {
    
}
