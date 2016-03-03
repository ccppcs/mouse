
// MouseTrainDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "TabOne.h"
#include "TabTwo.h"

// CMouseTrainDlg 대화 상자
class CMouseTrainDlg : public CDialogEx
{
// 생성입니다.
public:
	CMouseTrainDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	/*
	bool moveStateFlag;
	bool pointStatusFlag;
	CPoint mpoint;
	*/
	TabOne m_one;
	TabTwo m_two;
	CWnd* m_pwndShow;


	bool pointStatusFlag; //좌표상태
	//bool hideSetFlag;		//숨김설정
	//bool acSelect,wcSelect,bcSelect;  //화살,대기,버튼 커서 선택
	bool autoClickFlag;				//자동클릭 상태
	bool moveStateFlag;				//커서저장 기능 썼나 안썼나
	bool autoClickCheck;			//자동클릭 확인

	int autonum;	//자동클릭 설정 횟수

	//핫키
	int m_HotKey;
	int m_HotKey2;

	int msize;

	//커서
	HCURSOR hoc,arrow,o_arrow,wait,o_wait,button,o_button,ctemp;

	
	
	
	CPoint mpoint; //마우스 좌표설정

	//불러오기 관련
	CString cname;
	CString namearry[10];
	char* cpath;

	//트레이 아이콘
	BOOL trayflag;
	void SetMinimizeToTray();
    void SetRestoreDialog();
    LRESULT OnTrayIconClick(WPARAM wParam, LPARAM lParam);



// 대화 상자 데이터입니다.
	enum { IDD = IDD_MOUSETRAIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
