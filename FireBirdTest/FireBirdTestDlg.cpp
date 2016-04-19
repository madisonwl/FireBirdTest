
// FireBirdTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FireBirdTest.h"
#include "FireBirdTestDlg.h"
#include "afxdialogex.h"

#include <windowsx.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  IBPP_WINDOWS

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFireBirdTestDlg 对话框



CFireBirdTestDlg::CFireBirdTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFireBirdTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFireBirdTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFireBirdTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CFireBirdTestDlg::OnBnClickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CFireBirdTestDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &CFireBirdTestDlg::OnBnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CFireBirdTestDlg::OnBnClickedButtonRead)
END_MESSAGE_MAP()


// CFireBirdTestDlg 消息处理程序

BOOL CFireBirdTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFireBirdTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFireBirdTestDlg::OnPaint()
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
HCURSOR CFireBirdTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

const char* g_szDBName = "d:\\test.fdb";
//服务器名，针对服务器版本。对于嵌入式，它应该是""
const char* g_szServerName = "";

//这里的用户名和密码是FireBird默认值，对于服务器版，用你自己的密码
//对于嵌入式，就是这个（FireBird嵌入式版没有加密功能）。
const char* g_szUserName = "SYSDBA";
const char* g_szPassword = "masterkey";

void CFireBirdTestDlg::OnBnClickedButtonCreate()
{
	// TODO:  在此添加控件通知处理程序代码
	db = IBPP::DatabaseFactory(g_szServerName, g_szDBName, g_szUserName, g_szPassword);
	//建立数据库
	db->Create(3);
}


void CFireBirdTestDlg::OnBnClickedButtonConnect()
{
	// TODO:  在此添加控件通知处理程序代码
	//连接数据库
	db->Connect();
}


void CFireBirdTestDlg::OnBnClickedButtonWrite()
{
	// TODO:  在此添加控件通知处理程序代码
	tr = IBPP::TransactionFactory(db);  //创建事务
	tr->Start(); //开始事务
	try
	{
		st = IBPP::StatementFactory(db, tr);
		//建立数据表
		st->Execute(
			"CREATE TABLE TESTTABLE("
			"    ID INTEGER NOT NULL PRIMARY KEY,"
			"    RNO VARCHAR(10) NOT NULL UNIQUE,"
			"    SHIFT VARCHAR(5) NOT NULL"
			"        CHECK(SHIFT IN('A','B','C','D')),"
			"    LINE CHAR(20) NOT NULL,"
			"    SL COMPUTED BY(SHIFT||'.'||LINE),"
			"    EMP CHAR(20)"
			"    )"
			);
		tr->CommitRetain();
		//插入数据,华安和小强
		st->Execute(
			"INSERT INTO TESTTABLE(ID,RNO,SHIFT,LINE,EMP)"
			"VALUES(1,'B9527','B','DAZHA','Hua,An')"
			);
		st->Execute(
			"INSERT INTO TESTTABLE(ID,RNO,SHIFT,LINE,EMP)"
			"VALUES(2,'B9528','B','ZHUANGSI','Xiao,Qiang')"
			);

		tr->CommitRetain();
		//插入数据,石榴和祝枝山
		st->Execute(
			"INSERT INTO TESTTABLE(ID,RNO,SHIFT,LINE,EMP)"
			"VALUES(3,'B9525','A','DAZHA','Shi,Liu')"
			);
		//SHIFT只能是ABCD，看看写X会有什么情况发生
		/*st->Execute(
			"INSERT INTO TESTTABLE(ID,RNO,SHIFT,LINE,EMP)"
			"VALUES(4,'B9526','X','DAZHA','Zhu,ZiShang')"
			);*/
		tr->Commit();  //提交事务
	}
	catch (IBPP::SQLException &e)
	{
		//cerr << e.what() << endl;
		tr->Rollback();  //撤销事务
	}

	
}


void CFireBirdTestDlg::OnBnClickedButtonRead()
{
	// TODO:  在此添加控件通知处理程序代码
	tr->Start();
	try
	{
		//IBPP::Statement st = IBPP::StatementFactory(db, tr);
		st->Execute("SELECT RNO, EMP FROM TESTTABLE");
		//显示SELECT得到的数据
		while (st->Fetch())
		{
			string rno, emp;
			st->Get("RNO", rno);
			st->Get("EMP", emp);
			//cout << "RNO:" << rno << " EMP:" << emp << endl;
		}
		tr->Commit();
	}
	catch (IBPP::SQLException &e)
	{
		//cerr << e.what() << end
		tr->Rollback();
	}
}
