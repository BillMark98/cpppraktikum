//
//  sudoku.cpp
//  a6
//
//  Created by BillHu on 23.01.19.
//  Copyright © 2019 BillHu. All rights reserved.
//


#include "sudoku.h"

int global = 0;
// ----------------------------------------------------------------------
// Klasse Sudoku


// Ein-/Ausgabeoperatoren
ostream& operator<< (ostream& out, const Sudoku& S)
{
    for (int r=1; r<=9; ++r) {
        for (int c=1; c<=9; ++c) {
            const int z= S(r,c);
            if (z==0)
                out << ". ";
            else
                out << z << ' ';
        }
        out << endl;
    }
    return out;
}

istream& operator>> (istream& in, Sudoku& S)
{
    for (int r=1; r<=9; ++r)
        for (int c=1; c<=9; ++c)
            in >> S(r,c);
    return in;
}

// Sudoku-Methoden

void Sudoku::check( int& idx) const
{
    if (idx < 1) {
        cout << "Index " << idx << " ist ungueltig." << endl;
        idx= 1;
    }
    if (idx > 9) {
        cout << "Index " << idx << " ist ungueltig." << endl;
        idx= 9;
    }
}

int Sudoku::getNumEmpty() const
{
    int numEmpty= 0;
    for (int i=0; i<81; ++i)
        if (Data[i]==0)
            ++numEmpty;
    return numEmpty;
}

bool Sudoku::validRow( int r) const
{
    int haeufigkeit[10]= {}; // mit Nullen initialisiert
    
    for (int c=1; c<=9; ++c) {
        int z= (*this)(r,c);
        if (z != 0) {
            haeufigkeit[z]++;
            if (haeufigkeit[z] > 1) // z kommt mehr als einmal vor
                return false;
        }
    }
    return true;
}

bool Sudoku::validCol( int c) const
{
    int haeufigkeit[10]= {}; // mit Nullen initialisiert
    
    for (int r=1; r<=9; ++r) {
        int z= (*this)(r,c);
        if (z != 0) {
            haeufigkeit[z]++;
            if (haeufigkeit[z] > 1)
                return false;
        }
    }
    return true;
}

bool Sudoku::validSqr( int a, int b) const
{
    int haeufigkeit[10]= {}; // mit Nullen initialisiert
    // Eintrag oben links ist (r,c)
    const int r= 3*(a-1)+1, c= 3*(b-1)+1;
    
    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            int z= (*this)(r+i,c+j);
            if (z != 0) {
                haeufigkeit[z]++;
                if (haeufigkeit[z] > 1)
                    return false;
            }
        }
    }
    return true;
}

bool Sudoku::valid() const
{
    bool val= true;
    
    for (int i=1; i<=9; ++i) {
        val= val && validRow(i)
        && validCol(i);
    }
    for (int i=1; i<=3; ++i)
        for (int j=1; j<=3; ++j)
            val= val && validSqr( i, j);
    
    return val;
}

int possibleDigits::operator()(int index) const
{
    int len = (int) possible.size();
    if(index < 0 || index >= len)
    {
        cout << "cannot extract the number given index " << index << endl;
        cout << "error in possibleDigits()\n";
        exit(3);
    }
    return possible[index];
}

// ----------------------------------------------------------------------
// Klasse possibleDigits fuer die Hilfszahlen

ostream& operator<<( ostream& out, const possibleDigits& a)
{
    out << "Possible digits are:\n";
    for(int number = 1; number < 10; number ++)
    {
        if((a.isPossible(number)))
        {
            out.width(3);
            out << number;
        }
        
    }
    out << endl;
    return out;
}

possibleDigits operator&&( const possibleDigits& a, const possibleDigits& b)
{
    possibleDigits schnitt_digits;
    for(int index = 0; index < 9; index ++)
    {
        schnitt_digits.possible[index] = a.possible[index] && b.possible[index];
    }
    return schnitt_digits;
}

// possibleDigits-Methoden

int possibleDigits::numPossible() const
{
    /*hier fehlt was*/
    vector<bool>::const_iterator it;
    int count = 0;
    for( it = possible.begin(); it != possible.end(); it++)
    {
        if((*it))
        {
            count ++;
        }
    }
    return count;
}


// ----------------------------------------------------------------------
// Klasse SudokuSolver

SudokuSolver::SudokuSolver( Sudoku& S)
: /*hier fehlt was*/ Sudo(S)
{
    pdRow.resize(9);
    pdCol.resize(9);
    pdSqr.resize(9);
    for(int row = 1; row < 10; row++)
    {
        for(int column = 1; column < 10; column++)
        {
            int number = Sudo(row,column);
            if(number)
            {
                pdRow[row-1].disable(number);
                pdCol[column-1].disable(number);
                int hor = (row - 1)/3;
                int ver = (column - 1)/ 3;
                pdSqr[hor * 3 + ver].disable(number);
                
            }
        }
    }
}

void SudokuSolver::setDigit( int r, int c, int digit)
{
    Sudo(r,c) = digit;
    // pdRow, pdCol, pdSqr update
    // To do: if digits already appeared in the same row, col or square
    
    pdRow[r-1].disable(digit);
    pdCol[c-1].disable(digit);
    // int hor = (r - 1)/3;
    // int ver = (c - 1)/ 3;
    // pdSqr[hor * 3 + ver].disable(digit);
    pdSqr[getSqr(r,c)-1].disable(digit);
}

void SudokuSolver::unsetDigit( int r, int c)
{
    /*hier fehlt was*/
    int digit = Sudo(r,c);
    Sudo(r,c) = 0;
    pdRow[r-1].enable(digit);
    pdCol[c-1].enable(digit);
    pdSqr[getSqr(r, c) - 1].enable(digit);
}

possibleDigits SudokuSolver::getPossible( int r, int c) const
{
    /*hier fehlt was*/
    
    // temp
    int digit = Sudo(r,c);
    if (digit != 0) // field not free no possible digits
    {
        possibleDigits result(false);
        return result;
    }
    else
    {
        possibleDigits result = pdRow[r-1] && pdCol[c-1] && pdSqr[getSqr(r, c) - 1];
        return result;
    }
}

void SudokuSolver::getNextCell( int& r_min, int& c_min) const
{
    int min = 9;
    int rmin = 10;
    int cmin = 10;
    for(int row = 1; row < 10; row++)
    {
        for(int col = 1; col < 10; col++)
        {
            int digit = Sudo(row,col);
            int number_of_digits;
            if(!digit)
            {
                number_of_digits = getPossible(row, col).numPossible();
                if(min > number_of_digits)
                {
                    min = number_of_digits;
                    rmin = row;
                    cmin = col;
                }
            }
        }
    }
    if( rmin < 10 && cmin < 10)
        // there are fields to enter
    {
        r_min = rmin;
        c_min = cmin;
    }
    else
    {
        cout << "No places to enter digit! error in getNextCell \n";
        exit(2);
    }
    
}

bool SudokuSolver::solve( int numEmpty)
{
    global++;
//    bool success = false;
   if(Sudo.getNumEmpty() == 0)  // or numEmpty == 0  ????
   {
       if(Sudo.valid())
       {
           cout << "Success!!!!\n";
           cout << Sudo << endl;
           return true;
       }
       else
       {
           // fail in this case try another possible digits at the upper layer of the recursion
           return false;
       }
   }
    int row, col;
    getNextCell(row, col);
    possibleDigits pos_digits = getPossible(row, col);
    int len = pos_digits.numPossible();
    if(!len)
    {
        // no possible digits to write in
        return false;
    }
    for(int digit = 1; digit < 10; digit++)
    {
        if(pos_digits.isPossible(digit))
        {
            setDigit(row, col, digit);
            if(!solve(numEmpty - 1))
            {
                // this setting unsuccessful!
                unsetDigit(row, col);
            }
            else
            {
                // this setting successful!
//                unsetDigit(row, col);
//                success = true;
                return true;
            }
            
        }
    }
    // all possible digits tried,still unsuccessful
    return false;
//    return success;
}
