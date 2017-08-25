#pragma once
#include <string>
#include <list>
#include <time.h>

namespace MM_QUOT
{
	//报价信息结构
	struct QB_Quotation 
	{
		//报价ID
		std::string sQuotationID;
		//方向
		std::string sDirect;
		//资产
		std::string sAssetsType;
		//期限
		std::string sTerm;
		//期限类型
		int nTermType;
		//数量
		std::string sCount;
		//价格
		std::string sPrice;
		//撤销时间
		time_t tExpirationTime;
		//撤销计时类型
		int nCancelType;
		//标签 合并的信息,多个标签间用#分隔
		std::string sTags;
		//备注
		std::string sMemo;
		//创建用户
		std::string sCreateUsr;

		void Clear()
		{
			sQuotationID = "";
			sDirect = "";
			sAssetsType = "";
			sTerm = "";
			nTermType = 0;
			sCount = "";
			sPrice = "";
			tExpirationTime = 0;
			nCancelType = 0;
			sTags = "";
			sMemo = "";
			sCreateUsr = "";
		}
	};

	typedef std::list<QB_Quotation> LstQBQuotation;

	//联系人信息结构
	struct QB_Contact
	{
		//联系人ID
		std::string sContactID;
		int nContactType;	//nContactType: 0为个人;1为group
		time_t SendTime;
	};

	typedef std::list<QB_Contact> LstQBContact;

	//报价管理信息
	struct QB_QuotationMngInfo
	{
		Quotation Quot;
		LstContact Contacts;
		int nMngType;	//0为发送, 1为撤销
		int nOpFlag;	//0为新增 1为报价修改 2为联系人修改
	};

	typedef std::list<QB_QuotationMngInfo> LstQBQuotationMngInfo;


	//联系人信息
	struct QB_ContactInfo
	{
		Contact ct;
		//sInfo 根据不同的联系人类型把相关信息组合起来
		std::string sInfo;
	};

	typedef std::list<QB_ContactInfo> LstQBContactInfo;

	//报价发送记录信息
	struct QB_Quotation_History
	{
		Quotation Quot;
		time_t SendTime;
		ContactInfo CtInfo;
		int nRecType;		//0为发送, 1为撤销
	};

	typedef std::list<QB_Quotation_History> LstQBQuotation_History;
}