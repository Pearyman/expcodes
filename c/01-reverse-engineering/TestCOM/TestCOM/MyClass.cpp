// MyClass.cpp : CMyClass ��ʵ��

#include "stdafx.h"
#include "MyClass.h"


// CMyClass



STDMETHODIMP CMyClass::add(LONG a, LONG b, LONG* result)
{
	// TODO: �ڴ����ʵ�ִ���
	*result = a + b;
	return S_OK;
}
