/*****************************************
  Description: ���� DLL Ӧ�ó������ڵ�
  Authod     : EXP | http://exp-blog.com
  Modify By  : None
  Date       : 2015-07-20
******************************************/

// _WIN32/WIN32 ���������ж��Ƿ� Windows ϵͳ�����ڿ�ƽ̨����
// _WIN64 �����жϱ��뻷���� x86 ���� x64
#ifdef _WIN32

	#include "stdafx.h"
	#include <windows.h>

	BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call,  LPVOID lpReserved)
	{
		switch (ul_reason_for_call)
		{
			case DLL_PROCESS_ATTACH:
			case DLL_THREAD_ATTACH:
			case DLL_THREAD_DETACH:
			case DLL_PROCESS_DETACH:
				break;
		}
		return TRUE;
	}

#endif

