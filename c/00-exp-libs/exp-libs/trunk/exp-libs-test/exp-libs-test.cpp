// exp-libs-test.cpp : �������̨Ӧ�ó������ڵ㡣
// �ο��̳̣���VS2010��д��̬���ӿ�DLL����Ԫ���������� http://blog.csdn.net/testcs_dn/article/details/27237509

#include "stdafx.h"
#include "..\\exp-libs\utils_time.h"
#include "..\\exp-libs\utils_num.h"
#include "..\\exp-libs\\utils_str.h"
#include "..\\exp-libs\\utils_log.h"
#include "..\\exp-libs\\utils_crypto.h"
#include "..\\exp-libs\\utils_os.h"

#include <string>
#include <iostream>
using namespace std;

#pragma comment(lib, "..\\x64\\Debug\\exp-libs.lib")	// ���dll��(��������)�������includeͷ�ļ�֮��


int _tmain(int argc, _TCHAR* argv[])
{
	cout << TIME_UTILS::getCurrentTimeMillis() << endl;
	cout << NUM_UTILS::toStr(1234LL) << endl;
	cout << STR_UTILS::toUpperCase("abC12XDsdk") << endl;
	cout << LOG_UTILS::log("line1", false) << endl;
	cout << LOG_UTILS::log("line2", true) << endl;
	cout << CRYPTO_UTILS::toMD5("asfjhsj128y89&&32", "explibs") << endl;
	cout << OS_UTILS::isX64() << endl;
	cout << string(STR_UTILS::toChar(_T("ABCf134"))) << endl;

	wprintf(STR_UTILS::toWChar("System.console"));
	cout << endl;

	OS_UTILS::copyToClipboard("abcd���������uasa");
	const char* data = OS_UTILS::pasteFromClipboard();
	cout << data << endl;
	
	system("pause");
	return 0;
}

