/*****************************************
  Description: ϵͳ���߰�
  Authod     : EXP
  Modify By  : None
  Date       : 2017-11-14
******************************************/

#pragma once;

#ifndef __UTILS_OS_H_
#define __UTILS_OS_H_

	#include "stdafx.h"

	namespace OS_UTILS {

		DLL_API bool isX64();

		DLL_API bool copyToClipboard(const char* pData);

		DLL_API bool copyToClipboard(const char* pData, const int len);

		DLL_API const char* pasteFromClipboard();

	}

#endif
