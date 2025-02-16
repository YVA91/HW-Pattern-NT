#include "sql_query_builder.h"

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(std::string columnName)
{
    if (columnIsEmpty)
    {
        column = columnName;
        columnIsEmpty = false;
    }
    else
    {
        column = column + ", " + columnName;
    }
    return *this;
};

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(std::string tableName)
{
    table = tableName;
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(std::string _whereColumn_, std::string _whereValue_)
{
    if (whereIsEmpty)
    {
        where = where + _whereColumn_ + "=" + _whereValue_;
        whereIsEmpty = false;
    }
    else
    {
        where = where + " AND " + _whereColumn_ + "=" + _whereValue_;
    }
    return *this;
};

std::string SqlSelectQueryBuilder::BuildQuery()
{
    buildQuery = "SELECT";
    buildQuery += " " + column + " FROM " + table + " WHERE " + where + ";";
    return buildQuery;
}
