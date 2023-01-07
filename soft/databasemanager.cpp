#include "databasemanager.h"

#include <unordered_map>

#include "algorithm"

std::vector<DataBaseTuple>::iterator DataBaseManager::getDataBaseIterator(size_t number, const std::string& value)
{
    std::sort(dataBase_->tuples_.begin(), dataBase_->tuples_.end(),
        [&number](const DataBaseTuple& r1, const DataBaseTuple& r2) {
            return r1.values_[number] < r2.values_[number];
        });
    return std::find_if(dataBase_->tuples_.begin(), dataBase_->tuples_.end(),
        [&number, &value](const auto& r1) { return r1.values_[number] == value; });
}
std::vector<DataBaseTuple>& DataBaseManager::getTuplesAccess()
{
    return dataBase_->tuples_;
}
void DataBaseManager::filtDataBase(std::vector<DataBaseTuple>& db_tuples, size_t number, std::string sign,
    std::string value)
{
    std::unordered_map<std::string, std::function<bool(const DataBaseTuple&, const DataBaseTuple&)>> compMapSort {
        { "<", [&](const auto& c1, const auto& c2) { return c1.values_[number] < c2.values_[number]; } },
        { "<=", [&](const auto& c1, const auto& c2) { return c1.values_[number] < c2.values_[number]; } },
        { "=", [&](const auto& c1, const auto& c2) { return c1.values_[number] < c2.values_[number]; } },
        { ">=", [&](const auto& c1, const auto& c2) { return c1.values_[number] > c2.values_[number]; } },
        { ">", [&](const auto& c1, const auto& c2) { return c1.values_[number] > c2.values_[number]; } },
        { " like ", [&](const auto& c1, const auto& c2) { return c1.values_[number] < c2.values_[number]; } }
    };

    sort(db_tuples.begin(), db_tuples.end(), compMapSort[sign]);

    std::unordered_map<std::string, std::function<bool(const DataBaseTuple&)>> compMapErase {
        { "<", [&](const auto& c1) { return c1.values_[number] < value; } },
        { "<=", [&](const auto& c1) { return c1.values_[number] <= value; } },
        { "=", [&](const auto& c1) { return c1.values_[number] != value; } },
        { ">=", [&](const auto& c1) { return c1.values_[number] >= value; } },
        { ">", [&](const auto& c1) { return c1.values_[number] > value; } },
        { " like ", [&](const auto& c1) { return c1.values_[number].find(value) == std::string::npos; } }
    };

    auto fUn = compMapErase[sign];
    auto pp = find_if_not(db_tuples.begin(), db_tuples.end(), [&](const DataBaseTuple& c) { return fUn(c); });

    if (pp != db_tuples.end()) {
        if (sign == "=") {
            std::vector<DataBaseTuple> temp;
            for (auto& it = pp; it != db_tuples.end(); ++it)
                if (it->values_[number] == value)
                    temp.push_back(*it);
            db_tuples.clear();
            for (const auto& t : temp)
                db_tuples.push_back(t);
        }
        else if (sign == " like ") {
            std::vector<DataBaseTuple> temp;
            for (auto& it = pp; it != db_tuples.end(); ++it)
                if (it->values_[number].find(value) != std::string::npos)
                    temp.push_back(*it);
            db_tuples.clear();
            for (const auto& t : temp)
                db_tuples.push_back(t);
        }
        else {
            db_tuples.erase(pp, db_tuples.end());
        }
    }
    else if (sign == "=" || sign == " like ") {
        db_tuples.clear();
    }
    std::sort(db_tuples.begin(), db_tuples.end(), [&number](const DataBaseTuple& r1, const DataBaseTuple& r2) { return r1.values_[number] < r2.values_[number]; });
}
