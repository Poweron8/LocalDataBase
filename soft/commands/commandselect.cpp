#include "commandselect.h"

#include <algorithm>

#include "../databasemanager.h"

bool CommandSelect::validateArgsCount(const std::vector<std::string>& args) const
{
    return true;
}

bool CommandSelect::parseArgs(const std::vector<std::string>& args)
{
    for (auto& arg : args)
    {
        if (arg.empty())
            return false;
        if (arg == "and")
            continue;
        auto start_pos = 0;
        auto fin_pos = arg.length() - 1;
        if (arg[start_pos] == '\"' && arg[fin_pos] == '\"')
        {
            ++start_pos;
            --fin_pos;
        }
        if (arg[start_pos] != '-')
            return false;
        SelectArgs ca;
        std::vector<std::string> divs { "<=", ">=", "<", ">", " like ", "=" };
        std::string div;
        size_t div_pos { 0 };
        for (const auto& d : divs)
        {
            auto pos = arg.find(d);
            if (pos != std::string::npos)
            {
                div = d;
                div_pos = pos;
                break;
            }
        }
        if (div.empty())
            return false;
        std::string left;
        left.assign(arg, start_pos, div_pos - start_pos);
        if (left == "-name")
            ca.db_name_ = DataBaseAttribute::NAME;
        else if (left == "-description")
            ca.db_name_ = DataBaseAttribute::DESCRIPTION;
        else if (left == "-date")
            ca.db_name_ = DataBaseAttribute::DATE;
        else if (left == "-category")
            ca.db_name_ = DataBaseAttribute::CATEGORY;
        else if (left == "-status")
            ca.db_name_ = DataBaseAttribute::STATUS;
        else
            return false;

        ca.sign_.assign(arg, div_pos, div.length());
        ca.value_.assign(arg, div_pos + ca.sign_.length(), fin_pos + 1 - left.length() - ca.sign_.length());
        selectArgs_.push_back(ca);
    }
    return !selectArgs_.empty() || args.empty();
}

void CommandSelect::execute(DataBase* dataBase) const
{
    DataBase db { *dataBase };
    DataBaseManager manager(&db);

    for (const auto& c : selectArgs_)
        manager.filtDataBase(manager.getTuplesAccess(), c.db_name_, c.sign_, c.value_);
    for (const auto& tuple : manager.getTuplesAccess())
        std::cout << tuple << std::endl;
}
