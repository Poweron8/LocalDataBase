#include "common.h"

#include <algorithm>

#include "../soft/commands/selectargs.h"
#include "../soft/databasecolumn.h"
#include "../soft/databasemanager.h"
const unsigned Common::getTestCount()
{
    return 1000;
}
const std::string Common::getDataBaseFileName()
{
    return "test.txt";
}
const std::vector<std::string> Common::getDefaultArgs()
{
    return { "test", "task 07", "2009-06-12 02:00", "cat2", "in process" };
}
std::shared_ptr<DataBase> Common::makeDataBase10()
{
    auto base = std::make_shared<DataBase>(getDataBaseFileName());
    DataBaseManager manager { base.get() };
    const unsigned nColumn { 10 };
    DataBaseColumn columns[nColumn];
    columns[0].values_ = { "test00", "description 22", "2008-01-11 02:10", "cat2", "in process" };
    columns[1].values_ = { "test01", "description 15", "2006-03-23 03:20", "cat1", "done" };
    columns[2].values_ = { "test02", "description 4", "2004-04-24 03:10", "cat3", "in process" };
    columns[3].values_ = { "test03", "description 7", "2003-05-25 04:10", "cat2", "in process" };
    columns[4].values_ = { "test04", "no description", "2005-06-25 00:20", "cat3", "in process" };
    columns[5].values_ = { "test05", "description 5", "2007-09-25 12:25", "cat4", "in process" };
    columns[6].values_ = { "test06", "description 7", "2008-12-02 12:25", "cat2", "in process" };
    columns[7].values_ = { "test07", "description 16", "2006-06-04 13:10", "cat3", "no status" };
    columns[8].values_ = { "test08", "description 9", "2010-06-20 14:10", "cat2", "in process" };
    columns[9].values_ = { "test09", "description 0", "2020-09-12 03:45", "cat0", "in process" };

    for (const auto c : columns)
        manager.getColumns().push_back(c);
    std::random_shuffle(manager.getColumns().begin(), manager.getColumns().end());
    return base;
}

SelectArgs Common::getRandomSelectTask()
{
    std::vector<std::string> values { " ", "", "test 01", "_", "test00" };
    std::random_shuffle(values.begin(), values.end());
    return { getRandomBaseName(), getRandomSign(), values[0] };
}

std::string Common::nameToString(DataBaseName dataBaseName)
{
    switch (dataBaseName)
    {
    case name:
        return "name";
    case description:
        return "description";
    case date:
        return "date";
    case category:
        return "category";
    case status:
        return "status";
    default:
        return {};
    }
}

bool Common::checkCondition(const std::string& s1, const std::string& sign, const std::string& s2)
{
    if (sign == "<=")
        return s1 <= s2;
    else if (sign == "<")
        return s1 < s2;
    else if (sign == "=")
        return s1 == s2;
    else if (sign == ">")
        return s1 > s2;
    else if (sign == ">=")
        return s1 >= s2;
    else if (sign == " like ")
        return s1.find(s2) != std::string::npos;
    return false;
}

DataBaseName Common::getRandomBaseName()
{
    std::vector<DataBaseName> names { name, description, category, date, status };
    std::random_shuffle(names.begin(), names.end());
    return names[0];
}

std::string Common::getRandomSign()
{
    std::vector<std::string> signs { "<", "<=", "=", ">=", ">", " like " };
    std::random_shuffle(signs.begin(), signs.end());
    return signs[0];
}
