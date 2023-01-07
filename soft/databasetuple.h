#pragma once
#include <array>
#include <iostream>
#include <vector>

#include "databasename.h"

struct DataBaseTuple {
    std::array<std::string, DataBaseAttribute::DATA_BASE_DEGREE> values_;
    DataBaseTuple() = default;
    ~DataBaseTuple() = default;
    friend std::ostream& operator<<(std::ostream& out, const DataBaseTuple& tuple);
};
