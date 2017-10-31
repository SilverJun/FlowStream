#pragma once

#define SELECTED_COLOR	Gdiplus::Color(50, 0, 162, 232)

//===========================================
// CShape : GDI+ 로 그릴 도형을 편리하게 사용할 수 있게 클래스화.
class CShape
{
public:
	CShape();
	virtual ~CShape();

protected :
	//===========================================
	// Rectangle
	// 사각형을 그린다.
	// graphics : GDI+ 객체, color - 색깔
	// fill - 채워진 도형을 그릴지
	// xPos - X좌표, yPos - Y좌표
	// width - X크기, height - Y크기
	VOID	Rectangle(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height);
	//===========================================
	// RoofRectangle
	// 지붕모양의 사각형을 그린다.
	// graphics : GDI+ 객체, color - 색깔
	// fill - 채워진 도형을 그릴지, roof - 지붕모양의 방향
	// xPos - X좌표, yPos - Y좌표
	// width - X크기, height - Y크기
	// gap - 6각형의 각진 모서리의 거리
	VOID	RoofRectangle(Graphics* graphics, Color color, BOOL fill, BOOL roof, INT xPos, INT yPos, INT width, INT height, INT gap);
	//===========================================
	// RoundedRectangle
	// 둥근 모서리 사각형을 그린다.
	// graphics : GDI+ 객체, color - 색깔
	// fill - 채워진 도형을 그릴지
	// xPos - X좌표, yPos - Y좌표
	// width - X크기, height - Y크기
	// radius - 모서리 크기
	VOID	RoundedRectangle(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height, INT radius);
	//===========================================
	// Parallelogram
	// 평행사변형을 그린다.
	// graphics : GDI+ 객체, color - 색깔
	// fill - 채워진 도형을 그릴지
	// xPos - X좌표, yPos - Y좌표
	// width - X크기, height - Y크기
	VOID	Parallelogram(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height);
	//===========================================
	// Hexagon
	// 육각형을 그린다.
	// graphics : GDI+ 객체, color - 색깔
	// fill - 채워진 도형을 그릴지
	// xPos - X좌표, yPos - Y좌표
	// width - X크기, height - Y크기
	// gap - 6각형의 각진 모서리의 거리
	// edge - 테두리를 그리는가.
	VOID	Hexagon(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height, INT gap, BOOL edge = FALSE);
	//===========================================
	// Rhombus
	// 마름모를 그린다.
	// graphics : GDI+ 객체, color - 색깔
	// fill - 채워진 도형을 그릴지
	// xPos - X좌표, yPos - Y좌표
	// width - X크기, height - Y크기
	VOID	Rhombus(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height);
	//===========================================
	// Circle
	// 원을 그린다.
	// graphics : GDI+ 객체, color - 색깔
	// fill - 채워진 도형을 그릴지
	// xPos - X좌표, yPos - Y좌표
	// width - X크기, height - Y크기
	VOID	Circle(Graphics* graphics, Color color, BOOL fill, INT xPos, INT yPos, INT width, INT height);
public :
	//===========================================
	// DrawSymbol
	// 순수 가상 함수, 이 클래스를 상속받는 함수들이 필수로 구현해야 할 기호 그리기 함수.
	// graphics : GDI+ 객체
	// xPos - X좌표, yPos - Y좌표
	virtual VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE) = 0;
};

