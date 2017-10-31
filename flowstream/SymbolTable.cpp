#include "stdafx.h"
#include "SymbolTable.h"
#include "Error.h"
#include "State.h"

//SymbolTable::VarTable SymbolTable::globalVarTable = VarTable();
//SymbolTable::FuncTable SymbolTable::funcTable = FuncTable();


Value SymbolTable::GetValue(std::string variable)
{
	Value nResult;
	VarTable::iterator itor = varTable.find(variable);			//변수 탐색
	if (itor == varTable.end())				//탐색실패.
	{
		itor = SymbolTable::globalVarTable.find(variable);
		if (itor == SymbolTable::globalVarTable.end())
		{
			//throw(Error(std::string("Undefined Variable : ") + variable));
			return Value(vNull);
		}
		else
			nResult = itor->second->data;			//탐색성공후 값 반환.
	}
	else
		nResult = itor->second->data;			//탐색성공후 값 반환.

	return nResult;
}

Value SymbolTable::SetValue(std::string variable, Value value)
{
	if (varTable.find(variable) == varTable.end())			//변수 탐색
	{
		if (SymbolTable::globalVarTable.find(variable) == SymbolTable::globalVarTable.end())
			throw(Error(std::string("Uncleared Variable : ") + variable));		//탐색 실패.
		else
		{
			return SymbolTable::globalVarTable[variable]->data.operator=(value);
		}
	}
	else
		return varTable[variable]->data.operator=(value);
}

void SymbolTable::DeleteValue(std::string variable)
{
	VarTable::iterator itor = varTable.find(variable);
	if (itor == varTable.end())
	{
		itor = SymbolTable::globalVarTable.find(variable);
		if (itor == SymbolTable::globalVarTable.end())
			throw(Error(std::string("Uncleared Variable ") + variable));
		else
		{
			delete itor->second;
			SymbolTable::globalVarTable.erase(itor);
		}
	}
	else
	{
		delete itor->second;
		varTable.erase(itor);
	}
}

void SymbolTable::AddValue(std::string variable, ValueType T)
{
	VarTable::iterator itor;
	int i = varTable.size();
	if (i != 0)		//변수 테이블에 아무런 값이 없으면 바로 넣음, 있으면 중복 검사.
	{
		itor = varTable.find(variable);
		if (itor != varTable.end())			//탐색 성공 -> 변수가 이미 등록되어있다.
			throw(Error(std::string("Already Registered Variable : ") + variable));

		itor = SymbolTable::globalVarTable.find(variable);
		if (itor != SymbolTable::globalVarTable.end())			//탐색 성공 -> 변수가 이미 등록되어있다.
			throw(Error(std::string("Already Registered Variable : ") + variable));

	}

	switch (g_State->programScope.top())
	{
	case eGlobal:
		SymbolTable::globalVarTable[variable] = new Symbol(variable, Value(T)); //탐색 실패 -> 변수를 등록할 수 있다.
		break;
	case eFunction:
		varTable[variable] = new Symbol(variable, Value(T)); //탐색 실패 -> 변수를 등록할 수 있다.
		break;
	}
}

bool SymbolTable::CheckValue(std::string variable)
{
	VarTable::iterator itor = varTable.find(variable);			//변수 탐색
	if (itor == varTable.end())				//탐색실패.
	{
		itor = SymbolTable::globalVarTable.find(variable);
		if (itor == SymbolTable::globalVarTable.end())
			return false;
		else
			return true;
	}
	else
		return true;
}

FunctionValue* SymbolTable::GetFunc(std::string funcname)
{
	FunctionValue* nResult;
	FuncTable::iterator itor = funcTable.find(funcname);			//변수 탐색
	if (itor == funcTable.end())				//탐색실패.
		throw(Error(std::string("Undefined Function : ") + funcname));
	else
		nResult = itor->second;			//탐색성공후 값 반환.

	return nResult;
}

void SymbolTable::AddFunc(std::string funcname, FunctionValue* func)
{
	funcTable[funcname] = func;
}
