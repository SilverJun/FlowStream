#pragma once

#include "Singleton.h"
#include <stack>

enum eState
{	
	eInitial,
	eLexicalAnalyzing,
	ePasingTree,
	eExecute,
	eError,
	eEnd
};

enum eScope
{
	eGlobal,
	eFunction
};

struct CState : CSingleton<CState>
{
	CState() : programState(eInitial) { programScope.push(eScope::eGlobal); }
	~CState(){}

	eState programState;
	std::stack<eScope> programScope;
};

#define g_State CState::GetInstance()
