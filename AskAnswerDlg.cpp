// AskAnswerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Multi_Choice.h"
#include "AskAnswerDlg.h"
#include "afxdialogex.h"

UINT indicators_ask_answer_dlg[]={
IDS_STRING_STATUS
};


// CAskAnswerDlg 对话框

IMPLEMENT_DYNAMIC(CAskAnswerDlg, CDialogEx)

CAskAnswerDlg::CAskAnswerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAskAnswerDlg::IDD, pParent)
{

}

CAskAnswerDlg::~CAskAnswerDlg()
{
}

void CAskAnswerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_QUESTION, m_edit_question);
	DDX_Control(pDX, IDC_EDIT_ANSWER, m_edit_answer);
	DDX_Control(pDX, IDC_BTN_PREV, m_btn_prev);
	DDX_Control(pDX, IDC_BTN_NEW, m_btn_add);
	DDX_Control(pDX, IDC_BTN_DEL, m_btn_del);
	DDX_Control(pDX, IDC_BTN_NEXT, m_btn_next);
	DDX_Control(pDX, IDC_STATIC_NO, m_lbl_no);
}


BEGIN_MESSAGE_MAP(CAskAnswerDlg, CDialogEx)
	ON_COMMAND(ID__MENU_NEW, &CAskAnswerDlg::OnMenuNew)
	ON_COMMAND(ID_MENU_LOAD, &CAskAnswerDlg::OnMenuOpen)
	ON_COMMAND(ID_MENU_SAVE, &CAskAnswerDlg::OnMenuSave)
	ON_COMMAND(ID__MENU_EXIT, &CAskAnswerDlg::OnMenuExit)
	ON_BN_CLICKED(IDC_BTN_PREV, &CAskAnswerDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEW, &CAskAnswerDlg::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_DEL, &CAskAnswerDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CAskAnswerDlg::OnBnClickedBtnNext)
END_MESSAGE_MAP()


// CAskAnswerDlg 消息处理程序

BOOL CAskAnswerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO: 在此添加额外的初始化代码
	if (!m_statusbar_status.Create(this) ||
        !m_statusbar_status.SetIndicators(indicators_ask_answer_dlg,sizeof(indicators_ask_answer_dlg)/sizeof(UINT))
        )
	{
		   TRACE0("Failed to create status bar\n");
		   return -1;      // fail to create
	}
	m_statusbar_status.SetPaneInfo(0,indicators_ask_answer_dlg[0],SBPS_STRETCH,400);	
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,AFX_IDW_CONTROLBAR_FIRST);

	setEnable(FALSE);
	m_oper_type = OperationType::Normal;
	m_current_index = 0;
	return TRUE;
}
BOOL CAskAnswerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}
void CAskAnswerDlg::setEnable(BOOL enable)
{
	m_edit_question.EnableWindow(enable);
	m_edit_answer.EnableWindow(enable);
	m_btn_prev.EnableWindow(enable);
	m_btn_add.EnableWindow(enable);
	m_btn_del.EnableWindow(enable);
	m_btn_next.EnableWindow(enable);
}
void CAskAnswerDlg::OnMenuNew()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	if(m_oper_type == OperationType::New || m_oper_type == OperationType::Load)
	{
		switch(MessageBox(L"需要保存之前的更改?",L"提示",MB_YESNOCANCEL))
		{
		case IDOK:
			{
				OnMenuSave();
			}
			break;
		case IDNO:
			{
			}
			break;
		case IDCANCEL:
			{
				return;
			}
			break;
		}
	   
	}	
	OnBnClickedBtnNew();	   
	m_oper_type = OperationType::New;
	setEnable(TRUE); 
}


void CAskAnswerDlg::OnMenuOpen()
{
	// TODO: 在此添加命令处理程序代码
}


void CAskAnswerDlg::OnMenuSave()
{
	// TODO: 在此添加命令处理程序代码
}


void CAskAnswerDlg::OnMenuExit()
{
	// TODO: 在此添加命令处理程序代码
}


void CAskAnswerDlg::OnBnClickedBtnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CAskAnswerDlg::updateQuestionUI()
{
	int maxsize = m_list.size();
	if(m_current_index>= maxsize){
		--m_current_index;
	}
	CModelAskAnswer* model = (CModelAskAnswer*)m_list[m_current_index];
	
	CString tmp;
	tmp.Format(L"%d/%d",m_current_index+1,m_list.size());
	m_lbl_no.SetWindowTextW(tmp);
}
void CAskAnswerDlg::OnBnClickedBtnNew()
{
	// TODO: 在此添加控件通知处理程序代码
	CModelAskAnswer* model = new CModelAskAnswer;
	m_list.push_back(model);
	m_current_index = m_list.size()-1;
	updateQuestionUI();
}


void CAskAnswerDlg::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CAskAnswerDlg::OnBnClickedBtnNext()
{
	// TODO: 在此添加控件通知处理程序代码
}
