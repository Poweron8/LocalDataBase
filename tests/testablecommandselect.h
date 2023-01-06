#pragma once

#include "../soft/commands/commandselect.h"

class TestableCommandSelect : public CommandSelect
{
public:
    auto getSelectArgs() -> decltype(selectArgs_) const;
    void filtDataBase(std::vector<DataBaseTuple>& args, size_t number, std::string sign, std::string value);
    virtual void execute(DataBase* dataBase) const override;
};
