
// Multi_ChoiceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Multi_Choice.h"
#include "Multi_ChoiceDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include "NoteEditorDlg.h"
#include "MainDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT indicators_multi_choice_dlg[]={
IDS_STRING_STATUS
};


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_lbl_version;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VERSION, m_lbl_version);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_lbl_version.SetWindowTextW(VERSION);
	return TRUE;
}
// CMulti_ChoiceDlg 对话框




CMulti_ChoiceDlg::CMulti_ChoiceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMulti_ChoiceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMulti_ChoiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_edit_title);
	DDX_Control(pDX, IDC_EDIT_CHOICE1, m_edit_choice1);
	DDX_Control(pDX, IDC_EDIT_CHOICE2, m_edit_choice2);
	DDX_Control(pDX, IDC_EDIT_CHOICE3, m_edit_choice3);
	DDX_Control(pDX, IDC_EDIT_CHOICE4, m_edit_choice4);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_lbl_title);
	DDX_Control(pDX, IDC_STATIC_CHOICE1, m_lbl_choice1);
	DDX_Control(pDX, IDC_STATIC_CHOICE2, m_lbl_choice2);
	DDX_Control(pDX, IDC_STATIC_CHOICE3, m_lbl_choice3);
	DDX_Control(pDX, IDC_STATIC_CHOICE4, m_lbl_choice4);
	DDX_Control(pDX, IDC_BTN_NEXT, m_btn_next);
	DDX_Control(pDX, IDC_BTN_PREV, m_btn_prev);
	DDX_Control(pDX, IDC_RADIO_ANSWER1, m_radio_answer1);
	DDX_Control(pDX, IDC_RADIO_ANSWER2, m_radio_answer2);
	DDX_Control(pDX, IDC_RADIO_ANSWER3, m_radio_answer3);
	DDX_Control(pDX, IDC_RADIO_ANSWER4, m_radio_answer4);
	DDX_Control(pDX, IDC_BTN_NOTE, m_btn_note);
	DDX_Control(pDX, IDC_STATIC_NO, m_lbl_no);
	DDX_Control(pDX, IDC_BTN_NEW, m_btn_new);
	DDX_Control(pDX, IDC_BTN_DEL, m_btn_del);
}


BEGIN_MESSAGE_MAP(CMulti_ChoiceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID__MENU_EXIT, &CMulti_ChoiceDlg::OnMenuExit)	
	ON_COMMAND(ID_MENU_SAVE, &CMulti_ChoiceDlg::OnMenuSave)
	ON_COMMAND(ID_MENU_LOAD, &CMulti_ChoiceDlg::OnMenuLoad)
	ON_BN_CLICKED(IDC_BTN_PREV, &CMulti_ChoiceDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CMulti_ChoiceDlg::OnBnClickedBtnNext)
	ON_BN_CLICKED(IDC_BTN_NOTE, &CMulti_ChoiceDlg::OnBnClickedBtnNote)
	ON_COMMAND(ID__MENU_NEW, &CMulti_ChoiceDlg::OnMenuNew)
	ON_BN_CLICKED(IDC_RADIO_ANSWER1, &CMulti_ChoiceDlg::OnBnClickedRadioAnswer1)
	ON_BN_CLICKED(IDC_RADIO_ANSWER2, &CMulti_ChoiceDlg::OnBnClickedRadioAnswer2)
	ON_BN_CLICKED(IDC_RADIO_ANSWER3, &CMulti_ChoiceDlg::OnBnClickedRadioAnswer3)
	ON_BN_CLICKED(IDC_RADIO_ANSWER4, &CMulti_ChoiceDlg::OnBnClickedRadioAnswer4)
	ON_BN_CLICKED(IDC_BTN_NEW, &CMulti_ChoiceDlg::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_DEL, &CMulti_ChoiceDlg::OnBnClickedBtnDel)
	ON_EN_CHANGE(IDC_EDIT_TITLE, &CMulti_ChoiceDlg::OnEnChangeEditTitle)
	ON_EN_CHANGE(IDC_EDIT_CHOICE1, &CMulti_ChoiceDlg::OnEnChangeEditChoice1)
	ON_EN_CHANGE(IDC_EDIT_CHOICE2, &CMulti_ChoiceDlg::OnEnChangeEditChoice2)
	ON_EN_CHANGE(IDC_EDIT_CHOICE3, &CMulti_ChoiceDlg::OnEnChangeEditChoice3)
	ON_EN_CHANGE(IDC_EDIT_CHOICE4, &CMulti_ChoiceDlg::OnEnChangeEditChoice4)
	ON_MESSAGE(WM_MSG_STATUS,&CMulti_ChoiceDlg::OnMessageReceive)
	ON_WM_CLOSE()	
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMulti_ChoiceDlg 消息处理程序

BOOL CMulti_ChoiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if (!m_statusbar_status.Create(this) ||
        !m_statusbar_status.SetIndicators(indicators_multi_choice_dlg,sizeof(indicators_multi_choice_dlg)/sizeof(UINT))
        )
	{
		   TRACE0("Failed to create status bar\n");
		   return -1;      // fail to create
	}
	m_statusbar_status.SetPaneInfo(0,indicators_multi_choice_dlg[0],SBPS_STRETCH,400);	
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,AFX_IDW_CONTROLBAR_FIRST);

	
	CRect rect_edit_title = Util::getControlPosition(m_edit_title,this);
	CRect rect_lbl_title = Util::getControlPosition(m_lbl_title,this);
	Util::setControlPosition(m_lbl_title,this,rect_lbl_title.left,rect_edit_title.top);
	m_lbl_no.SetWindowTextW(L"");
	Util::setControlPosition(m_lbl_no,this,rect_lbl_title.left,rect_lbl_title.bottom+10);

	CRect rect_choice;
	//Choice1
	Util::setControlPosition(m_edit_choice1,this,rect_edit_title.left,rect_edit_title.bottom+INTERVAL_CHOICE);	
	rect_choice = Util::getControlPosition(m_edit_choice1,this);

	Util::setControlPosition(m_lbl_choice1,this,rect_lbl_title.left,rect_choice.top);
	//Answer
	Util::setControlPosition(m_radio_answer1,this,rect_choice.right+INTERVAL_ANSWER,rect_choice.top);

	//Choice2
	Util::setControlPosition(m_edit_choice2,this,rect_edit_title.left,rect_choice.bottom+INTERVAL_CHOICE);	
	rect_choice = Util::getControlPosition(m_edit_choice2,this);
	Util::setControlPosition(m_lbl_choice2,this,rect_lbl_title.left,rect_choice.top);
	//Answer
	Util::setControlPosition(m_radio_answer2,this,rect_choice.right+INTERVAL_ANSWER,rect_choice.top);
	
	//Choice3
	Util::setControlPosition(m_edit_choice3,this,rect_edit_title.left,rect_choice.bottom+INTERVAL_CHOICE);	
	rect_choice = Util::getControlPosition(m_edit_choice3,this);
	Util::setControlPosition(m_lbl_choice3,this,rect_lbl_title.left,rect_choice.top);
	//Answer
	Util::setControlPosition(m_radio_answer3,this,rect_choice.right+INTERVAL_ANSWER,rect_choice.top);

	//Choice4
	Util::setControlPosition(m_edit_choice4,this,rect_edit_title.left,rect_choice.bottom+INTERVAL_CHOICE);	
	rect_choice = Util::getControlPosition(m_edit_choice4,this);
	Util::setControlPosition(m_lbl_choice4,this,rect_lbl_title.left,rect_choice.top);
	//Answer
	Util::setControlPosition(m_radio_answer4,this,rect_choice.right+INTERVAL_ANSWER,rect_choice.top);
	//Prev Button
	Util::setControlPosition(m_btn_prev,this,0,rect_choice.bottom+INTERVAL_CHOICE);	

	//New Button
	CRect rect_btn_new = Util::getControlPosition(m_btn_new,this);
	Util::setControlPosition(m_btn_new,this,rect_btn_new.left,rect_choice.bottom+INTERVAL_CHOICE);	

	//Del Button
	CRect rect_btn_del = Util::getControlPosition(m_btn_del,this);
	Util::setControlPosition(m_btn_del,this,rect_btn_del.left,rect_choice.bottom+INTERVAL_CHOICE);	

	CRect rect_window;	
	GetClientRect(&rect_window);
	//Next Button
	CRect rect_btn_next = Util::getControlPosition(m_btn_next,this);
	int width_btn_next = rect_btn_next.right - rect_btn_next.left;
	Util::setControlPosition(m_btn_next,this,rect_window.right-width_btn_next,rect_choice.bottom+INTERVAL_CHOICE);	
	//Util::LOG(L"%d",rect_choice.bottom);
	//Util::LOG(L"(%d,%d) (%d,%d)",rect.left,rect.top,rect.right,rect.bottom);

	m_current_index = 0;

	CRect rect_radio1 = Util::getControlPosition(m_radio_answer1,this);
	Util::setControlPosition(m_btn_note,this,rect_radio1.right+10,rect_radio1.top);


	m_oper_type = OperationType::Normal;
	setEnable(FALSE);
	//OnMenuLoad();
	 
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMulti_ChoiceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMulti_ChoiceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMulti_ChoiceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CMulti_ChoiceDlg::PreTranslateMessage(MSG* pMsg)
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
				m_edit_title.SetSel(0,-1);
				m_edit_choice1.SetSel(0,-1);
				m_edit_choice2.SetSel(0,-1);
				m_edit_choice3.SetSel(0,-1);
				m_edit_choice4.SetSel(0,-1);
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
				OnMenuLoad();
			}
			break;
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
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 

return CDialog::PreTranslateMessage(pMsg);
}
void CMulti_ChoiceDlg::OnMenuExit()
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

UINT ThreadSave(LPVOID lPvoid)
{
	CMulti_ChoiceDlg* dlg = (CMulti_ChoiceDlg*)lPvoid;

	dlg->m_oper_type = OperationType::Save;
	CMarkup xml;	
	xml.SetDoc(L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
	xml.AddElem(L"root");

	xml.IntoElem();

	int size = dlg->m_list.size();

	for(int i=0;i<size;i++)
	{
	CModelChoice* model = (CModelChoice*)dlg->m_list[i];

	xml.AddElem(L"question");
	xml.AddAttrib(L"title",model->m_title.Trim());
	xml.AddAttrib(L"answer",model->m_answer.Trim());
	
	CString and;
	
	/*if(model->m_note.Trim().Replace(L"\r\n",L"&#x0A;&#x0D;")>0)
	{

	}*/

	
	CString note = model->m_note;
	note.Replace(L"\r\n",L"&#x0A;");
	xml.AddAttrib(L"note",note.Trim());
		xml.IntoElem();
		xml.AddElem(L"choice",model->m_choices[0].Trim());
		xml.AddElem(L"choice",model->m_choices[1].Trim());
		xml.AddElem(L"choice",model->m_choices[2].Trim());
		xml.AddElem(L"choice",model->m_choices[3].Trim());
		xml.OutOfElem();	

	}

	xml.OutOfElem();
	
	CString result = xml.GetDoc();
	result.Replace(L"amp;",L"");
	xml.SetDoc(result);
	xml.Save(dlg->m_strFileName);
	dlg->SendMessageStatus(MSG_TYPE::MSG_Finish);
//	Util::LOG(L"%s",xml.GetDoc());	
return 0;
}


void CMulti_ChoiceDlg::OnMenuSave()
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
		AfxBeginThread(ThreadSave,this);
}


void CMulti_ChoiceDlg::OnMenuLoad()
{
	// TODO: 在此添加命令处理程序代码
	CString strFilter = _T("xml files(*.xml)|*.xml||");
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
		m_strFileName = FileDlg.GetPathName();

	OpenFile();
}
void CMulti_ChoiceDlg::updateQuestionUI()
{
	int maxsize = m_list.size();
	if(m_current_index>= maxsize){
		--m_current_index;
	}
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	m_edit_title.SetWindowTextW(model->m_title);
	m_edit_choice1.SetWindowTextW(model->m_choices[0]);
	m_edit_choice2.SetWindowTextW(model->m_choices[1]);
	m_edit_choice3.SetWindowTextW(model->m_choices[2]);
	m_edit_choice4.SetWindowTextW(model->m_choices[3]);
	
	if(model->m_choices[0].Trim()==model->m_answer.Trim())
	{
		m_radio_answer1.SetCheck(TRUE);

		m_radio_answer2.SetCheck(FALSE);
		m_radio_answer3.SetCheck(FALSE);
		m_radio_answer4.SetCheck(FALSE);
	}
	else if(model->m_choices[1].Trim()==model->m_answer.Trim())
	{
		m_radio_answer2.SetCheck(TRUE);

		m_radio_answer1.SetCheck(FALSE);
		m_radio_answer3.SetCheck(FALSE);
		m_radio_answer4.SetCheck(FALSE);
	}
	else if(model->m_choices[2].Trim()==model->m_answer.Trim())
	{
		m_radio_answer3.SetCheck(TRUE);

		m_radio_answer2.SetCheck(FALSE);
		m_radio_answer1.SetCheck(FALSE);
		m_radio_answer4.SetCheck(FALSE);
	}
	else
	{
		m_radio_answer4.SetCheck(TRUE);

		m_radio_answer2.SetCheck(FALSE);
		m_radio_answer3.SetCheck(FALSE);
		m_radio_answer1.SetCheck(FALSE);
	}
	CString tmp;
	tmp.Format(L"%d/%d",m_current_index+1,m_list.size());
	m_lbl_no.SetWindowTextW(tmp);
}

void CMulti_ChoiceDlg::OnBnClickedBtnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	if( (m_current_index-1) >=0)
	{
		if(m_current_index == m_list.size()-1)
	{
	 CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	 CString tmp;
	 m_edit_title.GetWindowTextW(tmp);
	 model->m_title = tmp.Trim();

	 m_edit_choice1.GetWindowTextW(tmp);
	 model->m_choices[0]=tmp;

	 m_edit_choice2.GetWindowTextW(tmp);
	 model->m_choices[1]=tmp;

	 m_edit_choice3.GetWindowTextW(tmp);
	 model->m_choices[2]=tmp;

	 m_edit_choice4.GetWindowTextW(tmp);
	 model->m_choices[3]=tmp;
	}

		--m_current_index;
		updateQuestionUI();
	}

	

}


void CMulti_ChoiceDlg::OnBnClickedBtnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	int maxsize = m_list.size();
	if( (m_current_index+1) <maxsize)
	{
		++m_current_index;
		updateQuestionUI();
	}
}


void CMulti_ChoiceDlg::OnBnClickedBtnNote()
{
	// TODO: 在此添加控件通知处理程序代码
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];

	CNoteEditorDlg dlg;
	dlg.m_str_content = model->m_note;
	dlg.DoModal();

	if(dlg.m_ok)
	{
		model->m_note = dlg.m_str_content;
	}
}


void CMulti_ChoiceDlg::OnMenuNew()
{
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


void CMulti_ChoiceDlg::OnBnClickedRadioAnswer1()
{
	// TODO: 在此添加控件通知处理程序代码
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	model->m_answer = model->m_choices[0];
}


void CMulti_ChoiceDlg::OnBnClickedRadioAnswer2()
{
	// TODO: 在此添加控件通知处理程序代码
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	model->m_answer = model->m_choices[1];
}


void CMulti_ChoiceDlg::OnBnClickedRadioAnswer3()
{
	// TODO: 在此添加控件通知处理程序代码
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	model->m_answer = model->m_choices[2];
}


void CMulti_ChoiceDlg::OnBnClickedRadioAnswer4()
{
	// TODO: 在此添加控件通知处理程序代码
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	model->m_answer = model->m_choices[3];
}


void CMulti_ChoiceDlg::OnBnClickedBtnNew()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CModelChoice* model = new CModelChoice;
	m_list.push_back(model);
	m_current_index = m_list.size()-1;
	updateQuestionUI();
}


void CMulti_ChoiceDlg::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(IDOK == MessageBox(L"确定删除?",L"提示",MB_OKCANCEL))
	{
	vector<CModelChoice*>::iterator it = m_list.begin()+m_current_index;
	
	m_list.erase(it);	

	updateQuestionUI();
	}
}
void CMulti_ChoiceDlg::setEnable(BOOL enable)
{
	m_edit_title.EnableWindow(enable);
	m_edit_choice1.EnableWindow(enable);
	m_edit_choice2.EnableWindow(enable);
	m_edit_choice3.EnableWindow(enable);
	m_edit_choice4.EnableWindow(enable);
	m_btn_del.EnableWindow(enable);
	m_btn_new.EnableWindow(enable);
	m_btn_next.EnableWindow(enable);
	m_btn_note.EnableWindow(enable);
	m_btn_prev.EnableWindow(enable);	
	m_radio_answer1.EnableWindow(enable);
	m_radio_answer2.EnableWindow(enable);
	m_radio_answer3.EnableWindow(enable);
	m_radio_answer4.EnableWindow(enable);

}

void CMulti_ChoiceDlg::OnEnChangeEditTitle()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	CString title;
	m_edit_title.GetWindowTextW(title);
	model->m_title = title;
}


void CMulti_ChoiceDlg::OnEnChangeEditChoice1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	CString choice;
	m_edit_choice1.GetWindowTextW(choice);
	model->m_choices[0] = choice;


	if(m_radio_answer1.GetCheck()==TRUE)
	{
		model->m_answer = choice;
	}
}


void CMulti_ChoiceDlg::OnEnChangeEditChoice2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	CString choice;
	m_edit_choice2.GetWindowTextW(choice);
	model->m_choices[1] = choice;

	if(m_radio_answer2.GetCheck()==TRUE)
	{
		model->m_answer = choice;
	}
}


void CMulti_ChoiceDlg::OnEnChangeEditChoice3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	CString choice;
	m_edit_choice3.GetWindowTextW(choice);
	model->m_choices[2] = choice;

	if(m_radio_answer3.GetCheck()==TRUE)
	{
		model->m_answer = choice;
	}
}


void CMulti_ChoiceDlg::OnEnChangeEditChoice4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CModelChoice* model = (CModelChoice*)m_list[m_current_index];
	CString choice;
	m_edit_choice4.GetWindowTextW(choice);
	model->m_choices[3] = choice;
	
	if(m_radio_answer4.GetCheck()==TRUE)
	{
		model->m_answer = choice;
	}
}
void CMulti_ChoiceDlg::SendMessageStatus(MSG_TYPE type,CString msg)
{
	SendMessage(WM_MSG_STATUS,type,(LPARAM)msg.GetBuffer());
	msg.ReleaseBuffer();
}
LONG CMulti_ChoiceDlg::OnMessageReceive(WPARAM wParam,LPARAM lParam)
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

void CMulti_ChoiceDlg::OnClose()
{
	CDialog::OnClose();
	m_list.clear();	
}

void CMulti_ChoiceDlg::OnDropFiles(HDROP hDropInfo)
{
	//Util::LOG(L"OnDropFiles");
	TCHAR FileName[512];
	memset(FileName,0,512 * sizeof(TCHAR));
    UINT nChars= ::DragQueryFile( hDropInfo, 0 ,FileName , 512 * sizeof( TCHAR ) );

	m_strFileName = FileName;
	OpenFile();
    ::DragFinish( hDropInfo ); 
}

void CMulti_ChoiceDlg::OpenFile()
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
	    CString title = xml.GetAttrib(L"title");
		CString answer = xml.GetAttrib(L"answer");
		CString note = xml.GetAttrib(L"note");
		
		CModelChoice *model = new CModelChoice;

		model->m_title = title;
		model->m_answer = answer;
		model->m_note = note;
	
		
		Util::AddReturnFromXml(model->m_note);
	
		
		Util::LOG(L"\ntitle=%s answer=%s note=%s\n",title,answer,note);

		

		xml.IntoElem();
			
		xml.ResetMainPos();
		int i=0;
		while(xml.FindElem(L"choice")){
			CString choice=xml.GetData();
			model->m_choices[i] = choice;
			Util::LOG(L"\nchoice%d=%s\n",i,choice);
			++i;
		}		
		m_list.push_back(model);

		xml.OutOfElem();

	}
	xml.OutOfElem();
	m_current_index = 0;
	updateQuestionUI();
	SendMessageStatus(MSG_TYPE::MSG_Finish);
}