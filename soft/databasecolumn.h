#pragma once
#include<iostream>
#include<vector>
#include<array>
#include "databasename.h"

struct DataBaseColumn
{
    std::array<std::string, DataBaseName::dataBaseNameCount>values_;
    DataBaseColumn() = default;
    ~DataBaseColumn() = default;
    friend std::ostream& operator<<(std::ostream& out, const DataBaseColumn& column);
};

