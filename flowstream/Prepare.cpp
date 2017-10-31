#include "stdafx.h"
#include "Prepare.h"


CPrepare::CPrepare()
{
}


CPrepare::~CPrepare()
{
}

VOID CPrepare::DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag)
{
	// �ɺ� ���� ����
	if (selected)
		CShape::Hexagon(graphics, SELECTED_COLOR, TRUE, xPos - (PREPARE_XGAP), yPos - (PREPARE_YGAP), size.Width + (PREPARE_XGAP * 2), size.Height + (PREPARE_YGAP * 2), (size.Width + PREPARE_XGAP * 2) / 4, TRUE);

	// �ɺ� ����
	CShape::Hexagon(graphics, Gdiplus::Color(255, 255, 255, 255), TRUE, xPos, yPos, size.Width, size.Height, size.Width / 4);
	// �ɺ� �׵θ�
	CShape::Hexagon(graphics, Gdiplus::Color(255, 81, 143, 246), FALSE, xPos, yPos, size.Width, size.Height, size.Width / 4);
}
