// DialogProcessDetail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinProcess.h"
#include "DialogProcessDetail.h"
#include "afxdialogex.h"
#include "SystemProcessMgr.h"
#include "utils_str.h"


// DialogProcessDetail �Ի���

IMPLEMENT_DYNAMIC(DialogProcessDetail, CDialogEx)


DialogProcessDetail::DialogProcessDetail(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogProcessDetail::IDD, pParent)
{
}

DialogProcessDetail::~DialogProcessDetail()
{
}

void DialogProcessDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODULE_LIST, m_module_table);
}

BOOL DialogProcessDetail::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	/*++++ ��ʼ������ģ��� ++++*/
	DWORD style = m_module_table.GetExtendedStyle();
	style |= LVS_EX_FULLROWSELECT;	// ��ѡ��ĳ����Ԫ��ʱͬʱѡ������
	style |= LVS_EX_GRIDLINES;		// ��ʾ����
	style |= LVS_ALIGNTOP;			// ��ֱ������
	m_module_table.SetExtendedStyle(style);

	m_module_table.InsertColumn(0, _T("���"), LVCFMT_CENTER, 50);
	m_module_table.InsertColumn(1, _T("ģ������"), LVCFMT_CENTER, 100);
	m_module_table.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);	// �Զ��������һ���п�, ������ֿ���
	/*---- ��ʼ������ģ��� ----*/

	return TRUE;
}

void DialogProcessDetail::updateToList(ProcessModule* pm) {

	TRACE(_T("\n ---->  me32.dwSize==%d"), pm->mSize);
	TRACE(_T("\n ---->  me32.GlblcntUsage==%d"), pm->usage);
	TRACE(_T("\n ---->  me32.hModule==0x%x"), pm->hModule);
	TRACE(_T("\n ---->  me32.modBaseAddr==0x%x"), pm->baseAddr);
	//TRACE(_T("\n ---->  me32.szExePath==%s"), me.szExePath);
	//TRACE(_T("\n ---->  me32.szModule==%s"), me.szModule);
	TRACE(_T("\n ---->  me32.th32ModuleID==%d"), pm->mID);
	TRACE(_T("\n ---->  me32.th32ProcessID==%d"), pm->pid);
	TRACE(_T("\n ---->  CNT==%d\n"), pm->mCnt);


	m_module_table.DeleteAllItems();
	list<string>::iterator nameIts = pm->mNames->begin();
	list<string>::iterator pathIts = pm->mPaths->begin();
	for(int i = 0; i < pm->mCnt; i++, nameIts++, pathIts++) {
		string name = *nameIts;
		string path = *pathIts;
		addToList(i, name, path);
	}

}

// FIXME : toWChar���ص�������ռ�õ���Դδ���ͷ�
void DialogProcessDetail::addToList(int idx, string mName, string mPath) {
	TCHAR* wIDX = STR_UTILS::toWChar(idx + 1);
	TCHAR* wName = STR_UTILS::toWChar(mName.c_str());
	TCHAR* wPath = STR_UTILS::toWChar(mPath.c_str());

	m_module_table.InsertItem(idx, wIDX);
	m_module_table.SetItemText(idx, 1, wName);
	m_module_table.SetItemText(idx, 2, wPath);

	STR_UTILS::sFree(wIDX);
	STR_UTILS::sFree(wName);
	STR_UTILS::sFree(wPath);
}

BEGIN_MESSAGE_MAP(DialogProcessDetail, CDialogEx)
END_MESSAGE_MAP()


// DialogProcessDetail ��Ϣ�������