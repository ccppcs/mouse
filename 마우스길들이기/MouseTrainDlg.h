
// MouseTrainDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "TabOne.h"
#include "TabTwo.h"

// CMouseTrainDlg ��ȭ ����
class CMouseTrainDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMouseTrainDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	/*
	bool moveStateFlag;
	bool pointStatusFlag;
	CPoint mpoint;
	*/
	TabOne m_one;
	TabTwo m_two;
	CWnd* m_pwndShow;


	bool pointStatusFlag; //��ǥ����
	//bool hideSetFlag;		//���輳��
	//bool acSelect,wcSelect,bcSelect;  //ȭ��,���,��ư Ŀ�� ����
	bool autoClickFlag;				//�ڵ�Ŭ�� ����
	bool moveStateFlag;				//Ŀ������ ��� �質 �Ƚ質
	bool autoClickCheck;			//�ڵ�Ŭ�� Ȯ��

	int autonum;	//�ڵ�Ŭ�� ���� Ƚ��

	//��Ű
	int m_HotKey;
	int m_HotKey2;

	int msize;

	//Ŀ��
	HCURSOR hoc,arrow,o_arrow,wait,o_wait,button,o_button,ctemp;

	
	
	
	CPoint mpoint; //���콺 ��ǥ����

	//�ҷ����� ����
	CString cname;
	CString namearry[10];
	char* cpath;

	//Ʈ���� ������
	BOOL trayflag;
	void SetMinimizeToTray();
    void SetRestoreDialog();
    LRESULT OnTrayIconClick(WPARAM wParam, LPARAM lParam);



// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MOUSETRAIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);


	LRESULT OnHotKey(WPARAM wp, LPARAM);


	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTraymenuOpen();
	afx_msg void OnTraymenuClose();

	virtual BOOL DestroyWindow();
	afx_msg void OnClose();
};
