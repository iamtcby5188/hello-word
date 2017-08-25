#include "stdafx.h"
#include "MsgQueueMap.h"
#include "SSMQClient\MyCSLock.h"

CMsgQueueMap::CMsgQueueMap()
{
    InitializeCriticalSection(&m_cs);
	InitMap();
}

CMsgQueueMap::~CMsgQueueMap()
{
    Clear();
    DeleteCriticalSection(&m_cs);
}

std::string CMsgQueueMap::GetQueueHead(const sdbus::Message& msg)
{
	std::string sUnkonw("unknow");
	if (msg.MapValue().Size() < 1)
	{
		return sUnkonw;
	}

	std::string sCmd("");
	msg.GetString(1, sCmd);

    CMyCSLock lk(&m_cs);
	StrMap::iterator iterf = m_MsgQueueMap.find(sCmd);
	if (iterf != m_MsgQueueMap.end())
	{
		return iterf->second;
	}
	return sUnkonw;
}

void CMsgQueueMap::InitMap()
{
    CMyCSLock lk(&m_cs);
	m_MsgQueueMap[MSGCMD_MM_SelContacts] = "qm1";
	m_MsgQueueMap[MSGCMD_MM_EditContacts] = "qm2";
	m_MsgQueueMap[MSGCMD_MM_SendQuot] = "qm3";
    m_MsgQueueMap[MSGCMD_MM_SendQuotV2] = "qm3";
	m_MsgQueueMap[MSGCMD_MM_QueryContactInfo] = "qm2";
	m_MsgQueueMap[MSGCMD_RequestBondInfosRet] = "qm4";
	m_MsgQueueMap[MSGCMD_OpenMainPanel] = "qm2";
	m_MsgQueueMap[MSGCMD_RefreshBondInfos] = "qm2";
	m_MsgQueueMap[MSGCMD_OpenDialogue] = "qm1";
	m_MsgQueueMap[MSGCMD_BOND_SendQuotByCode] = "qm3";
    m_MsgQueueMap[MSGCMD_BOND_SendQuotByCodeV2] = "qm3";
	m_MsgQueueMap[MSGCMD_BOND_SendQuotByCondition] = "qm3";
	m_MsgQueueMap[MSGCMD_MM_ReplyQuot] = "qm2";
	m_MsgQueueMap[MSGCMD_QueryCurUsrID] = "qm2";
	m_MsgQueueMap[MSGCMD_QueryCurUsrFriendIDs] = "qm2";
	m_MsgQueueMap[MSGCMD_QueryCurUsrGroupIDs] = "qm2";
	m_MsgQueueMap[MSGCMD_SendMsg] = "qm2";
    m_MsgQueueMap[MSGCMD_QueryQBWndPosRet] = "qm5";
    m_MsgQueueMap[MSGCMD_QueryQMWndPos] = "qm5";
    m_MsgQueueMap[MSGCMD_QueryQBWndHandleRet] = "qm5";
    m_MsgQueueMap[MSGCMD_QueryQMWndHandle] = "qm5";
    m_MsgQueueMap[MSGCMD_QueryQBPermRet] = "qm5";
    m_MsgQueueMap[MSGCMD_QuotShare_QueryShareGroup] = "qm6";
    m_MsgQueueMap[MSGCMD_SearchQMContact] = "qm6";
    m_MsgQueueMap[MSGCMD_ContactIsDealerRet] = "qm5";
    m_MsgQueueMap[MSGCMD_GetAllDealerRet] = "qm5";
    m_MsgQueueMap[MSGCMD_BOND_ReplyQuotByCode] = "qm2";
    m_MsgQueueMap[MSGCMD_Purchase_Send] = "qm5";
    m_MsgQueueMap[MSGCMD_Purchase_QueryStatusRet] = "qm5";
    m_MsgQueueMap[MSGCMD_Purchase_IsEditValidRet] = "qm5";
    m_MsgQueueMap[MSGCMD_Purchase_ConfirmRet] = "qm5";
    m_MsgQueueMap[MSGCMD_MM_QueryQuotStatusRet] = "qm5";
    m_MsgQueueMap[MSGCMD_Bond_QueryQuotByCodeStatusRet] = "qm5";
    m_MsgQueueMap[MSGCMD_Purchase_StatusPush] = "qm6";
    m_MsgQueueMap[MSGCMD_Purchase_IsEditValidPush] = "qm6";
    m_MsgQueueMap[MSGCMD_ContactIsDealerPush] = "qm6";
    m_MsgQueueMap[MSGCMD_QueryQMIDByQBAccount] = "qm6";
    m_MsgQueueMap[MSGCMD_Remind_QueryQMRemindConfig] = "qm7";
    m_MsgQueueMap[MSGCMD_Remind_SetQMRemindConfig] = "qm7";
    m_MsgQueueMap[MSGCMD_Remind_AddQMRemindKeyItem] = "qm7";
    m_MsgQueueMap[MSGCMD_Remind_ModifyQMRemindKeyItem] = "qm7";
    m_MsgQueueMap[MSGCMD_Remind_DelQMRemindKeyItem] = "qm7";
    m_MsgQueueMap[MSGCMD_Remind_AddQMRemindFriendItem] = "qm7";
    m_MsgQueueMap[MSGCMD_Remind_ModifyQMRemindFriendItem] = "qm7";
    m_MsgQueueMap[MSGCMD_Remind_DelQMRemindFriendItem] = "qm7";
    m_MsgQueueMap[MSGCMD_Remind_SetQMRemindType] = "qm7";
    m_MsgQueueMap[MSGCMD_OpenNewsBulletin] = "qm1";
    m_MsgQueueMap[MSGCMD_QueryCustomService] = "qm6";
    m_MsgQueueMap[MSGCMD_QBModifyPwd] = "qm2";
    m_MsgQueueMap[MSGCMD_ShareBond] = "qm2";
    m_MsgQueueMap[MSGCMD_ReqJoinGroup] = "qm7";
	m_MsgQueueMap[MSGCMD_ReqOpenNews] = "qm7";
    m_MsgQueueMap[MSGCMD_SharePic] = "qm7";
    m_MsgQueueMap[MSGCMD_OpenDialogueByUserID] = "qm7";
    m_MsgQueueMap[MSGCMD_ShareNewsDetail] = "qm7";
    m_MsgQueueMap[MSGCMD_QueryQMStatus] = "qm7";
    m_MsgQueueMap[MSGCMD_ReqOpenSellsWnd] = "qm7";
    m_MsgQueueMap[MSGCMD_ReqQueryNoInstituteContact] = "qm7";
    m_MsgQueueMap[MSGCMD_ReqSetNoInstituteContact] = "qm7";
    m_MsgQueueMap[MSGCMD_ReqOpenSellsSearchWnd] = "qm7";


	m_MsgQueueMap[MSGCMD_MM_SelContactsRet] = "qb1";
	m_MsgQueueMap[MSGCMD_MM_EditContactsRet] = "qb2";
	m_MsgQueueMap[MSGCMD_MM_SendQuotRet] = "qb2";
    m_MsgQueueMap[MSGCMD_MM_SendQuotRetV2] = "qb2";
	m_MsgQueueMap[MSGCMD_MM_QueryContactInfoRet] = "qb5";
	m_MsgQueueMap[MSGCMD_RequestBondInfos] = "qb3";
	m_MsgQueueMap[MSGCMD_ShowDlgBondDetail] = "qb2";
	m_MsgQueueMap[MSGCMD_BOND_SendQuotByCodeRet] = "qb2";
    m_MsgQueueMap[MSGCMD_BOND_SendQuotByCodeRetV2] = "qb2";
	m_MsgQueueMap[MSGCMD_BOND_SendQuotByConditionRet] = "qb2";
	m_MsgQueueMap[MSGCMD_MM_RecvQuot] = "qb4";
	m_MsgQueueMap[MSGCMD_QueryCurUsrIDRet] = "qb2";
	m_MsgQueueMap[MSGCMD_QueryCurUsrFriendIDsRet] = "qb2";
	m_MsgQueueMap[MSGCMD_QueryCurUsrGroupIDsRet] = "qb2";
	m_MsgQueueMap[MSGCMD_CurUsrGroupChange] = "qb2";
    m_MsgQueueMap[MSGCMD_CurUsrFriendChange] = "qb2";
	m_MsgQueueMap[MSGCMD_GroupDisband] = "qb2";
    m_MsgQueueMap[MSGCMD_QueryQBWndPos] = "qb6";
    m_MsgQueueMap[MSGCMD_QueryQMWndPosRet] = "qb6";
    m_MsgQueueMap[MSGCMD_QueryQBWndHandle] = "qb6";
    m_MsgQueueMap[MSGCMD_QueryQMWndHandleRet] = "qb6";
    m_MsgQueueMap[MSGCMD_QueryQBPerm] = "qb6";
    m_MsgQueueMap[MSGCMD_OpenMMQuot] = "qb4";
    m_MsgQueueMap[MSGCMD_QuotShare_QueryShareGroupRet] = "qb7";
    m_MsgQueueMap[MSGCMD_SearchQMContactRet] = "qb7";
    m_MsgQueueMap[MSGCMD_ContactIsDealer] = "qb6";
    m_MsgQueueMap[MSGCMD_OpenSubscribeDlg] = "qb4";
    m_MsgQueueMap[MSGCMD_GetAllDealer] = "qb6";
    m_MsgQueueMap[MSGCMD_QMErrInfo] = "qb2";
    m_MsgQueueMap[MSGCMD_Purchase_QueryStatus] = "qb4";
    m_MsgQueueMap[MSGCMD_Purchase_Confirm] = "qb4";
    m_MsgQueueMap[MSGCMD_Purchase_IsEditValid] = "qb6";
    m_MsgQueueMap[MSGCMD_Purchase_Edit] = "qb4";
    m_MsgQueueMap[MSGCMD_MM_QueryQuotStatus] = "qb8";
    m_MsgQueueMap[MSGCMD_Bond_QueryQuotByCodeStatus] = "qb8";
    m_MsgQueueMap[MSGCMD_ContactInfoPush] = "qb3";
    m_MsgQueueMap[MSGCMD_ContactStatusPush] = "qb3";
    m_MsgQueueMap[MSGCMD_QueryQMIDByQBAccountRet] = "qb3";
    m_MsgQueueMap[MSGCMD_Remind_QueryQMRemindConfigRet] = "qb9";
    m_MsgQueueMap[MSGCMD_Remind_AddQMRemindKeyItemRet] = "qb9";
    m_MsgQueueMap[MSGCMD_Remind_ModifyQMRemindKeyItemRet] = "qb9";
    m_MsgQueueMap[MSGCMD_Remind_DelQMRemindKeyItemRet] = "qb9";
    m_MsgQueueMap[MSGCMD_Remind_AddQMRemindFriendItemRet] = "qb9";
    m_MsgQueueMap[MSGCMD_Remind_ModifyQMRemindFriendItemRet] = "qb9";
    m_MsgQueueMap[MSGCMD_Remind_DelQMRemindFriendItemRet] = "qb9";
    m_MsgQueueMap[MSGCMD_Remind_SetQMRemindTypeRet] = "qb9";
    m_MsgQueueMap[MSGCMD_QueryCustomServiceRet] = "qb7";
    m_MsgQueueMap[MSGCMD_ReqJoinGroupRet] = "qb7";
    m_MsgQueueMap[MSGCMD_ReqOpenNewsDetail] = "qb7";
    m_MsgQueueMap[MSGCMD_ReqOpenNewsWnd] = "qb7";
    m_MsgQueueMap[MSGCMD_QueryQMStatusRet] = "qb7";
    m_MsgQueueMap[MSGCMD_ReqQueryNoInstituteContactRet] = "qb7";
    m_MsgQueueMap[MSGCMD_ModifyNoInstituteContactRet] = "qb7";
}

void CMsgQueueMap::Clear()
{
    CMyCSLock lk(&m_cs);
	m_MsgQueueMap.clear();
}
