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
	ON_MESSAGE(WM_MSG_STATUS,&CAskAnswerDlg::OnMessageReceive)
	ON_EN_CHANGE(IDC_EDIT_QUESTION, &CAskAnswerDlg::OnEnChangeEditQuestion)
	ON_EN_CHANGE(IDC_EDIT_ANSWER, &CAskAnswerDlg::OnEnChangeEditAnswer)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


UINT ThreadSaveInAskAnswer(LPVOID lPvoid)
{
	CAskAnswerDlg* dlg = (CAskAnswerDlg*)lPvoid;

	dlg->m_oper_type = OperationType::Save;
	CMarkup xml;	
	xml.SetDoc(L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
	xml.AddElem(L"root");

	xml.IntoElem();

	int size = dlg->m_list.size();

	for(int i=0;i<size;i++)
	{
	CModelAskAnswer * model = (CModelAskAnswer*)dlg->m_list[i];

	xml.AddElem(L"question");
	
	CString and;

		xml.IntoElem();;
		xml.AddElem(L"text");
		xml.AddAttrib(L"tag",L"question");
		xml.AddAttrib(L"value",model->m_ask);
		
		xml.AddElem(L"text");
		xml.AddAttrib(L"tag",L"answer");
		
		CString answer = model->m_answer;
		answer.Replace(L"\r\n",L"&#x0A;");
		xml.AddAttrib(L"value",answer);
		//Util::LOG(L"answer=%s",model->m_answer);
		xml.OutOfElem();	

	}

	xml.OutOfElem();
	
	CString result = xml.GetDoc();
	result.Replace(L"amp;",L"");
	xml.SetDoc(result);
	xml.Save(dlg->m_strFileName);
	dlg->SendMessageStatus(MSG_TYPE::MSG_Finish);
	//Util::LOG(L"%s",xml.GetDoc());	
return 0;
}
LONG CAskAnswerDlg::OnMessageReceive(WPARAM wParam,LPARAM lParam)
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
	SetWindowTextW(L"简答题编辑器");
	ModifyStyleEx(0,WS_EX_APPWINDOW);
	return TRUE;
}
BOOL CAskAnswerDlg::PreTranslateMessage(MSG* pMsg)
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
				m_edit_question.SetSel(0,-1);
				m_edit_answer.SetSel(0,-1);				
			}			
			break;
			case 'N':
			if (bCtrl)
			{
				OnMenuNew();
			}
			break;
			case 'S':
			if (bCtrl)
			{
				OnMenuSave();
			}
			break;
			case 'O':
			if (bCtrl)
			{
				OnMenuOpen();
			}
			break;
			/*case 'I':
			{				
			if(bCtrl && bAlt && m_edit_answer.IsWindowEnabled())
			{
				// TODO: 在此添加控件通知处理程序代码
				int start,end;
				m_edit_answer.GetSel(start,end);
				CString content;
	
				if(start == end)
				{
					CString insertStr= L"&#x0A;";
					m_edit_answer.GetWindowTextW(content);
					content.Insert(start,insertStr);
					m_edit_answer.SetWindowTextW(content);
					m_edit_answer.SetSel(start + insertStr.GetLength(),start + insertStr.GetLength());
				}
				OnEnChangeEditAnswer();
			 }
			}
			break;*/
			case VK_LEFT:
			if (bCtrl)
			{
				OnBnClickedBtnPrev();
			}
			break;
			case VK_RIGHT:
			if (bCtrl)
			{
				OnBnClickedBtnNext();
			}
			break;
		}
	}

	if(pMsg->message==WM_KEYDOWN && 
	pMsg->wParam==VK_ESCAPE) return TRUE; 
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
		// TODO: 在此添加命令处理程序代码
	CString strFilter = _T("xml files(*.xml)|*.xml||");
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
		m_strFileName = FileDlg.GetPathName();

	OpenFile();
}


void CAskAnswerDlg::OnMenuSave()
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
	}
	SendMessageStatus(MSG_TYPE::MSG_Processing);
	AfxBeginThread(ThreadSaveInAskAnswer,this);
}

void CAskAnswerDlg::OnDropFiles(HDROP hDropInfo)
{
	//Util::LOG(L"OnDropFiles");
	TCHAR FileName[512];
	memset(FileName,0,512 * sizeof(TCHAR));
    UINT nChars= ::DragQueryFile( hDropInfo, 0 ,FileName , 512 * sizeof( TCHAR ) );

	m_strFileName = FileName;
	OpenFile();
    ::DragFinish( hDropInfo ); 
}
void CAskAnswerDlg::OnMenuExit()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	if(m_oper_type == OperationType::New)
	{
		if(IDOK == MessageBox(L"需要保存刚才的更改?",L"提示",MB_OKCANCEL))
		{
			OnMenuSave();
		}
	}
	CDialog::OnCancel();
}


void CAskAnswerDlg::OnBnClickedBtnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	if( (m_current_index-1) >=0)
	{
		if(m_current_index == m_list.size()-1)
	    {
	      CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	      CString tmp;	
	    }

		--m_current_index;
		updateQuestionUI();
	}
}

void CAskAnswerDlg::updateQuestionUI()
{
	int maxsize = m_list.size();
	if(m_current_index>= maxsize){
		--m_current_index;
	}
	CModelAskAnswer* model = (CModelAskAnswer*)m_list[m_current_index];
	m_edit_question.SetWindowTextW(model->m_ask);
	m_edit_answer.SetWindowTextW(model->m_answer);
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
	m_edit_question.SetFocus();
}


void CAskAnswerDlg::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(IDOK == MessageBox(L"确定删除?",L"提示",MB_OKCANCEL))
	{
	vector<CModelAskAnswer*>::iterator it = m_list.begin()+m_current_index;
	
	m_list.erase(it);	

	updateQuestionUI();
	}
}


void CAskAnswerDlg::OnBnClickedBtnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	int maxsize = m_list.size();
	if( (m_current_index+1) <maxsize)
	{
		++m_current_index;
		updateQuestionUI();
	}
}
void CAskAnswerDlg::SendMessageStatus(MSG_TYPE type,CString msg)
{
	SendMessage(WM_MSG_STATUS,type,(LPARAM)msg.GetBuffer());
	msg.ReleaseBuffer();
}

void CAskAnswerDlg::OnEnChangeEditQuestion()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CModelAskAnswer* model = (CModelAskAnswer*)m_list[m_current_index];
	CString title;
	m_edit_question.GetWindowTextW(title);
	model->m_ask = title;
}


void CAskAnswerDlg::OnEnChangeEditAnswer()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CModelAskAnswer* model = (CModelAskAnswer*)m_list[m_current_index];
	CString answer;
	m_edit_answer.GetWindowTextW(answer);
	//Util::LOG(L"answer=%s",answer);
	model->m_answer = answer;
}
void CAskAnswerDlg::OpenFile()
{
	if(m_strFileName.Right(4)!=L".xml")
	{
		MessageBox(L"格式有误");
		return;
	}	

	
	SetWindowTextW(Util::GetFileNameByPath(m_strFileName));

	SendMessageStatus(MSG_TYPE::MSG_Loading);
	m_oper_type = OperationType::Load;
	setEnable(TRUE);
	
	CMarkup xml;
	BOOL flag = xml.Load(m_strFileName);
	Util::LOG(L"flag=%d",flag);
	 
	xml.FindElem(L"root");
	xml.IntoElem();
	m_list.clear();
	while(xml.FindElem(L"question"))
	{
	  
		xml.IntoElem();			
		xml.ResetMainPos();
		
		CModelAskAnswer *model = new CModelAskAnswer;
		while(xml.FindElem(L"text"))
		{
			CString tag = xml.GetAttrib(L"tag");
			if(tag == L"question")
			{
				model->m_ask = xml.GetAttrib(L"value");
			}
			else
			{
				model->m_answer = xml.GetAttrib(L"value");				
				//Util::LOG(L"length=%d",model->m_answer.GetLength());
				Util::AddReturnFromXml(model->m_answer);				
				//Util::LOG(L"answer=%s",model->m_answer);
			}
			//Util::LOG(L"tag=%s",tag);
		}
		m_list.push_back(model);

		xml.OutOfElem();

	}
	xml.OutOfElem();
	m_current_index = 0;
	updateQuestionUI();
	SendMessageStatus(MSG_TYPE::MSG_Finish);
}

void CAskAnswerDlg::OnOK()
{
 return;
}