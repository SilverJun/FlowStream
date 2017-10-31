#pragma once

class FunctionValue;

#include "InterpreterSymbol.h"

class SymbolTable
{
public:
	Value GetValue(std::string variable);			//���� �޾ƿ´�.
	Value SetValue(std::string variable, Value value);			//���� �����ϰ� ��ȯ�Ѵ�.
	bool CheckValue(std::string variable);			//������ �ִ��� Ȯ���Ѵ�.
	void DeleteValue(std::string variable);

	void AddValue(std::string variable, ValueType T);			//������ ����Ѵ�.

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

