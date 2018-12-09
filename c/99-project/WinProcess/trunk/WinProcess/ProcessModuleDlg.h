#pragma once

#include "SystemProcessMgr.h"

// ProcessModuleDlg �Ի���

class ProcessModuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ProcessModuleDlg)

public:
	ProcessModuleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProcessModuleDlg();

	void updateToList(Process* pm);

// �Ի�������
	enum { IDD = IDD_PROC_DETAIL };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	void addToList(int idx, Module* module);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_module_table;
	afx_msg void OnBnClickedOk();

};
