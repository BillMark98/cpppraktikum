#include <iostream>
#include <string>
using namespace std;
int main()
{
    string name;
    cout << "What's your name?\n";
    // cin >> name; this syntax can only get input without space,e.g Bill Hu 
    // only Bill will be accepted.
    getline(cin, name);
    cout << "Hello, " << name << endl;
    return 0;
}