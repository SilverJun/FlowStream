#pragma once

#include "Token.h"
#include "Statement.h"

class Paser
{
public:
	Paser();
	~Paser();

	void RegisterTokenList(tokenList TokenList)
	{
		tokenlist = TokenList;
	}

	void SyntaxAnalysis(statementList &StatementList);

private:
	tokenList tokenlist;
};

