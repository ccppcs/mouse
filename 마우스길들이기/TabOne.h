
#pragma once
#include "TabTwo.h"

// TabOne ��ȭ �����Դϴ�.	

class TabOne : public CDialog
{
	DECLARE_DYNAMIC(TabOne)

public:

	bool moveStateFlag;
	bool pointStatusFlag;
	bool autoClickCheck;
	bool hideSetFlag;
	bool autoClickFlag;

	int autoClickSecond;
	int hideCount;  //���콺 ���� üũ ī��Ʈ����
	int hideTime;   //���콺 ���� ���� �ð�

	char* cpath;
	char* wpath;
	char* bpath;

	CPoint mpoint;
	CPoint HideFirstPoint;
	CPoint HideSecondPoint;
	CComboBox* pCombo;
	CComboBox* pCombo2;


	int m_HotKey;
	int m_HotKey2;
	int autonum;	//�ڵ�Ŭ�� ���� Ƚ��

	//�޺��ڽ�
	int select1;
	int select2;

	bool radioCheck;


	CString whereStr,autoStr;

	HCURSOR hc,hoc,hoi,hob,hc2,hc3,temp1,temp2,temp3,ahc;

	TabOne(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TabOne();




// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void PointSelect();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void AutoClickSet();
	afx_msg void AutoClickFree();
	long m_edit1;
	virtual BOOL OnInitDialog();
	afx_msg void HideSecondSet();
	afx_msg void HideSecondFree();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_edit2;
	virtual BOOL DestroyWindow();
	afx_msg void SelectKey();

	LRESULT OnHotKey(WPARAM wp, LPARAM);
	afx_msg void Keyselect2();
	int m_radio;
	afx_msg void OnBnClickedRadio(UINT msg);
	void ComboSetting(void);
	afx_msg void OnBnClickedButton6();
};
