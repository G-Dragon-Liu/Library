// queryDlg3.cpp: 实现文件
//

#include "pch.h"
#include "MFC_exp05.h"
#include "queryDlg3.h"
#include "afxdialogex.h"


// queryDlg3 对话框

IMPLEMENT_DYNAMIC(queryDlg3, CDialogEx)

queryDlg3::queryDlg3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Query3_DIALOG3, pParent)
{

}

queryDlg3::~queryDlg3()
{
}

void queryDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, Affiliation, cmbbox1);
	DDX_Control(pDX, cardtype, cmbbox2);
}


BEGIN_MESSAGE_MAP(queryDlg3, CDialogEx)
	ON_EN_KILLFOCUS(cardid, &queryDlg3::OnEnKillfocuscardid)
	ON_EN_KILLFOCUS(cardname, &queryDlg3::OnEnKillfocuscardname)
	ON_CBN_KILLFOCUS(Affiliation, &queryDlg3::OnCbnKillfocusAffiliation)
	ON_CBN_KILLFOCUS(cardtype, &queryDlg3::OnCbnKillfocuscardtype)
END_MESSAGE_MAP()


// queryDlg3 消息处理程序


void queryDlg3::OnEnKillfocuscardid()
{
	GetDlgItemText(cardid,cardid_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg3::OnEnKillfocuscardname()
{
	GetDlgItemText(cardname, cardname_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg3::OnCbnKillfocusAffiliation()
{
	GetDlgItemText(Affiliation, affiliation_text);
	int F_index = cmbbox1.FindStringExact(0, affiliation_text);
	if (F_index != CB_ERR) cmbbox1.AddString(affiliation_text);
	// TODO: 在此添加控件通知处理程序代码
}


void queryDlg3::OnCbnKillfocuscardtype()
{
	GetDlgItemText(cardtype, cardtype_text);
	int F_index = cmbbox2.FindStringExact(0, cardtype_text);
	if (F_index != CB_ERR) cmbbox2.AddString(cardtype_text);
	// TODO: 在此添加控件通知处理程序代码
}
