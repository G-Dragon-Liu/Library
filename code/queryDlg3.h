#pragma once


// queryDlg3 对话框

class queryDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(queryDlg3)

public:
	queryDlg3(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~queryDlg3();
	CString cardid_text;
	CString cardname_text;
	CString affiliation_text;
	CString cardtype_text;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Query3_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnKillfocuscardid();
	afx_msg void OnEnKillfocuscardname();
	afx_msg void OnCbnKillfocusAffiliation();
	CComboBox cmbbox1;
	CComboBox cmbbox2;
	afx_msg void OnCbnKillfocuscardtype();
};
