//-------------------------------------------------------------------------------------
//--Copyright	:	Sumscope
//--FileName	:	ISSMQDefine.h
//--Author		:	cheng.xu@sumscope.com
//--Date		:	2015.01.23
//--Desc		:	消息总线封装使用到的公共定义
//--History		:	Created by cheng.xu, 2015.01.23
//--				
//-------------------------------------------------------------------------------------

#ifndef __I_SS_MQDEFINE__
#define __I_SS_MQDEFINE__

#include "sdbus\type.h"

#define SSMQ_ENGINE	"zmq"
#define SSMQ_SRVNAME _T("SSMQServer.exe")
#define SSMQ_TOPIC_MNG "ssmq_topic_mng"
#define SSMQ_CMD_ADDCLIENT "ssmq_cmd_addclient"
#define SSMQ_CMD_REMOVECLIENT "ssmq_cmd_removeclient"
#define SSMQ_CMD_ACKSRVPROCID "ssmq_cmd_acksrvprocid"
#define SSMQ_CMD_CLOSEALL "ssmq_cmd_closeall"
#define SSMQ_CMD_CLOSECLIENT "ssmq_cmd_closeclient"

const sdbus::uint32_t SSMQ_MSGIDX_CMDTYPE = 1;
const sdbus::uint32_t SSMQ_MSGIDX_CMDPARA = 2;

#endif