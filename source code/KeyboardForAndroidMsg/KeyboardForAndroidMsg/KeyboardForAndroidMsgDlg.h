
// KeyboardForAndroidMsgDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DataSocket.h"
#include "atlimage.h"


// CKeyboardForAndroidMsgDlg ��ȭ ����
class CKeyboardForAndroidMsgDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CKeyboardForAndroidMsgDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CDataSocket dataSocket;
	CString m_strServerAddress;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_KEYBOARDFORANDROIDMSG_DIALOG };

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
