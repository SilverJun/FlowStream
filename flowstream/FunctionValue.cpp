#include "stdafx.h"
#include "FunctionValue.h"

#include "StatementImpl.h"

FunctionValue::FunctionValue(ValueType rt, Argument arg)
: funcArg(arg)
{
	returnType = rt;
	returnValue = Value(returnType);
}


FunctionValue::~FunctionValue()
{
}

void FunctionValue::Create(tokenItor &itor)
{
	while (itor->token != End)
		statements.push_back(StatementPtr(CStatement::Create(itor)));
}


Value FunctionValue::Execute(SymbolTable &context, std::vector<CExpression::ExprPtr> executeArgValue)
{
	SymbolTable localContext;
	
	g_State->programScope.push(eScope::eFunction);
	for (int i = 0; i < funcArg.valueArgc; i++)
	{
		localContext.AddValue(funcArg.valueArgv[i].name, funcArg.valueArgv[i].data.valueType);
		Value arg = Value(funcArg.valueArgv[i].data.valueType);
		localContext.SetValue(funcArg.valueArgv[i].name, arg.operator=(executeArgValue[i]->Evaluate(context)));
	}
	
	//½ÇÇà.

	for (statementList::iterator sitor = statements.begin(); sitor != statements.end(); sitor++)
	{
		sitor->get()->Execute(localContext);
		if (localContext.CheckValue(std::string("FUNCTION_RETURN")))
		{
			returnValue = localContext.GetValue(std::string("FUNCTION_RETURN"));
			break;
		}
	}

	g_State->programScope.pop();

	return returnValue;
}

