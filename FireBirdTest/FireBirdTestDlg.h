
// FireBirdTestDlg.h : ͷ�ļ�
//
#include"../ibpp-core/ibpp.h"
#pragma once


// CFireBirdTestDlg �Ի���
class CFireBirdTestDlg : public CDialogEx
{
// ����
public:
	CFireBirdTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FIREBIRDTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	//IBPP::Database db;
// ʵ��
public:
	IBPP::Database db;      //���ݿ�ʵ��
	IBPP::Transaction tr;   //����Transactionʵ���������������
	IBPP::Statement st;     //Statementʵ��������ִ��SQLָ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
