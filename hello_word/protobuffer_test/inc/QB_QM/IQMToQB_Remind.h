#pragma once

#include "QB_QMDefine.h"

using std::string;
//QM提醒相关的联动接口

namespace QB_QM
{
    //回调接口,由QM实现
    class IQMToQBCallback_Remind
    {
    protected:
        IQMToQBCallback_Remind(){}

    public:
        virtual ~IQMToQBCallback_Remind(){}

        //查询当前设置的QM提醒
        virtual void QueryQMRemindConfig(const string& sMsgID) = 0;
        //新增QM关键字提醒
        virtual void AddQMRemindKeyItem(const string& sMsgID, const QMRemindKeyItem& Item) = 0;
        //修改QM关键字提醒
        virtual void ModifyQMRemindKeyItem(const string& sMsgID, const QMRemindKeyItem& Item) = 0;
        //删除QM关键字提醒
        virtual void DelQMRemindKeyItem(const string& sMsgID, const SetString& setID) = 0;
        //新增QM好友提醒
        virtual void AddQMRemindFriendItem(const string& sMsgID, const QMRemindFriendItem& Item) = 0;
        //修改QM好友提醒
        virtual void ModifyQMRemindFriendItem(const string& sMsgID, const QMRemindFriendItem& Item) = 0;
        //删除QM好友提醒
        virtual void DelQMRemindFriendItem(const string& sMsgID, const SetString& setID) = 0;
        //设置QM提醒方式
        virtual void SetQMRemindType(const string& sMsgID, unsigned int nRemindType) = 0;
    };

    class IQMToQB_Remind
    {
    protected:
        IQMToQB_Remind(){}

    public:
        virtual ~IQMToQB_Remind(){}

        //注册Bond相关回调接口
        virtual void RegCallback(IQMToQBCallback_Remind* pCallback) = 0;
        //查询当前设置的QM提醒返回
        virtual void QueryQMRemindConfigRet(const string& sMsgID, const QMRemindConfig& QMRCfg) = 0;
        //新增QM关键字提醒返回
        virtual void AddQMRemindKeyItemRet(const string& sMsgID, const string& ItemID) = 0;
        //修改QM关键字提醒返回
        virtual void ModifyQMRemindKeyItemRet(const string& sMsgID, bool bSuccess) = 0;
        //删除QM关键字提醒返回
        virtual void DelQMRemindKeyItemRet(const string& sMsgID, const SetString& setSuccessID) = 0;
        //新增QM好友提醒返回
        virtual void AddQMRemindFriendItemRet(const string& sMsgID, const string& ItemID) = 0;
        //修改QM好友提醒返回
        virtual void ModifyQMRemindFriendItemRet(const string& sMsgID, bool bSuccess) = 0;
        //删除QM好友提醒返回
        virtual void DelQMRemindFriendItemRet(const string& sMsgID, const SetString& setSuccessID) = 0;
        //设置QM提醒方式返回
        virtual void SetQMRemindTypeRet(const string& sMsgID, bool bSuccess) = 0;
    };
}


