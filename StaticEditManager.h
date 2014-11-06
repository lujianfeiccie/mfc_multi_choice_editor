#pragma once
#include "ModelStaticEdit.h"
#include <vector>
using namespace std;
class CStaticEditManager
{
public:
	CStaticEditManager(CWnd* context);
	~CStaticEditManager(void);
	vector<CModelStaticEdit*> m_list;
	void add(TYPE type,TAG tag);
	void remove();
	int m_left;
	int m_top;
private:
	CWnd* context;
};

