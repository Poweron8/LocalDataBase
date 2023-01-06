#include "commandupdate.h"

#include <algorithm>

#include "../databasemanager.h"

bool commandUpdate::validateArgsCount(const std::vector<std::string>& args) const
{
    return args.size() == DataBaseAttribute::DATA_BASE_DEGREE;
}

bool commandUpdate::parseArgs(const std::vector<std::string>& args)
{
    auto dest = std::copy(args.begin(), args.end(), tuple_.values_.begin());
    return dest == tuple_.values_.end();
}

void commandUpdate::execute(DataBase* dataBase) const
{
    DataBaseManager dbm(dataBase);
    auto dbit = dbm.getDataBaseIterator(DataBaseAttribute::NAME, tuple_.values_[DataBaseAttribute::NAME]);
    if (dbit != dbm.getTuplesAccess().end())
    {
        for (int i = 0; i < DATA_BASE_DEGREE; ++i)
            dbit->values_[i] = tuple_.values_[i];
    }
}
