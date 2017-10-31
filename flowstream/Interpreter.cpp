#include "stdafx.h"
#include "Interpreter.h"
#include "Line.h"
#include "FlowObject.h"

#include "FlowStreamDoc.h"

CInterpreter::CInterpreter()
{
}


CInterpreter::~CInterpreter()
{
}

BOOL CInterpreter::Initialize(CSymbol* startSymbol, CSymbol* endSymbol)
{
	this->startSymbol = startSymbol;
	this->endSymbol = endSymbol;

	return TRUE;
}

BOOL CInterpreter::Interpret(CFlowObject* flowObject)
{
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	CFlowStreamDoc* pDoc = (CFlowStreamDoc*)mainFrame->GetActiveDocument();

	CT2CA convertedName(flowObject->name);
	std::string fileName = "Resource\\";
	
	if (!(pDoc->projectName == ""))		//빈문서 처리.
	{
		CT2CA convertedPath = pDoc->filePath;
		fileName = convertedPath;
		fileName += "Resource\\";
	}
	else
	{
		fileName = "Resource\\";
	}


	fileName += convertedName;
	fileName += "\\"; 
	fileName += convertedName; 
	fileName += ".txt";

	FILE*	interpreterFile = fopen(fileName.c_str(), "w+");

	CSymbol* symbol = startSymbol;

	// 기본적인 오브젝트의 변수들을 등록한다.
	fprintf(interpreterFile, symbol->InterpreterLabel().c_str());
	fprintf(interpreterFile, "\n");

	std::string baseLabel = "INT xPos\nINT yPos\nINT width\nINT height\n";
	baseLabel += "xPos = ";	baseLabel += std::to_string(flowObject->position.X);		baseLabel += "\n";
	baseLabel += "yPos = ";	baseLabel += std::to_string(flowObject->position.Y);		baseLabel += "\n";	
	baseLabel += "width = ";	baseLabel += std::to_string(flowObject->size.Width);	baseLabel += "\n";	
	baseLabel += "height = ";	baseLabel += std::to_string(flowObject->size.Height);	baseLabel += "\n";

	fprintf(interpreterFile, baseLabel.c_str());

	for (symbol = startSymbol->nextSymbol; symbol != endSymbol; symbol = symbol->nextSymbol)
	{
		// IF 분기문 처리
		if (symbol->bSymbolFlag)
		{
			std::string ifLabel = symbol->InterpreterLabel();
			ifLabel += "\n";
			fprintf(interpreterFile, ifLabel.c_str());
			FlagProc_IF(interpreterFile, symbol->trueSymbol);

			std::string elseLabel = "else\n{\n";
			fprintf(interpreterFile, elseLabel.c_str());
			symbol = FlagProc_IF(interpreterFile, symbol->falseSymbol);
		}
		else
		{
			std::string label = symbol->InterpreterLabel();
			label += "\n";

			fprintf(interpreterFile, label.c_str());
		}

		if (symbol->nextSymbol == nullptr)
		{
			AfxMessageBox(_T("인터프리터가 끝까지 연결되지 않았습니다."));

			return FALSE;
		}
	}

	fprintf(interpreterFile, endSymbol->InterpreterLabel().c_str());

	fclose(interpreterFile);

	return FALSE;
}

CSymbol* CInterpreter::FlagProc_IF(FILE* file, CSymbol* symbol)
{
	for (CSymbol* nextSymbol = symbol; ; nextSymbol = nextSymbol->nextSymbol)
	{
		if (nextSymbol == nullptr)
		{
			AfxMessageBox(_T("인터프리터가 끝까지 연결되지 않았습니다."));

			return nullptr;
		}

		if (nextSymbol->bSymbolFlag)
		{
			std::string ifLabel = symbol->InterpreterLabel();
			ifLabel += "\n";
			fprintf(file, ifLabel.c_str());
			FlagProc_IF(file, nextSymbol->trueSymbol);

			std::string elseLabel = "else\n{\n";
			fprintf(file, elseLabel.c_str());
			FlagProc_IF(file, nextSymbol->falseSymbol);
		}

		std::string label = nextSymbol->InterpreterLabel();

		fprintf(file, label.c_str());
		fprintf(file, "\n");

		if (label == "}")
			return nextSymbol;
	}
}

