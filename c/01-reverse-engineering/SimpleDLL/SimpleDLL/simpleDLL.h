//------------------ SimpleDLL.h ----------------

#pragma once;

//�ú������dll��Ŀ�ڲ�ʹ��__declspec(dllexport)����
//��dll��Ŀ�ⲿʹ��ʱ����__declspec(dllimport)����


#ifndef __SIMPLE_H_
#define __SIMPLE_H_

	#include "stdafx.h"

	namespace SIMPLE_UTILS {
		DLL_API int add(int x, int y); //�򵥷���
	}
	

#endif