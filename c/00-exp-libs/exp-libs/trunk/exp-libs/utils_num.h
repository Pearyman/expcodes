/*****************************************
  Description: ���ִ����߰�
  Authod     : EXP
  Modify By  : None
  Date       : 2017-11-14
******************************************/

#pragma once;

#ifndef __UTILS_NUM_H_
#define __UTILS_NUM_H_

	#include "stdafx.h"

	namespace NUM_UTILS {

		/*
		 * �������ַ���ת����long long��ֵ
		 * @param str �����ַ���
		 * @return long long ��ֵ
		 */
		DLL_API const long long toLongLong(const char* str);

		/*
		 * ��long long��ֵת���������ַ���
		 * @param _long long long ��ֵ
		 * @return �����ַ���
		 */
		DLL_API const char* toStr(const long long _long);

	}

#endif
