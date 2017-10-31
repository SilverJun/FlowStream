#pragma once

#include <string>
#include <list>

enum TokenID			//��ū ������
{
	If = 256,
	Else,
	While,
	For,
	To,
	Step,
	Output,
	Input,
	Func,
	ReturnType,
	Return,
	FuncCall,
	Identifier,
	Int,
	Float,
	Number,
	String,
	ConstString,
	Letter,
	Annotation,
	LessEqual,
	GreatEqual,
	NotEqual,
	Equal,
	Increment,
	Decrement,
	PlusAssign,
	MinusAssign,
	MultiAssign,
	DivideAssign,
	Eof,
	Comma = ',',
	Assignment = '=',
	Begin = '{',
	End = '}',
	ArrayOpen = '[',
	ArrayClose = ']',
	Quotmark = '"',
	Plus = '+',
	Minus = '-',
	Multi = '*',
	Divide = '/',
	Mod = '%',
	And = '&',
	Or = '|',
	Less = '<',
	Great = '>',
	OpenBracket = '(',
	CloseBracket = ')',
	Not = '!'
};

struct Token		//��ū ����ü
{
	Token()
	{
	}

	Token(TokenID token, float number = 0, std::string name = "") :
		token(token),
		number(number),
		name(name), 
		isFloat(false)
	{
	}

	Token(TokenID token, std::string name = "", float number = 0) :
		token(token),
		name(name),
		number(number),
		isFloat(false)
	{
	}

	TokenID token;	//��ū��
	std::string name;		//��ū�̸�
	float number;		//��

	bool isFloat;
};



typedef std::list<Token> tokenList;				//��ū ����Ʈ
typedef tokenList::iterator tokenItor;		//��ū ����Ʈ �ݺ���


