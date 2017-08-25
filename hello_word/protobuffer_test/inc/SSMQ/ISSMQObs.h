//-------------------------------------------------------------------------------------
//--Copyright	:	Sumscope
//--FileName	:	ISSMQObs.h
//--Author		:	cheng.xu@sumscope.com
//--Date		:	2015.01.23
//--Desc		:	消息总线消息监听接口
//--History		:	Created by cheng.xu, 2015.01.23
//--				
//-------------------------------------------------------------------------------------

#ifndef __I_SS_MQOBS__
#define __I_SS_MQOBS__

#include "sdbus/message.h"

namespace SSMQ
{
	enum SSMQDeliverType
	{
		SSMQDT_Undefine,
		SSMQDT_Direct,
		SSMQDT_Publish
	};

	class ISSMQObs
	{
	protected:
		ISSMQObs(){}

	public:
		virtual ~ISSMQObs(){}

		//监听器关注的消息topic
		virtual sdbus::string GetBindKey() = 0;
		//监听器关注的消息发送方式
		virtual SSMQDeliverType GetDeliverType() = 0;
		//监听到的消息
		virtual void OnMsgs(const sdbus::Message& msgs) = 0;
	};
}



#endif