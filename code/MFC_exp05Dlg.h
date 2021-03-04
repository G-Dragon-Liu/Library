
// MFC_exp05Dlg.h: 头文件
//

#pragma once
#include<mysql.h>
#include"queryDlg1.h"
#include"queryDlg2.h"
#include"queryDlg3.h"
#include"queryDlg4.h"

// CMFCexp05Dlg 对话框
class CMFCexp05Dlg : public CDialogEx
{
// 构造
public:
	CMFCexp05Dlg(CWnd* pParent = nullptr);	// 标准构造函数
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_EXP05_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedquery();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedlogin();
	
	afx_msg void OnBnClickedlogincancel();
	afx_msg void OnBnClickedlogout();
	afx_msg void OnLvnItemchangedlistctrl(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl list1;
	MYSQL m_sql1;

	CListCtrl list2;
	afx_msg void OnBnClickedborrow();
	afx_msg void OnBnClickedreturn();
	afx_msg void OnBnClickedin();
	afx_msg void OnBnClickedmanage();

	queryDlg1  m_queryDlg1;
	queryDlg2  m_queryDlg2;
	queryDlg3  m_queryDlg3;
	queryDlg4  m_queryDlg4;

	CTabCtrl m_tab;
	afx_msg void OnBnClickedbookquery1();
	afx_msg void OnBnClickedbookcancel1();
	afx_msg void OnBnClickedbookquery2();
	afx_msg void OnBnClickedbookcancel2();
	afx_msg void OnBnClickedcardadd3();
	afx_msg void OnBnClickedcardcancel3();
	afx_msg void OnBnClickedborrowrecord();
	CListCtrl list3;
	afx_msg void OnBnClickedborrowout();
	afx_msg void OnBnClickedbookback();
};
