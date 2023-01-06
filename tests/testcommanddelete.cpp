#include "../soft/commands/commanddelete.h"
#include "common.h"

TEST(CommandDeleteTest, ValidateArgsCount)
{
    auto c = std::make_unique<CommandDelete>();
    std::vector<std::string> args { "task06" };
    EXPECT_TRUE(c->validateArgsCount(args));
    std::vector<std::string> argsIncor1 {};
    EXPECT_FALSE(c->validateArgsCount(argsIncor1));
    std::vector<std::string> argsIncor2 { "task06", "task 07" };
    EXPECT_FALSE(c->validateArgsCount(argsIncor2));
}
TEST(CommandDeleteTest, ParseAndExecute)
{
    auto c = std::make_unique<CommandDelete>();
    bool isError { false };
    for (size_t i = 0; i < Common::getTestCount(); ++i)
    {
        auto db = Common::makeDataBase10();
        DataBaseManager manager { db.get() };
        size_t size = manager.getColumns().size();
        std::string name = manager.getColumns()[0].values_[DataBaseName::name];
        std::random_shuffle(manager.getColumns().begin(), manager.getColumns().end());
        c->parseArgs({ name });
        c->execute(db.get());
        for (const auto& c : manager.getColumns())
        {
            if (c.values_[DataBaseName::name] == name)
                isError = true;
        }
        EXPECT_TRUE(manager.getColumns().size() == size - 1);
    }
    EXPECT_FALSE(isError);
}
