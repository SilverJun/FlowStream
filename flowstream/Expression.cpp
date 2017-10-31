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
	//������ �켱������ ���ؼ� ���� �������� �ϴ� or������� �Ʒ��� �Ľ�Ʈ�� �ۼ�.
	return ExprPtr(COrExp::Parse(it));
}

// OrExp


