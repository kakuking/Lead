#pragma once

#include <lead/common.h>

class LeadException: public std::exception
{
public:
    LeadException(std::string what): whatTf{what} {}

    virtual const char* what() const throw()
    {
        return whatTf.c_str();
    }

protected:
    std::string whatTf;
};

