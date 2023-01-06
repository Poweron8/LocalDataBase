#include "../soft/commands/commandupdate.h"
#include "common.h"

TEST(CommandUpdateTest, ValidateArgsCount)
{
    auto c = std::make_unique<commandUpdate>();
    std::vector<std::string> args { "task06", "task 07", "2009-06-12 02:00", "cat2", "in process" };
    EXPECT_TRUE(c->validateArgsCount(args));
    std::vector<std::string> argsIncor1 { "task06", "task 07", "2009-06-12 02:00", "cat2" };
    EXPECT_FALSE(c->validateArgsCount(argsIncor1));
    std::vector<std::string> argsIncor2 { "task06", "task 07", "2009-06-12 02:00", "cat2", "in process", "" };
    EXPECT_FALSE(c->validateArgsCount(argsIncor2));
}
TEST(CommandUpdateTest, ParseAndExecute)
{
    auto c = std::make_unique<commandUpdate>();
    auto db = Common::makeDataBase10();
    DataBaseManager manager { db.get() };
    auto args = Common::getDefaultArgs();
    auto argsCheck = args;
    argsCheck[DataBaseName::description] = "check";
    DataBaseColumn column;
    DataBaseColumn columnCheck;
    std::copy(args.begin(), args.end(), column.values_.begin());
    std::copy(argsCheck.begin(), argsCheck.end(), columnCheck.values_.begin());
    manager.getColumns().push_back(column);
    bool isCheck { false };

    for (const auto& c : manager.getColumns())
        if (c.values_[DataBaseName::description] == "check")
            isCheck = true;

    EXPECT_FALSE(isCheck);
    isCheck = false;
    c->parseArgs(argsCheck);
    c->execute(db.get());
    for (const auto& c : manager.getColumns())
        if (c.values_[DataBaseName::description] == "check")
            isCheck = true;

    EXPECT_TRUE(isCheck);
}
