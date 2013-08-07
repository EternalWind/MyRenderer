#include "Exception.h"


Exception::Exception(string msg)
	: m_Message(msg)
{
}

string Exception::Message() const
{
	return m_Message;
}

Exception::~Exception(void)
{
}
