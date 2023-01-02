#include <iostream>
#include "database.h"
#include "databasequerry.h"

int main(int argc, char **argv)
{
    DataBase db{"base.txt"};
    bool load = db.load();
    if (!load)
    {
        std::cout << "unable to create a database ";
        return 1;
    }
    DataBaseQuery query(&db);
    bool success = query.execute(argc, argv);
    if (!success)
        std::cout << "unknown format, -help for examples";
    db.save();
    return 0;
}
