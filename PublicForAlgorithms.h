#ifndef __PUBLIC_FOR_ALGORITHM__
#define __PUBLIC_FOR_ALGORITHM__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Config.h"

#ifdef _WINDOWS_
#include <windows.h>
#endif

//�������
void Debug(char* s,...)
{
    va_list ap;
    va_start(ap,s);
    vfprintf(stderr,s,ap);
    va_end(ap);
}
//ÿ�����һ��
void LineDebug(char* s,...)
{
    va_list ap;
    va_start(ap,s);
    fprintf(stderr,"Debug:");
    vfprintf(stderr,s,ap);
    va_end(ap);
    fprintf(stderr,"\n");
}

//__VA_ARGS__��ҪC99֧��
#ifdef _DEBUG_OPEN_
    #ifndef _DEBUG_CLOSE_
	#ifdef __C_99__
	    #define DEBUG(...) Debug(__VA_ARGS__)
	#else
	    #define DEBUG(format,args...) Debug(format,##args);
	#endif
    #else
	#define DEBUG(...)
    #endif
#else
    #define DEBUG(...) 
#endif

#ifdef _DEBUG_OPEN_
    #ifndef _DEBUG_CLOSE_
	#ifdef __C_99__
	    #define LINE_DEBUG(...) LineDebug(__VA_ARGS__)
	#else
	    #define LINE_DEBUG(format,args...) LineDebug(format,##args);
	#endif
    #else
	#define LINE_DEBUG(format,args...)
    #endif
#else
    #define LINE_DEBUG(format,args...)
#endif

//windows�µ���ͣ
#ifdef _WINDOWS_
#define PAUSE() system("pause")
#else
#define PAUSE()
#endif

#define INT_MAX ~0x00;
//��ȫɾ��mallocָ��
#define SAFE_FREE(x) if(x!=NULL){free(x);x=NULL;}

//����C���õ�bool
typedef int bool;
#define true  1
#define false 0

//����״̬
typedef int Status;

//����ͼ����������
#define DIGRAPH      0X00000001  //����ͼ
#define UNDIGRAPH    0X00000010  //����ͼ
#define CYCLIC       0X00000100  //�л�
#define ACYCLIC      0X00001000  //�޻�
#define CONNECTED    0X00010000  //��ͨ
#define UNCONNECTED  0X00100000  //����ͨ
#define WEIGHTYES    0X01000000  //��Ȩ
#define WEIGHTNO     0X10000000  //����Ȩ











#endif
