
// WinProcessDlg.h : ͷ�ļ�
//

#pragma once

#include "SystemProcessMgr.h"
#include "ProcessModuleDlg.h"

// CWinProcessDlg �Ի���
class CWinProcessDlg : public CDialogEx
{
// ����
public:
	CWinProcessDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CWinProcessDlg();

// �Ի�������
	enum { IDD = IDD_WinProcess_DIALOG };

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

	void reflashProcessList(bool sortByPID);
	void addToList(int idx, Process process);

public:
	afx_msg void OnBnClickedReflash();
	afx_msg void OnBnClickedDetail();
	afx_msg void OnBnClickedExit();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_process_table;

	SystemProcessMgr* spMgr;
	ProcessModuleDlg* dpd;
};
