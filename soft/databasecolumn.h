#pragma once
#include<iostream>
#include<vector>
#include<array>
#include "databasename.h"

#include <nlohmann/json.hpp>
struct DataBaseColumn
{
    std::array<std::string, DataBaseName::dataBaseNameCount>values_;
    DataBaseColumn() = default;
    ~DataBaseColumn() = default;
    friend std::ostream& operator<<(std::ostream& out, const DataBaseColumn& column);
};

