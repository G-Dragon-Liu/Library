#pragma once


// queryDlg2 对话框

class queryDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(queryDlg2)

public:
	queryDlg2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~queryDlg2();
	CString bookname2_text;
	CString booktype2_text;
	CString bookpublisher2_text;
	CString bookauthor2_text;
	CString priceto2_text;
	CString pricefrom2_text;
	CString yearfrom2_text;
	CString yearto2_text;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Query2_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnKillfocusbookname11();
	afx_msg void OnEnKillfocusbooktype11();
	afx_msg void OnEnKillfocusbookauthor11();
	afx_msg void OnEnKillfocusbookpublisher11();
	afx_msg void OnCbnKillfocuspricefrom();
	CComboBox cmbprice1;
	CComboBox cmbprice2;
	afx_msg void OnCbnKillfocuspriceto();
	CComboBox cmbyear1;
	afx_msg void OnCbnKillfocusyearfrom();
	afx_msg void OnCbnSelchangeyearto();
	afx_msg void OnCbnKillfocusyearto();
	CComboBox cmbyear2;
	CEdit booknamev;
	afx_msg void OnEnChangebookname11();
	CEdit booktypev;
	CEdit bookauthorv;
	CEdit bookpublisherv;
};
