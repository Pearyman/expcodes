
#include "stdafx.h"
#include "os_utils.h"
#include "str_utils.h"
#include "SystemProcessMgr.h"

#include <algorithm>
#include <string>
#include <map>
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
using namespace std;


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
	map<DWORD, Process>::iterator its = processMap->begin();
	while(its != processMap->end()) {
		map<DWORD, Process>::iterator obj = its;
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
		TRACE(_T("Create Process Snapshot Error\r\n"));
		isOk = false;

	} else {
		PROCESSENTRY32 pe32;	// ���̽ṹ��
		pe32.dwSize = sizeof(PROCESSENTRY32);	// ���룺ָ��֮��Ҫ��ȡ�Ľ��̽ṹ���С
		const int LEN = sizeof(pe32.szExeFile) / sizeof(pe32.szExeFile[0]);	// �洢�������Ƶ����鳤��

		BOOL hasNext = Process32First(hProcessSNapshot, &pe32);	// ȡ�������б��еĵ�һ������
		while (hasNext) {
			char* tmp = toChar(pe32.szExeFile);
			string pName = string(tmp);
			DWORD pid = pe32.th32ProcessID;
			delete tmp;
			
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
const Process& SystemProcessMgr::addProcess(DWORD pid, string pName) {
	Process process;
	process.pid = pid;
	process.pName = pName;
	process.isX64 = isX64Process(pid);

	processMap->insert(pair<DWORD, Process>(pid, process));
	return getProcess(pid);	// ע��ֲ�����process�����������ѽ��������ܷ���֮
}


/************************************************************************/
/* ��ȡһ������                                                         */
/************************************************************************/
const Process& SystemProcessMgr::getProcess(DWORD pid) {
	map<DWORD, Process>::iterator its = processMap->find(pid);
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
	map<DWORD, Process>::iterator its = processMap->begin();
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
Process** SystemProcessMgr::getAllProcesses() {
	delete processes;
	const int LEN = processMap->size();
	processes = new Process*[LEN + 1];

	int idx = 0;
	map<DWORD, Process>::iterator its = processMap->begin();
	while(its != processMap->end()) {
		*(processes + idx++) = &(its->second);
		its++;
	}
	
	sort(processes, processes + LEN, compare);	// ����������������
	*(processes + idx) = &INVAILD_PROCESS;		// ���ĩβ��ʶ
	return processes;
}

bool SystemProcessMgr::compare(Process* aProc, Process* bProc) {
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


ProcessModule* SystemProcessMgr::getProcessModuleInfo(DWORD pid) {
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if(hProcess == INVALID_HANDLE_VALUE) {
		TRACE(_T("Create Process-Module Snapshot Error\r\n"));

	} else {
		MODULEENTRY32 me;
		me.dwSize = sizeof(MODULEENTRY32);

		int cnt = 0;
		BOOL hasNext = Module32First(hProcess, &me);
		while (hasNext) {
			cnt++;
			
			TRACE(_T("\n ---->  me32.dwSize==%d"), me.dwSize);
			TRACE(_T("\n ---->  me32.GlblcntUsage==%d"), me.GlblcntUsage);
			TRACE(_T("\n ---->  me32.hModule==0x%x"), me.hModule);
			TRACE(_T("\n ---->  me32.modBaseAddr==0x%x"), me.modBaseAddr);
			TRACE(_T("\n ---->  me32.ProccntUsage==%d"), me.ProccntUsage);
			TRACE(_T("\n ---->  me32.szExePath==%s"), me.szExePath);
			TRACE(_T("\n ---->  me32.szModule==%s"), me.szModule);
			TRACE(_T("\n ---->  me32.th32ModuleID==%d"), me.th32ModuleID);
			TRACE(_T("\n ---->  me32.th32ProcessID==%d"), me.th32ProcessID);
			TRACE(_T("\n ---->  CNT==%d\n"),cnt);
			hasNext = Module32Next(hProcess, &me);
		}
	}
	CloseHandle(hProcess);
	return NULL;	// FIXME
}

//void SystemProcessMgr::getProcessInfo2(DWORD pid) {
//	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
//
//	CloseHandle(hProcess);
//}
//
//void SystemProcessMgr::getProcessInfo3(DWORD pid) {
//	HMODULE hPsDll = LoadLibrary(_T("PSAPI.DLL"));	// FreeLibrary
//	ENUMPROCESSES pEnumProcesses = (ENUMPROCESSES) GetProcAddress(hPsDll, "EnumProcesses");
//	ENUMPROCESSMODULES pEnumProcessModules = (ENUMPROCESSMODULES) GetProcAddress(hPsDll, "EnumProcessModules");
//	GETMODULEFILENAMEEX pGetModuleFileNameEx = (GETMODULEFILENAMEEX) GetProcAddress(hPsDll, "GetModuleFileNameExA");
//
//	DWORD pids[1] = { pid };
//	DWORD rst[1];
//	pEnumProcesses(pids, sizeof(pid), rst);
//	DWORD processcount = rst[0] / sizeof(DWORD);
//
//	for (int i = 0; i < processcount; i++) {
//		//�򿪽���
//		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, false, pids[i]);
//		if (hProcess) {
//			pEnumProcessModules(hProcess, &hModule, sizeof(hModule), &needed);
//			pGetModuleFileNameEx(hProcess, hModule, path, sizeof(path));
//			GetShortPathName(path,path,256);
//			itoa(pids[i], temp, 10);
//			printf("%s --- %s\n",path,temp);
//
//		} else {
//			printf("Failed!!!\n");
//		}
//	}
//}
