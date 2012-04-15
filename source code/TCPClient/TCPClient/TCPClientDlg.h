
// TCPClientDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DataSocket.h"


// CTCPClientDlg ��ȭ ����
class CTCPClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTCPClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CDataSocket dataSocket;
	CString m_strServerAddress;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TCPCLIENT_DIALOG };

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
	CEdit m_edListData;
	CString m_strSendData;
	CString m_strPort;
	CIPAddressCtrl m_ipServerAddress;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonStop();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
