// SimpleDLLTest.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include "../SimpleDLL/simpleDLL.h" //���ͷ�ļ�����
#include "../SimpleDLL/time_utils.h"
#pragma comment(lib, "..\\x64\\Debug\\SimpleDLL.lib") //���lib�ļ����� 
#include <process.h>
#include <locale.h>
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	cout << SIMPLE_UTILS::add(1, 2) << endl;
	cout << TIME_UTILS::getCurrentTimeMillis() << endl;
	system("pause");
	return 0;
}
