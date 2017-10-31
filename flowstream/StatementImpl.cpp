#include "stdafx.h"
#include "StatementImpl.h"

#include "Error.h"
#include "FunctionValue.h"

#include "State.h"

// CIfStatement

CIfStatement::CIfStatement(tokenItor &itor) : ifStatement(nullptr), elseStatement(nullptr)
{
	Expect(If, *itor++);
	m_expression = CExpression::Parse(itor);
	ifStatement = StatementPtr(CStatement::Create(itor));
	
	if (itor->token == Else)
	{
		itor++;
		elseStatement = StatementPtr(CStatement::Create(itor));
	}
}

void CIfStatement::Execute(SymbolTable &context)
{
	int result = operator==(m_expression->Evaluate(context), Value(vInt, true)).intValue;
	if (result)
		ifStatement->Execute(context);
	else if (elseStatement != nullptr)
		elseStatement->Execute(context);
}

// CWhileStatement

CWhileStatement::CWhileStatement(tokenItor &itor)
{
	Expect(While, *itor++);
	m_expression = CExpression::Parse(itor);
	m_statement = StatementPtr(CStatement::Create(itor));
}

void CWhileStatement::Execute(SymbolTable &context)
{
	while (operator==(m_expression->Evaluate(context), Value(vInt, true)).intValue)
	{
		m_statement->Execute(context);

		Sleep(1);

		if (g_State->programState == eEnd)
			return;
	}
		
}

// CForStatement

CForStatement::CForStatement(tokenItor &itor)
{
	Expect(For, *itor++);
	m_init = StatementPtr(new CAssignmentStatement(itor));			//초기식
	Expect(To, *itor++);
	m_condition = CExpression::Parse(itor);					//조건식
	Expect(Step, *itor++);
	m_increment = StatementPtr(new CAssignmentStatement(itor));			//증감문

	m_statement = StatementPtr(CStatement::Create(itor));
}

void CForStatement::Execute(SymbolTable &context)
{
	for (m_init->Execute(context); operator==(m_condition->Evaluate(context), Value(vInt, true)).intValue; m_increment->Execute(context))
	{
		m_statement->Execute(context);

		Sleep(1);

		if (g_State->programState == eEnd)
			return;
	}
}


// COutputStatement

COutputStatement::COutputStatement(tokenItor &itor)
{
	Expect(Output, *itor++);
	m_expression = CExpression::Parse(itor);
}

void COutputStatement::Execute(SymbolTable &context)
{
	Value value = m_expression->Evaluate(context);

	switch (value.valueType)
	{
	case vNull:
		throw Error(std::string("Output Null Object"));
		break;
	case vInt:
		std::cout << value.intValue;
		break;
	case vFloat:
		std::cout << value.floatValue;
		break;
	case vString:
		std::cout << *value.stringValue;
		break;
	default:
		throw Error(std::string("Output Unexpected Object"));
		break;
	}
}

// CInputStatement

CInputStatement::CInputStatement(tokenItor &itor)
{
	Expect(Input, *itor++);
	m_variable = itor->name;
	itor++;
}

void CInputStatement::Execute(SymbolTable &context)
{
	std::cin >> m_data;
	context.SetValue(m_variable, Value(vInt, m_data));
}

// CCompoundStatement

CCompoundStatement::CCompoundStatement(tokenItor &itor)
{
	Expect(Begin, *itor++);
	while (itor->token != End)
		m_statements.push_back(StatementPtr(CStatement::Create(itor)));
	Expect(End, *itor++);
}

void CCompoundStatement::Execute(SymbolTable &context)
{
	clock_t CurTime, OldTime = clock();

	for (statementList::iterator itor = m_statements.begin(); itor != m_statements.end(); itor++)
	{
		itor->get()->Execute(context);
		if (typeid(*itor->get()) == typeid(CReturnStatement))
			break;

		/*while (1)
		{
			CurTime = clock();
			if (CurTime - OldTime > 33)
			{
				OldTime = CurTime;
				break;
			}
			if (g_State->programState == eEnd)
				return;
		}*/
	}
}

// CIntStatement

CIntStatement::CIntStatement(tokenItor &it)
{
	m_bAssign = false;
	Expect(Int, *it++);
	Expect(Identifier, *it);
	m_variable = it->name;
	if ((++it)->token == Assignment)
	{
		it++;
		m_expression = CExpression::Parse(it);
		m_bAssign = true;
	}
}

void CIntStatement::Execute(SymbolTable &context)
{
	context.AddValue(m_variable, vInt);
	if (m_bAssign)
		context.SetValue(m_variable, m_expression->Evaluate(context));
}

// CFloatStatement

CFloatStatement::CFloatStatement(tokenItor &it)
{
	m_bAssign = false;
	Expect(Float, *it++);
	Expect(Identifier, *it);
	m_variable = it->name;
	if ((++it)->token == Assignment)
	{
		it++;
		m_expression = CExpression::Parse(it);
		m_bAssign = true;
	}
}

void CFloatStatement::Execute(SymbolTable &context)
{
	context.AddValue(m_variable, vFloat);
	if (m_bAssign)
		context.SetValue(m_variable, m_expression->Evaluate(context));
}

// CStringStatement

CStringStatement::CStringStatement(tokenItor &it)
{
	m_bAssign = false;
	Expect(String, *it++);
	Expect(Identifier, *it);
	m_variable = it->name;
	if ((++it)->token == Assignment)
	{
		it++;
		m_expression = CExpression::Parse(it);
		m_bAssign = true;
	}
}

void CStringStatement::Execute(SymbolTable &context)
{
	context.AddValue(m_variable, vString);
	if (m_bAssign)
		context.SetValue(m_variable, m_expression->Evaluate(context));
}

// CAssignmentStatement

CAssignmentStatement::CAssignmentStatement(tokenItor &itor)
{
	Expect(Identifier, *itor);
	m_variable = itor->name;
	itor++;
	op = itor->token;
	itor++;
	m_expression = CExpression::Parse(itor);
}

void CAssignmentStatement::Execute(SymbolTable &context)
{
	Value* thisValue = &context.GetValue(m_variable);
	switch (op)
	{
	case PlusAssign:
		context.SetValue(m_variable, *thisValue + m_expression->Evaluate(context));
		break;
	case MinusAssign:
		context.SetValue(m_variable, *thisValue - m_expression->Evaluate(context));
		break;
	case MultiAssign:
		context.SetValue(m_variable, *thisValue * m_expression->Evaluate(context));
		break;
	case DivideAssign:
		context.SetValue(m_variable, *thisValue / m_expression->Evaluate(context));
		break;
	case Assignment:
		context.SetValue(m_variable, m_expression->Evaluate(context));
		break;
	default:
		throw(Error(std::string("Unexcepted Assignment ") + std::to_string(op)));
		break;
	}
}

CFuncStatement::CFuncStatement(tokenItor &itor)
{
	ValueType returnType;

	std::vector<Symbol> values;

	Expect(Func, *itor++);
	Expect(FuncCall, *itor);
	functionName = itor->name;
	itor++;
	Expect(OpenBracket, *itor++);

	for (; itor->token != CloseBracket; itor++)
	{
		ValueType T = vNull;

		if (itor->name == std::string("int"))
			T = vInt;
		else if (itor->name == std::string("float"))
			T = vFloat;
		else if (itor->name == std::string("string"))
			T = vString;
		else
			throw Error(std::string("Undefined ArgumentType ") + itor->name);
		itor++;

		Expect(Identifier, *itor);

		values.push_back(Symbol(itor->name, Value(T)));

		itor++;

		if (itor->token != Comma)
			break;
	}

	Expect(CloseBracket, *itor++);

	if (itor++->token == ReturnType)
	{
		if (itor->name == std::string("int"))
			returnType = vInt;
		else if (itor->name == std::string("float"))
			returnType = vFloat;
		else if (itor->name == std::string("string"))
			returnType = vString;
		else
			throw Error(std::string("Undefined ReturnType ") + itor->name);
	}
	itor++;
	Expect(Begin, *itor++);

	function = new FunctionValue(returnType, Argument(values));
	function->Create(itor);
	itor++;
}

void CFuncStatement::Execute(SymbolTable &context)
{
	context.AddFunc(functionName, function);
}

CReturnStatement::CReturnStatement(tokenItor &it)
{
	Expect(Return, *it++);
	m_expression = CExpression::Parse(it);
}

void CReturnStatement::Execute(SymbolTable &context)
{
	if (g_State->programScope.top() != eScope::eFunction)
		throw(Error(std::string("Return Error : Not In The Function Scope")));
	else
	{
		Value result = m_expression->Evaluate(context);
		context.AddValue(std::string("FUNCTION_RETURN"), result.valueType);
		context.SetValue(std::string("FUNCTION_RETURN"), result);
	}
}

