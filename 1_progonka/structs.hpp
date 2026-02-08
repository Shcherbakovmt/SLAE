#include <vector>
#include <iostream>

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
};
