#include "databasecolumn.h"
#include <algorithm>
#include <nlohmann/json.hpp>

std::ostream& operator<<(std::ostream& out, const DataBaseColumn& column)
{
    nlohmann::json j;
    for (const auto& v : column.values_)
        j.push_back(v);
    out << j;
    return out;
}

