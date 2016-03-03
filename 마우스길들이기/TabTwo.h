#pragma once
#include "afxwin.h"

// TabTwo ��ȭ �����Դϴ�.


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
	//�����
	CString acname;
	CString wcname;
	CString bcname;

	bool acSelect,wcSelect,bcSelect;  //ȭ��,���,��ư Ŀ�� ����
	bool acChangeFlag,wcChangeFlag,bcChangeFlag;   //���콺 Ŀ���� ����Ǿ����� Ȯ��


	HCURSOR hc,hoc,arrow,o_arrow,wait,o_wait,button,o_button,temp;

	
	//��ȯ��
	char* cpath;
	char* acpath;

	TabTwo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TabTwo();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
