#include "stdafx.h"
#include "VM.h"

#include "Error.h"
#include "StringPool.h"

#include "State.h"

VM::VM()
{
	
}


VM::~VM()
{
}


void VM::Execute(statementList StatementList)
{
	clock_t CurTime, OldTime = clock();

	statementList::iterator itor;
	for (itor = StatementList.begin(); itor != StatementList.end(); itor++)		//실행문들을 수행!
	{
		try
		{
			itor->get()->Execute(symbolTable);
		}
		catch (Error& error)
		{
			std::cout << "Runtime Error : " << error.what() << std::endl;
			return;
		}
		catch (std::bad_alloc)
		{
			std::cout << "Runtime Error : bad_alloc" << std::endl;
			return;
		}
		catch (...)
		{
			std::cout << "Runtime Error : Unexcepted Error" << std::endl;
			return;
		}

		/*while (1)
		{
			CurTime = clock();
			if (CurTime - OldTime > 33)
			{
				OldTime = CurTime;
				break;
			}
		}*/
	}
}
