#include "StdAfx.h"
#include "StaticEditManager.h"
#include "ControlTool.h"

CStaticEditManager::CStaticEditManager(CWnd* context)
{
	this->context = context;
}


CStaticEditManager::~CStaticEditManager(void)
{
	vector<CModelStaticEdit*>::iterator  it_pos;
    for (it_pos = m_list.begin(); it_pos != m_list.end(); it_pos++) 
	{  
		delete *it_pos;
	}
	m_list.clear();
	context = NULL;
}

void CStaticEditManager::add(TYPE type,TAG tag)
{
	CEdit* edit = CControlTool::CreateEdit(m_list.size(),
		CRect(0,m_list.size() * 100,500,m_list.size() * 100+50),
		context);
	
	CModelStaticEdit* model = new CModelStaticEdit;
	
	model->m_edit = edit;

	m_list.push_back(model);
}
void CStaticEditManager::remove()
{
	if(m_list.size()>0){
		CModelStaticEdit* model = m_list[m_list.size()-1];
		model->m_edit->DestroyWindow();
		delete model;
		m_list.pop_back();
	}
}
