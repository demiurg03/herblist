#pragma once
#include <stdexcept>

class NotImplemented : public std::logic_error
{
private:

    std::string _text;

    NotImplemented(const std::string message, const std::string function);;

public:

    NotImplemented();

    NotImplemented(const char* message);

    virtual const char *what() const throw();
};
