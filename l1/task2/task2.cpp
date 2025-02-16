#include <iostream>
#include <vector>
#include <map>
#include "sql_query_builder.h"

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");


    //std::vector<std::string> v = { "ab", "ac", "ad", "ak", "ae" };
    //query_builder.AddColumns(v);

    /*
    std::map<std::string, std::string> wh = {
        {"Moscow", "11"},
        {"Rome", "22"} };
    query_builder.AddWhere(wh);
    */

    std::cout << query_builder.BuildQuery();
}
