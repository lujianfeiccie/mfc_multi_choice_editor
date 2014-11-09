#include "StdAfx.h"
#include "BaseDlg.h"
#include "Resource.h"

UINT indicators_base_dlg[]={
IDS_STRING_STATUS
};


IMPLEMENT_DYNAMIC(CBaseDlg, CDialogEx)

void CBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBaseDlg, CDialogEx)	
	ON_MESSAGE(WM_MSG_STATUS,&CBaseDlg::OnMessageReceive)
	ON_WM_DROPFILES()
	ON_WM_SIZING()
END_MESSAGE_MAP()

CBaseDlg::CBaseDlg(UINT nIDTemplate, CWnd *pParent):CDialogEx(nIDTemplate,pParent)
{
	m_oper_type = OperationType::Normal;
	m_current_index = 0;
}


CBaseDlg::~CBaseDlg(void)
{
}


BOOL CBaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!m_statusbar_status.Create(this) ||
        !m_statusbar_status.SetIndicators(indicators_base_dlg,sizeof(indicators_base_dlg)/sizeof(UINT))
        )
	{
		   TRACE0("Failed to create status bar\n");
		   return -1;      // fail to create
	}
	m_statusbar_status.SetPaneInfo(0,indicators_base_dlg[0],SBPS_STRETCH,400);	
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,AFX_IDW_CONTROLBAR_FIRST);

	ModifyStyleEx(0,WS_EX_APPWINDOW);
	DragAcceptFiles();

	setEnable(FALSE);

	 
	return TRUE;
}

void CBaseDlg::SendMessageStatus(MSG_TYPE type,CString msg)
{
	SendMessage(WM_MSG_STATUS,type,(LPARAM)msg.GetBuffer());
	msg.ReleaseBuffer();
}
LONG CBaseDlg::OnMessageReceive(WPARAM wParam,LPARAM lParam)
{
	CString msg = (TCHAR*)lParam;
	switch(wParam)
	{	
	case MSG_TYPE::MSG_Processing:
		{
			m_statusbar_status.SetPaneText(0,L"进行中");
			setEnable(FALSE);
		}
		break;
	case MSG_TYPE::MSG_Finish:
		{
			setEnable(TRUE);

			m_statusbar_status.SetPaneText(0,L"完成");
			MessageBox(L"成功",L"提示");

		}
		break;
	case MSG_TYPE::MSG_Loading:
		{
		    m_statusbar_status.SetPaneText(0,L"处理中");
			setEnable(FALSE);
		}
		break;	
	case MSG_TYPE::MSG_Other:
		{
			m_statusbar_status.SetPaneText(0,msg);
		}
		break;
	}	
	return 0;
}

void CBaseDlg::OnDropFiles(HDROP hDropInfo)
{
	//Util::LOG(L"OnDropFiles");
	TCHAR FileName[512];
	memset(FileName,0,512 * sizeof(TCHAR));
    UINT nChars= ::DragQueryFile( hDropInfo, 0 ,FileName , 512 * sizeof( TCHAR ) );

	m_strFileName = FileName;
	OnDropFilesEx();
    ::DragFinish( hDropInfo ); 
}


BOOL CBaseDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_KEYDOWN)
	{

	}
	else
	if (pMsg->message==WM_KEYUP)
	{
	BOOL bCtrl=::GetKeyState(VK_CONTROL)&0x8000;
	BOOL bShift=::GetKeyState(VK_SHIFT)&0x8000;

	// only gets here if CTRL key is pressed
	BOOL bAlt=::GetKeyState(VK_MENU)&0x8000;
		switch( pMsg->wParam )
		{

			case 'A':
			if (bCtrl)
			{
				OnSelectAllByHotkey();
			}			
			break;
			case 'N':
			if (bCtrl)
			{
				OnMenuNewByHotkey();
			}
			break;
			case 'S':
			if (bCtrl)
			{
				OnMenuSaveByHotkey();
			}
			break;
			case 'O':
			if (bCtrl)
			{
				OnMenuOpenByHotkey();
			}
			break;
			case VK_LEFT:
			if (bCtrl)
			{
				OnLeftByHotKey();
			}
			break;
			case VK_RIGHT:
			if (bCtrl)
			{
				OnRightByHotKey();
			}
			break;
		}
		
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}

void CBaseDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
	//Util::LOG(L"sizeing");
	CRect rect = CRect(pRect);
	ScreenToClient(rect);
	//Util::LOG(L"(%d,%d) (%d,%d)",rect.left,rect.top,rect.right,rect.bottom);	
	CRect rect_status = Util::getControlPosition(m_statusbar_status,this);
	//For statusbar
	Util::setControlPosition(m_statusbar_status,this,0,rect.bottom - rect_status.Height()-10);

	OnSizingEx(rect);
}
void CBaseDlg::OnSizingEx(CRect Rect)
{

}