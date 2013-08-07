#pragma once

#include <string>

using namespace std;

class Exception
{
public:
	Exception(string msg = "");

	string Message() const;

	virtual ~Exception(void);

protected:
	string m_Message;
};

