#include "stdafx.h"
#include "SymbolTable.h"
#include "Error.h"
#include "State.h"

//SymbolTable::VarTable SymbolTable::globalVarTable = VarTable();
//SymbolTable::FuncTable SymbolTable::funcTable = FuncTable();


Value SymbolTable::GetValue(std::string variable)
{
	Value nResult;
	VarTable::iterator itor = varTable.find(variable);			//���� Ž��
	if (itor == varTable.end())				//Ž������.
	{
		itor = SymbolTable::globalVarTable.find(variable);
		if (itor == SymbolTable::globalVarTable.end())
		{
			//throw(Error(std::string("Undefined Variable : ") + variable));
			return Value(vNull);
		}
		else
			nResult = itor->second->data;			//Ž�������� �� ��ȯ.
	}
	else
		nResult = itor->second->data;			//Ž�������� �� ��ȯ.

	return nResult;
}

Value SymbolTable::SetValue(std::string variable, Value value)
{
	if (varTable.find(variable) == varTable.end())			//���� Ž��
	{
		if (SymbolTable::globalVarTable.find(variable) == SymbolTable::globalVarTable.end())
			throw(Error(std::string("Uncleared Variable : ") + variable));		//Ž�� ����.
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
	if (i != 0)		//���� ���̺� �ƹ��� ���� ������ �ٷ� ����, ������ �ߺ� �˻�.
	{
		itor = varTable.find(variable);
		if (itor != varTable.end())			//Ž�� ���� -> ������ �̹� ��ϵǾ��ִ�.
			throw(Error(std::string("Already Registered Variable : ") + variable));

		itor = SymbolTable::globalVarTable.find(variable);
		if (itor != SymbolTable::globalVarTable.end())			//Ž�� ���� -> ������ �̹� ��ϵǾ��ִ�.
			throw(Error(std::string("Already Registered Variable : ") + variable));

	}

	switch (g_State->programScope.top())
	{
	case eGlobal:
		SymbolTable::globalVarTable[variable] = new Symbol(variable, Value(T)); //Ž�� ���� -> ������ ����� �� �ִ�.
		break;
	case eFunction:
		varTable[variable] = new Symbol(variable, Value(T)); //Ž�� ���� -> ������ ����� �� �ִ�.
		break;
	}
}

bool SymbolTable::CheckValue(std::string variable)
{
	VarTable::iterator itor = varTable.find(variable);			//���� Ž��
	if (itor == varTable.end())				//Ž������.
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
	FuncTable::iterator itor = funcTable.find(funcname);			//���� Ž��
	if (itor == funcTable.end())				//Ž������.
		throw(Error(std::string("Undefined Function : ") + funcname));
	else
		nResult = itor->second;			//Ž�������� �� ��ȯ.

	return nResult;
}

void SymbolTable::AddFunc(std::string funcname, FunctionValue* func)
{
	funcTable[funcname] = func;
}
