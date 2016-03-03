
#pragma once
#include "TabTwo.h"

// TabOne 대화 상자입니다.	

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
	int hideCount;  //마우스 숨김 체크 카운트변수
	int hideTime;   //마우스 숨김 설정 시간

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
	int autonum;	//자동클릭 설정 횟수

	//콤보박스
	int select1;
	int select2;

	bool radioCheck;


	CString whereStr,autoStr;

	HCURSOR hc,hoc,hoi,hob,hc2,hc3,temp1,temp2,temp3,ahc;

	TabOne(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TabOne();




// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
