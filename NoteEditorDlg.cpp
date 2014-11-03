// NoteEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Multi_Choice.h"
#include "NoteEditorDlg.h"
#include "afxdialogex.h"


// CNoteEditorDlg 对话框

IMPLEMENT_DYNAMIC(CNoteEditorDlg, CDialogEx)

CNoteEditorDlg::CNoteEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNoteEditorDlg::IDD, pParent)
{

}

CNoteEditorDlg::~CNoteEditorDlg()
{
}

void CNoteEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_edit_content);
}


BEGIN_MESSAGE_MAP(CNoteEditorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OK, &CNoteEditorDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CNoteEditorDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CNoteEditorDlg 消息处理程序
BOOL CNoteEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_ok = FALSE;
	m_edit_content.SetWindowTextW(m_str_content);

	//m_edit_content.SetSel(m_str_content.GetLength()-1,m_str_content.GetLength()-1);
    return TRUE;
}

void CNoteEditorDlg::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ok = TRUE;
	m_edit_content.GetWindowTextW(m_str_content);
	
	CDialog::OnCancel();
}


void CNoteEditorDlg::OnBnClickedBtnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ok = FALSE;
	CDialog::OnCancel();
}

BOOL CNoteEditorDlg::PreTranslateMessage(MSG* pMsg)
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
			m_edit_content.SetSel(0,-1);
		}
		break;
		}
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 

return CDialog::PreTranslateMessage(pMsg);
}

void CNoteEditorDlg::OnBnClickedBtnInsertReturn()
{
	// TODO: 在此添加控件通知处理程序代码
	int start,end;
	m_edit_content.GetSel(start,end);
	CString content;
	
	if(start == end)
	{
		CString insertStr= L"&#x0A;&#x0D;";
		m_edit_content.GetWindowTextW(content);
		content.Insert(start,insertStr);
		m_edit_content.SetWindowTextW(content);
		m_edit_content.SetSel(start + insertStr.GetLength(),start + insertStr.GetLength());
	}
	Util::LOG(L"GetSel=%d,%d\n",start,end);
}
