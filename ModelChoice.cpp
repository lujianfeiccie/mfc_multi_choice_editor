#include "StdAfx.h"
#include "ModelChoice.h"


CModelChoice::CModelChoice(void)
{
	m_answer=L"";
	m_note = L"";
	m_title = L"";
	for(int i=0;i<4;i++) m_choices[i]=L"";
}


CModelChoice::~CModelChoice(void)
{
}
