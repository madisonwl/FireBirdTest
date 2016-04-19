
// FireBirdTestDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFireBirdTestDlg �Ի���



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


// CFireBirdTestDlg ��Ϣ�������

BOOL CFireBirdTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFireBirdTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFireBirdTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

const char* g_szDBName = "d:\\test.fdb";
//������������Է������汾������Ƕ��ʽ����Ӧ����""
const char* g_szServerName = "";

//������û�����������FireBirdĬ��ֵ�����ڷ������棬�����Լ�������
//����Ƕ��ʽ�����������FireBirdǶ��ʽ��û�м��ܹ��ܣ���
const char* g_szUserName = "SYSDBA";
const char* g_szPassword = "masterkey";

void CFireBirdTestDlg::OnBnClickedButtonCreate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	db = IBPP::DatabaseFactory(g_szServerName, g_szDBName, g_szUserName, g_szPassword);
	//�������ݿ�
	db->Create(3);
}


void CFireBirdTestDlg::OnBnClickedButtonConnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�������ݿ�
	db->Connect();
}


void CFireBirdTestDlg::OnBnClickedButtonWrite()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tr = IBPP::TransactionFactory(db);  //��������
	tr->Start(); //��ʼ����
	try
	{
		st = IBPP::StatementFactory(db, tr);
		//�������ݱ�
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
		//��������,������Сǿ
		st->Execute(
			"INSERT INTO TESTTABLE(ID,RNO,SHIFT,LINE,EMP)"
			"VALUES(1,'B9527','B','DAZHA','Hua,An')"
			);
		st->Execute(
			"INSERT INTO TESTTABLE(ID,RNO,SHIFT,LINE,EMP)"
			"VALUES(2,'B9528','B','ZHUANGSI','Xiao,Qiang')"
			);

		tr->CommitRetain();
		//��������,ʯ���ף֦ɽ
		st->Execute(
			"INSERT INTO TESTTABLE(ID,RNO,SHIFT,LINE,EMP)"
			"VALUES(3,'B9525','A','DAZHA','Shi,Liu')"
			);
		//SHIFTֻ����ABCD������дX����ʲô�������
		/*st->Execute(
			"INSERT INTO TESTTABLE(ID,RNO,SHIFT,LINE,EMP)"
			"VALUES(4,'B9526','X','DAZHA','Zhu,ZiShang')"
			);*/
		tr->Commit();  //�ύ����
	}
	catch (IBPP::SQLException &e)
	{
		//cerr << e.what() << endl;
		tr->Rollback();  //��������
	}

	
}


void CFireBirdTestDlg::OnBnClickedButtonRead()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tr->Start();
	try
	{
		//IBPP::Statement st = IBPP::StatementFactory(db, tr);
		st->Execute("SELECT RNO, EMP FROM TESTTABLE");
		//��ʾSELECT�õ�������
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
