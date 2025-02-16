#pragma once
#include <iostream>

class SqlSelectQueryBuilder
{
public:
	SqlSelectQueryBuilder& AddColumn(std::string columnName);
	SqlSelectQueryBuilder& AddFrom(std::string tableName);
	SqlSelectQueryBuilder& AddWhere(std::string _whereColumn_, std::string _whereValue_);
	std::string BuildQuery();

public:
	std::string column = "*";
	bool columnIsEmpty = true;
	std::string table = "";
	std::string where = "";
	bool whereIsEmpty = true;
	std::string buildQuery = "";
};
