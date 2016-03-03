#pragma once
#include "afxwin.h"

// TabTwo 대화 상자입니다.


class TabTwo : public CDialog
{
	DECLARE_DYNAMIC(TabTwo)


public:
	int msize;

	static char* dpath;
	static char* epath;
	static char* fpath;

	HBITMAP hbit;

	CString Filedir;
	CString Filter;
	//저장용
	CString acname;
	CString wcname;
	CString bcname;

	bool acSelect,wcSelect,bcSelect;  //화살,대기,버튼 커서 선택
	bool acChangeFlag,wcChangeFlag,bcChangeFlag;   //마우스 커서가 변경되었는지 확인


	HCURSOR hc,hoc,arrow,o_arrow,wait,o_wait,button,o_button,temp;

	
	//변환용
	char* cpath;
	char* acpath;

	TabTwo(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TabTwo();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_Pic1;
	CStatic m_Pic2;
	CStatic m_Pic3;
	afx_msg void ArrowCurserChange();
	afx_msg void WaitCurserChange();
	afx_msg void ButtonCurserChange();
	afx_msg void ArrowCurserFree();
	afx_msg void WaitCurserFree();
	afx_msg void ButtonCurserFree();
	virtual BOOL DestroyWindow();
	afx_msg void ButtonSizeDown();
	afx_msg void ButtonSizeUp();
	afx_msg void ResetButtonSize();
	void changecurser(void);
};
