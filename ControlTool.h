#pragma once
class CControlTool
{
public:
	CControlTool(void);
	~CControlTool(void);
	static CButton* CreateButton(int nID,CString text,CRect rect,CWnd* context);
	static CEdit* CreateEdit(int nID,CRect rect,CWnd* context);
};

