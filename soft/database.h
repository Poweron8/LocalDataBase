#pragma once
#include <vector>

#include "databasetuple.h"

class DataBase {
public:
    friend class DataBaseManager;
    DataBase(const std::string& file_name)
        : file_name_(file_name) {};
    bool load();
    void save();
    bool isAvailableForCreation();
    bool open();
    bool createTable();

private:
    std::string file_name_;
    std::vector<DataBaseTuple> tuples_;
};
