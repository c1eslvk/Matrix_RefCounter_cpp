#include <iostream>
#include <fstream>
#include "Matrix.h"
#include "Exceptions.h"

using namespace std;

void test(Matrix& m1, Matrix& m2);
void display(const Matrix& m1, const Matrix& m2);
void testCompare(const Matrix& m1, const Matrix& m2);
void testBasicOperators(const Matrix& m1, const Matrix& m2);
void testAssignmentOperators(Matrix& m1, Matrix& m2);
void testElementAcces(Matrix& m);

int main() {
    string path = "InputFile.txt";
    ifstream ifs(path, ifstream::in);

    try {
        Matrix m1(2, 2);
        Matrix m2(2, 2);

        ifs >> m2;

        m1(1, 1) = 2;
        m1(1, 2) = 5;
        m1(2, 1) = 7;
        m1(2, 2) = 1;

        test(m1, m2);

    } catch (NullPointerException& e) {
        cout << e.what() << endl;
    } catch (InvalidInputException& e) {
        cout << e.what() << endl;
    } catch (IndexOutOfBoundsException& e) {
        cout << e.what() << endl;
    } catch (InvalidFileException& e) {
        cout << e.what() << endl;
    } catch (InvalidSizeException& e) {
        cout << e.what() << endl;
    }

    ifs.close();

    return 0;
}

void test(Matrix& m1, Matrix& m2) {
    display(m1, m2);
    testCompare(m1, m2);
    testBasicOperators(m1, m2);
    testAssignmentOperators(m1, m2);
    testElementAcces(m2);
}

void display(const Matrix& m1, const Matrix& m2) {
    cout << "Matrix m1:" << endl << m1 << endl;
    cout << "Matrix m2:" << endl << m2 << endl;
}

void testCompare(const Matrix& m1, const Matrix& m2) {
    if (m1 == m2) {
        cout << "m1 and m2 are the same" << endl << endl;
    }
    else {
        cout << "m1 and m2 are not the same" << endl << endl;
    }

    if (m1 != m2) {
        cout << "m1 and m2 are not the same" << endl << endl;
    }
    else {
        cout << "m1 and m2 are the same" << endl << endl;
    }
}

void testBasicOperators(const Matrix& m1, const Matrix& m2) {
    try {
        cout << "Sum of m1 and m2:"<< endl << m1 + m2 << endl;
    } catch (InvalidSizeException& e) {
        cout << e.what() << endl << endl;
    }
    try {
        cout << "Difference of m1 and m2:"<< endl << m1 - m2 << endl;
    } catch (InvalidSizeException& e) {
        cout << e.what() << endl << endl;
    }
    try {
        cout << "Multiplication of m1 and m2" << endl << m1 * m2 << endl;
    } catch (InvalidSizeException& e) {
        cout << e.what() << endl << endl;
    }
}

void testAssignmentOperators(Matrix& m1, Matrix& m2) {
    try {
        cout << "m1 += m2:" << endl;
        m1 += m2;
        cout << m1 << endl;
    } catch (InvalidSizeException& e) {
        cout << e.what() << endl << endl;
    }
    try {
        cout << "m1 -= m2:" << endl;
        m1 -= m2;
        cout << m1 << endl;
    } catch (InvalidSizeException& e) {
        cout << e.what() << endl << endl;
    }
    try {
        cout << "m1 *= m2:" << endl;
        m1 *= m2;
        cout << m1 << endl;
    } catch (InvalidSizeException& e) {
        cout << e.what() << endl << endl;
    } catch (NullPointerException& e) {
        cout << e.what() << endl << endl;
    }
}

void testElementAcces(Matrix& m) {
    try {
        m(1, 2) = 8;
    } catch (IndexOutOfBoundsException& e) {
        cout << e.what() << endl;
    }
    try {
        double x = m(1, 2);
        cout << "element at (1, 2): " << x << endl;
    } catch (IndexOutOfBoundsException& e) {
        cout << e.what() << endl;
    }
    cout << "m2: " << endl << m;
}
