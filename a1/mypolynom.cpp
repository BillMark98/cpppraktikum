#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;
int main()
{
    
    double root1, root2;
    cout << "Enter two roots and I will give you a polynom\n"
         << ",the roots of which are the roots you have given\n";
    cin >> root1 >> root2;
    char ch1 = 'x';
    double B,C;
    B = -1*(root1 + root2);
    C = root1 * root2;
    cout << ch1 << "^2 " << setiosflags(ios::showpos) << B << ch1 << ' '
         << setiosflags(ios::showpos) <<C << endl;
}