#include <iostream>
#include <fstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::vector;
using std::ifstream;

// Matrix-Klasse fuer quadratische Matrizen
class SquareMatrix
{
  private:
    vector<double> matrix;
    int row; // number of rows
  public:
    SquareMatrix( int n); // Konstruktor fuer eine Matrix mit n Zeilen und Spalten

    int  getNumRowCol() const { return row; }  // gibt Anzahl Zeilen/Spalten zurueck
    void setNumRowCol( int n) { matrix.resize(n * n); row = n; }  // setzt Anzahl Zeilen/Spalten

    double& operator() (int i, int j);         // Lese-/Schreibzugriff
    double  operator() (int i, int j) const;   // Lesezugriff

    SquareMatrix transpose() const;            // gibt Transponierte zurueck
};

// Methoden der SquareMatrix-Klasse

SquareMatrix::SquareMatrix( int n) // Konstruktor fuer eine Matrix mit n Zeilen und Spalten
{
    matrix.resize(n*n);
    row = n;
}

double& SquareMatrix::operator() (int i, int j)       // Lese-/Schreibzugriff
{
    if( i < 0 || i >= row || j < 0 || j >= row)
    {
        cout << "Invalid indexes!\n";
        exit(1);
    }
    int index = i * row + j;
    return matrix[index];

}

double  SquareMatrix::operator() (int i, int j) const // Lesezugriff
{
    if( i < 0 || i >= row || j < 0 || j >= row)
    {
        cout << "Invalid indexes!\n";
        exit(1);
    }
    int index = i * row + j;
    return matrix[index];
}

SquareMatrix SquareMatrix::transpose() const // gibt Transponierte zurueck
{
    SquareMatrix transposed = SquareMatrix(row);
    for(int i = 0; i < row ; i++)
    {
        for(int j = 0; j < row; j++)
        {
            transposed(i,j) = (*this)(j,i);
        }
    }
    return transposed;
}

// Eingabe-/Ausgabe-Operatoren

istream& operator>> (istream& in, SquareMatrix& A)
{
    int n;
    in >> n;
    A.setNumRowCol(n); // redimensionieren
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
            in >> A(i,j);
    return in;
}

ostream& operator<< (ostream& out, const SquareMatrix& A)
{
    int row = A.getNumRowCol();
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < row; j++)
        {
            out.width(10);
            out << A(i,j);
        }
        out << endl;
    }
    out << endl;
    return out;
}

// arithmetische Operatoren

SquareMatrix operator+ (const SquareMatrix& A, const SquareMatrix& B)    // A + B
{
    const int n= A.getNumRowCol();
    SquareMatrix result( n);

    if (B.getNumRowCol() != n)
    {
        cout << "A+B: matrix dimensions must agree!" << endl;
        return result;
    }
    
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
            result(i,j)= A(i,j) + B(i,j);
    return result;
}

SquareMatrix operator* (const SquareMatrix& A, const SquareMatrix& B)    // A*B
{
    const int n = A.getNumRowCol();
    SquareMatrix result(n);
    if(B.getNumRowCol() != n)
    {
        cout << "A+B: matrix dimensions must agree!" << endl;
        return result;
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            // result(i,j) = 0;
            double temp = 0;
            for(int k = 0; k < n; k++)
            {
                temp += A(i,k) * B(k,j);
            }
            result(i,j) = temp;
        }
    }
    return result;
}


// pow-Funktion, berechnet M^p fuer p >= 0
SquareMatrix pow( const SquareMatrix& M, int p)
{
    if(p == 1)
    {
        return M;
    }
    if( p % 2 == 1)
    {
        return M * pow(M,p-1);
    }
    else
    {
        SquareMatrix temp = pow(M,p/2);
        return temp * temp;
    }
}


// Hauptprogramm
int main()
{
    SquareMatrix A(2);
    A(0,1)= 1;     // erzeugt die Matrix | 0 1 |
    A(1,0)= -1;    //                    |-1 0 |
    cout << A << endl << A.transpose() << endl;
        
    SquareMatrix Q(1);
    // Matrix Q aus Datei einlesen
    ifstream inFile;
    inFile.open("Q.txt");
    if(!inFile.is_open())
    {
        cout << "Open file error!\n";
        exit(3);
    }

    inFile >> Q;
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
    cout << "Q =\n" << Q << endl;
    
    SquareMatrix Q_QT= Q*Q.transpose();
    SquareMatrix QT_Q= Q.transpose()*Q;

    cout << "Q * Q^T =\n" << Q_QT << endl;
    cout << "Q^T * Q =\n" << QT_Q << endl;

    int p; // p = 8
    cout << "Gebe eine ganze Zahl p >= 2 ein: ";
    cin >> p;

    cout << "Q^p =\n" << pow( Q, p) << endl;

    return 0;
}
    
