#include "StdAfx.h"
#include "StaticEditManager.h"
#include "ControlTool.h"

CStaticEditManager::CStaticEditManager(CWnd* context)
{
	this->context = context;
	m_left = 0;
	m_top = 0;
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
	int height_interval = 80;

	int width_for_static = 70;
	int height_for_static = 70;

	int width_for_edit = 500;
	int height_for_edit = 70;
	CStatic* cstatic = CControlTool::CreateStatic(0,CRect(m_left,m_top+m_list.size() * height_interval,
		                         m_left+width_for_static,m_top+m_list.size() * height_interval+height_for_edit),context);
	switch(type)
	{
	case TYPE::TYPE_IMAGE:
		cstatic->SetWindowTextW(L"Í¼Æ¬");
		break;
	case TYPE::TYPE_TEXT:
		cstatic->SetWindowTextW(L"ÎÄ×Ö");
		break;
	}
	

	CRect rect;
	cstatic->GetClientRect(rect);
	Util::LOG(L"left=%ld,top=%ld,right=%ld",rect.left,rect.top,rect.right);
	CEdit* edit = CControlTool::CreateEdit(m_list.size(),
		CRect(rect.right,m_top+m_list.size() * height_interval,
		rect.right+width_for_edit, m_top+m_list.size() * height_interval+height_for_edit),context);
	
	
	CModelStaticEdit* model = new CModelStaticEdit;
	model->m_type = type;
	model->m_tag = tag;
	model->m_edit = edit;
	model->m_static = cstatic;
	m_list.push_back(model);
}
void CStaticEditManager::remove()
{
	if(m_list.size()>0){
		CModelStaticEdit* model = m_list[m_list.size()-1];
		model->m_edit->DestroyWindow();
		model->m_static->DestroyWindow();
		delete model;
		m_list.pop_back();
	}
}
