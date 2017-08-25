#pragma once
#include "MsgMng.h"

typedef std::map<std::string, std::string> StrMap;

class CMsgQueueMap
{
public:
	CMsgQueueMap();
	~CMsgQueueMap();

	std::string GetQueueHead(const sdbus::Message& msg);

protected:
	void InitMap();
	void Clear();

private:
	StrMap m_MsgQueueMap;
    CRITICAL_SECTION m_cs;
};