
// KeyboardForAndroidMsgDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "KeyboardForAndroidMsg.h"
#include "KeyboardForAndroidMsgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CKeyboardForAndroidMsgDlg ��ȭ ����




CKeyboardForAndroidMsgDlg::CKeyboardForAndroidMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyboardForAndroidMsgDlg::IDD, pParent)
	, m_strListData(_T(""))
	, m_strSendData(_T(""))
	, m_strPort(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyboardForAndroidMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LIST, m_strListData);
	DDX_Text(pDX, IDC_EDIT_SEND_DATA, m_strSendData);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
	DDX_Control(pDX, IDC_EDIT_LIST, m_edListData);
	DDX_Control(pDX, IDC_IPADDRESS, m_ipServerAddress);
}

BEGIN_MESSAGE_MAP(CKeyboardForAndroidMsgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CKeyboardForAndroidMsgDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CKeyboardForAndroidMsgDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CKeyboardForAndroidMsgDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_KATALK_START, &CKeyboardForAndroidMsgDlg::OnBnClickedButtonKatalkStart)
END_MESSAGE_MAP()


// CKeyboardForAndroidMsgDlg �޽��� ó����

BOOL CKeyboardForAndroidMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ���� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	AddMessage("�⺻ ip : 192.168.0.11");
	AddMessage("�⺻ ��Ʈ 3600");

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CKeyboardForAndroidMsgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CKeyboardForAndroidMsgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CKeyboardForAndroidMsgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKeyboardForAndroidMsgDlg::OnBnClickedButtonConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	int port;

	if(m_strPort != "")
	{
		port = atoi((LPCSTR)m_strPort);
	}
	else
	{
		port = 3600;
	}

	if(m_strServerAddress != "")
	{
		m_ipServerAddress.GetWindowText(m_strServerAddress);
	}
	else
	{
		m_strServerAddress = "192.168.0.11";
	}

	if(dataSocket.m_hSocket != INVALID_SOCKET)
	{
		AddMessage("�̹� ������ ���� �Ǿ��ֽ��ϴ�.");
	}

	if(!dataSocket.Create())
	{
		AddMessage("���� ���� ����");
	}

	if(!dataSocket.Connect(m_strServerAddress,port))
	{
		dataSocket.Close();
		AddMessage("���� ���� ����");
	}
	else
	{
		CString strPt;
		strPt.Format("��Ʈ��ȣ %d", port);
		AddMessage(strPt);
		AddMessage(m_strServerAddress);


		AddMessage("������ ���� �ƽ��ϴ�.");
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	}
}

void CKeyboardForAndroidMsgDlg::OnBnClickedButtonStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(dataSocket.m_hSocket != INVALID_SOCKET)
	{
		dataSocket.Close();
		AddMessage("�������� ������ �����մϴ�.");
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	}
	else
	{
		AddMessage("�̹� ����Ǿ����ϴ�.");
	}
}


void CKeyboardForAndroidMsgDlg::OnBnClickedButtonSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	CString strSend;
	strSend.Format("%s", m_strSendData);

	dataSocket.Send(strSend, strSend.GetLength()+1);

	GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	m_strSendData = "";
	UpdateData(FALSE);
}


BOOL CKeyboardForAndroidMsgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN && 
			GetFocus()->GetDlgCtrlID() == IDC_EDIT_SEND_DATA)
		{
			OnBnClickedButtonSend();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CKeyboardForAndroidMsgDlg::AddMessage(CString strMsg)
{
	UpdateData();
	if(m_strListData == "")
		m_strListData = strMsg;
	else
		m_strListData = m_strListData + "\r\n" + strMsg;

	UpdateData(FALSE);

	m_edListData.LineScroll(m_edListData.GetLineCount());
}


LRESULT CKeyboardForAndroidMsgDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{
	char Rcvdata[1024];

	CDataSocket* pDataSocket = (CDataSocket*)wParam;

	pDataSocket->Receive(Rcvdata, sizeof(Rcvdata));

	CString strMsg = Rcvdata;

	AddMessage(strMsg);

	return 0;
}

LRESULT CKeyboardForAndroidMsgDlg::OnCloseSocket(WPARAM wParam, LPARAM lParam)
{
	dataSocket.Close();

	AddMessage("������ ������ ���� �߽��ϴ�.");
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);

	return 0;
}

void CKeyboardForAndroidMsgDlg::OnBnClickedButtonKatalkStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();

	if(strKatalkStart == "")
	{
		strKatalkStart.Format("%s", "\\\\kakao_on");
		dataSocket.Send(strKatalkStart, strKatalkStart.GetLength()+1);

		GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
		UpdateData(FALSE);

		AddMessage("īī���� ����");
	}
	else
	{
		AddMessage("īī������ �̹� ����Ǿ����ϴ�.");
	}
}

CString CKeyboardForAndroidMsgDlg::AnsiToUTF8RetCString(CString inputStr)
{
	WCHAR szUnicode[1024];
	char szUTF8char[1024];

	CString strConvert;
	char* szSrc = (LPSTR)(LPCTSTR)inputStr;

	char szRetValue[1024] = "";

	int unicodeSize = MultiByteToWideChar(CP_ACP, 0,
		szSrc, (int)strlen(szSrc), 
		szUnicode, sizeof(szUnicode));

	int UTF8CodeSize = WideCharToMultiByte(CP_UTF8, 0, 
		szUnicode, unicodeSize, szUTF8char,
		sizeof(szUTF8char), NULL, NULL);

	memcpy(szRetValue, szUTF8char, UTF8CodeSize);
	strConvert = szRetValue;

	return strConvert;

}