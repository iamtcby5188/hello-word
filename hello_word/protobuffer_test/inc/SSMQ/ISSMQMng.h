//-------------------------------------------------------------------------------------
//--Copyright	:	Sumscope
//--FileName	:	ISSMQMng.h 
//--Author		:	cheng.xu@sumscope.com
//--Date		:	2015.01.23
//--Desc		:	消息总线封装接口
//--History		:	Created by cheng.xu, 2015.01.23
//--				
//-------------------------------------------------------------------------------------

#ifndef __I_SS_MQMNG__
#define __I_SS_MQMNG__

#include "../sdbus/message.h"

#ifdef SSMQCLIENT_EXPORTS
#define SSMQCLIENT_API __declspec(dllexport)
#else
#define SSMQCLIENT_API __declspec(dllimport)
#endif

namespace SSMQ
{
	class ISSMQObs;

	class ISSMQMngCallback
	{
	protected:
		ISSMQMngCallback(){}

	public:
		virtual ~ISSMQMngCallback(){}

		//总线可以通过该接口关闭客户端
		virtual void CloseClient() = 0;
	};

	class ISSMQMng
	{
	protected:
		ISSMQMng(){}

	public:
		virtual ~ISSMQMng(){}

		//初始化消息总线
		virtual bool InitServer() = 0;
		//释放消息总线
		virtual bool ReleaseServer() = 0;
		//设置管理回调接口
		virtual void SetMngCallback(ISSMQMngCallback* pCallback) = 0;
		//关闭当前客户端下的总线,供客户端升级调用
		virtual void CloseLocalDataBus() = 0;
		//注册消息监听接口
		virtual bool RegObs(ISSMQObs* pObs) = 0;
        //注销消息监听接口
        virtual void ReleaseObs(ISSMQObs* pObs) = 0;
        //注销所有消息监听接口
        virtual void ReleaseAllObs() = 0;
		//同步发送消息,对应SSMQDT_Direct的方式,注意timeout单位为秒
		virtual bool Send(const sdbus::string& bindKey , const sdbus::Message& request , sdbus::Message& response , int timeout = -1) = 0;
		//异步发送消息,对应SSMQDT_Direct的方式
		virtual bool Post(const sdbus::string& bindKey , const sdbus::Message& msg) = 0;
		//异步发送消息,对应SSMQDT_Publish的方式
		virtual bool Publish(const sdbus::string& bindKey , const sdbus::Message& msg) = 0;
        //生成一个消息ID
        virtual sdbus::string GetUniqueMsgID() = 0;
	};
}

//获取ISSMQMng接口,需要SSMQClient.lib sdbusd.lib
SSMQCLIENT_API SSMQ::ISSMQMng* GetSSMQMng();

#endif