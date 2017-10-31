#include "stdafx.h"
#include "Decision.h"


CDecision::CDecision()
{
}


CDecision::~CDecision()
{
}

VOID CDecision::DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag)
{
	// �ɺ� ���� ����
	if (selected)
		CShape::Rhombus(graphics, SELECTED_COLOR, TRUE, xPos - DECISION_XGAP, yPos - DECISION_YGAP, size.Width + DECISION_XGAP * 2, size.Height + (DECISION_YGAP * 2));

	// �ɺ� ����
	CShape::Rhombus(graphics, Gdiplus::Color(255, 255, 255, 255), TRUE, xPos, yPos, size.Width, size.Height);
	// �ɺ� �׵θ�
	CShape::Rhombus(graphics, Gdiplus::Color(255, 255, 248, 0), FALSE, xPos, yPos, size.Width, size.Height);
}

