#include "NotImplemented.hpp"

NotImplemented::NotImplemented(const std::string message, const std::string function)
    :
      std::logic_error("Not Implemented")
{
    _text = message;
    _text += " : ";
    _text += function;
}

NotImplemented::NotImplemented()
    :
      NotImplemented("Not Implememented", __FUNCTION__)
{
}

NotImplemented::NotImplemented(const char *message)
    :
      NotImplemented(message, __FUNCTION__)
{
}

const char *NotImplemented::what() const throw()
{
    return _text.c_str();
}
