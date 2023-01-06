#include "../soft/commands/commandadd.h"
#include "common.h"

TEST(CommandAddTest, ValidateArgsCount)
{
    auto c = std::make_unique<CommandAdd>();
    std::vector<std::string> args { "task06", "task 07", "2009-06-12 02:00", "cat2", "in process" };
    EXPECT_TRUE(c->validateArgsCount(args));
    std::vector<std::string> argsIncor1 { "task06", "task 07", "2009-06-12 02:00", "cat2" };
    EXPECT_FALSE(c->validateArgsCount(argsIncor1));
    std::vector<std::string> argsIncor2 { "task06", "task 07", "2009-06-12 02:00", "cat2", "in process", "" };
    EXPECT_FALSE(c->validateArgsCount(argsIncor2));
}
TEST(CommandAddTest, ParseAndExecute)
{
    auto c = std::make_unique<CommandAdd>();
    DataBase db { Common::getDataBaseFileName() };
    db.isAvailableForCreation();
    DataBaseManager manager { &db };

    bool isSame { true };
    for (size_t j = 0; j < 1000; ++j)
    {
        auto firstArg = "add task" + std::to_string(j);
        std::vector<std::string> args { firstArg, "task 07", "2009-06-12 02:00", "cat2", "in process" };
        c->parseArgs(args);
        c->execute(&db);

        if (!manager.getTuplesAccess().empty())
        {
            for (size_t i = 0; i < args.size(); ++i)
            {
                if (args[i] != manager.getTuplesAccess()[j].values_[i])
                    isSame = false;
            }
        }
        else
        {
            isSame = false;
        }
    }
    ASSERT_TRUE(isSame);
}
