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
    �perator = "="; 

    if (whereIsEmpty)
    {
        where = _whereColumn_ + �perator + _whereValue_;
        whereIsEmpty = false;
    }
    else
    {
        where = where + " AND " + _whereColumn_ + �perator + _whereValue_;
    }
    
    return *this;
};

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv)
{
    �perator = "=";

    for (const auto& item : kv)
    {
        if (whereIsEmpty)
        {
            where = item.first + �perator + item.second;
            whereIsEmpty = false;
        }
        else
        {
            where = where + " AND " + item.first + �perator + item.second;
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


SqlSelectQueryBuilderWith�perator& SqlSelectQueryBuilderWith�perator::AddWhere(std::string  _whereColumn_, std::string _�perator_, std::string _whereValue_)
{
    �perator = _�perator_;

    if (whereIsEmpty)
    {
        where = _whereColumn_ + �perator + _whereValue_;
        whereIsEmpty = false;
    }
    else
    {
        where = where + " AND " + _whereColumn_ + �perator + _whereValue_;
    }
    return *this;
}