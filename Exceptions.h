#include <iostream>

class InvalidFileException : public std::exception {
    public:
        const char* what();
};

class InvalidInputException : public std::exception {
    public:
        const char* what();
};

class InvalidSizeException : public std::exception {
    public:
        const char* what();
};

class NullPointerException : public std::exception {
    public:
        const char* what();
};

class IndexOutOfBoundsException : public std::exception {
    public:
        const char* what();
};