
// ChatClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CChatClientDlg 대화 상자




CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatClientDlg::IDD, pParent)
	, m_strMessage(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_List, m_List);
	DDX_Text(pDX, IDC_Edit_Message, m_strMessage);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Button_Send, &CChatClientDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CChatClientDlg 메시지 처리기

BOOL CChatClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	m_Socket.Create();
	if(m_Socket.Connect(_T("127.0.0.1"), 3600) == FALSE)
	{
		AfxMessageBox(_T("ERROR: Failed to connect server"));
		PostQuitMessage(0);

		return FALSE;
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

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
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatClientDlg::OnBnClickedButtonSend()
{
	
	UpdateData(TRUE);
	m_Socket.Send((LPVOID)(LPCTSTR)m_strMessage,
					m_strMessage.GetLength() * 2);

	m_strMessage = _T("");
	UpdateData(FALSE);
	/*
	CString strFileName = _T("123.jpeg");

	CFile sourceFile;
	sourceFile.Open((LPCTSTR)strFileName, CFile::modeRead | CFile::typeBinary);
	// strFileName은 CString 객체로 파일의 이름을 가지고 있다.

	int nNameLen = strFileName.GetLength(); // 파일이름의 길이를 저장한다.

	// 파일을 전송하기 전에 파일이름을 클라이언트에게 알려줘야 한다. 
	// 그래야 클라이언트는 전송받은 파일을 이름을 바꾸지 않고 정확히 쓸 것이다.
	/*
	int nNameLen = strFileName.GetLength(); // 파일이름의 길이를 저장한다.

	acceptSoc.Send(&nNameLen, 4); // 파일 이름의 길이를 전달한다.
	acceptSoc.Send((LPCTSTR)strFileName, nNameLen); // 파일 이름을 전달한다.
	// 데이터를 위한 임시 버퍼을 잡자.


	m_Socket.Send(&nNameLen, 4);
	m_Socket.Send((LPCTSTR)strFileName, nNameLen);
	byte * data = new byte[4096];
	DWORD dwRead;
	// 파일을 읽고 소켓으로 전송하자.
	do
	{
		dwRead = sourceFile.Read(data, 4096);
		m_Socket.Send(data, dwRead);
	}
	while(dwRead > 0);
	*/
}
