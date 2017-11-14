
#include "stdafx.h"
#include "str_utils.h"

TCHAR* toWChar(const int num) {
	TCHAR* _out_wchar = new TCHAR[22];	// int32�Ϊ11λ, int64�Ϊ21λ
	wsprintf(_out_wchar, _T("%d"), num);
	return _out_wchar;
}

TCHAR* toWChar(const char* _char) {
	int len = MultiByteToWideChar (CP_ACP, 0, _char, (strlen(_char) + 1), NULL, 0) ;  
	TCHAR* _out_wchar = new TCHAR[len];	// �ѿռ�new�ľֲ���������delete֮ǰ�����ͷ�

	MultiByteToWideChar (CP_ACP, 0, _char, (strlen(_char) + 1), _out_wchar, len) ;  
	return _out_wchar;
}

char* toChar(const TCHAR* _wchar) {
	int len = WideCharToMultiByte(CP_ACP, 0, _wchar, -1, NULL, 0, NULL, NULL);
	char* _out_char = new char[len];	// �ѿռ�new�ľֲ���������delete֮ǰ�����ͷ�

	WideCharToMultiByte(CP_ACP, 0, _wchar, -1, _out_char, len, NULL, NULL);   
	return _out_char;
}
