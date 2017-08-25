#pragma once
#include "../SSTool.h"
#include "../sdbus/message.h"
#include "QB_QMDefine.h"
using namespace QB_QM;

#define  MSGCMD_QuitQM "quitqm"
#define  MSGCMD_MM_SelContacts "mm.quotation.selcontacts"
#define  MSGCMD_MM_SelContactsRet "mm.quotation.selcontactsret"
#define  MSGCMD_MM_EditContacts "mm.quotation.editcontacts"
#define  MSGCMD_MM_EditContactsRet "mm.quotation.editcontactsret"
#define  MSGCMD_MM_SendQuot "mm.quotation.sendquot"
#define  MSGCMD_MM_SendQuotRet "mm.quotation.sendquotret"
#define  MSGCMD_MM_SendQuotV2 "mm.quotation.sendquotv2"
#define  MSGCMD_MM_SendQuotRetV2 "mm.quotation.sendquotretv2"
#define  MSGCMD_MM_RecvQuot "mm.quotation.recvquot"
#define  MSGCMD_MM_QueryContactInfo "mm.quotation.queryctinfo"
#define  MSGCMD_MM_QueryContactInfoRet "mm.quotation.queryctinforet"
#define  MSGCMD_RequestBondInfos "requestbondinfos"
#define  MSGCMD_RequestBondInfosRet "requestbondinfosret"
#define  MSGCMD_ShowDlgBondDetail "showdlgbonddetail"
#define  MSGCMD_OpenMainPanel "openmainpanel"
#define  MSGCMD_RefreshBondInfos "refreshbondinfos"
#define  MSGCMD_OpenDialogue "opendialogue"
#define  MSGCMD_RecvMsgs "recvmsgs"
#define  MSGCMD_ReadMsgsOfContact "readmsgsofcontact"
#define  MSGCMD_BOND_SendQuotByCode "bond.sendquotbycode"
#define  MSGCMD_BOND_SendQuotByCodeRet "bond.sendquotbycoderet"
#define  MSGCMD_BOND_SendQuotByCodeV2 "bond.sendquotbycodev2"
#define  MSGCMD_BOND_SendQuotByCodeRetV2 "bond.sendquotbycoderetv2"
#define  MSGCMD_BOND_ReplyQuotByCode "bond.replyquotbycode"
#define  MSGCMD_BOND_SendQuotByCondition "bond.sendquotbycondition"
#define  MSGCMD_BOND_SendQuotByConditionRet "bond.sendquotbyconditionret"
#define  MSGCMD_MM_RecvQuot "mm.quotation.recvquot"
#define  MSGCMD_MM_ReplyQuot "mm.quotation.replyquot"
#define  MSGCMD_QueryCurUsrID "querycurusrid"
#define  MSGCMD_QueryCurUsrIDRet "querycurusridret"
#define  MSGCMD_QueryCurUsrFriendIDs "querycurusrfriendids"
#define  MSGCMD_QueryCurUsrFriendIDsRet "querycurusrfriendidsret"
#define  MSGCMD_QueryCurUsrGroupIDs "querycurusrgroupids"
#define  MSGCMD_QueryCurUsrGroupIDsRet "querycurusrgroupidsret"
#define  MSGCMD_CurUsrGroupChange "curusrgroupchange"
#define  MSGCMD_CurUsrFriendChange "curusrfriendchange"
#define  MSGCMD_GroupDisband "groupdisband"
#define  MSGCMD_SendMsg "sendmsg"
#define  MSGCMD_QueryQBWndPos "queryqbwndpos"
#define  MSGCMD_QueryQBWndPosRet "queryqbwndposret"
#define  MSGCMD_QueryQMWndPos "queryqmwndpos"
#define  MSGCMD_QueryQMWndPosRet "queryqmwndposret"
#define  MSGCMD_QueryQBWndHandle "queryqbwndhandle"
#define  MSGCMD_QueryQBWndHandleRet "queryqbwndhandleret"
#define  MSGCMD_QueryQMWndHandle "queryqmwndhandle"
#define  MSGCMD_QueryQMWndHandleRet "queryqmwndhandleret"
#define  MSGCMD_QueryQBPerm "queryqbperm"
#define  MSGCMD_QueryQBPermRet "queryqbpermret"
#define  MSGCMD_OpenMMQuot "openmmquot"
#define  MSGCMD_QuotShare_QueryShareGroup "quotshare.querysharegroup"
#define  MSGCMD_QuotShare_QueryShareGroupRet "quotshare.querysharegroupret"
#define  MSGCMD_SearchQMContact "searchqmcontact"
#define  MSGCMD_SearchQMContactRet "searchqmcontactret"
#define  MSGCMD_ContactIsDealer "contactisdealer"
#define  MSGCMD_ContactIsDealerRet "contactisdealerret"
#define  MSGCMD_OpenSubscribeDlg "opensubscribedlg"
#define  MSGCMD_GetAllDealer "getalldealer"
#define  MSGCMD_GetAllDealerRet "getalldealerret"
#define  MSGCMD_QMErrInfo "qmerrinfo"
#define  MSGCMD_Purchase_Send "purchase.send"
#define  MSGCMD_Purchase_QueryStatus "purchase.querystatus"
#define  MSGCMD_Purchase_QueryStatusRet "purchase.querystatusret"
#define  MSGCMD_Purchase_Confirm "purchase.confirm"
#define  MSGCMD_Purchase_ConfirmRet "purchase.confirmret"
#define  MSGCMD_Purchase_IsEditValid "purchase.iseditvalid"
#define  MSGCMD_Purchase_IsEditValidRet "purchase.iseditvalidret"
#define  MSGCMD_Purchase_Edit "purchase.edit"
#define  MSGCMD_Purchase_StatusPush "purchase.statuspush"
#define  MSGCMD_MM_QueryQuotStatus "mm.quotation.querystatus"
#define  MSGCMD_MM_QueryQuotStatusRet "mm.quotation.querystatusret"
#define  MSGCMD_Bond_QueryQuotByCodeStatus "bond.queryquotbycodestatus"
#define  MSGCMD_Bond_QueryQuotByCodeStatusRet "bond.queryquotbycodestatusret"
#define  MSGCMD_Purchase_IsEditValidPush "purchase.iseditvalidpush"
#define  MSGCMD_ContactIsDealerPush "contactisdealerpush" 
#define  MSGCMD_ContactInfoPush "contactinfopush"
#define  MSGCMD_ContactStatusPush "contactstatuspush"
#define  MSGCMD_QueryQMIDByQBAccount "queryqmidbyqbaccount"
#define  MSGCMD_QueryQMIDByQBAccountRet "queryqbidbyqbaccountret"
#define  MSGCMD_Remind_QueryQMRemindConfig "queryqmremindconfig"
#define  MSGCMD_Remind_QueryQMRemindConfigRet "queryqmremindconfigret"
#define  MSGCMD_Remind_SetQMRemindConfig "setqmremindconfig"
#define  MSGCMD_Remind_AddQMRemindKeyItem "addqmremindkeyitem"
#define  MSGCMD_Remind_AddQMRemindKeyItemRet "addqmremindkeyitemret"
#define  MSGCMD_Remind_ModifyQMRemindKeyItem "modifyqmremindkeyitem"
#define  MSGCMD_Remind_ModifyQMRemindKeyItemRet "modifyqmremindkeyitemret"
#define  MSGCMD_Remind_DelQMRemindKeyItem "delqmremindkeyitem"
#define  MSGCMD_Remind_DelQMRemindKeyItemRet "delqmremindkeyitemret"
#define  MSGCMD_Remind_AddQMRemindFriendItem "addqmremindfrienditem"
#define  MSGCMD_Remind_AddQMRemindFriendItemRet "addqmremindfrienditemret"
#define  MSGCMD_Remind_ModifyQMRemindFriendItem "modifyqmremindfrienditem"
#define  MSGCMD_Remind_ModifyQMRemindFriendItemRet "modifyqmremindfrienditemret"
#define  MSGCMD_Remind_DelQMRemindFriendItem "delqmremindfrienditem"
#define  MSGCMD_Remind_DelQMRemindFriendItemRet "delqmremindfrienditemret"
#define  MSGCMD_Remind_SetQMRemindType "setqmremindtype"
#define  MSGCMD_Remind_SetQMRemindTypeRet "setqmremindtyperet"
#define  MSGCMD_OpenNewsBulletin "opennewsbulletin"
#define  MSGCMD_QueryCustomService "querycustomservice"
#define  MSGCMD_QueryCustomServiceRet "querycustomserviceret"
#define  MSGCMD_QBModifyPwd "qbmodifypwd"
#define  MSGCMD_ShareBond "sharebond"
#define  MSGCMD_ReqJoinGroup "reqjoingroup"
#define  MSGCMD_ReqJoinGroupRet "reqjoingroupret"
#define  MSGCMD_ReqOpenNews "reqopennews"
#define  MSGCMD_SharePic "sharepic"
#define  MSGCMD_ReqOpenNewsDetail "reqopennewsdetail"
#define  MSGCMD_ReqOpenNewsWnd "reqopennewswnd"
#define  MSGCMD_ShareNewsDetail "sharenewsdetail"
#define  MSGCMD_OpenDialogueByUserID "opendialoguebyuserid"
#define  MSGCMD_QueryQMStatus "queryqmstatus"
#define  MSGCMD_QueryQMStatusRet "queryqmstatusret"
#define  MSGCMD_ReqOpenSellsWnd "reqopensellswnd"
#define  MSGCMD_ReqQueryNoInstituteContact "reqquerynoinstitutecontact"
#define  MSGCMD_ReqQueryNoInstituteContactRet "reqquerynoinstitutecontactret"
#define  MSGCMD_ReqSetNoInstituteContact "reqsetnoinstitutecontact"
#define  MSGCMD_ReqOpenSellsSearchWnd "reqopensellssearchwnd"
#define  MSGCMD_ModifyNoInstituteContactRet "modifynoinstitutecontactret"

namespace ss
{
	class logger;
}


class CMsgMng : public ss_tool::SingletonTmpl<CMsgMng>
{
	friend class ss_tool::SingletonTmpl<CMsgMng>;
protected:
	CMsgMng(void);
public:
	~CMsgMng(void);

	void GetMsg_QuitQM(bool bChkSession, const std::string& sSessionID, sdbus::Message& msg);
	void ParseMsg_QuitQM(const sdbus::Message& msg, bool& bChkSession, std::string& sSessionID);

	void GetMsg_OpenMainPanel(const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_OpenMainPanel(const sdbus::Message& msg, std::string& sWndID);

	void GetMsg_SelContacts(const std::string& sSelID, const std::string& sWndID, int nLimit, bool bShowGrp, sdbus::Message& msg);
	void ParseMsg_SelContacts(const sdbus::Message& msg, std::string& sSelID, std::string& sWndID, int& nLimit, bool& bShowGrp);
	void GetMsg_SelContactsRet(const std::string& sSelID, const LstContact& Contacts, sdbus::Message& msg);
	void ParseMsg_SelContactsRet(const sdbus::Message& msg, std::string& sSelID, LstContact& Contacts);

	void GetMsg_EditContacts(const std::string& sEditID, const LstContact& Contacts, const std::string& sWndID, int nLimit, bool bShowGrp, sdbus::Message& msg);
	void ParseMsg_EditContacts(const sdbus::Message& msg, std::string& sEditID, LstContact& Contacts, std::string& sWndID, int& nLimit, bool& bShowGrp);
	void GetMsg_EditContactsRet(const std::string& sEditID, const LstContact& Contacts, sdbus::Message& msg);
	void ParseMsg_EditContactsRet(const sdbus::Message& msg, std::string& sEditID, LstContact& Contacts);

	void GetMsg_SendQuot(const LstQuotSendInfo& lstSend, sdbus::Message& msg);
	void ParseMsg_SendQuot(const sdbus::Message& msg, LstQuotSendInfo& lstSend);
    void GetMsg_SendQuotRet(const LstQuotSendInfo& lstSuccess, const LstQuotSendInfo& lstFailed, sdbus::Message& msg);
    void ParseMsg_SendQuotRet(const sdbus::Message& msg, LstQuotSendInfo& lstSuccess, LstQuotSendInfo& lstFailed);

    void GetMsg_SendQuotV2(const LstMMQuotSendInfoV2& lstSend, sdbus::Message& msg);
    void ParseMsg_SendQuotV2(const sdbus::Message& msg, LstMMQuotSendInfoV2& lstSend);
    void GetMsg_SendQuotRetV2(const Contact& ct, const SetString& Success, const SetString& Failed, sdbus::Message& msg);
    void ParseMsg_SendQuotRetV2(const sdbus::Message& msg, Contact& ct, SetString& Success, SetString& Failed);

	void GetMsg_RecvQuot(const LstQuotRecvInfo& lstIn, sdbus::Message& msg);
	void ParseMsg_RecvQuot(const sdbus::Message& msg, LstQuotRecvInfo& lstOut);

	void GetMsg_ReplyQuot(const QuotReplyInfo& ItemIn, const std::string& sWndID, sdbus::Message& msg);
	void ParseMsg_ReplyQuot(const sdbus::Message& msg, QuotReplyInfo& ItemOut, std::string& sWndID);

	void GetMsg_QueryContactsInfo(const LstContact& lstIn, sdbus::Message& msg);
	void ParseMsg_QueryContactsInfo(const sdbus::Message& msg, LstContact& lstOut);
	void GetMsg_QueryContactsInfoRet(const LstPersonInfo& lstPerson, const LstGroupInfo& lstGrp, const LstContact& lstFailed, sdbus::Message& msg);
	void ParseMsg_QueryContactsInfoRet(const sdbus::Message& msg, LstPersonInfo& lstPerson, LstGroupInfo& lstGrp, LstContact& lstFailed);

	void GetMsg_RequestBondInfos(sdbus::Message& msg);
	void GetMsg_RequestBondInfosRet(const LstBondItem& lstIn, sdbus::Message& msg);
	void ParseMsg_RequestBondInfosRet(const sdbus::Message& msg, LstBondItem& lstOut);

	void GetMsg_ShowDlgBondDetail(const std::string& sBondKey, sdbus::Message& msg);
	void ParseMsg_ShowDlgBondDetail(const sdbus::Message& msg, std::string& sBondKey);

	void GetMsg_RefreshBondInfos(sdbus::Message& msg);

	void GetMsg_OpenDialogue(const Contact& ct, const std::string& sSendMsg, const std::string& sWndID, const bool bOpen, sdbus::Message& msg);
	void ParseMsg_OpenDialogue(const sdbus::Message& msg, Contact& ct, std::string& sSendMsg, std::string& sWndID, bool &bOpen);

	void GetMsg_SendBondQuotByCode(const LstBondQuotByCodeSendInfo& lstIn, sdbus::Message& msg);
	void ParseMsg_SendBondQuotByCode(const sdbus::Message& msg, LstBondQuotByCodeSendInfo& lstOut);
	void GetMsg_SendBondQuotByCodeRet(const LstBondQuotByCodeSendInfo& lstSuccess, const LstBondQuotByCodeSendInfo& lstFailed, sdbus::Message& msg);
	void ParseMsg_SendBondQuotByCodeRet(const sdbus::Message& msg, LstBondQuotByCodeSendInfo& lstSuccess, LstBondQuotByCodeSendInfo& lstFailed);

    void GetMsg_SendBondQuotByCodeV2(const LstBondQuotByCodeSendInfoV2& lstIn, sdbus::Message& msg);
    void ParseMsg_SendBondQuotByCodeV2(const sdbus::Message& msg, LstBondQuotByCodeSendInfoV2& lstOut);
    void GetMsg_SendBondQuotByCodeRetV2(const Contact& ct, const SetString& Success, const SetString& Failed, sdbus::Message& msg);
    void ParseMsg_SendBondQuotByCodeRetV2(const sdbus::Message& msg, Contact& ct, SetString& Success, SetString& Failed);

    void GetMsg_ReplyBondQuotByCode(const BondQuotByCodeReplyInfo& ItemIn, const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_ReplyBondQuotByCode(const sdbus::Message& msg, BondQuotByCodeReplyInfo& ItemOut, std::string& sWndID); 

	void GetMsg_SendBondQuotByCondition(const LstBondQuotByConditionSendInfo& lstIn, sdbus::Message& msg);
	void ParseMsg_SendBondQuotByCondition(const sdbus::Message& msg, LstBondQuotByConditionSendInfo& lstOut);
	void GetMsg_SendBondQuotByConditionRet(const LstBondQuotByConditionSendInfo& lstSuccess, const LstBondQuotByConditionSendInfo& lstFailed, sdbus::Message& msg);
	void ParseMsg_SendBondQuotByConditionRet(const sdbus::Message& msg, LstBondQuotByConditionSendInfo& lstSuccess, LstBondQuotByConditionSendInfo& lstFailed);

	void GetMsg_QueryCurUsrID(sdbus::Message& msg);
	void GetMsg_QueryCurUsrIDRet(unsigned long long UsrID, sdbus::Message& msg);
	void ParseMsg_QueryCurUsrIDRet(const sdbus::Message& msg, unsigned long long& UsrID);

	void GetMsg_QueryCurUsrFriendIDs(sdbus::Message& msg);
	void GetMsg_QueryCurUsrFriendIDsRet(const SetUInt64& setIn, sdbus::Message& msg);
	void ParseMsg_QueryCurUsrFriendIDsRet(const sdbus::Message& msg, SetUInt64& setRet);

	void GetMsg_QueryCurUsrGroupIDs(sdbus::Message& msg);
	void GetMsg_QueryCurUsrGroupIDsRet(const SetUInt64& setIn, sdbus::Message& msg);
	void ParseMsg_QueryCurUsrGroupIDsRet(const sdbus::Message& msg, SetUInt64& setRet);

	void GetMsg_CurUsrGroupChange(const SetUInt64& JoinGrpIDs, const SetUInt64& LeaveGrpIDs, sdbus::Message& msg);
	void ParseMsg_CurUsrGroupChange(const sdbus::Message& msg, SetUInt64& JoinGrpIDs, SetUInt64& LeaveGrpIDs);

    void GetMsg_CurUsrFriendChange(const SetUInt64& AddFriendIDs, const SetUInt64& DelFriendIDs, sdbus::Message& msg);
    void ParseMsg_CurUsrFriendChange(const sdbus::Message& msg, SetUInt64& AddFriendIDs, SetUInt64& DelFriendIDs);

	void GetMsg_GroupDisband(unsigned long long GrpID, sdbus::Message& msg);
	void ParseMsg_GroupDisband(const sdbus::Message& msg, unsigned long long& GrpID);

	void GetMsg_SendMsg(const LstContact& lstCt, const std::string& sSendMsg, const std::string& sWndID, sdbus::Message& msg);
	void ParseMsg_SendMsg(const sdbus::Message& msg, LstContact& lstCt, std::string& sSendMsg, std::string& sWndID);

    void GetMsg_QueryQBWndPos(const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_QueryQBWndPos(const sdbus::Message& msg, std::string& sWndID);
    void GetMsg_QueryQBWndPosRet(int nTop, int nBottom, int nLeft, int nRight, sdbus::Message& msg);
    void ParseMsg_QueryQBWndPosRet(const sdbus::Message& msg, int& nTop, int& nBottom, int& nLeft, int& nRight);

    void GetMsg_QueryQMWndPos(const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_QueryQMWndPos(const sdbus::Message& msg, std::string& sWndID);
    void GetMsg_QueryQMWndPosRet(int nTop, int nBottom, int nLeft, int nRight, sdbus::Message& msg);
    void ParseMsg_QueryQMWndPosRet(const sdbus::Message& msg, int& nTop, int& nBottom, int& nLeft, int& nRight);

    void GetMsg_QueryQBWndHandle(const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_QueryQBWndHandle(const sdbus::Message& msg, std::string& sWndID);
    void GetMsg_QueryQBWndHandleRet(HWND hWnd, sdbus::Message& msg);
    void ParseMsg_QueryQBWndHandleRet(const sdbus::Message& msg, unsigned long long& hWnd);

    void GetMsg_QueryQMWndHandle(const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_QueryQMWndHandle(const sdbus::Message& msg, std::string& sWndID);
    void GetMsg_QueryQMWndHandleRet(unsigned long long hWnd, sdbus::Message& msg);
    void ParseMsg_QueryQMWndHandleRet(const sdbus::Message& msg, HWND& hWnd);

    void GetMsg_QueryQBPerm(sdbus::Message& msg);
    void GetMsg_QueryQBPermRet(const SetString& setPerm, sdbus::Message& msg);
    void ParseMsg_QueryQBPermRet(const sdbus::Message& msg, SetString& setPerm);

    void GetMsg_OpenMMQuot(const LstContact& lstCt, const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_OpenMMQuot(const sdbus::Message& msg, LstContact& lstCt, std::string& sWndID);

    void GetMsg_QueryShareGroup(sdbus::Message& msg);
    void GetMsg_QueryShareGroupRet(const Contact& ct, sdbus::Message& msg);
    void ParseMsg_QueryShareGroupRet(const sdbus::Message& msg, Contact& ct);

    void GetMsg_SearchQMContact(const ContactSearch& SearchInput, sdbus::Message& msg);
    void ParseMsg_SearchQMContact(const sdbus::Message& msg, ContactSearch& SearchInput);
    void GetMsg_SearchQMContactRet(const LstSearchUserInfo& Result, sdbus::Message& msg);
    void ParseMsg_SearchQMContactRet(const sdbus::Message& msg, LstSearchUserInfo& Result);

    void GetMsg_ContactIsDealer(const Contact& ct, sdbus::Message& msg);
    void ParseMsg_ContactIsDealer(const sdbus::Message& msg, Contact& ct);
    void GetMsg_ContactIsDealerRet(bool isDealer, sdbus::Message& msg);
    void ParseMsg_ContactIsDealerRet(const sdbus::Message& msg, bool& isDealer);

    void GetMsg_OpenSubscribeDlg(const Contact& ct, const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_OpenSubscribeDlg(const sdbus::Message& msg, Contact& ct, std::string& sWndID);

    void GetMsg_GetAllDealer(sdbus::Message& msg);
    void GetMsg_GetAllDealerRet(const SetUInt64& setIn, sdbus::Message& msg);
    void ParseMsg_GetAllDealerRet(const sdbus::Message& msg, SetUInt64& setRet);

    void GetMsg_QMErrInfo(int nCode, const std::string& sInfo, sdbus::Message& msg);
    void ParseMsg_QMErrInfo(const sdbus::Message& msg, int& nCode, std::string& sInfo);

    void GetMsg_Purchase(const Contact& Ct, const PurchaseInfo& PInfo, const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_Purchase(const sdbus::Message& msg, Contact& Ct, PurchaseInfo& PInfo, std::string& sWndID);

    void GetMsg_QueryPurchaseStatus(const LstPurchaseUkey& lstQuery, sdbus::Message& msg);
    void ParseMsg_QueryPurchaseStatus(const sdbus::Message& msg, LstPurchaseUkey& lstQuery);
    void GetMsg_QueryPurchaseStatusRet(const MapPurchaseStatus& mapPStatus, sdbus::Message& msg);
    void ParseMsg_QueryPurchaseStatusRet(const sdbus::Message& msg, MapPurchaseStatus& mapPStatus);

    void GetMsg_ConfirmPurchase(const std::string& sPurchaseID, time_t ModifyTime, sdbus::Message& msg);
    void ParseMsg_ConfirmPurchase(const sdbus::Message& msg, std::string& sPurchaseID, time_t& ModifyTime);
    void GetMsg_ConfirmPurchaseRet(int nStatus, sdbus::Message& msg);
    void ParseMsg_ConfirmPurchaseRet(const sdbus::Message& msg, int& nStatus);

    void GetMsg_IsEditPurchaseValid(const Contact& ct, sdbus::Message& msg);
    void ParseMsg_IsEditPurchaseValid(const sdbus::Message& msg, Contact& ct);
    void GetMsg_IsEditPurchaseValidRet(bool bValid, sdbus::Message& msg);
    void ParseMsg_IsEditPurchaseValidRet(const sdbus::Message& msg, bool& bValid);

    void GetMsg_EditPurchase(const Contact& ct, const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_EditPurchase(const sdbus::Message& msg, Contact& ct, std::string& sWndID);

    void GetMsg_QueryMMQuotStatus(const LstQuotStatusReq& lstReq, sdbus::Message& msg);
    void ParseMsg_QueryMMQuotStatus(const sdbus::Message& msg, LstQuotStatusReq& lstReq);
    void GetMsg_QueryMMQuotStatusRet(const LstQuotStatus& lstRet, sdbus::Message& msg);
    void ParseMsg_QueryMMQuotStatusRet(const sdbus::Message& msg, LstQuotStatus& lstRet);

    void GetMsg_QueryBondQuotByCodeStatus(const LstQuotStatusReq& lstReq, sdbus::Message& msg);
    void ParseMsg_QueryBondQuotByCodeStatus(const sdbus::Message& msg, LstQuotStatusReq& lstReq);
    void GetMsg_QueryBondQuotByCodeStatusRet(const LstQuotStatus& lstRet, sdbus::Message& msg);
    void ParseMsg_QueryBondQuotByCodeStatusRet(const sdbus::Message& msg, LstQuotStatus& lstRet);

    void GetMsg_PurchaseStatusPush(const MapPurchaseStatus& mapPStatus, sdbus::Message& msg);
    void ParseMsg_PurchaseStatusPush(const sdbus::Message& msg, MapPurchaseStatus& mapPStatus);

    void GetMsg_IsEditPurchaseValidPush(const Contact& ct, bool bValid, sdbus::Message& msg);
    void ParseMsg_IsEditPurchaseValidPush(const sdbus::Message& msg, Contact& ct, bool& bValid);

    void GetMsg_ContactIsDealerPush(const Contact& ct, bool isDealer, sdbus::Message& msg);
    void ParseMsg_ContactIsDealerPush(const sdbus::Message& msg, Contact& ct, bool& isDealer);

    void GetMsg_ContactInfoPush(const LstPersonInfo& PersonInfos, const LstGroupInfo& GrpInfos, sdbus::Message& msg);
    void ParseMsg_ContactInfoPush(const sdbus::Message& msg, LstPersonInfo& PersonInfos, LstGroupInfo& GrpInfos);

    void GetMsg_ContactStatusPush(const LstContactStatus& lstStatus, sdbus::Message& msg);
    void ParseMsg_ContactStatusPush(const sdbus::Message& msg, LstContactStatus& lstStatus);

    void GetMsg_QueryQMIDByQBAccount(const SetString& QBAccounts, sdbus::Message& msg);
    void ParseMsg_QueryQMIDByQBAccount(const sdbus::Message& msg, SetString& QBAccounts);
    void GetMsg_QueryQMIDByQBAccountRet(const LstQBAccount2QMID& lstInfo, sdbus::Message& msg);
    void ParseMsg_QueryQMIDByQBAccountRet(const sdbus::Message& msg, LstQBAccount2QMID& lstInfo);

    void GetMsg_QueryQMRemindConfig(sdbus::Message& msg);
    void BuildQueryQMRemindConfigRet(const QMRemindConfig& QMRCfg, sdbus::Message& msg);
    void ParseQueryQMRemindConfigRet(const sdbus::Message& msg, QMRemindConfig& QMRCfg);

    //感觉两个函数多余...
    void GetMsg_SetQMRemindConfig(const QMRemindConfig& QMRCfg, sdbus::Message& msg);
    void ParseMsg_SetQMRemindConfig(const sdbus::Message& msg, QMRemindConfig& QMRCfg);

    void GetMsg_AddQMRemindKeyItem(const QMRemindKeyItem& Item, sdbus::Message& msg);
    void ParseMsg_AddQMRemindKeyItem(const sdbus::Message& msg, QMRemindKeyItem& Item);
    void GetMsg_AddQMRemindKeyItemRet(const std::string& ItemID, sdbus::Message& msg);
    void ParseMsg_AddQMRemindKeyItemRet(const sdbus::Message& msg, std::string& ItemID);

    void GetMsg_ModifyQMRemindKeyItem(const QMRemindKeyItem& Item, sdbus::Message& msg);
    void ParseMsg_ModifyQMRemindKeyItem(const sdbus::Message& msg, QMRemindKeyItem& Item);
    void GetMsg_ModifyQMRemindKeyItemRet(bool bSuccess, sdbus::Message& msg);
    void ParseMsg_ModifyQMRemindKeyItemRet(const sdbus::Message& msg, bool& bSuccess);

    void GetMsg_DelQMRemindKeyItem(const SetString& setID, sdbus::Message& msg);
    void ParseMsg_DelQMRemindKeyItem(const sdbus::Message& msg, SetString& setID);
    void GetMsg_DelQMRemindKeyItemRet(const SetString& setSuccessID, sdbus::Message& msg);
    void ParseMsg_DelQMRemindKeyItemRet(const sdbus::Message& msg, SetString& setSuccessID);

    void GetMsg_AddQMRemindFriendItem(const QMRemindFriendItem& Item, sdbus::Message& msg);
    void ParseMsg_AddQMRemindFriendItem(const sdbus::Message& msg, QMRemindFriendItem& Item);
    void GetMsg_AddQMRemindFriendItemRet(const std::string& ItemID, sdbus::Message& msg);
    void ParseMsg_AddQMRemindFriendItemRet(const sdbus::Message& msg, std::string& ItemID);

    void GetMsg_ModifyQMRemindFriendItem(const QMRemindFriendItem& Item, sdbus::Message& msg);
    void ParseMsg_ModifyQMRemindFriendItem(const sdbus::Message& msg, QMRemindFriendItem& Item);
    void GetMsg_ModifyQMRemindFriendItemRet(bool bSuccess, sdbus::Message& msg);
    void ParseMsg_ModifyQMRemindFriendItemRet(const sdbus::Message& msg, bool& bSuccess);

    void GetMsg_DelQMRemindFriendItem(const SetString& setID, sdbus::Message& msg);
    void ParseMsg_DelQMRemindFriendItem(const sdbus::Message& msg, SetString& setID);
    void GetMsg_DelQMRemindFriendItemRet(const SetString& setSuccessID, sdbus::Message& msg);
    void ParseMsg_DelQMRemindFriendItemRet(const sdbus::Message& msg, SetString& setSuccessID);

    void GetMsg_SetQMRemindType(unsigned int nRemindType, sdbus::Message& msg);
    void ParseMsg_SetQMRemindType(const sdbus::Message& msg, unsigned int& nRemindType);
    void GetMsg_SetQMRemindTypeRet(bool bSuccess, sdbus::Message& msg);
    void ParseMsg_SetQMRemindTypeRet(const sdbus::Message& msg, bool& bSuccess);

    void GetMsg_OpenNewsBulletin(const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_OpenNewsBulletin(const sdbus::Message& msg, std::string& sWndID);

    void GetMsg_QueryCustomService(sdbus::Message& msg);
    void GetMsg_QueryCustomServiceRet(const Contact& ct, sdbus::Message& msg);
    void ParseMsg_QueryCustomServiceRet(const sdbus::Message& msg, Contact& ct);

    void GetMsg_QBModifyPwd(const std::string& sNewPwd, sdbus::Message& msg);
    void ParseMsg_QBModifyPwd(const sdbus::Message& msg, std::string& sNewPwd);

    void GetMsg_ShareBond(const LstContact& lstCt, const LstBondShare& lstBS, const std::string& sWndID, sdbus::Message& msg);
    void ParseMsg_ShareBond(const sdbus::Message& msg, LstContact& lstCt, LstBondShare& lstBS, std::string& sWndID);


    void BuildReqJoinGroup(const unsigned long long &llGroup, sdbus::Message &msg);
    void ParseReqJoinGroup(const sdbus::Message &msg, unsigned long long &llGroup);
    void BuildJoinGroupRet(bool bSuccess, sdbus::Message &msg);
    void ParseJoinGroupRet(const sdbus::Message &msg, bool &bSuccess);

	void BuildReqOpenNews(const NewsInfo &info, sdbus::Message &msg);
	void ParseReqOpenNews(const sdbus::Message &msg, NewsInfo &info);

    void BuildSharePic(const PicInfo &info, const LstContact &lstCt, sdbus::Message &msg);
    void ParseSharePic(const sdbus::Message &msg, PicInfo &info, LstContact &lstCt);

    void BuildReqOpenNewsDetail(const NewsInfoV2 &info, const bool bDisablePDF, sdbus::Message &msg);
    void ParseReqOpenNewsDetail(const sdbus::Message &msg, NewsInfoV2 &info, bool &bDisablePDF);

    void BuildReqOpenNewsWnd(sdbus::Message &msg);
    void ParseReqOpenNewsWnd(const sdbus::Message &msg);

    void BuildShareNewsDetail(const NewsInfoV2 &info, const LstContact& Contacts, bool bDisablePDF, sdbus::Message &msg);
    void ParseShareNewsDetail(const sdbus::Message &msg, NewsInfoV2 &info, LstContact& Contacts, bool &bDisablePDF);
    void BuildOpenDialogueByUserID(const std::string &userID, sdbus::Message &msg);
    void ParseOpenDialogueByUserID(const sdbus::Message &msg, std::string &userID);
    void BuildQueryQMStatusRet(int status, sdbus::Message &msg);
    void ParseQueryQMStatusRet(const sdbus::Message &msg, int &status);

    void BuildReqOpenSellsWnd(const std::string& sWndID, sdbus::Message &msg);
    void ParseReqOpenSellsWnd(const sdbus::Message &msg, std::string& sWndID);

    void BuildReqQueryNoInstituteContact(sdbus::Message &msg);
    void ParseReqQueryNoInstituteContact(const sdbus::Message &msg);
    void BuildReqQueryNoInstituteContactRet(const LstNoInstituteContact &contacts, int status, sdbus::Message &msg);
    void ParseReqQueryNoInstituteContactRet(const sdbus::Message &msg, LstNoInstituteContact &contacts, int &status);

    void BuildReqSetNoInstituteContact(const std::list<std::string> &QBAccounts, sdbus::Message &msg);
    void ParseReqSetNoInstituteContact(const sdbus::Message &msg, std::list<std::string> &QBAccounts);

    void BuildModifyNoInstituteContactRet(const LstNoInstituteContact &contacts, sdbus::Message &msg);
    void ParseModifyNoInstituteContactRet(const sdbus::Message &msg, LstNoInstituteContact &contacts);

    void BuildReqOpenSellsSearchWnd(const std::string& sWndID, sdbus::Message &msg);
    void ParseReqOpenSellsSearchWnd(const sdbus::Message &msg, std::string& sWndID);
	/////////element build&parse/////////

	void BuildLstString(const std::list<std::string>& lstString, sdbus::Message::Map& mapRet);
	void ParseLstString(const sdbus::Message::Map& mapIn, std::list<std::string>& lstString);

	void BuildSetUInt64(const SetUInt64& setIn, sdbus::Message::Map& mapRet);
	void ParseSetUInt64(const sdbus::Message::Map& mapIn, SetUInt64& setRet);

    void BuildSetString(const SetString& setIn, sdbus::Message::Map& mapRet);
    void ParseSetString(const sdbus::Message::Map& mapIn, SetString& setRet);

	void BuildKeyValues(const KeyValues& kvIn, sdbus::Message::Map& mapRet);
	void ParseKeyValues(const sdbus::Message::Map& mapIn, KeyValues& kvRet);

	void BuildLstMultilanguageStr(const LstMultilanguageStr& lstIn, sdbus::Message::Map& mapRet);
	void BuildMultilanguageStr(const MultilanguageStr& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstMultilanguageStr(const sdbus::Message::Map& mapIn, LstMultilanguageStr& lstOut);
	void ParseMultilanguageStr(const sdbus::Message::Map& mapIn, MultilanguageStr& ItemOut);

	void BuildLstTermInfo(const LstTermInfo& lstIn, sdbus::Message::Map& mapRet);
	void BuildTermInfo(const TermInfo& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstTermInfo(const sdbus::Message::Map& mapIn, LstTermInfo& lstOut);
	void ParseTermInfo(const sdbus::Message::Map& mapIn, TermInfo& ItemOut);

	void BuildLstQuotation(const LstQuotation& lstQuot, sdbus::Message::Map& mapRet);
	void BuildQuotation(const Quotation& Quot, sdbus::Message::Map& mapRet);
	void ParseLstQuotation(const sdbus::Message::Map& mapIn, LstQuotation& lstQuot);
	void ParseQuotation(const sdbus::Message::Map& mapIn, Quotation& Quot);

	void BuildLstQuotationMngInfo(const LstQuotationMngInfo& lstQuotMngInfo, sdbus::Message::Map& mapRet);
	void BuildQuotationMngInfo(const QuotationMngInfo& QuotMngIngo, sdbus::Message::Map& mapRet);
	void ParseLstQuotationMngInfo(const sdbus::Message::Map& mapIn, LstQuotationMngInfo& lstQuotMngInfo);
	void ParseQuotationMngInfo(const sdbus::Message::Map& mapIn, QuotationMngInfo& QuotMngInfo);

	void BuildLstQuotSendInfo(const LstQuotSendInfo& lstIn, sdbus::Message::Map& mapRet);
	void BuildQuotSendInfo(const QuotSendInfo& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstQuotSendInfo(const sdbus::Message::Map& mapIn, LstQuotSendInfo& lstOut);
	void ParseQuotSendInfo(const sdbus::Message::Map& mapIn, QuotSendInfo& ItemOut);

	void BuildLstQuotRecvInfo(const LstQuotRecvInfo& lstIn, sdbus::Message::Map& mapRet);
	void BuildQuotRecvInfo(const QuotRecvInfo& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstQuotRecvInfo(const sdbus::Message::Map& mapIn, LstQuotRecvInfo& lstOut);
	void ParseQuotRecvInfo(const sdbus::Message::Map& mapIn, QuotRecvInfo& ItemOut);

	void BuildLstQuotReplyInfo(const LstQuotReplyInfo& lstIn, sdbus::Message::Map& mapRet);
	void BuildQuotReplyInfo(const QuotReplyInfo& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstQuotReplyInfo(const sdbus::Message::Map& mapIn, LstQuotReplyInfo& lstOut);
	void ParseQuotReplyInfo(const sdbus::Message::Map& mapIn, QuotReplyInfo& ItemOut);

	void BuildLstContact(const LstContact& lstIn, sdbus::Message::Map& mapRet);
	void BuildContact(const Contact& ct, sdbus::Message::Map& mapRet);
	void ParseLstContact(const sdbus::Message::Map& mapIn, LstContact& lstOut);
	void ParseContact(const sdbus::Message::Map& mapIn, Contact& ct);

	void BuildLstPersonInfo(const LstPersonInfo& lstIn, sdbus::Message::Map& mapRet);
	void BuildPersonInfo(const PersonInfo& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstPersonInfo(const sdbus::Message::Map& mapIn, LstPersonInfo& lstOut);
	void ParsePersonInfo(const sdbus::Message::Map& mapIn, PersonInfo& ItemOut);

	void BuildLstGroupInfo(const LstGroupInfo& lstIn, sdbus::Message::Map& mapRet);
	void BuildGroupInfo(const GroupInfo& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstGroupInfo(const sdbus::Message::Map& mapIn, LstGroupInfo& lstOut);
	void ParseGroupInfo(const sdbus::Message::Map& mapIn, GroupInfo& ItemOut);

	void BuildLstBondItem(const LstBondItem& lstIn, sdbus::Message::Map& mapRet);
	void BuildBondItem(const BondItem& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstBondItem(const sdbus::Message::Map& mapIn, LstBondItem& lstOut);
	void ParseBondItem(const sdbus::Message::Map& mapIn, BondItem& ItemOut);

	void BuildLstMsgInfo(const LstMsgInfo& lstIn, sdbus::Message::Map& mapRet);
	void BuildMsgInfo(const MsgInfo& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstMsgInfo(const sdbus::Message::Map& mapIn, LstMsgInfo& lstOut);
	void ParseMsgInfo(const sdbus::Message::Map& mapIn, MsgInfo& ItemOut);

	void BuildLstBondQuotInfo(const LstBondQuotInfo& lstIn, sdbus::Message::Map& mapRet);
	void BuildBondQuotInfo(const BondQuotInfo& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstBondQuotInfo(const sdbus::Message::Map& mapIn, LstBondQuotInfo& lstOut);
	void ParseBondQuotInfo(const sdbus::Message::Map& mapIn, BondQuotInfo& ItemOut);

	void BuildLstBondQuotByCode(const LstBondQuotByCode& lstIn, sdbus::Message::Map& mapRet);
	void BuildBondQuotByCode(const BondQuotByCode& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstBondQuotByCode(const sdbus::Message::Map& mapIn, LstBondQuotByCode& lstOut);
	void ParseBondQuotByCode(const sdbus::Message::Map& mapIn, BondQuotByCode& ItemOut);

	void BuildLstBondQuotByCodeSendInfo(const LstBondQuotByCodeSendInfo& lstIn, sdbus::Message::Map& mapRet);
	void BuildBondQuotByCodeSendInfo(const BondQuotByCodeSendInfo& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstBondQuotByCodeSendInfo(const sdbus::Message::Map& mapIn, LstBondQuotByCodeSendInfo& lstOut);
	void ParseBondQuotByCodeSendInfo(const sdbus::Message::Map& mapIn, BondQuotByCodeSendInfo& ItemOut);

	void BuildLstCondition(const LstCondition& lstIn, sdbus::Message::Map& mapRet);
	void BuildCondition(const Condition& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstCondition(const sdbus::Message::Map& mapIn, LstCondition& lstOut);
	void ParseCondition(const sdbus::Message::Map& mapIn, Condition& ItemOut);

	void BuildLstBondQuotByCondition(const LstBondQuotByCondition& lstIn, sdbus::Message::Map& mapRet);
	void BuildBondQuotByCondition(const BondQuotByCondition& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstBondQuotByCondition(const sdbus::Message::Map& mapIn, LstBondQuotByCondition& lstOut);
	void ParseBondQuotByCondition(const sdbus::Message::Map& mapIn, BondQuotByCondition& ItemOut);

	void BuildLstBondQuotByConditionSendInfo(const LstBondQuotByConditionSendInfo& lstIn, sdbus::Message::Map& mapRet);
	void BuildBondQuotByConditionSendInfo(const BondQuotByConditionSendInfo& ItemIn, sdbus::Message::Map& mapRet);
	void ParseLstBondQuotByConditionSendInfo(const sdbus::Message::Map& mapIn, LstBondQuotByConditionSendInfo& lstOut);
	void ParseBondQuotByConditionSendInfo(const sdbus::Message::Map& mapIn, BondQuotByConditionSendInfo& ItemOut);

    void BuildContactSearch(const ContactSearch& ItemIn, sdbus::Message::Map& mapRet);
    void ParseContactSearch(const sdbus::Message::Map& mapIn, ContactSearch& ItemOut);

    void BuildLstSearchUserInfo(const LstSearchUserInfo& lstIn, sdbus::Message::Map& mapRet);
    void BuildSearchUserInfo(const SearchUserInfo& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstSearchUserInfo(const sdbus::Message::Map& mapIn, LstSearchUserInfo& lstOut);
    void ParseSearchUserInfo(const sdbus::Message::Map& mapIn, SearchUserInfo& ItemOut);

    void BuildLstMMQuotSendInfoV2(const LstMMQuotSendInfoV2& lstIn, sdbus::Message::Map& mapRet);
    void BuildQuotSendInfoV2_MM(const QuotSendInfoV2_MM& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstMMQuotSendInfoV2(const sdbus::Message::Map& mapIn, LstMMQuotSendInfoV2& lstOut);
    void ParseQuotSendInfoV2_MM(const sdbus::Message::Map& mapIn, QuotSendInfoV2_MM& ItemOut);

    void BuildLstBondQuotByCodeSendInfoV2(const LstBondQuotByCodeSendInfoV2& lstIn, sdbus::Message::Map& mapRet);
    void BuildQuotSendInfoV2_BondByCode(const QuotSendInfoV2_BondByCode& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstBondQuotByCodeSendInfoV2(const sdbus::Message::Map& mapIn, LstBondQuotByCodeSendInfoV2& lstOut);
    void ParseQuotSendInfoV2_BondByCode(const sdbus::Message::Map& mapIn, QuotSendInfoV2_BondByCode& ItemOut);

    void BuildBondQuotByCodeReplyInfo(const BondQuotByCodeReplyInfo& ItemIn, sdbus::Message::Map& mapRet);
    void ParseBondQuotByCodeReplyInfo(const sdbus::Message::Map& mapIn, BondQuotByCodeReplyInfo& ItemOut);

    void BuildPurchaseInfo(const PurchaseInfo& ItemIn, sdbus::Message::Map& mapRet);
    void ParsePurchaseInfo(const sdbus::Message::Map& mapIn, PurchaseInfo& ItemOut);

    void BuildLstPurchaseUkey(const LstPurchaseUkey& lstIn, sdbus::Message::Map& mapRet);
    void BuildPurchaseUkey(const PurchaseUkey& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstPurchaseUkey(const sdbus::Message::Map& mapIn, LstPurchaseUkey& lstOut);
    void ParsePurchaseUkey(const sdbus::Message::Map& mapIn, PurchaseUkey& ItemOut);

    void BuildMapPurchaseStatus(const MapPurchaseStatus& mapIn, sdbus::Message::Map& mapRet);
    void BuildPairPurchaseStatus(const PurchaseUkey& ItemIn, int nStatus, sdbus::Message::Map& mapRet);
    void ParseMapPurchaseStatus(const sdbus::Message::Map& mapIn, MapPurchaseStatus& mapOut);
    void ParsePairPurchaseStatus(const sdbus::Message::Map& mapIn, PurchaseUkey& ItemOut, int& nStatus);

    void BuildLstQuotStatusReq(const LstQuotStatusReq& lstIn, sdbus::Message::Map& mapRet);
    void BuildQuotStatusReq(const QuotStatusReq& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstQuotStatusReq(const sdbus::Message::Map& mapIn, LstQuotStatusReq& lstOut);
    void ParseQuotStatusReq(const sdbus::Message::Map& mapIn, QuotStatusReq& ItemOut);

    void BuildLstQuotStatus(const LstQuotStatus& lstIn, sdbus::Message::Map& mapRet);
    void BuildQuotStatus(const QuotStatus& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstQuotStatus(const sdbus::Message::Map& mapIn, LstQuotStatus& lstOut);
    void ParseQuotStatus(const sdbus::Message::Map& mapIn, QuotStatus& ItemOut);

    void BuildLstContactStatus(const LstContactStatus& lstIn, sdbus::Message::Map& mapRet);
    void BuildContactStatus(const ContactStatus& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstContactStatus(const sdbus::Message::Map& mapIn, LstContactStatus& lstOut);
    void ParseContactStatus(const sdbus::Message::Map& mapIn, ContactStatus& ItemOut);

    void BuildLstQBAccount2QMID(const LstQBAccount2QMID& lstIn, sdbus::Message::Map& mapRet);
    void BuildQBAccount2QMID(const QBAccount2QMID& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstQBAccount2QMID(const sdbus::Message::Map& mapIn, LstQBAccount2QMID& lstOut);
    void ParseQBAccount2QMID(const sdbus::Message::Map& mapIn, QBAccount2QMID& ItemOut);

    void BuildLstQMRKey(const LstQMRKey& lstIn, sdbus::Message::Map& mapRet);
    void BuildQMRemindKeyItem(const QMRemindKeyItem& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstQMRKey(const sdbus::Message::Map& mapIn, LstQMRKey& lstOut);
    void ParseQMRemindKeyItem(const sdbus::Message::Map& mapIn, QMRemindKeyItem& ItemOut);

    void BuildLstQMRFriend(const LstQMRFriend& lstIn, sdbus::Message::Map& mapRet);
    void BuildQMRemindFriendItem(const QMRemindFriendItem& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstQMRFriend(const sdbus::Message::Map& mapIn, LstQMRFriend& lstOut);
    void ParseQMRemindFriendItem(const sdbus::Message::Map& mapIn, QMRemindFriendItem& ItemOut);

    void BuildQMRemindConfig(const QMRemindConfig& ItemIn, sdbus::Message::Map& mapRet);
    void ParseQMRemindConfig(const sdbus::Message::Map& mapIn, QMRemindConfig& ItemOut);

    void BuildLstBondShare(const LstBondShare& lstIn, sdbus::Message::List& lstRet);
    void BuildBondShareItem(const BondShareItem& ItemIn, sdbus::Message::Map& mapRet);
    void ParseLstBondShare(const sdbus::Message::List& lstIn, LstBondShare& lstOut);
    void ParseBondShareItem(const sdbus::Message::Map& mapIn, BondShareItem& ItemOut);

    void BuildLstNoInstituteContact(const LstNoInstituteContact &lstIn, sdbus::Message::Map& mapRet);
    void ParseLstNoInstituteContact(const sdbus::Message::Map& mapIn, LstNoInstituteContact& lstOut);
private:
	ss::logger* m_pLogger;
};
