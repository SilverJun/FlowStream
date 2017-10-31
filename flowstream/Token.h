#pragma once

#include <string>
#include <list>

enum TokenID			//토큰 열거형
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

struct Token		//토큰 구조체
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

	TokenID token;	//토큰값
	std::string name;		//토큰이름
	float number;		//값

	bool isFloat;
};



typedef std::list<Token> tokenList;				//토큰 리스트
typedef tokenList::iterator tokenItor;		//토큰 리스트 반복자


