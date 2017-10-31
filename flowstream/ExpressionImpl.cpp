#include "stdafx.h"
#include "ExpressionImpl.h"

#include "Error.h"

CExpression::ExprPtr COrExp::Parse(tokenItor &it)
{
	COrExp *orExp = new COrExp;
	orExp->m_exprs.push_back(CAndExp::Parse(it));		//and �Ľ�Ʈ�� �ۼ�

	while (it->token == Or)			//or������ ������
	{
		it++;
		orExp->m_exprs.push_back(CAndExp::Parse(it));		//������ �����Ƿ� �ٽ� and �Ľ�Ʈ�� �ۼ�.
	}
	return orExp->m_exprs.size() == 1 ? *(orExp->m_exprs.begin()) : ExprPtr(orExp);		//or������ ������ ǥ������ �ּ� 2���̹Ƿ� ����Ʈ�� ù°���� �����ϰ�, or������ ������ ǥ������ �ϳ��̹Ƿ� shared_ptr�� ���� ����.
}

Value COrExp::Evaluate(SymbolTable &context)
{
	Value result = m_exprs.begin()->get()->Evaluate(context);
	Exprs::iterator it = m_exprs.begin();
	for (it++; it != m_exprs.end(); it++)
		result.operator=(operator|(result, it->get()->Evaluate(context)));			//or�������.
	return result;
}

// AndExp

CExpression::ExprPtr CAndExp::Parse(tokenItor &it)
{
	CAndExp *andExp = new CAndExp;
	andExp->m_exprs.push_back(CComparisonExp::Parse(it));		//�񱳿��� �Ľ�Ʈ�� �ۼ�

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
	//������ ������ ���� �ۿ� �����Ƿ� ���� ����, ������ ������ �ٽ� ���� �˻�.
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
	addExp->m_exprs.push_back(CMultExp::Parse(it));		//���� �Ľ�Ʈ�� �ۼ�

	while (it->token == Plus || it->token == Minus)		//��ū�� +, -�϶� �ݺ��� ����.
	{
		bool bAdd = it->token == Plus;			//�� : +, ���� : -
		addExp->m_ops.push_back(bAdd);
		it++;
		addExp->m_exprs.push_back(CMultExp::Parse(it));			//�����߿����� ������ �ü� �����Ƿ� �ٽ� �Ľ�Ʈ�� �ۼ�
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
	multExp->m_exprs.push_back(CAtom::Parse(it));			//���� ���� �Ľ�Ʈ�� �ۼ�(����)

	while (it->token == Multi || it->token == Divide || it->token == Mod)
	{
		multExp->m_ops.push_back(it->token);
		it++;
		multExp->m_exprs.push_back(CAtom::Parse(it));		//���� �߿��� ������ �־�� �ϴ� �ٽ� �Ľ�Ʈ�� �ۼ�
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

	switch (it->token)			//���� ó��.
	{
	case Not:
		it++;
		result = new CNot(Parse(it));		//���ȣ��� ó��
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
		result = new CCompoundAtom(CExpression::Parse(it));		//��ȣ�� ó������ ���� �Ľ�Ʈ�� �ۼ�.
		Expect(CloseBracket, *it++);
		break;
	default:
		throw Error(std::string("Unexpected : ") + it->name);
	}
	return ExprPtr(result);
}
