
// Multi_ChoiceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Multi_Choice.h"
#include "Multi_ChoiceDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT indicators_multi_choice_dlg[]={
IDS_STRING_STATUS
};
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
// ʵ��
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
// CMulti_ChoiceDlg �Ի���




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
}


BEGIN_MESSAGE_MAP(CMulti_ChoiceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID__MENU_EXIT, &CMulti_ChoiceDlg::OnMenuExit)	
	ON_COMMAND(ID_MENU_SAVE, &CMulti_ChoiceDlg::OnMenuSave)
	ON_COMMAND(ID_MENU_LOAD, &CMulti_ChoiceDlg::OnMenuLoad)
END_MESSAGE_MAP()


// CMulti_ChoiceDlg ��Ϣ�������

BOOL CMulti_ChoiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if (!m_statusbar_status.Create(this) ||
        !m_statusbar_status.SetIndicators(indicators_multi_choice_dlg,sizeof(indicators_multi_choice_dlg)/sizeof(UINT))
        )
	{
		   TRACE0("Failed to create status bar\n");
		   return -1;      // fail to create
	}
	m_statusbar_status.SetPaneInfo(0,indicators_multi_choice_dlg[0],SBPS_STRETCH,400);	
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,AFX_IDW_CONTROLBAR_FIRST);

	
	CRect rect_edit_title = Util::getControlPosition(&m_edit_title,this);
	CRect rect_lbl_title = Util::getControlPosition(&m_lbl_title,this);
	Util::setControlPosition(&m_lbl_title,this,rect_lbl_title.left,rect_edit_title.top);

	CRect rect_choice;
	//Choice1
	Util::setControlPosition(&m_edit_choice1,this,rect_edit_title.left,rect_edit_title.bottom+INTERVAL_CHOICE);
	rect_choice = Util::getControlPosition(&m_edit_choice1,this);

	Util::setControlPosition(&m_lbl_choice1,this,rect_lbl_title.left,rect_choice.top);


	//Choice2
	Util::setControlPosition(&m_edit_choice2,this,rect_edit_title.left,rect_choice.bottom+INTERVAL_CHOICE);	
	rect_choice = Util::getControlPosition(&m_edit_choice2,this);
	Util::setControlPosition(&m_lbl_choice2,this,rect_lbl_title.left,rect_choice.top);

	
	//Choice3
	Util::setControlPosition(&m_edit_choice3,this,rect_edit_title.left,rect_choice.bottom+INTERVAL_CHOICE);	
	rect_choice = Util::getControlPosition(&m_edit_choice3,this);
	Util::setControlPosition(&m_lbl_choice3,this,rect_lbl_title.left,rect_choice.top);
	

	//Choice4
	Util::setControlPosition(&m_edit_choice4,this,rect_edit_title.left,rect_choice.bottom+INTERVAL_CHOICE);	
	rect_choice = Util::getControlPosition(&m_edit_choice4,this);
	Util::setControlPosition(&m_lbl_choice4,this,rect_lbl_title.left,rect_choice.top);

	//Prev Button
	Util::setControlPosition(&m_btn_prev,this,0,rect_choice.bottom+INTERVAL_CHOICE);	

	CRect rect_window;
	GetWindowRect(&rect_window);
	//Next Button
	CRect rect_btn_next = Util::getControlPosition(&m_btn_next,this);
	int width_btn_next = rect_btn_next.right - rect_btn_next.left;
	Util::setControlPosition(&m_btn_next,this,rect_window.right-width_btn_next-15,rect_choice.bottom+INTERVAL_CHOICE);	
	//Util::LOG(L"%d",rect_choice.bottom);
	//Util::LOG(L"(%d,%d) (%d,%d)",rect.left,rect.top,rect.right,rect.bottom);
	OnMenuLoad();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMulti_ChoiceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		if (bCtrl){
		//	m_edit_excel_path.SetSel(0,-1);
		}
		break;
		}
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 

return CDialog::PreTranslateMessage(pMsg);
}
void CMulti_ChoiceDlg::OnMenuExit()
{
	// TODO: �ڴ���������������
	CDialog::OnCancel();
}




void CMulti_ChoiceDlg::OnMenuSave()
{
	// TODO: �ڴ���������������
}


void CMulti_ChoiceDlg::OnMenuLoad()
{
	// TODO: �ڴ���������������
	/*CString strFilter = _T("xml files(*.xml)|*.xml||");
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;*/
	//CString strFileName = FileDlg.GetPathName();
	CString strFileName;

	strFileName = L"C:\\Users\\john\\Desktop\\2013_10_new.xml";
	CMarkup xml;
	BOOL flag = xml.Load(strFileName);
	Util::LOG(L"flag=%d",flag);
	 
	xml.FindElem(L"root");
	xml.IntoElem();

	while(xml.FindElem(L"question"))
	{
	    CString title = xml.GetAttrib(L"title");
		CString answer = xml.GetAttrib(L"answer");
		CString note = xml.GetAttrib(L"note");
		CModelChoice *model = new CModelChoice;

		model->m_title = title;
		model->m_answer = answer;
		model->m_note = note;
	

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


}
