
// KeyboardForAndroidMsgDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "KeyboardForAndroidMsg.h"
#include "KeyboardForAndroidMsgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CKeyboardForAndroidMsgDlg 대화 상자




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
	DDX_Control(pDX, IDC_PICVIEW, imgViewer);
}

BEGIN_MESSAGE_MAP(CKeyboardForAndroidMsgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CKeyboardForAndroidMsgDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CKeyboardForAndroidMsgDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CKeyboardForAndroidMsgDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_KATALK_START, &CKeyboardForAndroidMsgDlg::OnBnClickedButtonKatalkStart)
	ON_BN_CLICKED(IDC_UP, &CKeyboardForAndroidMsgDlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_LEFT, &CKeyboardForAndroidMsgDlg::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_DOWN, &CKeyboardForAndroidMsgDlg::OnBnClickedDown)
	ON_BN_CLICKED(IDC_RIGHT, &CKeyboardForAndroidMsgDlg::OnBnClickedRight)
	ON_BN_CLICKED(IDC_ENTER, &CKeyboardForAndroidMsgDlg::OnBnClickedEnter)
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CKeyboardForAndroidMsgDlg 메시지 처리기

BOOL CKeyboardForAndroidMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CRect tmpRect;
	GetDlgItem(IDC_PICVIEW)->MoveWindow(10, 10, 300, 370);
	GetDlgItem(IDC_PICVIEW)->GetClientRect(tmpRect);
	imgViewerRect.SetRect(tmpRect.left+10, tmpRect.top+10, tmpRect.right+10, tmpRect.bottom+10);

	img.Load(CString("katalk.jpg"));
	Invalidate();

	AddMessage("기본 ip : 192.168.0.11");
	AddMessage("기본 포트 3600");

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CKeyboardForAndroidMsgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); 
	
		img.Draw(dc.m_hDC, imgViewerRect);

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CKeyboardForAndroidMsgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKeyboardForAndroidMsgDlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		AddMessage("이미 서버에 접속 되어있습니다.");
	}

	if(!dataSocket.Create())
	{
		AddMessage("소켓 생성 실패");
	}

	if(!dataSocket.Connect(m_strServerAddress,port))
	{
		dataSocket.Close();
		AddMessage("서버 접속 실패");
	}
	else
	{
		CString strPt;
		strPt.Format("포트번호 %d", port);
		AddMessage(strPt);
		AddMessage(m_strServerAddress);


		AddMessage("서버에 접속 됐습니다.");
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	}
}

void CKeyboardForAndroidMsgDlg::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(dataSocket.m_hSocket != INVALID_SOCKET)
	{
		dataSocket.Close();
		AddMessage("서버와의 접속을 종료합니다.");
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	}
	else
	{
		AddMessage("이미 종료되었습니다.");
	}
}


void CKeyboardForAndroidMsgDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	CString strSend;
	strSend.Format("%s", m_strSendData);

	dataSocket.Send(AnsiToUTF8RetCString(strSend), 
		AnsiToUTF8RetCString(strSend).GetLength()+1);

	GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	m_strSendData = "";
	UpdateData(FALSE);
}


BOOL CKeyboardForAndroidMsgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN && 
			GetFocus()->GetDlgCtrlID() == IDC_EDIT_SEND_DATA)
		{
			OnBnClickedButtonSend();
			return TRUE;
		}

		switch(pMsg->wParam){
			case VK_LEFT:
				OnBnClickedLeft();
				break;
			case VK_RIGHT:
				OnBnClickedRight();
				break;
			case VK_UP:
				OnBnClickedUp();
				break;
			case VK_DOWN:
				OnBnClickedDown();
				break;
		}

		/*
		else if(pMsg->wParam == VK_RETURN &&
			GetFocus()->GetDlgCtrlID() == IDD_KEYBOARDFORANDROIDMSG_DIALOG)
		{
			OnBnClickedEnter();
			return TRUE;
		}
		*/
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

	AddMessage("서버가 연결을 종료 했습니다.");
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);

	return 0;
}

void CKeyboardForAndroidMsgDlg::OnBnClickedButtonKatalkStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	
	CString strKatalkStart;
	strKatalkStart.Format("%s", "\\\\kakao_on");
	dataSocket.Send(strKatalkStart, strKatalkStart.GetLength()+1);

	GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	UpdateData(FALSE);

	AddMessage("카카오톡 실행");	
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

void CKeyboardForAndroidMsgDlg::OnBnClickedUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	
	CString strUp;
	strUp.Format("%s", "\\\\CONTROL_U");
	dataSocket.Send(strUp, strUp.GetLength()+1);

	GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	GetDlgItem(IDC_EDIT_SEND_DATA)->SendMessage(WM_KILLFOCUS, NULL); 
	GetDlgItem(IDC_UP)->SendMessage(WM_KILLFOCUS, NULL); 
	/*UpdateData(FALSE);*/
}


void CKeyboardForAndroidMsgDlg::OnBnClickedLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strLeft;
	strLeft.Format("%s", "\\\\CONTROL_L");
	dataSocket.Send(strLeft, strLeft.GetLength()+1);

	GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	GetDlgItem(IDC_LEFT)->SendMessage(WM_KILLFOCUS, NULL); 
	GetDlgItem(IDC_EDIT_SEND_DATA)->SendMessage(WM_KILLFOCUS, NULL);
	//UpdateData(FALSE);
}


void CKeyboardForAndroidMsgDlg::OnBnClickedDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strDown;
	strDown.Format("%s", "\\\\CONTROL_D");
	dataSocket.Send(strDown, strDown.GetLength()+1);

	GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	GetDlgItem(IDC_EDIT_SEND_DATA)->SendMessage(WM_KILLFOCUS, NULL); 
	GetDlgItem(IDC_DOWN)->SendMessage(WM_KILLFOCUS, NULL); 
}


void CKeyboardForAndroidMsgDlg::OnBnClickedRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strRight;
	strRight.Format("%s", "\\\\CONTROL_R");
	dataSocket.Send(strRight, strRight.GetLength()+1);

	GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	GetDlgItem(IDC_EDIT_SEND_DATA)->SendMessage(WM_KILLFOCUS, NULL); 
	GetDlgItem(IDC_RIGHT)->SendMessage(WM_KILLFOCUS, NULL); 
}


void CKeyboardForAndroidMsgDlg::OnBnClickedEnter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strEnter;
	strEnter.Format("%s", "\\\\CONTROL_E");
	dataSocket.Send(strEnter, strEnter.GetLength()+1);

	GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	GetDlgItem(IDC_EDIT_SEND_DATA)->SendMessage(WM_KILLFOCUS, NULL); 
	GetDlgItem(IDC_ENTER)->SendMessage(WM_KILLFOCUS, NULL); 
	//UpdateData(FALSE);
}

/*
void CKeyboardForAndroidMsgDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch(nChar)
	{
		case VK_LEFT:
			OnBnClickedLeft();
			break;
		case VK_RIGHT:
			OnBnClickedRight();
			break;
		case VK_UP:
			OnBnClickedUp();
			break;
		case VK_DOWN:
			OnBnClickedDown();
			break;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
*/