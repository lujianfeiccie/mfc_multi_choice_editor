#pragma once
class CBaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaseDlg)
public:
	CBaseDlg(UINT nIDTemplate, CWnd *pParent = NULL);
	virtual ~CBaseDlg(void);
	BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö
	DECLARE_MESSAGE_MAP()
	CStatusBar m_statusbar_status;

public:
	OperationType m_oper_type;
	int m_current_index;	
	CString m_strFileName;

	

	void SendMessageStatus(MSG_TYPE type,CString msg=L"");
	LONG OnMessageReceive(WPARAM wParam,LPARAM lParam);

	void OnDropFiles(HDROP hDropInfo);

	BOOL PreTranslateMessage(MSG* pMsg);
	virtual void updateQuestionUI()=0;
	virtual void setEnable(BOOL enable)=0;
	virtual void OnDropFilesEx()=0;
	virtual void OnMenuNewByHotkey()=0;
	virtual void OnMenuOpenByHotkey()=0;
	virtual void OnMenuSaveByHotkey()=0;
	virtual void OnSelectAllByHotkey()=0;
	virtual void OnLeftByHotKey()=0;
	virtual void OnRightByHotKey()=0;
};

