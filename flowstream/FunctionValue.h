#ifndef __FUNCTIONVALUE_H_
#define __FUNCTIONVALUE_H_

#include "Value.h"
#include "Expression.h"
#include "Statement.h"

#include "SymbolTable.h"

struct Argument
{
	Argument(std::vector<Symbol>& values)
	: valueArgc(values.size()), valueArgv(values)
	{
	}

	int valueArgc;
	std::vector<Symbol> valueArgv;
};


class FunctionValue
{
public:
	FunctionValue(ValueType rt, Argument arg);
	~FunctionValue();

	void Create(tokenItor &itor);
	Value Execute(SymbolTable &context, std::vector<CExpression::ExprPtr> executeArgValue);

private:
	Value returnValue;
	statementList statements;
	ValueType returnType;
	
	Argument funcArg;
};

#endif
