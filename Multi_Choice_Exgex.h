#pragma once
#include "ModelChoice.h"
#include <vector>
using namespace std;
class CMulti_Choice_Exgex
{
public:
	CMulti_Choice_Exgex(void);
	~CMulti_Choice_Exgex(void);
	void Parse(CString source);
	vector<CModelChoice*> m_list;
};

