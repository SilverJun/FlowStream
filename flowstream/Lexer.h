#pragma once

#include "Token.h"

class Lexer
{
public:
	Lexer();
	~Lexer();

	void RegisterCode(const std::string _code)
	{
		code.clear();
		code = _code;
	}

	void LexicalAnalysis(tokenList &TokenList);

private:
	void Lexer::PasingToken(tokenList &TokenList, std::string::iterator begin, std::string::const_iterator end);

	std::string code;

	TokenID TokenTable[256];

};

