#pragma once
#include "QB_QMDefine.h"

namespace QB_QM
{
	class IQBToQMCallback
	{
	protected:
		IQBToQMCallback(){}

	public:
		virtual ~IQBToQMCallback(){}

		//退出QB,关闭总线时会调用该接口
		virtual void QuitQB() = 0;
		//选择联系人返回
		virtual bool SelContactsRet(const std::string& sSelID, const LstContact& Contacts) = 0;
		//查询联系人信息返回,查询时无效的ID从lstFailed返回
		virtual bool QueryContactInfoRet(LstPersonInfo& PersonInfos, LstGroupInfo& GrpInfos, const LstContact& lstFailed) = 0;
		//编辑联系人返回
		virtual bool EditContactsRet(const std::string& sEditID, const LstContact& Contacts) = 0;
		//发送/撤销报价结果返回
		virtual bool SendQuotRet(const std::string& sMsgID, const Contact& ct, const SetString& Success, const SetString& Failed) = 0;
		//通报QM状态 1为在线;-1为掉线;2为登陆中 
		virtual void QMStatus(int nStatus) = 0;
		//请求债券信息
		virtual bool RequestBondInfos() = 0;
		//打开债券详情
		virtual bool ShowDlgBondDetail(const std::string& sBondKey) = 0;
		//查询当前用户的QMID返回
		virtual void QueryCurUsrIDRet(unsigned long long UsrID) = 0;
		//查询当前用户好友ID返回
		virtual void QueryCurUsrFriendIDsRet(const SetUInt64& setIDs) = 0;
		//查询当前用户群ID返回
		virtual void QueryCurUsrGroupIDsRet(const SetUInt64& setIDs) = 0;
		//当前用户群变化时通知QB    JoinGrpIDs:新加入的群ID    LeaveGrpIDs:离开的群ID
		virtual void CurUsrGroupChange(const SetUInt64& JoinGrpIDs, const SetUInt64& LeaveGrpIDs) = 0;
        //当前用户好友变化时通知QB    AddFriendIDs:新加好友ID    DelFriendIDs:删除好友ID
        virtual void CurUsrFriendChange(const SetUInt64& AddFriendIDs, const SetUInt64& DelFriendIDs) = 0;
        //查询QB窗口位置
        virtual bool QueryQBWndPos(const std::string& sWndID, int& nTop, int& nBottom, int& nLeft, int& nRight) = 0;
        //查询QB窗口句柄,若sWndID为空则默认为主窗口句柄
        virtual bool QueryQBWndHandle(const std::string& sWndID, HWND& hWnd) = 0;
        //查询QB相关权限:MM报价--mmquot;
        virtual bool QueryQBPerm(SetString& setPerm) = 0;
        //打开MM报价,Contacts是选择联系人时需要带回QM的联系人列表
        virtual void OpenMMQuot(const LstContact& Contacts, const std::string& sWndID) = 0;
        //搜索QM全市场联系人返回
        virtual void SearchQMContactRet(const std::string& sMsgID, const LstSearchUserInfo& Result) = 0;
        //查询对于指定联系人是否显示申购按钮
        virtual bool ContactIsDealer(const Contact& ct) = 0;
        //打开申购对话框
        virtual void OpenSubscribeDlg(const Contact& ct, const std::string& sWndID) = 0;
        //查询当前用户有权限看到的交易员QMID
        virtual void GetAllDealer(const std::string& sReqID) = 0;
		//发送/撤销债券报价(按代码)结果返回
		virtual bool SendBondQuotByCodeRet(const std::string& sMsgID, const Contact& ct, const SetString& Success, const SetString& Failed) = 0;
        //QM错误信息通知
        virtual void QMErrInfo(int nErrCode, const std::string& sErrInfo) = 0;
        //批量查询申购的状态
        virtual void QueryPurchaseStatus(const LstPurchaseUkey& lstQuery, MapPurchaseStatus& mapRet) = 0;
        //确认申购, 返回申购状态
        virtual void ConfirmPurchase(const std::string& sReqID, const std::string& sPurchaseID, time_t ModifyTime) = 0; 
        //查询指定联系人下申购是否能编辑
        virtual bool IsEditPurchaseValid(const Contact& ct) = 0;
        //编辑申购报价
        virtual void EditPurchase(const Contact& ct, const std::string& sWndID) = 0;
        //批量查询MM报价状态
        virtual void QueryMMQuotStatus(const std::string& sReqID, const LstQuotStatusReq& lstReq) = 0;
        //批量查询Bond报价(按代码)的状态
        virtual void QueryBondQuotByCodeStatus(const std::string& sReqID, const LstQuotStatusReq& lstReq) = 0;
        //联系人信息推送
        virtual void ContactInfoPush(const LstPersonInfo& PersonInfos, const LstGroupInfo& GrpInfos) = 0;
        //联系人在线状态推送
        virtual void ContactStatusPush(const LstContactStatus& lstStatus) = 0;
        //QBAccount批量查询QMID返回
        virtual void QueryQMIDByQBAccountRet(const std::string& sMsgID, const LstQBAccount2QMID& lstRet) = 0;
        //查询当前设置的QM提醒返回
        virtual void QueryQMRemindConfigRet(const std::string& sMsgID, const QMRemindConfig& QMRCfg) = 0;
        //新增QM关键字提醒返回
        virtual void AddQMRemindKeyItemRet(const std::string& sMsgID, const std::string& ItemID) = 0;
        //修改QM关键字提醒返回
        virtual void ModifyQMRemindKeyItemRet(const std::string& sMsgID, bool bSuccess) = 0;
        //删除QM关键字提醒返回
        virtual void DelQMRemindKeyItemRet(const std::string& sMsgID, const SetString& setSuccessID) = 0;
        //新增QM好友提醒返回
        virtual void AddQMRemindFriendItemRet(const std::string& sMsgID, const std::string& ItemID) = 0;
        //修改QM好友提醒返回
        virtual void ModifyQMRemindFriendItemRet(const std::string& sMsgID, bool bSuccess) = 0;
        //删除QM好友提醒返回
        virtual void DelQMRemindFriendItemRet(const std::string& sMsgID, const SetString& setSuccessID) = 0;
        //设置QM提醒方式返回
        virtual void SetQMRemindTypeRet(const std::string& sMsgID, bool bSuccess) = 0;
        //申请入群group返回
        virtual void ReqJoinGroupRet(const std::string& sMsgID, bool bSuccess) = 0;
        //打开新闻详情
        virtual void ReqOpenNewsDetail(const NewsInfoV2 &info, bool bDisablePDF = true) = 0;
        //打开新闻窗口
        virtual void ReqOpenNewsWnd() = 0;
        //查询QM在线状态返回 1=在线;-1=掉线;2=登录中
        virtual void QueryQMStatusRet(int status) = 0;
        //QM非机构联系人修改后的推送接口
        virtual void ModifyNoInstituteContactRet(const LstNoInstituteContact& Contacts) = 0;
	};

    struct QMProxyParam
    {
        //ProxyType:
        //Proxy_Type_None = 0,
        //Proxy_Type_HTTP = 1,
        //Proxy_Type_Socks4 = 2,
        //Proxy_Type_Socks5 = 3,
        //Proxy_Type_IE = 4,

        //代理类型
        int ProxyType;
        //代理地址
        std::string ProxyIP;
        //代理端口
        std::string ProxyPort;
        //代理用户
        std::string ProxyUser;
        //代理密码
        std::string ProxyPwd;
        //域
        std::string ProxyDomain;

        QMProxyParam()
            :ProxyType(0)
            ,ProxyIP("")
            ,ProxyPort("")
            ,ProxyUser("")
            ,ProxyPwd("")
            ,ProxyDomain("")
        {
        }

        QMProxyParam& operator= (const QMProxyParam& pi)
        {
            ProxyType = pi.ProxyType;
            ProxyIP = pi.ProxyIP;
            ProxyPort = pi.ProxyPort;
            ProxyUser = pi.ProxyUser;
            ProxyPwd = pi.ProxyPwd;
            ProxyDomain = pi.ProxyDomain;
            return (*this) ;
        }
    };

	struct QBToQMInitParam
	{
		//用户
		std::string sUsr;
		//密码
		std::string sPwd;
		//QM所在目录
		std::string sQMDir;
		//QM主程序名称
		std::string sQMExeName;
        //QM代理设置信息
        QMProxyParam stQMProxyInfo;

        QBToQMInitParam()
            :sUsr("")
            ,sPwd("")
            ,sQMDir("")
            ,sQMExeName("")
        {}
	};

	class IQBToQM
	{
	protected:
		IQBToQM(){}

	public:
		virtual ~IQBToQM(){}

		//初始化
		virtual bool Init(const QBToQMInitParam& InitParam) = 0;
		//注册回调接口
		virtual void RegCallback(IQBToQMCallback* pCallback) = 0;
		//关闭总线及所有连接的客户端(包括自己)
		virtual void CloseLocalDataBus() = 0;
		//选择联系人
		virtual bool SelContacts(const std::string& sSelID, const std::string& sWndID = "", int nLimit = 200, bool bShowGrp = true) = 0;
		//编辑联系人
		virtual bool EditContacts(const std::string& sEditID, const LstContact& Contacts, const std::string& sWndID = "", int nLimit = 200, bool bShowGrp = true) = 0;
		//发送/撤销报价, 返回MsgID用于和响应匹配
        virtual std::string SendQuot(const LstMMQuotSendInfoV2& lstSend) = 0;
		//查询联系人信息(异步返回)
		virtual bool QueryContactInfo(const LstContact& lstIn) = 0;
		//退出QM bChkSession为true时只退出相同账号,为false时不管账号,都退出
		virtual bool QuitQM(bool bChkSession) = 0;
		//请求债券信息返回
		virtual bool RequestBondInfosRet(const LstBondItem& LstRet) = 0;
		//打开QM主面板
		virtual bool OpenMainPanel(const std::string& sWndID = "") = 0;
		//打开对话, bDialogue表示A点击QB中B图标发起会话，B的窗口是否需弹出
		virtual bool OpenDialogue(const Contact& ct, const std::string& sSendMsg, const std::string& sWndID = "", const bool bDialogue = true) = 0;
		//回复报价
		virtual bool ReplyQuot(const QuotReplyInfo& Reply, const std::string& sWndID = "") = 0;
		//查询当前用户的QMID
		virtual bool QueryCurUsrID() = 0;
		//查询当前用户好友ID
		virtual bool QueryCurUsrFriendIDs() = 0;
		//查询当前用户群ID
		virtual bool QueryCurUsrGroupIDs() = 0;
		//发送/撤销债券报价(按代码), 返回MsgID用于和响应匹配
		virtual std::string SendBondQuotByCode(const LstBondQuotByCodeSendInfoV2& lstSend) = 0;
		//回复债券报价(按代码)
		virtual bool ReplyBondQuotByCode(const BondQuotByCodeReplyInfo& Reply, const std::string& sWndID = "") = 0;
		//向指定用户发送消息
		virtual bool SendMsg(const LstContact& Contacts, const std::string& sMsg, const std::string& sWndID = "") = 0;
        //查询QM窗口位置,同步接口,注意timeout的单位是秒,窗口ID为空时默认查询主窗口
        virtual bool QueryQMWndPos(const std::string& sWndID, int& nTop, int& nBottom, int& nLeft, int& nRight, int timeout = -1) = 0;
        //查询QM窗口句柄,同步接口,注意timeout的单位是秒,窗口ID为空时默认查询主窗口
        virtual bool QueryQMWndHandle(const std::string& sWndID, HWND& hWnd, int timeout = -1) = 0;
        //获取重复登陆提示同步状态,若返回为0则弹出提示,返回1则不弹提示
        virtual int GetMultiLoginStatus() = 0;
        //重设重复登陆提示同步状态,将状态置为0
        virtual void ResetMultiLoginStatus() = 0;
        //查询当前用户分享到的群
        virtual bool QuerySharedGroup(Contact& ct, int timeout = -1) = 0;
        //搜索QM联系人, 返回MsgID用于和响应匹配
        virtual std::string SearchQMContact(const ContactSearch& Input) = 0;
        //查询当前用户有权限看到的交易员QMID返回
        virtual void GetAllDealerRet(const std::string& sReqID, const SetUInt64& setID) = 0;
        //向指定用户发送申购信息
        virtual std::string Purchase(const Contact& ct, const PurchaseInfo& PInfo, const std::string& sWndID = "") = 0;
        //申购状态改变推送
        virtual void PurchaseStatusPush(const MapPurchaseStatus& mapPStatus) = 0;
        //确认申购返回
        virtual void ConfirmPurchaseRet(const std::string& sReqID, int nStatus) = 0; 
        //申购按钮是否显示推送
        virtual void ContactIsDealerPush(const Contact& ct, bool bRet) = 0;
        //申购编辑按钮是否显示推送
        virtual void IsEditPurchaseValidPush(const Contact& ct, bool bRet) = 0;
        //批量查询MM报价状态返回
        virtual void QueryMMQuotStatusRet(const std::string& sReqID, const LstQuotStatus& lstRet) = 0;
        //批量查询Bond报价(按代码)的状态返回
        virtual void QueryBondQuotByCodeStatusRet(const std::string& sReqID, const LstQuotStatus& lstRet) = 0;
        //通过QBAccount批量查询QMID, 返回MsgID用于和响应匹配
        virtual std::string QueryQMIDByQBAccount(const SetString& setQBAccount) = 0;
        //查询当前设置的QM提醒, 返回MsgID用于和响应匹配
        virtual std::string QueryQMRemindConfig() = 0;
        //新增QM关键字提醒, 返回MsgID用于和响应匹配
        virtual std::string AddQMRemindKeyItem(const QMRemindKeyItem& Item) = 0;
        //修改QM关键字提醒, 返回MsgID用于和响应匹配
        virtual std::string ModifyQMRemindKeyItem(const QMRemindKeyItem& Item) = 0;
        //删除QM关键字提醒, 返回MsgID用于和响应匹配
        virtual std::string DelQMRemindKeyItem(const SetString& setID) = 0;
        //新增QM好友提醒, 返回MsgID用于和响应匹配
        virtual std::string AddQMRemindFriendItem(const QMRemindFriendItem& Item) = 0;
        //修改QM好友提醒, 返回MsgID用于和响应匹配
        virtual std::string ModifyQMRemindFriendItem(const QMRemindFriendItem& Item) = 0;
        //删除QM好友提醒, 返回MsgID用于和响应匹配
        virtual std::string DelQMRemindFriendItem(const SetString& setID) = 0;
        //设置QM提醒方式, 返回MsgID用于和响应匹配
        virtual std::string SetQMRemindType(unsigned int nRemindType) = 0;
        //打开新闻资讯
        virtual bool OpenNewsBulletin(const std::string& sWndID = "") = 0;
        //查询客服
        virtual bool QueryCustomService(Contact& ct, int timeout = -1) = 0;
        //QB修改密码
        virtual void QBModifyPwd(const std::string& sNewPwd) = 0;
        //向指定用户分享债券
        virtual bool ShareBond(const LstContact& Contacts, const LstBondShare& lstBS, const std::string& sWndID = "") = 0;
        //申请入群group
        virtual std::string ReqJoinGroup(const unsigned long long &llGroup) = 0;
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
        virtual void ReqOpenSellsWnd(const std::string& sWndID = "") = 0;
        //查询QM非合作机构联系人接口 status表示查询是否成功 (0=成功;1=错误)
        virtual void ReqQueryNoInstituteContact(LstNoInstituteContact &contacts, int &status, int timeout = -1) = 0;
        //设置QM非合作机构联系人接口
        virtual void ReqSetNoInstituteContact(const std::list<std::string> &QBAccounts) = 0;
        //调用QM承销商界面中的点击管理后弹出的查找窗口
        virtual void ReqOpenSellsSearchWnd(const std::string& sWndID = "") = 0;
	};
}

QB_QM_API QB_QM::IQBToQM* GetQBToQM();

