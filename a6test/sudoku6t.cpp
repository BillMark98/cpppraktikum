
#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::vector;







// ----------------------------------------------------------------------
// Klasse Sudoku

class Sudoku
{
  private:
    vector<int> Data;     // Attribute

    void check( int& idx) const; // Index pruefen, evtl. korrigieren und
                                 // Fehlermeldung ausgeben
  public:
    Sudoku()
    {
        Data.resize(81);  // mit Nullen belegt
    }

    // Impliziter Destruktor ausreichend, da keine dyn. Speicherverwaltung.
    // Gleiches gilt fuer impliziten Kopierkonstr. und Zuweisungsoperator.

    // Zugriffsoperatoren
    int& operator() (int r, int c)
    {
        check(r); check(c);
        return Data[ (r-1)*9 + (c-1)];
    }

    int operator() (int r, int c) const
    {
        check(r); check(c);
        return Data[ (r-1)*9 + (c-1)];
    }

    // Methoden, die die Gueltigkeit pruefen
    bool validRow( int r) const;
    bool validCol( int c) const;
    bool validSqr( int a, int b) const;
    bool valid() const;

    bool solved() const
    { return getNumEmpty()==0 && valid(); }

    // Anzahl der leeren Felder
    int getNumEmpty() const;
};

// Ein-/Ausgabeoperatoren
ostream& operator<< (ostream& out, const Sudoku& S);

istream& operator>> (istream& in, Sudoku& S);


// ----------------------------------------------------------------------
// Klasse possibleDigits fuer Hilfszahlen: 
// welche Ziffern sind moeglich (true) bzw. nicht (false)?


class possibleDigits
{
  private:
    vector<bool> possible;    // 9 bool-Eintraege

  public:
    // Konstruktor mit Initialisierungswert fuer alle Ziffern
    possibleDigits( bool allPossible= true)
    { 
        possible.resize(9);
        for(int index = 0; index < 9; index++)
        {
            possible[index]  = allPossible;
        }
    }

    // Anzahl der moeglichen Ziffern
    int numPossible() const;

    // Praedikat: Ist die Ziffer moeglich?
    bool isPossible( int digit) const { return possible[digit-1];}
    
    // Setze die Ziffer als moeglich
    void enable ( int digit) { possible[digit - 1] = true; }
    // Setze die Ziffer als nicht moeglich
    void disable( int digit) { possible[digit-1] = false; }

    // Friend
    friend possibleDigits operator&&( const possibleDigits& a, const possibleDigits& b);
};

ostream& operator<<( ostream& out, const possibleDigits& a);

// a && b berechnet die Schnittmenge der Hilfszahlen a und b
possibleDigits operator&&( const possibleDigits& a, const possibleDigits& b);


// ----------------------------------------------------------------------
// Klasse SudokuSolver

class SudokuSolver
{
  private:
    vector<possibleDigits> pdRow, pdCol, pdSqr; // jeweils 9 Eintraege
    Sudoku&                Sudo;

    static int getSqr( int r, int c) { return 3*((r-1)/3) + (c-1)/3 + 1; }

  public:
    SudokuSolver( Sudoku& S);

    // trage Ziffer in Eintrag (r,c) ein und passe Hilfszahlen an
    void setDigit  ( int r, int c, int digit);
    // entferne Ziffer in Eintrag (r,c) und passe Hilfszahlen an
    void unsetDigit( int r, int c);

    // Hilfszahlen zum Eintrag (r,c)
    possibleDigits getPossible( int r, int c) const;

    // gibt Eintrag (r_min,c_min) mit moeglichst wenigen Hilfszahlen zurueck
    void getNextCell( int& r_min, int& c_min) const;

    bool solve( int numEmpty);
};

















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
    a.disable(3); a.disable(4);
    b.enable(1); b.enable(3);
    cout << "a: " << a << "\tb: " << b
         << "\na und b: " << (a && b) << endl;
    return 0;
}






























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
}

possibleDigits SudokuSolver::getPossible( int r, int c) const
{
    /*hier fehlt was*/
}

void SudokuSolver::getNextCell( int& r_min, int& c_min) const
{
    /*hier fehlt was*/
}

bool SudokuSolver::solve( int numEmpty)
{
    /*hier fehlt was*/
}









