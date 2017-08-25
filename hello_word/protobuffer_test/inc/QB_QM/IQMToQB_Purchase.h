#pragma once

#include "QB_QMDefine.h"

//一级申购相关的联动接口

namespace QB_QM
{
	//回调接口,由QM实现
	class IQMToQBCallback_Purchase
	{
	protected:
		IQMToQBCallback_Purchase(){}

	public:
		virtual ~IQMToQBCallback_Purchase(){}

        //向指定用户发送申购信息
        virtual bool Purchase(const Contact& ct, const PurchaseInfo& PInfo, const std::string& sWndID) = 0;
        //查询对于指定联系人是否显示申购按钮返回
        virtual void ContactIsDealerRet(const std::string& sReqID, bool bRet) = 0;
        //查询当前用户有权限看到的交易员QMID返回
        virtual void GetAllDealerRet(const std::string& sReqID, const SetUInt64& setID) = 0;
        //批量查询申购的状态返回
        virtual void QueryPurchaseStatusRet(const std::string& sReqID, const MapPurchaseStatus& mapPStatus) = 0; 
        //确认申购返回申购的状态
        virtual void ConfirmPurchaseRet(const std::string& sReqID, int nStatus) = 0;
        //查询指定联系人下申购是否能编辑返回
        virtual void IsEditPurchaseValidRet(const std::string& sReqID, bool bRet) = 0;
        //申购状态改变推送
        virtual void PurchaseStatusPush(const MapPurchaseStatus& mapPStatus) = 0;
        //申购按钮是否显示推送
        virtual void ContactIsDealerPush(const Contact& ct, bool bRet) = 0;
        //申购编辑按钮是否显示推送
        virtual void IsEditPurchaseValidPush(const Contact& ct, bool bRet) = 0;
	};

	class IQMToQB_Purchase
	{
	protected:
		IQMToQB_Purchase(){}

	public:
		virtual ~IQMToQB_Purchase(){}
		
        //注册申购相关回调接口
        virtual void RegCallback(IQMToQBCallback_Purchase* pCallback) = 0;
        //查询对于指定联系人是否显示申购按钮,异步接口,返回请求ID
        virtual std::string ContactIsDealer(const Contact& ct) = 0;
        //查询当前用户有权限看到的交易员QMID,异步接口,返回请求ID
        virtual std::string GetAllDealer() = 0;
        //打开申购对话框
        virtual void OpenSubscribeDlg(const Contact& ct, const std::string& sWndID = "") = 0;
        //批量查询申购的状态,异步接口,返回请求ID
        virtual std::string QueryPurchaseStatus(const LstPurchaseUkey& lstQuery) = 0;
        //确认申购,异步接口,返回请求ID
        virtual std::string ConfirmPurchase(const std::string& sPurchaseID, time_t ModifyTime) = 0; 
        //查询指定联系人下申购是否能编辑,异步接口,返回请求ID
        virtual std::string IsEditPurchaseValid(const Contact& ct) = 0;
        //编辑申购报价
        virtual void EditPurchase(const Contact& ct, const std::string& sWndID = "") = 0;
	};
}


