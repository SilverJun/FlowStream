#ifndef __EXPRESSION_IMPLEMENT_H_
#define __EXPRESSION_IMPLEMENT_H_

#include "Expression.h"

#include "FunctionValue.h"

#include "State.h"
#include "StringPool.h"

class CMultExp : public CExpression			//����ó��
{
public:
	static CExpression::ExprPtr Parse(tokenItor &it);
	virtual Value Evaluate(SymbolTable &context);
private:
	Exprs m_exprs;			//ǥ���ĵ�
	std::list<TokenID> m_ops;		//������, *, /, %�� �� Ŭ�������� �ѹ��� ó���Ѵ�.
};

class CAddExp : public CExpression			//����ó��
{
public:
	static CExpression::ExprPtr Parse(tokenItor &it);
	virtual Value Evaluate(SymbolTable &context);
private:
	Exprs m_exprs;			//ǥ���ĵ�
	std::list<bool> m_ops;			//�� : ����, ���� : ����
};

class CComparisonExp : public CExpression		//�񱳿���ó��
{
public:
	CComparisonExp(CExpression::ExprPtr lhs, CExpression::ExprPtr rhs, TokenID tok);
	static CExpression::ExprPtr Parse(tokenItor &it);
	virtual Value Evaluate(SymbolTable &context);
private:
	CExpression::ExprPtr m_lhs;			//����
	CExpression::ExprPtr m_rhs;			//����
	TokenID m_tok;			//�񱳿�����
	Value result;
};

class CAndExp : public CExpression			//��Ʈ����and
{
public:
	static CExpression::ExprPtr Parse(tokenItor &it);
	virtual Value Evaluate(SymbolTable &context);
private:
	Exprs m_exprs;			//ǥ���� ����Ʈ
	Value result;
};

class COrExp : public CExpression			//��Ʈ���� or
{
public:
	static CExpression::ExprPtr Parse(tokenItor &it);
	virtual Value Evaluate(SymbolTable &context);
private:
	Exprs m_exprs;			//ǥ���� ����Ʈ
	Value result;
};

class CAtom : public CExpression			//���׿����� ó��
{
public:
	static CExpression::ExprPtr Parse(tokenItor &it);
};

class CNumber : public CAtom			//�Ϲ� ����
{
public:
	CNumber(Token token)
	{
		if (token.isFloat)
		{
			m_number = Value(vFloat, token.number);
		}
		else
		{
			m_number = Value(vInt, (int)token.number);
		}
	}
	virtual Value Evaluate(SymbolTable &context) { return m_number; }
private:
	Value m_number;
};

class CNot : public CAtom				//������ not
{
public:
	CNot(CExpression::ExprPtr expr) : m_expr(expr) {}
	virtual Value Evaluate(SymbolTable &context) { return m_expr->Evaluate(context).operator!(); }
private:
	CExpression::ExprPtr m_expr;
};

class CStringAtom : public CAtom			//���ڿ� ǥ����.
{
public:
	CStringAtom(std::string str) : stringData(vString), stringRef(g_StringPool->AddConstString(str)) {}
	virtual Value Evaluate(SymbolTable &context)
	{
		stringData.stringValue = g_StringPool->GetConstString(stringRef);
		return stringData;
	}
private:
	const int stringRef;
	Value stringData;
};

class CIdentifier : public CAtom			//����ȣ��
{
public:
	CIdentifier(std::string identifier) : m_identifier(identifier) {}
	virtual Value Evaluate(SymbolTable &context) { return context.GetValue(m_identifier); }
private:
	std::string m_identifier;
};

class CCompoundAtom : public CAtom			//��ȣó��
{
public:
	CCompoundAtom(CExpression::ExprPtr expr) : m_CExpression(expr) {}
	virtual Value Evaluate(SymbolTable &context) { return m_CExpression->Evaluate(context); }
private:
	CExpression::ExprPtr m_CExpression;
};

class CFunction : public CAtom			//�Լ�ȣ��
{
public:
	CFunction(std::string func, tokenItor &it) : m_func(func)
	{
		Expect(FuncCall, *it++);
		Expect(OpenBracket, *it++);

		while (it->token != CloseBracket)
		{
			args.push_back(CExpression::Parse(it));
			if (it->token != Comma)
				break;
		}
		Expect(CloseBracket, *it++);
	}
	virtual Value Evaluate(SymbolTable &context)
	{
		FunctionValue* i = context.GetFunc(m_func);
		return i->Execute(context, args);
	}
private:
	std::string m_func;
	std::vector<CExpression::ExprPtr> args;
};

#endif
