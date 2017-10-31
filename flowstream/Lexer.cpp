#include "stdafx.h"
#include "Lexer.h"
#include "Error.h"

struct Keyword		//Ű���� ����ü
{
	TokenID tok;		//��ū ��
	const char *str;		//��ū ���ڿ�
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
	{ Func, "func" },					//�Լ�����
	{ Comma, "," },					//���Ÿ� ���� �޸�
	{ ReturnType, "->" },				//�Լ��� ����Ÿ��
	{ Return, "return" },				//�Լ���ü������ ����
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
	std::istringstream iss(code);			//string ó�� ��Ʈ�� getline�� ����ϱ� ���� ��.
	std::string codeLine;				//���ٿ� �ش��ϴ� �ڵ带 ��� ����.

	std::string::iterator begin;
	std::string::const_iterator end;

	try
	{
		while (std::getline(iss, codeLine, '\n'))		//���κ��� ��ū �м�
		{
			begin = codeLine.begin();
			end = codeLine.cend();
			PasingToken(TokenList, begin, end);					//��ū �м�.
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


	TokenList.push_back(Token(Eof, ""));			//�Ǹ������� EOF��ū �߰�
}

void Lexer::PasingToken(tokenList &TokenList, std::string::iterator begin, std::string::const_iterator end)
{
	std::string str = "";
	float num = 0;
	bool bIsFound;		//Ű���忡�� ��ū�� ã�Ҵ��� Ȯ��
	bool bIsFloat = false;
	Token temp;
	std::string::iterator itor;		//���ڿ� ��ȸ �ݺ���

	for (itor = begin; itor != end; ++itor)			//���ڿ� ������ ��ȸ
	{
		num = 0;
		bIsFound = false;
		bIsFloat = false;
		str = "";
		switch (TokenTable[*itor])			//�� ���ڿ� ���ؼ�..
		{
		case Number:				//���ڸ� ���ڳ����� �ν�
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
			itor--;			//�ݺ����� �����ϰ� ���� �ݺ��ڰ� �ϳ� �� �����ǹǷ� �ϳ��� ���ҽ����ش�.
			num = std::stof(str.c_str());			//���� ���ڸ� ���ڷ� ��ȯ.
			str = "";		//���ڿ� �ʱ�ȭ.
			temp = Token(Number, num);
			temp.isFloat = bIsFloat;
			TokenList.push_back(temp);
			break;
		case Letter:
			for (; itor != end; ++itor)
			{
				if (TokenTable[*itor] == Letter || TokenTable[*itor] == Number)					//���ڿ��� ���ڸ� ���� �޾Ƶ��δ�.
				{
					str += *itor;
				}
				else
				{
					break;
				}
			}

			for (const Keyword* i = KeyWordTokens; i->tok != Eof && !bIsFound; i++)				//���� ó������ Ű���忡 �ִ��� Ȯ���Ѵ�.
			{
				if (str == i->str)
				{
					bIsFound = true;
					TokenList.push_back(Token(i->tok, str));
				}
			}
			if (!bIsFound)					//Ű���忡�� ��ã���� ���� ���� ȣ��� �����Ѵ�.
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
			if (itor != end && TokenTable[*std::next(itor)] == '/')		//�ּ����� ������ ���������� �Ǻ�
				return;//�ּ��̸� ���峡���� �� ����
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
			if (itor != end && TokenTable[*std::next(itor)] == '=')				// !�� �ǰų� !=�� �� �� �����Ƿ� �˻�.
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
			if (*itor == ' ' || *itor == '\t' || *itor == '\0')				//���� ����
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