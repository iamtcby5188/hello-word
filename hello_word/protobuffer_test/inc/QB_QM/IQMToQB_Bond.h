#pragma once

#include "QB_QMDefine.h"

//Bond相关的联动接口

namespace QB_QM
{
	//回调接口,由QM实现
	class IQMToQBCallback_Bond
	{
	protected:
		IQMToQBCallback_Bond(){}

	public:
		virtual ~IQMToQBCallback_Bond(){}

		//请求债券信息返回
		virtual void RequestBondInfosRet(const LstBondItem& LstRet) = 0;
		//发送/撤销债券报价(按代码)
		virtual bool SendBondQuotByCode(const std::string& sMsgID, const LstBondQuotByCodeSendInfoV2& lstSend) = 0;
		//回复债券报价(按代码)
		virtual bool ReplyBondQuotByCode(const BondQuotByCodeReplyInfo& Reply, const std::string& sWndID) = 0;
        //批量查询Bond报价(按代码)的状态返回
        virtual void QueryBondQuotByCodeStatusRet(const std::string& sReqID, const LstQuotStatus& lstRet) = 0;
        //向指定用户分享债券
        virtual bool ShareBond(const LstContact& Contacts, const LstBondShare& lstBS, const std::string& sWndID) = 0;
	};

	class IQMToQB_Bond
	{
	protected:
		IQMToQB_Bond(){}

	public:
		virtual ~IQMToQB_Bond(){}
		
		//注册Bond相关回调接口
		virtual void RegCallback(IQMToQBCallback_Bond* pCallback) = 0;
		//请求债券信息
		virtual bool RequestBondInfos() = 0;
		//打开债券详情
		virtual bool ShowDlgBondDetail(const std::string& sBondKey) = 0;
		//发送/撤销债券报价(按代码)结果返回
		virtual bool SendBondQuotByCodeRet(const std::string& sMsgID, const Contact& ct, const SetString& Success, const SetString& Failed) = 0;
        //批量查询Bond报价(按代码)的状态,异步接口,返回请求ID
        virtual std::string QueryBondQuotByCodeStatus(const LstQuotStatusReq& lstReq) = 0;
	};
}


