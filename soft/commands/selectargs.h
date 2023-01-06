#pragma once
#include <string>

#include "../databasename.h"
class SelectArgs
{
public:
    DataBaseAttribute db_name_;
    std::string sign_;
    std::string value_;
};
