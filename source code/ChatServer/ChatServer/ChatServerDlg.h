
// ChatServerDlg.h : 헤더 파일
//

#pragma once

#include "afxwin.h"
#include "ListenSocket.h"
#include "ClientSocket.h"

// CChatServerDlg 대화 상자
class CChatServerDlg : public CDialog
{
// 생성입니다.
public:
	CChatServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	CListenSocket m_ListenSocket;
	CClientSocket m_Socket;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHATSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
