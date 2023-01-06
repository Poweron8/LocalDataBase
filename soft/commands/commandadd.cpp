#include "commandadd.h"

#include <algorithm>

#include "../databasemanager.h"

bool CommandAdd::validateArgsCount(const std::vector<std::string>& args) const
{
    return args.size() == DataBaseName::dataBaseNameCount;
}

bool CommandAdd::parseArgs(const std::vector<std::string>& args)
{
    auto dest = std::copy(args.begin(), args.end(), column_.values_.begin());
    return dest == column_.values_.end();
}

void CommandAdd::execute(DataBase* dataBase) const
{
    DataBaseManager dbm(dataBase);
    auto dbit = dbm.getDataBaseIterator(DataBaseName::name, column_.values_[DataBaseName::name]);
    if (dbit == dbm.getColumns().end())
        dbm.getColumns().emplace_back(column_);
}
