// queryDlg1.cpp: 实现文件
//

#include "pch.h"
#include "MFC_exp05.h"
#include "queryDlg1.h"
#include "afxdialogex.h"


// queryDlg1 对话框

IMPLEMENT_DYNAMIC(queryDlg1, CDialogEx)

queryDlg1::queryDlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Query1_DIALOG1, pParent)
{

}

queryDlg1::~queryDlg1()
{
}

void queryDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, bookyear11, cmbbox1);
}


BEGIN_MESSAGE_MAP(queryDlg1, CDialogEx)
	ON_BN_CLICKED(bookquery1, &queryDlg1::OnBnClickedbookquery1)
	ON_EN_KILLFOCUS(bookname11, &queryDlg1::OnEnKillfocusbookname11)
	ON_EN_KILLFOCUS(bookid11, &queryDlg1::OnEnKillfocusbookid11)
	ON_EN_KILLFOCUS(booktype11, &queryDlg1::OnEnKillfocusbooktype11)
	ON_EN_KILLFOCUS(bookpublisher11, &queryDlg1::OnEnKillfocusbookpublisher11)
	
	ON_EN_KILLFOCUS(bookauthor11, &queryDlg1::OnEnKillfocusbookauthor11)
	ON_EN_KILLFOCUS(bookprice11, &queryDlg1::OnEnKillfocusbookprice11)
	ON_EN_KILLFOCUS(booknum11, &queryDlg1::OnEnKillfocusbooknum11)
	ON_CBN_KILLFOCUS(bookyear11, &queryDlg1::OnCbnKillfocusbookyear11)
END_MESSAGE_MAP()


// queryDlg1 消息处理程序


void queryDlg1::OnBnClickedbookquery1()
{
	
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg1::OnEnKillfocusbookname11()
{
	GetDlgItemText(bookname11, bookname1_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg1::OnEnKillfocusbookid11()
{
	GetDlgItemText(bookid11, bookid1_text);
	//MessageBox(bookid_text, TEXT("!"), 1);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg1::OnEnKillfocusbooktype11()
{
	GetDlgItemText(booktype11, booktype1_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg1::OnEnKillfocusbookpublisher11()
{
	GetDlgItemText(bookpublisher11, bookpublisher1_text);
	// TODO: 在此添加控件通知处理程序代码
}

void queryDlg1::OnEnKillfocusbookauthor11()
{
	GetDlgItemText(bookauthor11, bookauthor1_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg1::OnEnKillfocusbookprice11()
{
	GetDlgItemText(bookprice11, bookprice1_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg1::OnEnKillfocusbooknum11()
{
	GetDlgItemText(booknum11, booknum1_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg1::OnCbnKillfocusbookyear11()
{
	GetDlgItemText(bookyear11, bookyear1_text);
	int F_index = cmbbox1.FindStringExact(0, bookyear1_text);
	if(F_index!=CB_ERR) cmbbox1.AddString(bookyear1_text);
	// TODO: 在此添加控件通知处理程序代码
}
