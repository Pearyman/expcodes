// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�


// ��DLL_IMPLEMENT��*.cpp�ж���  
#ifdef DLL_IMPLEMENT  
#define DLL_API __declspec(dllexport)  // ��dll��Ŀ�ڲ�ʹ��ʱ�򵼳� 
#else  
#define DLL_API __declspec(dllimport)  // ��dll��Ŀ�ⲿʹ��ʱ����
#endif
