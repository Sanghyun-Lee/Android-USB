
// KeyboardForAndroidMsgDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DataSocket.h"
#include "atlimage.h"


// CKeyboardForAndroidMsgDlg 대화 상자
class CKeyboardForAndroidMsgDlg : public CDialogEx
{
// 생성입니다.
public:
	CKeyboardForAndroidMsgDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	CDataSocket dataSocket;
	CString m_strServerAddress;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_KEYBOARDFORANDROIDMSG_DIALOG };

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
	afx_msg LRESULT OnCloseSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);
	void AddMessage(CString strMsg);
	DECLARE_MESSAGE_MAP()
public:
	CString m_strListData;
	CString m_strSendData;
	CString m_strPort;
	CEdit m_edListData;
	CIPAddressCtrl m_ipServerAddress;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonSend();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonKatalkStart();
	CImage img;
	CString AnsiToUTF8RetCString(CString inputStr);
	CRect imgViewerRect;
	CStatic imgViewer;
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedDown();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedEnter();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
