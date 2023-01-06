#include "databasemanager.h"

#include <unordered_map>

#include "algorithm"

std::vector<DataBaseColumn>::iterator DataBaseManager::getDataBaseIterator(size_t number, const std::string& value)
{
    std::sort(dataBase_->columns_.begin(), dataBase_->columns_.end(),
        [&number](const DataBaseColumn& r1, const DataBaseColumn& r2)
        {
            return r1.values_[number] < r2.values_[number];
        });
    return std::find_if(dataBase_->columns_.begin(), dataBase_->columns_.end(),
        [&number, &value](const auto& r1)
        { return r1.values_[number] == value; });
}
std::vector<DataBaseColumn>& DataBaseManager::getColumns()
{
    return dataBase_->columns_;
}
void DataBaseManager::filtDataBase(std::vector<DataBaseColumn>& db_columns, size_t number, std::string sign,
    std::string value)
{
    std::unordered_map<std::string, std::function<bool(const DataBaseColumn&, const DataBaseColumn&)>> compMapSort {
        { "<", [&](const auto& c1, const auto& c2)
            { return c1.values_[number] < c2.values_[number]; } },
        { "<=", [&](const auto& c1, const auto& c2)
            { return c1.values_[number] < c2.values_[number]; } },
        { "=", [&](const auto& c1, const auto& c2)
            { return c1.values_[number] < c2.values_[number]; } },
        { ">=", [&](const auto& c1, const auto& c2)
            { return c1.values_[number] > c2.values_[number]; } },
        { ">", [&](const auto& c1, const auto& c2)
            { return c1.values_[number] > c2.values_[number]; } },
        { " like ", [&](const auto& c1, const auto& c2)
            { return c1.values_[number] < c2.values_[number]; } }
    };

    sort(db_columns.begin(), db_columns.end(), compMapSort[sign]);

    std::unordered_map<std::string, std::function<bool(const DataBaseColumn&)>> compMapErase {
        { "<", [&](const auto& c1)
            { return c1.values_[number] < value; } },
        { "<=", [&](const auto& c1)
            { return c1.values_[number] <= value; } },
        { "=", [&](const auto& c1)
            { return c1.values_[number] != value; } },
        { ">=", [&](const auto& c1)
            { return c1.values_[number] >= value; } },
        { ">", [&](const auto& c1)
            { return c1.values_[number] > value; } },
        { " like ", [&](const auto& c1)
            { return c1.values_[number].find(value) == std::string::npos; } }
    };

    auto fUn = compMapErase[sign];
    auto pp = find_if_not(db_columns.begin(), db_columns.end(), [&](const DataBaseColumn& c)
        { return fUn(c); });

    if (pp != db_columns.end())
    {
        if (sign == "=")
        {
            std::vector<DataBaseColumn> temp;
            for (auto& it = pp; it != db_columns.end(); ++it)
                if (it->values_[number] == value)
                    temp.push_back(*it);
            db_columns.clear();
            for (const auto& t : temp)
                db_columns.push_back(t);
        }
        else if (sign == " like ")
        {
            std::vector<DataBaseColumn> temp;
            for (auto& it = pp; it != db_columns.end(); ++it)
                if (it->values_[number].find(value) != std::string::npos)
                    temp.push_back(*it);
            db_columns.clear();
            for (const auto& t : temp)
                db_columns.push_back(t);
        }
        else
        {
            db_columns.erase(pp, db_columns.end());
        }
    }
    else if (sign == "=" || sign == " like ")
    {
        db_columns.clear();
    }
    std::sort(db_columns.begin(), db_columns.end(), [&number](const DataBaseColumn& r1, const DataBaseColumn& r2)
        { return r1.values_[number] < r2.values_[number]; });
}
