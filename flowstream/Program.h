#pragma once

#include "Token.h"

#include "Lexer.h"
#include "Paser.h"
#include "VM.h"

#include "Statement.h"

class Program
{
public:
	Program();
	~Program();

	void SetCodeFile(std::string filename);

	void DeleteCode();

	void Init();

	void Release();

	int Run();			//메인에서 실행될 본체

	void Stop();

	VM* GetVM()
	{
		return &vm;
	}

private:
	Lexer lexer;
	Paser paser;
	VM vm;

	std::string code;
	tokenList tokenlist;
	
	statementList statementlist;
};

