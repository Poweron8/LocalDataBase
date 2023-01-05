#pragma once
#include "database.h"

class DataBaseManager
{
public:
    DataBaseManager(DataBase* dataBase) : dataBase_(dataBase){};
    std::vector<DataBaseColumn>::iterator getDataBaseIterator(size_t number, const std::string& value);
    void filtDataBase(std::vector<DataBaseColumn>& args, size_t number, std::string sign, std::string value);
    std::vector<DataBaseColumn>& getColumns();
private:
    DataBase *dataBase_;
};

