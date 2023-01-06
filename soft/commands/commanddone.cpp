#include "commanddone.h"

#include <algorithm>

#include "../databasemanager.h"

bool CommandDone::validateArgsCount(const std::vector<std::string>& args) const
{
    return args.size() == 1;
}

bool CommandDone::parseArgs(const std::vector<std::string>& args)
{
    name_ = args[0];
    return true;
}

void CommandDone::execute(DataBase* dataBase) const
{
    DataBaseManager dbm(dataBase);
    auto dbit = dbm.getDataBaseIterator(DataBaseName::name, name_);
    if (dbit != dbm.getColumns().end())
        dbit->values_[DataBaseName::status] = "done";
}
