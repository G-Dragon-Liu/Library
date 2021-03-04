#pragma once


// queryDlg1 对话框

class queryDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(queryDlg1)

public:
	queryDlg1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~queryDlg1();
	/*以下几个用来接收几个editbox 的内容 editbox 应该有相关的响应函数*/
	CString bookid1_text;
	CString booktype1_text;
	CString bookname1_text;
	CString bookpublisher1_text;
	CString bookyear1_text;
	CString bookauthor1_text;
	CString	bookprice1_text;
	CString booknum1_text;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Query1_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbookquery1();
	
	afx_msg void OnEnKillfocusbookname11();
	afx_msg void OnEnKillfocusbookid11();
	afx_msg void OnEnKillfocusbooktype11();
	afx_msg void OnEnKillfocusbookpublisher11();

	afx_msg void OnEnKillfocusbookauthor11();
	afx_msg void OnEnKillfocusbookprice11();
	afx_msg void OnEnKillfocusbooknum11();
	afx_msg void OnCbnKillfocusbookyear11();
	CComboBox cmbbox1;
};
