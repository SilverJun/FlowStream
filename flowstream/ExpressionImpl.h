#ifndef __EXPRESSION_IMPLEMENT_H_
#define __EXPRESSION_IMPLEMENT_H_

#include "Expression.h"

#include "FunctionValue.h"

#include "State.h"
#include "StringPool.h"

class CMultExp : public CExpression			//곱셈처리
{
public:
	static CExpression::ExprPtr Parse(tokenItor &it);
	virtual Value Evaluate(SymbolTable &context);
private:
	Exprs m_exprs;			//표현식들
	std::list<TokenID> m_ops;		//연산자, *, /, %를 이 클래스에서 한번에 처리한다.
};

class CAddExp : public CExpression			//덧셈처리
{
public:
	static CExpression::ExprPtr Parse(tokenItor &it);
	virtual Value Evaluate(SymbolTable &context);
private:
	Exprs m_exprs;			//표현식들
	std::list<bool> m_ops;			//참 : 덧셈, 거짓 : 뺄셈
};

class CComparisonExp : public CExpression		//비교연산처리
{
public:
	CComparisonExp(CExpression::ExprPtr lhs, CExpression::ExprPtr rhs, TokenID tok);
	static CExpression::ExprPtr Parse(tokenItor &it);
	virtual Value Evaluate(SymbolTable &context);
private:
	CExpression::ExprPtr m_lhs;			//좌항
	CExpression::ExprPtr m_rhs;			//우항
	TokenID m_tok;			//비교연산자
	Value result;
};

class CAndExp : public CExpression			//비트연산and
{
public:
	static CExpression::ExprPtr Parse(tokenItor &it);
	virtual Value Evaluate(SymbolTable &context);
private:
	Exprs m_exprs;			//표현식 리스트
	Value result;
};

class COrExp : public CExpression			//비트연산 or
{
public:
	static CExpression::ExprPtr Parse(tokenItor &it);
	virtual Value Evaluate(SymbolTable &context);
private:
	Exprs m_exprs;			//표현식 리스트
	Value result;
};

class CAtom : public CExpression			//단항연산자 처리
{
public:
	static CExpression::ExprPtr Parse(tokenItor &it);
};

class CNumber : public CAtom			//일반 숫자
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

class CNot : public CAtom				//논리연산 not
{
public:
	CNot(CExpression::ExprPtr expr) : m_expr(expr) {}
	virtual Value Evaluate(SymbolTable &context) { return m_expr->Evaluate(context).operator!(); }
private:
	CExpression::ExprPtr m_expr;
};

class CStringAtom : public CAtom			//문자열 표현식.
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

class CIdentifier : public CAtom			//변수호출
{
public:
	CIdentifier(std::string identifier) : m_identifier(identifier) {}
	virtual Value Evaluate(SymbolTable &context) { return context.GetValue(m_identifier); }
private:
	std::string m_identifier;
};

class CCompoundAtom : public CAtom			//괄호처리
{
public:
	CCompoundAtom(CExpression::ExprPtr expr) : m_CExpression(expr) {}
	virtual Value Evaluate(SymbolTable &context) { return m_CExpression->Evaluate(context); }
private:
	CExpression::ExprPtr m_CExpression;
};

class CFunction : public CAtom			//함수호출
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
