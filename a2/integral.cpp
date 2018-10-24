#include <iostream>
#include <cmath>
#define EPSILON 1e-18
#define NOZEROPOINT -100000
using namespace std;
void Wertetabelle(double a, double b, int N);
double MPRegel(double a, double b, int N);
bool Einschluss(double fa, double fb);
double Bisektion1(double a, double b, double eps);
double Bisektion(double a, double b, double eps);
double Sekantverfahren(double a, double b, double eps);
double Newton(double a, double b, double eps);
double myderivative(double a);
double myfunction(double a);
int main()
{
    // double a,b;
    // int N;
    // cout << "Please enter three numbers, a, b, N\n";
    // cin >> a >> b >> N;
    // Wertetabelle(a,b,N);
    
    //  cout << "The a = 1 b = 5 N = 16 case:\n";
    //  double result1;
    //  result1 = MPRegel(1,5,16);
    //  cout << "integral is :" << result1 << endl;
    
     //find out the first zero
    double zero1 = Bisektion(0,3,1e-10);
    double zero2 = Bisektion(4,7,1e-10);
    double zero3 = Sekantverfahren(0,3,1e-10);
    double zero4 = Sekantverfahren(4,7,1e-10);
    double zero5 = Newton(0,3,1e-10);
    double zero6 = Newton(4,7,1e-10);
    cout << "Zero1 function : " << zero1 << '\t' << myfunction(zero1) << endl;
    cout << " Zero2 function : " << zero2 << '\t' << myfunction(zero2) <<endl;
    cout << "Zero3 function : " << zero3 << '\t' << myfunction(zero3) << endl;
    cout << " Zero4 function : " << zero4 << '\t' << myfunction(zero4) <<endl;
    cout << "Zero5 function : " << zero5 << '\t' << myfunction(zero5) << endl;
    cout << " Zero6 function : " << zero6 << '\t' << myfunction(zero6) <<endl;
    double result = MPRegel(zero5, zero6, 10000);
    cout << "The result is " << result <<endl;
    return 0;
}

void Wertetabelle(double a, double b, int N)
{
    double step = (double)(b - a)/N;
    cout << "x \t f(x)\n";
    cout << "---------------\n";
    int i;
    double x;
    double result;
    for(i = 0; i <= N; i++)
    {
        x = a + i*step;
        result = exp(sin(x)) - (x-1)*(x-6);
        cout << x << " \t " << result << endl;
    }
}

double MPRegel(double a, double b, int N)
{
    double step = (double)(b - a)/N;
    int i;
    double x,result;
    double partialsum = 0;
    for(i = 1; i <= N; i++)
    {
        x = a + (i - 1.0/2)*step; // should be written 1.0/2 not 1/2 or it would be 0 instead of 0.5
        result = exp(sin(x)) - (x - 1) * (x - 6);
        // partialsum += result * step;
        partialsum += result;
    }
    partialsum *= step;
    return partialsum;
}
bool Einschluss(double fa, double fb)
{
    if( abs(fa*fb) < EPSILON)
    {
        return true;
    }
    else
    {
        if(fa * fb < 0)
        {
            return true;
        }
        else{
            return false;
        }
    }
}
double Bisektion1(double a, double b, double eps)
{
    double intervall_length = (b - a);
    if( intervall_length < eps)
        return (a + b)/2;
    else{
        double fa = myfunction(a);
        double fb = myfunction(b);
        if(!Einschluss(fa,fb))
        {
            cout << "There are no zero points within this intervall\n";
            return NOZEROPOINT;
        }
        else
        {
            double middle = (a + b)/2;
            double temp;
            while(abs(intervall_length) > eps)
            {
                temp = myfunction(middle);
                if(abs(fa * temp) > EPSILON)
                {
                    if((fa * temp) > 0)
                    {
                        a = middle;
                    }
                    else
                    {
                        b = middle;
                    }
                }
                else if(abs(fb * temp) > EPSILON)
                {
                    if((fb * temp) > 0)
                    {
                        b = middle;
                    }
                    else
                    {
                        a = middle;
                    }
                }
                else
                {
                    cout << "The function is too flat, the error too large\n";
                    cout << "Just ignore the eps and give back the middle point\n";
                    break;
                }
                fa = myfunction(a);
                fb = myfunction(b);
                middle = (a + b)/2;
            }
            
            return middle;
        }
    }
}

double Bisektion(double a, double b, double eps)
{
    double intervall_length = (b - a);
    if( intervall_length < eps)
        return (a + b)/2;
    else{
        double fa = myfunction(a);
        double fb = myfunction(b);
        if(!Einschluss(fa,fb))
        {
            cout << "There are no zero points within this intervall\n";
            return NOZEROPOINT;
        }
        else
        {
            double middle = (a + b)/2;
            double temp;
            int count = 0;
            while(abs(intervall_length) > eps)
            {
                count++;
                temp = myfunction(middle);
                if((fa * temp) > 0)
                {
                    a = middle;
                    fa = temp;
                }
                else
                {
                    b = middle;
                    fb = temp;
                }
                // fa = myfunction(a);
                // fb = myfunction(b);
                intervall_length = (b - a);
                middle = (a + b)/2;
            }
            cout << "Bisektion using " << count << " loops for " << a << " and " 
             << b << endl;
            return middle;
        }
    }
}
double myfunction(double a)
{
    double result;
    result = exp(sin(a)) - (a - 1)*(a - 6);
    return result;
}

double Sekantverfahren(double a, double b, double eps)
{
    double fa = myfunction(a);
    double fb = myfunction(b);
    if(!Einschluss(fa,fb))
    {
        cout << "There are no zeros in the intervall\n";
        return NOZEROPOINT;
    }
    else
    {
        double m1 = (fb * a - fa * b)/(fb - fa);
        double m2 = m1; // the m_{k+1}
        double temp = myfunction(m1);
        int count = 0;
        while(abs(m2 - m1) > eps || abs(temp) > eps)
        {
            count++;
            m1 = m2;
            if((fa * temp) > 0) 
            {
                fa = temp;
                a = m1;
            }
            else
            {
                fb = temp;
                b = m1;
            }
            m2 = (fb * a - fa * b)/(fb - fa);
            temp = myfunction(m2);
        }
        cout << "Sekante using " << count << " loops for " << a << " and " 
             << b << endl;
        return m2;
    }
}
double Newton(double a, double b, double eps)
{
    double fa = myfunction(a);
    double fb = myfunction(b);
    if(!Einschluss(fa, fb))
    {
        cout << "No zeros in the intervall\n";
        return NOZEROPOINT;
    }
    else
    {

        double m1 = (a + b)/2;
        double m2 = m1; // m_{k+1}
        double temp = myfunction(m1);
        double temp_deri = myderivative(m1);
        int count = 0;
        while(abs(m2 - m1) > eps || abs(temp) > eps)
        {
            count++;
            m1 = m2;
            m2 = m1 - temp/temp_deri;
            temp = myfunction(m2);
            temp_deri = myderivative(m2);            
        }
        cout << "The newton uses " << count << " iterations for a " << a << " and b"
             << b << endl;
        return m2;
    
    }
}
double myderivative(double a)
{
    double result = exp(sin(a))* cos(a) - 2*a + 7;
    return result;
}