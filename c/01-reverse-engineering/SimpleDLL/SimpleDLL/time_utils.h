/*****************************************
  Description: ����ʱ�乤�߰�
  Authod     : liaoquanbin
  Modify By  : None
  Date       : 2015-07-20
******************************************/

#pragma once;  

#ifndef __TIME_UTILS_H_
#define __TIME_UTILS_H_

	#include "stdafx.h"

	namespace TIME_UTILS {
		
		/*
		 * ��ȡ1970������UTC��΢��ʱ��ֵ
		 * ����java�ĵ�ǰϵͳʱ�亯��System.currentTimeMillis()�ȼ۵�ʱ��ֵ��
		 * @return ��ǰϵͳʱ��
		 */
		DLL_API const long long getCurrentTimeMillis();

	}

#endif