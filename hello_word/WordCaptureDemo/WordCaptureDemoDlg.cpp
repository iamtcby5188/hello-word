
// WordCaptureDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WordCaptureDemo.h"
#include "WordCaptureDemoDlg.h"
#include "afxdialogex.h"
//#include "../WordCaptureDll/WordCapture.h"
#include "../WordCapture/WordCapture.h"
#include <conio.h>
//#pragma comment(lib,"WordCaptureDll.lib")
#pragma comment(lib,"WordCapture.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWordCaptureDemoDlg* pDlg;
#define  WM_WORDCAPTURE (WM_USER + 1000)
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWordCaptureDemoDlg 对话框



CWordCaptureDemoDlg::CWordCaptureDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWordCaptureDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWordCaptureDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWordCaptureDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    ON_BN_CLICKED(IDOK, &CWordCaptureDemoDlg::OnBnClickedOk)
    ON_MESSAGE(WM_KICKIDLE,OnKickIdle)
    ON_BN_CLICKED(IDC_BUTTON1, &CWordCaptureDemoDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CWordCaptureDemoDlg::OnBnClickedButton2)
    ON_WM_DESTROY()
    ON_MESSAGE(WM_WORDCAPTURE,OnWordCapture)
    ON_BN_CLICKED(IDC_BUTTON3, &CWordCaptureDemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CWordCaptureDemoDlg 消息处理程序

BOOL CWordCaptureDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
    //AllocConsole();
    pDlg = this;
    WC_Init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWordCaptureDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWordCaptureDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWordCaptureDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWordCaptureDemoDlg::OnBnClickedOk()
{
     CDialogEx::OnOK();
}

void CWordCaptureDemoDlg::OnTimer(UINT_PTR nIDEvent)
{

}
 
LRESULT CWordCaptureDemoDlg::OnKickIdle(WPARAM wp, LPARAM lp)
{
    return 0;
}


void CWordCaptureDemoDlg::OnBnClickedButton1()
{
    // TODO:  在此添加控件通知处理程序代码
}


void CWordCaptureDemoDlg::OnBnClickedButton2()
{
    // TODO:  在此添加控件通知处理程序代码
    WC_StopCapture();
}


void CWordCaptureDemoDlg::OnDestroy()
{
    CDialogEx::OnDestroy();
    WC_Uninit();
    // TODO:  在此处添加消息处理程序代码
}

LRESULT CWordCaptureDemoDlg::OnWordCapture(WPARAM wp, LPARAM lp)
{
    GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_str);
    return 0;
}

void proc(char* sz, int size)
{
    CStringA sA(sz);
    pDlg->m_str = CString(sA);
    pDlg->PostMessage(WM_WORDCAPTURE, NULL, NULL);

}

void CWordCaptureDemoDlg::OnBnClickedButton3()
{
    //WC_StartCapture();
    WC_StartCapture(proc);

    // TODO:  在此添加控件通知处理程序代码
}
