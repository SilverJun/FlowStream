#pragma once
#include "Singleton.h"

class CStringPool : public CSingleton<CStringPool>
{
public:
	CStringPool();
	~CStringPool();

	std::string* GetConstString(int index);
	int AddConstString(const std::string str);

private:
	std::unordered_map<int, std::string> stringPool;
	int count;

};

#define g_StringPool CStringPool::GetInstance()
