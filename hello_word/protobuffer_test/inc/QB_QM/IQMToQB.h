#pragma once

#include "QB_QMDefine.h"

//总的联动接口,提供管理相关的方法

namespace QB_QM
{
	//MM相关的联动接口,使用的地方引用"IQMToQB_MM.h"
	class IQMToQB_MM;
	//Bond相关的联动接口,使用的地方引用"IQMToQB_Bond.h"
	class IQMToQB_Bond;
    //申购相关的联动接口,使用的地方引用"IQMToQB_Purchase.h"
    class IQMToQB_Purchase;
    //QM提醒相关的联动接口,使用的地方引用"IQMToQB_Remind.h"
    class IQMToQB_Remind;

	//回调接口,由QM实现
	class IQMToQBCallback
	{
	protected:
		IQMToQBCallback(){}

	public:
		virtual ~IQMToQBCallback(){}

		//选择联系人
		virtual bool SelContacts(const std::string& sSelID, const std::string& sWndID, int nLimit, bool bShowGrp) = 0;
		//编辑联系人
		virtual bool EditContacts(const std::string& sEditID, const LstContact& Contacts, const std::string& sWndID, int nLimit, bool bShowGrp) = 0;
		//查询联系人信息,查询时无效的ID从lstFailed返回
		virtual bool QueryContactInfo(const LstContact& lstIn, LstPersonInfo& lstPerson, LstGroupInfo& lstGrp, LstContact& lstFailed) = 0;
		//退出QM
		virtual void QuitQM() = 0;
		//打开QM主面板
		virtual bool OpenMainPanel(const std::string& sWndID) = 0;
		//打开对话
		virtual bool OpenDialogue(const Contact& ct, const std::string& sSendMsg, const std::string& sWndID, const bool bDialogue = true) = 0;
		//获取当前用户的QMID
		virtual unsigned long long GetCurUsrID() = 0;
		//查询当前用户好友ID
		virtual bool QueryCurUsrFriendIDs() = 0;
		//查询当前用户群ID
		virtual bool QueryCurUsrGroupIDs() = 0;
		//通报QB状态 1:QB在总线上 0:QB不在总线上
		virtual void QBStatus(int nStatus) = 0;
		//向指定用户发送消息
		virtual bool SendMsg(const LstContact& Contacts, const std::string& sMsg, const std::string& sWndID) = 0;
        //查询QM窗口位置,若sWndID为空则默认为主窗口位置
        virtual bool QueryQMWndPos(const std::string& sWndID, int& nTop, int& nBottom, int& nLeft, int& nRight) = 0;
        //查询QM窗口句柄,若sWndID为空则默认为主窗口句柄
        virtual bool QueryQMWndHandle(const std::string& sWndID, unsigned long long& hWnd) = 0;
        //查询当前用户分享到的群
        virtual bool QuerySharedGroup(Contact& ct) = 0;
        //搜索QM联系人
        virtual bool SearchQMContact(const ContactSearch& Input, LstSearchUserInfo& Result) = 0;
        //QBAccount批量查询QMID, MsgID用于和响应匹配
        virtual void QueryQMIDByQBAccount(const std::string& sMsgID, const SetString& setQBAccount) = 0;
        //打开新闻资讯
        virtual bool OpenNewsBulletin(const std::string& sWndID) = 0;
        //查询客服
        virtual bool QueryCustomService(Contact& ct) = 0;
        //QB修改密码
        virtual void QBModifyPwd(const std::string& sNewPwd) = 0;
        //申请入群group
        virtual void ReqJoinGroup(const std::string& sMsgID, const unsigned long long &llGroup) = 0;
		//打开指定新闻
		virtual void ReqOpenNews(const NewsInfo &info) = 0;
        //分享图片
        virtual void SharePic(const PicInfo &info, const LstContact& Contacts) = 0;
        //分享新闻给指定联系人
        virtual void ShareNewsDetail(const NewsInfoV2 &info, const LstContact& Contacts, bool bDisablePDF = true) = 0;
        //根据QB userID 打开对话框
        virtual void OpenDialogueByUserID(const std::string &userID) = 0;
        //查询QM在线状态
        virtual void QueryQMStatus() = 0;
        //调起QM承销商窗口接口
        virtual void ReqOpenSellsWnd(const std::string& sWndID) = 0;
        //查询QM非合作机构联系人接口
        virtual void ReqQueryNoInstituteContact(LstNoInstituteContact &contacts, int &status) = 0;
        //设置QM非合作机构联系人接口
        virtual void ReqSetNoInstituteContact(const std::list<std::string> &QBAccounts) = 0;
        //调用QM承销商界面中的点击管理后弹出的查找窗口
        virtual void ReqOpenSellsSearchWnd(const std::string& sWndID) = 0;
	};

	class IQMToQB
	{
	protected:
		IQMToQB(){}

	public:
		virtual ~IQMToQB(){}
		
		//初始化
		virtual void Init(const std::string& sUsr, const std::string& sPwd) = 0;
		//释放前端总线,QM退出前调用
		virtual void Release() = 0;
		//注册回调接口
		virtual void RegCallback(IQMToQBCallback* pCallback) = 0;
        //关闭总线及所有连接的客户端(包括自己)
        virtual void CloseLocalDataBus() = 0;
		//获取MM相关联动接口
		virtual IQMToQB_MM* GetSubInterface_MM() = 0;
		//获取Bond相关联动接口
		virtual IQMToQB_Bond* GetSubInterface_Bond() = 0;
        //获取申购相关联动接口
        virtual IQMToQB_Purchase* GetSubInterface_Purchase() = 0;
        //获取QM提醒相关联动接口
        virtual IQMToQB_Remind* GetSubInterface_Remind() = 0;
		//选择联系人返回
		virtual bool SelContactsRet(const std::string& sSelID, const LstContact& Contacts) = 0;
		//编辑联系人返回
		virtual bool EditContactsRet(const std::string& sEditID, const LstContact& Contacts) = 0;
		//设置QM的状态 1为在线;-1为掉线;2为登陆中 
		virtual void SetStatus(int nStatus) = 0;
		//查询当前用户好友ID返回
		virtual void QueryCurUsrFriendIDsRet(const SetUInt64& setIDs) = 0;
		//查询当前用户群ID返回
		virtual void QueryCurUsrGroupIDsRet(const SetUInt64& setIDs) = 0;
		//当前用户群变化时通知QB    JoinGrpIDs:新加入的群ID    LeaveGrpIDs:离开的群ID
		virtual void CurUsrGroupChange(const SetUInt64& JoinGrpIDs, const SetUInt64& LeaveGrpIDs) = 0;
        //当前用户好友变化时通知QB    AddFriendIDs:新加好友ID    DelFriendIDs:删除好友ID
        virtual void CurUsrFriendChange(const SetUInt64& AddFriendIDs, const SetUInt64& DelFriendIDs) = 0;
        //查询QB窗口位置,同步接口,注意timeout的单位是秒,窗口ID为空时默认查询主窗口
        virtual bool QueryQBWndPos(const std::string& sWndID, int& nTop, int& nBottom, int& nLeft, int& nRight, int timeout = -1) = 0;
        //查询QB窗口句柄,同步接口,注意timeout的单位是秒,窗口ID为空时默认查询主窗口
        virtual bool QueryQBWndHandle(const std::string& sWndID, unsigned long long& hWnd, int timeout = -1) = 0;
        //查询QB相关权限,同步接口,注意timeout的单位是秒
        //目前支持的权限:MM报价--mmquot;
        virtual bool QueryQBPerm(SetString& setPerm, int timeout = -1) = 0;
        //获取重复登陆提示同步状态,若返回为0则弹出提示,返回1则不弹提示
        virtual int GetMultiLoginStatus() = 0;
        //重设重复登陆提示同步状态,将状态置为0
        virtual void ResetMultiLoginStatus() = 0;
        //发送QM错误信息
        virtual void QMErrInfo(int nErrCode, const std::string& sErrInfo) = 0;
        //联系人信息推送
        virtual void ContactInfoPush(const LstPersonInfo& PersonInfos, const LstGroupInfo& GrpInfos) = 0;
        //联系人在线状态推送
        virtual void ContactStatusPush(const LstContactStatus& lstStatus) = 0;
        //QBAccount批量查询QMID返回
        virtual void QueryQMIDByQBAccountRet(const std::string& sMsgID, const LstQBAccount2QMID& lstRet) = 0;
        //申请入群group返回
        virtual void ReqJoinGroupRet(const std::string& sMsgID, bool bSuccess) = 0;
        //打开新闻详情,bDisablePDF表示是否禁用PDF下载
        virtual void ReqOpenNewsDetail(const NewsInfoV2 &info, bool bDisablePDF = true) = 0;
        //打开新闻窗口
        virtual void ReqOpenNewsWnd() = 0;
        //查询QM在线状态返回 1=在线;-1=掉线;2=登录中
        virtual void QueryQMStatusRet(int status) = 0;
        //QM非机构联系人修改后的推送接口
        virtual void ModifyNoInstituteContactRet(const LstNoInstituteContact& Contacts) = 0;
	};
}

QB_QM_API QB_QM::IQMToQB* GetQMToQB();

