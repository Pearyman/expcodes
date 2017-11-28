
#include "stdafx.h"
#include "utils_os.h"
#include "utils_str.h"
#include "SystemProcessMgr.h"

#include <algorithm>
#include <string>
#include <map>
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
using namespace std;

/************************************************************************/
/* ��ӽ���ģ��                                                         */
/************************************************************************/ 
void Process::add(Module* module) {
	modules->push_back(module);
	mCnt++;
}

/************************************************************************/
/* ��ս���ģ���б�                                                     */
/************************************************************************/ 
void Process::clear() {
	modules->clear();
}

/************************************************************************/
/* ˢ�µ�ǰϵͳ�����б�                                                 */
/* @return �Ƿ�ˢ�³ɹ�                                                 */
/************************************************************************/ 
bool SystemProcessMgr::reflashProcessList() {
	clearProcesses();
	bool isOk = traverseProcesses();

	if(isOk == true) {
		TRACE(_T("Reflash Processes Success\r\n"));
	} else {
		TRACE(_T("Reflash Processes Fail\r\n"));
	}
	return isOk;
}


/************************************************************************/
/* ��յ�ǰϵͳ�����б����                                             */
/************************************************************************/ 
void SystemProcessMgr::clearProcesses() {
	map<DWORD, BaseProcess>::iterator its = processMap->begin();
	while(its != processMap->end()) {
		map<DWORD, BaseProcess>::iterator obj = its;
		its++;
		processMap->erase(obj);
	}
	processMap->clear();
}


/************************************************************************/
/* ������ǰϵͳ���н���                                                 */
/* @return �Ƿ�����ɹ�                                                 */
/************************************************************************/ 
bool SystemProcessMgr::traverseProcesses() {
	bool isOk = true;

	// ��ȡ��ǰϵͳ�����б����
	HANDLE hProcessSNapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSNapshot == INVALID_HANDLE_VALUE) {
		TRACE(_T("Create BaseProcess Snapshot Error\r\n"));
		isOk = false;

	} else {
		PROCESSENTRY32 pe32;	// ���̽ṹ��
		pe32.dwSize = sizeof(PROCESSENTRY32);	// ���룺ָ��֮��Ҫ��ȡ�Ľ��̽ṹ���С
		const int LEN = sizeof(pe32.szExeFile) / sizeof(pe32.szExeFile[0]);	// �洢�������Ƶ����鳤��

		BOOL hasNext = Process32First(hProcessSNapshot, &pe32);	// ȡ�������б��еĵ�һ������
		while (hasNext) {
			char* tmp = STR_UTILS::toChar(pe32.szExeFile);
			string pName = string(tmp);
			DWORD pid = pe32.th32ProcessID;
			STR_UTILS::sFree(tmp);
			
			addProcess(pid, pName);	// �ѽ�����Ϣ��ӵ�����
			hasNext = Process32NextW(hProcessSNapshot, &pe32);	// ȡ�������б��е���һ������
		}
	}
	CloseHandle(hProcessSNapshot);	// �ͷſ����б���Դ
	return isOk;
}


/************************************************************************/
/* ���һ������                                                         */
/************************************************************************/
const BaseProcess& SystemProcessMgr::addProcess(DWORD pid, string pName) {
	BaseProcess process;
	process.pid = pid;
	process.pName = pName;
	process.isX64 = isX64Process(pid);

	processMap->insert(pair<DWORD, BaseProcess>(pid, process));
	return getBaseProcessInfo(pid);	// ע��ֲ�����process�����������ѽ��������ܷ���֮
}


/************************************************************************/
/* ��ȡһ������                                                         */
/************************************************************************/
const BaseProcess& SystemProcessMgr::getBaseProcessInfo(DWORD pid) {
	map<DWORD, BaseProcess>::iterator its = processMap->find(pid);
	return ( its == processMap->end() ? INVAILD_PROCESS : its->second );
}


/************************************************************************/
/* ��ȡ���н���ID                                                       */
/* @return ָ������ID���������һ��IDΪ-1��                             */
/************************************************************************/
DWORD* SystemProcessMgr::getAllPIDs() {
	delete pids;
	const int LEN = processMap->size();
	pids = new DWORD[LEN + 1];

	int idx = 0;
	map<DWORD, BaseProcess>::iterator its = processMap->begin();
	while(its != processMap->end()) {
		*(pids + idx++) = its->first;
		its++;
	}

	sort(pids, pids + LEN);			// �����̺���������
	*(pids + idx) = INVAILD_PID;	// ���ĩβ��ʶ
	return pids;
}

/************************************************************************/
/* ��ȡ���н��̶�������                                                 */
/* @return ���̶����ָ������ID���������һ������ΪINVAILD_PROCESS��    */
/************************************************************************/
BaseProcess** SystemProcessMgr::getAllProcesses() {
	delete processes;
	const int LEN = processMap->size();
	processes = new BaseProcess*[LEN + 1];

	int idx = 0;
	map<DWORD, BaseProcess>::iterator its = processMap->begin();
	while(its != processMap->end()) {
		*(processes + idx++) = &(its->second);
		its++;
	}
	
	sort(processes, processes + LEN, compare);	// ����������������
	*(processes + idx) = &INVAILD_PROCESS;		// ���ĩβ��ʶ
	return processes;
}

bool SystemProcessMgr::compare(BaseProcess* aProc, BaseProcess* bProc) {
	int rst = stricmp((*aProc).pName.c_str(), (*bProc).pName.c_str());

	// ע������sort()�汾BUG���⣬��rst==0ʱ���뷵��false������ᱨ��
	return (rst < 0 ? true : false);	// ����
	//return (rst > 0 ? true : false);	// ����
}

/************************************************************************/
/* �жϽ����Ƿ�Ϊ64λ                                                   */
/*  IsWow64Process ʵ���ϲ��������жϽ��̵�λ��                         */
/*   ��ʵ�ʺ�����ĳ�������ǲ�����[������wow64���⻷��]��                */
/*    ���ֿ��ܵ�������£�                                              */
/*    64-bit process on 64-bit Windows : FALSE                          */
/*    32-bit process on 64-bit Windows : TRUE                           */
/*    32-bit process on 32-bit Windows : FALSE                          */
/*   ���Է���ֻ�е�32λ����������64λƽ̨ʱ�Ż᷵��TRUE,                */
/*   ��Ҳ��Ϊʲô�ж������windows�Դ���������������ڳ���              */
/************************************************************************/
bool SystemProcessMgr::isX64Process(DWORD pid) {
	bool isX64Process = false;
	if(this->IS_X64_OS == true) {
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
		if(hProcess) {
			typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
			LPFN_ISWOW64PROCESS fnIsWow64Process = 
				(LPFN_ISWOW64PROCESS) GetProcAddress(GetModuleHandleW(L"kernel32"), "IsWow64Process");
			if(fnIsWow64Process != NULL) {
				BOOL isX64 = FALSE;
				fnIsWow64Process(hProcess, &isX64);
				isX64Process = isX64 ? true : false;
			}
		}
		CloseHandle(hProcess);
	}
	return isX64Process;
}

Process* SystemProcessMgr::getProcess(DWORD pid) {
	if(process != &INVAILD_PROCESS_MODULE) {
		delete process;	// INVAILD_PROCESS_MODULE ��ջ���󣬲��ܱ�delete
	}

	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if(hProcess == INVALID_HANDLE_VALUE) {
		process = &INVAILD_PROCESS_MODULE;
		TRACE(_T("Create BaseProcess-Module Snapshot Error\r\n"));

	} else {
		process = new Process();
		process->pid = pid;

		MODULEENTRY32 me;
		me.dwSize = sizeof(MODULEENTRY32);
		BOOL hasNext = Module32First(hProcess, &me);
		while (hasNext) {
			char* tmp = STR_UTILS::toChar(me.szModule);
			string mName = string(tmp);
			STR_UTILS::sFree(tmp);

			tmp = STR_UTILS::toChar(me.szExePath);
			string mPath = string(tmp);
			STR_UTILS::sFree(tmp);

			Module* module = new Module();
			module->mSize = me.dwSize;
			module->mid = me.th32ModuleID;
			module->usage = me.GlblcntUsage;
			module->pBaseAddr = me.modBaseAddr;
			module->hModule = me.hModule;
			module->name = mName;
			module->path = mPath;

			process->add(module);
			hasNext = Module32Next(hProcess, &me);
		}
	}
	CloseHandle(hProcess);
	return process;
}

//#include <Psapi.h>
//#pragma comment (lib,"Psapi.lib")
//Process* SystemProcessMgr::getProcess2(DWORD pid) {
//	HMODULE hMods[512] = {0};
//	DWORD cbNeeded = 0;
//	TCHAR szModName[MAX_PATH];
//	BOOL Wow64Process;
//
//	HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_QUERY_LIMITED_INFORMATION, FALSE, 1032);
//	IsWow64Process(hProcess, &Wow64Process); //�ж���32λ����64λ����
//	EnumProcessModulesEx(hProcess, hMods, sizeof(hMods), &cbNeeded, Wow64Process?LIST_MODULES_32BIT:LIST_MODULES_64BIT);
//
//	for (UINT i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
//	{
//		GetModuleFileNameEx(hProcess, hMods[i], szModName, _countof(szModName));
//		TRACE(TEXT("%s\n"),szModName);
//	}
//	CloseHandle(hProcess);
//
//	return NULL;
//}
