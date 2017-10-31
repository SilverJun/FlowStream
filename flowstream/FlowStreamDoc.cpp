
// FlowStreamDoc.cpp : CFlowStreamDoc Ŭ������ ����
//

#include "stdAFX.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "FlowStream.h"
#endif

#include "FlowStreamDoc.h"

#include <propkey.h>

#include "ListObject.h"
#include "FlowObject.h"

#include "FCIf.h"
#include "FCSet.h"
#include "FCWhileStart.h"
#include "FCCreate.h"
#include "FCPrint.h"
#include "FCInput.h"
#include "FCOutput.h"

typedef rapidjson::GenericValue<rapidjson::UTF16LE<wchar_t>, rapidjson::MemoryPoolAllocator<>> wValue;

//ObjectListView ���� ���� �̹��� ���� ��ü.
extern CImageList imageList;

using namespace rapidjson;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFlowStreamDoc

IMPLEMENT_DYNCREATE(CFlowStreamDoc, CDocument)

BEGIN_MESSAGE_MAP(CFlowStreamDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, &CFlowStreamDoc::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CFlowStreamDoc::OnFileSaveAs)
END_MESSAGE_MAP()

//���ڿ��� �������� �Ǻ�. �Ҽ������� �߰��� �Ǻ�.
bool stringIsNumber(CString& value, bool& bIsFloat)
{
	std::wstring temp = value;
	for each(wchar_t n in temp)
	{
		if (!isdigit(n))
		{
			if (n == '.')
				bIsFloat = true;
			else
				return false;
		}
	}
	return true;
};


// CFlowStreamDoc ����/�Ҹ�

CFlowStreamDoc::CFlowStreamDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	projectDoc = NULL;

}


CFlowStreamDoc::~CFlowStreamDoc()
{
}

BOOL CFlowStreamDoc::NewProjectFile(LPCTSTR path)
{
	//������Ʈ ����.
	projectDoc = rapidjson::GenericDocument<rapidjson::UTF16LE<wchar_t> >();
	CFile::CFile(path + CString(_T("\\Project.json")), CFile::modeCreate);
	CT2CA convertedpath(path);
	std::string resourceFolder = convertedpath + "\\Resource";
	mkdir(resourceFolder.c_str());
	this->filePath = CString(path + CString(_T("\\")));

	CMainFrame*	mainFrame = (CMainFrame*)AfxGetMainWnd();
	mainFrame->SetWindowText(projectName);
	
	return TRUE;
}

BOOL CFlowStreamDoc::SaveProjectFile(LPCTSTR path)
{
	CMainFrame*	mainFrame = (CMainFrame*)AfxGetMainWnd();

	rapidjson::GenericDocument<rapidjson::UTF16LE<wchar_t> > newDoc;
	
	Document::AllocatorType& allocator = newDoc.GetAllocator();

	//root ����.
	wValue root(kObjectType);
	root.SetObject();

	//projectName ����.
	wValue ProjName(kStringType);
	std::wstring projname = this->projectName;
	ProjName.SetString(StringRef(projname.c_str()), allocator);
	root.AddMember(wValue(_T("ProjectName")), ProjName, allocator);

	wValue Objects(kArrayType);

	for (int i = 0; i < mainFrame->objectList->objects.size(); i++)
	{
		wValue thisObject(kObjectType);
		thisObject.SetObject();
		
		wValue ObjectName(kStringType);
		wValue x(kNumberType), y(kNumberType), width(kNumberType), height(kNumberType);

		ObjectName.SetString(mainFrame->objectList->objects[i]->name, allocator);
		x = mainFrame->play->objects[i]->position.X;
		y = mainFrame->play->objects[i]->position.X;
		width = mainFrame->play->objects[i]->size.Width;
		height = mainFrame->play->objects[i]->size.Height;

		thisObject.AddMember(wValue(_T("ObjectName")), ObjectName, allocator);
		thisObject.AddMember(wValue(_T("x")), x, allocator);
		thisObject.AddMember(wValue(_T("y")), y, allocator);
		thisObject.AddMember(wValue(_T("width")), width, allocator);
		thisObject.AddMember(wValue(_T("height")), height, allocator);

		wValue Symbols(kArrayType);

		CObjectFlow* thisObjectFlow = mainFrame->objectFlow->objectFlows[i];

		for (auto itor = thisObjectFlow->symbols.begin(); itor != thisObjectFlow->symbols.end(); itor++)
		{
			wValue thisSymbol(kObjectType);
			
			wValue symbolX(kNumberType), symbolY(kNumberType), type(kStringType);
			wValue DataObject(kObjectType);
			wValue Line(kObjectType), LineType(kTrueType), LineXPos(kNumberType), LineYPos(kNumberType);
			
			//��ǥ
			symbolX = (*itor)->position.X;
			symbolY = (*itor)->position.Y;
			
			thisSymbol.AddMember(wValue(_T("x")), symbolX, allocator);
			thisSymbol.AddMember(wValue(_T("y")), symbolY, allocator);

			//Ÿ��, ������
			if (typeid(*(*itor)) == typeid(CFCStart))
			{
				type = _T("Start");
				thisSymbol.AddMember(wValue(_T("Type")), type, allocator);

			}
			else if (typeid(*(*itor)) == typeid(CFCEnd))
			{
				type = _T("End");
				thisSymbol.AddMember(wValue(_T("Type")), type, allocator);
			}
			else if (typeid(*(*itor)) == typeid(CFCCreate))
			{
				type = _T("Create");
				thisSymbol.AddMember(wValue(_T("Type")), type, allocator);

				wValue DataType(kStringType), Name(kStringType);

				auto dlg = dynamic_cast<CCreateVariable*>((*itor)->dialog);

				DataType.SetString(dlg->type, allocator);
				Name.SetString(dlg->name, allocator);

				DataObject.AddMember(wValue(_T("DataType")), DataType, allocator);
				DataObject.AddMember(wValue(_T("Name")), Name, allocator);

				thisSymbol.AddMember(wValue(_T("Data")), DataObject, allocator);
			}
			else if (typeid(*(*itor)) == typeid(CFCSet))
			{
				type = _T("Set");
				thisSymbol.AddMember(wValue(_T("Type")), type, allocator);

				wValue Variable(kStringType), Operator(kStringType), Value;

				auto dlg = dynamic_cast<CAllocation*>((*itor)->dialog);

				Variable.SetString(dlg->variableName, allocator);
				Operator.SetString(dlg->allocationOperator, allocator);
				Value.SetString(dlg->allocationValue, allocator);
				
				DataObject.AddMember(wValue(_T("Variable")), Variable, allocator);
				DataObject.AddMember(wValue(_T("Operator")), Operator, allocator);
				DataObject.AddMember(wValue(_T("Value")), Value, allocator);

				thisSymbol.AddMember(wValue(_T("Data")), DataObject, allocator);
			}
			else if (typeid(*(*itor)) == typeid(CFCOutput))
			{
				type = _T("Output");
				thisSymbol.AddMember(wValue(_T("Type")), type, allocator);

				wValue Expression(kStringType);

				auto dlg = dynamic_cast<CDataOutput*>((*itor)->dialog);

				Expression.SetString(dlg->ExpressionText, allocator);

				DataObject.AddMember(wValue(_T("Exp")), Expression, allocator);

				thisSymbol.AddMember(wValue(_T("Data")), DataObject, allocator);
			}
			else if (typeid(*(*itor)) == typeid(CFCInput))
			{
				type = _T("Input");
				thisSymbol.AddMember(wValue(_T("Type")), type, allocator);

				wValue Variable(kStringType);

				auto dlg = dynamic_cast<CDataInput*>((*itor)->dialog);

				Variable.SetString(dlg->VariableName, allocator);

				DataObject.AddMember(wValue(_T("Variable")), Variable, allocator);

				thisSymbol.AddMember(wValue(_T("Data")), DataObject, allocator);
			}
			else if (typeid(*(*itor)) == typeid(CFCIf))
			{
				type = _T("If");
				thisSymbol.AddMember(wValue(_T("Type")), type, allocator);
				
				wValue Variable(kStringType), Operator(kStringType), Value(kStringType);

				auto dlg = dynamic_cast<CConditionCheck*>((*itor)->dialog);

				CString s = (dlg->firstCheck) ? dlg->firstVariable : dlg->firstValue;
				Variable.SetString(s, allocator);
				Operator.SetString(dlg->compareOperator, allocator);
				s = (dlg->secondCheck) ? dlg->secondVariable : dlg->secondValue;
				Value.SetString(s, allocator);

				DataObject.AddMember(wValue(_T("IsExp1")), wValue((bool)dlg->firstCheck).GetBool(), allocator);
				DataObject.AddMember(wValue(_T("Variable")), Variable, allocator);
				DataObject.AddMember(wValue(_T("Operator")), Operator, allocator);
				DataObject.AddMember(wValue(_T("IsExp2")), wValue((bool)dlg->secondCheck).GetBool(), allocator);
				DataObject.AddMember(wValue(_T("Value")), Value, allocator);

				thisSymbol.AddMember(wValue(_T("Data")), DataObject, allocator);
			}
			else if (typeid(*(*itor)) == typeid(CFCIfEnd))
			{
				type = _T("IfEnd");
				thisSymbol.AddMember(wValue(_T("Type")), type, allocator);
			}
			else if (typeid(*(*itor)) == typeid(CFCWhileStart))
			{
				type = _T("While");
				thisSymbol.AddMember(wValue(_T("Type")), type, allocator);

				wValue Variable(kStringType), Operator(kStringType), Value(kStringType);

				auto dlg = dynamic_cast<CConditionCheck*>((*itor)->dialog);

				Variable.SetString((dlg->firstCheck) ? dlg->firstVariable : dlg->firstValue, allocator);
				Operator.SetString(dlg->compareOperator, allocator);
				Value.SetString((dlg->secondCheck) ? dlg->secondVariable : dlg->secondValue, allocator);

				DataObject.AddMember(wValue(_T("IsExp1")), wValue((bool)dlg->firstCheck), allocator);
				DataObject.AddMember(wValue(_T("Variable")), Variable, allocator);
				DataObject.AddMember(wValue(_T("Operator")), Operator, allocator);
				DataObject.AddMember(wValue(_T("IsExp2")), wValue((bool)dlg->secondCheck), allocator);
				DataObject.AddMember(wValue(_T("Value")), Value, allocator);

				thisSymbol.AddMember(wValue(_T("Data")), DataObject, allocator);
			}
			else if (typeid(*(*itor)) == typeid(CFCWhileEnd))
			{
				type = _T("WhileEnd");
				thisSymbol.AddMember(wValue(_T("Type")), type, allocator);
			}


			//����
			if (thisSymbol[_T("Type")].GetString() == _T("If"))
			{
				wValue TrueLine(kTrueType), FalseLine(kTrueType), LineTrueXPos(kNumberType), LineTrueYPos(kNumberType), LineFalseXPos(kNumberType), LineFalseYPos(kNumberType);
				bool t = ((*itor)->trueSymbol != nullptr) ? true : false, f = ((*itor)->falseSymbol != nullptr) ? true : false;
				TrueLine = t;
				FalseLine = f;

				LineTrueXPos = t ? (*itor)->trueSymbol->position.X : -1;
				LineTrueYPos = t ? (*itor)->trueSymbol->position.Y : -1;
				LineFalseXPos = f ? (*itor)->falseSymbol->position.X : -1;
				LineFalseYPos = f ? (*itor)->falseSymbol->position.Y : -1;

				Line.AddMember(wValue(_T("TrueLine")), TrueLine, allocator);
				Line.AddMember(wValue(_T("FalseLine")), FalseLine, allocator);

				Line.AddMember(wValue(_T("LinkTrueXPos")), LineTrueXPos, allocator);
				Line.AddMember(wValue(_T("LinkTrueYPos")), LineTrueYPos, allocator);
				Line.AddMember(wValue(_T("LinkFalseXPos")), LineFalseXPos, allocator);
				Line.AddMember(wValue(_T("LinkFalseYPos")), LineFalseYPos, allocator);

				thisSymbol.AddMember(wValue(_T("Line")), Line, allocator);
			}
			else
			{
				bool b = ((*itor)->nextSymbol != nullptr) ? true : false;
				LineType = b;
				LineXPos = LineType.GetBool() ? (*itor)->nextSymbol->position.X : -1;
				LineYPos = LineType.GetBool() ? (*itor)->nextSymbol->position.Y : -1;

				Line.AddMember(wValue(_T("LineType")), LineType, allocator);
				Line.AddMember(wValue(_T("LinkXPos")), LineXPos, allocator);
				Line.AddMember(wValue(_T("LinkYPos")), LineYPos, allocator);
				thisSymbol.AddMember(wValue(_T("Line")), Line, allocator);
			}

			//�������� �ϳ��� �ɺ��� �ϼ�
			Symbols.PushBack(thisSymbol, allocator);
		}
		
		thisObject.AddMember(wValue(_T("Symbols")), Symbols, allocator);
		Objects.PushBack(thisObject, allocator);
	}

	root.AddMember(wValue(_T("Objects")), Objects, allocator);

	//root ������Ʈ�� DOM�� ����.
	newDoc.CopyFrom(root, allocator);

	//��������.
	FILE* fp = _wfopen(path, _T("wb"));
	char writeBuffer[65536];

	FileWriteStream os(fp, writeBuffer, _countof(writeBuffer));
	EncodedOutputStream<UTF16LE<>, FileWriteStream> encodedOS(os);
	PrettyWriter<EncodedOutputStream<UTF16LE<>, FileWriteStream>, rapidjson::UTF16LE<>, rapidjson::UTF16LE<>, MemoryPoolAllocator<>> writer(encodedOS);
	newDoc.Accept(writer);

	projectDoc.CopyFrom(newDoc, allocator);
	fclose(fp);

	//���ҽ� ����.
	CString targetFolderPath = path;
	targetFolderPath.TrimRight(_T("Project.json"));
	for (int i = 0; i < mainFrame->objectList->objects.size(); i++)
	{
		//������ ������ 4��.
		//������Ʈ�̸�.bmp		- ���� �̹���.
		//������Ʈ�̸�.txt		- ���������� �ڵ�.
		//object.bmp			- �÷��̺信�� ���� �̹���
		//resize������Ʈ�̸�.bmp - ����Ʈ�信�� ���� �̹���. 50*50���� ����.
		CT2CA convertedFolder(targetFolderPath + _T("Resource\\") + mainFrame->objectList->objects[i]->name);
		std::string folder = convertedFolder;
		if (mkdir(folder.c_str()) == 0)
		{
			std::wstring sourceFilePath[4] = {
				this->filePath + _T("Resource\\") + mainFrame->objectList->objects[i]->name + _T("\\") + _T("object.bmp"),
				this->filePath + _T("Resource\\") + mainFrame->objectList->objects[i]->name + _T("\\") + mainFrame->objectList->objects[i]->name + _T(".txt"),
				this->filePath + _T("Resource\\") + mainFrame->objectList->objects[i]->name + _T("\\") + mainFrame->objectList->objects[i]->name + _T(".bmp"),
				this->filePath + _T("Resource\\") + mainFrame->objectList->objects[i]->name + _T("\\") + _T("resize") + mainFrame->objectList->objects[i]->name + _T(".bmp")
			}, targetFilePath[4] = {
				targetFolderPath + _T("Resource\\") + mainFrame->objectList->objects[i]->name + _T("\\") + _T("object.bmp"),
				targetFolderPath + _T("Resource\\") + mainFrame->objectList->objects[i]->name + _T("\\") + mainFrame->objectList->objects[i]->name + _T(".txt"),
				targetFolderPath + _T("Resource\\") + mainFrame->objectList->objects[i]->name + _T("\\") + mainFrame->objectList->objects[i]->name + _T(".bmp"),
				targetFolderPath + _T("Resource\\") + mainFrame->objectList->objects[i]->name + _T("\\") + _T("resize") + mainFrame->objectList->objects[i]->name + _T(".bmp")
			};
			for (int j = 0; j < 4; j++)
			{
				std::ifstream fileSource[4];
				std::ofstream fileTarget[4];

				fileSource[j] = std::ifstream(sourceFilePath[j], std::ios::in | std::ios::binary);
				fileTarget[j] = std::ofstream(targetFilePath[j], std::ios::out | std::ios::binary);

				if (fileSource[j].fail())
				{
					AfxMessageBox(_T("���� ���� ���� ����!"));
					return FALSE;
				}

				//���� ������ ���.
				std::streamoff size;
				fileSource[j].seekg(0, std::ios::end);
				size = fileSource[j].tellg();
				fileSource[j].seekg(0, std::ios::beg);
				fileSource[j].clear();

				//���� ����.
				char* buf = new char[size];
				fileSource[j].read(buf, size);
				fileTarget[j].write(buf, size);
				delete[] buf;

				fileTarget[j].close();
				fileSource[j].close();
			}
		}
	}

	return TRUE;
}

BOOL CFlowStreamDoc::LoadProjectFile(LPCTSTR path)
{
	FILE* projectFile = _wfopen(path, _T("rb")); // non-Windows use "r"

	filePath = path;

	filePath.TrimRight(_T("Project.json"));

	if (!projectFile)
	{
		AfxMessageBox(_T("Error : FileOpenError!"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	
	char readBuffer[65536];
	FileReadStream is(projectFile, readBuffer, sizeof(readBuffer));
	
	EncodedInputStream<UTF16LE<>, FileReadStream> encodedIS(is);

	projectDoc.ParseStream<0, UTF16LE<> >(encodedIS);

	fclose(projectFile);

	
	if (projectDoc.HasParseError())
	{
		std::string error = "Error(offset " + std::to_string((unsigned)projectDoc.GetErrorOffset()) + ") : " + GetParseError_En((ParseErrorCode)projectDoc.GetParseError());

		std::wstring error_w;
		//string -> wstring
		error_w.assign(error.begin(), error.end());

		std::wstring errorMessage = _T("rapidJson Parse Error : ") + error_w;
		AfxMessageBox(errorMessage.c_str(), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//������Ʈ json�ҷ����� �Ϸ�.

	if (!projectDoc.HasMember(_T("ProjectName")))
	{
		AfxMessageBox(_T("json���Ͽ� ������Ʈ ���� ���� �����ϴ�."), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	projectName = projectDoc[_T("ProjectName")].GetString();

	CMainFrame*	mainFrame = (CMainFrame*)AfxGetMainWnd();
	mainFrame->SetWindowText(projectName);

	CreateSymbols();
	
	return TRUE;
}

VOID CFlowStreamDoc::CreateSymbols()
{
	CMainFrame*	mainFrame = (CMainFrame*)AfxGetMainWnd();
	CListCtrl& list = mainFrame->objectList->GetListCtrl();
	
	CClientDC dc(mainFrame->objectList);
	
	auto Objects = projectDoc[_T("Objects")].GetArray();

	std::vector<std::tuple<eLineType, Point, Point>> vLinkLinePos;

	for (SizeType i = 0; i < Objects.Size(); i++)
	{
		if (!Objects[i].IsObject())
			return;

		auto& thisObject = Objects[i].GetObjectW();
		CString objName = thisObject[_T("ObjectName")].GetString();
		
		CListObject* newObject = new CListObject();

		CString imagefilePath = filePath;
		imagefilePath += _T("Resource\\");
		imagefilePath += objName;
		newObject->LoadImage(objName, imagefilePath, thisObject[_T("width")].GetInt(), thisObject[_T("height")].GetInt());
		
		// ������Ʈ ����
		CFlowObject*	flowobject = new CFlowObject();
		CObjectFlowView* objFlowView = mainFrame->objectFlow;
		flowobject->Initialize(objName);

		//�ɺ�ó��
		flowobject->objectFlow = new CObjectFlow();

		auto& symbols = thisObject[_T("Symbols")].GetArray();

		//���� ���� ������Ʈ�� ����.
		objFlowView->selectedObjectFlow = flowobject->objectFlow;

		CSymbol*	start = nullptr;
		CSymbol*	end = nullptr;
		CSymbol*	nowSymbol = nullptr;

		bool LineType = false;
		
		for (SizeType j = 0; j < symbols.Size(); j++)
		{
			CString	dataLabel;
			if (!symbols[j].IsObject())
				return;

			auto& symbol = symbols[j].GetObjectW();
			Point pos = { symbol[_T("x")].GetInt() , symbol[_T("y")].GetInt() };

			//�ɺ������� ó��
			std::wstring type = symbol[_T("Type")].GetString();

			if (type == _T("Start"))
			{
				if (start != nullptr)
					AfxMessageBox(_T("Start��ȣ�� 2�� �̻� �����մϴ�."));
				else
					start = objFlowView->CreateSymbolStart(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));
			}
			else if (type == _T("End"))
			{
				if (end != nullptr)
					AfxMessageBox(_T("End��ȣ�� 2�� �̻� �����մϴ�."));
				else
					end = objFlowView->CreateSymbolEnd(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));
			}
			else if (type == _T("Create"))
			{
				objFlowView->CreateSymbolCreate(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));

				nowSymbol = objFlowView->selectedObjectFlow->symbols.back();

				auto dlg = dynamic_cast<CCreateVariable*>(nowSymbol->dialog);

				auto& data = symbol[_T("Data")].GetObjectW();

				dataLabel = dlg->type = data[_T("DataType")].GetString();
				dataLabel += " ";
				dataLabel += dlg->name = data[_T("Name")].GetString();

				nowSymbol->label = dataLabel;
				nowSymbol->ResizeSymbol();
			}
			else if (type == _T("Output"))
			{
				objFlowView->CreateSymbolOutput(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));

				nowSymbol = objFlowView->selectedObjectFlow->symbols.back();

				auto dlg = dynamic_cast<CDataOutput*>(nowSymbol->dialog);

				auto& data = symbol[_T("Data")].GetObjectW();

				dataLabel = _T("output");
				dataLabel += " ";
				dataLabel += data[_T("Exp")].GetString();

				dlg->ExpressionText = data[_T("Exp")].GetString();

				nowSymbol->label = dataLabel;
				nowSymbol->ResizeSymbol();
			}
			else if (type == _T("Input"))
			{
				objFlowView->CreateSymbolInput(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));

				nowSymbol = objFlowView->selectedObjectFlow->symbols.back();

				auto dlg = dynamic_cast<CDataInput*>(nowSymbol->dialog);

				auto& data = symbol[_T("Data")].GetObjectW();

				dataLabel = _T("input");
				dataLabel += " ";
				dataLabel += data[_T("Variable")].GetString();

				dlg->VariableName = data[_T("Variable")].GetString();

				nowSymbol->label = dataLabel;
				nowSymbol->ResizeSymbol();
			}
			else if (type == _T("Set"))
			{
				objFlowView->CreateSymbolSet(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));

				nowSymbol = objFlowView->selectedObjectFlow->symbols.back();

				auto dlg = dynamic_cast<CAllocation*>(nowSymbol->dialog);

				auto& data = symbol[_T("Data")].GetObjectW();

				dataLabel = dlg->variableName = data[_T("Variable")].GetString();
				dataLabel += " ";
				dataLabel += dlg->allocationOperator = data[_T("Operator")].GetString();
				dataLabel += " ";
				dataLabel += dlg->allocationValue = data[_T("Value")].GetString();

				nowSymbol->label = dataLabel;
				nowSymbol->ResizeSymbol();
			}
			else if (type == _T("If"))
			{
				objFlowView->CreateSymbolIf(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));

				nowSymbol = objFlowView->selectedObjectFlow->symbols.back();

				auto* dlg = dynamic_cast<CConditionCheck*>(nowSymbol->dialog);

				auto& data = symbol[_T("Data")].GetObjectW();
				
				dlg->firstCheck = data[_T("IsExp1")].GetBool();
				dlg->secondCheck = data[_T("IsExp2")].GetBool();

				dataLabel = data[_T("Variable")].GetString();
				(dlg->firstCheck ? dlg->firstVariable = data[_T("Variable")].GetString() : dlg->firstValue = data[_T("Variable")].GetString());
				dataLabel += " ";
				dataLabel += data[_T("Operator")].GetString();
				dlg->compareOperator = data[_T("Operator")].GetString();
				dataLabel += " ";
				(dlg->secondCheck ? dlg->secondVariable = data[_T("Value")].GetString() : dlg->secondValue = data[_T("Value")].GetString()) ;
				dataLabel += data[_T("Value")].GetString();

				dlg->label = nowSymbol->label = dataLabel;
				nowSymbol->ResizeSymbol();

			}
			else if (type == _T("IfEnd"))
			{
				objFlowView->CreateSymbolIfEnd(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));
			}
			else if (type == _T("While"))
			{
				objFlowView->CreateSymbolWhile(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));

				nowSymbol = objFlowView->selectedObjectFlow->symbols.back();

				auto* dlg = dynamic_cast<CConditionCheck*>(nowSymbol->dialog);

				auto& data = symbol[_T("Data")].GetObjectW();

				dlg->firstCheck = data[_T("IsExp1")].GetBool();
				dlg->secondCheck = data[_T("IsExp2")].GetBool();

				dataLabel = data[_T("Variable")].GetString();
				(dlg->firstCheck ? dlg->firstVariable : dlg->firstValue) = data[_T("Variable")].GetString();
				dataLabel += " ";
				dataLabel += dlg->compareOperator = data[_T("Operator")].GetString();
				dataLabel += " ";
				(dlg->secondCheck ? dlg->secondVariable : dlg->secondValue) = data[_T("Value")].GetString();
				dataLabel += data[_T("Value")].GetString();

				dlg->label = nowSymbol->label = dataLabel;
				nowSymbol->ResizeSymbol();
			}
			else if (type == _T("WhileEnd"))
			{
				objFlowView->CreateSymbolWhileEnd(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));
			}
			else
			{
				AfxMessageBox(_T("�� �� ���� ��ȣ!"));
			}


			//������ �׾��� �ִ��� Ȯ��.
			auto& LineData = symbol[_T("Line")].GetObjectW();

			if (type == _T("If"))
			{
				if (LineData[_T("TrueLine")].GetBool())
				{
					int x = LineData[_T("LinkTrueXPos")].GetInt(), y = LineData[_T("LinkTrueYPos")].GetInt();
					vLinkLinePos.push_back(std::make_tuple(eTrueLine, pos + Point(10, 10) , Point(x, y) + Point(10, 10)));
				}
				if (LineData[_T("FalseLine")].GetBool())
				{
					int x = LineData[_T("LinkFalseXPos")].GetInt(), y = LineData[_T("LinkFalseYPos")].GetInt();
					vLinkLinePos.push_back(std::make_tuple(eFalseLine, pos + Point(10, 10), Point(x, y) + Point(10, 10)));
				}
			}
			else
			{
				LineType = LineData[_T("LineType")].GetBool();
				if (LineType)
				{
					int x = LineData[_T("LinkXPos")].GetInt(), y = LineData[_T("LinkYPos")].GetInt();
					vLinkLinePos.push_back(std::make_tuple(eYes, pos + Point(10, 10), Point(x, y) + Point(10, 10)));
				}
			}
		}

		//���� �߱�.
		for (auto itor = vLinkLinePos.begin(); itor != vLinkLinePos.end(); itor++)
		{
			//���� ����
			switch (std::get<0>(*itor))
			{
			case eYes:
				objFlowView->CreateLine(std::get<1>(*itor), std::get<2>(*itor));
				break;
			case eTrueLine:
				objFlowView->CreateTrueLine(std::get<1>(*itor), std::get<2>(*itor));
				break;
			case eFalseLine:
				objFlowView->CreateFalseLine(std::get<1>(*itor), std::get<2>(*itor));
				break;
			default:
				break;
			}
		}

		objFlowView->Invalidate();

		flowobject->objectFlow->Initialize(start, end, flowobject);

		mainFrame->objectFlow->objectFlows.push_back(flowobject->objectFlow);


		//�ɺ�ó�� ��
		mainFrame->play->PushObject(flowobject);
		mainFrame->play->Invalidate();

		// ������ �̹��� ����
		HANDLE hbitmap;
		hbitmap = LoadImageW(NULL, newObject->iconImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		CBitmap bitmap;
		bitmap.Attach(hbitmap);

		BITMAP	bmpInfo;
		bitmap.GetBitmap(&bmpInfo);

		imageList.Add(&bitmap, RGB(0, 0, 0));

		list.SetImageList(&imageList, LVSIL_NORMAL);

		INT imageCount = imageList.GetImageCount() - 1;

		list.InsertItem(imageCount, objName, imageCount);

		mainFrame->objectList->ImagePositionRevision();

		mainFrame->objectList->objects.push_back(newObject);

		mainFrame->objectList->Invalidate();
	}

	return;
}


BOOL CFlowStreamDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}


// CFlowStreamDoc serialization

void CFlowStreamDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CFlowStreamDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CFlowStreamDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CFlowStreamDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TExT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFlowStreamDoc ����

#ifdef _DEBUG
void CFlowStreamDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlowStreamDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFlowStreamDoc ���


BOOL CFlowStreamDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return LoadProjectFile(lpszPathName);
}


BOOL CFlowStreamDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return SaveProjectFile(lpszPathName);
}


void CFlowStreamDoc::OnFileSave()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (this->filePath == _T(""))
	{
		//������Ʈ �̸�, ��� ����.
		
		//���� ����.
		CFileDialog dlg(false, _T("Project.json"), _T("Project.json"), OFN_HIDEREADONLY, _T("FlowStream ProjectFile|Project.json||"), NULL);

		if (dlg.DoModal() == IDOK)
		{
			CString path = dlg.GetFolderPath();
			path += "\\";
			if (this->filePath != path)	//���� ������Ʈ ���� üũ.
			{
				CT2CA convertedFolder(path);
				std::string Folder;
				Folder = convertedFolder;
				Folder += "Resource";

				//resource ���͸� ����.
				mkdir(Folder.c_str());
				this->OnSaveDocument(dlg.GetPathName());
				this->filePath = dlg.GetPathName();
				SaveProjectFile(this->filePath);
				this->filePath.TrimRight(_T("Project.json"));
			}
		}
	}
	else
	{
		SaveProjectFile(this->filePath + _T("Project.json"));
	}
}


void CFlowStreamDoc::OnFileSaveAs()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg(false, _T("Project.json"), _T("Project.json"), OFN_HIDEREADONLY, _T("FlowStream ProjectFile|Project.json||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString path = dlg.GetFolderPath();
		path += "\\";
		
		CT2CA convertedFolder(path);
		std::string Folder;
		Folder = convertedFolder;
		Folder += "Resource";

		//resource ���͸� ����.
		mkdir(Folder.c_str());
		this->OnSaveDocument(dlg.GetPathName());
		this->filePath = dlg.GetPathName();
		this->filePath.TrimRight(_T("Project.json"));
	}
}
