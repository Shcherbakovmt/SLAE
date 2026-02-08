#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

template<typename T>
class Matrix {
private:
    size_t rows_;
    size_t cols_;
    std::vector<std::vector<T>> data;

public:
    // Конструктор по умолчанию
    Matrix() : rows_(0), cols_(0) {}
    
    Matrix(const std::vector<T>& vec) : rows_(vec.size()), cols_(1), data(vec.size(), std::vector<T>(1)) 
    {
        for (size_t i = 0; i < rows_; ++i) 
        {
            data[i][0] = vec[i];
        }
    }

    // Конструктор с указанием размеров (инициализирует нулями)
    Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols), 
                                       data(rows, std::vector<T>(cols, T{})) {}

    // Конструктор из вектора векторов
    Matrix(const std::vector<std::vector<T>>& arr) : 
        rows_(arr.size()), cols_(arr.empty() ? 0 : arr[0].size()), data(arr) 
    {
        // Проверка, что все строки имеют одинаковую длину
        for (const auto& row : data) {
            if (row.size() != cols_) {
                throw std::invalid_argument("All rows must have the same length");
            }
        }
    }

    // Конструктор трехдиагональной матрицы
    Matrix(size_t size, 
           const std::vector<T>& first,   // диагональ над главной (первый элемент игнорируется)
           const std::vector<T>& second,  // главная диагональ
           const std::vector<T>& third)   // диагональ под главной (последний элемент игнорируется)
        : rows_(size), cols_(size), data(size, std::vector<T>(size, T{}))
    {
        // Проверка размеров
        if (first.size() != size || second.size() != size || third.size() != size) {
            throw std::invalid_argument("All vectors must have size equal to matrix size");
        }

        // Заполнение трех диагоналей
        for (size_t i = 0; i < size; ++i) {
            // Главная диагональ
            data[i][i] = second[i];
            
            // Диагональ над главной (кроме последней строки и первого элемента)
            if (i < size - 1) {
                data[i][i + 1] = first[i];  // пропускаем first[0]
            }
            
            // Диагональ под главной (кроме первой строки и последнего элемента)
            if (i > 0) {
                data[i][i - 1] = third[i];  // пропускаем third[size-1]
            }
        }
    }

    // Конструктор копирования
    Matrix(const Matrix& other) = default;
    
    // Конструктор перемещения
    Matrix(Matrix&& other) = default;
    
    // Оператор присваивания копированием
    Matrix& operator=(const Matrix& other) = default;
    
    // Оператор присваивания перемещением
    Matrix& operator=(Matrix&& other) = default;

    // Доступ к элементам
    T& operator()(size_t row, size_t col) {
        if (row >= rows_ || col >= cols_) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }

    const T& operator()(size_t row, size_t col) const {
        if (row >= rows_ || col >= cols_) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }

    // Сложение матриц
    Matrix operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition");
        }
        
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Вычитание матриц
    Matrix operator-(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
        }
        
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Умножение матриц
    Matrix operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument(
                "Number of columns in first matrix must equal number of rows in second matrix");
        }
        
        Matrix result(rows_, other.cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < other.cols_; ++j) {
                T sum = T{};
                for (size_t k = 0; k < cols_; ++k) {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    // Умножение на скаляр
    Matrix operator*(const T& scalar) const {
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    // Деление на скаляр
    Matrix operator/(const T& scalar) const {
        if (scalar == T{}) {
            throw std::invalid_argument("Division by zero");
        }
        
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    // Норма матрицы по максимальному значению
    T norm() const {
        if (rows_ == 0 || cols_ == 0) {
            return T{};
        }
        
        T maxVal = std::abs(data[0][0]);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                T absVal = std::abs(data[i][j]);
                if (absVal > maxVal) {
                    maxVal = absVal;
                }
            }
        }
        return maxVal;
    }

    // Проверка на строгое равенство
    bool operator==(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            return false;
        }
        return data == other.data;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    // Получение количества строк и столбцов
    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }

    // Проверка, является ли матрица квадратной
    bool isSquare() const { return rows_ == cols_; }

    // Транспонирование матрицы
    Matrix transpose() const {
        Matrix result(cols_, rows_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    // Изменение размера матрицы
    void resize(size_t new_rows, size_t new_cols) {
        data.resize(new_rows);
        for (auto& row : data) {
            row.resize(new_cols, T{});
        }
        rows_ = new_rows;
        cols_ = new_cols;
    }

    // Получение строки матрицы
    std::vector<T> getRow(size_t row) const {
        if (row >= rows_) {
            throw std::out_of_range("Row index out of range");
        }
        return data[row];
    }

    // Получение столбца матрицы
    std::vector<T> getColumn(size_t col) const {
        if (col >= cols_) {
            throw std::out_of_range("Column index out of range");
        }
        
        std::vector<T> column(rows_);
        for (size_t i = 0; i < rows_; ++i) {
            column[i] = data[i][col];
        }
        return column;
    }

    // Вывод матрицы
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (size_t i = 0; i < matrix.rows_; ++i) {
            os << "[";
            for (size_t j = 0; j < matrix.cols_; ++j) {
                os << std::setw(6) << matrix.data[i][j];
                if (j < matrix.cols_ - 1) {
                    os << " ";
                }
            }
            os << "]";
            if (i < matrix.rows_ - 1) {
                os << "\n";
            }
        }
        return os;
    }

    // Получение внутренних данных (для тестирования)
    const std::vector<std::vector<T>>& getData() const {
        return data;
    }
};

// Умножение скаляра на матрицу (левое умножение)
template<typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix) {
    return matrix * scalar;
}
