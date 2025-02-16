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
    îperator = "="; 

    if (whereIsEmpty)
    {
        where = _whereColumn_ + îperator + _whereValue_;
        whereIsEmpty = false;
    }
    else
    {
        where = where + " AND " + _whereColumn_ + îperator + _whereValue_;
    }
    
    return *this;
};

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv)
{
    îperator = "=";

    for (const auto& item : kv)
    {
        if (whereIsEmpty)
        {
            where = item.first + îperator + item.second;
            whereIsEmpty = false;
        }
        else
        {
            where = where + " AND " + item.first + îperator + item.second;
        }
    }
  
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(const std::vector<std::string>& columns)
{
    for (const auto& item : columns)
    {
        if (columnIsEmpty)
        {
            column = item;
            columnIsEmpty = false;
        }
        else
        {
            column = column + ", " + item;
        }
    }
    return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery()
{
    buildQuery = "SELECT";
    buildQuery += " " + column + " FROM " + table + " WHERE " + where + ";";
    return buildQuery;
}


SqlSelectQueryBuilderWithÎperator& SqlSelectQueryBuilderWithÎperator::AddWhere(std::string  _whereColumn_, std::string _îperator_, std::string _whereValue_)
{
    îperator = _îperator_;

    if (whereIsEmpty)
    {
        where = _whereColumn_ + îperator + _whereValue_;
        whereIsEmpty = false;
    }
    else
    {
        where = where + " AND " + _whereColumn_ + îperator + _whereValue_;
    }
    return *this;
}