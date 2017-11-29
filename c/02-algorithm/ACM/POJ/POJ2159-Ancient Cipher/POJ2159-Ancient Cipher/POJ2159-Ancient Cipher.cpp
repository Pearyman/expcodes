/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 2159
	Problem:    Ancient Cipher
	URL:		http://poj.org/problem?id=2159
*/

/*
	���������
	  ��һ���ģ�����д��ĸ���У�����<100����
	  ����ʹ�� �������ܣ��滻���ܣ� �� ������� ��õ�����
	  ���������ּ��ܵ��ص㣬���������ıض��ȳ�����ͬΪ����д��ĸ���С�
	  �ָ���һ�����ĺ����ģ��²������Ƿ���ԡ�

	  ������Ҫ��ȷ�����ּ��ܷ�ʽ���ص㣺
	  �� �������ܣ���������������ĸ������ĸ������ǰ/���Թ̶�ֵƫ�Ʋ��滻
	  �� ������ܣ��������������������ÿ����ĸ��λ��

	  ����˼·����Ϊ���϶���ͨ��ĳ���ֶ�������ļ��ܻ�����Ľ��ܣ��Խ���ַ������бȽ�.
	  ����������Ŀ��δ�����������˴˷��������� 
	  ��������ֻ�п������ܣ��ǿ���ͨ����ײ26��ƫ��ֵ������ԭ�ģ�
	  �����ڻ�����������ܣ��������ĳ������Ϊ100������������������ǲ����ܵģ�


	  Ϊ����������ͨ���Ƚ����ĺ������ڼ���ǰ����Ȼ���еĹ����������²������Ƿ���ԣ�
	  �� ���ĺ����ĵȳ�
	  �� �������ֻ�ı�����������ĸ��˳��ԭ������ĸ��û�з����仯
	  �� ��������ÿ����ĸ����һ����������������ֻ�ı��˱������ƣ��ñ������ֵĴ���û�з����仯
	  �� �ۺϢ٢ڢۣ����ֱ�����ĺ�����ÿ����ĸ���в������ֱ����ÿ����ĸ�ĳ���Ƶ�Σ�
	     Ȼ���Ƶ���������������ĺ���������Եģ����Եõ�������ȫһ����Ƶ������
	  �� �Ƚ�Ƶ�����л������ײ���ʣ��༴ֻ�����ƽ⣨��������Ŀû�и�����������������ܵõ�׼ȷ�⣩
*/

#include <algorithm>
#include <iostream>
using namespace std;


const int MAX_LEN = 101;	// ����/������󳤶�
const int FRE_LEN = 26;	// Ƶ�����鳤��


void countFrequency(char* _in_str, int* _out_frequency);
bool isSame(int* aAry, int* bAry);

int main(void) {
	char cipher[MAX_LEN] = { '\0' };	// ����
	char text[MAX_LEN] = { '\0' };		// ����
	int cFrequency[FRE_LEN] = { 0 };	// ����Ƶ������
	int tFrequency[FRE_LEN] = { 0 };	// ����Ƶ������

	cin >> cipher >> text;
	countFrequency(cipher, cFrequency);
	countFrequency(text, tFrequency);

	cout << (isSame(cFrequency, tFrequency) ? "YES" : "NO") << endl; 

	//system("pause");
	return 0;
}


void countFrequency(char* _in_str, int* _out_frequency) {
	for(int i = 0; *(_in_str + i) != '\0'; i++) {
		*(_out_frequency + (*(_in_str + i) - 'A')) += 1;
	}
	sort(_out_frequency, _out_frequency + FRE_LEN);
}

bool isSame(int* aAry, int* bAry) {
	bool isSame = true;
	for(int i = 0; i < FRE_LEN; i++) {
		isSame = (*(aAry + i) == *(bAry + i));
		if(isSame == false) {
			break;
		}
	}
	return isSame;
}