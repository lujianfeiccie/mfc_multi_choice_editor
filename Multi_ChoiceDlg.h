
// Multi_ChoiceDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "BaseDlg.h"
#include <vector>
using namespace std;
class CModelChoice;

// CMulti_ChoiceDlg 对话框
class CMulti_ChoiceDlg : public CBaseDlg
{
// 构造
public:
	CMulti_ChoiceDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CMulti_ChoiceDlg();
// 对话框数据
	enum { IDD = IDD_MULTI_CHOICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuExit();
	
	afx_msg void OnMenuSave();
	afx_msg void OnMenuLoad();
	CEdit m_edit_title;
	CEdit m_edit_choice1;
	CEdit m_edit_choice2;
	CEdit m_edit_choice3;
	CEdit m_edit_choice4;
	CStatic m_lbl_title;
	CStatic m_lbl_choice1;
	CStatic m_lbl_choice2;
	CStatic m_lbl_choice3;
	CStatic m_lbl_choice4;
	CButton m_btn_next;
	CButton m_btn_prev;
	vector<CModelChoice*> m_list;
	
	CButton m_radio_answer1;
	CButton m_radio_answer2;
	CButton m_radio_answer3;
	CButton m_radio_answer4;
	CButton m_btn_note;

	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNext();
	CStatic m_lbl_no;
	afx_msg void OnBnClickedBtnNote();
	afx_msg void OnMenuNew();

	afx_msg void OnBnClickedRadioAnswer1();
	afx_msg void OnBnClickedRadioAnswer2();
	afx_msg void OnBnClickedRadioAnswer3();
	afx_msg void OnBnClickedRadioAnswer4();

	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnDel();
	CButton m_btn_new;
	CButton m_btn_del;

	afx_msg void OnEnChangeEditTitle();
	afx_msg void OnEnChangeEditChoice1();
	afx_msg void OnEnChangeEditChoice2();
	afx_msg void OnEnChangeEditChoice3();
	afx_msg void OnEnChangeEditChoice4();
	virtual void OnClose();
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
