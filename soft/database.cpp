#include "database.h"

#include <vector>
#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool DataBase::load()
{
    if (open())
        return true;
    if (restore())
        return true;
    return false;
}

void DataBase::save()
{
    std::ofstream out{file_name_, std::ios_base::out | std::ios_base::trunc};
    for (const auto& r : columns_){
        out << r;
    }
    out.close();
}

bool DataBase::restore()
{
    std::ofstream out{file_name_, std::ios_base::out | std::ios_base::trunc};
    if (!out.is_open())
        return false;
    out.close();
    return true;
}

bool DataBase::open()
{
    std::ifstream in{file_name_, std::ios_base::in};
    if (!in.is_open())
        return false;
    json j;
    try {
        j = json::parse(in);
    }
    catch (...) {
        return false;
    }

    DataBaseColumn column;
    for (auto it = j.begin(); it != j.end(); ++it){
        column.values_[(it - j.begin()) % DataBaseName::dataBaseNameCount] = *it;
        if ((it - j.begin()) % DataBaseName::dataBaseNameCount == DataBaseName::dataBaseNameCount - 1 && it != j.begin())
            columns_.push_back(column);
    }
    return true;
}
