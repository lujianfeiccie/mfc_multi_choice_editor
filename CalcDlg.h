#pragma once

#include "StaticEditManager.h"
#include "afxwin.h"
// CCalcDlg �Ի���

class CCalcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCalcDlg)

public:
	CCalcDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCalcDlg();

// �Ի�������
	enum { IDD = IDD_CALCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
	OperationType m_oper_type;
	int m_current_index;
	CStatusBar m_statusbar_status;
	void setEnable(BOOL enable);
	void OnBtnClick(UINT nCmdID);
	void OnEditChange(UINT ID);
	CStaticEditManager* m_static_edit_manager;
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	CButton m_radio_question;
	CButton m_radio_answer;
	CButton m_radio_text;
	CButton m_radio_image;
	void OnOK();
};
