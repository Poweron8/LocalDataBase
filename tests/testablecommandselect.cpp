#include "testablecommandselect.h"

#include "../soft/databasemanager.h"

auto TestableCommandSelect::getSelectArgs() -> decltype(selectArgs_) const
{
    return selectArgs_;
}

void TestableCommandSelect::execute(DataBase* dataBase) const
{
    DataBaseManager manager { dataBase };
    for (const auto& args : selectArgs_) {
        manager.filtDataBase(manager.getTuplesAccess(), args.db_name_, args.sign_, args.value_);
    }
}
