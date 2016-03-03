
// MouseTrainDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MouseTrain.h"
#include "MouseTrainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TRAY_NOTIFY          (WM_APP + 100) //Ʈ����
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


// CMouseTrainDlg ��ȭ ����




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
	ON_MESSAGE(WM_HOTKEY, OnHotKey)//��Ű
	//Ʈ����
	ON_MESSAGE(TRAY_NOTIFY, OnTrayIconClick)
    ON_COMMAND(ID_TRAYMENU_OPEN, &CMouseTrainDlg::OnTraymenuOpen)
	ON_COMMAND(ID_TRAYMENU_CLOSE, &CMouseTrainDlg::OnTraymenuClose)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMouseTrainDlg �޽��� ó����

BOOL CMouseTrainDlg::OnInitDialog()
{
	HANDLE hEvent;
	hEvent = CreateEvent(NULL, FALSE, TRUE, AfxGetAppName()); 
	if ( GetLastError() == ERROR_ALREADY_EXISTS) { 
	AfxMessageBox("�������α׷�����");
	exit(0) ;
	}
	
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	//��Ű ���
	/*
	m_HotKey = ::GlobalAddAtom("F3");
	RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F3);
	
	m_HotKey2 = ::GlobalAddAtom("F6");
	RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F6);
	*/



	//����Ʈ�� ����
	m_Tab.InsertItem(0, _T("���콺 ��ǥ"));
	m_Tab.InsertItem(1, _T("���콺 Ŀ��"));
	CRect rect;
	m_Tab.GetClientRect(&rect);
	m_one.Create(IDD_DIALOG1,&m_Tab);
	m_one.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_one;

	m_two.Create(IDD_DIALOG2,&m_Tab);
	m_two.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_NOZORDER);

	//�ʱ�ȭ
	autoClickFlag=true;
	moveStateFlag=false;
	msize=0;

	/////////�ҷ�����

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
	


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMouseTrainDlg::OnPaint()
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
			SetCursorPos(m_one.mpoint.x,m_one.mpoint.y);//����� ��Ű �Է½� ������ �۾� �Է��Ѵ�.	
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
					AfxMessageBox(_T("Ƚ���� �Է��ϼ���."));
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

	//����

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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	trayflag=false;
	CDialogEx::DestroyWindow();
}


void CMouseTrainDlg::OnTraymenuOpen()
{
	SetRestoreDialog();
}

//Ʈ���̷� ����� �Լ�
void CMouseTrainDlg::SetMinimizeToTray()
{
    NOTIFYICONDATA  nId; //Ʈ���� ������ ����ü ����
 
    ShowWindow(SW_SHOWMINIMIZED);
    PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);
 
	//�ʱ�ȭ

    nId.cbSize = sizeof(NOTIFYICONDATA);						
    nId.hWnd = this->m_hWnd;										
    nId.uID = 0;												
    Shell_NotifyIcon(NIM_DELETE, &nId);							//����(�ʱ�ȭ)
 
    nId.cbSize = sizeof(NOTIFYICONDATA);						//����ü ũ��
    nId.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);			//������ ����
    nId.hWnd = this->m_hWnd;										//������ �ڵ�
    CString str;
    GetWindowText(str);
    _tcscpy_s(nId.szTip, str.GetBuffer(str.GetLength()+1));
    str.ReleaseBuffer();
 
    nId.uID = 0;												//������ �ĺ���
    nId.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;				//�ݹ� �޽��� ���
    nId.uCallbackMessage = TRAY_NOTIFY;							//�������� hWnd������� ����ϱ� ���� ����� �޽���ID
    Shell_NotifyIcon(NIM_ADD, &nId);							//�߰�
}
 
// ������ ���̾�α� ���� �Լ�
void CMouseTrainDlg::SetRestoreDialog()
{
    NOTIFYICONDATA nId;
    nId.cbSize = sizeof(NOTIFYICONDATA);
    nId.hWnd = this->m_hWnd;
    nId.uID = 0;
    Shell_NotifyIcon(NIM_DELETE, &nId);							//����
 
    ShowWindow(SW_RESTORE);										//���̾�α� �ǻ츮��
    SetForegroundWindow();
}

LRESULT CMouseTrainDlg::OnTrayIconClick(WPARAM wParam, LPARAM lParam)
{
    switch(lParam)
    {
    case WM_LBUTTONDBLCLK:      // ���� ��ư ���� Ŭ���� ��� ���̾�α� ����
        {
            SetRestoreDialog();
            break;
        }
    case WM_RBUTTONDOWN:        // ������ ��ư Ŭ���� ��� �޴� ȣ��
        {
            CPoint ptMouse;
            ::GetCursorPos(&ptMouse);
 
            CMenu Menu;
            Menu.LoadMenu(IDR_TRAY_MENU);
            CMenu* pMenu = Menu.GetSubMenu(0);
            pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptMouse.x, ptMouse.y, AfxGetMainWnd()); //���콺 ��ġ���� �޴� ���
                         
            break;
        }
    }
 
    return 0;
}

void CMouseTrainDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if(trayflag)
		SetMinimizeToTray();
	else
		CDialogEx::OnClose();
}
