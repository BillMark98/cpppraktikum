#include <iostream>
using std::cout;
using std::cin;
using std::endl;
void Ausgabe(const double * feld, int n);
double Durchschnitt(const double * feld, int n);
int min_pos(const double * feld, int n);
void sortiere(double * feld, int n);
void swap(double & a, double & b);
int main()
{
    double arr[] = {47,11,0,8,5};
    Ausgabe(arr+2,3);
    cout << "Mean: " << Durchschnitt(arr,5) << endl;
    cout << "Min pos: " << min_pos(arr,5) << endl;
    cout << "Now sorting\n";
    sortiere(arr,5);
    Ausgabe(arr,5);
    return 0;
}
void Ausgabe(const double * feld, int n)
{
    int index;
    for(index = 0; index < n; index++)
    {
        cout << feld[index] << ' ';
    }
    cout << endl;
}
double Durchschnitt(const double * feld, int n)
{
    double sum = 0;
    int index;
    for(index = 0; index < n; index++)
    {
        sum += feld[index];
    }
    double result = (double)sum/n;
    return result;
}
int min_pos(const double * feld, int n)
{
    int index,min;
    for(index = 0,min = 0; index < n; index++)
    {
        if(feld[index] < feld[min])
        {
            min = index;
        }
    }
    return min;
}
void sortiere(double * feld, int n)
{
    int i,j;
    for(i = 0; i < n; i++)
    {
        j = min_pos(feld + i, n-i);
        swap(feld[i],feld[j]);
    }
}
void swap(double & a, double & b)
{
    double temp;
    temp = a;
    a = b;
    b = temp;
}