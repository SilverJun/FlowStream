#pragma once

class CObjectFlow;
class Program;

//==============================================
// CFlowObject : ������Ʈ ��ü
class CFlowObject
{
public:
	CFlowObject();
	virtual ~CFlowObject();

public :
	// ��ǥ
	Point				position;
	// ũ��
	Size					size;
	// ��ü �̸�
	CString			name;
	// �̹���
	Bitmap	*			image;
	// ���É����
	BOOL				bSelected;

	// Ŭ���� ��ġ
	Point				clickPosition;
	// �̵� ���ΰ�
	BOOL				bMove;

	// ������Ʈ�� �帧
	CObjectFlow*		objectFlow;

	// ������Ʈ�� ���� ����
	Program*			program;
	// ���� ���� �÷���
	BOOL					programFlag;

public :
	// �ʱ�ȭ
	BOOL	Initialize(CString name);
	// ����
	BOOL	Release();

	// ���� ���콺 ó��
	BOOL	LMouseDown(CPoint mousePosition);
	// ���콺�� �̵� �� �� ��
	BOOL	MouseMove(CPoint mousePosition);
	// ���� ���콺	�� Ŭ���� �Ϸ�Ǿ��� ��
	BOOL	LMouseUp(CPoint mousePosition);

	// �׸��� ó��
	BOOL	Draw(Graphics*	graphics);

public :
	// ������ �ڵ�
	HANDLE		threadHandle;
public :
	// ���� ����
	VOID	PlayLoop();
	// ������Ʈ ���� ������ �Լ�
	VOID	PlayCallBack();
	// ������ ������ ����
	VOID	PlayEnd();

	// �� ������Ʈ
	VOID	UpdateValue();
	

};

