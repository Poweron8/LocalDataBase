#include "database.h"

#include <vector>
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool DataBase::load()
{
    if (open())
        return true;
    if (isAvailableForCreation())
        return true;
    return false;
}

void DataBase::save()
{  
    json j;
    for (const auto& r : columns_){
        j.push_back(r.values_);
    }
    std::ofstream out{file_name_, std::ios_base::out | std::ios_base::trunc};
    out << j;
    out.close();
}

bool DataBase::isAvailableForCreation()
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
        std::copy(it->begin(), it->end(), column.values_.begin());
        columns_.push_back(column);
    }
    return true;
}
