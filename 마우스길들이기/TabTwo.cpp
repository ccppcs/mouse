// TabTwo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MouseTrain.h"
#include "TabTwo.h"
#include "afxdialogex.h"

char* TabTwo::dpath;
char* TabTwo::epath;
char* TabTwo::fpath;

// TabTwo 대화 상자입니다.

IMPLEMENT_DYNAMIC(TabTwo, CDialog)

TabTwo::TabTwo(CWnd* pParent /*=NULL*/)
	: CDialog(TabTwo::IDD, pParent)
{

}

TabTwo::~TabTwo()
{
}

void TabTwo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC1, m_Pic1);
	DDX_Control(pDX, IDC_PIC2, m_Pic2);
	DDX_Control(pDX, IDC_PIC3, m_Pic3);
}


BEGIN_MESSAGE_MAP(TabTwo, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &TabTwo::ArrowCurserChange)
	ON_BN_CLICKED(IDC_BUTTON3, &TabTwo::WaitCurserChange)
	ON_BN_CLICKED(IDC_BUTTON5, &TabTwo::ButtonCurserChange)
	ON_BN_CLICKED(IDC_BUTTON2, &TabTwo::ArrowCurserFree)
	ON_BN_CLICKED(IDC_BUTTON4, &TabTwo::WaitCurserFree)
	ON_BN_CLICKED(IDC_BUTTON6, &TabTwo::ButtonCurserFree)
	ON_BN_CLICKED(IDC_BUTTON8, &TabTwo::ButtonSizeDown)
	ON_BN_CLICKED(IDC_BUTTON9, &TabTwo::ButtonSizeUp)
	ON_BN_CLICKED(IDC_BUTTON10, &TabTwo::ResetButtonSize)
END_MESSAGE_MAP()


// TabTwo 메시지 처리기입니다.


BOOL TabTwo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
	m_Pic1.SetBitmap(hbit) ;
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
	m_Pic2.SetBitmap(hbit) ;
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2));
	m_Pic3.SetBitmap(hbit) ;

	//초기화
	acSelect=true;
	wcSelect=true;
	bcSelect=true;
	acChangeFlag = false;
	wcChangeFlag = false;
	bcChangeFlag = false;

	msize = 0;

	Filter= _T("cur(*.cur)|*.cur|ani(*.ani)|*.ani||");

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TabTwo::ArrowCurserChange()
{
	CFileDialog file(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,Filter,this);
	int iReturn = file.DoModal();
	if(iReturn == IDOK)
	{
		Filedir = file.GetPathName();
		cpath = Filedir.GetBuffer(0);
		acpath=cpath;
		dpath=cpath;
		if(acSelect)
		{
			o_arrow = LoadCursor(NULL,IDC_ARROW);
			o_arrow = CopyCursor(o_arrow);
		}
		//arrow = LoadCursorFromFile(cpath);
		arrow = (HCURSOR)LoadImage(AfxGetInstanceHandle(),cpath,IMAGE_CURSOR,32,32,LR_LOADFROMFILE);
		::SetSystemCursor(arrow,32512);
		acname=Filedir+";";
		acname.Replace("\\","\\\\");
		acSelect=false;
		acChangeFlag=true;
	}
}


void TabTwo::WaitCurserChange()
{
	CFileDialog file(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,Filter,this);
	int iReturn = file.DoModal();
	if(iReturn == IDOK)
	{
		Filedir = file.GetPathName();
		cpath = Filedir.GetBuffer(0);
		epath=cpath;
		if(wcSelect)
		{
			o_wait = LoadCursor(NULL,IDC_APPSTARTING);
			o_wait = CopyCursor(o_wait);
		}
		wait = LoadCursorFromFile(cpath);
		::SetSystemCursor(wait,32650);
		wcname=Filedir+";";
		wcname.Replace("\\","\\\\");
		wcSelect=false;
		wcChangeFlag=true;
	}
}


void TabTwo::ButtonCurserChange()
{
	CFileDialog file(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,Filter,this);
	int iReturn = file.DoModal();
	if(iReturn == IDOK)
	{
		Filedir = file.GetPathName();
		cpath = Filedir.GetBuffer(0);
		fpath=cpath;
		if(bcSelect)
		{
			o_button = LoadCursor(NULL,IDC_HAND);
			o_button = CopyCursor(o_button);
		}
		button = LoadCursorFromFile(cpath);
		::SetSystemCursor(button,32649);
		bcname=Filedir+";";
		bcname.Replace("\\","\\\\");	
		bcSelect=false;
		bcChangeFlag=true;
	}
}


void TabTwo::ArrowCurserFree()
{
	o_arrow = LoadCursorFromFile(".\\res\\image\\arrow.cur");
	::SetSystemCursor(o_arrow,32512);
	acChangeFlag=false;
}


void TabTwo::WaitCurserFree()
{
	o_wait = LoadCursorFromFile(".\\res\\image\\aero_busy.ani");
	::SetSystemCursor(o_wait,62650);
	wcChangeFlag=false;
}


void TabTwo::ButtonCurserFree()
{
	o_button = LoadCursorFromFile(".\\res\\image\\button.cur");
	::SetSystemCursor(o_button,32649);
	bcChangeFlag=false;
}


BOOL TabTwo::DestroyWindow()
{
	return CDialog::DestroyWindow();
}


void TabTwo::ButtonSizeDown()
{
	msize-=5;
	if(acChangeFlag)
		arrow = (HCURSOR)LoadImage(AfxGetInstanceHandle(),acpath,IMAGE_CURSOR,32+msize,32+msize,LR_LOADFROMFILE);
	else
		arrow = (HCURSOR)LoadImage(AfxGetInstanceHandle(),".\\res\\image\\arrow.cur",IMAGE_CURSOR,32+msize,32+msize,LR_LOADFROMFILE);
	::SetSystemCursor(arrow,32512);
}


void TabTwo::ButtonSizeUp()
{
	msize+=5;
	if(acChangeFlag)
		arrow = (HCURSOR)LoadImage(AfxGetInstanceHandle(),acpath,IMAGE_CURSOR,32+msize,32+msize,LR_LOADFROMFILE);
	else
		arrow = (HCURSOR)LoadImage(AfxGetInstanceHandle(),".\\res\\image\\arrow.cur",IMAGE_CURSOR,32+msize,32+msize,LR_LOADFROMFILE);
	::SetSystemCursor(arrow,32512);
}


void TabTwo::ResetButtonSize()
{
	msize=0;
	if(acChangeFlag)
		arrow = (HCURSOR)LoadImage(AfxGetInstanceHandle(),acpath,IMAGE_CURSOR,32,32,LR_LOADFROMFILE);
	else
		arrow = (HCURSOR)LoadImage(AfxGetInstanceHandle(),".\\res\\image\\arrow.cur",IMAGE_CURSOR,32,32,LR_LOADFROMFILE);
	::SetSystemCursor(arrow,32512);
}


void TabTwo::changecurser(void)
{
	temp=(HCURSOR)LoadImage(AfxGetInstanceHandle(),acpath,IMAGE_CURSOR,32,32,LR_LOADFROMFILE);
		::SetSystemCursor(arrow,32512);
}
