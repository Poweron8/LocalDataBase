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
        auto fin_pos = arg.length()-1;
        if (arg[start_pos] == '\"' && arg[fin_pos] == '\"')
        {
            ++start_pos;
            --fin_pos;
        }
        if (arg[start_pos] != '-')
            return false;
        SelectArgs ca;
        std::vector<string>divs{"<=", ">=", "<", ">", " like ", "="};
        string div;
        size_t div_pos{0};
        for (const auto& d : divs)
        {
            auto pos = arg.find(d);
            if (pos != string::npos)
            {
                div = d;
                div_pos = pos;
                break;
            }
        }
        if (div.empty())
            return false;
        string left;
        left.assign(arg, start_pos, div_pos - start_pos);
        if (left == "-name")
            ca.db_name_ = DataBaseName::name;
        else if (left == "-description")
            ca.db_name_ = DataBaseName::description;
        else if (left == "-date")
            ca.db_name_ = DataBaseName::date;
        else if (left == "-category")
            ca.db_name_ = DataBaseName::category;
        else if (left == "-status")
            ca.db_name_ = DataBaseName::status;
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
    DataBase db{*dataBase};
    DataBaseManager manager(&db);

    for (const auto& c: selectArgs_)
        manager.filtDataBase(manager.getColumns(), c.db_name_, c.sign_, c.value_);
    for (const auto& column : manager.getColumns())
        std::cout << column << std::endl;
}
