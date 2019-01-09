#include <iostream>
#include <fstream>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ifstream;
using std::ostream;
using std::ofstream;
using std::vector;

// to do: add a function to test if the number in Sudoku::Data is valid
// an integer between 0 to 9
// and modify the validRow,Col,Sqr function which should test
// the valid Data first

class Sudoku
{
    private:
        vector<int> Data;
    public:
        Sudoku();
        int& operator() (int r, int c);
        int operator() (int r, int c) const;
        bool validRow(int r) const;
        bool validCol(int c) const;
        bool validSqr(int a, int b) const;
        bool valid() const;
        int numEmpty() const;
        bool solved() const;
};
ostream& operator<< (ostream& out, const Sudoku& S);
istream& operator>> (istream& in, Sudoku& S);
int main()
{
    Sudoku mysudoku;
    mysudoku(2,4) = 9;
    mysudoku(4,1) = 2;
    cout << mysudoku << endl;

    // read in file 
    ifstream inFile;
    inFile.open("Sudoku1.txt");
    if(!inFile.is_open())
    {
        cout << "open File error.\n";
        exit(1);
    }
    inFile >> mysudoku;
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
    // some test for valid function
    // mysudoku(1,4) = 0;
    // mysudoku(2,7) = 7;
    // mysudoku(1,8) = 7;
    cout << mysudoku << endl;
    cout << mysudoku.valid() << endl;
    int row,column,number;
    while(!mysudoku.solved())
    {
        cout << "Please enter row : ";
        cin >> row;
        if(!cin)
        {
            cout << "program end due to invalid input.\n";
            break;
        }
        if(row < 1 || row > 9)
        {
            cout << "Invalid row.\n";
            continue;
        }
        cout << "Please enter col: ";
        cin >> column;
        if(!cin)
        {
            cout << "program end due to invalid input.\n";
            break;
        }
        if(column < 1 || column > 9)
        {
            cout << "Invalid column.\n";
            continue;
        }
        cout << "Please enter the number: ";
        cin >> number;
        if(!cin)
        {
            cout << "program end due to invalid input.\n";
            break;
        }
        if( number < 0 || number > 9)
        {
            cout << "Invalid number \n";
            continue;
        }
        mysudoku(row,column) = number;
        cout << "Modified sudoku.\n";
        cout << mysudoku << endl;


    }
    cout << "Hooray sudoku solved!!!!" << endl;
    inFile.close();

    return 0;
}
Sudoku::Sudoku()
{
    for(int index = 0; index < 81; index ++)
    {
        Data.push_back(0);
    }
}
int& Sudoku::operator() (int r, int c)
{
    if( r < 1 || r > 9 || c < 1 || c > 9)
    {
        cout << "Invalid index. Give back -1\n";
        exit(0);
    }
    else
    {
        int row = r-1;
        int column = c - 1;
        return Data[row * 9 + column];
    }
}
int Sudoku::operator() (int r, int c) const
{
    if( r < 1 || r > 9 || c < 1 || c > 9)
    {
        cout << "Invalid index. Give back -1\n";
        exit(0);
    }
    else
    {
        int row = r-1;
        int column = c - 1;
        return Data[row * 9 + column];
    }
}
bool Sudoku::validRow(int r) const
{
    if(r < 1 || r > 9)
    {
        cout << "invalid row.\n";
        exit(4);
    }
    int arr[] = { 0,1,2,3,4,5,6,7,8,9};
    for(int column = 1; column < 10; column++)
    {
        int temp;
        if((temp = (*this)(r,column)) != 0)
        {
            if(arr[temp] != 0)
            {
                // reaching this number for the first time
                arr[temp] = 0;
            }
            else
            {
                // already read this number
                // which means this number occurs more than once
                // in this row
                return false;
            }
        }
    }
    // no positive number occur more than once
    return true;
}
bool Sudoku::validCol(int c) const
{
    if(c < 1 || c > 9)
    {
        cout << "invalid column.\n";
        exit(4);
    }
    int arr[] = { 0,1,2,3,4,5,6,7,8,9};
    for( int row = 1; row < 10; row++)
    {
        int temp;
        if((temp = (*this)(row,c)) != 0)
        {
            if(arr[temp] != 0)
            {
                // first reach this number
                arr[temp] = 0;
            }
            else
            {
                // already read this number
                // which means this number occurs more than once
                // in this column
                return false;
            }
        }
    }
    // no positive number occur more than once
    return true;
}
bool Sudoku::validSqr(int a, int b) const
{
    if(a < 1 || a > 3 || b < 1 || b > 3)
    {
        cout << "Invalid index for square.\n";
        exit(4);
    }
    int arr[] = { 0,1,2,3,4,5,6,7,8,9};
    int rowup = 3*(a-1) + 1; // the uppest row of the square
    int colleft = 3*(b-1) + 1; // the leftest row of the squre
    // int count = 1;
    for( int row = rowup; row < rowup+3; row++)
    {
        int temp;
        for(int column = colleft; column < colleft + 3; column++)
        {
            if((temp = (*this)(row,column)) != 0)
            {
                if(arr[temp] != 0)
                {
                    // first reach this positve integer
                    arr[temp] = 0;
                }
                else
                {
                    // reach this positive integer a second time
                    return false;
                }
            }
        }
    }
    // all tests passed
    return true;
}
bool Sudoku::valid() const
{
    for(int row = 1; row < 10; row++)
    {
        if(!validRow(row))
        {
            cout << "row test failed at row " << row << endl;
            return false; // row test failed
        }
    }
    for(int column = 1; column < 10; column++)
    {
        if(!validCol(column))
        {
            cout << "col test failed at col " << column << endl;
            return false; // col test failed
        }
    }
    for(int a = 1; a < 4; a++)
    {
        for(int b = 1 ; b < 4 ; b++)
        {
            if(!validSqr(a,b))
            {
                cout << "sqr test failed at square a=" << a
                    << " b=" << b << endl;
                return false; // Sqr test failed
            }
        }
    }
    // all tests passed

    return true;
}
int Sudoku::numEmpty() const
{
    int count = 0;
    for( int row = 1; row < 10; row++)
    {
        for( int column = 1; column < 10; column++)
        {
            if((*this)(row,column) == 0)
            {
                count++;
            }
        }
    }
    return count;
}
bool Sudoku::solved() const
{
    if(!valid())
    {
        // not valid square
        cout << "Not valid square!\n";
        return false;
    }
    if( numEmpty() != 0)
    {
        cout << "Still some places not written.\n";
        return false;
    }
    // all tests passed
    return true;
}
        
ostream& operator<< (ostream& out, const Sudoku& S)
{
    out.width(4);
    out << ' ';
    for(int index = 1; index < 10; index ++)
    {
        out.width(4);
        out << index;
        if( index != 1 && index % 3 == 0)
            {
                out << " | ";
            }
    }
    out << endl;
    out << " ----------------------------------------------------\n";
    for(int row = 1; row < 10; row++)
    {
        if(row != 1 && row % 3 == 1)
        {
            out << " -----------------------------------------------------\n";
        }
        out.width(3);
        out << row << '|';
        for(int column = 1; column < 10; column++)
        {
            out.width(4);
            out << S(row,column);
            if( column != 1 && column % 3 == 0)
            {
                out << " | ";
            }
        }
        out << endl;
    }
    return out;
}
istream& operator>> (istream& in, Sudoku& S)
{
    for(int row = 1; row < 10; row++)
    {
        for(int column = 1; column < 10; column++)
        {
            in >> S(row,column);
        }
    }
    return in;
}