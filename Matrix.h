#include <iostream>
#include <fstream>
using namespace std;

void getMatrix(double m[], string s);

class Matrix {
    private:
        struct RefMatrix;
        RefMatrix* matrix;
        double read(int row, int col) const;
        void write(int row, int col, double value);

    public:
        class RefElement;
        Matrix();
        Matrix(int rows, int cols);
        Matrix(string path);
        Matrix(const Matrix& other);
        ~Matrix();
        Matrix& operator+=(const Matrix& m);
        Matrix& operator-=(const Matrix& m);
        Matrix& operator*=(const Matrix& m); 
        friend Matrix operator+(const Matrix& m1, const Matrix& m2);
        friend Matrix operator-(const Matrix& m, const Matrix& m2);
        friend Matrix operator*(const Matrix& m, const Matrix& m2);
        friend bool operator==(const Matrix& m1, const Matrix& m2); 
        friend bool operator!=(const Matrix& m1, const Matrix& m2);
        friend ostream& operator<<(ostream& os, const Matrix& m);
        friend ifstream& operator>>(ifstream& ifs, Matrix& m);
        RefElement operator()(int row, int col);
};

struct Matrix::RefMatrix {
    public:
        double** data;
        int rows;
        int cols;
        int n;

        RefMatrix();
        RefMatrix(int rows, int cols);
        RefMatrix(const RefMatrix& other);
        RefMatrix(string path);
        ~RefMatrix();
        RefMatrix* detach();
};

class Matrix::RefElement {
    private:
        friend class Matrix;
        Matrix& m;
        int row;
        int col;

    public:
        RefElement(Matrix& mm, int r, int c) : m(mm), row(r - 1), col(c - 1) {};
        operator double() const;
        Matrix::RefElement& operator=(double value);
        Matrix::RefElement& operator=(const RefElement& ref);
};