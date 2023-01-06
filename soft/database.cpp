#include "database.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

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
    for (const auto& r : tuples_)
    {
        j.push_back(r.values_);
    }
    std::ofstream out { file_name_, std::ios_base::out | std::ios_base::trunc };
    out << j;
    out.close();
}

bool DataBase::isAvailableForCreation()
{
    std::ofstream out { file_name_, std::ios_base::out | std::ios_base::trunc };
    if (!out.is_open())
        return false;
    out.close();
    return true;
}

bool DataBase::open()
{
    std::ifstream in { file_name_, std::ios_base::in };
    if (!in.is_open())
        return false;
    json j;
    try
    {
        j = json::parse(in);
    }
    catch (...)
    {
        return false;
    }

    DataBaseTuple tuple;
    for (auto it = j.begin(); it != j.end(); ++it)
    {
        std::copy(it->begin(), it->end(), tuple.values_.begin());
        tuples_.push_back(tuple);
    }
    return true;
}
