// AskAnswerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Multi_Choice.h"
#include "AskAnswerDlg.h"
#include "afxdialogex.h"

// CAskAnswerDlg �Ի���

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
// CAskAnswerDlg ��Ϣ�������

BOOL CAskAnswerDlg::OnInitDialog()
{
	CBaseDlg::OnInitDialog();
	SetWindowTextW(L"�����༭��");
	return TRUE;
}

void CAskAnswerDlg::OnMenuNew()
{
	// TODO: �ڴ���������������
	if(m_oper_type == OperationType::New || m_oper_type == OperationType::Load)
	{
		switch(MessageBox(L"��Ҫ����֮ǰ�ĸ���?",L"��ʾ",MB_YESNOCANCEL))
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
	SetWindowTextW(L"�½������");
	m_current_index = 0;
	m_list.clear();
	OnBnClickedBtnNew();	   
	m_oper_type = OperationType::New;
	setEnable(TRUE); 
}


void CAskAnswerDlg::OnMenuOpen()
{
	// TODO: �ڴ���������������
		// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	
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
	
	// TODO: �ڴ���������������
	if(m_oper_type == OperationType::New)
	{
		if(IDOK == MessageBox(L"��Ҫ����ղŵĸ���?",L"��ʾ",MB_OKCANCEL))
		{
			OnMenuSave();
		}
	}
	CDialog::OnCancel();
}


void CAskAnswerDlg::OnBnClickedBtnPrev()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Util::LOG(L"OnBnClickedBtnNew");
	CModelAskAnswer* model = new CModelAskAnswer;
	m_list.push_back(model);
	m_current_index = m_list.size()-1;
	updateQuestionUI();
	m_edit_question.SetFocus();
}


void CAskAnswerDlg::OnBnClickedBtnDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_list.size()==1)
	{
       MessageBox(L"��СΪ1,����ɾ��!");
	   return;
	}
	if(IDOK == MessageBox(L"ȷ��ɾ��?",L"��ʾ",MB_OKCANCEL))
	{
	vector<CModelAskAnswer*>::iterator it = m_list.begin()+m_current_index;
	
	m_list.erase(it);	

	updateQuestionUI();
	}
}


void CAskAnswerDlg::OnBnClickedBtnNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CModelAskAnswer* model = (CModelAskAnswer*)m_list[m_current_index];
	CString title;
	m_edit_question.GetWindowTextW(title);
	model->m_ask = title;
}


void CAskAnswerDlg::OnEnChangeEditAnswer()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(L"��ʽ����");
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