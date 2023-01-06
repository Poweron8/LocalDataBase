#pragma once
#include "database.h"

class DataBaseManager
{
public:
    DataBaseManager(DataBase* dataBase)
        : dataBase_(dataBase) {}
    std::vector<DataBaseTuple>::iterator getDataBaseIterator(size_t number, const std::string& value);
    void filtDataBase(std::vector<DataBaseTuple>& args, size_t number, std::string sign, std::string value);
    std::vector<DataBaseTuple>& getTuplesAccess();

private:
    DataBase* dataBase_;
};
