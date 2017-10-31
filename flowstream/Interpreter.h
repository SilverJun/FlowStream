#pragma once

class CSymbol;
class CLine;

//==============================================
// CInterpreter : 인터프리터를 구현한 클래스
class CInterpreter
{
public:
	CInterpreter();
	virtual ~CInterpreter();

private :
	CSymbol*	startSymbol;
	CSymbol*	endSymbol;

public :
	// 초기화
	BOOL	Initialize(CSymbol*	startSymbol, CSymbol*	endSymbol);
	// 인터프리터 파일을 뽑아낸다.
	BOOL	Interpret(CFlowObject* flowObject);
	//std::vector<CSymbol*> symbols, std::vector<CLine*> lines

private :
	// 특수화된 심볼에 대한 처리
	CSymbol*	FlagProc_IF(FILE* file, CSymbol* symbol);
};

