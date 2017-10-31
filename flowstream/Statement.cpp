#include "stdafx.h"
#include "Statement.h"

#include "Token.h"
#include "Error.h"

#include "StatementImpl.h"

CStatement::~CStatement()
{
}

void CStatement::Execute(SymbolTable &context)
{
}

void CStatement::Expect(TokenID Expected, const Token &NowToken)
{
	if (Expected != NowToken.token)
		throw(Error(std::string("StatementError : " + NowToken.name)));
}

CStatement *CStatement::Create(tokenItor &itor)
{
	switch (itor->token)
	{
	case If:
		return new CIfStatement(itor);
	case Output:
		return new COutputStatement(itor);
	case Input:
		return new CInputStatement(itor);
	case While:
		return new CWhileStatement(itor);
	case For:
		return new CForStatement(itor);
	case Begin:
		return new CCompoundStatement(itor);
	case Int:
		return new CIntStatement(itor);
	case Float:
		return new CFloatStatement(itor);
	case String:
		return new CStringStatement(itor);
	case Identifier:
		return new CAssignmentStatement(itor);
	case Func:
		return new CFuncStatement(itor);
	case Return:
		return new CReturnStatement(itor);
	case FuncCall:
		return new CFunctionCallStatement(itor);
	default:
		throw(Error(std::string("Unexpected Statement : ") + itor->name));
	}
}


