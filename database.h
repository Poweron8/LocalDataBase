#pragma once
#include <vector>
#include "databasecolumn.h"


class DataBase
{
public:
    DataBase(std::string file_name):file_name_(file_name){}
    std::vector<DataBaseColumn>columns_;
    bool Load();
    void Save();
private:
    std::string file_name_;
    bool Restore();
    bool Open();
    bool CreateTable();
};

