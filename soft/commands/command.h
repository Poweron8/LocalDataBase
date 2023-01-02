#pragma once
#include <string>
#include <vector>
#include "../database.h"

class Command
{
public:
    virtual ~Command() = default;

    virtual bool validateArgsCount(const std::vector<std::string>& args) const = 0;
    virtual bool parseArgs(const std::vector<std::string>& args) = 0;
    virtual void execute(DataBase* dataBase) const = 0;
};

