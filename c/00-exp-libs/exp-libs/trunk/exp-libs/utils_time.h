/*****************************************
  Description: ����ʱ�乤�߰�
  Authod     : EXP
  Modify By  : None
  Date       : 2017-11-14
******************************************/

#pragma once;  

#ifndef __UTILS_TIME_H_
#define __UTILS_TIME_H_

	#include "stdafx.h"

	namespace TIME_UTILS {
		
		/*
		 * ��ȡ1970������UTC�ĺ���ʱ��ֵ
		 * ����java�ĵ�ǰϵͳʱ�亯��System.currentTimeMillis()�ȼ۵�ʱ��ֵ��
		 * @return ��ǰϵͳʱ��
		 */
		DLL_API const long long getCurrentTimeMillis();

	}

#endif