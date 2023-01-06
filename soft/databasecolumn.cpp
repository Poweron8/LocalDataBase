#include "databasecolumn.h"

#include <algorithm>
#include <nlohmann/json.hpp>

std::ostream& operator<<(std::ostream& out, const DataBaseColumn& column)
{
    for (const auto& v : column.values_)
        out << v;
    return out;
}
