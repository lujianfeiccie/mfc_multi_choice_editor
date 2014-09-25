#pragma once
#include "afxwin.h"


// CNoteEditorDlg �Ի���

class CNoteEditorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNoteEditorDlg)

public:
	CNoteEditorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNoteEditorDlg();
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
// �Ի�������
	enum { IDD = IDD_NOTEEDITORDLG };
	CString m_str_content;
	BOOL m_ok;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_content;
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnInsertReturn();
};
