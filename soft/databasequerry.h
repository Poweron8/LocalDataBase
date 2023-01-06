#pragma once
#include <memory>

#include "commands/command.h"
#include "database.h"

class DataBaseQuery
{
    DataBase* db_;

public:
    DataBaseQuery(DataBase* db)
        : db_(db) {};
    bool execute(int argc, char** argv);

private:
    std::unique_ptr<Command> makeCommand(std::string command);
};
