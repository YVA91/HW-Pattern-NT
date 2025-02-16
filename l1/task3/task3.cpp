#include <iostream>
#include <vector>
#include <map>
#include "sql_query_builder.h"

int main() {
    SqlSelectQueryBuilderWithОperator query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    //query_builder.AddWhere("id", "42").AddWhere("name", "John");
    query_builder.AddWhere("id", ">", "42").AddWhere("id", "42").AddWhere("name", "John");
   //query_builder.AddWhere("id", "<" "42");

    std::cout << query_builder.BuildQuery();
}
