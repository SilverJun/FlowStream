#include "stdafx.h"
#include "Line.h"

CLine::CLine()
{
	startSymbol = nullptr;
	endSymbol = nullptr;
	bSelected = FALSE;
	bFlag = FALSE;
}


CLine::~CLine()
{
}

BOOL	CLine::LMouseDown(CPoint mousePosition, CPoint scrollPosition)
{
	// 위치에 따른 Rect값 수정

	FLOAT startX;
	FLOAT startY;
	FLOAT endX;
	FLOAT endY;

	if (startSymbol->position.X < endSymbol->position.X || startSymbol->position.X == endSymbol->position.X)
	{
		startX = startSymbol->position.X + startSymbol->size.Width / 2;
		endX = endSymbol->position.X + endSymbol->size.Width / 2 + 10;
	}
	else
	{
		startX = endSymbol->position.X + endSymbol->size.Width / 2;
		endX = startSymbol->position.X + startSymbol->size.Width / 2 + 10;
	}

	if (startSymbol->position.Y < endSymbol->position.Y || startSymbol->position.Y == endSymbol->position.Y)
	{
		startY = startSymbol->position.Y + startSymbol->size.Height;
		endY = endSymbol->position.Y + 10;
	}
	else
	{
		startY = endSymbol->position.Y + 10;
		endY = startSymbol->position.Y + startSymbol->size.Height;
	}

	// 선 충돌 체크 사각형
	CRect rect = CRect(startX - scrollPosition.x, startY - scrollPosition.y, endX - scrollPosition.x, endY - scrollPosition.y);

	// 마우스 클릭 위치가 선 안이라면
	if (rect.PtInRect(mousePosition))
		return TRUE;
	

	return FALSE;
}

BOOL CLine::MouseMove(CPoint mousePosition)
{

	return FALSE;
}

BOOL CLine::LMouseUp(CPoint mousePosition)
{

	return FALSE;
}

VOID CLine::Draw(Graphics* graphics, CPoint scrollPosition, BOOL flag)
{
	Pen selectedPen(SELECTED_COLOR, PEN_SIZE + 7.5F);
	Pen pen(color, PEN_SIZE);
	Point startPos;
	Point endPos;

	// IF문 처리
	if (startSymbol->bSymbolFlag)
	{
		if (bFlag)
		{
			startPos = Point(startSymbol->position.X - scrollPosition.x, startSymbol->position.Y + startSymbol->size.Height / 2 - scrollPosition.y);
		}
		else
		{
			startPos = Point(startSymbol->position.X + startSymbol->size.Width - scrollPosition.x, startSymbol->position.Y + startSymbol->size.Height / 2 - scrollPosition.y);
		}

		endPos = Point(endSymbol->position.X + endSymbol->size.Width / 2 - scrollPosition.x, endSymbol->position.Y - scrollPosition.y);
	}
	else
	{
		startPos = Point(startSymbol->position.X + startSymbol->size.Width / 2 - scrollPosition.x, startSymbol->position.Y + startSymbol->size.Height - scrollPosition.y);
		endPos = Point(endSymbol->position.X + endSymbol->size.Width / 2 - scrollPosition.x, endSymbol->position.Y - scrollPosition.y);
	}


	//selectedPen.SetEndCap(LineCapArrowAnchor);
	pen.SetEndCap(LineCapArrowAnchor);

	if (bSelected)
		graphics->DrawLine(&selectedPen,
			startPos,
			endPos);

	graphics->DrawLine(&pen,
		startPos,
		endPos);
}