#pragma once
#include <string>
#include "databasename.h"
using string = std::string;
class CommandArgs
{
    public:
    DataBaseName db_name_;
    string sign;
    string value;
    bool Empty() const {return sign.empty();}
};

