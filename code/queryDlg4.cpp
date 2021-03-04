// queryDlg4.cpp: 实现文件
//

#include "pch.h"
#include "MFC_exp05.h"
#include "queryDlg4.h"
#include "afxdialogex.h"


// queryDlg4 对话框

IMPLEMENT_DYNAMIC(queryDlg4, CDialogEx)

queryDlg4::queryDlg4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QUERY4_DIALOG4, pParent)
{

}

queryDlg4::~queryDlg4()
{
}

void queryDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(queryDlg4, CDialogEx)
	ON_EN_KILLFOCUS(borrowcard, &queryDlg4::OnEnKillfocusborrowcard)
	ON_EN_KILLFOCUS(bookid, &queryDlg4::OnEnKillfocusbookid)
END_MESSAGE_MAP()


// queryDlg4 消息处理程序


void queryDlg4::OnEnKillfocusborrowcard()
{
	GetDlgItemText(borrowcard, cardid_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg4::OnEnKillfocusbookid()
{
	GetDlgItemText(bookid, bookid_text);
	// TODO: 在此添加控件通知处理程序代码
}
