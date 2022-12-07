#include "database.h"
#include <vector>
#include <fstream>


bool DataBase::Load()
{
    if (Open())
        return true;
    if (Restore())
        return true;
    return false;
}

void DataBase::Save()
{
    std::ofstream out{file_name_, std::ios_base::out | std::ios_base::trunc};
    out << columns_.size() * DataBaseName::dataBaseNameCount << std::endl;
    for (const auto& r : columns_)
        out << r << std::endl;
    out.close();
}

bool DataBase::Restore()
{
    std::ofstream out{file_name_, std::ios_base::out | std::ios_base::trunc};
    if (!out.is_open())
        return false;
    out.close();
    return true;
}

bool DataBase::Open()
{
    std::ifstream in{file_name_, std::ios_base::in};
    if (!in.is_open())
        return false;
    std::size_t size;
    in >> size;
    std::vector<string>string_args;
    string_args.reserve(size);
    std::string s;
    std::string s_long;
    bool is_long{false};

    for (in >> s; !in.eof(); in >> s)
    {
        if (s.front() == '"')
        {
            is_long = true;
            s_long.append(s) ;
        }
        else
            if (is_long)
            {
                s_long.append(' ' + s);
                if (s.back() == '"')
                {
                    is_long = false;
                    s_long = s_long.substr(1, s_long.length()-2 > 1? s_long.length()-2 : 1);
                    string_args.push_back(std::move(s_long));
                }
            }
            else
            {
                string_args.push_back(std::move(s));
            }
    }

    if (string_args.size() != size)
        return false;

    DataBaseColumn column;
    for (size_t i = 0; i <  size; ++i)
    {
        auto idx = i % DataBaseName::dataBaseNameCount;
        column.values_[idx] = string_args[i];
        if (idx == DataBaseName::dataBaseNameCount - 1)
            columns_.push_back(column);
    }
    in.close();
    return true;
}
