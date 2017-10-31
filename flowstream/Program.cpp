#include "stdafx.h"
#include "Program.h"
#include "Error.h"

#include "State.h"
#include "StringPool.h"

Program::Program()
{
}


Program::~Program()
{
}


void Program::SetCodeFile(std::string filename)
{
	std::fstream file(filename, std::ios::in);

	if (file.fail())
	{
		TRACE(("Error : FileOpenError!" + filename).c_str());
		return;
	}

	char c;

	while ((c = file.get()) != -1)	//파일내부 코드 다 복사
	{
		code += c;
	}
	code += '\n';
	code += '\0';
}

void Program::DeleteCode()
{
	code.clear();
}

void Program::Init()
{
	CStringPool::GetInstance();
	g_State->programState = eState::eLexicalAnalyzing;
	lexer.RegisterCode(code);
	lexer.LexicalAnalysis(tokenlist);

	g_State->programState = eState::ePasingTree;
	paser.RegisterTokenList(tokenlist);
	paser.SyntaxAnalysis(statementlist);
}

void Program::Release()
{
	statementlist.clear();
	tokenlist.clear();
}

int Program::Run()
{
	g_State->programState = eState::eExecute;
	vm.Execute(statementlist);

	g_State->programState = eState::eEnd;
	return 0;
}

void Program::Stop()
{
	g_State->programState = eEnd;
}
