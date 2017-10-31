#pragma once

#include <string>

class Error			//Error Å¬·¡½º
{
public:
	Error(std::string msg) : m_Msg(msg)
	{
	}

	~Error()
	{
	}

	std::string what()
	{
		return m_Msg;
	}

private:
	std::string m_Msg;
};

