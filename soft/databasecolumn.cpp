#include "databasecolumn.h"
#include <algorithm>

std::ostream& operator<<(std::ostream& out, const DataBaseColumn& column)
{
    const std::string bad_simbols{" .:"};
    for (const auto& v : column.values_)
    {
        bool bs{false};
        if (v[0] != '"' && v[v.length() - 1] != '"')
        {
            for (const auto& s : bad_simbols)
            {
                bs = (v.find(s) != std::string::npos);
                if (bs)
                    break;
            }
        }
        if (bs)
            out << "\"" << v << "\"" <<" ";
        else
            out << v <<" ";
    }
    return out;
}
