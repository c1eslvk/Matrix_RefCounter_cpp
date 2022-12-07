#include "Matrix.h"
#include "Exceptions.h"

Matrix::RefElement::operator double() const {
    return m.read(row, col);
}

Matrix::RefElement& Matrix::RefElement::operator=(double value) {
    m.write(row, col, value);
    return *this;
}

Matrix::RefElement& Matrix::RefElement::operator=(const RefElement& ref) {
    return operator=(double(ref));
}