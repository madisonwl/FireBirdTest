
// FireBirdTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFireBirdTestApp: 
// �йش����ʵ�֣������ FireBirdTest.cpp
//

class CFireBirdTestApp : public CWinApp
{
public:
	CFireBirdTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFireBirdTestApp theApp;