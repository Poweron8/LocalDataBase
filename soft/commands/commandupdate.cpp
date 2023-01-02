#include "commandupdate.h"
#include <algorithm>
#include "../databasemanager.h"


bool commandUpdate::validateArgsCount(const std::vector<std::string>& args) const
{
    return args.size() == DataBaseName::dataBaseNameCount;
}

bool commandUpdate::parseArgs(const std::vector<std::string>& args)
{
    auto dest = std::copy(args.begin(), args.end(), column_.values_.begin());
    return dest == column_.values_.end();
}

void commandUpdate::execute(DataBase* dataBase) const
{
    DataBaseManager dbm(dataBase);
    auto dbit =  dbm.getDataBaseIterator(DataBaseName::name, column_.values_[DataBaseName::name]);
    if (dbit != dbm.getColumns().end())
    {
        for (int i = 0; i < dataBaseNameCount; ++i)
            dbit->values_[i] = column_.values_[i];
    }
}
