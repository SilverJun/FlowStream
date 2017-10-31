#pragma once

#include <string>
#include "Value.h"

struct Symbol
{
	std::string name;
	Value data;

	Symbol(std::string _name, Value _data) : name(_name), data(_data){}
	~Symbol(){  }
};

