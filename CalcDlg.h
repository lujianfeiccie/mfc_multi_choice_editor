#pragma once

#include "StaticEditManager.h"
#include "afxwin.h"
#include "ModelCalc.h"
#include <vector>
#include "BaseDlg.h"
using namespace std;
// CCalcDlg 对话框

class CCalcDlg : public CBaseDlg
{
	DECLARE_DYNAMIC(CCalcDlg)

public:
	CCalcDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCalcDlg();

// 对话框数据
	enum { IDD = IDD_CALCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
//	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
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
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnRemove();
	vector<vector<CModelStaticEdit*>> m_list;
	afx_msg void OnMenuNew();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuExit();	
	
	CButton m_btn_prev;
	CButton m_btn_next;
	CButton m_btn_new;
	CButton m_btn_remove;
	CButton m_btn_add;
	CButton m_btn_del;	

	
	CStatic m_lbl_no;

	void OpenFile();
	 void OnSizingEx(CRect Rect);
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
