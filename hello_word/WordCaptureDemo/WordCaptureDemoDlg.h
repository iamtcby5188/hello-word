
// WordCaptureDemoDlg.h : ͷ�ļ�
//

#pragma once


// CWordCaptureDemoDlg �Ի���
class CWordCaptureDemoDlg : public CDialogEx
{
// ����
public:
	CWordCaptureDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WORDCAPTUREDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    afx_msg LRESULT OnKickIdle(WPARAM wp, LPARAM lp);
    afx_msg LRESULT OnWordCapture(WPARAM wp, LPARAM lp);
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnDestroy();
    CString m_str;
public:
    afx_msg void OnBnClickedButton3();
};
