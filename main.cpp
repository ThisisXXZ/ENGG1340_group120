#include <iostream>
#include "chessboard.h"

using namespace std;



int main() {

    chessboard a;
    a.print();

    for (int i = 1; i <= 5; ++i)
        a.setPiece(i, 3, -1);
    
    cout << endl;
    a.print();
    cout << a.getPiece(4, 3) << endl;
    cout << a.chkSuccess() << endl;

    return 0;
}