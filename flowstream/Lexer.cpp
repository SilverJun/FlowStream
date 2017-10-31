#include "stdafx.h"
#include "Lexer.h"
#include "Error.h"

struct Keyword		//키워드 구조체
{
	TokenID tok;		//토큰 값
	const char *str;		//토큰 문자열
};

static const Keyword KeyWordTokens[] =
{
	{ While, "while" },
	{ For, "for" },
	{ To, "to" },
	{ Step, "step" },
	{ If, "if" },
	{ Else, "else" },
	{ Int, "INT" },
	{ Float, "FLOAT" },
	{ String, "STRING" },
	{ Output, "output" },
	{ Input, "input" },
	{ Func, "func" },					//함수선언
	{ Comma, "," },					//열거를 위한 콤마
	{ ReturnType, "->" },				//함수의 리턴타입
	{ Return, "return" },				//함수본체에서의 리턴
	{ Begin, "{" },
	{ End, "}" },
	{ Quotmark, "\"" },
	{ Or, "|" },
	{ And, "&" },
	{ Plus, "+" },
	{ Minus, "-" },
	{ Multi, "*" },
	{ Divide, "/" },
	{ Increment, "++" },
	{ Decrement, "--" },
	{ PlusAssign, "+=" },
	{ MinusAssign, "-=" },
	{ MultiAssign, "*=" },
	{ DivideAssign, "/=" },
	{ Assignment, "=" },
	{ NotEqual, "!=" },
	{ Less, "<" },
	{ Great, ">" },
	{ LessEqual, "<=" },
	{ GreatEqual, ">=" },
	{ Equal, "==" },
	{ OpenBracket, "(" },
	{ CloseBracket, ")" },
	{ Not, "!" },
	{ Mod, "%" },
	{ Annotation, "//" },
	{ Eof, "" }
};

Lexer::Lexer()
{
	for (int i = 0; i < 256; i++)
		TokenTable[i] = Eof;
	for (int i = '0'; i <= '9'; i++)
		TokenTable[i] = Number;
	for (int i = 'A'; i <= 'Z'; i++)
		TokenTable[i] = Letter;
	for (int i = 'a'; i <= 'z'; i++)
		TokenTable[i] = Letter;

	TokenTable['('] = OpenBracket;
	TokenTable[')'] = CloseBracket;
	TokenTable['+'] = Plus;
	TokenTable['-'] = Minus;
	TokenTable['*'] = Multi;
	TokenTable['/'] = Divide;
	TokenTable['%'] = Mod;
	TokenTable['!'] = Not;
	TokenTable['='] = Assignment;
	TokenTable['>'] = Great;
	TokenTable['<'] = Less;
	TokenTable['{'] = Begin;
	TokenTable['}'] = End;
	TokenTable['&'] = And;
	TokenTable['|'] = Or;
	TokenTable['"'] = Quotmark;
	TokenTable[','] = Comma;
}


Lexer::~Lexer()
{
}

void Lexer::LexicalAnalysis(tokenList &TokenList)
{
	std::istringstream iss(code);			//string 처리 스트림 getline을 사용하기 위해 씀.
	std::string codeLine;				//한줄에 해당하는 코드를 담고 있음.

	std::string::iterator begin;
	std::string::const_iterator end;

	try
	{
		while (std::getline(iss, codeLine, '\n'))		//라인별로 토큰 분석
		{
			begin = codeLine.begin();
			end = codeLine.cend();
			PasingToken(TokenList, begin, end);					//토큰 분석.
		}
	}
	catch (Error& error)
	{
		std::cout << "Lexical Error : " << error.what()  << std::endl;
		system("pause");
		return;
	}
	catch (...)
	{
		std::cout << "Lexical Error : Unexcepted Error" << std::endl;
		system("pause");
		return;
	}


	TokenList.push_back(Token(Eof, ""));			//맨마지막에 EOF토큰 추가
}

void Lexer::PasingToken(tokenList &TokenList, std::string::iterator begin, std::string::const_iterator end)
{
	std::string str = "";
	float num = 0;
	bool bIsFound;		//키워드에서 토큰을 찾았는지 확인
	bool bIsFloat = false;
	Token temp;
	std::string::iterator itor;		//문자열 순회 반복자

	for (itor = begin; itor != end; ++itor)			//문자열 끝까지 순회
	{
		num = 0;
		bIsFound = false;
		bIsFloat = false;
		str = "";
		switch (TokenTable[*itor])			//한 문자에 대해서..
		{
		case Number:				//숫자면 숫자끝까지 인식
			for (; itor != end; ++itor)
			{
				if (TokenTable[*itor] == Number)
				{
					str += *itor;
				}
				else if (*itor == '.')
				{
					bIsFloat = true;
					str += *itor;
				}
				else
					break;
			}
			itor--;			//반복문을 실행하고 나면 반복자가 하나 더 증가되므로 하나를 감소시켜준다.
			num = std::stof(str.c_str());			//얻은 문자를 숫자로 변환.
			str = "";		//문자열 초기화.
			temp = Token(Number, num);
			temp.isFloat = bIsFloat;
			TokenList.push_back(temp);
			break;
		case Letter:
			for (; itor != end; ++itor)
			{
				if (TokenTable[*itor] == Letter || TokenTable[*itor] == Number)					//문자열과 숫자를 같이 받아들인다.
				{
					str += *itor;
				}
				else
				{
					break;
				}
			}

			for (const Keyword* i = KeyWordTokens; i->tok != Eof && !bIsFound; i++)				//제일 처음에는 키워드에 있는지 확인한다.
			{
				if (str == i->str)
				{
					bIsFound = true;
					TokenList.push_back(Token(i->tok, str));
				}
			}
			if (!bIsFound)					//키워드에서 못찾았을 경우는 변수 호출로 간주한다.
			{
				if (itor != end && TokenTable[*itor] == OpenBracket)
				{
					TokenList.push_back(Token(FuncCall, str));
				}
				else
				{
					TokenList.push_back(Token(Identifier, str));
				}
			}
			itor--;
			break;
		case Quotmark:
			for (++itor; *itor != Quotmark && itor != end; ++itor)
			{
				if (*itor == '\\')
				{
					itor++;
					switch (*itor)
					{
					case 'n':
						str += '\n';
						break;
					case '0':
						str += '\0';
						break;
					case 't':
						str += '\t';
						break;
					case 'a':
						str += '\a';
						break;
					case 'r':
						str += '\r';
						break;
					case 'b':
						str += '\b';
						break;
					case '"':
						str += '\"';
						break;
					case '\'':
						str += '\'';
						break;
					case '\\':
						str += '\\';
						break;
					default:
						break;
					}
				}
				else
					str += *itor;
			}
			TokenList.push_back(Token(ConstString, str));

			break;
		case OpenBracket:
			TokenList.push_back(Token(OpenBracket, "("));
			break;
		case CloseBracket:
			TokenList.push_back(Token(CloseBracket, ")"));
			break;
		case Plus:
			if (itor != end && TokenTable[*std::next(itor)] == '+')
			{
				TokenList.push_back(Token(Increment, "++"));
				itor++;
			}
			else if (itor != end && TokenTable[*std::next(itor)] == '=')
			{
				TokenList.push_back(Token(PlusAssign, "+="));
				itor++;
			}
			else
			{
				TokenList.push_back(Token(Plus, "+"));
			}
			break;
		case Minus:
			if (itor != end && TokenTable[*std::next(itor)] == '-')
			{
				TokenList.push_back(Token(Decrement, "--"));
				itor++;
			}
			else if (itor != end && TokenTable[*std::next(itor)] == '>')
			{
				TokenList.push_back(Token(ReturnType, "->"));
				itor++;
			}
			else if (itor != end && TokenTable[*std::next(itor)] == '=')
			{
				TokenList.push_back(Token(MinusAssign, "-="));
				itor++;
			}
			else
			{
				TokenList.push_back(Token(Minus, "-"));
			}
			break;
		case Multi:
			if (itor != end && TokenTable[*std::next(itor)] == '=')
			{
				TokenList.push_back(Token(MultiAssign, "*="));
				itor++;
			}
			else
			{
				TokenList.push_back(Token(Multi, "*"));
			}
			break;
		case Divide:
			if (itor != end && TokenTable[*std::next(itor)] == '/')		//주석인지 나누기 연산자인지 판별
				return;//주석이면 문장끝까지 다 생략
			else if (itor != end && TokenTable[*std::next(itor)] == '=')
			{
				TokenList.push_back(Token(DivideAssign, "/="));
				itor++;
			}
			else
				TokenList.push_back(Token(Divide, "/"));
			break;
		case Mod:
			TokenList.push_back(Token(Mod, "%"));
			break;
		case Not:
			if (itor != end && TokenTable[*std::next(itor)] == '=')				// !이 되거나 !=이 될 수 있으므로 검사.
			{
				TokenList.push_back(Token(NotEqual, "!="));
				itor++;
			}
			else
			{
				TokenList.push_back(Token(Not, "!"));
			}
			break;
		case Great:
			if (itor != end && TokenTable[*std::next(itor)] == '=')
			{
				TokenList.push_back(Token(GreatEqual, ">="));
				itor++;
			}
			else
			{
				TokenList.push_back(Token(Great, ">"));
			}
			break;
		case Less:
			if (itor != end && TokenTable[*std::next(itor)] == '=')
			{
				TokenList.push_back(Token(LessEqual, "<="));
				itor++;
			}
			else
			{
				TokenList.push_back(Token(Less, "<"));
			}
			break;
		case Or:
			if (itor != end && TokenTable[*std::next(itor)] == '|')
			{
				//throw(Error(std::string("Unexpected Token : ") + '|'));
			}
			else
			{
				TokenList.push_back(Token(Or, "|"));
				itor++;
			}
			break;
		case And:
			if (itor != end && TokenTable[*std::next(itor)] == '&')
			{
				//throw(Error(std::string("Unexpected Token : ") + '&'));
			}
			else
			{
				TokenList.push_back(Token(And, "&"));
				itor++;
			}
			break;
		case Assignment:
			if (itor != end && TokenTable[*std::next(itor)] == '=')
			{
				TokenList.push_back(Token(Equal, "=="));
				itor++;
			}
			else
			{
				TokenList.push_back(Token(Assignment, "="));
			}
			break;
		case Begin:
			TokenList.push_back(Token(Begin, "{"));
			break;
		case End:
			TokenList.push_back(Token(End, "}"));
			break;
		case Comma:
			TokenList.push_back(Token(Comma, ","));
			break;
		default:
			if (*itor == ' ' || *itor == '\t' || *itor == '\0')				//공백 무시
			{
				break;
			}
			else
			{
				throw(Error(std::string("Unexpected Token : ") + *itor));
			}
			break;
		}
	}
}