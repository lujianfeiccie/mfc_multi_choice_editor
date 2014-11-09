// AskAnswerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Multi_Choice.h"
#include "AskAnswerDlg.h"
#include "afxdialogex.h"

// CAskAnswerDlg 对话框

IMPLEMENT_DYNAMIC(CAskAnswerDlg, CBaseDlg)

CAskAnswerDlg::CAskAnswerDlg(CWnd* pParent /*=NULL*/)
	: CBaseDlg(CAskAnswerDlg::IDD, pParent)
{

}

CAskAnswerDlg::~CAskAnswerDlg()
{
}

void CAskAnswerDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_QUESTION, m_edit_question);
	DDX_Control(pDX, IDC_EDIT_ANSWER, m_edit_answer);
	DDX_Control(pDX, IDC_BTN_PREV, m_btn_prev);
	DDX_Control(pDX, IDC_BTN_NEW, m_btn_add);
	DDX_Control(pDX, IDC_BTN_DEL, m_btn_del);
	DDX_Control(pDX, IDC_BTN_NEXT, m_btn_next);
	DDX_Control(pDX, IDC_STATIC_NO, m_lbl_no);
}


BEGIN_MESSAGE_MAP(CAskAnswerDlg, CBaseDlg)
	ON_COMMAND(ID__MENU_NEW, &CAskAnswerDlg::OnMenuNew)
	ON_COMMAND(ID_MENU_LOAD, &CAskAnswerDlg::OnMenuOpen)
	ON_COMMAND(ID_MENU_SAVE, &CAskAnswerDlg::OnMenuSave)
	ON_COMMAND(ID__MENU_EXIT, &CAskAnswerDlg::OnMenuExit)
	ON_BN_CLICKED(IDC_BTN_PREV, &CAskAnswerDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEW, &CAskAnswerDlg::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_DEL, &CAskAnswerDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CAskAnswerDlg::OnBnClickedBtnNext)
	ON_EN_CHANGE(IDC_EDIT_QUESTION, &CAskAnswerDlg::OnEnChangeEditQuestion)
	ON_EN_CHANGE(IDC_EDIT_ANSWER, &CAskAnswerDlg::OnEnChangeEditAnswer)
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
// CAskAnswerDlg 消息处理程序

BOOL CAskAnswerDlg::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	SetWindowTextW(L"简答题编辑器");
	return TRUE;
}

void CAskAnswerDlg::OnMenuNew()
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
			SetWindowTextW(Util::GetFileNameByPath(m_strFileName));
	}
	SendMessageStatus(MSG_TYPE::MSG_Processing);
	AfxBeginThread(ThreadSaveInAskAnswer,this);
}

void CAskAnswerDlg::OnMenuExit()
{
	
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

void CAskAnswerDlg::OnBnClickedBtnNew()
{
	// TODO: 在此添加控件通知处理程序代码
	Util::LOG(L"OnBnClickedBtnNew");
	CModelAskAnswer* model = new CModelAskAnswer;
	m_list.push_back(model);
	m_current_index = m_list.size()-1;
	updateQuestionUI();
	m_edit_question.SetFocus();
}


void CAskAnswerDlg::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_list.size()==1)
	{
       MessageBox(L"大小为1,不能删除!");
	   return;
	}
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
	Util::LOG(L"OnBnClickedBtnNext");
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
	Util::LOG(L"%d/%d",m_current_index+1,m_list.size());
	tmp.Format(L"%d/%d",m_current_index+1,m_list.size());
	m_lbl_no.SetWindowTextW(tmp);
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
void CAskAnswerDlg::OnDropFilesEx()
{
	OpenFile();
}
void CAskAnswerDlg::OnMenuNewByHotkey()
{
	OnMenuNew();
}
void CAskAnswerDlg::OnMenuOpenByHotkey()
{
	OnMenuOpen();
}
void CAskAnswerDlg::OnMenuSaveByHotkey()
{
	OnMenuSave();
}
void CAskAnswerDlg::OnSelectAllByHotkey()
{
	m_edit_question.SetSel(0,-1);
	m_edit_answer.SetSel(0,-1);	
}
void CAskAnswerDlg::OnLeftByHotKey()
{
	OnBnClickedBtnPrev();
}
void CAskAnswerDlg::OnRightByHotKey()
{
	OnBnClickedBtnNext();
}