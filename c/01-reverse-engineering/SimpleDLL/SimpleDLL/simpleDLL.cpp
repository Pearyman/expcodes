//------------------ SimpleDLL.cpp ----------------

//ע��˴��ĺ궨����Ҫд��#include "SimpleDLL.h"֮ǰ
//�������dll��Ŀ�ڲ�ʹ��__declspec(dllexport)����
//��dll��Ŀ�ⲿʹ��ʱ����__declspec(dllimport)����
#define DLL_IMPLEMENT

#include "SimpleDLL.h"
#include<Windows.h>
#include <intrin.h>
#include <stdlib.h>
#include <string.h>


namespace SIMPLE_UTILS {
	int DLL_API add(int x, int y)
	{
		return x+y;
	}
}

