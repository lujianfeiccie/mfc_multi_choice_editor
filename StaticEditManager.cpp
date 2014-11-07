#include "StdAfx.h"
#include "StaticEditManager.h"
#include "ControlTool.h"

CStaticEditManager::CStaticEditManager(CWnd* context)
{
	this->context = context;
	m_left = 0;
	m_top = 0;
	this->m_max_height =0;
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
	int height_interval = 10;

	int width_for_static = 70;
	int height_for_static = 70;

	int width_for_edit = 500;
	int height_for_edit = 70;
	int height_for_edit_image = 50;
	
		

	CStatic* cstatic = NULL;

	CEdit* edit = NULL;
	
	switch(type)
	{
	case TYPE::TYPE_IMAGE:
		{
		 cstatic = CControlTool::CreateStatic(0,
			 CRect(m_left,m_max_height+height_interval,
		m_left+width_for_static, m_max_height+height_interval+height_for_edit_image),
		context);

		 CRect rect;
		cstatic->GetWindowRect(rect);
		context->ScreenToClient(rect);
		 cstatic->SetWindowTextW(L"Í¼Æ¬");

		 edit = CControlTool::CreateEdit(m_list.size(),
		CRect(rect.right,rect.top,rect.right+width_for_edit, rect.bottom),
		context);

		 m_max_height =rect.bottom;
		}
		break;
	case TYPE::TYPE_TEXT:
		{
		cstatic = CControlTool::CreateStatic(0,
			 CRect(m_left,m_max_height+height_interval,
		m_left+width_for_static, m_max_height+height_interval+height_for_edit),
		context);

		CRect rect;
		cstatic->GetWindowRect(rect);
		context->ScreenToClient(rect);

		cstatic->SetWindowTextW(L"ÎÄ×Ö");

		edit = CControlTool::CreateEdit(m_list.size(),
			CRect(rect.right,rect.top,
			rect.right+width_for_edit, rect.bottom),
		context);
		
		m_max_height = rect.bottom;
		}
		break;
	}
	

	
	CModelStaticEdit* model = new CModelStaticEdit;
	model->m_type = type;
	model->m_tag = tag;
	model->m_edit = edit;
	model->m_static = cstatic;
	m_list.push_back(model);
}
void CStaticEditManager::remove()
{
	if(m_list.size()>1){
		CModelStaticEdit* model = m_list[m_list.size()-1];		
		CRect rect;
		model->m_edit->GetWindowRect(rect);
		context->ScreenToClient(rect);
		//Util::LOG(L"max_height=%d",rect.bottom);
		model->m_edit->DestroyWindow();
		model->m_static->DestroyWindow();
		delete model;

		CModelStaticEdit* model_pre = m_list[m_list.size()-2];
		
		model_pre->m_edit->GetWindowRect(rect);
		context->ScreenToClient(rect);
		m_max_height = rect.bottom;
		//Util::LOG(L"pre max_height=%d",rect.bottom);
		m_list.pop_back();		
	}
}
CModelStaticEdit* CStaticEditManager::at(int index)
{
	return m_list.at(index);
}
int CStaticEditManager::size()
{
	return m_list.size();
}