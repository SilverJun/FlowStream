#pragma once

#define SELECTED_COLOR	Gdiplus::Color(50, 0, 162, 232)

//===========================================
// CShape : GDI+ �� �׸� ������ ���ϰ� ����� �� �ְ� Ŭ����ȭ.
class CShape
{
public:
	CShape();
	virtual ~CShape();

protected :
	//===========================================
	// Rectangle
	// �簢���� �׸���.
	// graphics : GDI+ ��ü, color - ����
	// fill - ä���� ������ �׸���
	// xPos - X��ǥ, yPos - Y��ǥ
	// width - Xũ��, height - Yũ��
	VOID	Rectangle(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height);
	//===========================================
	// RoofRectangle
	// ���ظ���� �簢���� �׸���.
	// graphics : GDI+ ��ü, color - ����
	// fill - ä���� ������ �׸���, roof - ���ظ���� ����
	// xPos - X��ǥ, yPos - Y��ǥ
	// width - Xũ��, height - Yũ��
	// gap - 6������ ���� �𼭸��� �Ÿ�
	VOID	RoofRectangle(Graphics* graphics, Color color, BOOL fill, BOOL roof, INT xPos, INT yPos, INT width, INT height, INT gap);
	//===========================================
	// RoundedRectangle
	// �ձ� �𼭸� �簢���� �׸���.
	// graphics : GDI+ ��ü, color - ����
	// fill - ä���� ������ �׸���
	// xPos - X��ǥ, yPos - Y��ǥ
	// width - Xũ��, height - Yũ��
	// radius - �𼭸� ũ��
	VOID	RoundedRectangle(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height, INT radius);
	//===========================================
	// Parallelogram
	// ����纯���� �׸���.
	// graphics : GDI+ ��ü, color - ����
	// fill - ä���� ������ �׸���
	// xPos - X��ǥ, yPos - Y��ǥ
	// width - Xũ��, height - Yũ��
	VOID	Parallelogram(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height);
	//===========================================
	// Hexagon
	// �������� �׸���.
	// graphics : GDI+ ��ü, color - ����
	// fill - ä���� ������ �׸���
	// xPos - X��ǥ, yPos - Y��ǥ
	// width - Xũ��, height - Yũ��
	// gap - 6������ ���� �𼭸��� �Ÿ�
	// edge - �׵θ��� �׸��°�.
	VOID	Hexagon(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height, INT gap, BOOL edge = FALSE);
	//===========================================
	// Rhombus
	// ������ �׸���.
	// graphics : GDI+ ��ü, color - ����
	// fill - ä���� ������ �׸���
	// xPos - X��ǥ, yPos - Y��ǥ
	// width - Xũ��, height - Yũ��
	VOID	Rhombus(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height);
	//===========================================
	// Circle
	// ���� �׸���.
	// graphics : GDI+ ��ü, color - ����
	// fill - ä���� ������ �׸���
	// xPos - X��ǥ, yPos - Y��ǥ
	// width - Xũ��, height - Yũ��
	VOID	Circle(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height);
public :
	//===========================================
	// DrawSymbol
	// ���� ���� �Լ�, �� Ŭ������ ��ӹ޴� �Լ����� �ʼ��� �����ؾ� �� ��ȣ �׸��� �Լ�.
	// graphics : GDI+ ��ü
	// xPos - X��ǥ, yPos - Y��ǥ
	virtual VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE) = 0;
};

