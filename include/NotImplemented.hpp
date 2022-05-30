/**
 *
 *  @file NotImplemented.hpp
 *  @author Maxim Palshin
 *
 *  Copyright 2022, Maxim Palshin.  All rights reserved.
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  herblist
 *
 */



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
