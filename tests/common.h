#pragma once
#include <gtest/gtest.h>

#include "../soft/database.h"
#include "../soft/databasemanager.h"
//#include "../commands/selectargs.h"

#include <memory>
#include <string>
#include <vector>

class SelectArgs;
struct Common
{
    const static unsigned getTestCount();
    const static std::string getDataBaseFileName();
    const static std::vector<std::string> getDefaultArgs();
    static std::shared_ptr<DataBase> makeDataBase10();
    static SelectArgs getRandomSelectTask();
    static std::string nameToString(DataBaseName dataBaseName);
    static bool checkCondition(const std::string& s1, const std::string& sign, const std::string& s2);
    static DataBaseName getRandomBaseName();
    static std::string getRandomSign();
};
