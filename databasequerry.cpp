#include "databasequerry.h"
#include "databasename.h"
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <functional>

bool DataBaseQuery::Execute(int argc, char **argv)
{
    if (!db_)
        return false;

    bool result{false};

    std::vector<std::string>args;

    for (int i = 1; i < argc; ++i)
        args.push_back(argv[i]);

    if (args.empty())
        return false;

    auto first_arg = args[0];
    args.erase(args.begin());
    if (first_arg == "-add")
        result = Add(args);
    else if (first_arg == "-done")
        result = Done(args);
    else if (first_arg == "-update")
        result = Update(args);
    else if (first_arg == "-delete")
        result = Delete(args);
    else if (first_arg == "-select*where")
        result = Select(args);
    else if (first_arg == "-select*")
        result = Select(args);
    else if (first_arg == "-help")
        result = Help();

    return result;
}

bool DataBaseQuery::Done(const std::vector<string> &args)
{
    if (args.size() != 1)
        return false;
    auto dbit =  GetDataBaseIterator(DataBaseName::name, args[0]);
    if (dbit == db_->columns_.end())
        return false;
    dbit->values_[DataBaseName::status] = "done";
    return true;
}

bool DataBaseQuery::Update(const std::vector<string> &args)
{
    if (args.size() != DataBaseName::dataBaseNameCount)
        return false;
    auto dbit =  GetDataBaseIterator(DataBaseName::name, args[0]);
    if (dbit == db_->columns_.end())
        return false;
    for (auto i = 0u; i < args.size(); ++i)
        dbit->values_[i] = args[i];
    return true;
}

bool DataBaseQuery::Add(const std::vector<string> &args)
{
    if (args.size() != DataBaseName::dataBaseNameCount)
        return false;
    auto dbit =  GetDataBaseIterator(DataBaseName::name, args[0]);
    if (dbit == db_->columns_.end())
        db_->columns_.emplace_back(args);
    return true;
}

bool DataBaseQuery::Delete(const std::vector<string> &args)
{
    if (args.size() != 1)
        return false;
    auto dbit =  GetDataBaseIterator(DataBaseName::name, args[0]);
    if (dbit == db_->columns_.end())
        return false;
    db_->columns_.erase(dbit);
    return true;
}

bool DataBaseQuery::Select(const std::vector<string> &args)
{
    DataBase db{*db_};

    auto command_args = ParseSelectArgs(args);
    if (!args.empty() && command_args.empty())
    {
        if(command_args.empty())
            return false;
    }
    for (const auto& c: command_args)
        FiltDataBase(db.columns_, c.db_name_, c.sign, c.value);
    for (const auto & column : db.columns_)
        std::cout << column << std::endl;

    return true;
}

bool DataBaseQuery::Help()
{
    std::cout<<"  examples of commands:__________________________________________________" << std::endl;
    std::cout<<" -add task10 \"task 10\" \"2005-01-12 02:00\" cat1 \"in process\"" << std::endl;
    std::cout<<" -done task10" << std::endl;
    std::cout<<" -update task10 \"task 10 update\" \"2005-01-12 02:00\" cat1 \"in process\"" << std::endl;
    std::cout<<" -delete task10" << std::endl;
    std::cout<<" -select*where" << std::endl;
    std::cout<<" -select*where \"-date like 02:00\" and \"-description>=task10\" and \"-name<task11\"" << std::endl;
    std::cout<<"_________________________________________________________________________"<< std::endl;
    return true;
}
DB_Iterator DataBaseQuery::GetDataBaseIterator(size_t number, const string& value)
{
    std::sort(db_->columns_.begin(), db_->columns_.end(), [&number](const DataBaseColumn& r1, const DataBaseColumn& r2)  { return r1.values_[number] < r2.values_[number]; });
    return std::find_if(db_->columns_.begin(), db_->columns_.end(), [&number, &value](const auto& r1){ return r1.values_[number] == value; });
}

std::vector<CommandArgs>DataBaseQuery::ParseSelectArgs(const std::vector<string>&args) const
{
    std::vector<CommandArgs> res;
    for (auto& arg : args)
    {
        if (arg.empty())
            return {};
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
            return {};
        CommandArgs ca;
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
            return {};
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
            return {};

        ca.sign.assign(arg, div_pos, div.length());
        ca.value.assign(arg, div_pos + ca.sign.length(), fin_pos + 1 - left.length() - ca.sign.length());
        res.push_back(ca);
    }
    return res;
}

void DataBaseQuery::FiltDataBase(std::vector<DataBaseColumn>& db_columns, size_t number, string sign, string value) const
{
    std::map<string, std::function<bool(const DataBaseColumn&, const DataBaseColumn&)>>comp_map_sort{
    {"<" , [&](const auto& c1, const auto& c2){return c1.values_[number] < c2.values_[number];}},
    {"<=", [&](const auto& c1, const auto& c2){return c1.values_[number] < c2.values_[number];}},
    {"=",  [&](const auto& c1, const auto& c2){return c1.values_[number] < c2.values_[number];}},
    {">=", [&](const auto& c1, const auto& c2){return c1.values_[number] > c2.values_[number];}},
    {">",  [&](const auto& c1, const auto& c2){return c1.values_[number] > c2.values_[number];}},
    {" like ", [&](const auto& c1, const auto& c2){return c1.values_[number] < c2.values_[number];}}};

    std::map<string, std::function<bool(const DataBaseColumn&)>>comp_map_erase{
    {"<" , [&](const auto& c1){return c1.values_[number] < value;}},
    {"<=", [&](const auto& c1){return c1.values_[number] <= value;}},
    {"=",  [&](const auto& c1){return c1.values_[number] != value;}},
    {">=", [&](const auto& c1){return c1.values_[number] >= value;}},
    {">",  [&](const auto& c1){return c1.values_[number] > value;}},
    {" like ",  [&](const auto& c1){return c1.values_[number].find(value) == string::npos;}}};

    auto f_un = comp_map_erase[sign];
    sort(db_columns.begin(), db_columns.end(), comp_map_sort[sign]);
    auto pp = find_if_not(db_columns.begin(), db_columns.end(), [&](const DataBaseColumn& c){return f_un(c);});

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
        else if(sign == " like ")
        {
            std::vector<DataBaseColumn> temp;
            for (auto& it = pp; it != db_columns.end(); ++it)
                if (it->values_[number].find(value) != string::npos)
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
    std::sort(db_columns.begin(), db_columns.end(), [&number](const DataBaseColumn& r1, const DataBaseColumn& r2)  { return r1.values_[number] < r2.values_[number]; });
}


