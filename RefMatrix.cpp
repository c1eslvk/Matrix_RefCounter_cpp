#include <iostream>
#include <fstream>
#include "Matrix.h"
#include "Exceptions.h"

using namespace std;

void getMatrix(double m[], string s);
int countCols(string s);
void checkNullPtr(double** ptr);

Matrix::RefMatrix::RefMatrix() {
    rows = 0;
    cols = 0;
    data = NULL;
    n = 1;
}

Matrix::RefMatrix::RefMatrix(int rows, int cols) {
    n = 1;
    this->rows = rows;
    this->cols = cols;
    data = new double*[rows];
    checkNullPtr(data);
    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
        checkNullPtr(data);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = 0;
        }
    }
}

Matrix::RefMatrix::RefMatrix(const RefMatrix& other) {
    n = 1;
    rows = other.rows;
    cols = other.cols;
    
    data = new double*[rows];
    checkNullPtr(data);

    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
        checkNullPtr(data);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::RefMatrix::RefMatrix(string path) {
    n = 1;
    ifstream ifs(path);

    if (!ifs) {
        throw InvalidFileException();
    }  

    rows = 0;
    cols = 0;
    ifs >> rows;
    ifs >> this->cols;    

    data = new double*[rows];
    checkNullPtr(data);
    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
        checkNullPtr(data);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ifs >> data[i][j];
        }
    }        
}

Matrix::RefMatrix::~RefMatrix() {
    for (int i = 0; i < rows; i++) {
        delete[] data[i];
    }

    delete[] data;
}

Matrix::RefMatrix* Matrix::RefMatrix::detach() {
    if (n == 1) {
        return this;
    }
    RefMatrix* temp = new RefMatrix(*this);
    n--;
    return temp;
}

void getMatrix(double m[], string s) {
    string entry;
    int i = 0;
    for (size_t j = 0; j < s.length(); j++) {
        if (s[j] == ' ' || s[j] == '\n') {
            m[i] = stod(entry);
            entry = "";
            i++;
        }
        else {
            entry = entry + s[j];
        }
    }
}

int countCols(string s) {
    int cols = 0;
    int i = 0;
    while (s.at(i) != '\n') {
        if (s.at(i) == ' ') {
            cols++;
        }
        i++;
    }
    cols++;
    return cols;
}

void checkNullPtr(double** ptr) {
    if (ptr == NULL) {
        throw NullPointerException();
    }
}