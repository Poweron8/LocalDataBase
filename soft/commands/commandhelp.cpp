#include "commandhelp.h"
#include <algorithm>

bool CommandHelp::validateArgsCount(const std::vector<std::string>& args) const
{
    return args.empty();
}

bool CommandHelp::parseArgs(const std::vector<std::string>& args)
{
    return true;
}

void CommandHelp::execute(DataBase* dataBase) const
{
    std::cout<<"  examples of commands:__________________________________________________" << std::endl;
    std::cout<<" -add task10 \"task 10\" \"2005-01-12 02:00\" cat1 \"in process\"" << std::endl;
    std::cout<<" -done task10" << std::endl;
    std::cout<<" -update task10 \"task 10 update\" \"2005-01-12 02:00\" cat1 \"in process\"" << std::endl;
    std::cout<<" -delete task10" << std::endl;
    std::cout<<" -select*where" << std::endl;
    std::cout<<" -select*where \"-date like 02:00\" and \"-description>=task10\" and \"-name<task11\"" << std::endl;
    std::cout<<"_________________________________________________________________________"<< std::endl;
}
