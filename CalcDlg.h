#pragma once


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
};
