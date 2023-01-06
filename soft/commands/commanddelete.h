#pragma once

#include "command.h"

class CommandDelete : public Command
{
public:
    bool validateArgsCount(const std::vector<std::string>& args) const override;
    bool parseArgs(const std::vector<std::string>& args) override;
    void execute(DataBase* dataBase) const override;

private:
    std::string name_;
};
