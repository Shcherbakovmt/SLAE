#include <iostream>
#include "structs.hpp"


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
    const double Double_eps = 0.00000001;

    three_diag_matrix_system<double> matrix_system;


    Matrix<double> M(matrix_system.size, matrix_system.v1, matrix_system.v2, matrix_system.v3);
    //cout << "Matrix M:\n" << M << endl;

    Matrix<double> D(matrix_system.d); // вектор того что должны получить уже как матрица
    //cout << "D = \n" << D << endl;
    matrix_system.visualize_system();
    
    Matrix<double> X = matrix_system.solve();
    cout << "Equation X:\n" << X << endl << endl;
    
    
    if((D - M*X).norm() <= Double_eps)
    {
        cout << "Equation is correct\n";
        /*cout << "M:\n" << M << endl;
        cout << "X:\n" << X << endl;
        cout << "D:\n" << D << endl;
        cout  << "M*X: \n" << M*X << endl;
        cout << "norm = " << (M*X - D).norm() << endl; */
    }
    else
    {
        cout << "Fail\n";
        cout  << "M*X - D: \n" << M*X - D << endl;
        cout << "norm = " << (M*X - D).norm() << endl;
        cout << "Double_eps = " << Double_eps << endl;
    }
        
}