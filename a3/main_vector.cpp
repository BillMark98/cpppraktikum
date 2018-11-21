#include <iostream>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
typedef vector<double> dVector;
typedef const vector<double> const_dVector;
typedef vector<double>::iterator dViter;
typedef const vector<double>::iterator const_dViter;
void Ausgabe(dVector & arr);
double Durchschnitt(const_dVector &);
int min_pos(const dVector &);
void sortiere(double * feld, int n);
void swap(double & a, double & b);
void umdrehen(double * feld, int n);
double * glue( const double * feld1, int n1, const double * feld2, int n2);
int binSuche_pos(double x, const double * sfeld, int n);
double * merge(const double * sfeld1, int n1, const double *sfeld2,int n2);
double * merge_sort(double * feld, int n);
int main()
{

    dVector arr; //{47,11,0,8,5};
    arr[0] = 47; 
    arr[1] = 11;
    arr[2] = 0;
    arr[3] = 8;
    arr[4] = 5;
    Ausgabe(arr);
    // cout << "Mean: " << Durchschnitt(arr) << endl;
    // cout << "Min pos: " << min_pos(arr) << endl;
    // cout << "Now sorting\n";
    // sortiere(arr,5);
    // Ausgabe(arr,5);
    /*
    cout << "rotate the array\n";
    umdrehen(arr,5);
    Ausgabe(arr,5);
    cout << "Gluing two arrays\n";
    double * newarray = glue(arr,5,arr,5);
    Ausgabe(newarray,10);
    delete [] newarray;
    umdrehen(arr,5);
    cout << "Binary search: 47\n";
    cout << "Index: " << binSuche_pos(47,arr,5) << endl;
    cout << "Binary search: 42\n";
    cout << "Index: " << binSuche_pos(42,arr,5) << endl;
    cout << "Binary search: 8\n";
    cout << "Index: " << binSuche_pos(8,arr,5) << endl;

    */
    // double arr2[] = {1,2,3,6,7,10,12,19,21,30};
    // double * newarr = merge(arr,5,arr2,10);
    // Ausgabe(newarr,15);
    // delete [] newarr;
    // double arr3[] = {1,7,4,69,23,6,12,78};
    // double * newaf = merge_sort(arr3,8);
    // Ausgabe(newaf,8);
    // delete [] newaf;
    return 0;
}
void Ausgabe(dVector & arr)
{
    for(dViter pd = arr.begin(); pd != arr.end(); pd++)
    {
        cout << * pd << ' ';
    }
    cout << endl;
}

int min_pos(const dVector &);
double Durchschnitt(dVector &arr)
{
    double sum = 0;
    int n = arr.size();
    for( dViter pd = arr.begin(); pd != arr.end(); pd++)
    {
        sum += *pd;
    }
    double result = (double)sum/n;
    return result;
}
int min_pos(const double * feld, int n)
{
    int min = 0;
    for(int index = 0; index < n; index++)
    {
        if(feld[index] < feld[min])
        {
            min = index;
        }
    }
    return min;
}
// void sortiere(double * feld, int n)
// {

//     for(int i = 0;i < n; i++)
//     {
//         int j = min_pos(feld + i, n-i);
//         swap(feld[i],feld[i+j]);
//     }
// }
// void swap(double & a, double & b)
// {
//     double temp = a;
//     a = b;void merge_sort(double * feld, int n);
//     b = temp;
// }
// void umdrehen(double * feld, int n)
// {int i = 0, j = n-1;
//     int middle = (i + j)/2;

//     for(int i = 0, j = n-1; i < j; i++,j--)
//     {
//         swap(feld[i],feld[j]);
//     }
// }

// double * glue( const double * feld1, int n1, const double * feld2, int n2)
// {
//     double * newarray = new double[n1 + n2];
//     for(int i = 0; i < n1; i++)
//     {
//         newarray[i] = feld1[i];
//     }
//     for(int i = n1,j = 0; i < n1 + n2; i++,j++)
//     {
//         newarray[i] = feld2[j];
//     }
//     return newarray;
// }


// int binSuche_pos(double x, const double * sfeld, int n)
// {
//     int left = 0,right = n-1;
//     int middle = (left + right) /2;
//     while(left <= right)
//     {
//         double temp = sfeld[middle];
//         if(x < temp)
//         {
//             right = middle - 1;
//         }
//         else if( x > temp)
//         {
//             left = middle + 1;
//         }
//         else
//         {
//             return middle; // index found
//         }
//         middle = (left + right)/2;
//     }
//     return -1; // index not fint i = 0, j = n-1;
// }
// double * merge(const double * sfeld1, int n1, const double *sfeld2,int n2)
// {
//     double * newfeld = new double[n1 + n2];
//     int i = 0, j = 0,  k = 0;
//     while( i < n1 || j < n2)
//     {
//         if(i >= n1)
//         {
//             newfeld[k] = sfeld2[j];
//             j++;
//             k++;
//             continue;
//         }
//         if(j >= n2)
//         {void merge_sort(double * feld, int n);
//             newfeld[k] = sfeld1[i];
//             i++;
//             k++;
//             continue;
//         }
//         if(sfeld1[i] < sfeld2[j] && i < n1)
//         {
//             newfeld[k] = sfeld1[i];
//             i++;
//         }
//         else if(sfeld2[j] < sfeld1[i] && j < n2)
//         {
//             newfeld[k] = sfeld2[j];
//             j++;
//         }
//         k++;

//     }
//     return newfeld;
// }
// double * merge_sort(double * feld, int n)
// {

//     if( n <= 1)
//     {
//         return feld;
//     }
//     else{
//         int i = 0, j = n-1;
//         int middle = (i + j)/2;
//         double * feld1 = merge_sort(feld,(middle + 1));
//         double * feld2 = merge_sort((feld + middle+1),(n - middle - 1));
//         double *newfeld = merge(feld1, (middle + 1), feld2,(n - middle - 1));
//         if((middle + 1) > 1)
//         {
//             delete [] feld1;
//         }
//         if((n - middle - 1) > 1)
//         {
//             delete [] feld2;
//         }
//         return newfeld;
//     }
// }
