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
CEdit* CControlTool::CreateEdit(int nID,CRect rect,CWnd* context,BOOL isImage)
{
	CEdit *p_Edit = new CEdit();
	ASSERT_VALID(p_Edit);
	if(isImage)
	{
	    p_Edit->Create( WS_CHILD | WS_VISIBLE , rect, context, nID ); //创建按钮
	}
	else
	{
		p_Edit->Create( WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_WANTRETURN | ES_MULTILINE, rect, context, nID ); //创建按钮
	}
	return p_Edit;
}
CStatic* CControlTool::CreateStatic(int nID,CRect rect,CWnd* context)
{
	CStatic *p_Static = new CStatic();
	ASSERT_VALID(p_Static);
	p_Static->Create(L"",WS_CHILD | WS_VISIBLE,rect,context,nID);
	return p_Static;
}