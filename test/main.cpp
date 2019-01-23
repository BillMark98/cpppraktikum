#include <iostream>
#include <vector>

using namespace std;
int main()
{
    int a, b;
    a = 2;
    b = 4;
    int c = a  + b;
    cout << "Hello" << endl;
    cout << c << endl;

    string file;
    vector<string> files;
    files.resize(2);
    files[0] = "hello";
    cout << files[0] << endl;
    return 0;
}