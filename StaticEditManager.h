#pragma once
#include "ModelStaticEdit.h"
#include <vector>
using namespace std;
class CStaticEditManager
{
public:
	CStaticEditManager(CWnd* context);
	~CStaticEditManager(void);	
	void add(TYPE type,TAG tag);
	void remove();
	int m_left;
	int m_top;
	int size();
	int m_max_height;
	int m_id_start;
	CModelStaticEdit* at(int index);
	vector<CModelStaticEdit*> getList();
	void clear();
private:
	vector<CModelStaticEdit*> m_list;
	CWnd* context;	
};

