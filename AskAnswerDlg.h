#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ModelAskAnswer.h"
#include "BaseDlg.h"
#include <vector>
using namespace std;
// CAskAnswerDlg 对话框

class CAskAnswerDlg : public CBaseDlg
{
	DECLARE_DYNAMIC(CAskAnswerDlg)

public:
	CAskAnswerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAskAnswerDlg();

// 对话框数据
	enum { IDD = IDD_ASKANSWERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_question;
	CEdit m_edit_answer;	 
	vector<CModelAskAnswer*> m_list;
	
	afx_msg void OnMenuNew();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuExit();
	CButton m_btn_prev;
	CButton m_btn_add;
	CButton m_btn_del;
	CButton m_btn_next;
	
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnNext();

	CStatic m_lbl_no;
	afx_msg void OnEnChangeEditQuestion();
	afx_msg void OnEnChangeEditAnswer();
	void OnOK();
	void OpenFile();

	//Abstract method
	 void updateQuestionUI();
	 void setEnable(BOOL enable);
	 void OnDropFilesEx();
	 void OnMenuNewByHotkey();
	 void OnMenuOpenByHotkey();
	 void OnMenuSaveByHotkey();
	 void OnSelectAllByHotkey();
	 void OnLeftByHotKey();
	 void OnRightByHotKey();
};
