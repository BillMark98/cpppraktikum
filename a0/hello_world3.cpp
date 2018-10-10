#include <iostream>
#include <string>
using namespace std;
int main()
{
    string vorname;
    string nachname;

    cout << "What's your name?" <<endl;
    cin >> vorname;
    cin >> nachname;
    char ch = vorname.back();
    if(ch == 'a' || ch =='e')
    {
        cout << "Hello, Frau " << vorname << ' ' << nachname << '!' << endl;
    }
    else
    {
        cout << "Hello, Herr " << vorname << ' ' << nachname << '!' << endl;
    }
    
    return 0;
}