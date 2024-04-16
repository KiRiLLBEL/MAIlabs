#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <cmath>
#include <string>
#include <fstream>

namespace numeric {

    template<class T>
    class EigenResult {
    public:
        std::vector<T> eigenValues;
        std::vector<std::vector<T>> eigenVectors;

        explicit EigenResult(size_t size) : eigenValues(size), eigenVectors(size, std::vector<T>(size)) {}
    };

    template<class T, template<typename> class Container = std::vector>
    class AbstractMatrix {
    protected:
        size_t _rows;
        size_t _cols;
    public:
        virtual ~AbstractMatrix() = default;

        virtual size_t rows() const;

        virtual size_t cols() const;

        virtual std::unique_ptr<AbstractMatrix<T, Container>> transpose() const = 0;

        virtual Container<T> &operator[](size_t i) = 0;

        virtual const Container<T> &operator[](size_t i) const = 0;

    };

    template<class T, template<typename> class Container>
    size_t AbstractMatrix<T, Container>::rows() const {
        return _rows;
    }

    template<class T, template<typename> class Container>
    size_t AbstractMatrix<T, Container>::cols() const {
        return _cols;
    }

    template<class T>
    class Matrix : public AbstractMatrix<T, std::vector> {
    protected:
        std::vector<std::vector<T>> data;
        size_t _rows;
        size_t _cols;
    public:
        explicit Matrix(const std::vector<std::vector<T>> &data);

        explicit Matrix(size_t rows, size_t cols);

        Matrix(const Matrix &other);

        Matrix<T> &operator=(const Matrix &other);

        Matrix<T> &operator+=(const Matrix<T> &rhs);

        Matrix<T> &operator-=(const Matrix<T> &rhs);

        Matrix<T> &operator*=(const Matrix<T> &rhs);

        size_t rows() const override;

        size_t cols() const override;

        std::vector<T> &operator[](size_t i);

        const std::vector<T> &operator[](size_t i) const;

        std::unique_ptr<AbstractMatrix<T, std::vector>> transpose() const override;

        ~Matrix() override;
    };

    template<class T>
    class SquareMatrix : public AbstractMatrix<T, std::vector> {
    private:
        std::vector<std::vector<T>> data;
        size_t size;
    public:
        explicit SquareMatrix(const std::vector<std::vector<T>> &data);

        explicit SquareMatrix(size_t size);

        SquareMatrix(const SquareMatrix &other);

        SquareMatrix<T> &operator=(const SquareMatrix &other);

        SquareMatrix<T> &operator+=(const SquareMatrix<T> &rhs);

        SquareMatrix<T> &operator-=(const SquareMatrix<T> &rhs);

        SquareMatrix<T> &operator*=(const SquareMatrix<T> &rhs);

        size_t rows() const override;

        size_t cols() const override;

        std::vector<T> &operator[](size_t i);

        const std::vector<T> &operator[](size_t i) const;

        std::unique_ptr<AbstractMatrix<T, std::vector>> transpose() const override;

        explicit operator Matrix<T>() const;

        ~SquareMatrix() override;

    };

    template<class T>
    SquareMatrix<T>::operator Matrix<T>() const {
        Matrix<T> result(this->size, this->size);
        for (size_t i = 0; i < this->size; ++i) {
            for (size_t j = 0; j < this->size; ++j) {
                result[i][j] = this->data[i][j];
            }
        }
        return result;
    }

    template<class T>
    SquareMatrix<T> &SquareMatrix<T>::operator=(const SquareMatrix &other) {
        if (this != &other) {
            data = other.data;
            size = other.size;
        }
        return *this;
    }


    template<class T>
    SquareMatrix<T>::SquareMatrix(const SquareMatrix &other) : data(other.data), size(other.cols()) {

    }

    template<class T>
    Matrix<T> &Matrix<T>::operator=(const Matrix &other) {
        if (this != &other) {
            data = other.data;
            _rows = other._rows;
            _cols = other._cols;
        }
        return *this;
    }

    template<class T>
    Matrix<T>::Matrix(const Matrix &other) : data(other.data), _rows(other._rows), _cols(other._cols) {

    }

    template<typename T>
    class Row {
    private:
        std::map<size_t, T> row_data;

    public:
        T &operator[](size_t col) {
            return row_data[col];
        }

        const T &operator[](size_t col) const {
            auto it = row_data.find(col);
            if (it != row_data.end()) {
                return it->second;
            }
            static const T defaultValue{};
            return defaultValue;
        }
    };

    template<class T>
    class SparseMatrix : public AbstractMatrix<T, Row> {
    private:
        size_t _rows;
        size_t _cols;

        std::map<size_t, Row<T>> data;


    public:
        explicit SparseMatrix(size_t rows, size_t cols);

        SparseMatrix(const SparseMatrix &other);

        SparseMatrix<T> &operator=(const SparseMatrix &other);

        SparseMatrix<T> &operator+=(const SparseMatrix<T> &rhs);

        SparseMatrix<T> &operator-=(const SparseMatrix<T> &rhs);

        SparseMatrix<T> &operator*=(const SparseMatrix<T> &rhs);

        size_t rows() const override;

        size_t cols() const override;

        Row<T> &operator[](size_t row) override;

        const Row<T> &operator[](size_t row) const override;

        std::unique_ptr<AbstractMatrix<T, Row>> transpose() const override;

        ~SparseMatrix() override;
    };

    template<class T>
    Matrix<T>::Matrix(size_t rows, size_t cols) : data(rows, std::vector<T>(cols)), _rows(rows), _cols(cols) {

    }

    template<class T>
    Matrix<T>::Matrix(const std::vector<std::vector<T>> &data)
            : data(data), _rows(data.size()), _cols(data.begin()->size()) {
    }


    template<class T>
    size_t Matrix<T>::rows() const {
        return _rows;
    }

    template<class T>
    size_t Matrix<T>::cols() const {
        return _cols;
    }

    template<class T>
    std::vector<T> &Matrix<T>::operator[](size_t i) {
        return data[i];
    }

    template<class T>
    const std::vector<T> &Matrix<T>::operator[](size_t i) const {
        return data[i];
    }

    template<class T>
    std::unique_ptr<AbstractMatrix<T, std::vector>> Matrix<T>::transpose() const {
        auto transposedMatrix = std::make_unique<Matrix<T>>(_cols, _rows);
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = 0; j < cols(); ++j) {
                (*transposedMatrix)[j][i] = (*this)[i][j];
            }
        }
        return transposedMatrix;
    }

    template<class T>
    Matrix<T>::~Matrix() = default;

    template<class T>
    Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        Matrix<T> result(lhs.rows(), lhs.cols());
        for (size_t i = 0; i < lhs.rows(); ++i) {
            for (size_t j = 0; j < lhs.cols(); ++j) {
                result[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
        return result;
    }

    template<class T>
    std::vector<T> operator*(const std::vector<T> &vec, T scalar) {
        std::vector<T> result(vec.size());
        for (size_t i = 0; i < vec.size(); ++i) {
            result[i] = vec[i] * scalar;
        }
        return result;
    }

    template<class T>
    std::vector<T> operator*(T scalar, const std::vector<T> &vec) {
        return vec * scalar;
    }

    template<class T>
    Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }

        Matrix<T> result(lhs.rows(), lhs.cols());
        for (size_t i = 0; i < lhs.rows(); ++i) {
            for (size_t j = 0; j < lhs.cols(); ++j) {
                result[i][j] = lhs[i][j] - rhs[i][j];
            }
        }
        return result;
    }

    template<class T>
    Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs) {
        if (lhs.cols() != rhs.rows()) {
            throw std::invalid_argument(
                    "The number of columns in the first matrix must match the number of rows in the second.");
        }

        Matrix<T> result(lhs.rows(), rhs.cols());
        for (size_t i = 0; i < lhs.rows(); ++i) {
            for (size_t j = 0; j < rhs.cols(); ++j) {
                T sum = T();
                for (size_t k = 0; k < lhs.cols(); ++k) {
                    sum += lhs[i][k] * rhs[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    template<class T>
    Matrix<T> operator*(const Matrix<T> &matrix, T scalar) {
        Matrix<T> result(matrix.rows(), matrix.cols());
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                result[i][j] = matrix[i][j] * scalar;
            }
        }
        return result;
    }

    template<class T>
    Matrix<T> operator*(T scalar, const Matrix<T> &matrix) {
        return matrix * scalar;
    }

    template<class T>
    std::vector<T> operator*(const Matrix<T> &matrix, const std::vector<T> &vec) {
        if (matrix.cols() != vec.size()) {
            throw std::invalid_argument("The number of columns in the matrix must match the size of the vector.");
        }

        std::vector<T> result(matrix.rows(), T());
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t k = 0; k < matrix.cols(); ++k) {
                result[i] += matrix[i][k] * vec[k];
            }
        }
        return result;
    }

    template<class T>
    std::vector<T> operator*(const std::vector<T> &vec, const Matrix<T> &matrix) {
        if (vec.size() != matrix.rows()) {
            throw std::invalid_argument("The size of the vector must match the number of rows in the matrix.");
        }

        std::vector<T> result(matrix.cols(), T());
        for (size_t j = 0; j < matrix.cols(); ++j) {
            for (size_t i = 0; i < matrix.rows(); ++i) {
                result[j] += vec[i] * matrix[i][j];
            }
        }
        return result;
    }




    template<class T>
    Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &rhs) {
        if (_rows != rhs._rows || _cols != rhs._cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                data[i][j] += rhs.data[i][j];
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &rhs) {
        if (_rows != rhs._rows || _cols != rhs._cols) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                data[i][j] -= rhs.data[i][j];
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &rhs) {
        if (_cols != rhs._rows) {
            throw std::invalid_argument(
                    "The number of columns in the first matrix must match the number of rows in the second for multiplication.");
        }

        Matrix<T> result(_rows, rhs._cols);
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < rhs._cols; ++j) {
                for (size_t k = 0; k < _cols; ++k) {
                    result.data[i][j] += data[i][k] * rhs.data[k][j];
                }
            }
        }

        *this = std::move(result);
        return *this;
    }

    template<class T>
    SquareMatrix<T>::SquareMatrix(const std::vector<std::vector<T>> &data) : data(data), size(data.size()) {
        if (data.size() != data.begin()->size()) {
            throw std::invalid_argument("Not square matrix");
        }
    }

    template<class T>
    SquareMatrix<T>::SquareMatrix(size_t size) : size(size), data(size, std::vector<T>(size)) {
    }

    template<class T>
    size_t SquareMatrix<T>::rows() const {
        return size;
    }

    template<class T>
    size_t SquareMatrix<T>::cols() const {
        return size;
    }

    template<class T>
    std::vector<T> &SquareMatrix<T>::operator[](size_t i) {
        return data[i];
    }

    template<class T>
    const std::vector<T> &SquareMatrix<T>::operator[](size_t i) const {
        return data[i];
    }

    template<class T>
    std::unique_ptr<AbstractMatrix<T, std::vector>> SquareMatrix<T>::transpose() const {
        auto transposedMatrix = std::make_unique<SquareMatrix<T>>(size);
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = 0; j < cols(); ++j) {
                (*transposedMatrix)[j][i] = (*this)[i][j];
            }
        }
        return transposedMatrix;
    }

    template<class T>
    SquareMatrix<T>::~SquareMatrix() = default;

    template<class T>
    SquareMatrix<T> operator+(const SquareMatrix<T> &lhs, const SquareMatrix<T> &rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        SquareMatrix<T> result(lhs.cols());
        for (size_t i = 0; i < lhs.rows(); ++i) {
            for (size_t j = 0; j < lhs.cols(); ++j) {
                result[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
        return result;
    }

    template<class T>
    SquareMatrix<T> operator-(const SquareMatrix<T> &lhs, const SquareMatrix<T> &rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }

        SquareMatrix<T> result(lhs.cols());
        for (size_t i = 0; i < lhs.rows(); ++i) {
            for (size_t j = 0; j < lhs.cols(); ++j) {
                result[i][j] = lhs[i][j] - rhs[i][j];
            }
        }
        return result;
    }

    template<class T>
    SquareMatrix<T> operator*(const SquareMatrix<T> &lhs, const SquareMatrix<T> &rhs) {
        if (lhs.cols() != rhs.rows()) {
            throw std::invalid_argument(
                    "The number of columns in the first matrix must match the number of rows in the second.");
        }

        SquareMatrix<T> result(rhs.cols());
        for (size_t i = 0; i < lhs.rows(); ++i) {
            for (size_t j = 0; j < rhs.cols(); ++j) {
                T sum = T();
                for (size_t k = 0; k < lhs.cols(); ++k) {
                    sum += lhs[i][k] * rhs[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    template<class T>
    SquareMatrix<T> &SquareMatrix<T>::operator+=(const SquareMatrix<T> &rhs) {
        if (size != rhs.size || size != rhs.size) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                data[i][j] += rhs[i][j];
            }
        }
        return *this;
    }

    template<class T>
    SquareMatrix<T> &SquareMatrix<T>::operator-=(const SquareMatrix<T> &rhs) {
        if (size != rhs.size || size != rhs.size) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                data[i][j] -= rhs[i][j];
            }
        }
        return *this;
    }

    template<class T>
    SquareMatrix<T> &SquareMatrix<T>::operator*=(const SquareMatrix<T> &rhs) {
        if (size != rhs.size) {
            throw std::invalid_argument(
                    "The number of columns in the first matrix must match the number of rows in the second for multiplication.");
        }

        SquareMatrix<T> result(size);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < rhs.size; ++j) {
                for (size_t k = 0; k < size; ++k) {
                    result.data[i][j] += data[i][k] * rhs.data[k][j];
                }
            }
        }

        *this = std::move(result);
        return *this;
    }


    template<class T>
    SparseMatrix<T>::SparseMatrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {
    }

    template<class T>
    size_t SparseMatrix<T>::rows() const {
        return _rows;
    }

    template<class T>
    size_t SparseMatrix<T>::cols() const {
        return _cols;
    }

    template<class T>
    Row<T> &SparseMatrix<T>::operator[](size_t row) {
        return data[row];
    }

    template<class T>
    const Row<T> &SparseMatrix<T>::operator[](size_t row) const {
        auto it = data.find(row);
        if (it != data.end()) {
            return it->second;
        } else {
            static const Row<T> emptyRow{};
            return emptyRow;
        }
    }


    template<class T>
    std::unique_ptr<AbstractMatrix<T, Row>> SparseMatrix<T>::transpose() const {
        auto transposedMatrix = std::make_unique<SparseMatrix<T>>(cols(), rows());
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = 0; j < cols(); ++j) {
                (*transposedMatrix)[j][i] = (*this)[i][j];
            }
        }
        return transposedMatrix;
    }

    template<class T>
    SparseMatrix<T>::~SparseMatrix() = default;

    template<class T>
    SparseMatrix<T> operator+(const SparseMatrix<T> &lhs, const SparseMatrix<T> &rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        SparseMatrix<T> result(lhs.rows(), lhs.cols());
        for (size_t i = 0; i < lhs.rows(); ++i) {
            for (size_t j = 0; j < lhs.cols(); ++j) {
                result[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
        return result;
    }

    template<class T>
    SparseMatrix<T> operator-(const SparseMatrix<T> &lhs, const SparseMatrix<T> &rhs) {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }

        SparseMatrix<T> result(lhs.rows(), lhs.cols());
        for (size_t i = 0; i < lhs.rows(); ++i) {
            for (size_t j = 0; j < lhs.cols(); ++j) {
                result[i][j] = lhs[i][j] - rhs[i][j];
            }
        }
        return result;
    }

    template<class T>
    SparseMatrix<T> operator*(const SparseMatrix<T> &lhs, const SparseMatrix<T> &rhs) {
        if (lhs.cols() != rhs.rows()) {
            throw std::invalid_argument(
                    "The number of columns in the first matrix must match the number of rows in the second.");
        }

        SparseMatrix<T> result(lhs.rows(), rhs.cols());
        for (size_t i = 0; i < lhs.rows(); ++i) {
            for (size_t j = 0; j < rhs.cols(); ++j) {
                T sum = T();
                for (size_t k = 0; k < lhs.cols(); ++k) {
                    sum += lhs[i][k] * rhs[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    template<class T>
    SparseMatrix<T>::SparseMatrix(const SparseMatrix &other) : data(other.data), _rows(other._rows),
                                                               _cols(other._cols) {

    }

    template<class T>
    SparseMatrix<T> &SparseMatrix<T>::operator=(const SparseMatrix &other) {
        if (this != &other) {
            data = other.data;
            _rows = other._rows;
            _cols = other._cols;
        }
        return *this;
    }

    template<class T>
    SparseMatrix<T> &SparseMatrix<T>::operator+=(const SparseMatrix<T> &rhs) {
        if (_rows != rhs._rows || _cols != rhs._cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                data[i][j] += rhs[i][j];
            }
        }
        return *this;
    }

    template<class T>
    SparseMatrix<T> &SparseMatrix<T>::operator-=(const SparseMatrix<T> &rhs) {
        if (_rows != rhs._rows || _cols != rhs._cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                data[i][j] -= rhs[i][j];
            }
        }
        return *this;
    }

    template<class T>
    SparseMatrix<T> &SparseMatrix<T>::operator*=(const SparseMatrix<T> &rhs) {
        if (_cols != rhs._rows) {
            throw std::invalid_argument(
                    "The number of columns in the first matrix must match the number of rows in the second for multiplication.");
        }

        SparseMatrix<T> result(_rows, rhs._cols);
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < rhs._cols; ++j) {
                for (size_t k = 0; k < _cols; ++k) {
                    result[i][j] += data[i][k] * rhs[k][j];
                }
            }
        }

        *this = std::move(result);
        return *this;
    }

    template<class T>
    class LUMatrix {
    private:
        void init(const Matrix<T> &matrix);

    public:
        Matrix<T> L;
        Matrix<T> U;

        explicit LUMatrix(const Matrix<T> &matrix);

        Matrix<T> solve();

        T determinant();
    };

    template<class T>
    T LUMatrix<T>::determinant() {
        T deter = 1;
        for (size_t i = 0; i < U.rows(); ++i) {
            deter *= U[i][i];
        }

        return deter;
    }

    template<class T>
    Matrix<T> LUMatrix<T>::solve() {
        Matrix<T> result(U.rows(), U.cols() - U.rows());
        for (int k = 0; k < U.cols() - U.rows(); ++k) {
            for (int i = U.rows() - 1; i >= 0; --i) {
                T sum = 0.0;
                for (int j = i + 1; j < U.rows(); ++j) {
                    sum += U[i][j] * result[j][k];
                }
                result[i][k] = (U[i][U.rows() + k] - sum) / U[i][i];
            }
        }

        return result;
    }

    template<class T>
    void LUMatrix<T>::init(const Matrix<T> &matrix) {
        U = matrix;
        for (size_t i = 0; i < matrix.rows(); ++i) {
            T max = 0;
            size_t row = i;
            for (size_t k = i; k < matrix.rows(); ++k) {
                if (std::fabs(matrix[k][i]) > max) {
                    max = std::fabs(matrix[k][i]);
                    row = k;
                }
            }

            std::swap(U[i], U[row]);
            std::swap(L[i], L[row]);

            L[i][i] = 1;

            for (size_t j = i + 1; j < matrix.rows(); ++j) {
                double factor = U[j][i] / double(U[i][i]);
                L[j][i] = factor;
                for (size_t k = i; k < matrix.cols(); ++k) {
                    U[j][k] -= factor * U[i][k];
                }
            }
        }
    }

    template<class T>
    LUMatrix<T>::LUMatrix(const Matrix<T> &matrix) : L(matrix.rows(), matrix.cols()), U(matrix.rows(), matrix.cols()) {
        init(matrix);
    }

    template<class T>
    Matrix<T> inputMatrix(const std::string &path) {
        std::ifstream fin(path);
        size_t n, m;
        fin >> n >> m;
        Matrix<T> matrix(n, m);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                fin >> matrix[i][j];
            }
        }
        return matrix;
    }

    template<class T>
    std::vector<T> inputVector(const std::string &path) {
        std::ifstream fin(path);
        size_t n;
        fin >> n;
        std::vector<T> vec(n);
        for (size_t i = 0; i < n; ++i) {
            fin >> vec[i];
        }
        return vec;
    }

    template<class T>
    void printMatrix(const AbstractMatrix<T> &matrix) {
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.cols(); ++j) {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }

    template<class T>
    void printVector(const std::vector<T> &vector) {
        for (size_t i = 0; i < vector.size(); ++i)
            std::cout << vector[i] << " ";
    }

    template<class T>
    std::vector<T> tridiagonalSolve(const AbstractMatrix<T> &matrix, const std::vector<T> &b) {
        size_t n = matrix.rows();
        if (matrix.cols() != n || b.size() != n) {
            throw std::invalid_argument("Matrix must be square and the size of vector b must match.");
        }

        std::vector<T> C(n, 0);
        std::vector<T> D(n, 0);
        std::vector<T> x(n);

        C[0] = matrix[0][1] / matrix[0][0];
        D[0] = b[0] / matrix[0][0];

        for (size_t i = 1; i < n; ++i) {
            T m = 1 / (matrix[i][i] - matrix[i][i - 1] * C[i - 1]);
            C[i] = i < n - 1 ? matrix[i][i + 1] * m : 0;
            D[i] = (b[i] - matrix[i][i - 1] * D[i - 1]) * m;
        }

        x[n - 1] = D[n - 1];

        for (int i = n - 2; i >= 0; --i) {
            x[i] = D[i] - C[i] * x[i + 1];
        }

        return x;
    }

    template<class T>
    double norm(const AbstractMatrix<T> &matrix) {
        double norm = 0;
        for (size_t i = 0; i < matrix.rows(); ++i) {
            double currentSum = 0;
            for (size_t j = 0; j < matrix.cols(); ++j) {
                currentSum += fabs(matrix[i][j]);
            }
            norm = fmax(currentSum, norm);
        }

        return norm;
    }

    template<class T>
    double norm(const std::vector<T> &vector) {
        double norm = 0;
        for (size_t i = 0; i < vector.size(); ++i) {
            norm += pow(vector[i], 2);
        }
        return sqrt(norm);
    }

    template<class T>
    std::vector<T> diffVector(const std::vector<T> &lhs, const std::vector<T> &rhs) {
        if (lhs.size() != rhs.size())
            throw std::invalid_argument("invalid args");
        std::vector<T> result(lhs.size());
        for (size_t i = 0; i < lhs.size(); ++i) {
            result[i] = lhs[i] - rhs[i];
        }
        return result;
    }

    template<class T>
    std::vector<T> iterationSolve(const AbstractMatrix<T> &matrix, const std::vector<T> &b, T eps) {
        std::size_t n = matrix.rows();
        std::vector<T> beta(n, T());
        Matrix<T> alpha(n, n);
        for (std::size_t i = 0; i < n; ++i) {
            beta[i] = b[i] / matrix[i][i];
            for (std::size_t j = 0; j < n; ++j) {
                if (i == j) {
                    alpha[i][j] = 0;
                } else {
                    alpha[i][j] = -matrix[i][j] / matrix[i][i];
                }
            }
        }

        std::vector<T> x = beta;
        std::vector<T> x_next(n, T());

        bool continueIteration = true;

        double a = norm(alpha);

        std::cout << "\nNorm of matrix:\n";
        std::cout << a << "\n";

        size_t iter = 0;
        while (continueIteration) {
            continueIteration = false;

            for (std::size_t i = 0; i < n; ++i) {
                T sum = beta[i];
                for (std::size_t j = 0; j < n; ++j) {
                    sum += alpha[i][j] * x[j];
                }
                x_next[i] = sum;
            }

            if (a < 1) {
                if (a / (1 - a) * norm(diffVector(x_next, x)) > eps) {
                    continueIteration = true;
                }
            } else {
                if (norm(diffVector(x_next, x)) > eps) {
                    continueIteration = true;
                }
            }

            x = x_next;
            ++iter;
        }
        std::cout << "\nCount of iterations: " << iter << "\n";
        return x;
    }

    template<class T>
    std::vector<T> SeidelSolve(const AbstractMatrix<T> &matrix, const std::vector<T> &b, T eps) {
        std::size_t n = matrix.rows();
        std::vector<T> beta(n, T());
        Matrix<T> alpha(n, n);
        Matrix<T> CMatrix(n, n);
        for (std::size_t i = 0; i < n; ++i) {
            beta[i] = b[i] / matrix[i][i];
            for (std::size_t j = 0; j < n; ++j) {
                if (i == j) {
                    alpha[i][j] = 0;
                } else {
                    alpha[i][j] = -matrix[i][j] / matrix[i][i];
                }
            }
        }

        for(size_t i = 0; i < n; ++i) {
            for(size_t j = i; j < n; ++j) {
                CMatrix[i][j] = alpha[i][j];
            }
        }
        std::vector<T> x = beta;
        std::vector<T> x_next(n, T());

        bool continueIteration = true;

        double a = norm(alpha);
        double c = norm(CMatrix);
        std::cout << "\nNorm of matrix:\n";
        std::cout << a << "\n";
        std::cout << "\nNorm of C matrix:\n";
        std::cout << c << "\n";

        size_t iter = 0;
        while (continueIteration) {
            continueIteration = false;

            x_next = x;
            for (std::size_t i = 0; i < n; ++i) {
                T sum = beta[i];
                for (size_t j = 0; j < n; ++j) {
                    sum += alpha[i][j] * x_next[j];
                }
                x_next[i] = sum;
            }

            if (a < 1) {
                if (c / (1 - a) * norm(diffVector(x_next, x)) > eps) {
                    continueIteration = true;
                }
            } else {
                if (norm(diffVector(x_next, x)) > eps) {
                    continueIteration = true;
                }
            }

            x = x_next;
            ++iter;
        }
        std::cout << "\nCount of iterations: " << iter << "\n";
        return x;
    }

    template<class T>
    void applyRotation(AbstractMatrix<T> &matrix, std::vector<std::vector<T>> &eigenVectors, size_t p, size_t q, T c, T s) {
        size_t n = matrix.rows();
        for (size_t i = 0; i < n; ++i) {
            T mpi = matrix[i][p];
            T mqi = matrix[i][q];
            matrix[i][p] = c * mpi + s * mqi;
            matrix[i][q] = -s * mpi + c * mqi;

            T epi = eigenVectors[i][p];
            T eqi = eigenVectors[i][q];
            eigenVectors[i][p] = c * epi + s * eqi;
            eigenVectors[i][q] = -s * epi + c * eqi;
        }

        for (size_t j = 0; j < n; ++j) {
            T mpj = matrix[p][j];
            T mqj = matrix[q][j];
            matrix[p][j] = c * mpj + s * mqj;
            matrix[q][j] = -s * mpj + c * mqj;
        }
    }


    template<class T>
    EigenResult<T> findEigenvaluesAndEigenvectors(Matrix<T>& inputMatrix, double eps)  {
        size_t n = inputMatrix.rows();
        EigenResult<T> result(n);
        auto& eigenVectors = result.eigenVectors;
        auto& eigenValues = result.eigenValues;
        Matrix<T> matrix = inputMatrix;

        for (size_t i = 0; i < n; ++i) {
            eigenVectors[i][i] = 1;
        }

        double offDiagonalNorm;
        do {
            offDiagonalNorm = 0.0;
            for (size_t p = 0; p < n; ++p) {
                for (size_t q = p + 1; q < n; ++q) {
                    offDiagonalNorm += matrix[p][q] * matrix[p][q];
                }
            }

            if (sqrt(offDiagonalNorm) < eps)
                break;

            for (size_t p = 0; p < n; ++p) {
                for (size_t q = p + 1; q < n; ++q) {
                    T apq = matrix[p][q];
                    if (fabs(apq) > eps) {
                        T app = matrix[p][p];
                        T aqq = matrix[q][q];
                        T tau = (aqq - app) / (2 * apq);
                        T t = (tau / fabs(tau)) * (1.0 / (fabs(tau) + sqrt(1.0 + tau * tau)));
                        T c = 1 / sqrt(1 + t * t);
                        T s = t * c;

                        applyRotation(matrix, eigenVectors, p, q, c, s);
                    }
                }
            }
        } while (true);

        for (size_t i = 0; i < n; ++i) {
            eigenValues[i] = matrix[i][i];
        }

        return result;
    }

} // numeric

#endif //MATRIX_H
