
// usbip_uiDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "usbip_ui.h"
#include "usbip_uiDlg.h"
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


// Cusbip_uiDlg 대화 상자




Cusbip_uiDlg::Cusbip_uiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cusbip_uiDlg::IDD, pParent)
	, m_strListData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cusbip_uiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS, m_edIpServerAddress);
	DDX_Text(pDX, IDC_EDIT3, m_strListData);
	DDX_Control(pDX, IDC_EDIT3, m_edListData);
	DDX_Control(pDX, IDC_BUSID, selBusid);
}

BEGIN_MESSAGE_MAP(Cusbip_uiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_ACCEPT_MESSAGE, &Cusbip_uiDlg::OnAcceptClient)
	ON_MESSAGE(UM_RECEIVE_MESSAGE, &Cusbip_uiDlg::OnReceiveData)
	ON_MESSAGE(UM_CLOSE_MESSAGE, &Cusbip_uiDlg::OnCloseSocket)
	ON_BN_CLICKED(IDC_LIST, &Cusbip_uiDlg::OnBnClickedList)
	ON_BN_CLICKED(IDC_CONNECT, &Cusbip_uiDlg::OnBnClickedConnect)
<<<<<<< HEAD
	ON_BN_CLICKED(IDC_DISCONNECT, &Cusbip_uiDlg::OnBnClickedDisconnect)
	ON_EN_CHANGE(IDC_EDIT3, &Cusbip_uiDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_CLOSE, &Cusbip_uiDlg::OnBnClickedClose)
=======
	ON_CBN_SELCHANGE(IDC_BUSID, &Cusbip_uiDlg::OnCbnSelchangeBusid)
>>>>>>> 85414d9bbbf2165ee73f96dde613a13c86c0d59b
END_MESSAGE_MAP()


// Cusbip_uiDlg 메시지 처리기

BOOL Cusbip_uiDlg::OnInitDialog()
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

//	WinExec(_T("C:/WinDDK/7600.16385.1/src/usb/usbip/Debug/usbip.exe"), SW_SHOW);
/*	
	STARTUPINFO StartupInfo = {0};
	PROCESS_INFORMATION ProcessInfo;
	StartupInfo.cb = sizeof(STARTUPINFO);
	::CreateProcess(NULL, "C:/WinDDK/7600.16385.1/src/usb/usbip/Debug/usbip.exe",
		NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo);
*/
	if(listenSocket.m_hSocket != INVALID_SOCKET)
	{
		AddMessage("이미 대기 상태입니다.");
	}

	if(!listenSocket.Create(PORT))
	{
		AddMessage("소켓 생성 실패");
	}

	if(!listenSocket.Listen())
	{
		AddMessage("대기 실패");

		listenSocket.Close();
	}
	else
	{
		AddMessage("서버가 실행 되었습니다.");
	}
	//ShellExecute(NULL, _T("open") ,_T("C:/Documents and Settings/Administrator/바탕 화면/usbip/Debug/usbip.exe"),NULL ,NULL, SW_SHOW);
	ShellExecute(NULL, _T("open") ,_T("cmd.exe"),_T("/K Run.bat") ,NULL, SW_SHOW);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cusbip_uiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cusbip_uiDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cusbip_uiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT Cusbip_uiDlg::OnAcceptClient(WPARAM wParam, LPARAM lParam)
{
	listenSocket.Accept(dataSocket);
	AddMessage("클라이언트가 접속했습니다.");
	return 0;
}

LRESULT Cusbip_uiDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{
	char Rcvdata[MAXLINE];

	CDataSocket* pDataSocket = (CDataSocket*)wParam;

	pDataSocket->Receive(Rcvdata, sizeof(Rcvdata));

	CString strMsg = Rcvdata;

	AddMessage(strMsg);

	return 0;
}

// 서버와의 연결 종료 처리
LRESULT Cusbip_uiDlg::OnCloseSocket(WPARAM wParam, LPARAM lParam)
{
	dataSocket.Close();
	/*
	AddMessage("서버가 연결을 종료 했습니다.");
	// 접속끊기 버튼 비활성화, 서버접속 버튼 활성화, 보내기 버튼 비활성화
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	*/

	return 0;
}

void Cusbip_uiDlg::AddMessage(CString strMsg)
{

	UpdateData();
	
	m_strListData += strMsg + "\r\n";

	UpdateData(FALSE);

	m_edListData.LineScroll(m_edListData.GetLineCount());
}

BOOL Cusbip_uiDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void Cusbip_uiDlg::OnBnClickedList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int ret = 0;
	CString strMsg;
	char buf[8000];
	CString listData;
	CString strAddress;
	m_edIpServerAddress.GetWindowText(strAddress);
	strMsg.Format("l");
	
	ret = dataSocket.Send(strMsg, strMsg.GetLength()+1);
	if(ret < 1){
		AddMessage("메세지 전송 실패");
		return;
	}
	AddMessage("전송 : "+strMsg);

	ret = dataSocket.Send(strAddress, strAddress.GetLength()+1);
	if(ret < 1){
		AddMessage("메세지 전송 실패");
		return;
	}
	AddMessage("전송 : "+strAddress);

	
	while(dataSocket.Receive(buf, 8000)>0){
		listData += buf;
		memset(buf, 0, sizeof(buf));
	}

	m_edListData.SetWindowText(listData);
}


void Cusbip_uiDlg::OnBnClickedConnect()
{
<<<<<<< HEAD
	//ShellExecute(NULL, _T("open") ,_T("C:/Documents and Settings/Administrator/바탕 화면/usbip/Debug/usbip.exe"),NULL ,NULL, SW_SHOW);

	int ret = 0;
	CString strMsg;
	char buf[1024];
	CString listData;
	CString strAddress;
	m_edIpServerAddress.GetWindowText(strAddress);
	strMsg.Format("-a");
	
	ret = dataSocket.Send(strMsg, strMsg.GetLength()+1);
	if(ret < 1){
		AddMessage("메세지 전송 실패1");
		return;
	}
	AddMessage("전송 : "+strMsg);
	
	ret = dataSocket.Send(strAddress, strAddress.GetLength()+1);
	if(ret < 1){
		AddMessage("메세지 전송 실패2");
		return;
	}

	AddMessage("전송 : "+strAddress);

	
	
	while(dataSocket.Receive(buf, 8000)>0){
		listData += buf;
		memset(buf, 0, sizeof(buf));
	}

	m_edListData.SetWindowText(listData);
}


void Cusbip_uiDlg::OnBnClickedDisconnect()
{
	int ret = 0;
	CString strMsg;
	strMsg = "finish";

	ret = dataSocket.Send(strMsg, strMsg.GetLength()+1);
	if(ret < 1){
		AddMessage("메세지 전송 실패");
		return;
	}
}


void Cusbip_uiDlg::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Cusbip_uiDlg::OnBnClickedClose()
{
	int ret = 0;
	CString strMsg;
	strMsg = "finish";

	ret = dataSocket.Send(strMsg, strMsg.GetLength()+1);
	if(ret < 1){
		AddMessage("메세지 전송 실패");
		return;
	}
=======
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int ret = 0;
	CString strMsg;
	CString strAddress;
	m_edIpServerAddress.GetWindowText(strAddress);
	strMsg.Format("a");
	
	ret = dataSocket.Send(strMsg, strMsg.GetLength()+1);
	if(ret < 1){
		AddMessage("메세지 전송 실패");
		return;
	}
	AddMessage("전송 : "+strMsg);
	ret = dataSocket.Send(strAddress, strAddress.GetLength()+1);
	if(ret < 1){
		AddMessage("메세지 전송 실패");
		return;
	}
	AddMessage("전송 : "+strAddress);
	
>>>>>>> 85414d9bbbf2165ee73f96dde613a13c86c0d59b
}


void Cusbip_uiDlg::OnCbnSelchangeBusid()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = selBusid.GetCurSel();
	if(nIndex == -1){
		return;
	}

	CString busid;
	selBusid.GetLBText(nIndex, busid);

	sendMsg(busid);
	//GetDlgItem(IDC_EDIT_SEND_DATA)->SetFocus();
	UpdateData(FALSE);
}

void Cusbip_uiDlg::sendMsg(CString strMsg)
{
	int ret = 0;
	ret = dataSocket.Send(strMsg, strMsg.GetLength()+1);

	if(ret < 1){
		AddMessage("메세지 전송 실패");
		return;
	}
}
