
// TCPServerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ListenSocket.h"
#include "DataSocket.h"
#include "atlimage.h"

// CTCPServerDlg 대화 상자
class CTCPServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CListenSocket listenSocket;
	CDataSocket dataSocket;
	CTCPServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TCPSERVER_DIALOG };
	
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
	afx_msg LRESULT OnCloseSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAcceptClient(WPARAM wParam, LPARAM lParam);
	CString m_strListData;
	CString m_strSendData;
	CString m_strPort;
	CEdit m_edListData;
	afx_msg void OnBnClickedButtonStart();
	void AddMessage(CString strMsg);
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonStop();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic imgViewer;
	int nHeight;
	int nWidth;
	CRect imgViewerRect;
	afx_msg void OnBnClickedButtonKatalkStart();
	CString AnsiToUTF8RetCString(CString inputStr);
	CImage img;
	CString strKatalkStart;

};
