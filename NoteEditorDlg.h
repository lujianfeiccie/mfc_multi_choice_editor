#pragma once
#include "afxwin.h"


// CNoteEditorDlg 对话框

class CNoteEditorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNoteEditorDlg)

public:
	CNoteEditorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNoteEditorDlg();
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
// 对话框数据
	enum { IDD = IDD_NOTEEDITORDLG };
	CString m_str_content;
	BOOL m_ok;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_content;
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnInsertReturn();
};
