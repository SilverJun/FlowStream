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
	// �ɺ� �浹 üũ �簢��
	CRect rect = CRect(
		position.X - scrollPosition.x,
		position.Y - scrollPosition.y,
		position.X + size.Width - scrollPosition.x,
		position.Y + size.Height - scrollPosition.y);

	// ���콺 Ŭ�� ��ġ�� �ɺ� ���̶��
	if (rect.PtInRect(mousePosition))
	{
		// �ɺ��� Ŭ���� ��ġ�� �����ϰ�, �̵� �� ���·� ��ȯ�Ѵ�. 
		clickPosition = Point(mousePosition.x - position.X, mousePosition.y - position.Y);

		bMove = TRUE;

		return TRUE;
	}

	return FALSE;
}

BOOL CSymbol::MouseMove(CPoint mousePosition)
{
	// �̵����̶��
	if (bMove)
	{
		// �ɺ��� Ŭ���� ��ġ�� �����ϸ鼭 �ɺ��� �̵���Ų��.
		position = Point(mousePosition.x - clickPosition.X, mousePosition.y - clickPosition.Y);
	
		return TRUE;
	}

	return FALSE;
}

BOOL CSymbol::LMouseUp(CPoint mousePosition)
{
	// �̵����̿��ٸ�
	if (bMove)
	{
		// �̵��� ������.
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

