#ifndef __STATEMENT_IMPLEMENT_H_
#define __STATEMENT_IMPLEMENT_H_

#include "Token.h"
#include "VM.h"
#include "Expression.h"
#include "Statement.h"

#include "State.h"

class CIfStatement : public CStatement
{
public:
	CIfStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);

private:
	CExpression::ExprPtr m_expression;			//if m_expression
	StatementPtr ifStatement;					//{m_statement}
	StatementPtr elseStatement;					//{m_statement}
};

class CWhileStatement : public CStatement
{
public:
	CWhileStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);

private:
	CExpression::ExprPtr m_expression;				//while m_expression
	StatementPtr m_statement;						//{m_statement}
};

class CForStatement : public CStatement
{
public:
	CForStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);

private:
	StatementPtr m_init;
	CExpression::ExprPtr m_condition;
	StatementPtr m_increment;
	StatementPtr m_statement;						//{m_statement}
};

class COutputStatement : public CStatement
{
public:
	COutputStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);

private:
	CExpression::ExprPtr m_expression;				//output m_expression
};

class CInputStatement : public CStatement
{
public:
	CInputStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);

private:
	std::string m_variable;
	int m_data;						//키보드에서 받을 int형 데이타를 저장할 변수
};

class CCompoundStatement : public CStatement
{
public:
	CCompoundStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);

private:
	statementList m_statements;					//{m_statement}
};

class CIntStatement : public CStatement
{
public:
	CIntStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);
private:
	bool m_bAssign;				//변수선언후 바로 초기화 구문이 있는지 없는지
	std::string m_variable;				//int m_variable
	CExpression::ExprPtr m_expression;		//int m_variable = m_expression
};

class CFloatStatement : public CStatement
{
public:
	CFloatStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);
private:
	bool m_bAssign;				//변수선언후 바로 초기화 구문이 있는지 없는지
	std::string m_variable;				//float m_variable
	CExpression::ExprPtr m_expression;		//float m_variable = m_expression
};

class CStringStatement : public CStatement
{
public:
	CStringStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);
private:
	bool m_bAssign;				//변수선언후 바로 초기화 구문이 있는지 없는지
	std::string m_variable;				//string m_variable
	CExpression::ExprPtr m_expression;		//string m_variable = m_expression
};

class CAssignmentStatement : public CStatement
{
public:
	CAssignmentStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);
private:
	std::string m_variable;				//m_variable = m_expression
	CExpression::ExprPtr m_expression;
	TokenID op;
};

class CFuncStatement : public CStatement
{
public:
	CFuncStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);

private:
	std::string functionName;
	FunctionValue* function;

	statementList m_statements;						//{m_statement}
};

class CReturnStatement : public CStatement
{
public:
	CReturnStatement(tokenItor &it);
	virtual void Execute(SymbolTable &context);

	friend FunctionValue;

private:
	CExpression::ExprPtr m_expression;
};

class CFunctionCallStatement : public CStatement
{
public:
	CFunctionCallStatement(tokenItor &it)
	{
		Expect(FuncCall, *it);
		m_expression = CExpression::Parse(it);
	}

	virtual void Execute(SymbolTable &context)
	{
		m_expression->Evaluate(context);
	}

private:
	CExpression::ExprPtr m_expression;
};

#endif
