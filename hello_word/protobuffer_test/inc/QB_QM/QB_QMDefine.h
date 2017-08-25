#pragma once

#ifdef QB_QM_EXPORTS
#define QB_QM_API __declspec(dllexport)
#else
#define QB_QM_API __declspec(dllimport)
#endif

#include <string>
#include <list>
#include <set>
#include <map>
#include <time.h>

namespace QB_QM
{

	typedef std::set<unsigned long long> SetUInt64;

    typedef std::set<std::string> SetString;

	typedef std::map<std::string, std::string> KeyValues;

	//支持多语言的字符串
	struct MultilanguageStr
	{
		//显示文本
		std::string sDisplay;
		//内部枚举值
		std::string sEnumVal;

		MultilanguageStr()
			:sDisplay("")
			,sEnumVal("")
		{}
	};

	typedef std::list<MultilanguageStr> LstMultilanguageStr;

	//期限信息
	struct TermInfo
	{
		//显示文本
		std::string sDisplay;
		//期限类型
		int nTermType;
		//内部枚举值
		std::list<std::string> LstEnumVal;
	};

	typedef std::list<TermInfo> LstTermInfo;

	//MM报价信息结构
	struct Quotation 
	{
		//报价ID
		std::string sQuotationID;
		//方向
		MultilanguageStr sDirect;
		//资产
		MultilanguageStr sAssetsType;
		//期限(支持多个),QM显示时多个期限的显示文本用逗号分隔
		LstTermInfo lstTerms;
		//数量
		MultilanguageStr sCount;
		//价格
		MultilanguageStr sPrice;
		//撤销时间
		time_t tExpirationTime;
		//撤销计时类型
		int nCancelType;
		//标签
		LstMultilanguageStr lstTags;
		//备注
		std::string sMemo;

		Quotation()
		{
			Clear();
		}

		void Clear()
		{
			sQuotationID = "";
			sDirect = MultilanguageStr();
			sAssetsType = MultilanguageStr();
			lstTerms.clear();
			sCount = MultilanguageStr();
			sPrice = MultilanguageStr();
			tExpirationTime = 0;
			nCancelType = 0;
			lstTags.clear();
			sMemo = "";
		}

		bool operator < (const Quotation& rIn) const
		{
			return sQuotationID < rIn.sQuotationID;
		}
	};

	typedef std::list<Quotation> LstQuotation;

	//联系人信息结构
	struct Contact
	{
		//联系人ID
		unsigned long long nContactID;
		//nContactType: 0为个人;1为group
		int nContactType;

		Contact()
			:nContactID(0)
			,nContactType(0)
		{
		}

		bool operator < (const Contact& rIn) const
		{
			if (nContactType != rIn.nContactType)
			{
				return nContactType < rIn.nContactType;
			}
			return nContactID < rIn.nContactID;
		}

        bool operator == (const Contact& rIn) const
        {
            return nContactType == rIn.nContactType && nContactID == rIn.nContactID;
        }
	};

	typedef std::list<Contact> LstContact;

	//报价管理信息
	struct QuotationMngInfo
	{
		Quotation Quot;
		LstContact Contacts;
		time_t SendTime;
		int nMngType;		//0为发送, 1为撤销

		QuotationMngInfo()
			:SendTime(0)
			,nMngType(0)
		{
		}
	};

	typedef std::list<QuotationMngInfo> LstQuotationMngInfo;

	//报价发送信息
	struct QuotSendInfo
	{
		Contact SendTo;
		LstQuotation lstQuots;
		time_t SendTime;
		int nMngType;		//0为发送, 1为撤销

		QuotSendInfo()
			:SendTime(0)
			,nMngType(0)
		{
		}
	};

	typedef std::list<QuotSendInfo> LstQuotSendInfo;

	//报价接受信息
	struct QuotRecvInfo
	{
		//从哪里接受到的(群或个人)
		Contact RecvFrom;
		//发自哪里的(只会是个人)
		Contact SendFrom;
		LstQuotation lstQuots;
		time_t RecvTime;
		int nMngType;		//0为发送, 1为撤销

		QuotRecvInfo()
			:RecvTime(0)
			,nMngType(0)
		{
		}
	};

	typedef std::list<QuotRecvInfo> LstQuotRecvInfo;

	//报价回复信息
	struct QuotReplyInfo
	{
		//回复到
		Contact ReplyTo;
		//报价信息
		Quotation Quot;
	};

	typedef std::list<QuotReplyInfo> LstQuotReplyInfo;


	//个人信息
	struct PersonInfo
	{
		//ID
		unsigned long long nID;
		//显示名称
		std::string sDisplayName;
		//手机
		std::string sMobile;
		//固话
		std::string sTel;
		//机构简称
		std::string sInstitution;
		//机构ID
		std::string sInstitutionID;
		//机构类型
		std::string sInstitutionType;
        //QBAccount
        std::string sQBAccount;

		//头像图片二进制信息(地址头+size)
		char* pAvatar;
		size_t nAvatarSize;

		PersonInfo()
			:nID(0)
			,sDisplayName("")
			,sMobile("")
			,sTel("")
			,sInstitution("")
			,sInstitutionID("")
			,sInstitutionType("")
            ,sQBAccount("")
			,pAvatar(NULL)
			,nAvatarSize(0)
		{
		}

        PersonInfo(const PersonInfo& pi)
        {
            nID = pi.nID;
            sDisplayName = pi.sDisplayName;
            sMobile = pi.sMobile;
            sTel = pi.sTel;
            sInstitution = pi.sInstitution;
            sInstitutionID = pi.sInstitutionID;
            sInstitutionType = pi.sInstitutionType;
            sQBAccount = pi.sQBAccount;
            pAvatar = NULL;
            nAvatarSize = 0;

            SetAvatar(pi.pAvatar, pi.nAvatarSize);
        }

		~PersonInfo()
		{
			if (pAvatar)
			{
				delete[] pAvatar;
				pAvatar = NULL;
				nAvatarSize = 0;
			}
		}

		PersonInfo& operator= (const PersonInfo& pi)
		{
			nID = pi.nID;
			sDisplayName = pi.sDisplayName;
			sMobile = pi.sMobile;
			sTel = pi.sTel;
			sInstitution = pi.sInstitution;
			sInstitutionID = pi.sInstitutionID;
			sInstitutionType = pi.sInstitutionType;
            sQBAccount = pi.sQBAccount;
			SetAvatar(pi.pAvatar, pi.nAvatarSize);
			return (*this) ;
		}

		void SetAvatar(const char* pData, size_t nLength)
		{
			if (pAvatar)
			{
				delete[] pAvatar;
				pAvatar = NULL;
				nAvatarSize = 0;
			}
			if (pData)
			{
				pAvatar = new char[nLength];
				nAvatarSize = nLength;
				memcpy(pAvatar, pData, nLength);
			}
		}
	};

	typedef std::list<PersonInfo> LstPersonInfo;

	//组信息
	struct GroupInfo
	{
		//ID
		unsigned long long nID;
		//显示名称
		std::string sDisplayName;
		//头像图片二进制信息(地址头+size)
		char* pAvatar;
		size_t nAvatarSize;

		GroupInfo()
			:nID(0)
			,sDisplayName("")
			,pAvatar(NULL)
			,nAvatarSize(0)
		{
		}

        GroupInfo(const GroupInfo& gi)
        {
            nID = gi.nID;
            sDisplayName = gi.sDisplayName;
            pAvatar = NULL;
            nAvatarSize = 0;

            SetAvatar(gi.pAvatar, gi.nAvatarSize);
        }

		~GroupInfo()
		{
			if (pAvatar)
			{
				delete[] pAvatar;
				pAvatar = NULL;
				nAvatarSize = 0;
			}
		}

		GroupInfo& operator= (const GroupInfo& gi)
		{
			nID = gi.nID;
			sDisplayName = gi.sDisplayName;
			SetAvatar(gi.pAvatar, gi.nAvatarSize);
			return (*this) ;
		}

		void SetAvatar(const char* pData, size_t nLength)
		{
			if (pAvatar)
			{
				delete[] pAvatar;
				pAvatar = NULL;
				nAvatarSize = 0;
			}
			if (pData)
			{
				pAvatar = new char[nLength];
				nAvatarSize = nLength;
				memcpy(pAvatar, pData, nLength);
			}
		}
	};

	typedef std::list<GroupInfo> LstGroupInfo;

	//新闻信息
	struct NewsInfo
	{
		NewsInfo()
			:pPic(NULL)
			,nLen(0)
		{

		}
		NewsInfo(const NewsInfo &info)
            :pPic(NULL)
            ,nLen(0)
		{
			Copy(info);
		}
		~NewsInfo()
		{
			ClearPic();
		}

		NewsInfo& operator= (const NewsInfo &info)
		{
			if (this == &info)
			{
				return *this;
			}

			Copy(info);
			return *this;
		}

		void SetPic(const char *ptr, size_t len)
		{
			ClearPic();
			if (ptr)
			{
				pPic = new char[len];
				nLen = len;
				memcpy(pPic, ptr, len);
			}
		}
		void ClearPic()
		{
			if (pPic)
			{
				delete []pPic;
				pPic = NULL;
				nLen = 0;
			}
		}

		void Copy(const NewsInfo &info)
		{
			sTitle = info.sTitle;
			sURL = info.sURL;
			SetPic(info.pPic, info.nLen);
		}

		//标题
		std::string sTitle;
		//url
		std::string sURL;
		//缩略图 二进制信息(地址头+size)
		char* pPic;
		size_t nLen;
	};

    //新闻信息
    struct NewsInfoV2
    {
		NewsInfoV2():bIsPdf(false)
        {

        }
        NewsInfoV2(const NewsInfoV2 &info)
        {
            Copy(info);
        }
        ~NewsInfoV2()
        {

        }

        NewsInfoV2& operator= (const NewsInfoV2 &info)
        {
            if (this == &info)
            {
                return *this;
            }

            Copy(info);
            return *this;
        }

        void Copy(const NewsInfoV2 &info)
        {
            sTitle = info.sTitle;
            sURL = info.sURL;
            sPicUUID = info.sPicUUID;
			sImage = info.sImage;
			bIsPdf = info.bIsPdf;
        }

        //标题
        std::string sTitle;
        //url
        std::string sURL;
        //缩略图 uuid
        std::string sPicUUID;
		std::string sImage;		// base64
		bool		bIsPdf;
    };

    struct PicInfo
    {
        PicInfo()
            :pPic(NULL)
            ,nLen(0)
        {

        }
        PicInfo(const PicInfo &info)
            :pPic(NULL)
            ,nLen(0)
        {
            Copy(info);
        }
        ~PicInfo()
        {
            ClearPic();
        }

        PicInfo& operator= (const PicInfo &info)
        {
            if (this == &info)
            {
                return *this;
            }

            Copy(info);
            return *this;
        }

        void SetPic(const char *ptr, size_t len)
        {
            ClearPic();
            if (ptr)
            {
                pPic = new char[len];
                nLen = len;
                memcpy(pPic, ptr, len);
            }
        }
        void ClearPic()
        {
            if (pPic)
            {
                delete []pPic;
                pPic = NULL;
                nLen = 0;
            }
        }

        void Copy(const PicInfo &info)
        {
            SetPic(info.pPic, info.nLen);
        }

        //缩略图 二进制信息(地址头+size)
        char* pPic;
        size_t nLen;
    };

	struct BondItem
	{
		std::string			m_sBondKey;							//债券编码
		std::string			m_sBondID;							//债券代码
		std::string			m_sListedMarket;					//CIB/SSE/SZE 代表不同的市场
		std::string			m_sCombBondKey;						//带有市场后缀的BondKey
		std::string			m_sCombBondID;						//带有市场后缀的BondCode
		std::string			m_sFullName;						//债券全称
		std::string			m_sShortName;						//债券简称
		std::string			m_sFullNameEn;						//英文全称
		std::string			m_sShortNameEn;						//英文简称
		std::string			m_sJianpin;							//简拼					编码：------
		std::string			m_sQuanpin;							//全拼					编码：------
		std::string			m_sMarketType;						//市场类型				1级，2级
		std::string			m_sBondSubType;						//债劵子类别
		std::string			m_sIssuerRating;					//发行人最新评级,主体评级
		std::string			m_sBondRating;						//最新债项评级
		std::string			m_sListDate;						//上市日期
		std::string			m_sInterestStartDate;				//起息日				编码："19860414"
		std::string			m_sMaturityDate;					//到期日				编码：“19860414”
		std::string			m_sPaymentDate;						//缴款日
		std::string		    m_sOptionDate;						//行权日期			
		std::string			m_sRateType;						//利率类型				编码："Shibor","Depo","固息"
		std::string			m_sOptionType;						//选择权类型			编码：------
		std::string			m_sMaturityTerm;					//偿还期限
		std::string			m_sTermToMaturity;					//偿还期限， "X+Y"
		std::string			m_sFRNIndexID;						//基础利率代码
		double				m_fCouponRateCurrent;				//中标价格,票面利率
		double				m_fPlannedIssueAmount;				//预期发行量
		std::string			m_sIssuerCode;						//发行人代码
		std::string			m_sInstitutionType;					//机构类型			编码：------
		std::string			m_sYieldCurveType;					//曲线类型			编码：------
		std::string			m_sEstcleanprice;					// 估值净价
		std::string			m_sEstPrice;						// 估值收益率

		std::string			m_sAuctionDateStart;				//招标建档起始日
		std::string			m_sAuctionDateEnd;					//招标建档截止日
		std::string			m_sAnnounceDate;					//公告日期
		std::string			m_sIssueStartDate;					//发行起始日
		std::string			m_sIssueEndDate;					//发行截止日
		std::string			m_sIsUnderwriter;					//是否在团
		int					m_nIsQuotTopflag;					//是否置顶,			编码: 1:置顶
		int					m_nIsWarrant;						//是否担保
		std::string			m_sMortgate;						//可质押				编码："Y"
		std::string			m_sCrossmarket;						//跨市场				编码："Y","N"
		std::string			m_sIsMunicipal;						//是否城投				编码："Y"
		std::string			m_sRemainDate;						//剩余期限，临时变量

		int		m_nBondType;						//根据QM需求提供的值 定义如下
		//enum EBondType
		//{
		//	Bond_Type_Begin = 0,                      // 起始符
		//	Bond_Type_National = Bond_Type_Begin,     // 国债
		//	Bond_Type_Financial,                      // 金融债
		//	Bond_Type_Municipals,                     // 地方债
		//	Bond_Type_ShortFinancial,                 // 短融
		//	Bond_Type_Ticket,                         // 中票
		//	Bond_Type_Enterprise,                     // 企业债
		//	Bond_Type_Others,                         // 其他
		//	Bond_Type_End,                            // 结束符
		//};
	};

	typedef std::list<BondItem> LstBondItem;

	struct MsgInfo
	{
		Contact MsgFrom;
		std::string sMsgDisplay;
		time_t RecvTime;
	};

	typedef std::list<MsgInfo> LstMsgInfo;

	struct BondQuotInfo
	{
		//债券唯一编码
		std::string sCombBondKey;
		//Bid价
		std::string sBid;
		//Bid数量
		std::string sVolBid;
		//Ofr价
		std::string sOfr;
		//Ofr数量
		std::string sVolOfr;
		//报价时间
		time_t QuotTime;
	};

	typedef std::list<BondQuotInfo> LstBondQuotInfo;

	struct BondQuotByCode
	{
		//报价ID
		std::string sQuotID;
		//报价信息
		BondQuotInfo BQInfo;
		//撤销时间
		time_t tExpirationTime;
		//撤销计时类型
		int nCancelType;
		//标签
		LstMultilanguageStr lstTags;
		//备注
		std::string sMemo;
	};

	typedef std::list<BondQuotByCode> LstBondQuotByCode;

	struct BondQuotByCodeSendInfo
	{
		Contact SendTo;
		LstBondQuotByCode lstQuots;
		time_t SendTime;
		int nMngType;		//0为发送, 1为撤销

		BondQuotByCodeSendInfo()
			:SendTime(0)
			,nMngType(0)
		{
		}
	};

	typedef std::list<BondQuotByCodeSendInfo> LstBondQuotByCodeSendInfo;

	//债券报价回复(按代码)
	struct BondQuotByCodeReplyInfo
	{
		//回复到
		Contact ReplyTo;
		//报价信息
		BondQuotByCode Quot;
	};

	struct Condition
	{
		MultilanguageStr sName;
		KeyValues ConditionInfo;
	};

	typedef std::list<Condition> LstCondition;

	struct BondQuotByCondition
	{
		std::string sQuotID;
		//方向
		MultilanguageStr sDirect;
		//数量
		std::string sCount;
		//条件
		LstCondition lstConditions;
		//撤销时间
		time_t tExpirationTime;
		//撤销计时类型
		int nCancelType;
		//标签
		LstMultilanguageStr lstTags;
		//备注
		std::string sMemo;
	};

	typedef std::list<BondQuotByCondition> LstBondQuotByCondition;

	struct BondQuotByConditionSendInfo
	{
		Contact SendTo;
		LstBondQuotByCondition lstQuots;
		time_t SendTime;
		int nMngType;		//0为发送, 1为撤销

		BondQuotByConditionSendInfo()
			:SendTime(0)
			,nMngType(0)
		{
		}
	};

	typedef std::list<BondQuotByConditionSendInfo> LstBondQuotByConditionSendInfo;

    //联系人搜索输入,只查询用户,不查询群
    struct ContactSearch
    {
        //搜索的关键字
        std::string sKey;
        //最大返回个数
        int nLimitUser;
        //查询类型:0为查询全市场;1为查询好友
        int nSearchType;

        ContactSearch()
            :sKey("")
            ,nLimitUser(0)
            ,nSearchType(0)
        {}
    };

    //联系人搜索返回
    struct SearchUserInfo
    {
        //用户ID
        unsigned long long nUserID;
        //用户名称
        std::string sUserName;
        //公司简称
        std::string sCompanyName;
    };

    typedef std::list<SearchUserInfo> LstSearchUserInfo;


	//债券报价回复(按条件)
	struct BondQuotByConditionReplyInfo
	{
		//回复到
		Contact ReplyTo;
		//报价信息
		BondQuotByCondition Quot;
	};


    //==报价发送信息V2 针对QM群发进行优化
    //MM报价
    struct QuotSendInfoV2_MM
    {
        LstQuotation lstQuots;
        LstContact lstSendTo; 
        time_t SendTime;
        int nMngType;		//0为发送, 1为撤销

        QuotSendInfoV2_MM()
            :SendTime(0)
            ,nMngType(0)
        {
        }
    };

    typedef std::list<QuotSendInfoV2_MM> LstMMQuotSendInfoV2;

    //Bond报价ByCode
    struct QuotSendInfoV2_BondByCode
    {
        LstBondQuotByCode lstQuots;
        LstContact lstSendTo;        
        time_t SendTime;
        int nMngType;		//0为发送, 1为撤销

        QuotSendInfoV2_BondByCode()
            :SendTime(0)
            ,nMngType(0)
        {
        }
    };

    typedef std::list<QuotSendInfoV2_BondByCode> LstBondQuotByCodeSendInfoV2;

    //====================================

    //一级申购报价信息
    struct PurchaseInfo
    {
        //申购ID
        std::string sPurchaseID;
        //最后修改时间
        time_t ModifyTime;
        //QM中显示的前半部信息
        std::string sMsgDisplayP1;
        //QM中显示的后半部信息
        std::string sMsgDisplayP2;

        PurchaseInfo()
            :sPurchaseID("")
            ,ModifyTime(0)
            ,sMsgDisplayP1("")
            ,sMsgDisplayP2("")
        {}
    };

    //一级申购报价唯一Key
    struct PurchaseUkey
    {
        //申购ID
        std::string sPurchaseID;
        //最后修改时间
        time_t ModifyTime;

        PurchaseUkey()
            :sPurchaseID("")
            ,ModifyTime(0)
        {}

        PurchaseUkey(const std::string& sPID, time_t mt)
            :sPurchaseID(sPID)
            ,ModifyTime(mt)
        {}

        bool operator < (const PurchaseUkey& rIn) const
        {
            if (sPurchaseID != rIn.sPurchaseID)
            {
                return sPurchaseID < rIn.sPurchaseID;
            }
            return ModifyTime < rIn.ModifyTime;
        }

        bool operator == (const PurchaseUkey& rIn) const
        {
            return sPurchaseID == rIn.sPurchaseID && ModifyTime == rIn.ModifyTime;
        }
    };

    typedef std::list<PurchaseUkey> LstPurchaseUkey;

    //申购报价的状态:1.申购可确认; 2.申购已确认; 3.无效的申购(已被修改); -1.查询失败;
    typedef std::map<PurchaseUkey, int> MapPurchaseStatus;

    //报价状态查询结构
    struct QuotStatusReq
    {
        //报价ID
        std::string sQuotID;
        //报价发送目标
        Contact Ct;

        QuotStatusReq()
            :sQuotID("")
        {}
    };

    typedef std::list<QuotStatusReq> LstQuotStatusReq;

    //报价状态
    struct QuotStatus
    {
        //报价ID
        std::string sQuotID;
        //报价发送目标
        Contact Ct;
        //报价状态
        //1.有效; 2.已撤销; -1.查询失败;
        int nStatus; 

        QuotStatus()
            :sQuotID("")
            ,nStatus(0)
        {}

        QuotStatus(const std::string& q, int s)
            :sQuotID(q)
            ,nStatus(s)
        {}
    };

    typedef std::list<QuotStatus> LstQuotStatus;

    //联系人状态
    struct ContactStatus
    {
        //联系人
        Contact Ct;
        //联系人状态
        //-1.无法获取状态; 1.在线; 2.离线; 3.离开; 4.忙碌;
        int nStatus;

        ContactStatus()
            :nStatus(0)
        {}
    };

    typedef std::list<ContactStatus> LstContactStatus;

    //非合作机构联系人
    struct NoInstituteContact
    {
        std::string sQBAccount;//QBID
        std::string sInstituteName;//机构名称
        std::string sName;//显示名称
        unsigned long long ullQMId;//QM登陆账号
    };
    typedef std::list<NoInstituteContact> LstNoInstituteContact;

    //QBAccount和QMID的对应结构
    struct QBAccount2QMID
    {
        std::string sQBAccount;
        unsigned long long nQMID;

        QBAccount2QMID()
            :sQBAccount("")
            ,nQMID(0)
        {}
    };

    typedef std::list<QBAccount2QMID> LstQBAccount2QMID;

    //begin============QM提醒设置相关结构============
    //关键字设置项
    struct QMRemindKeyItem
    {
        //ID
        std::string sID;
        //关键字
        std::string sKeyWord;
        //设置状态:0为未启用;1为已启用
        int nStatus;
        //显示顺序
        int nOrder;
        
        QMRemindKeyItem()
            :sID("")
            ,sKeyWord("")
            ,nStatus(0)
            ,nOrder(0)
        {}

    };

    typedef std::list<QMRemindKeyItem> LstQMRKey;

    //好友设置项
    struct QMRemindFriendItem
    {
        //ID
        std::string sID;
        //显示名称
        std::string sDisplayName;
        //好友QMID
        unsigned long long nQMID;
        //设置状态:0为未启用;1为已启用
        int nStatus;
        //显示顺序
        int nOrder;

        QMRemindFriendItem()
            :sDisplayName("")
            ,nQMID(0)
            ,nStatus(0)
            ,nOrder(0)
        {}
    };

    typedef std::list<QMRemindFriendItem> LstQMRFriend;

#define  REMINDTYPE_QM          0x00000001
#define  REMINDTYPE_POPWND      0x00000002

    //QM提醒设置
    struct QMRemindConfig
    {
        //关键字提醒内容
        LstQMRKey KeyConfig;
        //好友提醒内容
        LstQMRFriend FriendConfig;
        //提醒方式,可以通过与REMINDTYPE_QM和REMINDTYPE_POPWND的位运算判断
        unsigned int nRemindType;

        QMRemindConfig()
            :nRemindType(0)
        {}
    };
    //end============QM提醒设置相关结构============


    //begin============债券分享相关结构============

    struct BondShareItem
    {
        //债券唯一编码;
        std::string sCombBondKey;
        //债券代码
        std::string sBondCode;
        //债券简称
        std::string sBondShortName;
        //备注信息
        std::string sMemo;

        BondShareItem()
            :sCombBondKey("")
            ,sBondCode("")
            ,sBondShortName("")
            ,sMemo("")
        {}
    };
    
    typedef std::list<BondShareItem> LstBondShare;

    //end============债券分享相关接口============
}