#include "common.h"
#include "testablecommandselect.h"

TEST(CommandSelectTest, Parse)
{
    auto c = std::make_unique<TestableCommandSelect>();
    std::vector<std::string> sArgs;
    for (size_t i = 0; i < Common::getTestCount(); ++i)
    {
        auto args = Common::getRandomSelectTask();
        sArgs.push_back("-" + Common::nameToString(args.db_name_) + args.sign_ + args.value_);
        sArgs.push_back("and");
    }
    sArgs.pop_back();
    c->parseArgs(sArgs);
    auto parse = c->getSelectArgs();
    ASSERT_TRUE(parse.size() == (sArgs.size() + 1) / 2);
    bool isError { false };
    for (size_t i = 0; i < Common::getTestCount(); ++i)
    {
        if ("-" + Common::nameToString(parse[i].db_name_) + parse[i].sign_ + parse[i].value_ != sArgs[i * 2])
            isError = true;
    }
    ASSERT_FALSE(isError);
}

TEST(CommandSelectTest, Execute)
{
    for (size_t i = 0; i < Common::getTestCount(); ++i)
    {
        auto db = Common::makeDataBase10();
        DataBase checkDataBase { "check.txt" };
        DataBaseManager checkManager { &checkDataBase };
        DataBaseManager manager { db.get() };
        std::random_shuffle(manager.getColumns().begin(), manager.getColumns().end());
        DataBaseName name = Common::getRandomBaseName();
        std::string value = manager.getColumns()[0].values_[name];
        std::string sign = Common::getRandomSign();

        for (const auto& c : manager.getColumns())
        {
            if (Common::checkCondition(c.values_[name], sign, value))
                checkManager.getColumns().push_back(c);
        }
        std::string task = "-" + Common::nameToString(name) + sign + value;
        auto c = std::make_unique<TestableCommandSelect>();
        c->parseArgs({ task });
        c->execute(db.get());
        EXPECT_TRUE(manager.getColumns().size() == checkManager.getColumns().size())
            << "task " << task << " is failed" << std::endl;
        ;
    }
}
