
// Multi_ChoiceDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <vector>
using namespace std;
class CModelChoice;

typedef enum
{
	New,
	Load,
	Save,
	Normal
}OperationType;
// CMulti_ChoiceDlg �Ի���
class CMulti_ChoiceDlg : public CDialogEx
{
// ����
public:
	CMulti_ChoiceDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MULTI_CHOICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	int m_current_index;
	CButton m_radio_answer1;
	CButton m_radio_answer2;
	CButton m_radio_answer3;
	CButton m_radio_answer4;
	CButton m_btn_note;

	void updateQuestionUI();
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNext();
	CStatic m_lbl_no;
	afx_msg void OnBnClickedBtnNote();
	afx_msg void OnMenuNew();

	OperationType m_oper_type;
	afx_msg void OnBnClickedRadioAnswer1();
	afx_msg void OnBnClickedRadioAnswer2();
	afx_msg void OnBnClickedRadioAnswer3();
	afx_msg void OnBnClickedRadioAnswer4();

	CString m_strFileName;
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnDel();
	CButton m_btn_new;
	CButton m_btn_del;

	void setEnable(BOOL enable);
	afx_msg void OnEnChangeEditTitle();
	afx_msg void OnEnChangeEditChoice1();
	afx_msg void OnEnChangeEditChoice2();
	afx_msg void OnEnChangeEditChoice3();
	afx_msg void OnEnChangeEditChoice4();
	void SendMessageStatus(MSG_TYPE type,CString msg=L"");
	LONG OnMessageReceive(WPARAM wParam,LPARAM lParam);
};
