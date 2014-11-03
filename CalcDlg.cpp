// CalcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Multi_Choice.h"
#include "CalcDlg.h"
#include "afxdialogex.h"
#include "ControlTool.h"
UINT indicators_calc_dlg[]={
IDS_STRING_STATUS
};


// CCalcDlg 对话框

IMPLEMENT_DYNAMIC(CCalcDlg, CDialogEx)

CCalcDlg::CCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalcDlg::IDD, pParent)
{

}

CCalcDlg::~CCalcDlg()
{
}

void CCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCalcDlg, CDialogEx)
	ON_COMMAND_RANGE(2200,2210,OnBtnClick)
	ON_CONTROL_RANGE(EN_CHANGE,2211,2222,OnEditChange)
END_MESSAGE_MAP()


// CCalcDlg 消息处理程序

BOOL CCalcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO: 在此添加额外的初始化代码
	if (!m_statusbar_status.Create(this) ||
        !m_statusbar_status.SetIndicators(indicators_calc_dlg,sizeof(indicators_calc_dlg)/sizeof(UINT))
        )
	{
		   TRACE0("Failed to create status bar\n");
		   return -1;      // fail to create
	}
	m_statusbar_status.SetPaneInfo(0,indicators_calc_dlg[0],SBPS_STRETCH,400);	
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,AFX_IDW_CONTROLBAR_FIRST);

	setEnable(FALSE);
	m_oper_type = OperationType::Normal;
	m_current_index = 0;
	SetWindowTextW(L"计算题编辑器");
	ModifyStyleEx(0,WS_EX_APPWINDOW);

	CControlTool::CreateButton(2200,L"你牛逼",CRect(100,100,100+100,100+50),this);
	CControlTool::CreateButton(2201,L"你厉害",CRect(100,200,100+100,200+50),this);
	CEdit *edit = CControlTool::CreateEdit(2211,CRect(100,300,100+100,300+50),this);	
	return TRUE;
}
void CCalcDlg::setEnable(BOOL enable)
{

}

void CCalcDlg::OnBtnClick(UINT nCmdID)
{
	Util::LOG(L"id=%d",nCmdID);
}
void CCalcDlg::OnEditChange(UINT ID)
{
	Util::LOG(L"edit id=%d",ID);
}
BOOL CCalcDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}
