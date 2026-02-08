#include <iostream>
#include "structs.hpp"
#include "matrix.hpp"



template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v)
{
    for(auto x : v)
    {
        cout << x << " ";
    }
    return os;
}
int main()
{
    const double Double_eps = 0.000001;
    int s = 0;
    cout << "Enter size of matrix \n";
    cin >> s;
    while(s < 1)
    {
        cout << "Size must be > 0\nEnter again size\n";
        cin >> s;
    }
    
    const int size = s;
    vector<double> first(size);
    vector<double> second(size);
    vector<double> third(size);

    first[size-1] = 0;
    if(size != 1)
    {
        cout << "Enter 1 diag (" << size-1 << " numbers)\n";
        for(int i = 0; i < size-1; i++)
        {
            cin >> first[i];
        }
    }


    cout << "Enter 2 diag (" << size << " numbers)\n";
    for(int i = 0; i < size; i++)
    {
        cin >> second[i];
    }
    
    if(size != 1)
    {
        cout << "Enter 3 diag (" << size-1 << " numbers)\n";
        for(int i = 1; i < size; i++)
        {
            cin >> third[i];
        }
    }

    third[0] = 0;
    cout << endl;





    
    
    cout << "Enter column d (" << size << " numbers)\n";

    vector<double> d(size);

    for(int i = 0; i < size; i++)
    {
        cin >> d[i];
    }
    //cout << d << endl;
    three_diag_matrix_system matrix_system(first,second,third,d);
    
    
    vector<double> p(size);
    vector<double> q(size);
    p[0] = -first[0]/second[0];
    q[0] = d[0]/second[0];

    for(int i = 0; i < size-1; i++)
    {
        p[i+1] = -first[i]/(third[i] * p[i] + second[i]);
        q[i+1] = (d[i] - third[i]*q[i])/(third[i]*p[i] + second[i]);
    }

    vector<double> x(size);
    x[size-1] = (d[size-1] - third[size-1]*q[size-1])/(third[size-1]*p[size-1] + second[size-1]);

    for(int i = size-1; i > 0; i--)
    {
        x[i-1] = p[i] * x[i] + q[i];
    }

    /*
    cout << "first = " << first << endl;
    cout << "second = " << second << endl;
    cout << "third = " << third << endl;
    

    cout << endl;
    
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    
    cout << endl;
    
    cout << "x = " << x << endl;
    */

    matrix_system.visualize_system();
    
    Matrix<double> M(size, first,second,third);
    cout << "Matrix M:\n" << M << endl;
    
    Matrix<double> X(x); // вектор решения уже как матрица
    cout << "Equation X:\n" << X << endl;

    Matrix<double> D(d); // вектор того что должны получить уже как матрица
    cout << "D = \n" << D << endl;
    

    cout << "M * X = \n" << M * X << endl;

    if((D - M*X).norm() <= Double_eps)
    {
        cout << "Equation is correct\n";
    }
    else
    {
        cout << "Fail\n";
        cout << M*X - D << endl;
        cout << "norm = " << (M*X - D).norm() << endl;
        cout << "Double_eps = " << Double_eps << endl;
    }
    
    
}