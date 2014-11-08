// CalcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Multi_Choice.h"
#include "CalcDlg.h"
#include "afxdialogex.h"
#include "ControlTool.h"

#define EN_CHANGE_START 2000
#define EN_CHANGE_END 2020

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
	m_static_edit_manager->m_id_start = EN_CHANGE_START;
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
	DDX_Control(pDX, IDC_BTN_PREV, m_btn_prev);
	DDX_Control(pDX, IDC_BTN_NEXT, m_btn_next);
	DDX_Control(pDX, IDC_BTN_NEW, m_btn_new);
	DDX_Control(pDX, IDC_BTN_REMOVE, m_btn_remove);
	DDX_Control(pDX, IDC_BTN_ADD, m_btn_add);
	DDX_Control(pDX, IDC_BTN_DEL, m_btn_del);
	DDX_Control(pDX, IDC_STATIC_NO, m_lbl_no);
}


BEGIN_MESSAGE_MAP(CCalcDlg, CDialogEx)	
	ON_CONTROL_RANGE(EN_CHANGE,EN_CHANGE_START,EN_CHANGE_END,OnEditChange)
	ON_BN_CLICKED(IDC_BTN_ADD, &CCalcDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CCalcDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_PREV, &CCalcDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CCalcDlg::OnBnClickedBtnNext)
	ON_BN_CLICKED(IDC_BTN_NEW, &CCalcDlg::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_REMOVE, &CCalcDlg::OnBnClickedBtnRemove)
	ON_COMMAND(ID_32782, &CCalcDlg::OnMenuNew)
	ON_COMMAND(ID_32783, &CCalcDlg::OnMenuOpen)
	ON_COMMAND(ID_32784, &CCalcDlg::OnMenuSave)
	ON_COMMAND(ID_32785, &CCalcDlg::OnMenuExit)
	ON_MESSAGE(WM_MSG_STATUS,&CCalcDlg::OnMessageReceive)
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

	m_radio_question.SetCheck(TRUE);
	m_radio_text.SetCheck(TRUE);
	////CControlTool::CreateButton(2200,L"你牛逼",CRect(100,100,100+100,100+50),this);
	//CControlTool::CreateButton(2201,L"你厉害",CRect(100,200,100+100,200+50),this);
	//CEdit *edit = CControlTool::CreateEdit(2211,CRect(100,300,100+100,300+50),this);	
	OnBnClickedBtnAdd();
	setEnable(FALSE);
	m_oper_type = OperationType::Normal;
	m_current_index = 0;
	SetWindowTextW(L"计算题编辑器");
	ModifyStyleEx(0,WS_EX_APPWINDOW);
	return TRUE;
}
void CCalcDlg::setEnable(BOOL enable)
{
	m_btn_add.EnableWindow(enable);
	m_btn_del.EnableWindow(enable);
	m_btn_new.EnableWindow(enable);
	m_btn_next.EnableWindow(enable);
	m_btn_prev.EnableWindow(enable);
	m_btn_remove.EnableWindow(enable);
	m_radio_answer.EnableWindow(enable);
	m_radio_image.EnableWindow(enable);
	m_radio_question.EnableWindow(enable);
	m_radio_text.EnableWindow(enable);
	
	for(int i=0;i<m_static_edit_manager->size();i++)
	{
		CModelStaticEdit* model = m_static_edit_manager->at(i);
		model->m_edit->EnableWindow(enable);
		model->m_static->EnableWindow(enable);
	}
}

void CCalcDlg::OnEditChange(UINT ID)
{
	
	vector<CModelStaticEdit*> *model=&m_list[m_current_index];
	int index  = ID-EN_CHANGE_START;
	//Util::LOG(L"edit id=%d model size=%d",ID,model->size());
	if(index+1 > model->size())
	{
		CModelStaticEdit* item = new CModelStaticEdit;
		CString text;
		m_static_edit_manager->at(index)->m_edit->GetWindowTextW(text);
		//Util::LOG(L"text=%s",text);
		item->m_value = text;
		item->m_tag = m_static_edit_manager->at(index)->m_tag;
		item->m_type = m_static_edit_manager->at(index)->m_type;
		model->push_back(item);
	}
	else
	{
		CString text;
		m_static_edit_manager->at(index)->m_edit->GetWindowTextW(text);
		//Util::LOG(L"text=%s",text);
		(*model)[index]->m_value = text;
		(*model)[index]->m_tag = m_static_edit_manager->at(index)->m_tag;
		(*model)[index]->m_type = m_static_edit_manager->at(index)->m_type;
	}
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


void CCalcDlg::OnBnClickedBtnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	if( (m_current_index-1) >=0)
	{
		--m_current_index;
		updateQuestionUI();
	}
}


void CCalcDlg::OnBnClickedBtnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	int maxsize = m_list.size();
	if( (m_current_index+1) <maxsize)
	{
		++m_current_index;
		updateQuestionUI();
	}
}


void CCalcDlg::OnBnClickedBtnNew()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<CModelStaticEdit*> model;
	m_list.push_back(model);
	m_current_index = m_list.size()-1;
	updateQuestionUI();
	//m_edit_question.SetFocus();
}


void CCalcDlg::OnBnClickedBtnRemove()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCalcDlg::OnMenuNew()
{
	// TODO: 在此添加命令处理程序代码
	if(m_oper_type == OperationType::New || m_oper_type == OperationType::Load)
	{
		switch(MessageBox(L"需要保存之前的更改?",L"提示",MB_YESNOCANCEL))
		{
		case IDYES:
			{
				Util::LOG(L"Yes");
				OnMenuSave();
			}
			break;
		case IDNO:
			{	
				Util::LOG(L"No");
			}
			break;
		case IDCANCEL:
			{
				Util::LOG(L"Cancel");
			}
			return;
		}
	   
	}	
	Util::LOG(L"OnMenuNew");
	SetWindowTextW(L"新建简答题");
	m_current_index = 0;
	m_list.clear();
	OnBnClickedBtnNew();	   
	m_oper_type = OperationType::New;
	setEnable(TRUE); 
}


void CCalcDlg::OnMenuOpen()
{
	// TODO: 在此添加命令处理程序代码
	CString strFilter = _T("xml files(*.xml)|*.xml||");
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
		m_strFileName = FileDlg.GetPathName();
}


void CCalcDlg::OnMenuSave()
{
	// TODO: 在此添加命令处理程序代码
	if(m_oper_type == OperationType::New)
	{
		CString strFilter = _T("xml files(*.xml)|*.xml||");
		CFileDialog FileDlg(false,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
		if(FileDlg.DoModal()!=IDOK) return;
			m_strFileName = FileDlg.GetPathName();

			CString strFileExt = FileDlg.GetFileExt();
			if(strFileExt == "")
			{
				m_strFileName.Append(L".xml");
			}
			SetWindowTextW(Util::GetFileNameByPath(m_strFileName));
	}
	//SendMessageStatus(MSG_TYPE::MSG_Processing);
	//AfxBeginThread(ThreadSaveInAskAnswer,this);
}


void CCalcDlg::OnMenuExit()
{
	// TODO: 在此添加命令处理程序代码
}
void CCalcDlg::SendMessageStatus(MSG_TYPE type,CString msg)
{
	SendMessage(WM_MSG_STATUS,type,(LPARAM)msg.GetBuffer());
	msg.ReleaseBuffer();
}
LONG CCalcDlg::OnMessageReceive(WPARAM wParam,LPARAM lParam)
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

void CCalcDlg::updateQuestionUI()
{
	int maxsize = m_list.size();	
	if(m_current_index>= maxsize){
		--m_current_index;
	}
	m_static_edit_manager->clear();
	vector<CModelStaticEdit*> model = (vector<CModelStaticEdit*>)m_list[m_current_index];
	
	for(int i=0;i<model.size();i++)
	{		
			m_static_edit_manager->add(model[i]->m_type,model[i]->m_tag);
			m_static_edit_manager->at(i)->m_edit->SetWindowTextW(model[i]->m_value);			
			m_static_edit_manager->at(i)->m_tag = model[i]->m_tag;
			m_static_edit_manager->at(i)->m_type = model[i]->m_type;		
	}

	CString tmp;
	//Util::LOG(L"%d/%d",m_current_index+1,m_list.size());
	tmp.Format(L"%d/%d",m_current_index+1,m_list.size());

	m_lbl_no.SetWindowTextW(tmp);
}