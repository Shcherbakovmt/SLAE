#include <vector>
#include <iostream>
#include "matrix.hpp"

using std::vector;
using std::array;
using std::cout;
using std::cin;
using std::endl;


template <typename T>
class three_diag_matrix_system
{
public:
    std::vector<T> v1;
    std::vector<T> v2;
    std::vector<T> v3;

    std::vector<T> d; 
    int size = 0;

    three_diag_matrix_system()
    {
        int s = 0;
        cout << "Enter size of matrix \n";
        cin >> s;
        while(s < 1)
        {
            cout << "Size must be > 0\nEnter again size\n";
            cin >> s;
        }
        
        this->size = s;
        v1.resize(size);
        v2.resize(size);
        v3.resize(size);
        d.resize(size);

        
        v1[size-1] = 0;
        if(size != 1)
        {
            cout << "Enter 1 diag (" << size-1 << " numbers)\n";
            for(int i = 0; i < size-1; i++)
            {
                cin >> v1[i];
            }
        }


        cout << "Enter 2 diag (" << size << " numbers)\n";
        for(int i = 0; i < size; i++)
        {
            cin >> v2[i];
        }
    
        if(size != 1)
        {
            cout << "Enter 3 diag (" << size-1 << " numbers)\n";
            for(int i = 1; i < size; i++)
            {
                cin >> v3[i];
            }
        }

        v3[0] = 0;
        cout << endl;

        cout << "Enter column d (" << size << " numbers)\n";


        for(int i = 0; i < size; i++)
        {
            cin >> d[i];
        }

        
    }

    three_diag_matrix_system(vector<T> first, vector<T> second, vector<T> three, vector<T> dd)
    {
        this->v1 = first;
        this->v2 = second;
        this->v3 = three;
        this->d = dd;
        this->size = second.size();
    }
    void visualize_system()
    {

        cout << "\nVisualysing system:\n";
        if(size == 1)
        {
            cout << v2[0] << endl;
            return;
        }

        else if(size < 1)
        {
            cout << "Error, size must be > 0\n";
            return;
        }

        else
        {
            cout << v2[0] << " " << v1[1] << " ";
            for(int _ = 0; _ < size-2; _++) cout << "0 ";
            cout << " x0   " << d[0] << endl;

            for(int n = 3; n < size+1; n++)
            {
                for(int _ = 0; _ < n-3; _++) cout << "0 ";
                cout << v3[n-2] << " " << v2[n-2] << " " << v1[n-2] << " ";
                for(int _ = 0; _ < size - n; _++) cout << "0 ";
                cout << " x" << n-2 << "   " << d[n-2] << endl;
            }

            for(int _ = 0; _ < size-2; _++) cout << "0 ";
            cout << v3[size-2] << " " << v2[size-1] << "  x" << size-1 << "   " << d[size-1] << endl;
        }
        cout << endl;
    }

    Matrix<T> solve()
    {
        vector<double> p(size);
        vector<double> q(size);
        p[0] = -v1[0]/v2[0];
        q[0] = d[0]/v2[0];

        for(int i = 0; i < size-1; i++)
        {
            p[i+1] = -v1[i]/(v3[i] * p[i] + v2[i]);
            q[i+1] = (d[i] - v3[i]*q[i])/(v3[i]*p[i] + v2[i]);
        }

        vector<double> x(size);
        x[size-1] = (d[size-1] - v3[size-1]*q[size-1])/(v3[size-1]*p[size-1] + v2[size-1]);

        for(int i = size-1; i > 0; i--)
        {
            x[i-1] = p[i] * x[i] + q[i];
        }
        return Matrix<T>(x);

    }
};


