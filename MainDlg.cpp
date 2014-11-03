// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Multi_Choice.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "Multi_ChoiceDlg.h"
#include "AskAnswerDlg.h"
#include "CalcDlg.h"
// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_MULTI_CHOICE, &CMainDlg::OnBnClickedBtnMultiChoice)
	ON_BN_CLICKED(IDC_BTN_SHORT_ANSWER, &CMainDlg::OnBnClickedBtnShortAnswer)
	ON_BN_CLICKED(IDC_BTN_CALC, &CMainDlg::OnBnClickedBtnCalc)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序


void CMainDlg::OnBnClickedBtnMultiChoice()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
	CMulti_ChoiceDlg dlg;
	dlg.DoModal();
	
}


void CMainDlg::OnBnClickedBtnShortAnswer()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
	CAskAnswerDlg dlg;
	dlg.DoModal();
}
BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 
	return CDialog::PreTranslateMessage(pMsg);
}

void CMainDlg::OnBnClickedBtnCalc()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
	CCalcDlg dlg;
	dlg.DoModal();
}
