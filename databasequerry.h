#pragma once
#include "database.h"
#include "commandargs.h"

using DB_Iterator = std::vector<DataBaseColumn>::iterator;
class DataBaseQuery
{
    DataBase* db_;
public:
    DataBaseQuery(DataBase* db):db_(db){};
    bool Execute(int argc, char **argv);
private:
    DB_Iterator GetDataBaseIterator(size_t number, const string& value);

    //args: name description date category status
    bool Update(const std::vector<string>& args);
    //args: name description date category status
    bool Add(const std::vector<string>& args);
    //args: name
    bool Delete(const std::vector<string>& args);
    //args: name
    bool Done(const std::vector<string>& args);
    //args: predicate and predicate and...
    bool Select(const std::vector<string>& args);

    bool Help();

    std::vector<CommandArgs> ParseSelectArgs(const std::vector<string>&args) const;
    void FiltDataBase(std::vector<DataBaseColumn>& args, size_t number, string sign, string value) const;
};

