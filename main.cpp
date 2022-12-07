#include <iostream>
#include "database.h"
#include "databasequerry.h"

int main(int argc, char **argv)
{
    DataBase db{"base.txt"};
    auto load = db.Load();
    if (!load)
    {
        std::cout << "unable to create a database ";
        return 1;
    }
    DataBaseQuery query(&db);
    auto success = query.Execute(argc, argv);
    if (!success)
        std::cout << "unknown format, -help for examples";
    db.Save();
    return 0;
}
