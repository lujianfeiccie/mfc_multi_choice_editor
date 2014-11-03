// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Multi_Choice.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "Multi_ChoiceDlg.h"
#include "AskAnswerDlg.h"
#include "CalcDlg.h"
// CMainDlg �Ի���

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


// CMainDlg ��Ϣ�������


void CMainDlg::OnBnClickedBtnMultiChoice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
	CMulti_ChoiceDlg dlg;
	dlg.DoModal();
	
}


void CMainDlg::OnBnClickedBtnShortAnswer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
	CCalcDlg dlg;
	dlg.DoModal();
}
