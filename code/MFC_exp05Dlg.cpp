
// MFC_exp05Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC_exp05.h"
#include "MFC_exp05Dlg.h"
#include "afxdialogex.h"
#include"Login_window.h"
#include <afxwin.h> 
#include "winsock.h"//因为数据库是通过网络连接的，必须包含网络相关头文件
#include "mysql.h"//mysql头文件
#include <afx.h>  //CString 头文件
#include <afxpriv.h> //用于CString to char *

#include <atlstr.h>
#include <string>
#include <cstring>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCexp05Dlg 对话框



CMFCexp05Dlg::CMFCexp05Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_EXP05_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCexp05Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, listctrl1, list1);
	DDX_Control(pDX, listctrl2, list2);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, listctrl3, list3);
}

BEGIN_MESSAGE_MAP(CMFCexp05Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(book_query, &CMFCexp05Dlg::OnBnClickedquery)
	ON_BN_CLICKED(IDOK, &CMFCexp05Dlg::OnBnClickedOk)
	ON_BN_CLICKED(admin_login, &CMFCexp05Dlg::OnBnClickedlogin)
	


	ON_BN_CLICKED(admin_logout, &CMFCexp05Dlg::OnBnClickedlogout)
	//ON_NOTIFY(LVN_ITEMCHANGED, listctrl, &CMFCexp05Dlg::OnLvnItemchangedlistctrl)
	ON_BN_CLICKED(book_borrow, &CMFCexp05Dlg::OnBnClickedborrow)
	ON_BN_CLICKED(book_return, &CMFCexp05Dlg::OnBnClickedreturn)
	ON_BN_CLICKED(book_in, &CMFCexp05Dlg::OnBnClickedin)
	ON_BN_CLICKED(libcar_manage, &CMFCexp05Dlg::OnBnClickedmanage)
	ON_BN_CLICKED(bookquery1, &CMFCexp05Dlg::OnBnClickedbookquery1)
	ON_BN_CLICKED(bookcancel1, &CMFCexp05Dlg::OnBnClickedbookcancel1)
	ON_BN_CLICKED(bookquery2, &CMFCexp05Dlg::OnBnClickedbookquery2)
	ON_BN_CLICKED(bookcancel2, &CMFCexp05Dlg::OnBnClickedbookcancel2)
	ON_BN_CLICKED(cardadd3, &CMFCexp05Dlg::OnBnClickedcardadd3)
	ON_BN_CLICKED(cardcancel3, &CMFCexp05Dlg::OnBnClickedcardcancel3)
	ON_BN_CLICKED(borrowrecord, &CMFCexp05Dlg::OnBnClickedborrowrecord)
	ON_BN_CLICKED(borrowout, &CMFCexp05Dlg::OnBnClickedborrowout)
	ON_BN_CLICKED(bookback, &CMFCexp05Dlg::OnBnClickedbookback)
END_MESSAGE_MAP()


// CMFCexp05Dlg 消息处理程序

BOOL CMFCexp05Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	

	//隐藏借书管理book_borrow  还书管理book_return  图书入库book_in	借书证管理libcar_manage
	GetDlgItem(book_borrow)->ShowWindow(SW_HIDE);
	GetDlgItem(book_return)->ShowWindow(SW_HIDE);
	GetDlgItem(book_in)->ShowWindow(SW_HIDE);
	GetDlgItem(libcar_manage)->ShowWindow(SW_HIDE);
	GetDlgItem(admin_logout)->ShowWindow(SW_HIDE);

	GetDlgItem(borrowrecord)->ShowWindow(SW_HIDE);
	//设置登陆信息
	SetDlgItemText(cur_username, TEXT("未登录！"));

	//设置lisctctrol1
	list1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线
	list1.InsertColumn(0, _T(""), LVCFMT_LEFT, 20, -1);
	list1.InsertColumn(1, _T("书号"), LVCFMT_LEFT, 80,-1);
	list1.InsertColumn(2, _T("类别"), LVCFMT_LEFT, 60, -1); // 插入第2列的列名
	list1.InsertColumn(3, _T("书名"), LVCFMT_LEFT, 60, -1); // 插入第3列的列名
    list1.InsertColumn(4, _T("出版社"), LVCFMT_LEFT,120, -1); // 插入第4列的列名
	list1.InsertColumn(5, _T("作者"), LVCFMT_LEFT, 60, -1); // 插入第5列的列名
	list1.InsertColumn(6, _T("年份"), LVCFMT_LEFT, 60, -1); // 插入第6列的列名
	list1.InsertColumn(7, _T("价格"), LVCFMT_LEFT, 60, -1); // 插入第7列的列名
	list1.InsertColumn(8, _T("总藏书量"), LVCFMT_LEFT, 60, -1); // 插入第8列的列名
	list1.InsertColumn(9, _T("库存"), LVCFMT_LEFT, 60, -1); // 插入第9列的列名

	/*
	insert into  bookinfo values('00000000','计算机','数据结构','人民出版社','陈越','2000',100,100,100);
	*/
	
	//nWidth 以像素为单位的列宽。如果该参数为-1，那么没有设置列宽。
//nSubItem  与列相关联的子项的索引。如果该参数为-1，那么没有子项与列相关。
	//设置listctrl2
	
	list2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线
	list2.InsertColumn(0, _T(""), LVCFMT_LEFT, 20, -1);
	list2.InsertColumn(1, _T("卡号"), LVCFMT_LEFT, 100, -1);
	list2.InsertColumn(2, _T("姓名"), LVCFMT_LEFT, 100, -1); // 插入第2列的列名
	list2.InsertColumn(3, _T("所属单位"), LVCFMT_LEFT, 100, -1); // 插入第3列的列名
	list2.InsertColumn(4, _T("类别"), LVCFMT_LEFT, 100, -1);

	//设置listctrl3
	list3.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线
	list3.InsertColumn(0, _T(""), LVCFMT_LEFT, 20, -1);
	list3.InsertColumn(1, _T("卡号"), LVCFMT_LEFT, 100, -1);
	list3.InsertColumn(2, _T("书号"), LVCFMT_LEFT, 100, -1); // 插入第2列的列名
	list3.InsertColumn(3, _T("借书时间"), LVCFMT_LEFT, 150, -1); // 插入第3列的列名
	list3.InsertColumn(4, _T("还书时间"), LVCFMT_LEFT, 150, -1);
	//
	GetDlgItem(listctrl1)->ShowWindow(SW_HIDE);
	GetDlgItem(listctrl2)->ShowWindow(SW_HIDE);
	GetDlgItem(listctrl3)->ShowWindow(SW_HIDE);
	//关于tab 的使用

	m_queryDlg1.Create(IDD_Query1_DIALOG1, GetDlgItem(IDC_TAB1));
	m_queryDlg2.Create(IDD_Query2_DIALOG2, GetDlgItem(IDC_TAB1));
	m_queryDlg3.Create(IDD_Query3_DIALOG3, GetDlgItem(IDC_TAB1));
	m_queryDlg4.Create(IDD_QUERY4_DIALOG4, GetDlgItem(IDC_TAB1));

	//由于这里是初始化，所以不需要改，删，增

	//八个按钮的初始隐藏

	//八个按钮的控制
	GetDlgItem(bookquery1)->ShowWindow(SW_HIDE);
	GetDlgItem(bookcancel1)->ShowWindow(SW_HIDE);
	GetDlgItem(bookcancel2)->ShowWindow(SW_HIDE);
	GetDlgItem(bookquery2)->ShowWindow(SW_HIDE);

	GetDlgItem(cardcancel3)->ShowWindow(SW_HIDE);
	GetDlgItem(cardadd3)->ShowWindow(SW_HIDE);

	GetDlgItem(borrowout)->ShowWindow(SW_HIDE);
	GetDlgItem(bookback)->ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCexp05Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCexp05Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCexp05Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCexp05Dlg::OnBnClickedquery()
{
	int row_num = list1.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list1.DeleteItem(0);
	}
	//选项卡的选择显示与不显示
	m_queryDlg1.ShowWindow(SW_HIDE);
	m_queryDlg2.ShowWindow(SW_SHOW);
	m_queryDlg3.ShowWindow(SW_HIDE);
	m_queryDlg4.ShowWindow(SW_HIDE);

	//八个按钮的控制
	GetDlgItem(bookquery1)->ShowWindow(SW_SHOW);
	GetDlgItem(bookcancel1)->ShowWindow(SW_SHOW);
	GetDlgItem(bookcancel2)->ShowWindow(SW_HIDE);
	GetDlgItem(bookquery2)->ShowWindow(SW_HIDE);

	GetDlgItem(cardcancel3)->ShowWindow(SW_HIDE);
	GetDlgItem(cardadd3)->ShowWindow(SW_HIDE);

	GetDlgItem(borrowout)->ShowWindow(SW_HIDE);
	GetDlgItem(bookback)->ShowWindow(SW_HIDE);

	//关于数据库 首先先写一个简单查询


	GetDlgItem(listctrl1)->ShowWindow(SW_SHOW);
	GetDlgItem(listctrl2)->ShowWindow(SW_HIDE);
	GetDlgItem(listctrl3)->ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCexp05Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFCexp05Dlg::OnBnClickedlogin()
{
	
	Login_window lw;
	lw.DoModal();
	CString Cs_username(lw.username_text);
	SetDlgItemText(cur_username, lw.username_text);
	if (lw.username_text != "未登录") {

	GetDlgItem(book_borrow)->ShowWindow(SW_SHOW);
	GetDlgItem(book_return)->ShowWindow(SW_SHOW);
	GetDlgItem(book_in)->ShowWindow(SW_SHOW);
	GetDlgItem(libcar_manage)->ShowWindow(SW_SHOW);
	GetDlgItem(admin_login)->ShowWindow(SW_HIDE);
	GetDlgItem(admin_logout)->ShowWindow(SW_SHOW);

	GetDlgItem(borrowrecord)->ShowWindow(SW_SHOW);
	}
	// TODO: 在此添加控件通知处理程序代码
}





void CMFCexp05Dlg::OnBnClickedlogout()
{
	GetDlgItem(book_borrow)->ShowWindow(SW_HIDE);
	GetDlgItem(book_return)->ShowWindow(SW_HIDE);
	GetDlgItem(book_in)->ShowWindow(SW_HIDE);
	GetDlgItem(libcar_manage)->ShowWindow(SW_HIDE);
	GetDlgItem(admin_login)->ShowWindow(SW_SHOW);
	GetDlgItem(admin_logout)->ShowWindow(SW_HIDE);
	
	SetDlgItemText(cur_username, TEXT("未登录"));

	// TODO: 在此添加控件通知处理程序代码
}


void CMFCexp05Dlg::OnLvnItemchangedlistctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMFCexp05Dlg::OnBnClickedborrow()
{
	//list

	//选项卡管理
	m_queryDlg1.ShowWindow(SW_HIDE);
	m_queryDlg2.ShowWindow(SW_HIDE);
	m_queryDlg3.ShowWindow(SW_HIDE);
	m_queryDlg4.ShowWindow(SW_SHOW);
	//

	GetDlgItem(bookquery1)->ShowWindow(SW_HIDE);
	GetDlgItem(bookcancel1)->ShowWindow(SW_HIDE);
	GetDlgItem(bookcancel2)->ShowWindow(SW_HIDE);
	GetDlgItem(bookquery2)->ShowWindow(SW_HIDE);

	GetDlgItem(cardcancel3)->ShowWindow(SW_HIDE);
	GetDlgItem(cardadd3)->ShowWindow(SW_HIDE);

	GetDlgItem(borrowout)->ShowWindow(SW_SHOW);
	GetDlgItem(bookback)->ShowWindow(SW_HIDE);

	//显示借书按钮
	GetDlgItem(listctrl1)->ShowWindow(SW_SHOW);
	GetDlgItem(listctrl2)->ShowWindow(SW_HIDE);
	GetDlgItem(listctrl3)->ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCexp05Dlg::OnBnClickedreturn()
{
	//选项卡管理
	m_queryDlg1.ShowWindow(SW_HIDE);
	m_queryDlg2.ShowWindow(SW_HIDE);
	m_queryDlg3.ShowWindow(SW_HIDE);
	m_queryDlg4.ShowWindow(SW_SHOW);

	//GetDlgItem(bookquery1)->ShowWindow(SW_HIDE);
	GetDlgItem(bookcancel1)->ShowWindow(SW_HIDE);
	GetDlgItem(bookcancel2)->ShowWindow(SW_HIDE);
	GetDlgItem(bookquery2)->ShowWindow(SW_HIDE);

	GetDlgItem(cardcancel3)->ShowWindow(SW_HIDE);
	GetDlgItem(cardadd3)->ShowWindow(SW_HIDE);

	GetDlgItem(borrowout)->ShowWindow(SW_HIDE);
	GetDlgItem(bookback)->ShowWindow(SW_SHOW);
	// 显示还书按钮

	GetDlgItem(listctrl1)->ShowWindow(SW_SHOW);
	GetDlgItem(listctrl2)->ShowWindow(SW_HIDE);
	GetDlgItem(listctrl3)->ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCexp05Dlg::OnBnClickedin()
{
	
	
	int row_num = list1.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list1.DeleteItem(0);
	}

	mysql_init(&m_sql1);//初始化
	char querystate[200];
	char *wherestate;
	int flag = 0;
	std::string tempstr1;
	CString temp;
	std::string tempstr2;
	int size;

	MYSQL_RES *sqlResult = NULL;
	int list1row;
	int row;
	int field;
	MYSQL_ROW row_test;
	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from bookinfo \0");
		size = strlen(querystate);
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {
			AfxMessageBox(_T("查询失败"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			field = (int)mysql_num_fields(sqlResult);

			row_test = mysql_fetch_row(sqlResult);
			while (row_test) {

				list1.InsertItem(list1row, _T("")); // 插入行
				for (int i = 0; i < field; i++) { //对于表1 是9列
					CString CS_test(row_test[i]);
					list1.SetItemText(list1row, i + 1, CS_test);
				}
				row_test = mysql_fetch_row(sqlResult);
				list1row++;
			}
		}
		/*

		*/
	}

	//选项卡管理
	m_queryDlg1.ShowWindow(SW_SHOW);
	m_queryDlg2.ShowWindow(SW_HIDE);
	m_queryDlg3.ShowWindow(SW_HIDE);
	m_queryDlg4.ShowWindow(SW_HIDE);
	//
	GetDlgItem(bookquery1)->ShowWindow(SW_HIDE);
	GetDlgItem(bookcancel1)->ShowWindow(SW_HIDE);

	GetDlgItem(bookcancel2)->ShowWindow(SW_SHOW);
	GetDlgItem(bookquery2)->ShowWindow(SW_SHOW);

	GetDlgItem(cardcancel3)->ShowWindow(SW_HIDE);
	GetDlgItem(cardadd3)->ShowWindow(SW_HIDE);

	GetDlgItem(borrowout)->ShowWindow(SW_HIDE);
	GetDlgItem(bookback)->ShowWindow(SW_HIDE);
	//


	GetDlgItem(listctrl1)->ShowWindow(SW_SHOW);
	GetDlgItem(listctrl2)->ShowWindow(SW_HIDE);
	GetDlgItem(listctrl3)->ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCexp05Dlg::OnBnClickedmanage()
{
	int row_num = list2.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list2.DeleteItem(0);
	}

	mysql_init(&m_sql1);//初始化
	char querystate[200];
	char *wherestate;
	int flag = 0;
	std::string tempstr1;
	CString temp;
	std::string tempstr2;
	int size;

	MYSQL_RES *sqlResult = NULL;
	int list1row;
	int row;
	int field;
	MYSQL_ROW row_test;

	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));
	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from libcard \0");
		size = strlen(querystate);

		if (0 != mysql_real_query(&m_sql1, querystate, size)) {
			AfxMessageBox(_T("查询失败"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			field = (int)mysql_num_fields(sqlResult);
			row_test = mysql_fetch_row(sqlResult);
			while (row_test) {

				list2.InsertItem(list1row, _T("")); // 插入行
				for (int i = 0; i < field; i++) { //对于表1 是9列
					CString CS_test(row_test[i]);
					list2.SetItemText(list1row, i+1, CS_test);
				}
				row_test = mysql_fetch_row(sqlResult);
				list1row++;
			}
		}
		/*

		*/
	}
	//选项卡管理
	m_queryDlg1.ShowWindow(SW_HIDE);
	m_queryDlg2.ShowWindow(SW_HIDE);
	m_queryDlg3.ShowWindow(SW_SHOW);
	m_queryDlg4.ShowWindow(SW_HIDE);

	//
	GetDlgItem(bookquery1)->ShowWindow(SW_HIDE);
	GetDlgItem(bookcancel1)->ShowWindow(SW_HIDE);

	GetDlgItem(bookcancel2)->ShowWindow(SW_HIDE);
	GetDlgItem(bookquery2)->ShowWindow(SW_HIDE);

	GetDlgItem(cardcancel3)->ShowWindow(SW_SHOW);
	GetDlgItem(cardadd3)->ShowWindow(SW_SHOW);

	GetDlgItem(borrowout)->ShowWindow(SW_HIDE);
	GetDlgItem(bookback)->ShowWindow(SW_HIDE);

	//
	GetDlgItem(listctrl1)->ShowWindow(SW_HIDE);
	GetDlgItem(listctrl2)->ShowWindow(SW_SHOW);
	GetDlgItem(listctrl3)->ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCexp05Dlg::OnBnClickedbookquery1()
{
	int row_num = list1.GetItemCount();
	for (int i = 0; i <row_num; i++) {
		list1.DeleteItem(0);
	}
	//查询 针对 m_dialog2 查询的是表1（bookinfo）
	/*
		y由于删除行之后下面的会往上移动，比如删除第0行，第一行变成第0行
	*/
	// TODO: 在此添加控件通知处理程序代码
	//m_sql1 在.h中定义
//连接数据库
	
	mysql_init(&m_sql1);//初始化
	char querystate[200];
	char *wherestate;
	int flag = 0;
	std::string tempstr1;
	CString temp;
	std::string tempstr2;
	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate,"select * from bookinfo \0");
		wherestate=" where ";
		
		//由于是对 m_dialog2里面的东西进行查询，去出相应的元素
	
		flag = 0; //+and
		tempstr1 ="";
		temp="";
		
		//八个edit 的内容
		if (m_queryDlg2.bookname2_text != "") {
			temp = m_queryDlg2.bookname2_text;
			tempstr2=CT2A(temp.GetBuffer());
			if (flag == 1) {
				tempstr1 += " and ";
			}
			else flag = 1;
			tempstr1 += "book_name = '" + tempstr2+"'";
			
		}
		if (m_queryDlg2.booktype2_text != "") {
			temp = m_queryDlg2.booktype2_text;
			tempstr2 = CT2A(temp.GetBuffer());
			if (flag == 1) {
				tempstr1 += " and ";
			}
			else flag = 1;
			tempstr1 += "book_type = '" + tempstr2+"'";
			
		}
		if (m_queryDlg2.bookpublisher2_text != "") {
			temp = m_queryDlg2.bookpublisher2_text;
			tempstr2 = CT2A(temp.GetBuffer());
			if (flag == 1) {
				tempstr1 += " and ";
			}
			else flag = 1; 
			tempstr1 += "boonk_publisher = '" + tempstr2+"'";
			
		}
		if (m_queryDlg2.bookauthor2_text != "") {
			temp = m_queryDlg2.bookauthor2_text;
			tempstr2 = CT2A(temp.GetBuffer());
			if (flag == 1) {
				tempstr1 += " and ";
			}
			else flag = 1;
			tempstr1 += "book_author = '" + tempstr2 + "'";
		}
		if (m_queryDlg2.priceto2_text != "") {
			temp = m_queryDlg2.priceto2_text;
			tempstr2 = CT2A(temp.GetBuffer());
			if (flag == 1) {
				tempstr1 += " and ";
			}
			else flag = 1;
			tempstr1 += "book_price <= " + tempstr2 + "";
		}
		if (m_queryDlg2.pricefrom2_text != "") {
			temp = m_queryDlg2.pricefrom2_text;
			tempstr2 = CT2A(temp.GetBuffer());
			if (flag == 1) {
				tempstr1 += " and ";
			}
			else flag = 1;
			tempstr1 += "book_price >= " + tempstr2 + "";
		}
		if (m_queryDlg2.yearfrom2_text != "") {
			temp = m_queryDlg2.yearfrom2_text;
			tempstr2 = CT2A(temp.GetBuffer());
			if (flag == 1) {
				tempstr1 += " and ";
			}
			else flag = 1;
			tempstr1 += "book_year >= " + tempstr2 + "";
		}
		if (m_queryDlg2.yearto2_text != "") {
			temp = m_queryDlg2.yearto2_text;
			 tempstr2 = CT2A(temp.GetBuffer());
			if (flag == 1) {
				tempstr1 += " and ";
			}
			else flag = 1;
			tempstr1 += "book_year <= " + tempstr2 + "";
		}
		if (tempstr1 != "") {
			strcat(querystate, wherestate);
			strcat(querystate, tempstr1.c_str());
		}

		int size = strlen(querystate);
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {
			AfxMessageBox(_T("查询失败"));
		}
		else {
			MYSQL_RES *sqlResult = NULL;
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			int list1row = 0;//遍历行，读取数据
			int row = (int)mysql_num_rows(sqlResult);
			int field = (int)mysql_num_fields(sqlResult);
			MYSQL_ROW row_test;
			row_test = mysql_fetch_row(sqlResult);
			while (row_test) {

				list1.InsertItem(list1row, _T("")); // 插入行
				for (int i = 0; i <field; i++) { //对于表1 是9列
					CString CS_test(row_test[i]);
					list1.SetItemText(list1row, i+1, CS_test);
				}
				row_test = mysql_fetch_row(sqlResult);
				list1row++;
			}
		}
		/*
		
		*/
	}
	mysql_close(&m_sql1);//关闭Mysql连接
	
}


void CMFCexp05Dlg::OnBnClickedbookcancel1()
{
	//m_queryDlg2.SetDlgItemTextW();
	m_queryDlg2.bookname2_text="";
	m_queryDlg2.booktype2_text="";
	m_queryDlg2.bookpublisher2_text="";
	m_queryDlg2.bookauthor2_text="";
	m_queryDlg2.priceto2_text="";
	m_queryDlg2.pricefrom2_text="";
	m_queryDlg2.yearfrom2_text="";
	m_queryDlg2.yearto2_text="";
	//
	m_queryDlg2.booknamev.SetWindowTextW(TEXT(""));
	m_queryDlg2.booktypev.SetWindowTextW(TEXT(""));
	m_queryDlg2.bookauthorv.SetWindowTextW(TEXT(""));
	m_queryDlg2.bookpublisherv.SetWindowTextW(TEXT(""));
	m_queryDlg2.cmbprice1.SetWindowTextW(TEXT(""));
	m_queryDlg2.cmbprice2.SetWindowTextW(TEXT(""));
	m_queryDlg2.cmbyear1.SetWindowTextW(TEXT(""));
	m_queryDlg2.cmbyear2.SetWindowTextW(TEXT(""));
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCexp05Dlg::OnBnClickedbookquery2()
{
	int row_num = list1.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list1.DeleteItem(0);
	}
	if (m_queryDlg1.bookid1_text == "") {
		AfxMessageBox(_T("书号为空"));
		return;
	}
	//先select *
	//连接数据库

	
	mysql_init(&m_sql1);//初始化
	char querystate[200];
	char *wherestate;
	int flag = 0;
	std::string tempstr1;
	CString temp;
	std::string tempstr2;
	int size;

	MYSQL_RES *sqlResult = NULL;
	int list1row;
	int row;
	int field;
	MYSQL_ROW row_test;
	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from bookinfo \0");
		size = strlen(querystate);
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {
			AfxMessageBox(_T("查询失败"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			field = (int)mysql_num_fields(sqlResult);

			row_test = mysql_fetch_row(sqlResult);
			while (row_test) {

				list1.InsertItem(list1row, _T("")); // 插入行
				for (int i = 0; i < field; i++) { //对于表1 是9列
					CString CS_test(row_test[i]);
					list1.SetItemText(list1row, i + 1, CS_test);
				}
				row_test = mysql_fetch_row(sqlResult);
				list1row++;
			}
		}
		/*

		*/
	}
	//对表1 进行增、改、删、查 先查又没有，如果有就进行update else insert
	//删的话直接delete
	//此按键是增加（先查）
	mysql_init(&m_sql1);//初始化


	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from bookinfo \0");

		strcat(querystate, "where book_id = '");
		temp = m_queryDlg1.bookid1_text;//CString to string 
		tempstr2 = CT2A(temp);
		strcat(querystate, tempstr2.c_str());
		strcat(querystate, "'");

		size = strlen(querystate);
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {//
			AfxMessageBox(_T("查询错误"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			if (row == 0) {
				//insert 
	//insert into  bookinfo values('00000000','计算机','数据结构','人民出版社','陈越','2000',100,100,100);
				strcpy(querystate, "insert into bookinfo values('");

				temp = m_queryDlg1.bookid1_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("书号为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "','");
				//bookid
				temp = m_queryDlg1.booktype1_text;//CString to string
				if (temp == "") {
					AfxMessageBox(_T("书类型为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "','");
				//booktype
				temp = m_queryDlg1.bookname1_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("书名为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "','");
				//bookname;
				temp = m_queryDlg1.bookpublisher1_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("出版社为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "','");
				//bookpublisher
				temp = m_queryDlg1.bookauthor1_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("作者为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "',");
				//bookauthor
				temp = m_queryDlg1.bookyear1_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("年份为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, ",");
				//bookyear
				temp = m_queryDlg1.bookprice1_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("价格为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, ",");
				//book price1;
				temp = m_queryDlg1.booknum1_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("数量为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, ",");
				//book_total_store;
				temp = m_queryDlg1.booknum1_text;//CString to string 
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, ")");
				//booknow_store;
				size = strlen(querystate);
				if (0 != mysql_real_query(&m_sql1, querystate, size)) {
					AfxMessageBox(_T("插入数据失败"));
				}
				else {
					AfxMessageBox(_T("插入数据成功!"));
				}
			}
			else {
				if (IDOK == AfxMessageBox(_T("该书号已经存在，是否选择更改已有信息")), MB_OKCANCEL)//updtate
				{

					//update bookinfo set FirstName = 'Fred' WHERE LastName = 'Wilson'
					strcpy(querystate, "update bookinfo set ");
					//temp = m_queryDlg1.bookid1_text;//CString to string 

					//bookid
					temp = m_queryDlg1.booktype1_text;//CString to string
					flag = 0;
					if (temp != "") {
						tempstr2 = CT2A(temp);
						if (flag == 1) {
							strcat(querystate, " , ");
						}
						else flag = 0;
						strcat(querystate, " book_type = '");
						strcat(querystate, tempstr2.c_str());
						strcat(querystate, "' ");
					}
					//booktype
					temp = m_queryDlg1.bookname1_text;//CString to string 
					if (temp != "") {
						tempstr2 = CT2A(temp);
						if (flag == 1) {
							strcat(querystate, " , ");
						}
						else flag = 0;
						strcat(querystate, " book_name = '");
						strcat(querystate, tempstr2.c_str());
						strcat(querystate, "' ");
					}

					//bookname;
					temp = m_queryDlg1.bookauthor1_text;//CString to string 
					if (temp != "") {
						tempstr2 = CT2A(temp);
						if (flag == 1) {
							strcat(querystate, " , ");
						}
						else flag = 0;
						strcat(querystate, " book_author = '");
						strcat(querystate, tempstr2.c_str());
						strcat(querystate, "' ");
					}

					//bookauthor
					temp = m_queryDlg1.bookyear1_text;//CString to string 
					if (temp != "") {
						tempstr2 = CT2A(temp);
						if (flag == 1) {
							strcat(querystate, " , ");
						}
						else flag = 0;
						strcat(querystate, " book_year = ");
						strcat(querystate, tempstr2.c_str());

					}

					//bookyear
					temp = m_queryDlg1.bookprice1_text;//CString to string 
					if (temp != "") {
						tempstr2 = CT2A(temp);
						if (flag == 1) {
							strcat(querystate, " , ");
						}
						else flag = 0;
						strcat(querystate, " book_price = ");
						strcat(querystate, tempstr2.c_str());
					}

					//book price1;
					temp = m_queryDlg1.booknum1_text;//CString to string 
					if (temp != "") {
						tempstr2 = CT2A(temp);
						if (flag == 1) {
							strcat(querystate, " , ");
						}
						else flag = 0;
						strcat(querystate, "total_store = total_store +");
						strcat(querystate, tempstr2.c_str());

						strcat(querystate, " , ");
						strcat(querystate, " now_store = now_store + ");
						strcat(querystate, tempstr2.c_str());
					}

					strcat(querystate, " where book_id ='");
					temp = m_queryDlg1.bookid1_text;
					tempstr2 = CT2A(temp);
					strcat(querystate, tempstr2.c_str());
					strcat(querystate, "'");

					size = strlen(querystate);
					if (0 != mysql_real_query(&m_sql1, querystate, size)) {
						AfxMessageBox(_T("更新失败"));
					}
					else {
						AfxMessageBox(_T("更新数据成功!"));
					}

				}
				else {
					return;
				}//update
			}


		}
	}
		//最后select *

		row_num = list1.GetItemCount();
		for (int i = 0; i < row_num; i++) {
			list1.DeleteItem(0);
		}
		mysql_init(&m_sql1);//初始化
		if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
			//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
		{
			AfxMessageBox(_T("数据库连接失败!"));

		}
		else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
		{
			//AfxMessageBox(_T("数据库连接成功!"));

			// 查询
			mysql_query(&m_sql1, "SET NAMES 'GB2312'");
			//设置数据库字符格式，解决中文乱码问题
			strcpy(querystate, "select * from bookinfo \0");
			size = strlen(querystate);
			if (0 != mysql_real_query(&m_sql1, querystate, size)) {
				AfxMessageBox(_T("查询失败"));
			}
			else {
				sqlResult = mysql_store_result(&m_sql1);
				//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
				list1row = 0;//遍历行，读取数据
				row = (int)mysql_num_rows(sqlResult);
				field = (int)mysql_num_fields(sqlResult);
				row_test = mysql_fetch_row(sqlResult);
				while (row_test) {

					list1.InsertItem(list1row, _T("")); // 插入行
					for (int i = 0; i < field; i++) { //对于表1 是9列
						CString CS_test(row_test[i]);
						list1.SetItemText(list1row, i+1, CS_test);
					}
					row_test = mysql_fetch_row(sqlResult);
					list1row++;
				}
			}
		}
		mysql_close(&m_sql1);//关闭Mysql连接
		// TODO: 在此添加控件通知处理程序代码
	
}

void CMFCexp05Dlg::OnBnClickedbookcancel2()
{

	int primary_null = 0; //主码是否为空
	if (m_queryDlg1.bookid1_text == "") {
		primary_null = 1;
	}

	int row_num = list1.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list1.DeleteItem(0);
	}

	mysql_init(&m_sql1);//初始化
	char querystate[200];
	char wherestate[200];
	int flag = 0;
	std::string tempstr1;
	CString temp;
	std::string tempstr2;
	int size;

	MYSQL_RES *sqlResult = NULL;
	int list1row;
	int row;
	int field;
	MYSQL_ROW row_test;


	mysql_init(&m_sql1);//初始化

	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//delete from libcard where card_id = '00000000' and card_name = 'lzd';
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from bookinfo where \0");
		flag = 0;
		strcpy(wherestate, "");
		int flag_null = 1; //判断输入是否都为空。
		if (primary_null != 1) {

			strcat(wherestate, " book_id = '");
			temp = m_queryDlg1.bookid1_text;//CString to string 
			tempstr2 = CT2A(temp);
			strcat(wherestate, tempstr2.c_str());
			strcat(wherestate, "'");
			flag_null = 0;
		}
		else {
			temp = m_queryDlg1.bookname1_text;//CString to string 
			if (temp != "") {
				if (flag == 0) {
					flag = 1;
					flag_null = 0;
				}
				else {
					strcat(wherestate, " and ");
				}
				strcat(wherestate, " book_name ='");
				tempstr2 = CT2A(temp);
				strcat(wherestate, tempstr2.c_str());
				strcat(wherestate, "' ");
			}

			temp = m_queryDlg1.booktype1_text;//CString to string 
			if (temp != "") {
				if (flag == 0) {
					flag = 1;
					flag_null = 0;
				}
				else {
					strcat(wherestate, " and ");
				}
				strcat(wherestate, " book_type ='");
				tempstr2 = CT2A(temp);
				strcat(wherestate, tempstr2.c_str());
				strcat(wherestate, "' ");
			}

			temp = m_queryDlg1.bookpublisher1_text;//CString to string 
			if (temp != "") {
				if (flag == 0) {
					flag = 1;
					flag_null = 0;
				}
				else {
					strcat(wherestate, " and ");
				}
				strcat(wherestate, " book_publisher ='");
				tempstr2 = CT2A(temp);
				strcat(wherestate, tempstr2.c_str());
				strcat(wherestate, "' ");
			}
			temp = m_queryDlg1.bookyear1_text;//CString to string 
			if (temp != "") {
				if (flag == 0) {
					flag = 1;
					flag_null = 0;
				}
				else {
					strcat(wherestate, " and ");
				}
				strcat(wherestate, " book_year ='");
				tempstr2 = CT2A(temp);
				strcat(wherestate, tempstr2.c_str());
				strcat(wherestate, "' ");
			}
			temp = m_queryDlg1.bookprice1_text;//CString to string 
			if (temp != "") {
				if (flag == 0) {
					flag = 1;
					flag_null = 0;
				}
				else {
					strcat(wherestate, " and ");
				}
				strcat(wherestate, " book_price ='");
				tempstr2 = CT2A(temp);
				strcat(wherestate, tempstr2.c_str());
				strcat(wherestate, "' ");
			}
			
			temp = m_queryDlg1.bookauthor1_text;//CString to string 
			if (temp != "") {
				if (flag == 0) {
					flag = 1;
					flag_null = 0;
				}
				else {
					strcat(wherestate, " and ");
				}
				strcat(wherestate, " book_author ='");
				tempstr2 = CT2A(temp);
				strcat(wherestate, tempstr2.c_str());
				strcat(wherestate, "' ");
			}
		}
		if (flag_null == 1) {
			AfxMessageBox(_T("（除了数量，数量不能作为删除的条件）其他输入不能为空 "));
			
		}
		else {
			strcat(querystate, wherestate);
			size = strlen(querystate);
			if (0 != mysql_real_query(&m_sql1, querystate, size)) {//
				AfxMessageBox(_T("查询错误"));
			}
			else {
				sqlResult = mysql_store_result(&m_sql1);
				//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
				list1row = 0;//遍历行，读取数据
				row = (int)mysql_num_rows(sqlResult);
				flag = 0;
				if (row == 0) {//insert 
					AfxMessageBox(_T("该项目不存在"));
				}
				else {
					int tempv=1;//删
					strcpy(querystate, "delete from bookinfo where ");
					strcat(querystate, wherestate);
					if (primary_null == 1) {
						if (IDCANCEL == AfxMessageBox(_T("此项不是主码，删除或将导致多个数据被删确定吗？"), MB_OKCANCEL)) {
							tempv = 0;
						}
					}
					else if (IDCANCEL == AfxMessageBox(_T("确定删除吗？"), MB_OKCANCEL)) {
						tempv = 0;
					}
					if (tempv == 1) {//删了
						size = strlen(querystate);
						if (0 != mysql_real_query(&m_sql1, querystate, size)) {
							AfxMessageBox(_T("删除失败"));
						}
						else {
							AfxMessageBox(_T("删除成功"));
						}
					}
				}
			}
		}
	}


	row_num = list1.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list1.DeleteItem(0);
	}
	mysql_init(&m_sql1);//初始化
	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from bookinfo \0");
		size = strlen(querystate);
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {
			AfxMessageBox(_T("查询失败"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			field = (int)mysql_num_fields(sqlResult);
			row_test = mysql_fetch_row(sqlResult);
			while (row_test) {

				list1.InsertItem(list1row, _T("")); // 插入行
				for (int i = 0; i < field; i++) { //对于表1 是9列
					CString CS_test(row_test[i]);
					list1.SetItemText(list1row, i + 1, CS_test);
				}
				row_test = mysql_fetch_row(sqlResult);
				list1row++;
			}
		}
		/*

		*/
	}
	mysql_close(&m_sql1);//关闭Mysql连接
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCexp05Dlg::OnBnClickedcardadd3()
{
	int row_num = list2.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list2.DeleteItem(0);
	}

	mysql_init(&m_sql1);//初始化
	char querystate[200];
	char *wherestate;
	int flag = 0;
	std::string tempstr1;
	CString temp;
	std::string tempstr2;
	int size;

	MYSQL_RES *sqlResult = NULL;
	int list1row;
	int row;
	int field;
	MYSQL_ROW row_test;

	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from libcard \0");
		size = strlen(querystate);
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {
			AfxMessageBox(_T("查询失败"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			field = (int)mysql_num_fields(sqlResult);
			row_test = mysql_fetch_row(sqlResult);
			while (row_test) {

				list2.InsertItem(list1row, _T("")); // 插入行
				for (int i = 0; i < field; i++) { //对于表1 是9列
					CString CS_test(row_test[i]);
					list2.SetItemText(list1row, i + 1, CS_test);
				}
				row_test = mysql_fetch_row(sqlResult);
				list1row++;
			}
		}
		/*

		*/
	}
	//对表1 进行增、改、删、查 先查又没有，如果有就进行update else insert
	//删的话直接delete
	//此按键是增加（先查）
	mysql_init(&m_sql1);//初始化


	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from libcard \0");

		strcat(querystate, "where card_id = '");
		temp = m_queryDlg3.cardid_text;//CString to string 
		tempstr2 = CT2A(temp);
		strcat(querystate, tempstr2.c_str());
		strcat(querystate, "'");

		size = strlen(querystate);
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {//
			AfxMessageBox(_T("查询错误"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			if (row == 0) {//insert 
				strcpy(querystate, "insert into libcard values('");
				temp = m_queryDlg3.cardid_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("卡号为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "','");

				temp = m_queryDlg3.cardname_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("姓名为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "','");

				temp = m_queryDlg3.affiliation_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("所属单位为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "','");

				temp = m_queryDlg3.cardtype_text;//CString to string 
				if (temp == "") {
					AfxMessageBox(_T("类型为空"));
					return;
				}
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "')");

				size = strlen(querystate);
				if (0 != mysql_real_query(&m_sql1, querystate, size)) {
					AfxMessageBox(_T("插入数据失败"));
				}
				else {
					AfxMessageBox(_T("插入数据成功!"));
				}
			}
			else {
				if (IDOK == AfxMessageBox(_T("此卡号已存在,是否更新数据，确定即是，关闭即否"), MB_OKCANCEL)) {
					//更新
					//update bookinfo set FirstName = 'Fred' WHERE LastName = 'Wilson'
					strcpy(querystate, "update libcard set ");

					temp = m_queryDlg3.cardname_text;//CString to string
					if (temp != "") {
						tempstr2 = CT2A(temp);
						if (flag == 1) {
							strcat(querystate, " , ");
						}
						else flag = 0;
						strcat(querystate, " card_name = '");
						strcat(querystate, tempstr2.c_str());
						strcat(querystate, "' ");
					}

					temp = m_queryDlg3.affiliation_text;//CString to string
					if (temp != "") {
						tempstr2 = CT2A(temp);
						if (flag == 1) {
							strcat(querystate, " , ");
						}
						else flag = 0;
						strcat(querystate, " Affiliation = '");
						strcat(querystate, tempstr2.c_str());
						strcat(querystate, "' ");
					}

					temp = m_queryDlg3.cardtype_text;//CString to string
					if (temp != "") {
						tempstr2 = CT2A(temp);
						if (flag == 1) {
							strcat(querystate, " , ");
						}
						else flag = 0;
						strcat(querystate, " card_type = '");
						strcat(querystate, tempstr2.c_str());
						strcat(querystate, "' ");
					}

					strcat(querystate, " where card_id ='");
					temp = m_queryDlg3.cardid_text;
					tempstr2 = CT2A(temp);
					strcat(querystate, tempstr2.c_str());
					strcat(querystate, "'");

					size = strlen(querystate);
					if (0 != mysql_real_query(&m_sql1, querystate, size)) {
						AfxMessageBox(_T("更新失败"));
					}
					else {
						AfxMessageBox(_T("更新数据成功!"));
					}

				}
				
			}
		}
	}
	row_num = list2.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list2.DeleteItem(0);

	}
		mysql_init(&m_sql1);//初始化
		if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
			//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
		{
			AfxMessageBox(_T("数据库连接失败!"));

		}
		else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
		{
			//AfxMessageBox(_T("数据库连接成功!"));

			// 查询
			mysql_query(&m_sql1, "SET NAMES 'GB2312'");
			//设置数据库字符格式，解决中文乱码问题
			strcpy(querystate, "select * from libcard \0");
			size = strlen(querystate);
			if (0 != mysql_real_query(&m_sql1, querystate, size)) {
				AfxMessageBox(_T("查询失败"));
			}
			else {
				sqlResult = mysql_store_result(&m_sql1);
				//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
				list1row = 0;//遍历行，读取数据
				row = (int)mysql_num_rows(sqlResult);
				field = (int)mysql_num_fields(sqlResult);
				row_test = mysql_fetch_row(sqlResult);


				while (row_test) {

					list2.InsertItem(list1row, _T("")); // 插入行
					for (int i = 0; i < field; i++) { //对于表1 是9列
						CString CS_test(row_test[i]);
						list2.SetItemText(list1row, i + 1, CS_test);
					}
					row_test = mysql_fetch_row(sqlResult);
					list1row++;
				}
			}
			/*

			*/
		}
		// TODO: 在此添加控件通知处理程序代码
}


void CMFCexp05Dlg::OnBnClickedcardcancel3()
{
	int primary_null = 0; //主码是否为空
	if (m_queryDlg3.cardid_text == "") {
		primary_null = 1;
	}

	int row_num = list2.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list2.DeleteItem(0);
	}

	mysql_init(&m_sql1);//初始化
	char querystate[200];
	char *wherestate;
	int flag = 0;
	std::string tempstr1;
	CString temp;
	std::string tempstr2;
	int size;

	MYSQL_RES *sqlResult = NULL;
	int list1row;
	int row;
	int field;
	MYSQL_ROW row_test;


	mysql_init(&m_sql1);//初始化

	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//delete from libcard where card_id = '00000000' and card_name = 'lzd';
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from libcard \0");
		flag = 0;
		
		int flag_null= 1; //判断输入是否都为空。
		if (primary_null != 1) {

			strcat(querystate, "where card_id = '");
			temp = m_queryDlg3.cardid_text;//CString to string 
			tempstr2 = CT2A(temp);
			strcat(querystate, tempstr2.c_str());
			strcat(querystate, "'");
			flag_null = 0;
		}
		else {
			temp = m_queryDlg3.cardname_text;//CString to string 
			if (temp != "") {
				if (flag == 0) {
					flag = 1;
					flag_null = 0;
					strcat(querystate, " where ");
				}
				else {
					strcat(querystate, " and ");
				}
				strcat(querystate, " card_name ='");
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate,"' ");
			}

			temp = m_queryDlg3.affiliation_text;//CString to string 
			if (temp != "") {
				if (flag == 0) {
					flag = 1;
					flag_null = 0;
					strcat(querystate, " where ");
				}
				else {
					strcat(querystate, " and ");
				}
				strcat(querystate, " Affiliation ='");
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "' ");
			}

			temp = m_queryDlg3.cardtype_text;//CString to string 
			if (temp != "") {
				if (flag == 0) {
					flag = 1;
					flag_null = 0;
					strcat(querystate, " where ");
				}
				else {
					strcat(querystate, " and ");
				}
				strcat(querystate, " card_type ='");
				tempstr2 = CT2A(temp);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "' ");
			}
		}
		if (flag_null == 1) {
				AfxMessageBox(_T("输入不能为空"));
				return;
		}
		else {
			size = strlen(querystate);
			if (0 != mysql_real_query(&m_sql1, querystate, size)) {//
				AfxMessageBox(_T("查询错误"));
			}
			else {
				sqlResult = mysql_store_result(&m_sql1);
				//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
				list1row = 0;//遍历行，读取数据
				row = (int)mysql_num_rows(sqlResult);
				flag = 0;
				if (row == 0) {//insert 
					AfxMessageBox(_T("该项目不存在"));
				}
				else {
					strcpy(querystate, "delete from libcard where ");
					if (primary_null != 1) {
						strcat(querystate, " card_id = '");
						temp = m_queryDlg3.cardid_text;//CString to string 
						tempstr2 = CT2A(temp);
						strcat(querystate, tempstr2.c_str());
						strcat(querystate, "'");
						
					}
					else {
						temp = m_queryDlg3.cardname_text;//CString to string 
						if (temp != "") {
							if (flag != 0) {
								flag = 1;
								strcat(querystate, " and ");
							}
							else flag = 1;
							strcat(querystate, " card_name ='");
							tempstr2 = CT2A(temp);
							strcat(querystate, tempstr2.c_str());
							strcat(querystate, "' ");
						}

						temp = m_queryDlg3.affiliation_text;//CString to string 
						if (temp != "") {
							if (flag != 0) {
								flag = 1;
								strcat(querystate, " and ");
							}
							else flag = 1;
							strcat(querystate, " Affiliation ='");
							tempstr2 = CT2A(temp);
							strcat(querystate, tempstr2.c_str());
							strcat(querystate, "' ");
						}

						temp = m_queryDlg3.cardtype_text;//CString to string 
						if (temp != "") {
								if (flag != 0) {
									flag = 1;
									strcat(querystate, " and ");
								}
								else flag = 1;
							strcat(querystate, " card_type ='");
							tempstr2 = CT2A(temp);
							strcat(querystate, tempstr2.c_str());
							strcat(querystate, "' ");
						}
						
					}
					if (primary_null == 1) {
						if (IDCANCEL != AfxMessageBox(_T("此项不是主码，删除或将导致多个数据被删确定吗？"), MB_OKCANCEL)) {
							size = strlen(querystate);
							if (0 != mysql_real_query(&m_sql1, querystate, size)) {
								AfxMessageBox(_T("删除失败"));
							}
							else {
								AfxMessageBox(_T("删除成功"));
							}
						}
					}
					else if (IDCANCEL != AfxMessageBox(_T("确定删除吗？"), MB_OKCANCEL)) {
						size = strlen(querystate);
						if (0 != mysql_real_query(&m_sql1, querystate, size)) {
							AfxMessageBox(_T("删除失败"));
						}
						else {
							AfxMessageBox(_T("删除成功"));
						}
					}
					
				}
			}
		}

	}

	row_num = list2.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list2.DeleteItem(0);
	}
	mysql_init(&m_sql1);//初始化
	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from libcard \0");
		size = strlen(querystate);
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {
			AfxMessageBox(_T("查询失败"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			field = (int)mysql_num_fields(sqlResult);
			row_test = mysql_fetch_row(sqlResult);
			while (row_test) {

				list2.InsertItem(list1row, _T("")); // 插入行
				for (int i = 0; i < field; i++) { //对于表1 是9列
					CString CS_test(row_test[i]);
					list2.SetItemText(list1row, i+1 , CS_test);
				}
				row_test = mysql_fetch_row(sqlResult);
				list1row++;
			}
		}
		/*

		*/
	}
	mysql_close(&m_sql1);//关闭Mysql连接

	// TODO: 在此添加控件通知处理程序代码
}


void CMFCexp05Dlg::OnBnClickedborrowrecord()
{
	int row_num = list3.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list3.DeleteItem(0);
	}

	mysql_init(&m_sql1);//初始化
	char querystate[200];
	char *wherestate;
	int flag = 0;
	std::string tempstr1;
	CString temp;
	std::string tempstr2;
	int size;

	MYSQL_RES *sqlResult = NULL;
	int list1row;
	int row;
	int field;
	MYSQL_ROW row_test;
	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from borrowinfo \0");
		size = strlen(querystate);
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {
			AfxMessageBox(_T("查询失败"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			field = (int)mysql_num_fields(sqlResult);

			row_test = mysql_fetch_row(sqlResult);
			while (row_test) {

				list3.InsertItem(list1row, _T("")); // 插入行
				for (int i = 0; i < field; i++) { //对于表1 是9列
					CString CS_test(row_test[i]);
					list3.SetItemText(list1row, i + 1, CS_test);
				}
				row_test = mysql_fetch_row(sqlResult);
				list1row++;
			}
		}
		/*

		*/
	}

	SYSTEMTIME st; //定义SYSTEMTIME变量st
	CString strDate, strTime; //定义CString变量strDate和strTime
	GetLocalTime(&st); //获取系统时间到st
	strDate.Format(_T("%4d-%2d-%2d"), st.wYear, st.wMonth, st.wDay); //设置strDate变量的格式为年-月-日
	strTime.Format(_T("%2d:%2d:%2d"), st.wHour, st.wMinute, st.wSecond); //设置strTime变量的格式为时:分:秒
	SetDlgItemText(curtime, strDate + _T(" ") + strTime);
	// TODO: 在此添加控件通知处理程序代码





	//选项卡管理
	m_queryDlg1.ShowWindow(SW_HIDE);
	m_queryDlg2.ShowWindow(SW_HIDE);
	m_queryDlg3.ShowWindow(SW_HIDE);
	m_queryDlg4.ShowWindow(SW_HIDE);

	//
	

	GetDlgItem(bookquery1)->ShowWindow(SW_HIDE);
	GetDlgItem(bookcancel1)->ShowWindow(SW_HIDE);

	GetDlgItem(bookcancel2)->ShowWindow(SW_HIDE);
	GetDlgItem(bookquery2)->ShowWindow(SW_HIDE);

	GetDlgItem(cardcancel3)->ShowWindow(SW_HIDE);
	GetDlgItem(cardadd3)->ShowWindow(SW_HIDE);

	GetDlgItem(borrowout)->ShowWindow(SW_HIDE);
	GetDlgItem(bookback)->ShowWindow(SW_HIDE);

	//
	GetDlgItem(listctrl1)->ShowWindow(SW_HIDE);
	GetDlgItem(listctrl2)->ShowWindow(SW_HIDE);
	GetDlgItem(listctrl3)->ShowWindow(SW_SHOW);
}


void CMFCexp05Dlg::OnBnClickedborrowout()
{
	//借出，
	//查表borrowrecord 
	//直接insert;
	//btimefrom 可以设置
	//btimeto 设为未还书.

	//查询 针对 m_dialog2 查询的是表1（bookinfo）
	/*
		y由于删除行之后下面的会往上移动，比如删除第0行，第一行变成第0行
	*/
	// TODO: 在此添加控件通知处理程序代码
	//m_sql1 在.h中定义
//连接数据库

	mysql_init(&m_sql1);//初始化
	char querystate[200];
	char wherestate[200];
	int flag = 0;
	int size;
	std::string tempstr1;
	CString temp;
	std::string tempstr2;


	MYSQL_RES *sqlResult = NULL;
	int list1row;
	int row;
	int field;
	MYSQL_ROW row_test;
	
	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select *from  borrowinfo ");
		strcpy(wherestate, " where ");
		temp = m_queryDlg4.cardid_text;
		tempstr2 = CT2A(temp);
		if (temp == "") {
			AfxMessageBox(_T("卡号不能为空"));
			return;
		}
		strcat(wherestate, " card_id='");
		strcat(wherestate, tempstr2.c_str());
		strcat(wherestate, "' and ");
		//cardid
		temp = m_queryDlg4.bookid_text;
		tempstr2 = CT2A(temp);
		if (temp == "") {
			AfxMessageBox(_T("书号不能为空"));
			return;
		}
		strcat(wherestate, " book_id='");
		strcat(wherestate, tempstr2.c_str());
		strcat(wherestate, "' and ");

		strcat(wherestate, "btimeto='未还书'");
		strcat(querystate, wherestate);
		size = strlen(querystate);
	
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {
			AfxMessageBox(_T("查询失败"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			if (row != 0) { //出现没还书的情况
				AfxMessageBox(_T("对不起，您该书目未还书，请还书后在进行借书，谢谢！"));
			}
			//AfxMessageBox(_T("数据库连接成功!"));
			else {
				// 查询
				mysql_query(&m_sql1, "SET NAMES 'GB2312'");
				//设置数据库字符格式，解决中文乱码问题
				strcpy(querystate, "insert into borrowinfo values('");
				temp = m_queryDlg4.cardid_text;
				tempstr2 = CT2A(temp);
				if (temp == "") {
					AfxMessageBox(_T("卡号不能为空"));
					return;
				}
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "','");
				//cardid
				temp = m_queryDlg4.bookid_text;
				tempstr2 = CT2A(temp);
				if (temp == "") {
					AfxMessageBox(_T("书号不能为空"));
					return;
				}
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "','");

				SYSTEMTIME st; //定义SYSTEMTIME变量st
				CString strDate, strTime; //定义CString变量strDate和strTime
				GetLocalTime(&st); //获取系统时间到st
				strDate.Format(_T("%4d-%2d-%2d"), st.wYear, st.wMonth, st.wDay); //设置strDate变量的格式为年-月-日
				strTime.Format(_T("%2d:%2d:%2d"), st.wHour, st.wMinute, st.wSecond); //设置strTime变量的格式为时:分:秒
				tempstr2 = CT2A(strDate);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, " ");
				tempstr2 = CT2A(strTime);
				strcat(querystate, tempstr2.c_str());
				strcat(querystate, "','");

				strcat(querystate, "未还书')");
				size = strlen(querystate);
				if (0 != mysql_real_query(&m_sql1, querystate, size)) {
					AfxMessageBox(_T("借书失败（原因之一：未还书）"));
				}
				else {
					mysql_init(&m_sql1);//初始化
					if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
						//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
					{
						AfxMessageBox(_T("数据库连接失败!"));

					}
					else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
					{

						strcpy(querystate, "update bookinfo set ");
						strcat(querystate, "now_store=now_store - 1 where book_id ='");
						temp = m_queryDlg4.bookid_text;
						tempstr2 = CT2A(temp);
						strcat(querystate, tempstr2.c_str());
						strcat(querystate, "'");
						size = strlen(querystate);
						if (0 != mysql_real_query(&m_sql1, querystate, size)) {
							AfxMessageBox(_T("更新失败"));
						}
						else {
							AfxMessageBox(_T("借书成功（更新成功）"));
						}
					}

				}
			}
		}
	}
	

		int row_num = list1.GetItemCount();
		for (int i = 0; i < row_num; i++) {
			list1.DeleteItem(0);
		}

		mysql_init(&m_sql1);//初始化
		if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
			//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
		{
			AfxMessageBox(_T("数据库连接失败!"));

		}
		else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
		{
			//AfxMessageBox(_T("数据库连接成功!"));

			// 查询
			mysql_query(&m_sql1, "SET NAMES 'GB2312'");
			//设置数据库字符格式，解决中文乱码问题
			strcpy(querystate, "select * from bookinfo \0");
			size = strlen(querystate);
			if (0 != mysql_real_query(&m_sql1, querystate, size)) {
				AfxMessageBox(_T("查询失败"));
			}
			else {
				sqlResult = mysql_store_result(&m_sql1);
				//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
				list1row = 0;//遍历行，读取数据
				row = (int)mysql_num_rows(sqlResult);
				field = (int)mysql_num_fields(sqlResult);

				row_test = mysql_fetch_row(sqlResult);
				while (row_test) {

					list1.InsertItem(list1row, _T("")); // 插入行
					for (int i = 0; i < field; i++) { //对于表1 是9列
						CString CS_test(row_test[i]);
						list1.SetItemText(list1row, i + 1, CS_test);
					}
					row_test = mysql_fetch_row(sqlResult);
					list1row++;
				}
			}
			/*

			*/
		}

		// TODO: 在此添加控件通知处理程序代码
}

void CMFCexp05Dlg::OnBnClickedbookback()
{
	mysql_init(&m_sql1);//初始化
	char querystate[200];
	char wherestate[200];
	int flag = 0;
	int size;
	std::string tempstr1;
	CString temp;
	std::string tempstr2;


	MYSQL_RES *sqlResult = NULL;
	int list1row;
	int row;
	int field;
	MYSQL_ROW row_test;

	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//同一本书同一个人只能借用一次,
		//且必须等还书后才能续借。

		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from  borrowinfo ");
		strcpy(wherestate, " where ");
		temp = m_queryDlg4.cardid_text;
		tempstr2 = CT2A(temp);
		if (temp == "") {
			AfxMessageBox(_T("卡号不能为空"));
			return;
		}
		strcat(wherestate, " card_id='");
		strcat(wherestate, tempstr2.c_str());
		strcat(wherestate, "' and ");
		//cardid
		temp = m_queryDlg4.bookid_text;
		tempstr2 = CT2A(temp);
		if (temp == "") {
			AfxMessageBox(_T("书号不能为空"));
			return;
		}
		strcat(wherestate, " book_id='");
		strcat(wherestate, tempstr2.c_str());
		strcat(wherestate, "' and ");

		strcat(wherestate, "btimeto='未还书'");
		strcat(querystate, wherestate);
		size = strlen(querystate);
			if (0 != mysql_real_query(&m_sql1, querystate, size)) {
				AfxMessageBox(_T("查询失败"));
			}
			else {
				sqlResult = mysql_store_result(&m_sql1);
				//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
				list1row = 0;//遍历行，读取数据
				row = (int)mysql_num_rows(sqlResult);
				if (row != 0) {
					strcpy(querystate, "update borrowinfo set btimeto='");
					SYSTEMTIME st; //定义SYSTEMTIME变量st
					CString strDate, strTime; //定义CString变量strDate和strTime
					GetLocalTime(&st); //获取系统时间到st
					strDate.Format(_T("%4d-%2d-%2d"), st.wYear, st.wMonth, st.wDay); //设置strDate变量的格式为年-月-日
					strTime.Format(_T("%2d:%2d:%2d"), st.wHour, st.wMinute, st.wSecond); //设置strTime变量的格式为时:分:秒
					tempstr2 = CT2A(strDate);
					strcat(querystate, tempstr2.c_str());
					strcat(querystate, " ");
					tempstr2 = CT2A(strTime);
					strcat(querystate, tempstr2.c_str());
					strcat(querystate, "' ");

					strcat(querystate, wherestate);
					size = strlen(querystate);
					if (0 != mysql_real_query(&m_sql1, querystate, size)) {
						AfxMessageBox(_T("还书失败（多种错误原因）"));
					}
					else {
						//还书
					//update bookinfo now_store=now_stor +1 where;

						strcpy(querystate, "update bookinfo set ");
						strcat(querystate, "now_store=now_store + 1 where book_id ='");
						temp = m_queryDlg4.bookid_text;
						tempstr2 = CT2A(temp);
						strcat(querystate, tempstr2.c_str());
						strcat(querystate, "'");
						size = strlen(querystate);
						if (0 != mysql_real_query(&m_sql1, querystate, size)) {
							AfxMessageBox(_T("更新bookinfo失败"));
						}
						else {
							AfxMessageBox(_T("还书成功"));
						}
					}
				}
				else {
					AfxMessageBox(_T("系统bug，出现还书却没借书的情况"));
				}
			}
		
	}

	int row_num = list1.GetItemCount();
	for (int i = 0; i < row_num; i++) {
		list1.DeleteItem(0);
	}

	mysql_init(&m_sql1);//初始化
	if (!mysql_real_connect(&m_sql1, "localhost", "root", "liuzhendong0.", "lms", 3306, NULL, 0))
		//localhost:服务器地址，可以直接填入IP;root:账号;liuzhedonong0.:密码;lms:数据库名;3306:网络端口
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		// 查询
		mysql_query(&m_sql1, "SET NAMES 'GB2312'");
		//设置数据库字符格式，解决中文乱码问题
		strcpy(querystate, "select * from bookinfo \0");
		size = strlen(querystate);
		if (0 != mysql_real_query(&m_sql1, querystate, size)) {
			AfxMessageBox(_T("查询失败"));
		}
		else {
			sqlResult = mysql_store_result(&m_sql1);
			//MYSQL_FIELD* fieldArray = mysql_fetch_field(sqlResult);
			list1row = 0;//遍历行，读取数据
			row = (int)mysql_num_rows(sqlResult);
			field = (int)mysql_num_fields(sqlResult);

			row_test = mysql_fetch_row(sqlResult);
			while (row_test) {

				list1.InsertItem(list1row, _T("")); // 插入行
				for (int i = 0; i < field; i++) { //对于表1 是9列
					CString CS_test(row_test[i]);
					list1.SetItemText(list1row, i + 1, CS_test);
				}
				row_test = mysql_fetch_row(sqlResult);
				list1row++;
			}
		}
		/*

		*/
	}
	// TODO: 在此添加控件通知处理程序代码
}
