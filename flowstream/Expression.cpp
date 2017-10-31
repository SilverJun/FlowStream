#include "stdafx.h"
#include "Expression.h"

#include "Error.h"

#include "ExpressionImpl.h"

void CExpression::Expect(TokenID Expected, const Token &NowToken)
{
	if (Expected != NowToken.token)
		throw(Error(std::string("SyntaxError : ") + NowToken.name));
}

CExpression::ExprPtr CExpression::Parse(tokenItor &it)
{
	//연산자 우선순위에 의해서 제일 마지막에 하는 or연산부터 아래로 파스트리 작성.
	return ExprPtr(COrExp::Parse(it));
}

// OrExp


