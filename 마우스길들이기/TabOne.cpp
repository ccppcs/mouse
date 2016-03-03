// TabOne.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MouseTrain.h"
#include "TabOne.h"
#include "afxdialogex.h"
#include "time.h"
#include "TabTwo.h"



// TabOne 대화 상자입니다.

IMPLEMENT_DYNAMIC(TabOne, CDialog)

TabOne::TabOne(CWnd* pParent /*=NULL*/)
	: CDialog(TabOne::IDD, pParent)
	, m_edit1(0)
	, m_edit2(0)
	//, m_radio(1)
{

}

TabOne::~TabOne()
{
}

void TabOne::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
}


BEGIN_MESSAGE_MAP(TabOne, CDialog)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)//핫키
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO2, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_BUTTON1, &TabOne::PointSelect)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON2, &TabOne::AutoClickSet)
	ON_BN_CLICKED(IDC_BUTTON3, &TabOne::AutoClickFree)
	ON_BN_CLICKED(IDC_BUTTON4, &TabOne::HideSecondSet)
	ON_BN_CLICKED(IDC_BUTTON5, &TabOne::HideSecondFree)
	ON_WM_TIMER()
	ON_CBN_SELENDOK(IDC_COMBO1, &TabOne::SelectKey)
	ON_CBN_SELENDOK(IDC_COMBO2, &TabOne::Keyselect2)
	ON_BN_CLICKED(IDC_BUTTON6, &TabOne::OnBnClickedButton6)
END_MESSAGE_MAP()


// TabOne 메시지 처리기입니다.


void TabOne::PointSelect() // 좌표정하기
{
	moveStateFlag=true;
	pointStatusFlag=true;
	SetCapture();
}


void TabOne::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(pointStatusFlag)
	{
		ReleaseCapture();
		GetCursorPos(&mpoint);
		AfxMessageBox(_T("좌표가 저장되었습니다."));
		pointStatusFlag=false;
	}
	CDialog::OnLButtonDown(nFlags, point);
}


void TabOne::AutoClickSet()
{
	autoClickCheck=true;
	autoClickSecond=GetDlgItemInt(IDC_EDIT1); 
	if(autoClickSecond<1)
	{
		AfxMessageBox(_T("1이상 해주세요!"));
		return;
	}
}


void TabOne::AutoClickFree()
{
	if(autoClickFlag==false)
	{
		AfxMessageBox(_T("오토클릭 기능을 끄세요!!"));
		return;
	}
	else
		autoClickCheck=false;
}


BOOL TabOne::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	moveStateFlag=false;
	pointStatusFlag=false;
	hideCount=0;
	
	autoClickCheck=false;


	

	
	
	


	
	select1=1123;
	select2=2233;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TabOne::HideSecondSet()
{
	if((hideTime=GetDlgItemInt(IDC_EDIT2))==0 || (hideTime=GetDlgItemInt(IDC_EDIT2))==NULL)
	{
		AfxMessageBox(_T("시간을 입력하세요."));
		return;
	}
	else if((hideTime=GetDlgItemInt(IDC_EDIT2))<3 )
	{
		AfxMessageBox(_T("3초이상 해주세요!"));
		return;
	}
	SetTimer(0,100,NULL);
	hideTime=GetDlgItemInt(IDC_EDIT2);
}


void TabOne::HideSecondFree()
{
	if(hideSetFlag)
		KillTimer(0);
	else
		return;

}


void TabOne::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case 0 :
		GetCursorPos(&HideFirstPoint);
		if(HideFirstPoint==HideSecondPoint)
		{
			hideCount++;

		}
		else
		{
			HideSecondPoint=HideFirstPoint;
			hideCount=0;
			hoc = (HCURSOR)LoadImage(AfxGetInstanceHandle(),cpath,IMAGE_CURSOR,32,32,LR_LOADFROMFILE); //화살
			hoi = LoadCursorFromFile(".\\res\\image\\beam_r.cur");  //I빔
			hob = (HCURSOR)LoadImage(AfxGetInstanceHandle(),bpath,IMAGE_CURSOR,32,32,LR_LOADFROMFILE);  //버튼
			::SetSystemCursor(hoc,32512);	
			::SetSystemCursor(hoi,32513);
			::SetSystemCursor(hob,32649);
			::DestroyCursor(hc);
			::DestroyCursor(hc2);
			::DestroyCursor(hc3);
			hideSetFlag=true;			
		}

		if(hideCount==(hideTime-1)*10)
		{
			/*
			hoc = LoadCursor(NULL,IDC_ARROW); //화살
			hoc = CopyCursor(hoc);
			hoi = LoadCursor(NULL,IDC_IBEAM);  //I빔
			hoi = CopyCursor(hoi);
			hob = LoadCursor(NULL,IDC_HAND);  //버튼
			hob = CopyCursor(hob);	
			*/
			hc = LoadCursorFromFile(".\\res\\image\\hide.cur");
			hc = CopyCursor(hc);		
			hc2 = LoadCursorFromFile(".\\res\\image\\hide.cur");
			hc2 = CopyCursor(hc);
			hc3 = LoadCursorFromFile(".\\res\\image\\hide.cur");
			hc3 = CopyCursor(hc);
			
			::SetSystemCursor(hc,32512);
			::SetSystemCursor(hc2,32513);
			::SetSystemCursor(hc3,32649);
			hideSetFlag=false;
			
		}
		break;
	case 1 :
		mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
		mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
		break;
	case 2 :
		hc = (HCURSOR)LoadImage(AfxGetInstanceHandle(),".\\res\\image\\here.ani",IMAGE_CURSOR,480,480,LR_LOADFROMFILE);
		hc2 = (HCURSOR)LoadImage(AfxGetInstanceHandle(),".\\res\\image\\here.ani",IMAGE_CURSOR,480,480,LR_LOADFROMFILE);
		hc3 = (HCURSOR)LoadImage(AfxGetInstanceHandle(),".\\res\\image\\here.ani",IMAGE_CURSOR,480,480,LR_LOADFROMFILE);
		::SetSystemCursor(hc,32512);
		::SetSystemCursor(hc2,32513);
		::SetSystemCursor(hc3,32649);
		Sleep(1700);
		cpath=TabTwo::dpath;
		hoc = (HCURSOR)LoadImage(AfxGetInstanceHandle(),cpath,IMAGE_CURSOR,32,32,LR_LOADFROMFILE);
		hoi = LoadCursorFromFile(".\\res\\image\\beam_r.cur");
		hob = (HCURSOR)LoadImage(AfxGetInstanceHandle(),bpath,IMAGE_CURSOR,32,32,LR_LOADFROMFILE);
		::SetSystemCursor(hoc,32512);
		::SetSystemCursor(hoi,32513);
		::SetSystemCursor(hob,32649);
		KillTimer(2);
		break;
	}

	CDialog::OnTimer(nIDEvent);
}


BOOL TabOne::DestroyWindow()
{
	::DestroyCursor(hoc); ::DestroyCursor(hc);	::DestroyCursor(hoi); ::DestroyCursor(hob);
	::DestroyCursor(hc2); ::DestroyCursor(hc3);
	return CDialog::DestroyWindow();
}


void TabOne::SelectKey()
{
	select1 = pCombo->GetCurSel();
	if(select1==select2)
	{
		AfxMessageBox("자동클릭 단축키와 동일합니다.\n 다른 키를 선택 해 주세요.");
		return;
	}
	CString str;
	pCombo->GetLBText(select1, str);
	m_HotKey = ::GlobalAddAtom(str);
	switch(select1)
	{
	case 0 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F1);
		whereStr="F1";
		break;
	case 1 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F2);
		whereStr="F2";
		break;
	case 2 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F3);
		whereStr="F3";
		break;
	case 3 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F4);
		whereStr="F4";
		break;
	case 4 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F5);
		whereStr="F5";
		break;
	case 5 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F6);
		whereStr="F6";
		break;
	case 6 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F7);
		whereStr="F7";
		break;
	case 7 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F8);
		whereStr="F8";
		break;
	case 8 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F9);
		whereStr="F9";
		break;
	case 9 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F10);
		whereStr="F10";
		break;
	case 10 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F11);
		whereStr="F11";
		break;
	case 11 :
		UnregisterHotKey(m_hWnd, m_HotKey);
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F12);
		whereStr="F12";
		break;
	}
}


LRESULT TabOne::OnHotKey(WPARAM wp, LPARAM)
{
	if((int)wp == m_HotKey)
	{
		if(m_radio)
		{
			if(moveStateFlag)
			{
				SetCursorPos(mpoint.x,mpoint.y);//등록한 핫키 입력시 수행할 작업 입력한다.	
				ReleaseCapture();
			}
		}
		else
		{
			SetTimer(2,10,NULL);
		}
	}
	
	if((int)wp == m_HotKey2)
	{
		if(autoClickCheck)
		{
			if(autoClickFlag)
			{
				int temp=autoClickSecond;
				if(temp==0)
				{
					AfxMessageBox(_T("횟수를 입력하세요."));
				}
				else
				{
					autonum=temp;
					SetTimer(1,1000/autonum,NULL);
					autoClickFlag=false;
				}
			}
			else
			{
				KillTimer(1);
				autoClickFlag=true;
			}
		}
		else
		{
			return 0;
		}
	}

	return 0; // ignore
	
}

void TabOne::Keyselect2()
{
	select2 = pCombo2->GetCurSel();
	if(select1==select2)
	{
		AfxMessageBox("위치지정 단축키와 동일합니다.\n 다른 키를 선택 해 주세요.");
		return;
	}
	CString str;
	pCombo2->GetLBText(select2, str);
	m_HotKey2 = ::GlobalAddAtom(str);
	switch(select2)
	{
	case 0 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F1);
		autoStr="F1";
		break;
	case 1 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F2);
		autoStr="F2";
		break;
	case 2 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F3);
		autoStr="F3";
		break;
	case 3 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F4);
		autoStr="F4";
		break;
	case 4 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F5);
		autoStr="F5";
		break;
	case 5 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F6);
		autoStr="F6";
		break;
	case 6 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F7);
		autoStr="F7";
		break;
	case 7 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F8);
		autoStr="F8";
		break;
	case 8 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F9);
		autoStr="F9";
		break;
	case 9 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F10);
		autoStr="F10";
		break;
	case 10 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F11);
		autoStr="F11";
		break;
	case 11 :
		UnregisterHotKey(m_hWnd, m_HotKey2);
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F12);
		autoStr="F12";
		break;
	}
}

void TabOne::OnBnClickedRadio(UINT msg)
{
 UpdateData(TRUE);
}

void TabOne::ComboSetting(void)
{
	if(whereStr=="F1")
	{
		m_HotKey = ::GlobalAddAtom("F1");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F1);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(0);
	}
	else if(whereStr=="F2")
	{
		m_HotKey = ::GlobalAddAtom("F2");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F2);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(1);
	}
	else if(whereStr=="F3")
	{
		m_HotKey = ::GlobalAddAtom("F3");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F3);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(2);
	}
	else if(whereStr=="F4")
	{
		m_HotKey = ::GlobalAddAtom("F4");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F4);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(3);
	}
	else if(whereStr=="F5")
	{
		m_HotKey = ::GlobalAddAtom("F5");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F5);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(4);
	}
	else if(whereStr=="F6")
	{
		m_HotKey = ::GlobalAddAtom("F6");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F6);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(5);
	}
	else if(whereStr=="F7")
	{
		m_HotKey = ::GlobalAddAtom("F7");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F7);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(6);
	}
	else if(whereStr=="F8")
	{
		m_HotKey = ::GlobalAddAtom("F8");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F8);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(7);
	}
	else if(whereStr=="F9")
	{
		m_HotKey = ::GlobalAddAtom("F9");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F9);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(8);
	}
	else if(whereStr=="F10")
	{
		m_HotKey = ::GlobalAddAtom("F10");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F10);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(9);
	}
	else if(whereStr=="F11")
	{
		m_HotKey = ::GlobalAddAtom("F11");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F11);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(10);
	}
	else if(whereStr=="F12")
	{
		m_HotKey = ::GlobalAddAtom("F12");
		RegisterHotKey(m_hWnd, m_HotKey, 0, VK_F12);
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(11);
	}
	else
	{
		pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(2);
	}
	
	

	if(autoStr=="F1")
	{
		m_HotKey2 = ::GlobalAddAtom("F1");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F1);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(0);
	}
	else if(autoStr=="F2")
	{
		m_HotKey2 = ::GlobalAddAtom("F2");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F2);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(1);
	}
	else if(autoStr=="F3")
	{
		m_HotKey2 = ::GlobalAddAtom("F3");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F3);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(2);
	}
	else if(autoStr=="F4")
	{
		m_HotKey2 = ::GlobalAddAtom("F4");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F4);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(3);
	}
	else if(autoStr=="F5")
	{
		m_HotKey2 = ::GlobalAddAtom("F5");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F5);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(4);
	}
	else if(autoStr=="F6")
	{
		m_HotKey2 = ::GlobalAddAtom("F6");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F6);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(5);
	}
	else if(autoStr=="F7")
	{
		m_HotKey2 = ::GlobalAddAtom("F7");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F7);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(6);
	}
	else if(autoStr=="F8")
	{
		m_HotKey2 = ::GlobalAddAtom("F8");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F8);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(7);
	}
	else if(autoStr=="F9")
	{
		m_HotKey2 = ::GlobalAddAtom("F9");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F9);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(8);
	}
	else if(autoStr=="F10")
	{
		m_HotKey2 = ::GlobalAddAtom("F10");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F10);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(9);
	}
	else if(autoStr=="F11")
	{
		m_HotKey2 = ::GlobalAddAtom("F11");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F11);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(10);
	}
	else if(autoStr=="F12")
	{
		m_HotKey2 = ::GlobalAddAtom("F12");
		RegisterHotKey(m_hWnd, m_HotKey2, 0, VK_F12);
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(11);
	}
	else
	{
		pCombo2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
		pCombo2->SetCurSel(5);
	}

	if(m_radio)
	{
		
		CButton *pCheck;
		pCheck=(CButton *)GetDlgItem(IDC_RADIO2);
		pCheck->SetCheck(TRUE);
	}
	else
	{
		CButton *pCheck;
		pCheck=(CButton *)GetDlgItem(IDC_RADIO1);
		pCheck->SetCheck(TRUE);
	}
}


void TabOne::OnBnClickedButton6()
{
	ShellExecute(NULL, "open", "readme1.txt", NULL, NULL, SW_SHOW);
}
