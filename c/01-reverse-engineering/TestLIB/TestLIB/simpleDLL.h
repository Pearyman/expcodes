//------------------ SimpleDLL.h ----------------

#pragma once;

//�ú������dll��Ŀ�ڲ�ʹ��__declspec(dllexport)����
//��dll��Ŀ�ⲿʹ��ʱ����__declspec(dllimport)����
//��DLL_IMPLEMENT��SimpleDLL.cpp�ж���

#include "stdafx.h"
DLL_API int add(int x, int y); //�򵥷���