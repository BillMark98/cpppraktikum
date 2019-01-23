//
//  sudoku.hpp
//  a6
//
//  Created by BillHu on 23.01.19.
//  Copyright © 2019 BillHu. All rights reserved.
//

#ifndef sudoku_hpp
#define sudoku_hpp

#include <vector>
#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::vector;
using std::ifstream;

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
    
    // add-ons, to extract the number at the given index if possible
    int operator()(int index) const;
    
    // Friend
    friend possibleDigits operator&&( const possibleDigits& a, const possibleDigits& b);
};

ostream& operator<<( ostream& out, const possibleDigits& a);

//// a && b berechnet die Schnittmenge der Hilfszahlen a und b
//possibleDigits operator&&( const possibleDigits& a, const possibleDigits& b);


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


#endif /* sudoku_hpp */
