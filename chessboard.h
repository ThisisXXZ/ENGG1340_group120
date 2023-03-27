#ifndef CHESSBOARD
#define CHESSBOARD

class chessboard{
    
    char b[30][30];                    // the board

public:
    chessboard();
    void print();
    int setPiece(int x, int y, int p); // p (party): 0 for black, 1 for white
                                       // setPiece has return value: 1 for improper instructions
    int chkSuccess();                  // return -1 if game should proceed; 
                                       // otherwise return the winning party

};

#endif