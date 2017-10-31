#include "stdafx.h"
#include "ObjectFlow.h"
#include "Line.h"
#include "Interpreter.h"
#include "FlowObject.h"

CObjectFlow::CObjectFlow()
{
	selectedSymbol = nullptr;
	selectedLine = nullptr;
}


CObjectFlow::~CObjectFlow()
{
}

BOOL CObjectFlow::Initialize(CSymbol* start, CSymbol* end, CFlowObject* object)
{
	Interpreter = new CInterpreter();

	Interpreter->Initialize(start, end);

	startSymbol = start;
	endSymbol = end;

	FCVariable* xPos = new FCVariable;
	xPos->bPushed = TRUE;
	xPos->name = "xPos";
	xPos->type = eFCVariableType::eVariableType_INT;
	xPos->intValue = &object->position.X;

	PushVariable(xPos);

	FCVariable* yPos = new FCVariable;
	yPos->bPushed = TRUE;
	yPos->name = "yPos";
	yPos->type = eFCVariableType::eVariableType_INT;
	yPos->intValue = &object->position.Y;

	PushVariable(yPos);

	FCVariable* width  = new FCVariable;
	width->bPushed = TRUE;
	width->name = "width";
	width->type = eFCVariableType::eVariableType_INT;
	width->intValue = &object->size.Width;

	PushVariable(width);

	FCVariable* height = new FCVariable;
	height->bPushed = TRUE;
	height->name = "height";
	height->type = eFCVariableType::eVariableType_INT;
	height->intValue = &object->size.Height;

	PushVariable(height);

	return TRUE;
}

BOOL CObjectFlow::PushSymbol(CSymbol* symbol)
{
	if (selectedSymbol == nullptr)
		selectedSymbol = symbol;

	symbols.push_back(symbol);

	return TRUE;
}

BOOL CObjectFlow::SymbolDraw(Graphics* graphics, CPoint scrollPosition)
{
	for each (CSymbol* symbol in symbols)
	{
		symbol->Draw(graphics, scrollPosition);
	}

	return TRUE;
}

BOOL	CObjectFlow::LMouseDown(CPoint mousePosition, CPoint scrollPosition)
{
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	// 선 선택 검사
	for each (CLine* line in lines)
	{
		if (line->LMouseDown(mousePosition, scrollPosition))
		{
			if (selectedSymbol != nullptr)
			{
				// 이전의 심볼의 선택 상태를 반전시킨다.
				selectedSymbol->bSelected = FALSE;
			}

			if (selectedLine != nullptr)
			{
				// 이전의 선의 선택 상태를 반전시킨다.
				selectedLine->bSelected = FALSE;
			}

			// 현재 선택된 선을 바꾼다.
			selectedLine = line;
			// 현재 선택된 선의 선택 상태를 반전시킨다.
			selectedLine->bSelected = TRUE;

			return TRUE;
		}
	}

	// 심볼 선택 검사
	for each (CSymbol* symbol in symbols)
	{
		if (symbol->LMouseDown(mousePosition, scrollPosition))
		{
			if (selectedLine != nullptr)
			{
				// 이전의 선의 선택 상태를 반전시킨다.
				selectedLine->bSelected = FALSE;
			}

			if (symbol != selectedSymbol)
			{
				mainFrame->symbolProperty->PropertyUpdate(symbol);
			}

			if (selectedSymbol != nullptr)
			{
				// 이전의 심볼의 선택 상태를 반전시킨다.
				selectedSymbol->bSelected = FALSE;
			}

			// 현재 선택된 심볼을 바꾼다.
			selectedSymbol = symbol;
			// 현재 선택된 심볼의 선택 상태를 반전시킨다.
			selectedSymbol->bSelected = TRUE;

			// 변수 업데이트
			mainFrame->symbolProperty->PropertyChange(symbol);

			return TRUE;
		}
	}

	return FALSE;
}

BOOL	CObjectFlow::MouseMove(CPoint MousePosition)
{
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	bool flag = FALSE;

	for each (CSymbol* symbol in symbols)
	{
		if (symbol->MouseMove(MousePosition))
		{
			flag = TRUE;
		}
	}

	return flag;
}

BOOL	CObjectFlow::LMouseUp(CPoint MousePosition)
{
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	bool flag = FALSE;

	for each (CSymbol* symbol in symbols)
	{
		if (symbol->LMouseUp(MousePosition))
		{
			flag = TRUE;
		}
	}

	return flag;
}

BOOL CObjectFlow::CreateLine(Point startPos, Point endPos, CPoint scrollPosition, Color color)
{
	CLine*	line = new CLine();

	// 시작 위치에 심볼이 있는지 검사한다.
	for each (CSymbol* symbol in symbols)
	{
		if (CRect(symbol->position.X - scrollPosition.x,
						symbol->position.Y - scrollPosition.y,
						symbol->position.X + symbol->size.Width - scrollPosition.x,
						symbol->position.Y + symbol->size.Height - scrollPosition.y).PtInRect(CPoint(startPos.X, startPos.Y)))
		{
			if (symbol->bSymbolFlag)
				return FALSE;

			// 심볼이 다음심볼을 연결했는가
			if (symbol->nextSymbol != nullptr)
				return FALSE;

			line->startSymbol = symbol;

			break;
		}
	}

	// 끝 위치에 심볼이 있는지 검사한다.
	for each (CSymbol* symbol in symbols)
	{
		if (CRect(symbol->position.X - scrollPosition.x,
						symbol->position.Y - scrollPosition.y,
						symbol->position.X + symbol->size.Width - scrollPosition.x,
						symbol->position.Y + symbol->size.Height - scrollPosition.y).PtInRect(CPoint(endPos.X, endPos.Y)))
		{
			//// 심볼이 연결된 상태인가
			//if (symbol->beforeSymbol != nullptr)
			//	return FALSE;

			line->endSymbol = symbol;

			break;
		}
	}

	// 선이 만들어지지 못함
	if (line->startSymbol == NULL || line->endSymbol == NULL)
		return FALSE;

	if (selectedLine == nullptr)
		selectedLine = line;

	line->color = color;

	// 연결된 선을 통해 심볼들을 연결한다.
	line->startSymbol->nextSymbol = line->endSymbol;
	line->endSymbol->beforeSymbol = line->startSymbol;

	lines.push_back(line);

	return TRUE;
}

BOOL CObjectFlow::CreateFlagLine(Point startPos, Point endPos, CPoint scrollPosition, Color color, BOOL flag)
{
	CLine*	line = new CLine();
	line->bFlag = flag;

	// 시작 위치에 심볼이 있는지 검사한다.
	for each (CSymbol* symbol in symbols)
	{
		if (CRect(symbol->position.X - scrollPosition.x,
			symbol->position.Y - scrollPosition.y,
			symbol->position.X + symbol->size.Width - scrollPosition.x,
			symbol->position.Y + symbol->size.Height - scrollPosition.y).PtInRect(CPoint(startPos.X, startPos.Y)))
		{
			if (symbol->bSymbolFlag)
			{
				if (flag)
				{
					if (symbol->trueSymbol != nullptr)
						return FALSE;
				}
				else
				{
					if (symbol->falseSymbol != nullptr)
						return FALSE;
				}
			}
			else
			{
				return FALSE;
			}

			line->startSymbol = symbol;

			break;
		}
	}

	// 끝 위치에 심볼이 있는지 검사한다.
	for each (CSymbol* symbol in symbols)
	{
		if (CRect(symbol->position.X - scrollPosition.x,
			symbol->position.Y - scrollPosition.y,
			symbol->position.X + symbol->size.Width - scrollPosition.x,
			symbol->position.Y + symbol->size.Height - scrollPosition.y).PtInRect(CPoint(endPos.X, endPos.Y)))
		{
			line->endSymbol = symbol;

			break;
		}
	}

	// 선이 만들어지지 못함
	if (line->startSymbol == NULL || line->endSymbol == NULL)
		return FALSE;

	if (selectedLine == nullptr)
		selectedLine = line;

	line->color = color;

	// 연결된 선을 통해 심볼들을 연결한다.
	if (flag)
		line->startSymbol->trueSymbol = line->endSymbol;
	else
		line->startSymbol->falseSymbol = line->endSymbol;

	lines.push_back(line);

	return TRUE;
}

VOID CObjectFlow::DrawLines(Graphics* graphics, CPoint scrollPosition)
{
	for each (CLine* line in lines)
	{
		line->Draw(graphics, scrollPosition);
	}
}

BOOL CObjectFlow::PushVariable(FCVariable* variable)
{
	for each (FCVariable* var in variables)
	{
		if (var->name == variable->name)
			return FALSE;
	}

	variables.push_back(variable);

	return TRUE;
}

BOOL CObjectFlow::DeleteSelectedObject()
{
	if (selectedLine != nullptr && selectedLine->bSelected)
	{
		// 벡터에서 삭제할 선을 찾는다.
		std::vector<CLine*>::iterator lineIter = std::find(lines.begin(), lines.end(), selectedLine);

		// 특수화 라인과 일반 라인 처리
		if (selectedLine->startSymbol->bSymbolFlag)
		{
			if ((*lineIter)->bFlag)
			{
				selectedLine->startSymbol->trueSymbol = nullptr;

				selectedLine = nullptr;
			}
			else
			{
				selectedLine->startSymbol->falseSymbol = nullptr;

				selectedLine = nullptr;
			}
		}
		else
		{
			selectedLine->startSymbol->nextSymbol = nullptr;

			selectedLine = nullptr;
		}

		// 벡터에서 선을 제거한다.
		lines.erase(lineIter);

		return TRUE;
	}

	if (selectedSymbol != nullptr && selectedSymbol->bSelected)
	{
		if (selectedSymbol == startSymbol || selectedSymbol == endSymbol)
			return FALSE;

		// 이 심볼이 연결한 선이 있는지 찾는다.
		for each (CLine* line in lines)
		{
			// 선이 있다면 그 선을 해제한다.
			if (line->startSymbol == selectedSymbol)
			{
				// 벡터에서 삭제할 선을 찾는다.
				std::vector<CLine*>::iterator lineIter = std::find(lines.begin(), lines.end(), line);

				lines.erase(lineIter);

				// IF문일 경우에, 연결된 선이 두개일 경우를 대비해 한번더 루프를 돈다.
				if (line->startSymbol->bSymbolFlag)
				{
					for each (CLine* flagLine in lines)
					{
						// 선이 있다면 그 선을 해제한다.
						if (flagLine->startSymbol == selectedSymbol)
						{
							// 벡터에서 삭제할 선을 찾는다.
							std::vector<CLine*>::iterator flagLineIter = std::find(lines.begin(), lines.end(), flagLine);
					
							line = nullptr;

							flagLine = nullptr;

							lines.erase(flagLineIter);

							break;
						}
					}

					break;
				}
				else
				{
					break;
				}

				if (lines.size() == 0)
				{
					break;
				}
			}
		}

		// 이 심볼을 연결한 선이 있는지 찾는다.
		for each (CLine* line in lines)
		{
			// 선이 있다면
			if (line->endSymbol == selectedSymbol)
			{
				line->startSymbol->nextSymbol = nullptr;

				// 벡터에서 삭제할 선을 찾는다.
				std::vector<CLine*>::iterator lineIter = std::find(lines.begin(), lines.end(), line);

				line = nullptr;

				lines.erase(lineIter);

				break;
			}
		}
	
		// 벡터에서 삭제할 심볼을 찾는다.
		std::vector<CSymbol*>::iterator symbolIter = std::find(symbols.begin(), symbols.end(), selectedSymbol);

		if (selectedSymbol->bVariableFlag)
		{
			// 벡터에서 삭제할 심볼의 변수를 찾는다.
			std::vector<FCVariable*>::iterator variableIter = std::find(variables.begin(), variables.end(), (*symbolIter)->variable);

			variables.erase(variableIter);
		}

		selectedSymbol = nullptr;

		symbols.erase(symbolIter);

		return TRUE;
	}

	return FALSE;
}
