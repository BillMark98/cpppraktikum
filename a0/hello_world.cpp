#include <iostream>
using std::cout;
using std::cin;
using std::endl;
int main()
{
    cout << "Hello world" << endl;
    int * p = new int[5];
    cout << sizeof(p) << endl;
    delete [] p;
    double test1,test2;
    cin >> test1 >> test2 ;
    cout <<test1 << '\t' <<test2 <<endl;
    
    return 0;
}