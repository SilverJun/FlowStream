#pragma once

class CObjectFlow;
class Program;

//==============================================
// CFlowObject : 오브젝트 객체
class CFlowObject
{
public:
	CFlowObject();
	virtual ~CFlowObject();

public :
	// 좌표
	Point				position;
	// 크기
	Size					size;
	// 객체 이름
	CString			name;
	// 이미지
	Bitmap	*			image;
	// 선택됬는지
	BOOL				bSelected;

	// 클릭한 위치
	Point				clickPosition;
	// 이동 중인가
	BOOL				bMove;

	// 오브젝트의 흐름
	CObjectFlow*		objectFlow;

	// 오브젝트의 실행 루프
	Program*			program;
	// 실행 루프 플래그
	BOOL					programFlag;

public :
	// 초기화
	BOOL	Initialize(CString name);
	// 해제
	BOOL	Release();

	// 왼쪽 마우스 처리
	BOOL	LMouseDown(CPoint mousePosition);
	// 마우스가 이동 중 일 때
	BOOL	MouseMove(CPoint mousePosition);
	// 왼쪽 마우스	의 클릭이 완료되었을 때
	BOOL	LMouseUp(CPoint mousePosition);

	// 그리기 처리
	BOOL	Draw(Graphics*	graphics);

public :
	// 쓰레드 핸들
	HANDLE		threadHandle;
public :
	// 실제 루프
	VOID	PlayLoop();
	// 오브젝트 실행 쓰레드 함수
	VOID	PlayCallBack();
	// 루프를 강제로 종료
	VOID	PlayEnd();

	// 값 업데이트
	VOID	UpdateValue();
	

};

