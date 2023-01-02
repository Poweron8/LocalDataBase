#pragma once

#include "command.h"
#include "../commandargs.h"

class CommandSelect : public Command
{
public:

    bool validateArgsCount(const std::vector<std::string>& args) const override;
    bool parseArgs(const std::vector<std::string>& args) override;
    virtual void execute(DataBase* dataBase) const override;
protected:
    std::vector<SelectArgs> selectArgs_;
};

