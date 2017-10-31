#pragma once

class FunctionValue;

#include "InterpreterSymbol.h"

class SymbolTable
{
public:
	Value GetValue(std::string variable);			//값을 받아온다.
	Value SetValue(std::string variable, Value value);			//값을 저장하고 반환한다.
	bool CheckValue(std::string variable);			//변수가 있는지 확인한다.
	void DeleteValue(std::string variable);

	void AddValue(std::string variable, ValueType T);			//변수를 등록한다.

	void AddFunc(std::string funcname, FunctionValue* func);
	FunctionValue* GetFunc(std::string funcname);
	
	

private:
	typedef std::unordered_map<std::string, Symbol*> VarTable;
	typedef std::unordered_map<std::string, VarTable> LocalVarTable;

	VarTable varTable;
	
	typedef std::unordered_map<std::string, FunctionValue*> FuncTable;

	FuncTable funcTable;
	VarTable globalVarTable;
};

