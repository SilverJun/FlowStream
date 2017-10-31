#include "stdafx.h"
#include "Paser.h"

#include "Error.h"

Paser::Paser()
{
}


Paser::~Paser()
{
}

void Paser::SyntaxAnalysis(statementList &StatementList)
{
	

	try
	{
		tokenItor tokenitor = tokenlist.begin();
		while (tokenitor->token != Eof)
			StatementList.push_back(StatementPtr(CStatement::Create(tokenitor)));
	}
	catch (Error& error)
	{
		std::cout << "Paser Error : " << error.what() << std::endl;
		return;
	}
	catch (...)
	{
		std::cout << "Paser Error : Unexcepted Error" << std::endl;
		return;
	}
	
}
//if���� ���� ������, loop���� ���� ������ ������ �󼼱��
//