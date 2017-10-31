#include "stdafx.h"
#include "StringPool.h"

#include "Error.h"

CStringPool::CStringPool() : count(0)
{
}

CStringPool::~CStringPool()
{
}

std::string* CStringPool::GetConstString(int index)
{
	auto it = stringPool.find(index);
	if (it == stringPool.end())
		throw(Error(std::string("Can`t Find ConstString")));

	return &it->second;
}

int CStringPool::AddConstString(const std::string str)
{
	stringPool[count] = str;
	return count++;
}
