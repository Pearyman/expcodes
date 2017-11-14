#pragma once

#include "stdafx.h"
#include "utils_os.h"

#include <Windows.h>
#include <string>
#include <map>
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



class ProcessModule : public Process {
	public:
		DWORD mSize;		// modBaseSize ģ���С���ֽڣ�
		DWORD mID;			// th32ModuleID, �˳�Ա�Ѿ����ٱ�ʹ�ã�ͨ��������Ϊ1
		DWORD usage;		// GlblcntUsage �� ProccntUsage ȫ��ģ���ʹ�ü�������ģ��������������ͨ����һ����û�������
		BYTE* baseAddr;		// modBaseAddr ģ���ַ�����������̷�Χ�ڣ�
		HMODULE hModule;	// hModule ģ������ַ�����������̷�Χ�ڣ�
		string mName;		// szModule[MAX_MODULE_NAME32 + 1];	 NULL��β���ַ��������а���ģ������
		string mPath;		// szExePath[MAX_PATH];	 NULL��β���ַ��������а�����λ�ã���ģ���·����

		ProcessModule() : Process() {

		}
};

/************************************************************************/
/* 
��ע�༭
modBaseAddr��hModule�ĳ�Աֻ����ָ����th32ProcessID�����в���Ч��

---->  me32.dwSize==1080
---->  me32.GlblcntUsage==2
---->  me32.hModule==0xfd930000
---->  me32.modBaseAddr==0xfd930000
---->  me32.ProccntUsage==2
---->  me32.szExePath==C:\Windows\system32\CRYPTBASE.dll
---->  me32.szModule==CRYPTBASE.dll
---->  me32.th32ModuleID==1
---->  me32.th32ProcessID==664
---->  CNT==16

---->  me32.dwSize==1080
---->  me32.GlblcntUsage==2
---->  me32.hModule==0xff760000
---->  me32.modBaseAddr==0xff760000
---->  me32.ProccntUsage==2
---->  me32.szExePath==C:\Windows\system32\ADVAPI32.dll
---->  me32.szModule==ADVAPI32.dll
---->  me32.th32ModuleID==1
---->  me32.th32ProcessID==664
---->  CNT==17

---->  me32.dwSize==1080
---->  me32.GlblcntUsage==8
---->  me32.hModule==0xff240000
---->  me32.modBaseAddr==0xff240000
---->  me32.ProccntUsage==8
---->  me32.szExePath==C:\Windows\SYSTEM32\sechost.dll
---->  me32.szModule==sechost.dll
---->  me32.th32ModuleID==1
---->  me32.th32ProcessID==664
---->  CNT==18*/
/************************************************************************/


/************************************************************************/
/* ϵͳ���̼��������                                                   */
/************************************************************************/ 
class SystemProcessMgr
{
	public:
		SystemProcessMgr() {
			IS_X64_OS = OS_UTILS::isX64();
			processMap = new map<DWORD, Process>();
			pids = new DWORD[1];
			processes = new Process*[1];
		}

		~SystemProcessMgr() {
			clearProcesses();
			delete processMap;
			delete pids;
			delete processes;
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
};


//��psaipi.dll�еĺ���EnumProcesses����ö�ٽ��� 
typedef BOOL (_stdcall *ENUMPROCESSES)(  //ע������Ҫָ������Լ��Ϊ-stdcall
	DWORD* pProcessIds,  //ָ�����ID������  
	DWORD cb,    //ID����Ĵ�С�����ֽڼ���
	DWORD* pBytesReturned);   //���ص��ֽ�

//��psapi.dll�еĺ���EnumProcessModules����ö�ٽ���ģ��
typedef BOOL (_stdcall *ENUMPROCESSMODULES)(
	HANDLE hProcess,   //���̾��
	HMODULE* lphModule, //ָ��ģ����������
	DWORD cb,    //ģ���������С���ֽڼ���
	LPDWORD lpcbNeeded);   //�洢����ģ����������ֽ���

//��psapi.dll�еĺ���GetModuleFileNameEx��ý���ģ����
typedef DWORD (_stdcall *GETMODULEFILENAMEEX)(
	HANDLE hProcess,   //���̾��
	HMODULE hModule,   //����ģ����
	LPTSTR lpFilename,   //���ģ��ȫ·����
	DWORD nSize    //lpFilename��������С���ַ�����
	);