#include <iostream>
#include <cmath>
#define ERROR 1e-9
using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;


// Minitest 2

// neuer Datentyp fuer komplexe Zahlen
class Complex
{
  private:
    double Re, Im;                            // Attribute: Real-/Imaginaerteil

  public:
    Complex( double real= 0, double imag= 0); // Konstruktor

    double GetReal() const;                   // Methode: Realteil

    double GetImag() const;                   // Methode: Imaginaerteil

    double GetAbs() const;                    // Methode: Betrag

    void Conjugate();                         // Methode: Komplex-Konjugation (veraendert das Objekt!)

    void SetCartesian( double re, double im)
    { Re= re;  Im= im; }
};

//-----------------------------
// Operatoren zur Ein-/Ausgabe

Complex::Complex( double real, double imag)
{
    Re = real;
    Im = imag;
}

double Complex::GetReal() const
{
    return Re;
}
double Complex::GetImag() const
{
    return Im;
}
double Complex::GetAbs() const
{
    double sum = pow(Re,2) + pow(Im,2);
    return sqrt(sum);
}
void Complex::Conjugate()
{
    Im = -Im;
}

istream& operator>>( istream& in, Complex& x)
{
    double re, im;
    in >> re >> im;
    x.SetCartesian( re, im);
    return in;
}

ostream& operator<<( ostream& out, Complex x)
{
    if(abs(x.GetImag() - 0) < ERROR)
    {
        // reelle Zahl;
        out << x.GetReal() << endl;
        return out;
    }
    else if( abs(x.GetReal() - 0) < ERROR )
    {
        // reine imaginaere Zahl;
        out << x.GetImag() << "i" << endl;
        return out;
    }
    out << x.GetReal() << " + " << x.GetImag() << "i" << endl;
    return out;
}

//-----------------------------
// artithmetische Operatoren

Complex operator+ ( Complex x, Complex y)
{
    double re= x.GetReal() + y.GetReal(),
           im= x.GetImag() + y.GetImag();
    Complex z( re, im);
    return z;
}

Complex operator- ( Complex x, Complex y)
{
    double re= x.GetReal() - y.GetReal(),
           im= x.GetImag() - y.GetImag();
    Complex z( re, im);
    return z;
}

Complex operator* ( Complex x, Complex y)
{
    double re= x.GetReal()* y.GetReal() - x.GetImag() * y.GetImag();
    double im= x.GetReal() * y.GetImag() + x.GetImag() * y.GetReal();
    Complex z( re, im);
    return z;
}

Complex operator/ ( Complex x, Complex y)
{
    double betrag = pow(y.GetAbs(),2);
    double re = (x.GetReal() * y.GetReal() + x.GetImag() * y.GetImag())/betrag;
    double im = (x.GetImag() * y.GetReal() - x.GetReal() * y.GetImag())/betrag;
    Complex z(re,im);
    return z;
}


Complex pow( Complex z, int k)
{
    Complex x(1,0);
    if(k == 0)
    {
        return x;
    }
    for(int i = 1; i <= k; i++)
    {
        x = x * z;
    }
    return x;
}


int main()
{
    Complex x( 0, 1),    // = 0 + 1 i   = i
            y( 1, 1);    // = 1 + 1 i

    cout << "x+y = " << x+y << endl;  //  1 + 2i
    cout << "x-y = " << x-y << endl;  // -1 + 0i
    cout << "x*y = " << x*y << endl;  // -1 + 1i
    cout << "x/y = " << x/y << endl;  // 0.5 + 0.5i

    cout << "Bitte eine komplexe zahl eingeben ( real, im): ";
    Complex z;
    cin >> z;
    Complex result = pow(z,5) - pow(z,3) + 1;
    cout << " z^5 - z^3 + 1 = " << result  << endl;
    return 0;
}


