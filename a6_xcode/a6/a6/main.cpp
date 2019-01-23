
#include "sudoku.h"


extern int global;

int main()
{
    possibleDigits mypos_digits;
    for(int index = 1; index < 10; index ++)
    {
        
        if(mypos_digits.isPossible(index))
        {
            cout <<" possible: " << index;
        }
    }
    cout << endl;
    possibleDigits a(true), b(false);
    cout << "a poosible digits " << a.numPossible() << endl;
    cout << "b possible digits " << b.numPossible() << endl;
    a.disable(3); a.disable(4);
    b.enable(1); b.enable(3);
    cout << "a poosible digits " << a.numPossible() << endl;
    cout << "b possible digits " << b.numPossible() << endl;
    cout << "a: " << a << "\tb: " << b
    << "\na und b: " << (a && b) << endl;\
    
    ifstream inFile;
    inFile.open("sudoku3.txt");
    if(!inFile.is_open())
    {
        cout << "open File error.\n";
        exit(1);
    }
    Sudoku sudoku_test;
    inFile >> sudoku_test;
    if(inFile.eof())
    {
        cout << "end of file reached.\n";
    }
    else if(inFile.fail())
    {
        cout << "Input terminated by data mismatch.\n";
    }
    else
    {
        cout << "Input terminated by unkown reasons.\n";
    }
    cout << sudoku_test;
    
    SudokuSolver solver1(sudoku_test);
    possibleDigits t1 = solver1.getPossible(1, 2);
    possibleDigits t2 = solver1.getPossible(5, 5);
    possibleDigits t3 = solver1.getPossible(7, 7);
    
    cout << "t1" << t1 <<endl << "t2" << t2 << endl
    << "t3" << t3 << endl;
    int row, col;
    solver1.getNextCell(row, col);
    cout << "Next row and col: " << row << '\t' << col << endl;
    
    cout << "Testing!\n";
    solver1.solve(sudoku_test.getNumEmpty());
    cout << "calls of solve are : " << global << endl;
    inFile.close();
        
    
    return 0;
}




























