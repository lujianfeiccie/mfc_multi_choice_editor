
// Multi_Choice.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMulti_ChoiceApp:
// �йش����ʵ�֣������ Multi_Choice.cpp
//

class CMulti_ChoiceApp : public CWinApp
{
public:
	CMulti_ChoiceApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMulti_ChoiceApp theApp;