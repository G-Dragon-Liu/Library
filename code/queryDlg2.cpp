// queryDlg2.cpp: 实现文件
//

#include "pch.h"
#include "MFC_exp05.h"
#include "queryDlg2.h"
#include "afxdialogex.h"


// queryDlg2 对话框

IMPLEMENT_DYNAMIC(queryDlg2, CDialogEx)

queryDlg2::queryDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Query2_DIALOG2, pParent)
{

}

queryDlg2::~queryDlg2()
{
}

void queryDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, pricefrom, cmbprice1);
	DDX_Control(pDX, priceto, cmbprice2);
	DDX_Control(pDX, yearfrom, cmbyear1);
	DDX_Control(pDX, yearto, cmbyear2);
	DDX_Control(pDX, bookname11, booknamev);
	DDX_Control(pDX, booktype11, booktypev);
	DDX_Control(pDX, bookauthor11, bookauthorv);
	DDX_Control(pDX, bookpublisher11, bookpublisherv);
}


BEGIN_MESSAGE_MAP(queryDlg2, CDialogEx)
	ON_EN_KILLFOCUS(bookname11, &queryDlg2::OnEnKillfocusbookname11)
	ON_EN_KILLFOCUS(booktype11, &queryDlg2::OnEnKillfocusbooktype11)
	ON_EN_KILLFOCUS(bookauthor11, &queryDlg2::OnEnKillfocusbookauthor11)
	ON_EN_KILLFOCUS(bookpublisher11, &queryDlg2::OnEnKillfocusbookpublisher11)
	ON_CBN_KILLFOCUS(pricefrom, &queryDlg2::OnCbnKillfocuspricefrom)
	ON_CBN_KILLFOCUS(priceto, &queryDlg2::OnCbnKillfocuspriceto)
	ON_CBN_KILLFOCUS(yearfrom, &queryDlg2::OnCbnKillfocusyearfrom)
	
	ON_CBN_KILLFOCUS(yearto, &queryDlg2::OnCbnKillfocusyearto)
	ON_EN_CHANGE(bookname11, &queryDlg2::OnEnChangebookname11)
END_MESSAGE_MAP()


// queryDlg2 消息处理程序


void queryDlg2::OnEnKillfocusbookname11()
{
	GetDlgItemText(bookname11, bookname2_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg2::OnEnKillfocusbooktype11()
{
	GetDlgItemText(booktype11, booktype2_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg2::OnEnKillfocusbookauthor11()
{
	GetDlgItemText(bookauthor11, bookauthor2_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg2::OnEnKillfocusbookpublisher11()
{
	GetDlgItemText(bookpublisher11, bookpublisher2_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg2::OnCbnKillfocuspricefrom()
{
	GetDlgItemText(pricefrom, pricefrom2_text);
	int F_index =cmbprice1.FindStringExact(0, pricefrom2_text);
	if (F_index != CB_ERR) cmbprice1.AddString(pricefrom2_text);
	// TODO: 在此添加控件通知处理程序代码2
}


void queryDlg2::OnCbnKillfocuspriceto()
{
	GetDlgItemText(priceto, priceto2_text);
	int F_index = cmbprice2.FindStringExact(0, priceto2_text);
	if (F_index != CB_ERR) cmbprice2.AddString(priceto2_text);

	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg2::OnCbnKillfocusyearfrom()
{
	GetDlgItemText(yearfrom, yearfrom2_text);
	int F_index = cmbyear1.FindStringExact(0, yearfrom2_text);
	if (F_index != CB_ERR) cmbyear1.AddString(yearfrom2_text);
	// TODO: 在此添加控件通知处理程序代码
}




void queryDlg2::OnCbnKillfocusyearto()
{
	GetDlgItemText(yearto, yearto2_text);
	int F_index = cmbyear2.FindStringExact(0, yearto2_text);
	if (F_index != CB_ERR) cmbyear2.AddString(yearto2_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg2::OnEnChangebookname11()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
