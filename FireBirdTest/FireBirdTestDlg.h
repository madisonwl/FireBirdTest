
// FireBirdTestDlg.h : 头文件
//
#include"../ibpp-core/ibpp.h"
#pragma once


// CFireBirdTestDlg 对话框
class CFireBirdTestDlg : public CDialogEx
{
// 构造
public:
	CFireBirdTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FIREBIRDTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	//IBPP::Database db;
// 实现
public:
	IBPP::Database db;      //数据库实例
	IBPP::Transaction tr;   //事务：Transaction实例，进行事务管理
	IBPP::Statement st;     //Statement实例，用于执行SQL指令
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCreate();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonWrite();
	afx_msg void OnBnClickedButtonRead();
};
