#include <iostream>
using namespace std;
int main()
{
    cout << "Hello world" << endl;
    int * p = new int[5];
    cout << sizeof(p) << endl;
    
    return 0;
}