#include "stdafx.h"
#include "FlowObject.h"
#include "Program.h"

#include "FlowStreamDoc.h"

unsigned WINAPI PlayThreadCallBack(void* arg)
{
	CFlowObject* flowObject = reinterpret_cast<CFlowObject*>(arg);

	flowObject->PlayCallBack();

	_endthread();

	return 0;
}

CFlowObject::CFlowObject()
{
}


CFlowObject::~CFlowObject()
{
}

BOOL CFlowObject::Initialize(CString name)
{
	position.X = 50;
	position.Y = 50;

	this->name = name;

	CMainFrame*	mainFrame = (CMainFrame*)AfxGetMainWnd();

	CFlowStreamDoc* pDoc = (CFlowStreamDoc*)mainFrame->GetActiveDocument();

	CString imageDirectory = pDoc->filePath;
	imageDirectory += "Resource\\";
	imageDirectory += name;
	imageDirectory += "\\Object.bmp";

	image = new Bitmap(imageDirectory);

	size.Width = image->GetWidth();
	size.Height = image->GetHeight();

	bSelected = FALSE;

	bMove = FALSE;

	program = new Program();

	programFlag = FALSE;

	threadHandle = nullptr;

	return TRUE;
}

BOOL	CFlowObject::Release()
{
	delete	image;
	delete	objectFlow;

	return TRUE;
}

BOOL CFlowObject::LMouseDown(CPoint mousePosition)
{
	CRect rect(position.X, position.Y, position.X + size.Width, position.Y + size.Height);

	if (rect.PtInRect(mousePosition))
	{
		// �ɺ��� Ŭ���� ��ġ�� �����ϰ�, �̵� �� ���·� ��ȯ�Ѵ�. 
		clickPosition = Point(mousePosition.x - position.X, mousePosition.y - position.Y);

		bMove = TRUE;

		return TRUE;
	}

	return FALSE;
}

BOOL CFlowObject::MouseMove(CPoint mousePosition)
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

BOOL CFlowObject::LMouseUp(CPoint mousePosition)
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

BOOL CFlowObject::Draw(Graphics* graphics)
{
	if (bSelected)
	{
		SolidBrush	solidBrush(SELECTED_COLOR);

		graphics->FillRectangle(&solidBrush, Rect(position.X - 10, position.Y - 10, size.Width + 20, size.Height + 20));
	}

	graphics->DrawImage(image, position);

	return TRUE;
}

VOID CFlowObject::PlayLoop()
{
	CMainFrame*	mainFrame = (CMainFrame*)AfxGetMainWnd();
	CFlowStreamDoc* pDoc = (CFlowStreamDoc*)mainFrame->GetActiveDocument();

	CT2CA objectName(name);

	std::string sourceFile;


	CT2CA convertedProjectName(pDoc->projectName);

	if (!(pDoc->projectName == ""))		//�󹮼� ó��.
	{
		CT2CA convertedPath = pDoc->filePath;
		sourceFile = convertedPath;
		sourceFile += "Resource\\";
	}
	else
	{
		sourceFile = "Resource\\";
	}

	sourceFile += objectName;
	sourceFile += "\\";
	sourceFile += objectName;
	sourceFile += ".txt";

	program->SetCodeFile(sourceFile);
	program->Init();

	programFlag = TRUE;

	// ������ ����
	threadHandle = (HANDLE)_beginthreadex(NULL, 0, PlayThreadCallBack, this, 0, NULL);

}

VOID CFlowObject::PlayCallBack()
{
	program->Run();

	programFlag = FALSE;
}

VOID CFlowObject::PlayEnd()
{
	program->Stop();

	UpdateValue();

	CMainFrame*		mainFrame = (CMainFrame*)AfxGetMainWnd();
	mainFrame->play->Invalidate();

	program->DeleteCode();

	program->Release();

	programFlag = FALSE;
}

VOID CFlowObject::UpdateValue()
{
	CMainFrame*		mainFrame = (CMainFrame*)AfxGetMainWnd();

	for each (FCVariable* variable in objectFlow->variables)
	{
		CT2CA		variableName(variable->name);
		std::string	sName = variableName;

		if (!programFlag)
			return;

		if (variable->type == eFCVariableType::eVariableType_INT)
		{
			if (variable->intValue != nullptr)
			{
				(*variable->intValue) = program->GetVM()->GetSymbolTable()->GetValue(sName).intValue;

				variable->value.Format(_T("%d"), *variable->intValue);
			}
			else
			{
				variable->intValue = (INT*)&(program->GetVM()->GetSymbolTable()->GetValue(sName));
			}
		}
		else if (variable->type == eFCVariableType::eVariableType_FLOAT)
		{
			if (variable->floatValue != nullptr)
			{
				(*variable->floatValue) = program->GetVM()->GetSymbolTable()->GetValue(sName).floatValue;

				variable->value.Format(_T("%f"), *variable->floatValue);
			}
			else
			{
				variable->floatValue = (FLOAT*)&(program->GetVM()->GetSymbolTable()->GetValue(sName));
			}
		}
		else if (variable->type == eFCVariableType::eVariableType_STRING)
		{
			if (variable->stringValue != nullptr)
			{
				variable->stringValue = program->GetVM()->GetSymbolTable()->GetValue(sName).stringValue;

				std::string tempString(*variable->stringValue);

				variable->value = CString(tempString.c_str());
			}
			else
			{
				variable->stringValue = (std::string*)&(program->GetVM()->GetSymbolTable()->GetValue(sName));
			}
		}
	}
}