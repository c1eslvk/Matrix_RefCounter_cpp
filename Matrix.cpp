#include <iostream>
#include <string>
#include "Matrix.h"
#include "Exceptions.h"

using namespace std;

int countCols(string s);
void checkNullPtr(double** ptr);
void checkInput(int a, int b);

Matrix::Matrix() {
    matrix = new RefMatrix();
}

Matrix::Matrix(int rows, int cols) {
    checkInput(rows, cols);
    matrix = new RefMatrix(rows, cols);
}

void checkInput(int a, int b) {
    if (a < 1 || b < 1) {
        throw InvalidInputException();
    }
}

Matrix::Matrix(const Matrix& other) {
    other.matrix->n++;
    matrix = other.matrix;
}

Matrix::Matrix(string path) {
    matrix = new RefMatrix(path);
}

Matrix::~Matrix() {
    if (--matrix->n == 0) {
        delete matrix;
    }
}

void Matrix::write(int row, int col, double value) {
    if (row < 0 || row >= matrix->rows || col < 0 || col >= matrix->cols) {
        throw IndexOutOfBoundsException();
    }

    matrix = matrix->detach();

    matrix->data[row][col] = value;
}

double Matrix::read(int row, int col) const {
    if (row < 0 || row >= matrix->rows || col < 0 || col >= matrix->cols) {
        throw IndexOutOfBoundsException();
    }

    return matrix->data[row][col];
}

ostream& operator<<(ostream& os, const Matrix& m) {
    for (int i = 0; i < m.matrix->rows; i++) {
        for (int j = 0; j < m.matrix->cols; j++) {
            os << m.matrix->data[i][j] << "  ";
        }
        os << endl;
    }
    return os;
}

ifstream& operator>>(ifstream& ifs, Matrix& m) {
    if (!ifs) {
        throw InvalidFileException();
    }   

    int ifsRows = 0;
    int ifsCols = 0;

    ifs >> ifsRows;
    ifs >> ifsCols;

    if (ifsRows > m.matrix->rows || ifsCols > m.matrix->cols) {
        throw InvalidSizeException();
    }

    m.matrix = m.matrix->detach();

    for (int i = 0; i < ifsRows; i++) {
        for (int j = 0; j < ifsCols; j++) {
            ifs >> m.matrix->data[i][j];
        }
    }
    return ifs;
}

bool operator==(const Matrix& m1, const Matrix& m2) {
    if (m1.matrix->rows != m2.matrix->rows || m1.matrix->cols != m2.matrix->cols) {
        return false;
    }
    else {
        for (int i = 0; i < m1.matrix->rows; i++) {
            for (int j = 0; j < m1.matrix->cols; j++) {
                if (m1.matrix->data[i][j] != m2.matrix->data[i][j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& m1, const Matrix& m2) {
    if (m1.matrix->rows != m2.matrix->rows || m1.matrix->cols != m2.matrix->cols) {
        return true;
    }
    else {
        for (int i = 0; i < m1.matrix->rows; i++) {
            for (int j = 0; j < m1.matrix->cols; j++) {
                if (m1.matrix->data[i][j] != m2.matrix->data[i][j]) {
                    return true;
                }
            }
        }
    }
    return false;
}

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    if (m1.matrix->cols != m2.matrix->cols || m1.matrix->rows != m2.matrix->rows) {
        throw InvalidSizeException();
    }

    Matrix temp(m1.matrix->rows, m1.matrix->cols);

    for (int i = 0; i < temp.matrix->rows; i++) {
        for (int j = 0; j < temp.matrix->cols; j++) {
            temp.matrix->data[i][j] += m2.matrix->data[i][j];
        }
    }

    return temp;
}


Matrix operator-(const Matrix& m1, const Matrix& m2) {
    if (m1.matrix->cols != m2.matrix->cols || m1.matrix->rows != m2.matrix->rows) {
        throw InvalidSizeException();
    }

    Matrix temp(m1.matrix->cols, m1.matrix->rows);

    for (int i = 0; i < temp.matrix->rows; i++) {
        for (int j = 0; j < temp.matrix->cols; j++) {
            temp.matrix->data[i][j] = m1.matrix->data[i][j] - m2.matrix->data[i][j];
        }
    }

    return temp;
}

Matrix& Matrix::operator+=(const Matrix& m) {
    if (matrix->cols != m.matrix->cols || matrix->rows != m.matrix->rows) {
        throw InvalidSizeException();
    }

    matrix = matrix->detach();

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            matrix->data[i][j] += m.matrix->data[i][j];
        }
    }    

    return *this; 
}

Matrix& Matrix::operator-=(const Matrix& m) {
    if (matrix->cols != m.matrix->cols || matrix->rows != m.matrix->rows) {
        throw InvalidSizeException();
    }

    matrix = matrix->detach();

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            matrix->data[i][j] -= m.matrix->data[i][j];
        }
    }    

    return *this; 
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    if (m1.matrix->cols != m2.matrix->rows) {
        throw InvalidSizeException();
    }
    
    Matrix temp(m1.matrix->rows, m2.matrix->cols);

    for (int i = 0; i < m1.matrix->rows; ++i) {
        for (int j = 0; j < m2.matrix->cols; ++j) {
            for (int k = 0; k < m1.matrix->cols; ++k) {
                temp.matrix->data[i][j] += m1.matrix->data[i][k] * m2.matrix->data[k][j];
            }
        }
    }

    return temp;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    if (matrix->cols != m.matrix->rows) {
        throw InvalidSizeException();
    }

    Matrix temp(*this);

    matrix = matrix->detach();

    for (int i = 0; i < this->matrix->rows; i++) {
        delete[] this->matrix->data[i];
    }

    delete[] this->matrix->data;

    this->matrix->rows = temp.matrix->rows;
    this->matrix->cols = m.matrix->cols;
    this->matrix->data = new double*[matrix->rows];
    checkNullPtr(this->matrix->data);

    for (int i = 0; i < this->matrix->rows; i++) {
        this->matrix->data[i] = new double[this->matrix->cols];
        checkNullPtr(this->matrix->data);
    }

    for (int i = 0; i < this->matrix->rows; i++) {
        for (int j = 0; j < this->matrix->cols; j++) {
            this->matrix->data[i][j] = 0;
        }
    }

    for (int i = 0; i < temp.matrix->rows; ++i) {
        for (int j = 0; j < m.matrix->cols; ++j) {
            for (int k = 0; k < temp.matrix->cols; ++k) {
                this->matrix->data[i][j] += temp.matrix->data[i][k] * m.matrix->data[k][j];
            }
        }
    }

    return *this;
}

Matrix::RefElement Matrix::operator()(int row, int col) {
    if (row < 0 || row > matrix->rows || col < 0 || col > matrix->cols) {
        throw IndexOutOfBoundsException();
    }

    return RefElement(*this, row, col);
}