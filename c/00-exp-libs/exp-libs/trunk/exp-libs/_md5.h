/*****************************************
  Description: MD5�㷨
  Authod     : Internet: [http://blog.csdn.net/flydream0/article/details/7045429]
  Modify By  : EXP
  Date       : 2017-11-14
******************************************/

#pragma once;  

#ifndef __MD5_H_
#define __MD5_H_

	#include <string>
	#include <fstream>
	using std::string;
	using std::ifstream;

	/* Type define */
	typedef unsigned char _byte;

	// MD5�㷨�����_ulong������λ�����㣬���뱣֤ 32bit��64bit �����ݵȳ�
	// �������Ϊ���ݱ��ض����⣬���� 32bit��64bit ƽ̨����������һ�¡�
	#ifdef _LP64	
		typedef unsigned long _ulong;
	#else
		typedef unsigned long long _ulong;  // ��ʵ����32����64��ֱ������long long���ɹ̶�����Ϊ64
	#endif

	/* MD5 declaration. */
	class MD5 {
		public:
			MD5();
			MD5(const void *input, size_t length);  // �����ַ�����MD5�루�Ƽ���
			MD5(const string &str);	// �����ַ�����MD5��
			MD5(ifstream &in);		// �����ļ�����MD5��
			
			const string toString();	// ����MD5��
			const char* toCharArray();	// ����MD5�� ������string.c_str()�Ƕѿռ䣬�޷��־ñ��棬�����Ӵ˷�����

		private:
            string bytesToHexString(const _byte *input, size_t length);
            
			void *(memset) (void *s, int c, size_t n);	// �ڴ�����ã�ʵ�ֲ��õ���c���Դ�룬Ŀ����Ϊ��ƽ̨�޹أ�
			void *memcpy(void *dst, const void *src, size_t len);// �ڴ�鸴�ƣ�ʵ�ֲ��õ���c���Դ�룬Ŀ����Ϊ��ƽ̨�޹أ�

		private:
            void reset();
            const _byte* digest();

			void update(const void *input, size_t length);
			void update(const string &str);
			void update(ifstream &in);
			void update(const _byte *input, size_t length);
			void transform(const _byte block[64]);
            void final();

			void encode(const _ulong *input, _byte *output, size_t length);
			void decode(const _byte *input, _ulong *output, size_t length);
			
			/* class uncopyable */
			MD5(const MD5&);
			MD5& operator=(const MD5&);

        private:
			_ulong _state[4]; /* state (ABCD) */
			_ulong _count[2]; /* number of bits, modulo 2^64 (low-order word first) */
			_byte _buffer[64]; /* input buffer */
			_byte _digest[16]; /* message digest */
			bool _finished;  /* calculate finished ? */

			const static _byte PADDING[64]; /* padding for calculate */
			const static char HEX[16];		// 16���Ʊ�

			const static size_t BUFFER_SIZE = 1024;
	};


#endif/*_MD5_H_*/