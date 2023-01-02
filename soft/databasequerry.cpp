#include "databasequerry.h"
#include "commands/commandadd.h"
#include "commands/commanddone.h"
#include "commands/commandupdate.h"
#include "commands/commanddelete.h"
#include "commands/commandselect.h"
#include "commands/commandhelp.h"

bool DataBaseQuery::execute(int argc, char **argv)
{
    if (!db_)
        return false;

    std::vector<std::string>args;
    for (int i = 1; i < argc; ++i)
        args.push_back(argv[i]);

    if (args.empty())
        return false;

    auto first_arg = args[0];
    args.erase(args.begin());
    auto command = makeCommand(first_arg);
    if (command == nullptr)
        return false;
    if (!command->validateArgsCount(args))
        return false;
    if (!command->parseArgs(args))
        return false;
    command->execute(db_);
    return true;
}

std::unique_ptr<Command> DataBaseQuery::makeCommand(std::string command)
{
    if (command == "-add")
        return std::make_unique<CommandAdd>();
    else if (command == "-done")
        return std::make_unique<CommandDone>();
    else if (command == "-update")
        return std::make_unique<commandUpdate>();
    else if (command == "-delete")
        return std::make_unique<CommandDelete>();
    else if (command == "-select*where")
        return std::make_unique<CommandSelect>();
    else if (command == "-select*")
        return std::make_unique<CommandSelect>();
    else if (command == "-help")
        return std::make_unique<CommandHelp>();
    return nullptr;
}


