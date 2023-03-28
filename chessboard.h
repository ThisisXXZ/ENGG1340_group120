#ifndef CHESSBOARD
#define CHESSBOARD

class chessboard{
    
    char b[30][30];                    // the board

public:
    chessboard();
    void print();

    int getPiece(int x, int y);        // -1(X) for black, 0 for unoccupied, 1(O) for white
    int setPiece(int x, int y, int p); // p (party): -1(X) for black, 1(O) for white
                                       // setPiece() has return value: 1 for improper instructions
    int chkSuccess();                  // return 0 if game should proceed; 
                                       // otherwise return the winning party
    int chkVerticle(int x, int y);
    int chkHorizontal(int x, int y);
    int chkLeftSlant(int x, int y);    
    int chkRightSlant(int x, int y);   // 4 subfuntions for chkSuccess(); return value has the same logic
                                       // as chkSuccess()
};

#endif