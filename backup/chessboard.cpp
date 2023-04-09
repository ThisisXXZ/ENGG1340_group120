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

int chessboard::getPiece(int x, int y) {
    if (b[x][y] == 'X') return -1;
    if (b[x][y] == 'O') return 0;
    return 0;
}

int chessboard::setPiece(int x, int y, int p) {
    if (x > 15 || x < 1 || y > 15 || y < 1) 
        return 1;
    if (b[x][y] != ' ')
        return 1;
    b[x][y] = (p == -1) ? 'X' : 'O'; 
    return 0;
}

int chessboard::chkVerticle(int x, int y) {
    if (b[x][y] == ' ' || y > 11)
        return 0;
    for (int _y = y; _y < y + 5; ++_y) {
        if (b[x][_y] != b[x][y])    return 0;
    } 
    return (b[x][y] == 'X') ? -1 : 1;
}

int chessboard::chkHorizontal(int x, int y) {
    if (b[x][y] == ' ' || x > 11)
        return 0;
    for (int _x = x; _x < x + 5; ++_x) {
        if (b[_x][y] != b[x][y])    return 0;
    }
    return (b[x][y] == 'X') ? -1 : 1;
}

int chessboard::chkRightSlant(int x, int y) {
    if (b[x][y] == ' ' || x > 11 || y > 11)
        return 0;
}

int chessboard::chkLeftSlant(int x, int y) {
    if (b[x][y] == ' ' || x > 11 || y < 5)
        return 0;
}

int chessboard::chkSuccess() {
    for (int x = 1; x <= 15; ++x)
        for (int y = 1; y <= 15; ++y) {
            int res = chkVerticle(x, y);
            if (res)    return res;
            res = chkHorizontal(x, y);
            if (res)    return res;
            res = chkRightSlant(x, y);
            if (res)    return res;
            res = chkLeftSlant(x, y);
        }
    return 0;
}
