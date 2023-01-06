#include "../soft/commands/commanddone.h"
#include "common.h"

TEST(CommandDoneTest, ValidateArgsCount)
{
    auto c = std::make_unique<CommandDone>();
    std::vector<std::string> args { "task06" };
    EXPECT_TRUE(c->validateArgsCount(args));
    std::vector<std::string> argsIncor1 {};
    EXPECT_FALSE(c->validateArgsCount(argsIncor1));
    std::vector<std::string> argsIncor2 { "task06", "task 07" };
    EXPECT_FALSE(c->validateArgsCount(argsIncor2));
}
TEST(CommandDoneTest, ParseAndExecute)
{
    auto c = std::make_unique<CommandDone>();

    bool isError { false };
    for (size_t i = 0; i < Common::getTestCount(); ++i)
    {
        auto db = Common::makeDataBase10();
        DataBaseManager manager { db.get() };
        std::string name = manager.getColumns()[0].values_[DataBaseName::name];
        std::random_shuffle(manager.getColumns().begin(), manager.getColumns().end());
        c->parseArgs({ name });
        c->execute(db.get());
        for (const auto& c : manager.getColumns())
        {
            if (c.values_[DataBaseName::name] == name && c.values_[DataBaseName::status] != "done")
                isError = true;
        }
    }
    EXPECT_FALSE(isError);
}
