#pragma once

#include "QB_QMDefine.h"

//MM相关的联动接口

namespace QB_QM
{
	//回调接口,由QM实现
	class IQMToQBCallback_MM
	{
	protected:
		IQMToQBCallback_MM(){}

	public:
		virtual ~IQMToQBCallback_MM(){}

		//发送/撤销MM报价
		virtual bool SendQuot(const std::string& sMsgID, const LstMMQuotSendInfoV2& lstSend) = 0;
		//回复MM报价
		virtual bool ReplyQuot(const QuotReplyInfo& Reply, const std::string& sWndID) = 0;
        //批量查询MM报价状态返回
        virtual void QueryMMQuotStatusRet(const std::string& sReqID, const LstQuotStatus& lstRet) = 0;
	};

	class IQMToQB_MM
	{
	protected:
		IQMToQB_MM(){}

	public:
		virtual ~IQMToQB_MM(){}
		
		//注册MM相关回调接口
		virtual void RegCallback(IQMToQBCallback_MM* pCallback) = 0;
		//发送/撤销报价结果返回
		virtual bool SendQuotRet(const std::string& sMsgID, const Contact& ct, const SetString& Success, const SetString& Failed) = 0;
        //打开MM报价,Contacts是选择联系人时需要带回QM的联系人列表
        virtual void OpenMMQuot(const LstContact& Contacts, const std::string& sWndID = "") = 0;
        //批量查询MM报价状态,异步接口,返回请求ID
        virtual std::string QueryMMQuotStatus(const LstQuotStatusReq& lstReq) = 0;
	};
}


