#include <iostream>
#include <complex>
#include <cmath>
using namespace std;
typedef std::complex<double> Complex;

int main()
{
    Complex root1(0,-1);
    cout << sqrt(root1) << endl;
    const   complex<double> i(0.0,1.0);    
    cout << i << endl ;
    Complex root2(-1,0);
    cout << sqrt(root2) << endl;
}