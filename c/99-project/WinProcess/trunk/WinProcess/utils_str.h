/*****************************************
  Description: �ַ��������߰�
  Authod     : EXP
  Modify By  : None
  Date       : 2017-11-14
******************************************/

#pragma once;

#ifndef __UTILS_STR_H_
#define __UTILS_STR_H_

	#include "stdafx.h"

	namespace STR_UTILS {

		/*
		 * �����ַ�������
		 * @param str �ַ���
		 * @return �ַ�������
		 */
		DLL_API const int sLen(const char* str);

		/*
		 * ��ת�ַ���
		 * @param str �ַ���
		 * @return ��ת���ַ���
		 */
		DLL_API const char* reverse(const char* str);

		/*
		 * ��ȡ�Ӵ�
		 * @param str �ַ���
		 * @param start ��ʼ�±꣨����������С0�Զ�����Ϊ0
		 * @param end ��ֹ�±꣨���������������ڴ����Զ�����Ϊ����
		 * @return �Ӵ�
		 */
		DLL_API const char* substr(const char* str, const int start, const int end);

		/*
		 * �ַ���ƴ��
		 * @param str1 �ַ���1
		 * @param str2 �ַ���2
		 * @return str1 + str2
		 */
		DLL_API const char* concat(const char* str1, const char* str2);

		/*
		 * ���ַ���������Ӣ���ַ�ת��Ϊ��д
		 * @param str �ַ���
		 * @return ת���ɴ�д���ַ���
		 */
		DLL_API const char* toUpperCase(const char* str);

		/*
		 * ���ַ���������Ӣ���ַ�ת��ΪСд
		 * @param str �ַ���
		 * @return ת����Сд���ַ���
		 */
		DLL_API const char* toLowCase(const char* str);

		/*
		 * �Ƚ��ַ�����ֵ�Ƿ���ͬ
		 * @param str1 �ַ���1
		 * @param str2 �ַ���2
		 * @return true:��ͬ; false:��ͬ
		 */
		DLL_API const bool isEqual(const char* str1, const char* str2);

		/*
		 * �ͷ��ַ���ָ��ָ����ڴ�
		 * @param str �ַ���ָ��
		 */
		DLL_API void sFree(const char* str);

		/*
		 * �ͷ��ַ���ָ��ָ����ڴ�
		 * @param str �ȿ��ַ���ָ��
		 */
		DLL_API void sFree(const wchar_t* str);

		/*
		 * ��[����]ת����[�ȿ��ַ�����(unicode)]
		 * @param num ����
		 * @return �ȿ��ַ�����(unicode)
		 */
		DLL_API wchar_t* toWChar(const int num);

		/*
		 * ��[���ȿ��ַ�����]ת����[�ȿ��ַ�����(unicode)]
		 * @param _char ���ȿ��ַ�����
		 * @return �ȿ��ַ�����(unicode)
		 */
		DLL_API wchar_t* toWChar(const char* _char);

		/*
		 * ��[�ȿ��ַ�����(unicode)]ת����[���ȿ��ַ�����]
		 * @param _wchar �ȿ��ַ�����(unicode)
		 * @return ���ȿ��ַ�����
		 */
		DLL_API char* toChar(const wchar_t* _wchar);

	}

#endif