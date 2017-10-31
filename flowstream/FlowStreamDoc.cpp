
// FlowStreamDoc.cpp : CFlowStreamDoc 클래스의 구현
//

#include "stdAFX.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

//ObjectListView 에서 쓰는 이미지 관리 객체.
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

//문자열이 숫자인지 판별. 소수인지도 추가로 판별.
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


// CFlowStreamDoc 생성/소멸

CFlowStreamDoc::CFlowStreamDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	projectDoc = NULL;

}


CFlowStreamDoc::~CFlowStreamDoc()
{
}

BOOL CFlowStreamDoc::NewProjectFile(LPCTSTR path)
{
	//프로젝트 생성.
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

	//root 생성.
	wValue root(kObjectType);
	root.SetObject();

	//projectName 저장.
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
			
			//좌표
			symbolX = (*itor)->position.X;
			symbolY = (*itor)->position.Y;
			
			thisSymbol.AddMember(wValue(_T("x")), symbolX, allocator);
			thisSymbol.AddMember(wValue(_T("y")), symbolY, allocator);

			//타입, 데이터
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


			//라인
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

			//최종으로 하나의 심볼이 완성
			Symbols.PushBack(thisSymbol, allocator);
		}
		
		thisObject.AddMember(wValue(_T("Symbols")), Symbols, allocator);
		Objects.PushBack(thisObject, allocator);
	}

	root.AddMember(wValue(_T("Objects")), Objects, allocator);

	//root 오브젝트를 DOM에 복사.
	newDoc.CopyFrom(root, allocator);

	//파일저장.
	FILE* fp = _wfopen(path, _T("wb"));
	char writeBuffer[65536];

	FileWriteStream os(fp, writeBuffer, _countof(writeBuffer));
	EncodedOutputStream<UTF16LE<>, FileWriteStream> encodedOS(os);
	PrettyWriter<EncodedOutputStream<UTF16LE<>, FileWriteStream>, rapidjson::UTF16LE<>, rapidjson::UTF16LE<>, MemoryPoolAllocator<>> writer(encodedOS);
	newDoc.Accept(writer);

	projectDoc.CopyFrom(newDoc, allocator);
	fclose(fp);

	//리소스 복사.
	CString targetFolderPath = path;
	targetFolderPath.TrimRight(_T("Project.json"));
	for (int i = 0; i < mainFrame->objectList->objects.size(); i++)
	{
		//복사할 파일은 4개.
		//오브젝트이름.bmp		- 원본 이미지.
		//오브젝트이름.txt		- 인터프리터 코드.
		//object.bmp			- 플레이뷰에서 쓰일 이미지
		//resize오브젝트이름.bmp - 리스트뷰에서 쓰일 이미지. 50*50으로 고정.
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
					AfxMessageBox(_T("원본 파일 열기 에러!"));
					return FALSE;
				}

				//파일 사이즈 계산.
				std::streamoff size;
				fileSource[j].seekg(0, std::ios::end);
				size = fileSource[j].tellg();
				fileSource[j].seekg(0, std::ios::beg);
				fileSource[j].clear();

				//파일 복사.
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

	//프로젝트 json불러오기 완료.

	if (!projectDoc.HasMember(_T("ProjectName")))
	{
		AfxMessageBox(_T("json파일에 프로젝트 관련 값이 없습니다."), MB_OK | MB_ICONEXCLAMATION);
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
		
		// 오브젝트 생성
		CFlowObject*	flowobject = new CFlowObject();
		CObjectFlowView* objFlowView = mainFrame->objectFlow;
		flowobject->Initialize(objName);

		//심볼처리
		flowobject->objectFlow = new CObjectFlow();

		auto& symbols = thisObject[_T("Symbols")].GetArray();

		//새로 만든 오브젝트를 선택.
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

			//심볼데이터 처리
			std::wstring type = symbol[_T("Type")].GetString();

			if (type == _T("Start"))
			{
				if (start != nullptr)
					AfxMessageBox(_T("Start기호가 2개 이상 존재합니다."));
				else
					start = objFlowView->CreateSymbolStart(pos, Size(SYMBOL_XSIZE, SYMBOL_YSIZE));
			}
			else if (type == _T("End"))
			{
				if (end != nullptr)
					AfxMessageBox(_T("End기호가 2개 이상 존재합니다."));
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
				AfxMessageBox(_T("알 수 없는 기호!"));
			}


			//라인이 그어저 있는지 확인.
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

		//라인 긋기.
		for (auto itor = vLinkLinePos.begin(); itor != vLinkLinePos.end(); itor++)
		{
			//라인 종류
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


		//심볼처리 끝
		mainFrame->play->PushObject(flowobject);
		mainFrame->play->Invalidate();

		// 아이콘 이미지 생성
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

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}


// CFlowStreamDoc serialization

void CFlowStreamDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CFlowStreamDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CFlowStreamDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CFlowStreamDoc 진단

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


// CFlowStreamDoc 명령


BOOL CFlowStreamDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return LoadProjectFile(lpszPathName);
}


BOOL CFlowStreamDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return SaveProjectFile(lpszPathName);
}


void CFlowStreamDoc::OnFileSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (this->filePath == _T(""))
	{
		//프로젝트 이름, 경로 설정.
		
		//파일 저장.
		CFileDialog dlg(false, _T("Project.json"), _T("Project.json"), OFN_HIDEREADONLY, _T("FlowStream ProjectFile|Project.json||"), NULL);

		if (dlg.DoModal() == IDOK)
		{
			CString path = dlg.GetFolderPath();
			path += "\\";
			if (this->filePath != path)	//같은 프로젝트 열기 체크.
			{
				CT2CA convertedFolder(path);
				std::string Folder;
				Folder = convertedFolder;
				Folder += "Resource";

				//resource 디렉터리 생성.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog dlg(false, _T("Project.json"), _T("Project.json"), OFN_HIDEREADONLY, _T("FlowStream ProjectFile|Project.json||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString path = dlg.GetFolderPath();
		path += "\\";
		
		CT2CA convertedFolder(path);
		std::string Folder;
		Folder = convertedFolder;
		Folder += "Resource";

		//resource 디렉터리 생성.
		mkdir(Folder.c_str());
		this->OnSaveDocument(dlg.GetPathName());
		this->filePath = dlg.GetPathName();
		this->filePath.TrimRight(_T("Project.json"));
	}
}
