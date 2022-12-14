#pragma once

#include "../databasetuple.h"
#include "command.h"

class CommandAdd : public Command {
public:
    bool validateArgsCount(const std::vector<std::string>& args) const override;
    bool parseArgs(const std::vector<std::string>& args) override;
    void execute(DataBase* dataBase) const override;

private:
    DataBaseTuple tuple_;
};
