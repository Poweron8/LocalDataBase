#include "databasetuple.h"

#include <algorithm>

#include <nlohmann/json.hpp>

std::ostream& operator<<(std::ostream& out, const DataBaseTuple& tuple)
{
    for (const auto& v : tuple.values_)
        out << v;
    return out;
}
