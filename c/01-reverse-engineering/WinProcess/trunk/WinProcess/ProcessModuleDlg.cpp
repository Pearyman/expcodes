// ProcessModuleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinProcess.h"
#include "ProcessModuleDlg.h"
#include "afxdialogex.h"
#include "SystemProcessMgr.h"
#include "utils_str.h"


// ProcessModuleDlg �Ի���

IMPLEMENT_DYNAMIC(ProcessModuleDlg, CDialogEx)


ProcessModuleDlg::ProcessModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ProcessModuleDlg::IDD, pParent)
{
}

ProcessModuleDlg::~ProcessModuleDlg()
{
}

void ProcessModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODULE_LIST, m_module_table);
}

BOOL ProcessModuleDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	/*++++ ��ʼ������ģ��� ++++*/
	DWORD style = m_module_table.GetExtendedStyle();
	style |= LVS_EX_FULLROWSELECT;	// ��ѡ��ĳ����Ԫ��ʱͬʱѡ������
	style |= LVS_EX_GRIDLINES;		// ��ʾ����
	style |= LVS_ALIGNTOP;			// ��ֱ������
	m_module_table.SetExtendedStyle(style);

	m_module_table.InsertColumn(0, _T("���"), LVCFMT_CENTER, 40);
	m_module_table.InsertColumn(1, _T("ģ���С(byte)"), LVCFMT_CENTER, 100);
	m_module_table.InsertColumn(2, _T("ȫ��������"), LVCFMT_CENTER, 80);
	m_module_table.InsertColumn(3, _T("��ַָ��(ָ���ַ������Ч)"), LVCFMT_CENTER, 180);
	m_module_table.InsertColumn(4, _T("ģ������"), LVCFMT_CENTER, 100);
	m_module_table.InsertColumn(5, _T("ģ��·��"), LVCFMT_CENTER, 100);
	m_module_table.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);	// �Զ��������һ���п�, ������ֿ���
	/*---- ��ʼ������ģ��� ----*/

	return TRUE;
}

void ProcessModuleDlg::updateToList(Process* process) {

	TCHAR* wTmp = STR_UTILS::toWChar(process->pid);
	SetDlgItemText(IDC_STATIC_PID, wTmp);
	STR_UTILS::sFree(wTmp);

	wTmp = STR_UTILS::toWChar(process->mCnt);
	SetDlgItemText(IDC_STATIC_MCNT, wTmp);
	STR_UTILS::sFree(wTmp);

	m_module_table.DeleteAllItems();
	list<Module*>::iterator moduleIts = process->modules->begin();
	for(int i = 0; i < process->mCnt; i++, moduleIts++) {
		Module* module = *moduleIts;
		addToList(i, module);
	}

}


//m_module_table.InsertColumn(4, _T("ģ���ַ"), LVCFMT_CENTER, 40);
//m_module_table.InsertColumn(5, _T("ģ������ַ"), LVCFMT_CENTER, 40);
void ProcessModuleDlg::addToList(int idx, Module* module) {
	TCHAR* wIDX = STR_UTILS::toWChar(idx + 1);
	TCHAR* wSize = STR_UTILS::toWChar(module->mSize);
	TCHAR* wUsage = STR_UTILS::toWChar(module->usage);
	TCHAR* wName = STR_UTILS::toWChar(module->name.c_str());
	TCHAR* wPath = STR_UTILS::toWChar(module->path.c_str());

	m_module_table.InsertItem(idx, wIDX);
	m_module_table.SetItemText(idx, 1, wSize);
	m_module_table.SetItemText(idx, 2, wUsage);
	m_module_table.SetItemText(idx, 4, wName);
	m_module_table.SetItemText(idx, 5, wPath);

	STR_UTILS::sFree(wIDX);
	STR_UTILS::sFree(wSize);
	STR_UTILS::sFree(wUsage);
	STR_UTILS::sFree(wName);
	STR_UTILS::sFree(wPath);



	// FIXME: �˴���ӡ�ġ���ַָ�롿����������
	// �� ʵ�ʻ�ַָ�볤��Ϊ˫�ֽڣ�16λ������swprintf_s����ǿ�аѸ�8λȫ����
	// �� �û�ַָ����ָ��Ļ�ַδ������Ч��ַ���ƺ�����win����Ȩ�޵�����,����x64ģ���ַ�����Σ�
	const int ADDR_LEN = 32;
	TCHAR wAddr[ADDR_LEN] = {0};
	swprintf_s(wAddr, ADDR_LEN, _T("0x%016x"), module->pBaseAddr);
	m_module_table.SetItemText(idx, 3, wAddr);
}

BEGIN_MESSAGE_MAP(ProcessModuleDlg, CDialogEx)
END_MESSAGE_MAP()


// ProcessModuleDlg ��Ϣ�������