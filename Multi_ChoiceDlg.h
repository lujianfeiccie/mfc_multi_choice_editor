
// Multi_ChoiceDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <vector>
using namespace std;
class CModelChoice;
// CMulti_ChoiceDlg 对话框
class CMulti_ChoiceDlg : public CDialogEx
{
// 构造
public:
	CMulti_ChoiceDlg(CWnd* pParent = NULL);	// 标准构造函数

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
	CStatusBar m_statusbar_status;
	BOOL PreTranslateMessage(MSG* pMsg);
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
};
