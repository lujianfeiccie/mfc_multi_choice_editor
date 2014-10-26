#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ModelAskAnswer.h"
#include <vector>
using namespace std;
// CAskAnswerDlg 对话框

class CAskAnswerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAskAnswerDlg)

public:
	CAskAnswerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAskAnswerDlg();

// 对话框数据
	enum { IDD = IDD_ASKANSWERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CStatusBar m_statusbar_status;
	CEdit m_edit_question;
	CEdit m_edit_answer;	 
	vector<CModelAskAnswer*> m_list;
	void setEnable(BOOL enable);
	afx_msg void OnMenuNew();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuExit();
	CButton m_btn_prev;
	CButton m_btn_add;
	CButton m_btn_del;
	CButton m_btn_next;
	OperationType m_oper_type;
	int m_current_index;
	void updateQuestionUI();
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnNext();
	CStatic m_lbl_no;
	CString m_strFileName;
	void SendMessageStatus(MSG_TYPE type,CString msg=L"");
	LONG OnMessageReceive(WPARAM wParam,LPARAM lParam);
	afx_msg void OnEnChangeEditQuestion();
	afx_msg void OnEnChangeEditAnswer();
	void OnOK();

};
