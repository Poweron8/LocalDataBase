#pragma once
#include <vector>
#include "databasecolumn.h"

class DataBase
{
public:
    friend class DataBaseManager;
    DataBase(std::string file_name):file_name_(file_name){}
    bool load();
    void save();
    bool restore();
    bool open();
    bool createTable();
private:
    std::string file_name_;
    std::vector<DataBaseColumn>columns_;
};

