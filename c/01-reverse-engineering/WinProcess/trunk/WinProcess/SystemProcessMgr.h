#pragma once

#include "stdafx.h"
#include "utils_os.h"

#include <Windows.h>
#include <string>
#include <map>
#include <list>
using namespace std;

// ��Ч�Ľ��̺�(ϵͳ���̺�Ϊ0, DWORDΪ�޷������ͣ�ֻ��ȡ���ֵ)
const static DWORD INVAILD_PID = 0xFFFFFFFF;


/************************************************************************/
/* �������̵���Ϣ����                                                   */
/************************************************************************/ 
class Process {
	public:
		DWORD pid;
		string pName;
		bool isX64;

		Process(): pid(INVAILD_PID), pName(""), isX64(false) {}

		bool operator == (const Process& other) {
			return (this == &other || this->pid == other.pid);
		}

		bool operator != (const Process& other) {
			return !(operator == (other));
		}
};

// Ĭ�ϵĿս��̶���
static Process INVAILD_PROCESS;


/************************************************************************/
/* ���������ڵ�����ģ�����                                             */
/************************************************************************/ 
class ProcessModule : public Process {
	public:
		int mCnt;					// ģ�����
		DWORD mSize;				// modBaseSize ����ģ���С���ֽڣ�
		DWORD mID;					// th32ModuleID, �˳�Ա�Ѿ����ٱ�ʹ�ã�ͨ��������Ϊ1
		DWORD usage;				// GlblcntUsage �� ProccntUsage ȫ��ģ���ʹ�ü�������ģ��������������ͨ����һ����û�������
		BYTE* baseAddr;				// modBaseAddr ģ���ַ�����������̷�Χ�ڣ�
		HMODULE hModule;			// hModule ģ������ַ�����������̷�Χ�ڣ�
		list<string>* mNames;		// szModule[MAX_MODULE_NAME32 + 1];	 NULL��β���ַ��������а���ģ������
		list<string>* mPaths;		// szExePath[MAX_PATH];	 NULL��β���ַ��������а�����λ�ã���ģ���·����

		ProcessModule() : Process(), 
			mCnt(0), mSize(0), mID(0), usage(0), baseAddr(NULL), hModule(NULL) {
			this->mNames = new list<string>();
			this->mPaths = new list<string>();
		}

		~ProcessModule() {
			clear();
			delete mNames; mNames = NULL;
			delete mPaths; mPaths = NULL;
		}

	private:
		void clear();
};

// Ĭ�ϵĿս���ģ�����
static ProcessModule INVAILD_PROCESS_MODULE;


/************************************************************************/
/* ϵͳ���̼��������                                                   */
/************************************************************************/ 
class SystemProcessMgr
{
	public:
		SystemProcessMgr() {
			this->IS_X64_OS = OS_UTILS::isX64();
			this->processMap = new map<DWORD, Process>();
			this->pids = new DWORD[1];
			this->processes = new Process*[1];
			this->processModule = new ProcessModule();
		}

		~SystemProcessMgr() {
			clearProcesses();
			delete processMap; processMap = NULL;
			delete[] pids; pids = NULL;
			delete[] processes; processes = NULL;
			delete processModule; processModule = NULL;
		}

		bool reflashProcessList();
		const Process& getProcess(DWORD pid);

		DWORD* getAllPIDs();
		Process** getAllProcesses();	// ��ȡ���н��̶���ĵ�ַ����
		ProcessModule* getProcessModuleInfo(DWORD pid);	// ��ȡ����ģ����Ϣ

	protected:
		bool traverseProcesses();
		void clearProcesses();

		const Process& addProcess(DWORD pid, string pName);
		bool isX64Process(DWORD pid);
		static bool compare(Process* aProc, Process* bProc);	// ���ڵ�sort�ȽϺ��������Ǿ�̬

	private:
		bool IS_X64_OS;
		map<DWORD, Process>* processMap;	// ��ǰ���̱�
		DWORD* pids;						// ��ǰ���̶��������
		Process** processes;				// ��ǰ���̶����ָ������
		ProcessModule* processModule;		// ��ǰѡ�еĽ���ģ��ָ��
};


////��psaipi.dll�еĺ���EnumProcesses����ö�ٽ��� 
//typedef BOOL (_stdcall *ENUMPROCESSES)(  //ע������Ҫָ������Լ��Ϊ-stdcall
//	DWORD* pProcessIds,  //ָ�����ID������  
//	DWORD cb,    //ID����Ĵ�С�����ֽڼ���
//	DWORD* pBytesReturned);   //���ص��ֽ�
//
////��psapi.dll�еĺ���EnumProcessModules����ö�ٽ���ģ��
//typedef BOOL (_stdcall *ENUMPROCESSMODULES)(
//	HANDLE hProcess,   //���̾��
//	HMODULE* lphModule, //ָ��ģ����������
//	DWORD cb,    //ģ���������С���ֽڼ���
//	LPDWORD lpcbNeeded);   //�洢����ģ����������ֽ���
//
////��psapi.dll�еĺ���GetModuleFileNameEx��ý���ģ����
//typedef DWORD (_stdcall *GETMODULEFILENAMEEX)(
//	HANDLE hProcess,   //���̾��
//	HMODULE hModule,   //����ģ����
//	LPTSTR lpFilename,   //���ģ��ȫ·����
//	DWORD nSize    //lpFilename��������С���ַ�����
//	);