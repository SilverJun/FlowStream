#include "stdafx.h"
#include "Symbol.h"

CSymbol::CSymbol()
{
	bMove = FALSE;
	bSelected = FALSE;
	bSymbolFlag = FALSE;
	bVariableFlag = FALSE;

	nextSymbol = nullptr;
	trueSymbol = nullptr;
	falseSymbol = nullptr;
	variable = nullptr;
}


CSymbol::~CSymbol()
{
}

BOOL	CSymbol::LMouseDown(CPoint mousePosition, CPoint scrollPosition)
{
	// 심볼 충돌 체크 사각형
	CRect rect = CRect(
		position.X - scrollPosition.x,
		position.Y - scrollPosition.y,
		position.X + size.Width - scrollPosition.x,
		position.Y + size.Height - scrollPosition.y);

	// 마우스 클릭 위치가 심볼 안이라면
	if (rect.PtInRect(mousePosition))
	{
		// 심볼을 클릭한 위치를 지정하고, 이동 중 상태로 전환한다. 
		clickPosition = Point(mousePosition.x - position.X, mousePosition.y - position.Y);

		bMove = TRUE;

		return TRUE;
	}

	return FALSE;
}

BOOL CSymbol::MouseMove(CPoint mousePosition)
{
	// 이동중이라면
	if (bMove)
	{
		// 심볼을 클릭한 위치를 보정하면서 심볼을 이동시킨다.
		position = Point(mousePosition.x - clickPosition.X, mousePosition.y - clickPosition.Y);
	
		return TRUE;
	}

	return FALSE;
}

BOOL CSymbol::LMouseUp(CPoint mousePosition)
{
	// 이동중이였다면
	if (bMove)
	{
		// 이동을 끝낸다.
		bMove = FALSE;
	
		return TRUE;
	}

	return FALSE;
}

BOOL CSymbol::ResizeSymbol()
{
	INT xSize = label.GetLength() * LABEL_SIZE / 2 + 40;
	INT ySize = ((xSize / 4) * 3) / 2;

	if (xSize <= SYMBOL_XSIZE)
		xSize = SYMBOL_XSIZE;

	size.Width = xSize;
	size.Height = ySize;

	return TRUE;
}

BOOL CSymbol::DrawLabel(Graphics* graphics, CPoint scrollPosition)
{
	Gdiplus::Font font(_T("Arial"), LABEL_SIZE, FontStyleBold, UnitPixel);
	SolidBrush	textBrush(Color::Black);

	//FLOAT	xPos = position.X + (size.Width / label.GetLength()) - (LABEL_SIZE / 4);
	FLOAT	xPos = position.X + (size.Width / 2) - ((LABEL_SIZE / 3) * label.GetLength());
	FLOAT	yPos = position.Y + (size.Height / 2) - (LABEL_SIZE / 2);

	graphics->DrawString(label, -1, &font, PointF(xPos - scrollPosition.x, yPos - scrollPosition.y), &textBrush);

	return TRUE;
}

