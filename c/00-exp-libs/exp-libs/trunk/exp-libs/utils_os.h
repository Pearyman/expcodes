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

		/*
		 * �жϵ�ǰϵͳ�Ƿ�Ϊ64λ
		 * @return true:64λ; false:32λ
		 */
		DLL_API bool isX64();

		/*
		 * �����ı����ݵ�������
		 * @param pData �ı�����
		 * @return true:���Ƴɹ�; false:����ʧ��
		 */
		DLL_API bool copyToClipboard(const char* pData);

		/*
		 * �����ı����ݵ�������
		 * @param pData �ı�����
		 * @param len �ı����ݳ���
		 * @return true:���Ƴɹ�; false:����ʧ��
		 */
		DLL_API bool copyToClipboard(const char* pData, const int len);

		/*
		 * �Ӽ������ȡ�ı�����
		 * @return �ı�����
		 */
		DLL_API const char* pasteFromClipboard();

	}

#endif
