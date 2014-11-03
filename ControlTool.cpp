#include "StdAfx.h"
#include "ControlTool.h"


CControlTool::CControlTool(void)
{
}


CControlTool::~CControlTool(void)
{
}

CButton* CControlTool::CreateButton(int nID,CString text,CRect rect,CWnd* context)
{
CButton *p_Button = new CButton();
ASSERT_VALID(p_Button);
p_Button->Create( text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect, context, nID ); //创建按钮
return p_Button;
}
CEdit* CControlTool::CreateEdit(int nID,CRect rect,CWnd* context)
{
	CEdit *p_Edit = new CEdit();
	ASSERT_VALID(p_Edit);
	p_Edit->Create( WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect, context, nID ); //创建按钮
	return p_Edit;
}