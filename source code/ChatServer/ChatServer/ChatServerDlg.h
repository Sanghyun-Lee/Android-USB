
// ChatServerDlg.h : ��� ����
//

#pragma once

#include "afxwin.h"
#include "ListenSocket.h"
#include "ClientSocket.h"

// CChatServerDlg ��ȭ ����
class CChatServerDlg : public CDialog
{
// �����Դϴ�.
public:
	CChatServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CListenSocket m_ListenSocket;
	CClientSocket m_Socket;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHATSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
	CString m_strMsg;
	TCHAR* StringToTChar(CString string);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedSend();
	CEdit etext;
};
