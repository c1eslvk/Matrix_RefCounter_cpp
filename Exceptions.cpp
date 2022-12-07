#include <iostream>
#include "Exceptions.h"

const char* InvalidFileException::what() {
    return "File Error";
}

const char* IndexOutOfBoundsException::what() {
    return "Error. Index out of bounds.";
}

const char* InvalidInputException::what() {
    return "Error. Invalid input.";
}

const char* InvalidSizeException::what() {
    return "Wrong size. Cannot execute operation.";
}

const char* NullPointerException::what() {
    return "Error with allocating memory";
}