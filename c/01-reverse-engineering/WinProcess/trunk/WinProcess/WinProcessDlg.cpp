
// WinProcessDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinProcess.h"
#include "WinProcessDlg.h"
#include "afxdialogex.h"

#include "utils_str.h"
#include "DialogProcessDetail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWinProcessDlg �Ի���




CWinProcessDlg::CWinProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinProcessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	spMgr = new SystemProcessMgr();
}

CWinProcessDlg::~CWinProcessDlg() {
	delete spMgr; spMgr = NULL;
}

void CWinProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROCESS_LIST, m_process_table);
}

BEGIN_MESSAGE_MAP(CWinProcessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CWinProcessDlg::OnBnClickedReflash)
	ON_BN_CLICKED(IDC_DETAIL, &CWinProcessDlg::OnBnClickedDetail)
	ON_BN_CLICKED(IDCANCEL, &CWinProcessDlg::OnBnClickedExit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PROCESS_LIST, &CWinProcessDlg::OnLvnItemchangedList2)
END_MESSAGE_MAP()


// CWinProcessDlg ��Ϣ�������

BOOL CWinProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	/*++++ ��ʼ�����̱� ++++*/
	DWORD style = m_process_table.GetExtendedStyle();
	style |= LVS_EX_FULLROWSELECT;	// ��ѡ��ĳ����Ԫ��ʱͬʱѡ������
	style |= LVS_EX_GRIDLINES;		// ��ʾ����
	style |= LVS_ALIGNTOP;			// ��ֱ������
	m_process_table.SetExtendedStyle(style);

	m_process_table.InsertColumn(0, _T("���"), LVCFMT_CENTER, 50);
	m_process_table.InsertColumn(1, _T("���̺�"), LVCFMT_CENTER, 75);
	m_process_table.InsertColumn(2, _T("ƽ̨"), LVCFMT_CENTER, 50);
	m_process_table.InsertColumn(3, _T("��������"), LVCFMT_CENTER, 100);
	m_process_table.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);	// �Զ��������һ���п�, ������ֿ���
	/*---- ��ʼ�����̱� ----*/

	// ˢ�½����б�
	reflashProcessList(true);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWinProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWinProcessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWinProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ˢ�½����б�ť�¼�
void CWinProcessDlg::OnBnClickedReflash()
{
	bool sortByPID = (::MessageBox(this->m_hWnd, _T("Sort By PID ? ( Else By Name )"), _T("Tips"), MB_OKCANCEL) == IDOK);
	reflashProcessList(sortByPID);
}

// ˢ�½����б�
void CWinProcessDlg::reflashProcessList(bool sortByPID) {
	// ��ս����б�
	m_process_table.DeleteAllItems();

	// ��ȡ��ǰϵͳ������Ϣ
	spMgr->reflashProcessList();

	// ���½����б�
	int cnt = 0;
	if(sortByPID == true) {	// �����̺���������
		DWORD* pids = spMgr->getAllPIDs();
		for(; *(pids + cnt) != INVAILD_PID; cnt++) {
			DWORD pid = *(pids + cnt);
			Process process = spMgr->getProcess(pid);
			addToList(cnt, process);
		}

	} else {	// ����������������
		Process** processes = spMgr->getAllProcesses();
		for(; (**(processes + cnt)) != INVAILD_PROCESS; cnt++) {
			Process process = (**(processes + cnt));
			addToList(cnt, process);
		}
	}

	// ���½�������
	TCHAR* wCNT = STR_UTILS::toWChar(cnt);
	SetDlgItemText(IDC_PROCESS_NUM, wCNT);
	STR_UTILS::sFree(wCNT);
}

// FIXME : toWChar���ص�������ռ�õ���Դδ���ͷ�
void CWinProcessDlg::addToList(int idx, Process process) {
	TCHAR* wIDX = STR_UTILS::toWChar(idx + 1);
	TCHAR* wPID = STR_UTILS::toWChar(process.pid);
	TCHAR* wName = STR_UTILS::toWChar(process.pName.c_str());

	m_process_table.InsertItem(idx, wIDX);
	m_process_table.SetItemText(idx, 1, wPID);
	m_process_table.SetItemText(idx, 2, (process.isX64 ? _T("x64") : _T("x86")));
	m_process_table.SetItemText(idx, 3, wName);	

	STR_UTILS::sFree(wIDX);
	STR_UTILS::sFree(wPID);
	STR_UTILS::sFree(wName);
}

void CWinProcessDlg::OnBnClickedDetail()
{
	int rowId = m_process_table.GetNextItem(-1, LVIS_SELECTED);
	if(rowId >= 0) {
		CString sPID = m_process_table.GetItemText(rowId, 1);
		DWORD pid = _wtol(sPID);

		ProcessModule* pm = spMgr->getProcessModuleInfo(pid);
		DialogProcessDetail* dpd = new DialogProcessDetail();
		dpd->updateToList(pm);
		dpd->DoModal();	// ��ʾ����
	}
}

void CWinProcessDlg::OnBnClickedExit()
{
	if(::MessageBox(this->m_hWnd, _T("Exit ?"), _T("Tips"), MB_OKCANCEL) == IDOK) {
		CDialogEx::OnCancel();
	}
}

void CWinProcessDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
