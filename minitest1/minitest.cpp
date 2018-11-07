#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
void SchreibeRueckwaerts(int n);
int Spiegelzahl(int n);
int main()
{
    int eingabe;
    // SchreibeRueckwaerts(n);
    // cout << endl;
    // int result = Spiegelzahl(14);
    // cout << "Result: " << result <<endl;
    cout << "Bitte eine Zahl eingeben: ";
    cin >> eingabe;
    
    if( eingabe > 0)
    {
        cout << "Sie haben eine positive Zahl eingegeben.\n";
        cout << "Die Zahl : " << eingabe << endl;
        cout << "Ziffer Rueckwaerts: ";
        SchreibeRueckwaerts(eingabe);
        cout << endl;
        int result = Spiegelzahl(eingabe);
        cout << "Die Spiegelzahl: " << result << endl;
        if ( result == eingabe )
        {
            cout << "Die Zahl ist ein Palindrom.\n";
        }
        else
        {
            cout << "Die Zahl ist kein Palindrom.\n";
        }
    }
    else
    {
        cout << "Die Zahl ist nicht positiv. Tut nichts.\n";
    }

    return 0;
}
void SchreibeRueckwaerts(int n)
{
    if(n/10 == 0)
        cout << n << ' ';
    else
    {
        cout << (n % 10) << ' ';
        SchreibeRueckwaerts(n/10); 
    }
}
int Spiegelzahl(int n)
{
    int result = 0;
    int temp = 0;
    while(n / 10 != 0)
    {
        temp = n % 10;
        n = n/10;
        result *= 10;
        result += temp;
    }

    result *= 10;
    result += n;
    return result;
    
}