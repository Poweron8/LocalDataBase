#pragma once

#include "../soft/commands/commandselect.h"

class TestableCommandSelect : public CommandSelect
{
public:
    auto getSelectArgs()->decltype(selectArgs_) const;
    void filtDataBase(std::vector<DataBaseColumn>& args, size_t number, string sign, string value);
    virtual void execute(DataBase* dataBase) const override;
};
