#pragma once

class CSymbol;
class CLine;

//==============================================
// CInterpreter : ���������͸� ������ Ŭ����
class CInterpreter
{
public:
	CInterpreter();
	virtual ~CInterpreter();

private :
	CSymbol*	startSymbol;
	CSymbol*	endSymbol;

public :
	// �ʱ�ȭ
	BOOL	Initialize(CSymbol*	startSymbol, CSymbol*	endSymbol);
	// ���������� ������ �̾Ƴ���.
	BOOL	Interpret(CFlowObject* flowObject);
	//std::vector<CSymbol*> symbols, std::vector<CLine*> lines

private :
	// Ư��ȭ�� �ɺ��� ���� ó��
	CSymbol*	FlagProc_IF(FILE* file, CSymbol* symbol);
};

