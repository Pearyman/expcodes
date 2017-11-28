#pragma once

#include "stdafx.h"
#include "utils_os.h"

#include <Windows.h>
#include <string>
#include <map>
#include <list>
using namespace std;


/************************************************************************/
/* ����ģ����󣨴� MODULEENTRY32 ӳ���ֶΣ�                            */
/************************************************************************/ 
class Module {
public:
	DWORD mid;			// th32ModuleID, �˳�Ա�Ѿ����ٱ�ʹ�ã�ͨ��������Ϊ1
	DWORD mSize;		// modBaseSize ����ģ���С���ֽڣ�
	DWORD usage;		// GlblcntUsage �� ProccntUsage ȫ��ģ���ʹ�ü�������ģ��������������ͨ����һ����û�������
	BYTE* pBaseAddr;	// modBaseAddr ģ���ַ��ָ�루���������̷�Χ�ڣ�����ʵ������unsigned char*
	HMODULE hModule;	// hModule ģ������ַ��ָ�루���������̷�Χ�ڣ�����ʵ������int�� 16���Ƶ�ֵַ����pBaseAddr
	string name;		// szModule[MAX_MODULE_NAME32 + 1];	 NULL��β���ַ��������а���ģ������
	string path;		// szExePath[MAX_PATH];	 NULL��β���ַ��������а�����λ�ã���ģ���·����

	Module() : mSize(0), mid(0), usage(0), pBaseAddr(0), hModule(0) {
		// Undo
	}

	~Module() {
		// Undo
	}
};


// ��Ч�Ľ��̺�(ϵͳ���̺�Ϊ0, DWORDΪ�޷������ͣ�ֻ��ȡ���ֵ)
const static DWORD INVAILD_PID = 0xFFFFFFFF;


/************************************************************************/
/* �������̵���Ϣ����                                                   */
/************************************************************************/ 
class BaseProcess {
	public:
		DWORD pid;
		string pName;
		bool isX64;

		BaseProcess(): pid(INVAILD_PID), pName(""), isX64(false) {}

		bool operator == (const BaseProcess& other) {
			return (this == &other || this->pid == other.pid);
		}

		bool operator != (const BaseProcess& other) {
			return !(operator == (other));
		}
};

// Ĭ�ϵĿս��̶���
static BaseProcess INVAILD_PROCESS;


/************************************************************************/
/* ���������ڵ�����ģ�����                                             */
/************************************************************************/ 
class Process : public BaseProcess {	// �� MODULEENTRY32 ӳ���ֶ�
	public:
		Process() : BaseProcess() {
			this->mCnt = 0;
			this->modules = new list<Module*>();
		}

		~Process() {
			clear();
			delete modules; modules = NULL;
		}

		int mCnt;					// ģ�����
		list<Module*>* modules;		// ģ���б�
		void add(Module* modules);

	private:
		void clear();
};

// Ĭ�ϵĿս���ģ�����
static Process INVAILD_PROCESS_MODULE;


/************************************************************************/
/* ϵͳ���̼��������                                                   */
/************************************************************************/ 
class SystemProcessMgr
{
	public:
		SystemProcessMgr() {
			this->IS_X64_OS = OS_UTILS::isX64();
			this->processMap = new map<DWORD, BaseProcess>();
			this->pids = new DWORD[1];
			this->processes = new BaseProcess*[1];
			this->process = new Process();
		}

		~SystemProcessMgr() {
			clearProcesses();
			delete processMap; processMap = NULL;
			delete[] pids; pids = NULL;
			delete[] processes; processes = NULL;
			delete process; process = NULL;
		}

		bool reflashProcessList();
		const BaseProcess& getBaseProcessInfo(DWORD pid);	// ��ȡ�򵥵Ľ�����Ϣ

		DWORD* getAllPIDs();
		BaseProcess** getAllProcesses();	// ��ȡ���н��̶���ĵ�ַ����
		Process* getProcess(DWORD pid);		// ��ȡ���̶���ָ��(����ģ����Ϣ)

	protected:
		bool traverseProcesses();
		void clearProcesses();

		const BaseProcess& addProcess(DWORD pid, string pName);
		bool isX64Process(DWORD pid);
		static bool compare(BaseProcess* aProc, BaseProcess* bProc);	// ���ڵ�sort�ȽϺ��������Ǿ�̬

	private:
		bool IS_X64_OS;
		map<DWORD, BaseProcess>* processMap;	// ��ǰ���̱�
		DWORD* pids;							// ��ǰ���̶����ID����
		BaseProcess** processes;				// ��ǰ���̶����ָ������
		Process* process;						// ��ǰѡ�еĽ���ָ��
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