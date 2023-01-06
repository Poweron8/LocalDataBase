#include "commandadd.h"

#include <algorithm>

#include "../databasemanager.h"

bool CommandAdd::validateArgsCount(const std::vector<std::string>& args) const
{
    return args.size() == DataBaseAttribute::DATA_BASE_DEGREE;
}

bool CommandAdd::parseArgs(const std::vector<std::string>& args)
{
    auto dest = std::copy(args.begin(), args.end(), tuple_.values_.begin());
    return dest == tuple_.values_.end();
}

void CommandAdd::execute(DataBase* dataBase) const
{
    DataBaseManager dbm(dataBase);
    auto dbit = dbm.getDataBaseIterator(DataBaseAttribute::NAME, tuple_.values_[DataBaseAttribute::NAME]);
    if (dbit == dbm.getTuplesAccess().end())
        dbm.getTuplesAccess().emplace_back(tuple_);
}
