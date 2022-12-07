#pragma once
#include<iostream>
#include<vector>
#include<array>
#include "databasename.h"
using string = std::string;
struct DataBaseColumn
{
    std::array<string, DataBaseName::dataBaseNameCount>values_;
    DataBaseColumn() = default;
    ~DataBaseColumn() = default;
    DataBaseColumn(const std::array<string, DataBaseName::dataBaseNameCount>&values) : values_(values){}
    DataBaseColumn(const std::vector<string>&args);
    friend std::ostream& operator<<(std::ostream& out, const DataBaseColumn& column);
};

