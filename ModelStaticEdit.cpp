#include "StdAfx.h"
#include "ModelStaticEdit.h"


CModelStaticEdit::CModelStaticEdit(void)
{

}


CModelStaticEdit::~CModelStaticEdit(void)
{
	if(m_edit!=NULL)
	{
	  delete m_edit;
	}
	if(m_static != NULL)
	{
		delete m_static;
	}
}
