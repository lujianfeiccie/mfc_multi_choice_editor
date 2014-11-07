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
	m_static_edit_manager = new CStaticEditManager(this);
	m_static_edit_manager->m_left = 10;
	m_static_edit_manager->m_top  = 10;
}

CCalcDlg::~CCalcDlg()
{
	delete m_static_edit_manager;
}

void CCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_QUESTION, m_radio_question);
	DDX_Control(pDX, IDC_RADIO_ANSWER, m_radio_answer);
	DDX_Control(pDX, IDC_RADIO_TEXT, m_radio_text);
	DDX_Control(pDX, IDC_RADIO_IMAGE, m_radio_image);
}


BEGIN_MESSAGE_MAP(CCalcDlg, CDialogEx)
	ON_COMMAND_RANGE(2200,2210,OnBtnClick)
	ON_CONTROL_RANGE(EN_CHANGE,2211,2222,OnEditChange)
	ON_BN_CLICKED(IDC_BTN_ADD, &CCalcDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CCalcDlg::OnBnClickedBtnDel)
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

	////CControlTool::CreateButton(2200,L"你牛逼",CRect(100,100,100+100,100+50),this);
	//CControlTool::CreateButton(2201,L"你厉害",CRect(100,200,100+100,200+50),this);
	//CEdit *edit = CControlTool::CreateEdit(2211,CRect(100,300,100+100,300+50),this);	
	

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
	if (pMsg->message==WM_KEYDOWN)
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
				for(int i=0;i<m_static_edit_manager->size();i++)
				{
					m_static_edit_manager->at(i)->m_edit->SetSel(0,-1);
				}
			}			
			break;
		}
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}
void CCalcDlg::OnOK()
{
 return;
}

void CCalcDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	TYPE type;
	if(m_radio_text.GetCheck())
	{
		type = TYPE::TYPE_TEXT;
	}
	else
	{
		type = TYPE::TYPE_IMAGE;
	}
	TAG tag;
	if(m_radio_question.GetCheck())
	{
		tag = TAG::TAG_QUESTION;
	}
	else
	{
		tag = TAG::TAG_ANSWER;
	}
	m_static_edit_manager->add(type,tag);
}


void CCalcDlg::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_static_edit_manager->remove();
}
