#include "commanddelete.h"

#include <algorithm>

#include "../databasemanager.h"

bool CommandDelete::validateArgsCount(const std::vector<std::string>& args) const
{
    return args.size() == 1;
}

bool CommandDelete::parseArgs(const std::vector<std::string>& args)
{
    name_ = args[0];
    return true;
}

void CommandDelete::execute(DataBase* dataBase) const
{
    DataBaseManager dbm(dataBase);
    auto dbit = dbm.getDataBaseIterator(DataBaseAttribute::NAME, name_);
    if (dbit != dbm.getTuplesAccess().end())
        dbm.getTuplesAccess().erase(dbit);
}
