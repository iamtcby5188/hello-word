#include "stdafx.h"
#include "MsgMng.h"
#include "..\..\code\SSRTL\SSLog.h"
#include "..\LogMarco.h"

CMsgMng::CMsgMng(void)
:m_pLogger(NULL)
{
	m_pLogger = new ss::logger("log\\QB_QM_Msg");
	m_pLogger->set_level_by_config("config\\logconfig.ini", "maincfg.msgmng");
}

CMsgMng::~CMsgMng(void)
{
	if (m_pLogger)
	{
		delete m_pLogger;
		m_pLogger = NULL;
	}
}

void CMsgMng::GetMsg_QuitQM(bool bChkSession, const std::string& sSessionID, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_QuitQM);
	msg.SetBool(2, bChkSession);
	msg.SetString(3, sSessionID);
}

void CMsgMng::ParseMsg_QuitQM(const sdbus::Message& msg, bool& bChkSession, std::string& sSessionID)
{
	if (msg.FieldCount() != 3)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QuitQM!\n");
		return;
	}

	msg.GetBool(2, bChkSession);
	msg.GetString(3, sSessionID);
}

void CMsgMng::GetMsg_OpenMainPanel(const std::string& sWndID, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_OpenMainPanel);
	msg.SetString(2, sWndID);
}

void CMsgMng::ParseMsg_OpenMainPanel(const sdbus::Message& msg, std::string& sWndID)
{
    if (msg.MapValue().Size() < 2)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse OpenMainPanel!\n");
        return;
    }

    msg.GetString(2, sWndID);
}

void CMsgMng::GetMsg_SelContacts(const std::string& sSelID, const std::string& sWndID, int nLimit, bool bShowGrp, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_MM_SelContacts);
	msg.SetString(2, sSelID);
    msg.SetString(3, sWndID);
    msg.SetInt32(4, nLimit);
    msg.SetBool(5, bShowGrp);
}

void CMsgMng::ParseMsg_SelContacts(const sdbus::Message& msg, std::string& sSelID, std::string& sWndID, int& nLimit, bool& bShowGrp)
{
	msg.GetString(2, sSelID);
    msg.GetString(3, sWndID);
    if (!msg.GetInt32(4,nLimit))
    {
        nLimit = 200;
    }
    if (!msg.GetBool(5, bShowGrp))
    {
        bShowGrp = true;
    }
}

void CMsgMng::GetMsg_SelContactsRet(const std::string& sSelID, const LstContact& Contacts, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_MM_SelContactsRet);
	msg.SetString(2, sSelID);
	sdbus::Message::Map mapRet;
	BuildLstContact(Contacts, mapRet);
	msg.SetMap(3, mapRet);
}

void CMsgMng::ParseMsg_SelContactsRet(const sdbus::Message& msg, std::string& sSelID, LstContact& Contacts)
{
	msg.GetString(2, sSelID);
	sdbus::Message::Map mapRet;
	msg.GetMap(3, mapRet);
	ParseLstContact(mapRet, Contacts);
}

void CMsgMng::GetMsg_EditContacts(const std::string& sEditID, const LstContact& Contacts, const std::string& sWndID, int nLimit, bool bShowGrp, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_MM_EditContacts);
	msg.SetString(2, sEditID);
	sdbus::Message::Map mapRet;
	BuildLstContact(Contacts, mapRet);
	msg.SetMap(3, mapRet);
    msg.SetString(4, sWndID);
    msg.SetInt32(5, nLimit);
    msg.SetBool(6, bShowGrp);
}

void CMsgMng::ParseMsg_EditContacts(const sdbus::Message& msg, std::string& sEditID, LstContact& Contacts, std::string& sWndID, int& nLimit, bool& bShowGrp)
{
	msg.GetString(2, sEditID);
	sdbus::Message::Map mapRet;
	msg.GetMap(3, mapRet);
	ParseLstContact(mapRet, Contacts);
    msg.GetString(4, sWndID);
    if (!msg.GetInt32(5, nLimit))
    {
        nLimit = 200;
    }
    if (!msg.GetBool(6, bShowGrp))
    {
        bShowGrp = true;
    }
}

void CMsgMng::GetMsg_EditContactsRet(const std::string& sEditID, const LstContact& Contacts, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_MM_EditContactsRet);
	msg.SetString(2, sEditID);
	sdbus::Message::Map mapRet;
	BuildLstContact(Contacts, mapRet);
	msg.SetMap(3, mapRet);
}

void CMsgMng::ParseMsg_EditContactsRet(const sdbus::Message& msg, std::string& sEditID, LstContact& Contacts)
{
	msg.GetString(2, sEditID);
	sdbus::Message::Map mapRet;
	msg.GetMap(3, mapRet);
	ParseLstContact(mapRet, Contacts);
}

void CMsgMng::GetMsg_SendQuot(const LstQuotSendInfo& lstSend, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_MM_SendQuot);

	sdbus::Message::Map mapRet;
	BuildLstQuotSendInfo(lstSend, mapRet);
	msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_SendQuot(const sdbus::Message& msg, LstQuotSendInfo& lstSend)
{
	sdbus::Message::Map mapRet;
	msg.GetMap(2, mapRet);
	ParseLstQuotSendInfo(mapRet, lstSend);
}

void CMsgMng::GetMsg_SendQuotRet(const LstQuotSendInfo& lstSuccess, const LstQuotSendInfo& lstFailed, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_MM_SendQuotRet);

    sdbus::Message::Map mapRetSuccess;
    BuildLstQuotSendInfo(lstSuccess, mapRetSuccess);
    msg.SetMap(2, mapRetSuccess);

    sdbus::Message::Map mapRetFailed;
    BuildLstQuotSendInfo(lstFailed, mapRetFailed);
    msg.SetMap(3, mapRetFailed);
}

void CMsgMng::ParseMsg_SendQuotRet(const sdbus::Message& msg, LstQuotSendInfo& lstSuccess, LstQuotSendInfo& lstFailed)
{
    sdbus::Message::Map mapRetSuccess;
    msg.GetMap(2, mapRetSuccess);
    ParseLstQuotSendInfo(mapRetSuccess, lstSuccess);

    sdbus::Message::Map mapRetFailed;
    msg.GetMap(3, mapRetFailed);
    ParseLstQuotSendInfo(mapRetFailed, lstFailed);
}

void CMsgMng::GetMsg_SendQuotV2(const LstMMQuotSendInfoV2& lstSend, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_MM_SendQuotV2);

    sdbus::Message::Map mapRet;
    BuildLstMMQuotSendInfoV2(lstSend, mapRet);
    msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_SendQuotV2(const sdbus::Message& msg, LstMMQuotSendInfoV2& lstSend)
{
    sdbus::Message::Map mapRet;
    msg.GetMap(2, mapRet);
    ParseLstMMQuotSendInfoV2(mapRet, lstSend);
}

void CMsgMng::GetMsg_SendQuotRetV2(const Contact& ct, const SetString& Success, const SetString& Failed, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_MM_SendQuotRetV2);

    sdbus::Message::Map mapCt;
    BuildContact(ct, mapCt);
    msg.SetMap(2, mapCt);

    sdbus::Message::Map mapRetSuccess;
    BuildSetString(Success, mapRetSuccess);
    msg.SetMap(3, mapRetSuccess);

    sdbus::Message::Map mapRetFailed;
    BuildSetString(Failed, mapRetFailed);
    msg.SetMap(4, mapRetFailed);
}

void CMsgMng::ParseMsg_SendQuotRetV2(const sdbus::Message& msg, Contact& ct, SetString& Success, SetString& Failed)
{
    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        BuildContact(ct, mapCt);
    }

    sdbus::Message::Map mapRetSuccess;
    if (msg.GetMap(3, mapRetSuccess))
    {
        ParseSetString(mapRetSuccess, Success);
    }

    sdbus::Message::Map mapRetFailed;
    if (msg.GetMap(4, mapRetFailed))
    {
        ParseSetString(mapRetFailed, Failed);
    }
}

void CMsgMng::GetMsg_RecvQuot(const LstQuotRecvInfo& lstIn, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_MM_RecvQuot);

	sdbus::Message::Map mapRet;
	BuildLstQuotRecvInfo(lstIn, mapRet);
	msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_RecvQuot(const sdbus::Message& msg, LstQuotRecvInfo& lstOut)
{
	sdbus::Message::Map mapRet;
	msg.GetMap(2, mapRet);
	ParseLstQuotRecvInfo(mapRet, lstOut);
}

void CMsgMng::GetMsg_ReplyQuot(const QuotReplyInfo& ItemIn, const std::string& sWndID, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_MM_ReplyQuot);

	sdbus::Message::Map mapRet;
	BuildQuotReplyInfo(ItemIn, mapRet);
	msg.SetMap(2, mapRet);

    msg.SetString(3, sWndID);
}

void CMsgMng::ParseMsg_ReplyQuot(const sdbus::Message& msg, QuotReplyInfo& ItemOut, std::string& sWndID)
{
	sdbus::Message::Map mapRet;
	msg.GetMap(2, mapRet);
	ParseQuotReplyInfo(mapRet, ItemOut);

    msg.GetString(3, sWndID);
}

void CMsgMng::GetMsg_QueryContactsInfo(const LstContact& lstIn, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_MM_QueryContactInfo);

	sdbus::Message::Map mapRet;
	BuildLstContact(lstIn, mapRet);
	msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_QueryContactsInfo(const sdbus::Message& msg, LstContact& lstOut)
{
	sdbus::Message::Map mapRet;
	msg.GetMap(2, mapRet);
	ParseLstContact(mapRet, lstOut);
}

void CMsgMng::GetMsg_QueryContactsInfoRet(const LstPersonInfo& lstPerson, const LstGroupInfo& lstGrp, const LstContact& lstFailed, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_MM_QueryContactInfoRet);

	sdbus::Message::Map mapPerson;
	BuildLstPersonInfo(lstPerson, mapPerson);
	msg.SetMap(2, mapPerson);

	sdbus::Message::Map mapGroup;
	BuildLstGroupInfo(lstGrp, mapGroup);
	msg.SetMap(3, mapGroup);

    sdbus::Message::Map mapFailed;
    BuildLstContact(lstFailed, mapFailed);
    msg.SetMap(4, mapFailed);
}

void CMsgMng::ParseMsg_QueryContactsInfoRet(const sdbus::Message& msg, LstPersonInfo& lstPerson, LstGroupInfo& lstGrp, LstContact& lstFailed)
{
	sdbus::Message::Map mapPerson;
	msg.GetMap(2, mapPerson);
	ParseLstPersonInfo(mapPerson, lstPerson);

	sdbus::Message::Map mapGroup;
	msg.GetMap(3, mapGroup);
	ParseLstGroupInfo(mapGroup, lstGrp);

    sdbus::Message::Map mapFailed;
    if (msg.GetMap(4, mapFailed))
    {
        ParseLstContact(mapFailed, lstFailed);
    }
}

void CMsgMng::GetMsg_RequestBondInfos(sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_RequestBondInfos);
	msg.SetString(2, MSGCMD_RequestBondInfos);
}

void CMsgMng::GetMsg_RequestBondInfosRet(const LstBondItem& lstIn, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_RequestBondInfosRet);

	sdbus::Message::Map mapIn;
	BuildLstBondItem(lstIn, mapIn);
	msg.SetMap(2, mapIn);
}

void CMsgMng::ParseMsg_RequestBondInfosRet(const sdbus::Message& msg, LstBondItem& lstOut)
{
	sdbus::Message::Map mapOut;
	msg.GetMap(2, mapOut);
	ParseLstBondItem(mapOut, lstOut);
}

void CMsgMng::GetMsg_ShowDlgBondDetail(const std::string& sBondKey, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_ShowDlgBondDetail);

	msg.SetString(2, sBondKey);
}

void CMsgMng::ParseMsg_ShowDlgBondDetail(const sdbus::Message& msg, std::string& sBondKey)
{
	msg.GetString(2, sBondKey);
}

void CMsgMng::GetMsg_RefreshBondInfos(sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_RefreshBondInfos);
	msg.SetString(2, MSGCMD_RefreshBondInfos);
}

void CMsgMng::GetMsg_OpenDialogue(const Contact& ct, const std::string& sSendMsg, const std::string& sWndID, const bool bOpen, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_OpenDialogue);

	sdbus::Message::Map mapIn;
	BuildContact(ct, mapIn);
	msg.SetMap(2, mapIn);

	msg.SetString(3, sSendMsg);

    msg.SetString(4, sWndID);
    msg.SetBool(5, bOpen);
}

void CMsgMng::ParseMsg_OpenDialogue(const sdbus::Message& msg, Contact& ct, std::string& sSendMsg, std::string& sWndID, bool &bOpen)
{
	if (msg.MapValue().Size() < 3)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse OpenDialogue!\n");
		return;
	}
	sdbus::Message::Map mapOut;
	msg.GetMap(2, mapOut);
	ParseContact(mapOut, ct);

	msg.GetString(3, sSendMsg);
    msg.GetString(4, sWndID);
    msg.GetBool(5, bOpen);
}

void CMsgMng::GetMsg_SendBondQuotByCode(const LstBondQuotByCodeSendInfo& lstIn, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_BOND_SendQuotByCode);

	sdbus::Message::Map mapRet;
	BuildLstBondQuotByCodeSendInfo(lstIn, mapRet);
	msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_SendBondQuotByCode(const sdbus::Message& msg, LstBondQuotByCodeSendInfo& lstOut)
{
	if (msg.MapValue().Size() != 2)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse SentBondQuotByCode!\n");
		return;
	}
	sdbus::Message::Map mapOut;
	msg.GetMap(2, mapOut);
	ParseLstBondQuotByCodeSendInfo(mapOut, lstOut);
}

void CMsgMng::GetMsg_SendBondQuotByCodeRet(const LstBondQuotByCodeSendInfo& lstSuccess, const LstBondQuotByCodeSendInfo& lstFailed, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_BOND_SendQuotByCodeRet);

	sdbus::Message::Map mapRetSuccess;
	BuildLstBondQuotByCodeSendInfo(lstSuccess, mapRetSuccess);
	msg.SetMap(2, mapRetSuccess);

	sdbus::Message::Map mapRetFailed;
	BuildLstBondQuotByCodeSendInfo(lstFailed, mapRetFailed);
	msg.SetMap(3, mapRetFailed);
}

void CMsgMng::ParseMsg_SendBondQuotByCodeRet(const sdbus::Message& msg, LstBondQuotByCodeSendInfo& lstSuccess, LstBondQuotByCodeSendInfo& lstFailed)
{
	if (msg.MapValue().Size() != 3)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse SentBondQuotByCodeRet!\n");
		return;
	}

	sdbus::Message::Map mapRetSuccess;
	msg.GetMap(2, mapRetSuccess);
	ParseLstBondQuotByCodeSendInfo(mapRetSuccess, lstSuccess);

	sdbus::Message::Map mapRetFailed;
	msg.GetMap(3, mapRetFailed);
	ParseLstBondQuotByCodeSendInfo(mapRetFailed, lstFailed);
}

void CMsgMng::GetMsg_SendBondQuotByCodeV2(const LstBondQuotByCodeSendInfoV2& lstIn, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_BOND_SendQuotByCodeV2);

    sdbus::Message::Map mapRet;
    BuildLstBondQuotByCodeSendInfoV2(lstIn, mapRet);
    msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_SendBondQuotByCodeV2(const sdbus::Message& msg, LstBondQuotByCodeSendInfoV2& lstOut)
{
    if (msg.MapValue().Size() < 2)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse SendBondQuotByCodeV2!\n");
        return;
    }
    sdbus::Message::Map mapOut;
    msg.GetMap(2, mapOut);
    ParseLstBondQuotByCodeSendInfoV2(mapOut, lstOut);
}

void CMsgMng::GetMsg_SendBondQuotByCodeRetV2(const Contact& ct, const SetString& Success, const SetString& Failed, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_BOND_SendQuotByCodeRetV2);

    sdbus::Message::Map mapCt;
    BuildContact(ct, mapCt);
    msg.SetMap(2, mapCt);

    sdbus::Message::Map mapRetSuccess;
    BuildSetString(Success, mapRetSuccess);
    msg.SetMap(3, mapRetSuccess);

    sdbus::Message::Map mapRetFailed;
    BuildSetString(Failed, mapRetFailed);
    msg.SetMap(4, mapRetFailed);
}

void CMsgMng::ParseMsg_SendBondQuotByCodeRetV2(const sdbus::Message& msg, Contact& ct, SetString& Success, SetString& Failed)
{
    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        BuildContact(ct, mapCt);
    }

    sdbus::Message::Map mapRetSuccess;
    if (msg.GetMap(3, mapRetSuccess))
    {
        ParseSetString(mapRetSuccess, Success);
    }

    sdbus::Message::Map mapRetFailed;
    if (msg.GetMap(4, mapRetFailed))
    {
        ParseSetString(mapRetFailed, Failed);
    }
}

void CMsgMng::GetMsg_ReplyBondQuotByCode(const BondQuotByCodeReplyInfo& ItemIn, const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_BOND_ReplyQuotByCode);

    sdbus::Message::Map mapRet;
    BuildBondQuotByCodeReplyInfo(ItemIn, mapRet);
    msg.SetMap(2, mapRet);

    msg.SetString(3, sWndID);
}

void CMsgMng::ParseMsg_ReplyBondQuotByCode(const sdbus::Message& msg, BondQuotByCodeReplyInfo& ItemOut, std::string& sWndID)
{
    sdbus::Message::Map mapRet;
    if (msg.GetMap(2, mapRet))
    {
        ParseBondQuotByCodeReplyInfo(mapRet, ItemOut);
    }

    msg.GetString(3, sWndID);
}

void CMsgMng::GetMsg_SendBondQuotByCondition(const LstBondQuotByConditionSendInfo& lstIn, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_BOND_SendQuotByCondition);

	sdbus::Message::Map mapRet;
	BuildLstBondQuotByConditionSendInfo(lstIn, mapRet);
	msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_SendBondQuotByCondition(const sdbus::Message& msg, LstBondQuotByConditionSendInfo& lstOut)
{
	if (msg.MapValue().Size() != 2)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse SentBondQuotByCondition!\n");
		return;
	}
	sdbus::Message::Map mapOut;
	msg.GetMap(2, mapOut);
	ParseLstBondQuotByConditionSendInfo(mapOut, lstOut);
}

void CMsgMng::GetMsg_SendBondQuotByConditionRet(const LstBondQuotByConditionSendInfo& lstSuccess, const LstBondQuotByConditionSendInfo& lstFailed, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_BOND_SendQuotByConditionRet);

	sdbus::Message::Map mapRetSuccess;
	BuildLstBondQuotByConditionSendInfo(lstSuccess, mapRetSuccess);
	msg.SetMap(2, mapRetSuccess);

	sdbus::Message::Map mapRetFailed;
	BuildLstBondQuotByConditionSendInfo(lstFailed, mapRetFailed);
	msg.SetMap(3, mapRetFailed);
}

void CMsgMng::ParseMsg_SendBondQuotByConditionRet(const sdbus::Message& msg, LstBondQuotByConditionSendInfo& lstSuccess, LstBondQuotByConditionSendInfo& lstFailed)
{
	if (msg.MapValue().Size() != 3)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse SentBondQuotByConditionRet!\n");
		return;
	}

	sdbus::Message::Map mapRetSuccess;
	msg.GetMap(2, mapRetSuccess);
	ParseLstBondQuotByConditionSendInfo(mapRetSuccess, lstSuccess);

	sdbus::Message::Map mapRetFailed;
	msg.GetMap(3, mapRetFailed);
	ParseLstBondQuotByConditionSendInfo(mapRetFailed, lstFailed);
}

void CMsgMng::GetMsg_QueryCurUsrID(sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_QueryCurUsrID);
	msg.SetString(2, MSGCMD_QueryCurUsrID);
}

void CMsgMng::GetMsg_QueryCurUsrIDRet(unsigned long long UsrID, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_QueryCurUsrIDRet);

	msg.SetUInt64(2, UsrID);
}

void CMsgMng::ParseMsg_QueryCurUsrIDRet(const sdbus::Message& msg, unsigned long long& UsrID)
{
	if (msg.MapValue().Size() != 2)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryCurUsrIDRet!\n");
		return;
	}

	msg.GetUInt64(2, UsrID);
}

void CMsgMng::GetMsg_QueryCurUsrFriendIDs(sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_QueryCurUsrFriendIDs);
	msg.SetString(2, MSGCMD_QueryCurUsrFriendIDs);
}

void CMsgMng::GetMsg_QueryCurUsrFriendIDsRet(const SetUInt64& setIn, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_QueryCurUsrFriendIDsRet);

	sdbus::Message::Map mapRet;
	BuildSetUInt64(setIn, mapRet);
	msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_QueryCurUsrFriendIDsRet(const sdbus::Message& msg, SetUInt64& setRet)
{
	if (msg.MapValue().Size() != 2)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryCurUsrFriendIDsRet!\n");
		return;
	}

	sdbus::Message::Map mapRet;
	msg.GetMap(2, mapRet);
	ParseSetUInt64(mapRet, setRet);
}

void CMsgMng::GetMsg_QueryCurUsrGroupIDs(sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_QueryCurUsrGroupIDs);
	msg.SetString(2, MSGCMD_QueryCurUsrGroupIDs);
}

void CMsgMng::GetMsg_QueryCurUsrGroupIDsRet(const SetUInt64& setIn, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_QueryCurUsrGroupIDsRet);

	sdbus::Message::Map mapRet;
	BuildSetUInt64(setIn, mapRet);
	msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_QueryCurUsrGroupIDsRet(const sdbus::Message& msg, SetUInt64& setRet)
{
	if (msg.MapValue().Size() != 2)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryCurUsrGroupIDsRet!\n");
		return;
	}

	sdbus::Message::Map mapRet;
	msg.GetMap(2, mapRet);
	ParseSetUInt64(mapRet, setRet);
}

void CMsgMng::GetMsg_CurUsrGroupChange(const SetUInt64& JoinGrpIDs, const SetUInt64& LeaveGrpIDs, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_CurUsrGroupChange);

    sdbus::Message::Map mapJoin;
    BuildSetUInt64(JoinGrpIDs, mapJoin);
    msg.SetMap(2, mapJoin);

    sdbus::Message::Map mapLeave;
    BuildSetUInt64(LeaveGrpIDs, mapLeave);
    msg.SetMap(3, mapLeave);
}

void CMsgMng::ParseMsg_CurUsrGroupChange(const sdbus::Message& msg, SetUInt64& JoinGrpIDs, SetUInt64& LeaveGrpIDs)
{
	if (msg.MapValue().Size() != 3)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse CurUsrGroupChange!\n");
		return;
	}

	sdbus::Message::Map mapJoin;
	msg.GetMap(2, mapJoin);
	ParseSetUInt64(mapJoin, JoinGrpIDs);

	sdbus::Message::Map mapLeave;
	msg.GetMap(3, mapLeave);
	ParseSetUInt64(mapLeave, LeaveGrpIDs);
}

void CMsgMng::GetMsg_CurUsrFriendChange(const SetUInt64& AddFriendIDs, const SetUInt64& DelFriendIDs, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_CurUsrFriendChange);

    sdbus::Message::Map mapAdd;
    BuildSetUInt64(AddFriendIDs, mapAdd);
    msg.SetMap(2, mapAdd);

    sdbus::Message::Map mapDel;
    BuildSetUInt64(DelFriendIDs, mapDel);
    msg.SetMap(3, mapDel);
}

void CMsgMng::ParseMsg_CurUsrFriendChange(const sdbus::Message& msg, SetUInt64& AddFriendIDs, SetUInt64& DelFriendIDs)
{
    bool bR = true;
    sdbus::Message::Map mapAdd;
    if (msg.GetMap(2, mapAdd))
    {
        ParseSetUInt64(mapAdd, AddFriendIDs);
    }
    else
    {
        bR =false;
    }


    sdbus::Message::Map mapDel;
    if (msg.GetMap(3, mapDel))
    {
        ParseSetUInt64(mapDel, DelFriendIDs);
    }
    else
    {
        bR = false;
    }

    if (!bR)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse CurUsrFriendChange!\n");
    }
}

void CMsgMng::GetMsg_GroupDisband(unsigned long long GrpID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_GroupDisband);

    msg.SetUInt64(2, GrpID);
}

void CMsgMng::ParseMsg_GroupDisband(const sdbus::Message& msg, unsigned long long& GrpID)
{
    if (msg.MapValue().Size() != 2)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse GroupDisband!\n");
        return;
    }

    msg.GetUInt64(2, GrpID);
}


void CMsgMng::GetMsg_SendMsg(const LstContact& lstCt, const std::string& sSendMsg, const std::string& sWndID, sdbus::Message& msg)
{
	msg.SetString(1, MSGCMD_SendMsg);

	sdbus::Message::Map mapIn;
	BuildLstContact(lstCt, mapIn);
	msg.SetMap(2, mapIn);

	msg.SetString(3, sSendMsg);

    msg.SetString(4, sWndID);
}

void CMsgMng::ParseMsg_SendMsg(const sdbus::Message& msg, LstContact& lstCt, std::string& sSendMsg, std::string& sWndID)
{
	if (msg.MapValue().Size() < 3)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse SendMsg!\n");
		return;
	}
	sdbus::Message::Map mapOut;
	msg.GetMap(2, mapOut);
	ParseLstContact(mapOut, lstCt);

	msg.GetString(3, sSendMsg);

    msg.GetString(4, sWndID);
}

void CMsgMng::GetMsg_QueryQBWndPos(const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQBWndPos);
    msg.SetString(2, sWndID);
}

void CMsgMng::ParseMsg_QueryQBWndPos(const sdbus::Message& msg, std::string& sWndID)
{
    if (msg.MapValue().Size() != 2)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryQBWndPos!\n");
        return;
    }

    msg.GetString(2, sWndID);
}

void CMsgMng::GetMsg_QueryQBWndPosRet(int nTop, int nBottom, int nLeft, int nRight, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQBWndPosRet);

    msg.SetInt32(2, nTop);
    msg.SetInt32(3, nBottom);
    msg.SetInt32(4, nLeft);
    msg.SetInt32(5, nRight);
}

void CMsgMng::ParseMsg_QueryQBWndPosRet(const sdbus::Message& msg, int& nTop, int& nBottom, int& nLeft, int& nRight)
{
    if (msg.MapValue().Size() != 5)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryQBWndPosRet!\n");
        return;
    }

    msg.GetInt32(2, nTop);
    msg.GetInt32(3, nBottom);
    msg.GetInt32(4, nLeft);
    msg.GetInt32(5, nRight);
}


void CMsgMng::GetMsg_QueryQMWndPos(const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQMWndPos);
    msg.SetString(2, sWndID);
}

void CMsgMng::ParseMsg_QueryQMWndPos(const sdbus::Message& msg, std::string& sWndID)
{
    if (msg.MapValue().Size() != 2)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryQMWndPos!\n");
        return;
    }

    msg.GetString(2, sWndID);
}

void CMsgMng::GetMsg_QueryQMWndPosRet(int nTop, int nBottom, int nLeft, int nRight, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQMWndPosRet);

    msg.SetInt32(2, nTop);
    msg.SetInt32(3, nBottom);
    msg.SetInt32(4, nLeft);
    msg.SetInt32(5, nRight);
}

void CMsgMng::ParseMsg_QueryQMWndPosRet(const sdbus::Message& msg, int& nTop, int& nBottom, int& nLeft, int& nRight)
{
    if (msg.MapValue().Size() != 5)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryQMWndPosRet!\n");
        return;
    }

    msg.GetInt32(2, nTop);
    msg.GetInt32(3, nBottom);
    msg.GetInt32(4, nLeft);
    msg.GetInt32(5, nRight);
}

void CMsgMng::GetMsg_QueryQBWndHandle(const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQBWndHandle);
    msg.SetString(2, sWndID);
}

void CMsgMng::ParseMsg_QueryQBWndHandle(const sdbus::Message& msg, std::string& sWndID)
{
    if (!msg.GetString(2, sWndID))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryQBWndHandle!\n");
    }
}

void CMsgMng::GetMsg_QueryQBWndHandleRet(HWND hWnd, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQBWndHandleRet);
    msg.SetUInt64(2, (unsigned long long)hWnd);
}

void CMsgMng::ParseMsg_QueryQBWndHandleRet(const sdbus::Message& msg, unsigned long long& hWnd)
{
    sdbus::uint64_t u64(0);
    if (!msg.GetUInt64(2, u64))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryQBWndHandleRet!\n");
    }
    hWnd = u64;
}

void CMsgMng::GetMsg_QueryQMWndHandle(const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQMWndHandle);
    msg.SetString(2, sWndID);
}

void CMsgMng::ParseMsg_QueryQMWndHandle(const sdbus::Message& msg, std::string& sWndID)
{
    if (!msg.GetString(2, sWndID))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryQMWndHandle!\n");
    }
}

void CMsgMng::GetMsg_QueryQMWndHandleRet(unsigned long long hWnd, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQMWndHandleRet);
    msg.SetUInt64(2, hWnd);
}

void CMsgMng::ParseMsg_QueryQMWndHandleRet(const sdbus::Message& msg, HWND& hWnd)
{
    sdbus::uint64_t u64(0);
    if (!msg.GetUInt64(2, u64))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryQMWndHandleRet!\n");
    }
    hWnd = (HWND)u64;
}

void CMsgMng::GetMsg_QueryQBPerm(sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQBPerm);
    msg.SetString(2, MSGCMD_QueryQBPerm);
}

void CMsgMng::GetMsg_QueryQBPermRet(const SetString& setPerm, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQBPermRet);

    sdbus::Message::Map mapPerm;
    BuildSetString(setPerm, mapPerm);
    msg.SetMap(2, mapPerm);
}

void CMsgMng::ParseMsg_QueryQBPermRet(const sdbus::Message& msg, SetString& setPerm)
{
    if (msg.MapValue().Size() != 2)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QueryQBPermRet!\n");
        return;
    }

    sdbus::Message::Map mapPerm;
    msg.GetMap(2, mapPerm);
    ParseSetString(mapPerm, setPerm);
}

void CMsgMng::GetMsg_OpenMMQuot(const LstContact& lstCt, const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_OpenMMQuot);

    sdbus::Message::Map map_lstCt;
    BuildLstContact(lstCt, map_lstCt);
    msg.SetMap(2, map_lstCt);

    msg.SetString(3, sWndID);
}

void CMsgMng::ParseMsg_OpenMMQuot(const sdbus::Message& msg, LstContact& lstCt, std::string& sWndID)
{
    bool bSuccess = true;

    sdbus::Message::Map map_lstCt;
    bSuccess &= msg.GetMap(2, map_lstCt);
    ParseLstContact(map_lstCt, lstCt);

    bSuccess &= msg.GetString(3, sWndID);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse OpenMMQuot!\n");
    }
}

void CMsgMng::GetMsg_QueryShareGroup(sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QuotShare_QueryShareGroup);
    msg.SetString(2, MSGCMD_QuotShare_QueryShareGroup);
}

void CMsgMng::GetMsg_QueryShareGroupRet(const Contact& ct, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QuotShare_QueryShareGroupRet);

    sdbus::Message::Map mapCt;
    BuildContact(ct, mapCt);
    msg.SetMap(2, mapCt);
}

void CMsgMng::ParseMsg_QueryShareGroupRet(const sdbus::Message& msg, Contact& ct)
{
    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        ParseContact(mapCt, ct);
    }
}

void CMsgMng::GetMsg_SearchQMContact(const ContactSearch& SearchInput, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_SearchQMContact);

    sdbus::Message::Map mapSI;
    BuildContactSearch(SearchInput, mapSI);
    msg.SetMap(2, mapSI);
}

void CMsgMng::ParseMsg_SearchQMContact(const sdbus::Message& msg, ContactSearch& SearchInput)
{
    sdbus::Message::Map mapSI;
    if (msg.GetMap(2, mapSI))
    {
        ParseContactSearch(mapSI, SearchInput);
    }
}

void CMsgMng::GetMsg_SearchQMContactRet(const LstSearchUserInfo& Result, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_SearchQMContactRet);

    sdbus::Message::Map mapResult;
    BuildLstSearchUserInfo(Result, mapResult);
    msg.SetMap(2, mapResult);
}

void CMsgMng::ParseMsg_SearchQMContactRet(const sdbus::Message& msg, LstSearchUserInfo& Result)
{
    sdbus::Message::Map mapResult;
    if (msg.GetMap(2, mapResult))
    {
        ParseLstSearchUserInfo(mapResult, Result);
    }
}

void CMsgMng::GetMsg_ContactIsDealer(const Contact& ct, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_ContactIsDealer);

    sdbus::Message::Map mapCt;
    BuildContact(ct, mapCt);
    msg.SetMap(2, mapCt);
}

void CMsgMng::ParseMsg_ContactIsDealer(const sdbus::Message& msg, Contact& ct)
{
    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        ParseContact(mapCt, ct);
    }
}

void CMsgMng::GetMsg_ContactIsDealerRet(bool isDealer, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_ContactIsDealerRet);
    msg.SetBool(2, isDealer);
}

void CMsgMng::ParseMsg_ContactIsDealerRet(const sdbus::Message& msg, bool& isDealer)
{
    if (!msg.GetBool(2, isDealer))
    {
        isDealer = false;
    }
}

void CMsgMng::GetMsg_OpenSubscribeDlg(const Contact& ct, const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_OpenSubscribeDlg);

    sdbus::Message::Map mapCt;
    BuildContact(ct, mapCt);
    msg.SetMap(2, mapCt);

    msg.SetString(3, sWndID);
}

void CMsgMng::ParseMsg_OpenSubscribeDlg(const sdbus::Message& msg, Contact& ct, std::string& sWndID)
{
    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        ParseContact(mapCt, ct);
    }

    msg.GetString(3, sWndID);
}

void CMsgMng::GetMsg_GetAllDealer(sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_GetAllDealer);
    msg.SetString(2, MSGCMD_GetAllDealer);
}

void CMsgMng::GetMsg_GetAllDealerRet(const SetUInt64& setIn, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_GetAllDealerRet);

    sdbus::Message::Map mapID;
    BuildSetUInt64(setIn, mapID);
    msg.SetMap(2, mapID);
}

void CMsgMng::ParseMsg_GetAllDealerRet(const sdbus::Message& msg, SetUInt64& setRet)
{
    sdbus::Message::Map mapID;
    if (msg.GetMap(2, mapID))
    {
        ParseSetUInt64(mapID, setRet);
    }
}

void CMsgMng::GetMsg_QMErrInfo(int nCode, const std::string& sInfo, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QMErrInfo);
    msg.SetInt32(2, nCode);
    msg.SetString(3, sInfo);
}

void CMsgMng::ParseMsg_QMErrInfo(const sdbus::Message& msg, int& nCode, std::string& sInfo)
{
    bool bSuccess = true;
    bSuccess &= msg.GetInt32(2, nCode);
    bSuccess &= msg.GetString(3, sInfo);
    
    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QMErrInfo!\n");
    }
}

void CMsgMng::GetMsg_Purchase(const Contact& Ct, const PurchaseInfo& PInfo, const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Purchase_Send);

    sdbus::Message::Map mapCt;
    BuildContact(Ct, mapCt);
    msg.SetMap(2, mapCt);

    sdbus::Message::Map mapPInfo;
    BuildPurchaseInfo(PInfo, mapPInfo);
    msg.SetMap(3, mapPInfo);

    msg.SetString(4, sWndID);
}

void CMsgMng::ParseMsg_Purchase(const sdbus::Message& msg, Contact& Ct, PurchaseInfo& PInfo, std::string& sWndID)
{
    bool bSuccess = true;

    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        ParseContact(mapCt, Ct);
    }
    else
    {
        bSuccess = false;
    }
    
    sdbus::Message::Map mapPInfo;
    if (msg.GetMap(3, mapPInfo))
    {
        ParsePurchaseInfo(mapPInfo, PInfo);
    }
    else
    {
        bSuccess = false;
    }

    bSuccess &= msg.GetString(4, sWndID);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg Purchase!\n");
    }
}

void CMsgMng::GetMsg_QueryPurchaseStatus(const LstPurchaseUkey& lstQuery, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Purchase_QueryStatus);

    sdbus::Message::Map mapRet;
    BuildLstPurchaseUkey(lstQuery, mapRet);
    msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_QueryPurchaseStatus(const sdbus::Message& msg, LstPurchaseUkey& lstQuery)
{
    sdbus::Message::Map mapRet;
    if (msg.GetMap(2, mapRet))
    {
        ParseLstPurchaseUkey(mapRet, lstQuery);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QueryPurchaseStatus!\n");
    }
}

void CMsgMng::GetMsg_QueryPurchaseStatusRet(const MapPurchaseStatus& mapPStatus, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Purchase_QueryStatusRet);
    
    sdbus::Message::Map mapRet;
    BuildMapPurchaseStatus(mapPStatus, mapRet);
    msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_QueryPurchaseStatusRet(const sdbus::Message& msg, MapPurchaseStatus& mapPStatus)
{
    sdbus::Message::Map mapRet;
    if (msg.GetMap(2, mapRet))
    {
        ParseMapPurchaseStatus(mapRet, mapPStatus);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QueryPurchaseStatusRet!\n");
    }
}

void CMsgMng::GetMsg_ConfirmPurchase(const std::string& sPurchaseID, time_t ModifyTime, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Purchase_Confirm);
    msg.SetString(2, sPurchaseID);
    msg.SetUInt64(3, ModifyTime);
}

void CMsgMng::ParseMsg_ConfirmPurchase(const sdbus::Message& msg, std::string& sPurchaseID, time_t& ModifyTime)
{
    bool bSuccess = true;
    bSuccess &= msg.GetString(2, sPurchaseID);
    sdbus::uint64_t u64;
    bSuccess &= msg.GetUInt64(3, u64);
    ModifyTime = u64;

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ConfirmPurchase!\n");
    }
}

void CMsgMng::GetMsg_ConfirmPurchaseRet(int nStatus, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Purchase_ConfirmRet);
    msg.SetInt32(2, nStatus);
}

void CMsgMng::ParseMsg_ConfirmPurchaseRet(const sdbus::Message& msg, int& nStatus)
{
    if (!msg.GetInt32(2, nStatus))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ConfirmPurchaseRet!\n");
    }
}

void CMsgMng::GetMsg_IsEditPurchaseValid(const Contact& ct, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Purchase_IsEditValid);

    sdbus::Message::Map mapCt;
    BuildContact(ct, mapCt);
    msg.SetMap(2, mapCt);
}

void CMsgMng::ParseMsg_IsEditPurchaseValid(const sdbus::Message& msg, Contact& ct)
{
    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        ParseContact(mapCt, ct);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg IsEditPurchaseValid!\n");
    }
}

void CMsgMng::GetMsg_IsEditPurchaseValidRet(bool bValid, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Purchase_IsEditValidRet);
    msg.SetBool(2, bValid);
}

void CMsgMng::ParseMsg_IsEditPurchaseValidRet(const sdbus::Message& msg, bool& bValid)
{
    if (!msg.GetBool(2, bValid))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg IsEditPurchaseValidRet!\n");
    }
}

void CMsgMng::GetMsg_EditPurchase(const Contact& ct, const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Purchase_Edit);

    sdbus::Message::Map mapCt;
    BuildContact(ct, mapCt);
    msg.SetMap(2, mapCt);

    msg.SetString(3, sWndID);
}

void CMsgMng::ParseMsg_EditPurchase(const sdbus::Message& msg, Contact& ct, std::string& sWndID)
{
    bool bSuccess = true;

    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        ParseContact(mapCt, ct);
    }
    else
    {
        bSuccess = false;
    }

    bSuccess &= msg.GetString(3, sWndID);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg EditPurchase!\n");
    }
}

void CMsgMng::GetMsg_QueryMMQuotStatus(const LstQuotStatusReq& lstReq, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_MM_QueryQuotStatus);

    sdbus::Message::Map map_lstReq;
    BuildLstQuotStatusReq(lstReq, map_lstReq);
    msg.SetMap(2, map_lstReq);
}

void CMsgMng::ParseMsg_QueryMMQuotStatus(const sdbus::Message& msg, LstQuotStatusReq& lstReq)
{
    sdbus::Message::Map map_lstReq;
    if (!msg.GetMap(2, map_lstReq))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QueryMMQuotStatus!\n");
    }
    ParseLstQuotStatusReq(map_lstReq, lstReq);
}

void CMsgMng::GetMsg_QueryMMQuotStatusRet(const LstQuotStatus& lstRet, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_MM_QueryQuotStatusRet);

    sdbus::Message::Map map_lstRet;
    BuildLstQuotStatus(lstRet, map_lstRet);
    msg.SetMap(2, map_lstRet);
}

void CMsgMng::ParseMsg_QueryMMQuotStatusRet(const sdbus::Message& msg, LstQuotStatus& lstRet)
{
    sdbus::Message::Map map_lstRet;
    if (!msg.GetMap(2, map_lstRet))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QueryMMQuotStatusRet!\n");
    }
    ParseLstQuotStatus(map_lstRet, lstRet);
}

void CMsgMng::GetMsg_QueryBondQuotByCodeStatus(const LstQuotStatusReq& lstReq, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Bond_QueryQuotByCodeStatus);
    
    sdbus::Message::Map map_lstReq;
    BuildLstQuotStatusReq(lstReq, map_lstReq);
    msg.SetMap(2, map_lstReq);
}

void CMsgMng::ParseMsg_QueryBondQuotByCodeStatus(const sdbus::Message& msg, LstQuotStatusReq& lstReq)
{
    sdbus::Message::Map map_lstReq;
    if (!msg.GetMap(2, map_lstReq))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QueryBondQuotByCodeStatus!\n");
    }
    ParseLstQuotStatusReq(map_lstReq, lstReq);
}

void CMsgMng::GetMsg_QueryBondQuotByCodeStatusRet(const LstQuotStatus& lstRet, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Bond_QueryQuotByCodeStatusRet);
    
    sdbus::Message::Map map_lstRet;
    BuildLstQuotStatus(lstRet, map_lstRet);
    msg.SetMap(2, map_lstRet);
}

void CMsgMng::ParseMsg_QueryBondQuotByCodeStatusRet(const sdbus::Message& msg, LstQuotStatus& lstRet)
{
    sdbus::Message::Map map_lstRet;
    if (!msg.GetMap(2, map_lstRet))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QueryBondQuotByCodeStatusRet!\n");
    }
    ParseLstQuotStatus(map_lstRet, lstRet);
}

void CMsgMng::GetMsg_PurchaseStatusPush(const MapPurchaseStatus& mapPStatus, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Purchase_StatusPush);

    sdbus::Message::Map mapRet;
    BuildMapPurchaseStatus(mapPStatus, mapRet);
    msg.SetMap(2, mapRet);
}

void CMsgMng::ParseMsg_PurchaseStatusPush(const sdbus::Message& msg, MapPurchaseStatus& mapPStatus)
{
    sdbus::Message::Map mapRet;
    if (msg.GetMap(2, mapRet))
    {
        ParseMapPurchaseStatus(mapRet, mapPStatus);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg PurchaseStatusPush!\n");
    }
}

void CMsgMng::GetMsg_IsEditPurchaseValidPush(const Contact& ct, bool bValid, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Purchase_IsEditValidPush);

    sdbus::Message::Map mapCt;
    BuildContact(ct, mapCt);
    msg.SetMap(2, mapCt);

    msg.SetBool(3, bValid);
}

void CMsgMng::ParseMsg_IsEditPurchaseValidPush(const sdbus::Message& msg, Contact& ct, bool& bValid)
{
    bool bSuccess = true;

    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        ParseContact(mapCt, ct);
    }
    else
    {
        bSuccess = false;
    }

    bSuccess &= msg.GetBool(3, bValid);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg IsEditPurchaseValidPush!\n");
    }
}

void CMsgMng::GetMsg_ContactIsDealerPush(const Contact& ct, bool isDealer, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_ContactIsDealerPush);

    sdbus::Message::Map mapCt;
    BuildContact(ct, mapCt);
    msg.SetMap(2, mapCt);

    msg.SetBool(3, isDealer);
}

void CMsgMng::ParseMsg_ContactIsDealerPush(const sdbus::Message& msg, Contact& ct, bool& isDealer)
{
    bool bSuccess = true;

    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        ParseContact(mapCt, ct);
    }
    else
    {
        bSuccess = false;
    }

    bSuccess &= msg.GetBool(3, isDealer);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ContactIsDealerPush!\n");
    }
}

void CMsgMng::GetMsg_ContactInfoPush(const LstPersonInfo& PersonInfos, const LstGroupInfo& GrpInfos, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_ContactInfoPush);

    sdbus::Message::Map mapPerson;
    BuildLstPersonInfo(PersonInfos, mapPerson);
    msg.SetMap(2, mapPerson);

    sdbus::Message::Map mapGroup;
    BuildLstGroupInfo(GrpInfos, mapGroup);
    msg.SetMap(3, mapGroup);
}

void CMsgMng::ParseMsg_ContactInfoPush(const sdbus::Message& msg, LstPersonInfo& PersonInfos, LstGroupInfo& GrpInfos)
{
    sdbus::Message::Map mapPerson;
    if (msg.GetMap(2, mapPerson))
    {
        ParseLstPersonInfo(mapPerson, PersonInfos);
    }

    sdbus::Message::Map mapGroup;
    if (msg.GetMap(3, mapGroup))
    {
        ParseLstGroupInfo(mapGroup, GrpInfos);
    }
}

void CMsgMng::GetMsg_ContactStatusPush(const LstContactStatus& lstStatus, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_ContactStatusPush);

    sdbus::Message::Map mapStatus;
    BuildLstContactStatus(lstStatus, mapStatus);
    msg.SetMap(2, mapStatus);
}

void CMsgMng::ParseMsg_ContactStatusPush(const sdbus::Message& msg, LstContactStatus& lstStatus)
{
    sdbus::Message::Map mapStatus;
    if (msg.GetMap(2, mapStatus))
    {
        ParseLstContactStatus(mapStatus, lstStatus);
    }
}

void CMsgMng::GetMsg_QueryQMIDByQBAccount(const SetString& QBAccounts, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQMIDByQBAccount);

    sdbus::Message::Map mapQBAccounts;
    BuildSetString(QBAccounts, mapQBAccounts);
    msg.SetMap(2, mapQBAccounts);
}

void CMsgMng::ParseMsg_QueryQMIDByQBAccount(const sdbus::Message& msg, SetString& QBAccounts)
{
    sdbus::Message::Map mapQBAccounts;
    if (msg.GetMap(2, mapQBAccounts))
    {
        ParseSetString(mapQBAccounts, QBAccounts);
    }
}

void CMsgMng::GetMsg_QueryQMIDByQBAccountRet(const LstQBAccount2QMID& lstInfo, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryQMIDByQBAccountRet);

    sdbus::Message::Map mapRetInfo;
    BuildLstQBAccount2QMID(lstInfo, mapRetInfo);
    msg.SetMap(2, mapRetInfo);
}

void CMsgMng::ParseMsg_QueryQMIDByQBAccountRet(const sdbus::Message& msg, LstQBAccount2QMID& lstInfo)
{
    sdbus::Message::Map mapRetInfo;
    if (msg.GetMap(2, mapRetInfo))
    {
        ParseLstQBAccount2QMID(mapRetInfo, lstInfo);
    }
}

void CMsgMng::GetMsg_QueryQMRemindConfig(sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_QueryQMRemindConfig);
    msg.SetString(2, MSGCMD_Remind_QueryQMRemindConfig);
}

void CMsgMng::BuildQueryQMRemindConfigRet(const QMRemindConfig& QMRCfg, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_QueryQMRemindConfigRet);

    sdbus::Message::Map mapQMRCfg;
    BuildQMRemindConfig(QMRCfg, mapQMRCfg);
    msg.SetMap(2, mapQMRCfg);
}

void CMsgMng::ParseQueryQMRemindConfigRet(const sdbus::Message& msg, QMRemindConfig& QMRCfg)
{
    sdbus::Message::Map mapQMRCfg;
    if (msg.GetMap(2, mapQMRCfg))
    {
        ParseQMRemindConfig(mapQMRCfg, QMRCfg);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QueryQMRemindConfigRet!\n");
    }
}

void CMsgMng::GetMsg_SetQMRemindConfig(const QMRemindConfig& QMRCfg, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_SetQMRemindConfig);

    sdbus::Message::Map mapQMRCfg;
    BuildQMRemindConfig(QMRCfg, mapQMRCfg);
    msg.SetMap(2, mapQMRCfg);
}

void CMsgMng::ParseMsg_SetQMRemindConfig(const sdbus::Message& msg, QMRemindConfig& QMRCfg)
{
    sdbus::Message::Map mapQMRCfg;
    if (msg.GetMap(2, mapQMRCfg))
    {
        ParseQMRemindConfig(mapQMRCfg, QMRCfg);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg SetQMRemindConfig!\n");
    }
}

void CMsgMng::GetMsg_AddQMRemindKeyItem(const QMRemindKeyItem& Item, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_AddQMRemindKeyItem);

    sdbus::Message::Map mapItem;
    BuildQMRemindKeyItem(Item, mapItem);
    msg.SetMap(2, mapItem);
}

void CMsgMng::ParseMsg_AddQMRemindKeyItem(const sdbus::Message& msg, QMRemindKeyItem& Item)
{
    sdbus::Message::Map mapItem;
    if (msg.GetMap(2, mapItem))
    {
        ParseQMRemindKeyItem(mapItem, Item);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg AddQMRemindKeyItem!\n");
    }
}

void CMsgMng::GetMsg_AddQMRemindKeyItemRet(const std::string& ItemID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_AddQMRemindKeyItemRet);
    msg.SetString(2, ItemID);
}

void CMsgMng::ParseMsg_AddQMRemindKeyItemRet(const sdbus::Message& msg, std::string& ItemID)
{
    if (!msg.GetString(2, ItemID))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg AddQMRemindKeyItemRet!\n");
    }
}

void CMsgMng::GetMsg_ModifyQMRemindKeyItem(const QMRemindKeyItem& Item, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_ModifyQMRemindKeyItem);

    sdbus::Message::Map mapItem;
    BuildQMRemindKeyItem(Item, mapItem);
    msg.SetMap(2, mapItem);
}

void CMsgMng::ParseMsg_ModifyQMRemindKeyItem(const sdbus::Message& msg, QMRemindKeyItem& Item)
{
    sdbus::Message::Map mapItem;
    if (msg.GetMap(2, mapItem))
    {
        ParseQMRemindKeyItem(mapItem, Item);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ModifyQMRemindKeyItem!\n");
    }
}

void CMsgMng::GetMsg_ModifyQMRemindKeyItemRet(bool bSuccess, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_ModifyQMRemindKeyItemRet);
    msg.SetBool(2, bSuccess);
}

void CMsgMng::ParseMsg_ModifyQMRemindKeyItemRet(const sdbus::Message& msg, bool& bSuccess)
{
    if (!msg.GetBool(2, bSuccess))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ModifyQMRemindKeyItemRet!\n");
    }
}

void CMsgMng::GetMsg_DelQMRemindKeyItem(const SetString& setID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_DelQMRemindKeyItem);

    sdbus::Message::Map mapDelID;
    BuildSetString(setID, mapDelID);
    msg.SetMap(2, mapDelID);
}

void CMsgMng::ParseMsg_DelQMRemindKeyItem(const sdbus::Message& msg, SetString& setID)
{
    sdbus::Message::Map mapDelID;
    if (msg.GetMap(2, mapDelID))
    {
        ParseSetString(mapDelID, setID);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg DelQMRemindKeyItem!\n");
    }
}

void CMsgMng::GetMsg_DelQMRemindKeyItemRet(const SetString& setSuccessID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_DelQMRemindKeyItemRet);

    sdbus::Message::Map mapSuccessID;
    BuildSetString(setSuccessID, mapSuccessID);
    msg.SetMap(2, mapSuccessID);
}

void CMsgMng::ParseMsg_DelQMRemindKeyItemRet(const sdbus::Message& msg, SetString& setSuccessID)
{
    sdbus::Message::Map mapSuccessID;
    if (msg.GetMap(2, mapSuccessID))
    {
        ParseSetString(mapSuccessID, setSuccessID);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg DelQMRemindKeyItemRet!\n");
    }
}

void CMsgMng::GetMsg_AddQMRemindFriendItem(const QMRemindFriendItem& Item, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_AddQMRemindFriendItem);

    sdbus::Message::Map mapItem;
    BuildQMRemindFriendItem(Item, mapItem);
    msg.SetMap(2, mapItem);
}

void CMsgMng::ParseMsg_AddQMRemindFriendItem(const sdbus::Message& msg, QMRemindFriendItem& Item)
{
    sdbus::Message::Map mapItem;
    if (msg.GetMap(2, mapItem))
    {
        ParseQMRemindFriendItem(mapItem, Item);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg AddQMRemindFriendItem!\n");
    }
}

void CMsgMng::GetMsg_AddQMRemindFriendItemRet(const std::string& ItemID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_AddQMRemindFriendItemRet);
    msg.SetString(2, ItemID);
}

void CMsgMng::ParseMsg_AddQMRemindFriendItemRet(const sdbus::Message& msg, std::string& ItemID)
{
    if (!msg.GetString(2, ItemID))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg AddQMRemindFriendItemRet!\n");
    }
}

void CMsgMng::GetMsg_ModifyQMRemindFriendItem(const QMRemindFriendItem& Item, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_ModifyQMRemindFriendItem);

    sdbus::Message::Map mapItem;
    BuildQMRemindFriendItem(Item, mapItem);
    msg.SetMap(2, mapItem);
}

void CMsgMng::ParseMsg_ModifyQMRemindFriendItem(const sdbus::Message& msg, QMRemindFriendItem& Item)
{
    sdbus::Message::Map mapItem;
    if (msg.GetMap(2, mapItem))
    {
        ParseQMRemindFriendItem(mapItem, Item);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ModifyQMRemindFriendItem!\n");
    }
}

void CMsgMng::GetMsg_ModifyQMRemindFriendItemRet(bool bSuccess, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_ModifyQMRemindFriendItemRet);
    msg.SetBool(2, bSuccess);
}

void CMsgMng::ParseMsg_ModifyQMRemindFriendItemRet(const sdbus::Message& msg, bool& bSuccess)
{
    if (!msg.GetBool(2, bSuccess))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ModifyQMRemindFriendItemRet!\n");
    }
}

void CMsgMng::GetMsg_DelQMRemindFriendItem(const SetString& setID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_DelQMRemindFriendItem);

    sdbus::Message::Map mapDelID;
    BuildSetString(setID, mapDelID);
    msg.SetMap(2, mapDelID);
}

void CMsgMng::ParseMsg_DelQMRemindFriendItem(const sdbus::Message& msg, SetString& setID)
{
    sdbus::Message::Map mapDelID;
    if (msg.GetMap(2, mapDelID))
    {
        ParseSetString(mapDelID, setID);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg DelQMRemindFriendItem!\n");
    }
}

void CMsgMng::GetMsg_DelQMRemindFriendItemRet(const SetString& setSuccessID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_DelQMRemindFriendItemRet);

    sdbus::Message::Map mapSuccessID;
    BuildSetString(setSuccessID, mapSuccessID);
    msg.SetMap(2, mapSuccessID);
}

void CMsgMng::ParseMsg_DelQMRemindFriendItemRet(const sdbus::Message& msg, SetString& setSuccessID)
{
    sdbus::Message::Map mapSuccessID;
    if (msg.GetMap(2, mapSuccessID))
    {
        ParseSetString(mapSuccessID, setSuccessID);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg DelQMRemindFriendItemRet!\n");
    }
}

void CMsgMng::GetMsg_SetQMRemindType(unsigned int nRemindType, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_SetQMRemindType);
    msg.SetUInt32(2, nRemindType);
}

void CMsgMng::ParseMsg_SetQMRemindType(const sdbus::Message& msg, unsigned int& nRemindType)
{
    if (!msg.GetUInt32(2, nRemindType))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg SetQMRemindType!\n");
    }
}

void CMsgMng::GetMsg_SetQMRemindTypeRet(bool bSuccess, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_Remind_SetQMRemindTypeRet);
    msg.SetBool(2, bSuccess);
}

void CMsgMng::ParseMsg_SetQMRemindTypeRet(const sdbus::Message& msg, bool& bSuccess)
{
    if (!msg.GetBool(2, bSuccess))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg SetQMRemindTypeRet!\n");
    }
}

void CMsgMng::GetMsg_OpenNewsBulletin(const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_OpenNewsBulletin);
    msg.SetString(2, sWndID);
}

void CMsgMng::ParseMsg_OpenNewsBulletin(const sdbus::Message& msg, std::string& sWndID)
{
    if (!msg.GetString(2, sWndID))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg OpenNewsBulletin!\n");
    }
}

void CMsgMng::GetMsg_QueryCustomService(sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryCustomService);
    msg.SetString(2, MSGCMD_QueryCustomService);
}
void CMsgMng::GetMsg_QueryCustomServiceRet(const Contact& ct, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QueryCustomServiceRet);

    sdbus::Message::Map mapCt;
    BuildContact(ct, mapCt);
    msg.SetMap(2, mapCt);
}

void CMsgMng::ParseMsg_QueryCustomServiceRet(const sdbus::Message& msg, Contact& ct)
{
    sdbus::Message::Map mapCt;
    if (msg.GetMap(2, mapCt))
    {
        ParseContact(mapCt, ct);
    }
    else
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QueryCustomServiceRet!\n");
    }
}

void CMsgMng::GetMsg_QBModifyPwd(const std::string& sNewPwd, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_QBModifyPwd);
    msg.SetString(2, sNewPwd);
}

void CMsgMng::ParseMsg_QBModifyPwd(const sdbus::Message& msg, std::string& sNewPwd)
{
    if (!msg.GetString(2, sNewPwd))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QBModifyPwd!\n");
    }
}

void CMsgMng::GetMsg_ShareBond(const LstContact& lstCt, const LstBondShare& lstBS, const std::string& sWndID, sdbus::Message& msg)
{
    msg.SetString(1, MSGCMD_ShareBond);

    sdbus::Message::Map mapIn;
    BuildLstContact(lstCt, mapIn);
    msg.SetMap(2, mapIn);

    sdbus::Message::List lst_BS;
    BuildLstBondShare(lstBS, lst_BS);
    msg.SetList(3, lst_BS);

    msg.SetString(4, sWndID);
}

void CMsgMng::ParseMsg_ShareBond(const sdbus::Message& msg, LstContact& lstCt, LstBondShare& lstBS, std::string& sWndID)
{
    bool bSuccess = true;

    sdbus::Message::Map mapOut;
    if (msg.GetMap(2, mapOut))
    {
        ParseLstContact(mapOut, lstCt);
    }
    else
    {
        bSuccess = false;
    }
    

    sdbus::Message::List lst_BS;
    if (msg.GetList(3, lst_BS))
    {
        ParseLstBondShare(lst_BS, lstBS);
    }
    else
    {
        bSuccess = false;
    }

    bSuccess &= msg.GetString(4, sWndID);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ShareBond!\n");
    }
}

/////////element build&parse/////////

void CMsgMng::BuildLstString(const std::list<std::string>& lstString, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (std::list<std::string>::const_iterator iter = lstString.begin(); iter != lstString.end(); ++iter)
	{
		mapRet.SetString(nPos, *iter);
		nPos++;
	}
}

void CMsgMng::ParseLstString(const sdbus::Message::Map& mapIn, std::list<std::string>& lstString)
{
	lstString.clear();
	for (int i = 0; i< mapIn.Size(); ++i)
	{
		std::string sTemp;
		mapIn.GetString(i+1, sTemp);
		lstString.push_back(sTemp);
	}
}

void CMsgMng::BuildSetUInt64(const SetUInt64& setIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (SetUInt64::const_iterator iter = setIn.begin(); iter != setIn.end(); ++iter)
	{
		mapRet.SetUInt64(nPos, *iter);
		nPos++;
	}
}

void CMsgMng::ParseSetUInt64(const sdbus::Message::Map& mapIn, SetUInt64& setRet)
{
	setRet.clear();
	for (int i = 0; i< mapIn.Size(); ++i)
	{
		sdbus::uint64_t ui64;
		mapIn.GetUInt64(i+1, ui64);
		setRet.insert(ui64);
	}
}

void CMsgMng::BuildSetString(const SetString& setIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (SetString::const_iterator iter = setIn.begin(); iter != setIn.end(); ++iter)
    {
        mapRet.SetString(nPos, *iter);
        nPos++;
    }
}

void CMsgMng::ParseSetString(const sdbus::Message::Map& mapIn, SetString& setRet)
{
    setRet.clear();
    for (int i = 0; i< mapIn.Size(); ++i)
    {
        std::string sVal;
        mapIn.GetString(i+1, sVal);
        setRet.insert(sVal);
    }
}

void CMsgMng::BuildKeyValues(const KeyValues& kvIn, sdbus::Message::Map& mapRet)
{

}

void CMsgMng::ParseKeyValues(const sdbus::Message::Map& mapIn, KeyValues& kvRet)
{

}

void CMsgMng::BuildLstMultilanguageStr(const LstMultilanguageStr& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstMultilanguageStr::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildMultilanguageStr(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildMultilanguageStr(const MultilanguageStr& ItemIn, sdbus::Message::Map& mapRet)
{
	mapRet.SetString(1, ItemIn.sDisplay);
	mapRet.SetString(2, ItemIn.sEnumVal);
}

void CMsgMng::ParseLstMultilanguageStr(const sdbus::Message::Map& mapIn, LstMultilanguageStr& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		MultilanguageStr ParseOut;
		ParseMultilanguageStr(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseMultilanguageStr(const sdbus::Message::Map& mapIn, MultilanguageStr& ItemOut)
{
	if (mapIn.Size() != 2)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse MultilanguageStr!\n");
		return;
	}

	mapIn.GetString(1, ItemOut.sDisplay);
	mapIn.GetString(2, ItemOut.sEnumVal);
}

void CMsgMng::BuildLstTermInfo(const LstTermInfo& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstTermInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildTermInfo(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildTermInfo(const TermInfo& ItemIn, sdbus::Message::Map& mapRet)
{
	mapRet.SetString(1, ItemIn.sDisplay);

	mapRet.SetUInt8(2, ItemIn.nTermType);

	sdbus::Message::Map mapEnumVal;
	BuildLstString(ItemIn.LstEnumVal, mapEnumVal);
	mapRet.SetMap(3, mapEnumVal);
}

void CMsgMng::ParseLstTermInfo(const sdbus::Message::Map& mapIn, LstTermInfo& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		TermInfo ParseOut;
		ParseTermInfo(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseTermInfo(const sdbus::Message::Map& mapIn, TermInfo& ItemOut)
{
	if (mapIn.Size() != 3)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse TermInfo!\n");
		return;
	}

	mapIn.GetString(1, ItemOut.sDisplay);

	sdbus::uint8_t ui8;
	mapIn.GetUInt8(2, ui8);
	ItemOut.nTermType = ui8;

	sdbus::Message::Map mapEnumVal;
	mapIn.GetMap(3, mapEnumVal);
	ParseLstString(mapEnumVal, ItemOut.LstEnumVal);
}

void CMsgMng::BuildLstQuotation(const LstQuotation& lstQuot, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstQuotation::const_iterator iter = lstQuot.begin(); iter != lstQuot.end(); ++iter)
	{
		sdbus::Message::Map QuotItem;
		BuildQuotation(*iter, QuotItem);
		mapRet.SetMap(nPos, QuotItem);
		nPos++;
	}
}

void CMsgMng::BuildQuotation(const Quotation& Quot, sdbus::Message::Map& mapRet)
{
	mapRet.SetString(1, Quot.sQuotationID);

	sdbus::Message::Map mapDirect;
	BuildMultilanguageStr(Quot.sDirect, mapDirect);
	mapRet.SetMap(2, mapDirect);
	
	sdbus::Message::Map mapAssetsType;
	BuildMultilanguageStr(Quot.sAssetsType, mapAssetsType);
	mapRet.SetMap(3, mapAssetsType);

	sdbus::Message::Map mapTerms;
	BuildLstTermInfo(Quot.lstTerms, mapTerms);
	mapRet.SetMap(4, mapTerms);

	sdbus::Message::Map mapCount;
	BuildMultilanguageStr(Quot.sCount, mapCount);
	mapRet.SetMap(5, mapCount);

    sdbus::Message::Map mapPrice;
    BuildMultilanguageStr(Quot.sPrice, mapPrice);
	mapRet.SetMap(6, mapPrice);

	mapRet.SetUInt64(7, Quot.tExpirationTime);
	mapRet.SetInt8(8, Quot.nCancelType);

	sdbus::Message::Map mapTags;
	BuildLstMultilanguageStr(Quot.lstTags, mapTags);
	mapRet.SetMap(9, mapTags);

	mapRet.SetString(10, Quot.sMemo);
}

void CMsgMng::ParseLstQuotation(const sdbus::Message::Map& mapIn, LstQuotation& lstQuot)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map MapQuotItem;
		mapIn.GetMap(i+1, MapQuotItem);
		Quotation QuotItem;
		ParseQuotation(MapQuotItem, QuotItem);
		lstQuot.push_back(QuotItem);
	}
}

void CMsgMng::ParseQuotation(const sdbus::Message::Map& mapIn, Quotation& Quot)
{
	if (mapIn.Size() != 10)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Quotation!\n");
		return;
	}
	mapIn.GetString(1, Quot.sQuotationID);

	sdbus::Message::Map mapDirect;
	mapIn.GetMap(2, mapDirect);
	ParseMultilanguageStr(mapDirect, Quot.sDirect);

	sdbus::Message::Map mapAssetsType;
	mapIn.GetMap(3,	mapAssetsType);
	ParseMultilanguageStr(mapAssetsType, Quot.sAssetsType);

	sdbus::Message::Map mapTerms;
	mapIn.GetMap(4, mapTerms);
	ParseLstTermInfo(mapTerms, Quot.lstTerms);

	sdbus::Message::Map mapCount;
	mapIn.GetMap(5, mapCount);
	ParseMultilanguageStr(mapCount, Quot.sCount);

    sdbus::Message::Map mapPrice;
    mapIn.GetMap(6, mapPrice);
	ParseMultilanguageStr(mapPrice, Quot.sPrice);

	sdbus::uint64_t t64;
	mapIn.GetUInt64(7, t64);
	Quot.tExpirationTime = t64;

	sdbus::int8_t t8;
	mapIn.GetInt8(8, t8);
	Quot.nCancelType = t8;

	sdbus::Message::Map mapTags;
	mapIn.GetMap(9, mapTags);
	ParseLstMultilanguageStr(mapTags, Quot.lstTags);

	mapIn.GetString(10, Quot.sMemo);
}

void CMsgMng::BuildLstQuotationMngInfo(const LstQuotationMngInfo& lstQuotMngInfo, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstQuotationMngInfo::const_iterator iter = lstQuotMngInfo.begin(); iter != lstQuotMngInfo.end(); ++iter)
	{
		sdbus::Message::Map QuotMngInfoItem;
		BuildQuotationMngInfo(*iter, QuotMngInfoItem);
		mapRet.SetMap(nPos, QuotMngInfoItem);
		nPos++;
	}
}

void CMsgMng::BuildQuotationMngInfo(const QuotationMngInfo& QuotMngIngo, sdbus::Message::Map& mapRet)
{
	sdbus::Message::Map mapQuotItem;
	BuildQuotation(QuotMngIngo.Quot, mapQuotItem);
	mapRet.SetMap(1, mapQuotItem);

	sdbus::Message::Map mapCts;
	BuildLstContact(QuotMngIngo.Contacts, mapCts);
	mapRet.SetMap(2, mapCts);

	mapRet.SetUInt64(3, QuotMngIngo.SendTime);

	mapRet.SetInt8(4, QuotMngIngo.nMngType);
}

void CMsgMng::ParseLstQuotationMngInfo(const sdbus::Message::Map& mapIn, LstQuotationMngInfo& lstQuotMngInfo)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		QuotationMngInfo ParseOut;
		ParseQuotationMngInfo(ParseIn, ParseOut);
		lstQuotMngInfo.push_back(ParseOut);
	}
}

void CMsgMng::ParseQuotationMngInfo(const sdbus::Message::Map& mapIn, QuotationMngInfo& QuotMngInfo)
{
	if (mapIn.Size() != 4)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QuotationMngInfo!\n");
		return;
	}

	sdbus::Message::Map mapQuotItem;
	mapIn.GetMap(1, mapQuotItem);
	ParseQuotation(mapQuotItem, QuotMngInfo.Quot);

	sdbus::Message::Map mapCts;
	mapIn.GetMap(2, mapCts);
	ParseLstContact(mapCts, QuotMngInfo.Contacts);

	sdbus::uint64_t t64;
	mapIn.GetUInt64(3, t64);
	QuotMngInfo.SendTime = t64;

	sdbus::int8_t t8;
	mapIn.GetInt8(4, t8);
	QuotMngInfo.nMngType = t8;
}

void CMsgMng::BuildLstQuotSendInfo(const LstQuotSendInfo& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstQuotSendInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildQuotSendInfo(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildQuotSendInfo(const QuotSendInfo& ItemIn, sdbus::Message::Map& mapRet)
{
	sdbus::Message::Map mapSendTo;
	BuildContact(ItemIn.SendTo, mapSendTo);
	mapRet.SetMap(1, mapSendTo);

	sdbus::Message::Map mapQuots;
	BuildLstQuotation(ItemIn.lstQuots, mapQuots);
	mapRet.SetMap(2, mapQuots);

	mapRet.SetUInt64(3, ItemIn.SendTime);

	mapRet.SetInt8(4, ItemIn.nMngType);
}

void CMsgMng::ParseLstQuotSendInfo(const sdbus::Message::Map& mapIn, LstQuotSendInfo& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		QuotSendInfo ParseOut;
		ParseQuotSendInfo(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseQuotSendInfo(const sdbus::Message::Map& mapIn, QuotSendInfo& ItemOut)
{
	if (mapIn.Size() != 4)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QuotSendInfo!\n");
		return;
	}

	sdbus::Message::Map mapSendTo;
	mapIn.GetMap(1, mapSendTo);
	ParseContact(mapSendTo, ItemOut.SendTo);

	sdbus::Message::Map mapQuots;
	mapIn.GetMap(2, mapQuots);
	ParseLstQuotation(mapQuots, ItemOut.lstQuots);

	sdbus::uint64_t t64;
	mapIn.GetUInt64(3, t64);
	ItemOut.SendTime = t64;

	sdbus::int8_t t8;
	mapIn.GetInt8(4, t8);
	ItemOut.nMngType = t8;
}

void CMsgMng::BuildLstQuotRecvInfo(const LstQuotRecvInfo& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstQuotRecvInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildQuotRecvInfo(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildQuotRecvInfo(const QuotRecvInfo& ItemIn, sdbus::Message::Map& mapRet)
{
	sdbus::Message::Map mapRecvFrom;
	BuildContact(ItemIn.RecvFrom, mapRecvFrom);
	mapRet.SetMap(1, mapRecvFrom);

	sdbus::Message::Map mapSendFrom;
	BuildContact(ItemIn.SendFrom, mapSendFrom);
	mapRet.SetMap(2, mapSendFrom);

	sdbus::Message::Map mapQuots;
	BuildLstQuotation(ItemIn.lstQuots, mapQuots);
	mapRet.SetMap(3, mapQuots);

	mapRet.SetUInt64(4, ItemIn.RecvTime);

	mapRet.SetInt8(5, ItemIn.nMngType);
}

void CMsgMng::ParseLstQuotRecvInfo(const sdbus::Message::Map& mapIn, LstQuotRecvInfo& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		QuotRecvInfo ParseOut;
		ParseQuotRecvInfo(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseQuotRecvInfo(const sdbus::Message::Map& mapIn, QuotRecvInfo& ItemOut)
{
	if (mapIn.Size() != 5)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QuotRecvInfo!\n");
		return;
	}

	sdbus::Message::Map mapRecvFrom;
	mapIn.GetMap(1, mapRecvFrom);
	ParseContact(mapRecvFrom, ItemOut.RecvFrom);

	sdbus::Message::Map mapSendFrom;
	mapIn.GetMap(2, mapSendFrom);
	ParseContact(mapSendFrom, ItemOut.SendFrom);

	sdbus::Message::Map mapQuots;
	mapIn.GetMap(3, mapQuots);
	ParseLstQuotation(mapQuots, ItemOut.lstQuots);

	sdbus::uint64_t t64;
	mapIn.GetUInt64(4, t64);
	ItemOut.RecvTime = t64;

	sdbus::int8_t t8;
	mapIn.GetInt8(5, t8);
	ItemOut.nMngType = t8;
}

void CMsgMng::BuildLstQuotReplyInfo(const LstQuotReplyInfo& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstQuotReplyInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildQuotReplyInfo(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildQuotReplyInfo(const QuotReplyInfo& ItemIn, sdbus::Message::Map& mapRet)
{
	sdbus::Message::Map mapReplyTo;
	BuildContact(ItemIn.ReplyTo, mapReplyTo);
	mapRet.SetMap(1, mapReplyTo);

	sdbus::Message::Map mapQuot;
	BuildQuotation(ItemIn.Quot, mapQuot);
	mapRet.SetMap(2, mapQuot);
}

void CMsgMng::ParseLstQuotReplyInfo(const sdbus::Message::Map& mapIn, LstQuotReplyInfo& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		QuotReplyInfo ParseOut;
		ParseQuotReplyInfo(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseQuotReplyInfo(const sdbus::Message::Map& mapIn, QuotReplyInfo& ItemOut)
{
	if (mapIn.Size() != 2)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QuotReplyInfo!\n");
		return;
	}

	sdbus::Message::Map mapReplyTo;
	mapIn.GetMap(1, mapReplyTo);
	ParseContact(mapReplyTo, ItemOut.ReplyTo);

	sdbus::Message::Map mapQuot;
	mapIn.GetMap(2, mapQuot);
	ParseQuotation(mapQuot, ItemOut.Quot);
}

void CMsgMng::BuildLstContact(const LstContact& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstContact::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildContact(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildContact(const Contact& ct, sdbus::Message::Map& mapRet)
{
	mapRet.SetUInt64(1, ct.nContactID);
	mapRet.SetInt8(2, ct.nContactType);
}

void CMsgMng::ParseLstContact(const sdbus::Message::Map& mapIn, LstContact& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		Contact ParseOut;
		ParseContact(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseContact(const sdbus::Message::Map& mapIn, Contact& ct)
{
	if (mapIn.Size() != 2)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Contact!\n");
		return;
	}

	mapIn.GetUInt64(1, ct.nContactID);
	sdbus::int8_t int8;
	mapIn.GetInt8(2, int8);
	ct.nContactType = int8;
}

void CMsgMng::BuildLstPersonInfo(const LstPersonInfo& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstPersonInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildPersonInfo(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildPersonInfo(const PersonInfo& ItemIn, sdbus::Message::Map& mapRet)
{
	mapRet.SetUInt64(1, ItemIn.nID);
	mapRet.SetString(2, ItemIn.sDisplayName);
	mapRet.SetString(3, ItemIn.sTel);
	mapRet.SetString(4, ItemIn.sInstitution);
	mapRet.SetString(5, ItemIn.sInstitutionID);
	mapRet.SetString(6, ItemIn.sInstitutionType);
	mapRet.SetString(7, ItemIn.sMobile);
	mapRet.SetRaw(8, ItemIn.pAvatar, ItemIn.nAvatarSize);
    mapRet.SetString(9, ItemIn.sQBAccount);
}

void CMsgMng::ParseLstPersonInfo(const sdbus::Message::Map& mapIn, LstPersonInfo& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		PersonInfo ParseOut;
		ParsePersonInfo(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParsePersonInfo(const sdbus::Message::Map& mapIn, PersonInfo& ItemOut)
{
	if (mapIn.Size() < 7)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse PersonInfo!\n");
		return;
	}

	mapIn.GetUInt64(1, ItemOut.nID);
	mapIn.GetString(2, ItemOut.sDisplayName);
	mapIn.GetString(3, ItemOut.sTel);
	mapIn.GetString(4, ItemOut.sInstitution);
	mapIn.GetString(5, ItemOut.sInstitutionID);
	mapIn.GetString(6, ItemOut.sInstitutionType);
	mapIn.GetString(7, ItemOut.sMobile);

   	sdbus::string sRawData("");
	if (mapIn.GetRaw(8, sRawData))
	{
		ItemOut.SetAvatar(sRawData.data(), sRawData.length());
	}

    mapIn.GetString(9, ItemOut.sQBAccount);
}

void CMsgMng::BuildLstGroupInfo(const LstGroupInfo& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstGroupInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildGroupInfo(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildGroupInfo(const GroupInfo& ItemIn, sdbus::Message::Map& mapRet)
{
	mapRet.SetUInt64(1, ItemIn.nID);
	mapRet.SetString(2, ItemIn.sDisplayName);
	mapRet.SetRaw(3, ItemIn.pAvatar, ItemIn.nAvatarSize);
}

void CMsgMng::ParseLstGroupInfo(const sdbus::Message::Map& mapIn, LstGroupInfo& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		GroupInfo ParseOut;
		ParseGroupInfo(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseGroupInfo(const sdbus::Message::Map& mapIn, GroupInfo& ItemOut)
{
	if (mapIn.Size() < 2)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse GroupInfo!\n");
		return;
	}

	mapIn.GetUInt64(1, ItemOut.nID);
	mapIn.GetString(2, ItemOut.sDisplayName);

	if (mapIn.Size() == 3)
	{
		sdbus::string sRawData;
		mapIn.GetRaw(3, sRawData);
		ItemOut.SetAvatar(sRawData.data(), sRawData.length());
	}
}

void CMsgMng::BuildLstBondItem(const LstBondItem& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstBondItem::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildBondItem(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildBondItem(const BondItem& ItemIn, sdbus::Message::Map& mapRet)
{
	//mapRet.SetString(1, ItemIn.m_sBondKey);
	//mapRet.SetString(2, ItemIn.m_sBondID);
	//mapRet.SetString(3, ItemIn.m_sListedMarket);
	mapRet.SetString(4, ItemIn.m_sCombBondKey);
	mapRet.SetString(5, ItemIn.m_sCombBondID);
	//mapRet.SetString(6, ItemIn.m_sFullName);
	mapRet.SetString(7, ItemIn.m_sShortName);
	//mapRet.SetString(8, ItemIn.m_sFullNameEn);
	//mapRet.SetString(9, ItemIn.m_sShortNameEn);
	mapRet.SetString(10, ItemIn.m_sJianpin);
	mapRet.SetString(11, ItemIn.m_sQuanpin);
	mapRet.SetString(12, ItemIn.m_sMarketType);
	//mapRet.SetString(13, ItemIn.m_sBondSubType);
	mapRet.SetString(14, ItemIn.m_sIssuerRating);
	mapRet.SetString(15, ItemIn.m_sBondRating);
	//mapRet.SetString(16, ItemIn.m_sListDate);
	//mapRet.SetString(17, ItemIn.m_sInterestStartDate);
	//mapRet.SetString(18, ItemIn.m_sMaturityDate);
	//mapRet.SetString(19, ItemIn.m_sPaymentDate);
	//mapRet.SetString(20, ItemIn.m_sOptionDate);
	//mapRet.SetString(21, ItemIn.m_sRateType);
	//mapRet.SetString(22, ItemIn.m_sOptionType);
	//mapRet.SetString(23, ItemIn.m_sMaturityTerm);
	//mapRet.SetString(24, ItemIn.m_sTermToMaturity);
	//mapRet.SetString(25, ItemIn.m_sFRNIndexID);
	//mapRet.SetDouble(26, ItemIn.m_fCouponRateCurrent);
	//mapRet.SetDouble(27, ItemIn.m_fPlannedIssueAmount);
	//mapRet.SetString(28, ItemIn.m_sIssuerCode);
	//mapRet.SetString(29, ItemIn.m_sInstitutionType);
	//mapRet.SetString(30, ItemIn.m_sYieldCurveType);
	//mapRet.SetString(31, ItemIn.m_sEstcleanprice);
	//mapRet.SetString(32, ItemIn.m_sEstPrice);
	//mapRet.SetString(33, ItemIn.m_sAuctionDateStart);
	//mapRet.SetString(34, ItemIn.m_sAuctionDateEnd);
	//mapRet.SetString(35, ItemIn.m_sAnnounceDate);
	//mapRet.SetString(36, ItemIn.m_sIssueStartDate);
	//mapRet.SetString(37, ItemIn.m_sIssueEndDate);
	//mapRet.SetString(38, ItemIn.m_sIsUnderwriter);
	//mapRet.SetInt8(39, ItemIn.m_nIsQuotTopflag);
	//mapRet.SetInt8(40, ItemIn.m_nIsWarrant);
	//mapRet.SetString(41, ItemIn.m_sMortgate);
	//mapRet.SetString(42, ItemIn.m_sCrossmarket);
	//mapRet.SetString(43, ItemIn.m_sIsMunicipal);
	mapRet.SetString(44, ItemIn.m_sRemainDate);
	mapRet.SetInt8(45, ItemIn.m_nBondType);
}

void CMsgMng::ParseLstBondItem(const sdbus::Message::Map& mapIn, LstBondItem& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		BondItem ParseOut;
		ParseBondItem(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseBondItem(const sdbus::Message::Map& mapIn, BondItem& ItemOut)
{
    bool bSuccess = true;
	//bSuccess &= mapIn.GetString(1, ItemOut.m_sBondKey);
	//bSuccess &= mapIn.GetString(2, ItemOut.m_sBondID);
	//bSuccess &= mapIn.GetString(3, ItemOut.m_sListedMarket);
	bSuccess &= mapIn.GetString(4, ItemOut.m_sCombBondKey);
	bSuccess &= mapIn.GetString(5, ItemOut.m_sCombBondID);
	//bSuccess &= mapIn.GetString(6, ItemOut.m_sFullName);
	bSuccess &= mapIn.GetString(7, ItemOut.m_sShortName);
	//bSuccess &= mapIn.GetString(8, ItemOut.m_sFullNameEn);
	//bSuccess &= mapIn.GetString(9, ItemOut.m_sShortNameEn);
	bSuccess &= mapIn.GetString(10, ItemOut.m_sJianpin);
	bSuccess &= mapIn.GetString(11, ItemOut.m_sQuanpin);
	bSuccess &= mapIn.GetString(12, ItemOut.m_sMarketType);
	//bSuccess &= mapIn.GetString(13, ItemOut.m_sBondSubType);
	bSuccess &= mapIn.GetString(14, ItemOut.m_sIssuerRating);
	bSuccess &= mapIn.GetString(15, ItemOut.m_sBondRating);
	//bSuccess &= mapIn.GetString(16, ItemOut.m_sListDate);
	//bSuccess &= mapIn.GetString(17, ItemOut.m_sInterestStartDate);
	//bSuccess &= mapIn.GetString(18, ItemOut.m_sMaturityDate);
	//bSuccess &= mapIn.GetString(19, ItemOut.m_sPaymentDate);
	//bSuccess &= mapIn.GetString(20, ItemOut.m_sOptionDate);
	//bSuccess &= mapIn.GetString(21, ItemOut.m_sRateType);
	//bSuccess &= mapIn.GetString(22, ItemOut.m_sOptionType);
	//bSuccess &= mapIn.GetString(23, ItemOut.m_sMaturityTerm);
	//bSuccess &= mapIn.GetString(24, ItemOut.m_sTermToMaturity);
	//bSuccess &= mapIn.GetString(25, ItemOut.m_sFRNIndexID);
	//bSuccess &= mapIn.GetDouble(26, ItemOut.m_fCouponRateCurrent);
	//bSuccess &= mapIn.GetDouble(27, ItemOut.m_fPlannedIssueAmount);
	//bSuccess &= mapIn.GetString(28, ItemOut.m_sIssuerCode);
	//bSuccess &= mapIn.GetString(29, ItemOut.m_sInstitutionType);
	//bSuccess &= mapIn.GetString(30, ItemOut.m_sYieldCurveType);
	//bSuccess &= mapIn.GetString(31, ItemOut.m_sEstcleanprice);
	//bSuccess &= mapIn.GetString(32, ItemOut.m_sEstPrice);
	//bSuccess &= mapIn.GetString(33, ItemOut.m_sAuctionDateStart);
	//bSuccess &= mapIn.GetString(34, ItemOut.m_sAuctionDateEnd);
	//bSuccess &= mapIn.GetString(35, ItemOut.m_sAnnounceDate);
	//bSuccess &= mapIn.GetString(36, ItemOut.m_sIssueStartDate);
	//bSuccess &= mapIn.GetString(37, ItemOut.m_sIssueEndDate);
	//bSuccess &= mapIn.GetString(38, ItemOut.m_sIsUnderwriter);
	sdbus::int8_t i8;
	//bSuccess &= mapIn.GetInt8(39, i8);
	//ItemOut.m_nIsQuotTopflag = i8;
	//bSuccess &= mapIn.GetInt8(40, i8);
	//ItemOut.m_nIsWarrant = i8;
	//bSuccess &= mapIn.GetString(41, ItemOut.m_sMortgate);
	//bSuccess &= mapIn.GetString(42, ItemOut.m_sCrossmarket);
	//bSuccess &= mapIn.GetString(43, ItemOut.m_sIsMunicipal);
	bSuccess &= mapIn.GetString(44, ItemOut.m_sRemainDate);
	bSuccess &= mapIn.GetInt8(45, i8);
	ItemOut.m_nBondType = i8;

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse BondItem!\n");
    }
}


void CMsgMng::BuildLstMsgInfo(const LstMsgInfo& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstMsgInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildMsgInfo(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildMsgInfo(const MsgInfo& ItemIn, sdbus::Message::Map& mapRet)
{
	sdbus::Message::Map ct;
	BuildContact(ItemIn.MsgFrom, ct);
	mapRet.SetMap(1, ct);
	mapRet.SetString(2, ItemIn.sMsgDisplay);
	mapRet.SetUInt64(3, ItemIn.RecvTime);
}

void CMsgMng::ParseLstMsgInfo(const sdbus::Message::Map& mapIn, LstMsgInfo& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		MsgInfo ParseOut;
		ParseMsgInfo(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseMsgInfo(const sdbus::Message::Map& mapIn, MsgInfo& ItemOut)
{
	if (mapIn.Size() != 3)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse MsgInfo!\n");
		return;
	}

	sdbus::Message::Map ct;
	mapIn.GetMap(1, ct);
	ParseContact(ct, ItemOut.MsgFrom);

	mapIn.GetString(2, ItemOut.sMsgDisplay);
	
	sdbus::uint64_t t64;
	mapIn.GetUInt64(3, t64);
	ItemOut.RecvTime = t64;
}

void CMsgMng::BuildLstBondQuotInfo(const LstBondQuotInfo& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstBondQuotInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildBondQuotInfo(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildBondQuotInfo(const BondQuotInfo& ItemIn, sdbus::Message::Map& mapRet)
{
	mapRet.SetString(1, ItemIn.sCombBondKey);
	mapRet.SetString(2, ItemIn.sBid);
	mapRet.SetString(3, ItemIn.sVolBid);
	mapRet.SetString(4, ItemIn.sOfr);
	mapRet.SetString(5, ItemIn.sVolOfr);
	mapRet.SetUInt64(6, ItemIn.QuotTime);
}

void CMsgMng::ParseLstBondQuotInfo(const sdbus::Message::Map& mapIn, LstBondQuotInfo& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		BondQuotInfo ParseOut;
		ParseBondQuotInfo(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseBondQuotInfo(const sdbus::Message::Map& mapIn, BondQuotInfo& ItemOut)
{
	if (mapIn.Size() != 6)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse ParseBondQuotInfo!\n");
		return;
	}
	mapIn.GetString(1, ItemOut.sCombBondKey);
	mapIn.GetString(2, ItemOut.sBid);
	mapIn.GetString(3, ItemOut.sVolBid);
	mapIn.GetString(4, ItemOut.sOfr);
	mapIn.GetString(5, ItemOut.sVolOfr);

	sdbus::uint64_t t64;
	mapIn.GetUInt64(6, t64);
	ItemOut.QuotTime = t64;
}

void CMsgMng::BuildLstBondQuotByCode(const LstBondQuotByCode& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstBondQuotByCode::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildBondQuotByCode(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildBondQuotByCode(const BondQuotByCode& ItemIn, sdbus::Message::Map& mapRet)
{
	mapRet.SetString(1, ItemIn.sQuotID);

	sdbus::Message::Map mapBQInfo;
	BuildBondQuotInfo(ItemIn.BQInfo, mapBQInfo);
	mapRet.SetMap(2, mapBQInfo);

	mapRet.SetUInt64(3, ItemIn.tExpirationTime);

	mapRet.SetInt8(4, ItemIn.nCancelType);

	sdbus::Message::Map mapTags;
	BuildLstMultilanguageStr(ItemIn.lstTags, mapTags);
	mapRet.SetMap(5, mapTags);

	mapRet.SetString(6, ItemIn.sMemo);
}

void CMsgMng::ParseLstBondQuotByCode(const sdbus::Message::Map& mapIn, LstBondQuotByCode& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		BondQuotByCode ParseOut;
		ParseBondQuotByCode(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseBondQuotByCode(const sdbus::Message::Map& mapIn, BondQuotByCode& ItemOut)
{
	if (mapIn.Size() != 6)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse BondQuotByCode!\n");
		return;
	}
	mapIn.GetString(1, ItemOut.sQuotID);

	sdbus::Message::Map mapBQInfo;
	mapIn.GetMap(2, mapBQInfo);
	ParseBondQuotInfo(mapBQInfo, ItemOut.BQInfo);

	sdbus::uint64_t t64;
	mapIn.GetUInt64(3, t64);
	ItemOut.tExpirationTime = t64;

	sdbus::int8_t t8;
	mapIn.GetInt8(4, t8);
	ItemOut.nCancelType = t8;

	sdbus::Message::Map mapTags;
	mapIn.GetMap(5, mapTags);
	ParseLstMultilanguageStr(mapTags, ItemOut.lstTags);

	mapIn.GetString(6, ItemOut.sMemo);
}

void CMsgMng::BuildLstBondQuotByCodeSendInfo(const LstBondQuotByCodeSendInfo& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstBondQuotByCodeSendInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildBondQuotByCodeSendInfo(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildBondQuotByCodeSendInfo(const BondQuotByCodeSendInfo& ItemIn, sdbus::Message::Map& mapRet)
{
	sdbus::Message::Map mapSendTo;
	BuildContact(ItemIn.SendTo, mapSendTo);
	mapRet.SetMap(1, mapSendTo);

	sdbus::Message::Map mapQuots;
	BuildLstBondQuotByCode(ItemIn.lstQuots, mapQuots);
	mapRet.SetMap(2, mapQuots);

	mapRet.SetUInt64(3, ItemIn.SendTime);

	mapRet.SetInt8(4, ItemIn.nMngType);
}

void CMsgMng::ParseLstBondQuotByCodeSendInfo(const sdbus::Message::Map& mapIn, LstBondQuotByCodeSendInfo& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		BondQuotByCodeSendInfo ParseOut;
		ParseBondQuotByCodeSendInfo(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseBondQuotByCodeSendInfo(const sdbus::Message::Map& mapIn, BondQuotByCodeSendInfo& ItemOut)
{
	if (mapIn.Size() != 4)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse BondQuotByCodeSendInfo!\n");
		return;
	}

	sdbus::Message::Map mapSendTo;
	mapIn.GetMap(1, mapSendTo);
	ParseContact(mapSendTo, ItemOut.SendTo);

	sdbus::Message::Map mapQuots;
	mapIn.GetMap(2, mapQuots);
	ParseLstBondQuotByCode(mapQuots, ItemOut.lstQuots);

	sdbus::uint64_t t64;
	mapIn.GetUInt64(3, t64);
	ItemOut.SendTime = t64;

	sdbus::int8_t t8;
	mapIn.GetInt8(4, t8);
	ItemOut.nMngType = t8;
}

void CMsgMng::BuildLstCondition(const LstCondition& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstCondition::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildCondition(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildCondition(const Condition& ItemIn, sdbus::Message::Map& mapRet)
{
	sdbus::Message::Map mapName;
	BuildMultilanguageStr(ItemIn.sName, mapName);
	mapRet.SetMap(1, mapName);

	sdbus::Message::Map mapInfo;
	BuildKeyValues(ItemIn.ConditionInfo, mapInfo);
	mapRet.SetMap(2, mapInfo);
}

void CMsgMng::ParseLstCondition(const sdbus::Message::Map& mapIn, LstCondition& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		Condition ParseOut;
		ParseCondition(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseCondition(const sdbus::Message::Map& mapIn, Condition& ItemOut)
{
	if (mapIn.Size() != 2)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Condition!\n");
		return;
	}

	sdbus::Message::Map mapName;
	mapIn.GetMap(1, mapName);
	ParseMultilanguageStr(mapName, ItemOut.sName);

	sdbus::Message::Map mapInfo;
	mapIn.GetMap(2, mapInfo);
	ParseKeyValues(mapInfo, ItemOut.ConditionInfo);
}

void CMsgMng::BuildLstBondQuotByCondition(const LstBondQuotByCondition& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstBondQuotByCondition::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildBondQuotByCondition(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildBondQuotByCondition(const BondQuotByCondition& ItemIn, sdbus::Message::Map& mapRet)
{
	mapRet.SetString(1, ItemIn.sQuotID);

	sdbus::Message::Map mapDirect;
	BuildMultilanguageStr(ItemIn.sDirect, mapDirect);
	mapRet.SetMap(2, mapDirect);

	mapRet.SetString(3, ItemIn.sCount);

	sdbus::Message::Map mapConditions;
	BuildLstCondition(ItemIn.lstConditions, mapConditions);
	mapRet.SetMap(4, mapConditions);

	mapRet.SetUInt64(5, ItemIn.tExpirationTime);
	mapRet.SetInt8(6, ItemIn.nCancelType);
	sdbus::Message::Map mapTags;
	BuildLstMultilanguageStr(ItemIn.lstTags, mapTags);
	mapRet.SetMap(7, mapTags);
	mapRet.SetString(8, ItemIn.sMemo);
}

void CMsgMng::ParseLstBondQuotByCondition(const sdbus::Message::Map& mapIn, LstBondQuotByCondition& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		BondQuotByCondition ParseOut;
		ParseBondQuotByCondition(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseBondQuotByCondition(const sdbus::Message::Map& mapIn, BondQuotByCondition& ItemOut)
{
	if (mapIn.Size() != 8)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse BondQuotByCondition!\n");
		return;
	}

	mapIn.GetString(1, ItemOut.sQuotID);

	sdbus::Message::Map mapDirect;
	mapIn.GetMap(2,mapDirect);
	ParseMultilanguageStr(mapDirect, ItemOut.sDirect);

	mapIn.GetString(3, ItemOut.sCount);

	sdbus::Message::Map mapConditions;
	mapIn.GetMap(4, mapConditions);
	ParseLstCondition(mapConditions, ItemOut.lstConditions);

	sdbus::uint64_t t64;
	mapIn.GetUInt64(5, t64);
	ItemOut.tExpirationTime = t64;
	sdbus::int8_t t8;
	mapIn.GetInt8(6, t8);
	ItemOut.nCancelType = t8;
	sdbus::Message::Map mapTags;
	mapIn.GetMap(7, mapTags);
	ParseLstMultilanguageStr(mapTags, ItemOut.lstTags);
	mapIn.GetString(8, ItemOut.sMemo);
}

void CMsgMng::BuildLstBondQuotByConditionSendInfo(const LstBondQuotByConditionSendInfo& lstIn, sdbus::Message::Map& mapRet)
{
	int nPos = 1;
	for (LstBondQuotByConditionSendInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
	{
		sdbus::Message::Map Item;
		BuildBondQuotByConditionSendInfo(*iter, Item);
		mapRet.SetMap(nPos, Item);
		nPos++;
	}
}

void CMsgMng::BuildBondQuotByConditionSendInfo(const BondQuotByConditionSendInfo& ItemIn, sdbus::Message::Map& mapRet)
{
	sdbus::Message::Map mapSendTo;
	BuildContact(ItemIn.SendTo, mapSendTo);
	mapRet.SetMap(1, mapSendTo);

	sdbus::Message::Map mapQuots;
	BuildLstBondQuotByCondition(ItemIn.lstQuots, mapQuots);
	mapRet.SetMap(2, mapQuots);

	mapRet.SetUInt64(3, ItemIn.SendTime);

	mapRet.SetInt8(4, ItemIn.nMngType);
}

void CMsgMng::ParseLstBondQuotByConditionSendInfo(const sdbus::Message::Map& mapIn, LstBondQuotByConditionSendInfo& lstOut)
{
	int nCnt = mapIn.Size();
	for (int i = 0; i < nCnt; ++i)
	{
		sdbus::Message::Map ParseIn;
		mapIn.GetMap(i+1, ParseIn);
		BondQuotByConditionSendInfo ParseOut;
		ParseBondQuotByConditionSendInfo(ParseIn, ParseOut);
		lstOut.push_back(ParseOut);
	}
}

void CMsgMng::ParseBondQuotByConditionSendInfo(const sdbus::Message::Map& mapIn, BondQuotByConditionSendInfo& ItemOut)
{
	if (mapIn.Size() != 4)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse BondQuotByConditionSendInfo!\n");
		return;
	}

	sdbus::Message::Map mapSendTo;
	mapIn.GetMap(1, mapSendTo);
	ParseContact(mapSendTo, ItemOut.SendTo);

	sdbus::Message::Map mapQuots;
	mapIn.GetMap(2, mapQuots);
	ParseLstBondQuotByCondition(mapQuots, ItemOut.lstQuots);

	sdbus::uint64_t t64;
	mapIn.GetUInt64(3, t64);
	ItemOut.SendTime = t64;

	sdbus::int8_t t8;
	mapIn.GetInt8(4, t8);
	ItemOut.nMngType = t8;
}


void CMsgMng::BuildContactSearch(const ContactSearch& ItemIn, sdbus::Message::Map& mapRet)
{
    mapRet.SetString(1, ItemIn.sKey);
    mapRet.SetInt32(2, ItemIn.nLimitUser);
    mapRet.SetInt32(3, ItemIn.nSearchType);
}

void CMsgMng::ParseContactSearch(const sdbus::Message::Map& mapIn, ContactSearch& ItemOut)
{
    mapIn.GetString(1, ItemOut.sKey);
    mapIn.GetInt32(2, ItemOut.nLimitUser);
    if (!mapIn.GetInt32(3, ItemOut.nSearchType))
    {
        ItemOut.nSearchType = 0;
    }
}

void CMsgMng::BuildLstSearchUserInfo(const LstSearchUserInfo& lstIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (LstSearchUserInfo::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildSearchUserInfo(*iter, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildSearchUserInfo(const SearchUserInfo& ItemIn, sdbus::Message::Map& mapRet)
{
    mapRet.SetUInt64(1, ItemIn.nUserID);
    mapRet.SetString(2, ItemIn.sUserName);
    mapRet.SetString(3, ItemIn.sCompanyName);
}

void CMsgMng::ParseLstSearchUserInfo(const sdbus::Message::Map& mapIn, LstSearchUserInfo& lstOut)
{
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        SearchUserInfo ParseOut;
        ParseSearchUserInfo(ParseIn, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParseSearchUserInfo(const sdbus::Message::Map& mapIn, SearchUserInfo& ItemOut)
{
    mapIn.GetUInt64(1, ItemOut.nUserID);
    mapIn.GetString(2, ItemOut.sUserName);
    mapIn.GetString(3, ItemOut.sCompanyName);
}

void CMsgMng::BuildLstMMQuotSendInfoV2(const LstMMQuotSendInfoV2& lstIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (LstMMQuotSendInfoV2::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildQuotSendInfoV2_MM(*iter, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildQuotSendInfoV2_MM(const QuotSendInfoV2_MM& ItemIn, sdbus::Message::Map& mapRet)
{
    sdbus::Message::Map mapQuots;
    BuildLstQuotation(ItemIn.lstQuots, mapQuots);
    mapRet.SetMap(1, mapQuots);

    sdbus::Message::Map mapSendTo;
    BuildLstContact(ItemIn.lstSendTo, mapSendTo);
    mapRet.SetMap(2, mapSendTo);

    mapRet.SetUInt64(3, ItemIn.SendTime);

    mapRet.SetInt8(4, ItemIn.nMngType);
}

void CMsgMng::ParseLstMMQuotSendInfoV2(const sdbus::Message::Map& mapIn, LstMMQuotSendInfoV2& lstOut)
{
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        QuotSendInfoV2_MM ParseOut;
        ParseQuotSendInfoV2_MM(ParseIn, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParseQuotSendInfoV2_MM(const sdbus::Message::Map& mapIn, QuotSendInfoV2_MM& ItemOut)
{
    if (mapIn.Size() < 4)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QuotSendInfoV2_MM!\n");
        return;
    }

    sdbus::Message::Map mapQuots;
    mapIn.GetMap(1, mapQuots);
    ParseLstQuotation(mapQuots, ItemOut.lstQuots);

    sdbus::Message::Map mapSendTo;
    mapIn.GetMap(2, mapSendTo);
    ParseLstContact(mapSendTo, ItemOut.lstSendTo);

    sdbus::uint64_t t64;
    mapIn.GetUInt64(3, t64);
    ItemOut.SendTime = t64;

    sdbus::int8_t t8;
    mapIn.GetInt8(4, t8);
    ItemOut.nMngType = t8;
}

void CMsgMng::BuildLstBondQuotByCodeSendInfoV2(const LstBondQuotByCodeSendInfoV2& lstIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (LstBondQuotByCodeSendInfoV2::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildQuotSendInfoV2_BondByCode(*iter, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildQuotSendInfoV2_BondByCode(const QuotSendInfoV2_BondByCode& ItemIn, sdbus::Message::Map& mapRet)
{
    sdbus::Message::Map mapQuots;
    BuildLstBondQuotByCode(ItemIn.lstQuots, mapQuots);
    mapRet.SetMap(1, mapQuots);

    sdbus::Message::Map mapSendTo;
    BuildLstContact(ItemIn.lstSendTo, mapSendTo);
    mapRet.SetMap(2, mapSendTo);

    mapRet.SetUInt64(3, ItemIn.SendTime);

    mapRet.SetInt8(4, ItemIn.nMngType);
}

void CMsgMng::ParseLstBondQuotByCodeSendInfoV2(const sdbus::Message::Map& mapIn, LstBondQuotByCodeSendInfoV2& lstOut)
{
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        QuotSendInfoV2_BondByCode ParseOut;
        ParseQuotSendInfoV2_BondByCode(ParseIn, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParseQuotSendInfoV2_BondByCode(const sdbus::Message::Map& mapIn, QuotSendInfoV2_BondByCode& ItemOut)
{
    if (mapIn.Size() < 4)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QuotSendInfoV2_BondByCode!\n");
        return;
    }

    sdbus::Message::Map mapQuots;
    mapIn.GetMap(1, mapQuots);
    ParseLstBondQuotByCode(mapQuots, ItemOut.lstQuots);

    sdbus::Message::Map mapSendTo;
    mapIn.GetMap(2, mapSendTo);
    ParseLstContact(mapSendTo, ItemOut.lstSendTo);

    sdbus::uint64_t t64;
    mapIn.GetUInt64(3, t64);
    ItemOut.SendTime = t64;

    sdbus::int8_t t8;
    mapIn.GetInt8(4, t8);
    ItemOut.nMngType = t8;
}

void CMsgMng::BuildBondQuotByCodeReplyInfo(const BondQuotByCodeReplyInfo& ItemIn, sdbus::Message::Map& mapRet)
{
    sdbus::Message::Map mapReplyTo;
    BuildContact(ItemIn.ReplyTo, mapReplyTo);
    mapRet.SetMap(1, mapReplyTo);

    sdbus::Message::Map mapQuot;
    BuildBondQuotByCode(ItemIn.Quot, mapQuot);
    mapRet.SetMap(2, mapQuot);
}

void CMsgMng::ParseBondQuotByCodeReplyInfo(const sdbus::Message::Map& mapIn, BondQuotByCodeReplyInfo& ItemOut)
{
    sdbus::Message::Map mapReplyTo;
    if (mapIn.GetMap(1, mapReplyTo))
    {
        ParseContact(mapReplyTo, ItemOut.ReplyTo);
    }

    sdbus::Message::Map mapQuot;
    if (mapIn.GetMap(2, mapQuot))
    {
        ParseBondQuotByCode(mapQuot, ItemOut.Quot);
    }
}

void CMsgMng::BuildPurchaseInfo(const PurchaseInfo& ItemIn, sdbus::Message::Map& mapRet)
{
    mapRet.SetString(1, ItemIn.sPurchaseID);
    mapRet.SetUInt64(2, ItemIn.ModifyTime);
    mapRet.SetString(3, ItemIn.sMsgDisplayP1);
    mapRet.SetString(4, ItemIn.sMsgDisplayP2);
}

void CMsgMng::ParsePurchaseInfo(const sdbus::Message::Map& mapIn, PurchaseInfo& ItemOut)
{
    bool bSuccess = true;
    bSuccess &= mapIn.GetString(1, ItemOut.sPurchaseID);
    sdbus::uint64_t u64;
    bSuccess &= mapIn.GetUInt64(2, u64);
    ItemOut.ModifyTime = u64;
    bSuccess &= mapIn.GetString(3, ItemOut.sMsgDisplayP1);
    bSuccess &= mapIn.GetString(4, ItemOut.sMsgDisplayP2);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse PurchaseInfo!\n");
    }
}

void CMsgMng::BuildLstPurchaseUkey(const LstPurchaseUkey& lstIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (LstPurchaseUkey::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildPurchaseUkey(*iter, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildPurchaseUkey(const PurchaseUkey& ItemIn, sdbus::Message::Map& mapRet)
{
    mapRet.SetString(1, ItemIn.sPurchaseID);
    mapRet.SetUInt64(2, ItemIn.ModifyTime);
}

void CMsgMng::ParseLstPurchaseUkey(const sdbus::Message::Map& mapIn, LstPurchaseUkey& lstOut)
{
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        PurchaseUkey ParseOut;
        ParsePurchaseUkey(ParseIn, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParsePurchaseUkey(const sdbus::Message::Map& mapIn, PurchaseUkey& ItemOut)
{
    bool bSuccess = true;
    bSuccess &= mapIn.GetString(1, ItemOut.sPurchaseID);
    sdbus::uint64_t u64;
    bSuccess &= mapIn.GetUInt64(2, u64);
    ItemOut.ModifyTime = u64;

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse PurchaseUkey!\n");
    }
}

void CMsgMng::BuildMapPurchaseStatus(const MapPurchaseStatus& mapIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (MapPurchaseStatus::const_iterator iter = mapIn.begin(); iter != mapIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildPairPurchaseStatus(iter->first, iter->second, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildPairPurchaseStatus(const PurchaseUkey& ItemIn, int nStatus, sdbus::Message::Map& mapRet)
{
    mapRet.SetString(1, ItemIn.sPurchaseID);
    mapRet.SetUInt64(2, ItemIn.ModifyTime);
    mapRet.SetInt32(3, nStatus);
}

void CMsgMng::ParseMapPurchaseStatus(const sdbus::Message::Map& mapIn, MapPurchaseStatus& mapOut)
{
    mapOut.clear();
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        PurchaseUkey ParseOut;
        int nStatus;
        ParsePairPurchaseStatus(ParseIn, ParseOut, nStatus);
        mapOut[ParseOut] = nStatus;
    }
}

void CMsgMng::ParsePairPurchaseStatus(const sdbus::Message::Map& mapIn, PurchaseUkey& ItemOut, int& nStatus)
{
    bool bSuccess = true;
    bSuccess &= mapIn.GetString(1, ItemOut.sPurchaseID);
    sdbus::uint64_t u64;
    bSuccess &= mapIn.GetUInt64(2, u64);
    ItemOut.ModifyTime = u64;
    bSuccess &= mapIn.GetInt32(3, nStatus);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse PairPurchaseStatus!\n");
    }
}

void CMsgMng::BuildLstQuotStatusReq(const LstQuotStatusReq& lstIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (LstQuotStatusReq::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildQuotStatusReq(*iter, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildQuotStatusReq(const QuotStatusReq& ItemIn, sdbus::Message::Map& mapRet)
{
    mapRet.SetString(1, ItemIn.sQuotID);

    sdbus::Message::Map submapCt;
    BuildContact(ItemIn.Ct, submapCt);
    mapRet.SetMap(2, submapCt);
}

void CMsgMng::ParseLstQuotStatusReq(const sdbus::Message::Map& mapIn, LstQuotStatusReq& lstOut)
{
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        QuotStatusReq ParseOut;
        ParseQuotStatusReq(ParseIn, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParseQuotStatusReq(const sdbus::Message::Map& mapIn, QuotStatusReq& ItemOut)
{
    bool bSuccess = true;
    bSuccess &= mapIn.GetString(1, ItemOut.sQuotID);

    sdbus::Message::Map submapCt;
    if (mapIn.GetMap(2, submapCt))
    {
        ParseContact(submapCt, ItemOut.Ct);
    }
    else
    {
        bSuccess = false;
    }

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QuotStatusReq!\n");
    }
}

void CMsgMng::BuildLstQuotStatus(const LstQuotStatus& lstIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (LstQuotStatus::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildQuotStatus(*iter, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildQuotStatus(const QuotStatus& ItemIn, sdbus::Message::Map& mapRet)
{
    mapRet.SetString(1, ItemIn.sQuotID);

    sdbus::Message::Map submapCt;
    BuildContact(ItemIn.Ct, submapCt);
    mapRet.SetMap(2, submapCt);

    mapRet.SetInt32(3, ItemIn.nStatus);
}

void CMsgMng::ParseLstQuotStatus(const sdbus::Message::Map& mapIn, LstQuotStatus& lstOut)
{
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        QuotStatus ParseOut;
        ParseQuotStatus(ParseIn, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParseQuotStatus(const sdbus::Message::Map& mapIn, QuotStatus& ItemOut)
{
    bool bSuccess = true;
    bSuccess &= mapIn.GetString(1, ItemOut.sQuotID);

    sdbus::Message::Map submapCt;
    if (mapIn.GetMap(2, submapCt))
    {
        ParseContact(submapCt, ItemOut.Ct);
    }
    else
    {
        bSuccess = false;
    }

    bSuccess &= mapIn.GetInt32(3, ItemOut.nStatus);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QuotStatus!\n");
    }
}

void CMsgMng::BuildLstContactStatus(const LstContactStatus& lstIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (LstContactStatus::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildContactStatus(*iter, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildContactStatus(const ContactStatus& ItemIn, sdbus::Message::Map& mapRet)
{
    sdbus::Message::Map submapCt;
    BuildContact(ItemIn.Ct, submapCt);
    mapRet.SetMap(1, submapCt);

    mapRet.SetInt32(2, ItemIn.nStatus);
}

void CMsgMng::ParseLstContactStatus(const sdbus::Message::Map& mapIn, LstContactStatus& lstOut)
{
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        ContactStatus ParseOut;
        ParseContactStatus(ParseIn, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParseContactStatus(const sdbus::Message::Map& mapIn, ContactStatus& ItemOut)
{
    bool bSuccess = true;

    sdbus::Message::Map submapCt;
    if (mapIn.GetMap(1, submapCt))
    {
        ParseContact(submapCt, ItemOut.Ct);
    }
    else
    {
        bSuccess = false;
    }

    bSuccess &= mapIn.GetInt32(2, ItemOut.nStatus);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse ContactStatus!\n");
    }
}

void CMsgMng::BuildLstQBAccount2QMID(const LstQBAccount2QMID& lstIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (LstQBAccount2QMID::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildQBAccount2QMID(*iter, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildQBAccount2QMID(const QBAccount2QMID& ItemIn, sdbus::Message::Map& mapRet)
{
    mapRet.SetString(1, ItemIn.sQBAccount);
    mapRet.SetUInt64(2, ItemIn.nQMID);
}

void CMsgMng::ParseLstQBAccount2QMID(const sdbus::Message::Map& mapIn, LstQBAccount2QMID& lstOut)
{
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        QBAccount2QMID ParseOut;
        ParseQBAccount2QMID(ParseIn, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParseQBAccount2QMID(const sdbus::Message::Map& mapIn, QBAccount2QMID& ItemOut)
{
    bool bSuccess = true;
    bSuccess &= mapIn.GetString(1, ItemOut.sQBAccount);
    bSuccess &= mapIn.GetUInt64(2, ItemOut.nQMID);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QBAccount2QMID!\n");
    }
}

void CMsgMng::BuildLstQMRKey(const LstQMRKey& lstIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (LstQMRKey::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildQMRemindKeyItem(*iter, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildQMRemindKeyItem(const QMRemindKeyItem& ItemIn, sdbus::Message::Map& mapRet)
{
    mapRet.SetString(1, ItemIn.sID);
    mapRet.SetString(2, ItemIn.sKeyWord);
    mapRet.SetInt32(3, ItemIn.nStatus);
    mapRet.SetInt32(4, ItemIn.nOrder);
}

void CMsgMng::ParseLstQMRKey(const sdbus::Message::Map& mapIn, LstQMRKey& lstOut)
{
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        QMRemindKeyItem ParseOut;
        ParseQMRemindKeyItem(ParseIn, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParseQMRemindKeyItem(const sdbus::Message::Map& mapIn, QMRemindKeyItem& ItemOut)
{
    bool bSuccess = true;
    bSuccess &= mapIn.GetString(1, ItemOut.sID);
    bSuccess &= mapIn.GetString(2, ItemOut.sKeyWord);
    bSuccess &= mapIn.GetInt32(3, ItemOut.nStatus);
    bSuccess &= mapIn.GetInt32(4, ItemOut.nOrder);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QMRemindKeyItem!\n");
    }
}

void CMsgMng::BuildLstQMRFriend(const LstQMRFriend& lstIn, sdbus::Message::Map& mapRet)
{
    int nPos = 1;
    for (LstQMRFriend::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildQMRemindFriendItem(*iter, Item);
        mapRet.SetMap(nPos, Item);
        nPos++;
    }
}

void CMsgMng::BuildQMRemindFriendItem(const QMRemindFriendItem& ItemIn, sdbus::Message::Map& mapRet)
{
    mapRet.SetString(1, ItemIn.sID);
    mapRet.SetString(2, ItemIn.sDisplayName);
    mapRet.SetUInt64(3, ItemIn.nQMID);
    mapRet.SetInt32(4, ItemIn.nStatus);
    mapRet.SetInt32(5, ItemIn.nOrder);
}

void CMsgMng::ParseLstQMRFriend(const sdbus::Message::Map& mapIn, LstQMRFriend& lstOut)
{
    int nCnt = mapIn.Size();
    for (int i = 0; i < nCnt; ++i)
    {
        sdbus::Message::Map ParseIn;
        mapIn.GetMap(i+1, ParseIn);
        QMRemindFriendItem ParseOut;
        ParseQMRemindFriendItem(ParseIn, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParseQMRemindFriendItem(const sdbus::Message::Map& mapIn, QMRemindFriendItem& ItemOut)
{
    bool bSuccess = true;
    bSuccess &= mapIn.GetString(1, ItemOut.sID);
    bSuccess &= mapIn.GetString(2, ItemOut.sDisplayName);
    bSuccess &= mapIn.GetUInt64(3, ItemOut.nQMID);
    bSuccess &= mapIn.GetInt32(4, ItemOut.nStatus);
    bSuccess &= mapIn.GetInt32(5, ItemOut.nOrder);
    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QMRemindFriendItem!\n");
    }
}

void CMsgMng::BuildQMRemindConfig(const QMRemindConfig& ItemIn, sdbus::Message::Map& mapRet)
{
    sdbus::Message::Map submapKeyConfig;
    BuildLstQMRKey(ItemIn.KeyConfig, submapKeyConfig);
    mapRet.SetMap(1, submapKeyConfig);

    sdbus::Message::Map submapFriendConfig;
    BuildLstQMRFriend(ItemIn.FriendConfig, submapFriendConfig);
    mapRet.SetMap(2, submapFriendConfig);

    mapRet.SetUInt32(3, ItemIn.nRemindType);
}

void CMsgMng::ParseQMRemindConfig(const sdbus::Message::Map& mapIn, QMRemindConfig& ItemOut)
{
    bool bSuccess = true;
    sdbus::Message::Map submapKeyConfig;
    if (mapIn.GetMap(1, submapKeyConfig))
    {
        ParseLstQMRKey(submapKeyConfig, ItemOut.KeyConfig);
    }
    else
    {
        bSuccess = false;
    }

    sdbus::Message::Map submapFriendConfig;
    if (mapIn.GetMap(2, submapFriendConfig))
    {
        ParseLstQMRFriend(submapFriendConfig, ItemOut.FriendConfig);
    }
    else
    {
        bSuccess = false;
    }

    bSuccess &= mapIn.GetUInt32(3, ItemOut.nRemindType);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse QMRemindConfig!\n");
    }
}

void CMsgMng::BuildLstBondShare(const LstBondShare& lstIn, sdbus::Message::List& lstRet)
{
    for (LstBondShare::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        BuildBondShareItem(*iter, Item);
        lstRet.PushBack(Item);
    }
}

void CMsgMng::BuildBondShareItem(const BondShareItem& ItemIn, sdbus::Message::Map& mapRet)
{
    mapRet.SetString(1, ItemIn.sCombBondKey);
    mapRet.SetString(2, ItemIn.sBondCode);
    mapRet.SetString(3, ItemIn.sBondShortName);
    mapRet.SetString(4, ItemIn.sMemo);
}

void CMsgMng::ParseLstBondShare(const sdbus::Message::List& lstIn, LstBondShare& lstOut)
{
    for (size_t i = 0; i < lstIn.Size(); ++i)
    {
        const sdbus::Variant* pItem = lstIn.Get(i);
        if (!pItem)
        {
            continue;
        }
        if (pItem->Type != sdbus::Variant::VAR_MAP)
        {
            continue;
        }

        BondShareItem ParseOut;
        ParseBondShareItem(*pItem, ParseOut);
        lstOut.push_back(ParseOut);
    }
}

void CMsgMng::ParseBondShareItem(const sdbus::Message::Map &mapIn, BondShareItem &ItemOut)
{
    bool bSuccess = true;
    bSuccess &= mapIn.GetString(1, ItemOut.sCombBondKey);
    bSuccess &= mapIn.GetString(2, ItemOut.sBondCode);
    bSuccess &= mapIn.GetString(3, ItemOut.sBondShortName);
    bSuccess &= mapIn.GetString(4, ItemOut.sMemo);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse BondShareItem!\n");
    }
}

void CMsgMng::BuildReqJoinGroup( const unsigned long long &llGroup, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ReqJoinGroup);
    msg.SetUInt64(2, llGroup);
}

void CMsgMng::ParseReqJoinGroup( const sdbus::Message &msg, unsigned long long &llGroup )
{
    bool bSuccess(true);
    bSuccess &= msg.GetUInt64(2, llGroup);
    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ReqJoinGroup!\n");
    }
}

void CMsgMng::BuildJoinGroupRet( bool bSuccess, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ReqJoinGroupRet);
    msg.SetBool(2, bSuccess);
}

void CMsgMng::ParseJoinGroupRet( const sdbus::Message &msg, bool &bSuccess )
{
    if (!msg.GetBool(2, bSuccess))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ParseJoinGroupRet!\n");
    }
}

void CMsgMng::BuildReqOpenNews( const NewsInfo &info, sdbus::Message &msg )
{
	msg.SetString(1, MSGCMD_ReqOpenNews);
	msg.SetString(2, info.sTitle);
	msg.SetString(3, info.sURL);
	msg.SetRaw(4, info.pPic, info.nLen);
}

void CMsgMng::ParseReqOpenNews( const sdbus::Message &msg, NewsInfo &info )
{
	bool bSuccess(true);
	bSuccess &= msg.GetString(2, info.sTitle);
	bSuccess &= msg.GetString(3, info.sURL);

	sdbus::string sRawData;
	bSuccess &= msg.GetRaw(4, sRawData);
	info.SetPic(sRawData.data(), sRawData.length());

	if (!bSuccess)
	{
		CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ReqOpenNews!\n");
	}
}

void CMsgMng::BuildSharePic( const PicInfo &info, const LstContact &lstCt, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_SharePic);
    msg.SetRaw(2, info.pPic, info.nLen);

    sdbus::Message::Map mapIn;
    BuildLstContact(lstCt, mapIn);
    msg.SetMap(3, mapIn);
}

void CMsgMng::ParseSharePic( const sdbus::Message &msg, PicInfo &info, LstContact &lstCt )
{
    bool bSuccess(true);

    sdbus::string sRawData;
    bSuccess &= msg.GetRaw(2, sRawData);
    info.SetPic(sRawData.data(), sRawData.length());

    sdbus::Message::Map mapOut;
    if (msg.GetMap(3, mapOut))
    {
        ParseLstContact(mapOut, lstCt);
    }
    else
    {
        bSuccess = false;
    }

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg SharePic!\n");
    }
}

void CMsgMng::BuildReqOpenNewsDetail( const NewsInfoV2 &info, const bool bDisablePDF, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ReqOpenNewsDetail);
    msg.SetString(2, info.sTitle);
    msg.SetString(3, info.sURL);
    msg.SetString(4, info.sPicUUID);
    msg.SetBool(5, bDisablePDF);
	msg.SetString(6,info.sImage);
	msg.SetBool(7,info.bIsPdf);
}

void CMsgMng::ParseReqOpenNewsDetail( const sdbus::Message &msg, NewsInfoV2 &info, bool &bDisablePDF )
{
    bool bSuccess(true);
    bSuccess &= msg.GetString(2, info.sTitle);
    bSuccess &= msg.GetString(3, info.sURL);
    bSuccess &= msg.GetString(4, info.sPicUUID);
    bSuccess &= msg.GetBool(5, bDisablePDF);
    bSuccess &= msg.GetString(6, info.sImage);
    bSuccess &= msg.GetBool(7, info.bIsPdf);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ReqOpenNewsDetail!\n");
    }
}

void CMsgMng::BuildReqOpenNewsWnd( sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ReqOpenNewsWnd);
}

void CMsgMng::ParseReqOpenNewsWnd( const sdbus::Message &msg )
{

}

void CMsgMng::BuildShareNewsDetail( const NewsInfoV2 &info, const LstContact& lstCt, bool bDisablePDF, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ShareNewsDetail);
    msg.SetString(2, info.sTitle);
    msg.SetString(3, info.sURL);
    msg.SetString(4, info.sPicUUID);
	msg.SetString(5, info.sImage);
	msg.SetBool(6,info.bIsPdf);

    sdbus::Message::Map mapIn;
    BuildLstContact(lstCt, mapIn);
    msg.SetMap(5, mapIn);
    msg.SetBool(6, bDisablePDF);
}

void CMsgMng::ParseShareNewsDetail( const sdbus::Message &msg, NewsInfoV2 &info, LstContact& lstCt, bool &bDisablePDF )
{
    bool bSuccess(true);
    bSuccess &= msg.GetString(2, info.sTitle);
    bSuccess &= msg.GetString(3, info.sURL);
    bSuccess &= msg.GetString(4, info.sPicUUID);
	bSuccess &= msg.GetString(5, info.sImage);
	bSuccess &= msg.GetBool(6,info.bIsPdf);


    sdbus::Message::Map mapOut;
    if (msg.GetMap(5, mapOut))
    {
        ParseLstContact(mapOut, lstCt);
    }
    else
    {
        bSuccess = false;
    }

    bSuccess &= msg.GetBool(6, bDisablePDF);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ShareNewsDetail!\n");
    }
}

void CMsgMng::BuildOpenDialogueByUserID( const std::string &userID, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_OpenDialogueByUserID);
    msg.SetString(2, userID);
}

void CMsgMng::ParseOpenDialogueByUserID( const sdbus::Message &msg, std::string &userID )
{
    bool bSuccess(true);
    bSuccess &= msg.GetString(2, userID);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg OpenDialogueByUserID!\n");
    }
}

void CMsgMng::BuildQueryQMStatusRet( int status, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_QueryQMStatusRet);
    msg.SetInt32(2, status);
}

void CMsgMng::ParseQueryQMStatusRet( const sdbus::Message &msg, int &status )
{
    bool bSuccess(true);
    bSuccess &= msg.GetInt32(2, status);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QueryQMStatusRet!\n");
    }
}

void CMsgMng::BuildReqOpenSellsWnd( const std::string& sWndID, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ReqOpenSellsWnd);
    msg.SetString(2, sWndID);
}

void CMsgMng::ParseReqOpenSellsWnd( const sdbus::Message &msg, std::string& sWndID )
{
    if (!msg.GetString(2, sWndID))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse ReqOpenSellsWnd!\n");
    }
}

void CMsgMng::BuildReqQueryNoInstituteContact( sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ReqQueryNoInstituteContact);
}

void CMsgMng::ParseReqQueryNoInstituteContact( const sdbus::Message &msg )
{

}

void CMsgMng::BuildReqQueryNoInstituteContactRet( const LstNoInstituteContact &contacts, int status, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ReqQueryNoInstituteContactRet);

    sdbus::Message::Map map;
    BuildLstNoInstituteContact(contacts, map);
    msg.SetMap(2, map);

    msg.SetInt32(3, status);
}

void CMsgMng::ParseReqQueryNoInstituteContactRet( const sdbus::Message &msg, LstNoInstituteContact &contacts, int &status )
{
    bool bSuccess = true;

    sdbus::Message::Map map;
    if (msg.GetMap(2, map))
    {
        ParseLstNoInstituteContact(map, contacts);
    }
    else
    {
        bSuccess = false;
    }

    bSuccess &= msg.GetInt32(3, status);

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg QueryNoInstituteContactRet!\n");
    }
}

void CMsgMng::BuildReqSetNoInstituteContact( const std::list<std::string> &QBAccounts, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ReqSetNoInstituteContact);

    sdbus::Message::Map map;
    BuildLstString(QBAccounts, map);
    msg.SetMap(2, map);
}

void CMsgMng::ParseReqSetNoInstituteContact( const sdbus::Message &msg, std::list<std::string> &QBAccounts )
{
    bool bSuccess = true;

    sdbus::Message::Map map;
    if (msg.GetMap(2, map))
    {
        ParseLstString(map, QBAccounts);
    }
    else
    {
        bSuccess = false;
    }

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg SetNoInstituteContact!\n");
    }
}

void CMsgMng::BuildModifyNoInstituteContactRet( const LstNoInstituteContact &contacts, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ModifyNoInstituteContactRet);

    sdbus::Message::Map map;
    BuildLstNoInstituteContact(contacts, map);
    msg.SetMap(2, map);
}

void CMsgMng::ParseModifyNoInstituteContactRet( const sdbus::Message &msg, LstNoInstituteContact &contacts )
{
    bool bSuccess = true;

    sdbus::Message::Map map;
    if (msg.GetMap(2, map))
    {
        ParseLstNoInstituteContact(map, contacts);
    }
    else
    {
        bSuccess = false;
    }

    if (!bSuccess)
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse Msg ModifyNoInstituteContactRet!\n");
    }
}

void CMsgMng::BuildReqOpenSellsSearchWnd( const std::string& sWndID, sdbus::Message &msg )
{
    msg.SetString(1, MSGCMD_ReqOpenSellsSearchWnd);
    msg.SetString(2, sWndID);
}

void CMsgMng::ParseReqOpenSellsSearchWnd( const sdbus::Message &msg, std::string& sWndID )
{
    if (!msg.GetString(2, sWndID))
    {
        CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse ReqOpenSellsSearchWnd!\n");
    }
}

void CMsgMng::BuildLstNoInstituteContact( const LstNoInstituteContact &lstIn, sdbus::Message::Map& mapRet )
{
    int nPos(1);
    for (LstNoInstituteContact::const_iterator iter = lstIn.begin(); iter != lstIn.end(); ++iter)
    {
        sdbus::Message::Map Item;
        Item.SetString(1, iter->sQBAccount);
        Item.SetString(2, iter->sInstituteName);
        Item.SetString(3, iter->sName);
        Item.SetUInt64(4, iter->ullQMId);

        mapRet.SetMap(nPos, Item);
        ++nPos;
    }
}

void CMsgMng::ParseLstNoInstituteContact( const sdbus::Message::Map& mapIn, LstNoInstituteContact& lstOut )
{
    for (size_t i = 0; i < mapIn.Size(); ++i)
    {
        sdbus::Message::Map mpItem;
        mapIn.GetMap(i+1, mpItem);

        bool bSuccess = true;
        NoInstituteContact ParseOut;
        bSuccess &= mpItem.GetString(1, ParseOut.sQBAccount);
        bSuccess &= mpItem.GetString(2, ParseOut.sInstituteName);
        bSuccess &= mpItem.GetString(3, ParseOut.sName);
        bSuccess &= mpItem.GetUInt64(4, ParseOut.ullQMId);
        if (!bSuccess)
        {
            CURLOGGERWRITEWITHLV(m_pLogger, ss::LOG_LEVEL::LOG_ERR, "Failed To Parse NoInstituteContactItem!\n");
        }

        lstOut.push_back(ParseOut);
    }
}
