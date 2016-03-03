
// MouseTrainDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MouseTrain.h"
#include "MouseTrainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TRAY_NOTIFY          (WM_APP + 100) //트레이
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


// CMouseTrainDlg 대화 상자




CMouseTrainDlg::CMouseTrainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMouseTrainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pwndShow=NULL;
}

void CMouseTrainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB2, m_Tab);
}

BEGIN_MESSAGE_MAP(CMouseTrainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CMouseTrainDlg::OnTcnSelchangeTab2)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)//핫키
	//트레이
	ON_MESSAGE(TRAY_NOTIFY, OnTrayIconClick)
    ON_COMMAND(ID_TRAYMENU_OPEN, &CMouseTrainDlg::OnTraymenuOpen)
	ON_COMMAND(ID_TRAYMENU_CLOSE, &CMouseTrainDlg::OnTraymenuClose)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMouseTrainDlg 메시지 처리기

BOOL CMouseTrainDlg::OnInitDialog()
{
	HANDLE hEvent;
	hEvent = CreateEvent(NULL, FALSE, TRUE, AfxGetAppName()); 
	if ( GetLastError() == ERROR_ALREADY_EXISTS) { 
	AfxMessageBox("같은프로그램실행");
	exit(0) ;
	}
	
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

	//핫키 등록
	/*
	m_HotKey = ::GlobalAddAtom("F3");
	RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F3);
	
	m_HotKey2 = ::GlobalAddAtom("F6");
	RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F6);
	*/



	//탭컨트롤 설정
	m_Tab.InsertItem(0, _T("마우스 좌표"));
	m_Tab.InsertItem(1, _T("마우스 커서"));
	CRect rect;
	m_Tab.GetClientRect(&rect);
	m_one.Create(IDD_DIALOG1,&m_Tab);
	m_one.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_one;

	m_two.Create(IDD_DIALOG2,&m_Tab);
	m_two.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_NOZORDER);

	//초기화
	autoClickFlag=true;
	moveStateFlag=false;
	msize=0;

	/////////불러오기

	CStdioFile file;
	CFileStatus status;
	CFileException e;
	
	if(!file.Open("save.txt", CFile::modeRead, &e))
	{
        e.ReportError();
        return false;
    }
	
	CString temp;
	CString temp2;
	int c=0;
	while(file.ReadString(temp))
	{
		cname+=temp;
	}
	
	while(AfxExtractSubString(temp2, cname, c, ';'))   
	{   
		namearry[c++]=temp2;
	}

	cpath=namearry[0].GetBuffer(0);
	m_two.acpath=cpath;
	m_one.cpath=cpath;
	TabTwo::dpath=cpath;

	msize=_ttoi(namearry[6]);
	arrow = (HCURSOR)LoadImage(AfxGetInstanceHandle(),cpath,IMAGE_CURSOR,32+msize,32+msize,LR_LOADFROMFILE);
	ctemp = CopyCursor(arrow);
	::SetSystemCursor(arrow,32512);
	m_two.acChangeFlag=true;
	m_two.acname=namearry[0]+";";

	cpath=namearry[1].GetBuffer(0);
	wait = LoadCursorFromFile(cpath);
	ctemp = CopyCursor(wait);
	::SetSystemCursor(wait,32650);
	m_two.wcChangeFlag=true;
	m_two.wcname=namearry[1]+";";
	
	cpath=namearry[2].GetBuffer(0);
	TabTwo::fpath=cpath;
	m_one.bpath=cpath;
	button = LoadCursorFromFile(cpath);
	ctemp = CopyCursor(button);
	::SetSystemCursor(button,32649);
	m_two.bcChangeFlag=true;
	m_two.bcname=namearry[2]+";";

	if(namearry[3]=="1")
		m_one.moveStateFlag=true;
	else
		m_one.moveStateFlag=false;

	int a=_ttoi(namearry[4]);
	m_one.mpoint.x=a;
	a=_ttoi(namearry[5]);
	m_one.mpoint.y=a;

	m_one.whereStr=namearry[7];
	m_one.autoStr=namearry[8];	
	if(namearry[9]=="1")
		m_one.m_radio=1;
	else
		m_one.m_radio=0;
	m_one.ComboSetting();
	


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMouseTrainDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMouseTrainDlg::OnPaint()
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
HCURSOR CMouseTrainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMouseTrainDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	if(m_pwndShow != NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}
	int nIndex = m_Tab.GetCurSel();
	switch(nIndex)
	{
	case 0 : 
		m_one.ShowWindow(SW_SHOW);
		m_pwndShow = &m_one;
		break;
	case 1 :
		m_two.ShowWindow(SW_SHOW);
		m_pwndShow = &m_two;
		break;
	}
	*pResult = 0;
}


LRESULT CMouseTrainDlg::OnHotKey(WPARAM wp, LPARAM)
{
	
	if((int)wp == m_HotKey)
	{
		if(m_one.moveStateFlag)
		{
			SetCursorPos(m_one.mpoint.x,m_one.mpoint.y);//등록한 핫키 입력시 수행할 작업 입력한다.	
			ReleaseCapture();
		}
	}
	
	if((int)wp == m_HotKey2)
	{

		autoClickCheck=m_one.autoClickCheck;

		if(autoClickCheck)
		{
			if(autoClickFlag)
			{
				int temp=m_one.autoClickSecond;
				if(temp==0)
				{
					AfxMessageBox(_T("횟수를 입력하세요."));
				}
				else
				{
					autonum=temp;
					SetTimer(1,1000/autonum,NULL);
					autoClickFlag=false;
					m_one.autoClickFlag=false;
				}
			}
			else
			{
				KillTimer(1);
				autoClickFlag=true;
				m_one.autoClickFlag=true;
			}
		}
		else
		{
			return 0;
		}
	}


	

	return 0; // ignore
	
}


void CMouseTrainDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case 1 :
		mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
		mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CMouseTrainDlg::DestroyWindow()
{
	hoc = m_two.hoc;
	o_arrow = m_two.o_arrow;
	o_wait = m_two.o_wait;
	o_button = m_two.o_button;

	//MAKEINTRESOURCE(IDC_CURSOR1),IMAGE_CURSOR,64,64,LR_DEFAULTCOLOR); 
	//m_hCursor=(HCURSOR)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CURSOR1),IMAGE_CURSOR,64,64,LR_DEFAULTCOLOR); 
	// m_hCursor=CopyCursor(m_hCursor);
	hoc = LoadCursorFromFile(".\\res\\image\\arrow.cur");
	::SetSystemCursor(hoc,32512);

	o_arrow = LoadCursorFromFile(".\\res\\image\\arrow.cur");
	::SetSystemCursor(o_arrow,32512);

	o_wait = LoadCursorFromFile(".\\res\\image\\aero_busy.ani");
	::SetSystemCursor(o_wait,32514);

	o_button = LoadCursorFromFile(".\\res\\image\\button.cur");
	::SetSystemCursor(o_button,32649);

	UnregisterHotKey(m_hWnd, m_HotKey);
	UnregisterHotKey(m_hWnd, m_HotKey2);

	::DestroyCursor(hoc); ::DestroyCursor(arrow);	::DestroyCursor(o_arrow); ::DestroyCursor(wait);
	::DestroyCursor(o_wait); ::DestroyCursor(button); ::DestroyCursor(o_button); ::DestroyCursor(ctemp);

	//저장

	CFileException ex;
	CFile file;
	CString name=_T("save.txt");
	CString temp;

	file.Open(name, CFile::modeCreate | CFile::modeReadWrite, &ex);


	if(m_two.acChangeFlag)
	{
		file.Write(m_two.acname,m_two.acname.GetLength());
	}
	else
	{
		temp=".\\\\res\\\\image\\\\arrow.cur;";
		file.Write(temp,temp.GetLength());
	}


	if(m_two.wcChangeFlag)
	{	
		file.Write(m_two.wcname,m_two.wcname.GetLength());
	}
	else
	{
		temp=".\\\\res\\\\image\\\\aero_busy.ani;";
		file.Write(temp,temp.GetLength());
	}

	if(m_two.bcChangeFlag)
	{
		file.Write(m_two.bcname,m_two.bcname.GetLength());
	}
	else
	{
		temp=".\\\\res\\\\image\\\\button.cur;";
		file.Write(temp,temp.GetLength());
	}

	int a;
	if(m_one.moveStateFlag)
	{
		a=1;
		temp.Format("%d;",a);
		file.Write(temp,temp.GetLength());
	}
	else
	{
		a=0;
		temp.Format("%d;",a);
		file.Write(temp,temp.GetLength());
	}

	temp.Format("%d;%d;",m_one.mpoint.x,m_one.mpoint.y);
	file.Write(temp,temp.GetLength());
	
	
	temp.Format("%d;",m_two.msize);
	file.Write(temp,temp.GetLength());

	temp=m_one.whereStr+";";
	file.Write(temp,temp.GetLength());

	temp=m_one.autoStr+";";
	file.Write(temp,temp.GetLength());

	if(m_one.m_radio)
	{
		a=1;
		temp.Format("%d",a);
		file.Write(temp,temp.GetLength());
	}
	else
	{
		a=0;
		temp.Format("%d",a);
		file.Write(temp,temp.GetLength());
	}
	

	file.Close();

	return CDialogEx::DestroyWindow();
}

void CMouseTrainDlg::OnTraymenuClose()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	trayflag=false;
	CDialogEx::DestroyWindow();
}


void CMouseTrainDlg::OnTraymenuOpen()
{
	SetRestoreDialog();
}

//트레이로 만드는 함수
void CMouseTrainDlg::SetMinimizeToTray()
{
    NOTIFYICONDATA  nId; //트레이 아이콘 구조체 생성
 
    ShowWindow(SW_SHOWMINIMIZED);
    PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);
 
	//초기화

    nId.cbSize = sizeof(NOTIFYICONDATA);						
    nId.hWnd = this->m_hWnd;										
    nId.uID = 0;												
    Shell_NotifyIcon(NIM_DELETE, &nId);							//제거(초기화)
 
    nId.cbSize = sizeof(NOTIFYICONDATA);						//구조체 크기
    nId.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);			//아이콘 설정
    nId.hWnd = this->m_hWnd;										//윈도우 핸들
    CString str;
    GetWindowText(str);
    _tcscpy_s(nId.szTip, str.GetBuffer(str.GetLength()+1));
    str.ReleaseBuffer();
 
    nId.uID = 0;												//아이콘 식별자
    nId.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;				//콜백 메시지 사용
    nId.uCallbackMessage = TRAY_NOTIFY;							//아이콘이 hWnd윈도우와 통신하기 위해 사용할 메시지ID
    Shell_NotifyIcon(NIM_ADD, &nId);							//추가
}
 
// 윈도우 다이얼로그 복원 함수
void CMouseTrainDlg::SetRestoreDialog()
{
    NOTIFYICONDATA nId;
    nId.cbSize = sizeof(NOTIFYICONDATA);
    nId.hWnd = this->m_hWnd;
    nId.uID = 0;
    Shell_NotifyIcon(NIM_DELETE, &nId);							//제거
 
    ShowWindow(SW_RESTORE);										//다이얼로그 되살리기
    SetForegroundWindow();
}

LRESULT CMouseTrainDlg::OnTrayIconClick(WPARAM wParam, LPARAM lParam)
{
    switch(lParam)
    {
    case WM_LBUTTONDBLCLK:      // 왼쪽 버튼 더블 클릭의 경우 다이얼로그 복원
        {
            SetRestoreDialog();
            break;
        }
    case WM_RBUTTONDOWN:        // 오른쪽 버튼 클릭의 경우 메뉴 호출
        {
            CPoint ptMouse;
            ::GetCursorPos(&ptMouse);
 
            CMenu Menu;
            Menu.LoadMenu(IDR_TRAY_MENU);
            CMenu* pMenu = Menu.GetSubMenu(0);
            pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptMouse.x, ptMouse.y, AfxGetMainWnd()); //마우스 위치에서 메뉴 띄움
                         
            break;
        }
    }
 
    return 0;
}

void CMouseTrainDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(trayflag)
		SetMinimizeToTray();
	else
		CDialogEx::OnClose();
}
