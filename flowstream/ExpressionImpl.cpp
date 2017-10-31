#include "stdafx.h"
#include "ExpressionImpl.h"

#include "Error.h"

CExpression::ExprPtr COrExp::Parse(tokenItor &it)
{
	COrExp *orExp = new COrExp;
	orExp->m_exprs.push_back(CAndExp::Parse(it));		//and 파스트리 작성

	while (it->token == Or)			//or연산이 있으면
	{
		it++;
		orExp->m_exprs.push_back(CAndExp::Parse(it));		//우항이 있으므로 다시 and 파스트리 작성.
	}
	return orExp->m_exprs.size() == 1 ? *(orExp->m_exprs.begin()) : ExprPtr(orExp);		//or연산이 있으면 표현식이 최소 2개이므로 리스트의 첫째항을 리턴하고, or연산이 없으면 표현식이 하나이므로 shared_ptr로 감싸 리턴.
}

Value COrExp::Evaluate(SymbolTable &context)
{
	Value result = m_exprs.begin()->get()->Evaluate(context);
	Exprs::iterator it = m_exprs.begin();
	for (it++; it != m_exprs.end(); it++)
		result.operator=(operator|(result, it->get()->Evaluate(context)));			//or연산실행.
	return result;
}

// AndExp

CExpression::ExprPtr CAndExp::Parse(tokenItor &it)
{
	CAndExp *andExp = new CAndExp;
	andExp->m_exprs.push_back(CComparisonExp::Parse(it));		//비교연산 파스트리 작성

	while (it->token == And)
	{
		it++;
		andExp->m_exprs.push_back(CComparisonExp::Parse(it));
	}
	return andExp->m_exprs.size() == 1 ? *(andExp->m_exprs.begin()) : ExprPtr(andExp);
}

Value CAndExp::Evaluate(SymbolTable &context)
{
	Value result = m_exprs.begin()->get()->Evaluate(context);
	Exprs::iterator it = m_exprs.begin();
	for (it++; it != m_exprs.end(); it++)
		result.operator=(operator&(result, it->get()->Evaluate(context)));
	return result;
}


// ComparisonExp

CComparisonExp::CComparisonExp(ExprPtr lhs, ExprPtr rhs, TokenID tok)
	: m_lhs(lhs)
	, m_rhs(rhs)
	, m_tok(tok)
{}

CExpression::ExprPtr CComparisonExp::Parse(tokenItor &it)
{
	ExprPtr lhs, rhs;

	lhs = CAddExp::Parse(it);

	TokenID tok = it->token;
	if (tok == Equal || tok == Less || tok == LessEqual || tok == GreatEqual || tok == Great || tok == NotEqual)
	{
		it++;
		rhs = CAddExp::Parse(it);
	}
	//우항이 없으면 좌항 밖에 없으므로 좌항 리턴, 우항이 있으면 다시 우항 검사.
	return rhs.get() == NULL ? ExprPtr(lhs) : ExprPtr(new CComparisonExp(lhs, rhs, tok));
}

Value CComparisonExp::Evaluate(SymbolTable &context)
{
	switch (m_tok)
	{
	case Equal:
		result = operator==(m_lhs->Evaluate(context), m_rhs->Evaluate(context));
		break;
	case Less:
		result = operator<(m_lhs->Evaluate(context), m_rhs->Evaluate(context));
		break;
	case Great:
		result = operator>(m_lhs->Evaluate(context), m_rhs->Evaluate(context));
		break;
	case LessEqual:
		result = operator<=(m_lhs->Evaluate(context), m_rhs->Evaluate(context));
		break;
	case GreatEqual:
		result = operator>=(m_lhs->Evaluate(context), m_rhs->Evaluate(context));
		break;
	case NotEqual:
		result = operator!=(m_lhs->Evaluate(context), m_rhs->Evaluate(context));
		break;
	default:
		throw(Error(std::string("Unexpected Comparison Token")));
		break;
	}
	return result;
}

// AddExp

CExpression::ExprPtr CAddExp::Parse(tokenItor &it)
{
	CAddExp *addExp = new CAddExp;
	addExp->m_exprs.push_back(CMultExp::Parse(it));		//곱셈 파스트리 작성

	while (it->token == Plus || it->token == Minus)		//토큰이 +, -일때 반복문 실행.
	{
		bool bAdd = it->token == Plus;			//참 : +, 거짓 : -
		addExp->m_ops.push_back(bAdd);
		it++;
		addExp->m_exprs.push_back(CMultExp::Parse(it));			//덧셈중에서도 곱셈이 올수 있으므로 다시 파스트리 작성
	}
	return addExp->m_exprs.size() == 1 ? *(addExp->m_exprs.begin()) : ExprPtr(addExp);
}

Value CAddExp::Evaluate(SymbolTable &context)
{
	Exprs::iterator it = m_exprs.begin();

	Value result = it->get()->Evaluate(context);

	for (std::list<bool>::iterator opIt = m_ops.begin(); opIt != m_ops.end(); opIt++)
	{
		it++;
		if (*opIt)
			result.operator=(operator+(result, it->get()->Evaluate(context)));
		else
			result.operator=(operator-(result, it->get()->Evaluate(context)));
	}
	return result;
}


// MultExp

CExpression::ExprPtr CMultExp::Parse(tokenItor &it)
{
	CMultExp *multExp = new CMultExp;
	multExp->m_exprs.push_back(CAtom::Parse(it));			//단항 연산 파스트리 작성(좌항)

	while (it->token == Multi || it->token == Divide || it->token == Mod)
	{
		multExp->m_ops.push_back(it->token);
		it++;
		multExp->m_exprs.push_back(CAtom::Parse(it));		//곱셈 중에서 우항이 있어야 하니 다시 파스트리 작성
	}
	return multExp->m_exprs.size() == 1 ? *(multExp->m_exprs.begin()) : ExprPtr(multExp);
}

Value CMultExp::Evaluate(SymbolTable &context)
{
	Exprs::iterator it = m_exprs.begin();

	Value result = it->get()->Evaluate(context);

	for (std::list<TokenID>::iterator opIt = m_ops.begin(); opIt != m_ops.end(); opIt++)
	{
		it++;
		if (*opIt == Multi)
			result.operator=(operator*(result, it->get()->Evaluate(context)));
		else if (*opIt == Divide)
			result.operator=(operator/(result, it->get()->Evaluate(context)));
		else if (*opIt == Mod)
			result.operator=(operator%(result, it->get()->Evaluate(context)));
	}
	return result;
}

// Atom

CExpression::ExprPtr CAtom::Parse(tokenItor &it)
{
	CAtom *result;

	switch (it->token)			//단항 처리.
	{
	case Not:
		it++;
		result = new CNot(Parse(it));		//재귀호출로 처리
		break;
	case Number:
		result = new CNumber(*it);
		it++;
		break;
	case Identifier:
		result = new CIdentifier(it->name);
		it++;
		break;
	case ConstString:
		result = new CStringAtom(it->name);
		it++;
		break;
	case FuncCall:
		result = new CFunction(it->name, it);
		break;
	case OpenBracket:
		it++;
		result = new CCompoundAtom(CExpression::Parse(it));		//괄호는 처음부터 새로 파스트리 작성.
		Expect(CloseBracket, *it++);
		break;
	default:
		throw Error(std::string("Unexpected : ") + it->name);
	}
	return ExprPtr(result);
}
