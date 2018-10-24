#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main()
{
    double A,B,C;
    cout << "Please enter three numbers.\n";
    cin >> A >> B >> C;
    if (A)
    {
        double decriminent = B * B - 4 * A * C;
        double root1, root2;
        if(decriminent < 0)
        {
            cout << "Real roots dont exist.\n";
            cout << "Complex roots are: ";
            double decri_complex = -1 * decriminent;
            double img1, img2;
            root1 = ((-1)*B)/(2*A);
            img1 = -1*sqrt(decri_complex)/(2*A);
            img2 = -1*img1;
            char ch1 = '+';
            // char ch2 = '-';
            char ch3 = 'i';
            // cout << root1 << ' + ' << img1 << 'i' <<endl;
            // cout << root1 << ' + ' << img2 << 'i' <<endl;
            if( abs(root1) > __DBL_EPSILON__)
            {   
                cout << root1 << img1 << ch3 <<endl;
                cout << root1 << ch1 << img2 << ch3 <<endl;
            }
            else
            {
                cout << img1 << ch3 <<endl;
                cout << setiosflags(ios::showpos) << img2 << ch3 <<endl;
            }
        }
        else    
        {
            root1 = ((-1)*B + sqrt(decriminent))/(2*A);
            root2 = ((-1)*B - sqrt(decriminent))/(2*A);
            cout << "The roots of the equation are: " 
             << root1 << " and " << root2 << endl;
        }
            double extre_value;
            extre_value = C - B * B/(4 * A);
        if( A > 0)
        {   
            cout << "The minimum value is " << extre_value << endl;
        }
        else if( A < 0)
        {
            cout << "The maximum value is " << extre_value << endl;
        }
        return 0;
    }
    if( !A )
    {
        cout << "A linear function\n";
        double root;
        root = -1 * C/B;
        cout << "The root is " << root << endl;
        cout << "There are no extreme values\n";
        return 0;
    }
}