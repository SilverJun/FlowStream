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

	// �� ���� �˻�
	for each (CLine* line in lines)
	{
		if (line->LMouseDown(mousePosition, scrollPosition))
		{
			if (selectedSymbol != nullptr)
			{
				// ������ �ɺ��� ���� ���¸� ������Ų��.
				selectedSymbol->bSelected = FALSE;
			}

			if (selectedLine != nullptr)
			{
				// ������ ���� ���� ���¸� ������Ų��.
				selectedLine->bSelected = FALSE;
			}

			// ���� ���õ� ���� �ٲ۴�.
			selectedLine = line;
			// ���� ���õ� ���� ���� ���¸� ������Ų��.
			selectedLine->bSelected = TRUE;

			return TRUE;
		}
	}

	// �ɺ� ���� �˻�
	for each (CSymbol* symbol in symbols)
	{
		if (symbol->LMouseDown(mousePosition, scrollPosition))
		{
			if (selectedLine != nullptr)
			{
				// ������ ���� ���� ���¸� ������Ų��.
				selectedLine->bSelected = FALSE;
			}

			if (symbol != selectedSymbol)
			{
				mainFrame->symbolProperty->PropertyUpdate(symbol);
			}

			if (selectedSymbol != nullptr)
			{
				// ������ �ɺ��� ���� ���¸� ������Ų��.
				selectedSymbol->bSelected = FALSE;
			}

			// ���� ���õ� �ɺ��� �ٲ۴�.
			selectedSymbol = symbol;
			// ���� ���õ� �ɺ��� ���� ���¸� ������Ų��.
			selectedSymbol->bSelected = TRUE;

			// ���� ������Ʈ
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

	// ���� ��ġ�� �ɺ��� �ִ��� �˻��Ѵ�.
	for each (CSymbol* symbol in symbols)
	{
		if (CRect(symbol->position.X - scrollPosition.x,
						symbol->position.Y - scrollPosition.y,
						symbol->position.X + symbol->size.Width - scrollPosition.x,
						symbol->position.Y + symbol->size.Height - scrollPosition.y).PtInRect(CPoint(startPos.X, startPos.Y)))
		{
			if (symbol->bSymbolFlag)
				return FALSE;

			// �ɺ��� �����ɺ��� �����ߴ°�
			if (symbol->nextSymbol != nullptr)
				return FALSE;

			line->startSymbol = symbol;

			break;
		}
	}

	// �� ��ġ�� �ɺ��� �ִ��� �˻��Ѵ�.
	for each (CSymbol* symbol in symbols)
	{
		if (CRect(symbol->position.X - scrollPosition.x,
						symbol->position.Y - scrollPosition.y,
						symbol->position.X + symbol->size.Width - scrollPosition.x,
						symbol->position.Y + symbol->size.Height - scrollPosition.y).PtInRect(CPoint(endPos.X, endPos.Y)))
		{
			//// �ɺ��� ����� �����ΰ�
			//if (symbol->beforeSymbol != nullptr)
			//	return FALSE;

			line->endSymbol = symbol;

			break;
		}
	}

	// ���� ��������� ����
	if (line->startSymbol == NULL || line->endSymbol == NULL)
		return FALSE;

	if (selectedLine == nullptr)
		selectedLine = line;

	line->color = color;

	// ����� ���� ���� �ɺ����� �����Ѵ�.
	line->startSymbol->nextSymbol = line->endSymbol;
	line->endSymbol->beforeSymbol = line->startSymbol;

	lines.push_back(line);

	return TRUE;
}

BOOL CObjectFlow::CreateFlagLine(Point startPos, Point endPos, CPoint scrollPosition, Color color, BOOL flag)
{
	CLine*	line = new CLine();
	line->bFlag = flag;

	// ���� ��ġ�� �ɺ��� �ִ��� �˻��Ѵ�.
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

	// �� ��ġ�� �ɺ��� �ִ��� �˻��Ѵ�.
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

	// ���� ��������� ����
	if (line->startSymbol == NULL || line->endSymbol == NULL)
		return FALSE;

	if (selectedLine == nullptr)
		selectedLine = line;

	line->color = color;

	// ����� ���� ���� �ɺ����� �����Ѵ�.
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
		// ���Ϳ��� ������ ���� ã�´�.
		std::vector<CLine*>::iterator lineIter = std::find(lines.begin(), lines.end(), selectedLine);

		// Ư��ȭ ���ΰ� �Ϲ� ���� ó��
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

		// ���Ϳ��� ���� �����Ѵ�.
		lines.erase(lineIter);

		return TRUE;
	}

	if (selectedSymbol != nullptr && selectedSymbol->bSelected)
	{
		if (selectedSymbol == startSymbol || selectedSymbol == endSymbol)
			return FALSE;

		// �� �ɺ��� ������ ���� �ִ��� ã�´�.
		for each (CLine* line in lines)
		{
			// ���� �ִٸ� �� ���� �����Ѵ�.
			if (line->startSymbol == selectedSymbol)
			{
				// ���Ϳ��� ������ ���� ã�´�.
				std::vector<CLine*>::iterator lineIter = std::find(lines.begin(), lines.end(), line);

				lines.erase(lineIter);

				// IF���� ��쿡, ����� ���� �ΰ��� ��츦 ����� �ѹ��� ������ ����.
				if (line->startSymbol->bSymbolFlag)
				{
					for each (CLine* flagLine in lines)
					{
						// ���� �ִٸ� �� ���� �����Ѵ�.
						if (flagLine->startSymbol == selectedSymbol)
						{
							// ���Ϳ��� ������ ���� ã�´�.
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

		// �� �ɺ��� ������ ���� �ִ��� ã�´�.
		for each (CLine* line in lines)
		{
			// ���� �ִٸ�
			if (line->endSymbol == selectedSymbol)
			{
				line->startSymbol->nextSymbol = nullptr;

				// ���Ϳ��� ������ ���� ã�´�.
				std::vector<CLine*>::iterator lineIter = std::find(lines.begin(), lines.end(), line);

				line = nullptr;

				lines.erase(lineIter);

				break;
			}
		}
	
		// ���Ϳ��� ������ �ɺ��� ã�´�.
		std::vector<CSymbol*>::iterator symbolIter = std::find(symbols.begin(), symbols.end(), selectedSymbol);

		if (selectedSymbol->bVariableFlag)
		{
			// ���Ϳ��� ������ �ɺ��� ������ ã�´�.
			std::vector<FCVariable*>::iterator variableIter = std::find(variables.begin(), variables.end(), (*symbolIter)->variable);

			variables.erase(variableIter);
		}

		selectedSymbol = nullptr;

		symbols.erase(symbolIter);

		return TRUE;
	}

	return FALSE;
}
