#include <iostream>
#include <cstdlib>
using std::cout;
using std::string;
using std::cin;
using std::endl;
int main()
{
    double weight;
    double height;
    double BMI;
    int mode;
    cout << "Enter your weight(in kg):\n";
    cin >> weight;
    cout << "Choose the unit of the height, 1 for cm and 2 for m\n";
    cin >> mode;
    if(mode == 2)
    {    
        cout << "Enter your height(in m):\n";
        cin >> height;
    }
    else if(mode == 1)
    {
        cout << "Enter your height(in cm):\n";
        cin >> height;
        height /= 100;
    }
    else
    {
        cout << "invalid mode number\n";
        exit(1);
    }
    BMI = weight/height;
    BMI /= height;
    cout << "The BMI: " << BMI << endl;
    return 0;
}