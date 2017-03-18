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

//自由输出
void Debug(char* s,...)
{
    va_list ap;
    va_start(ap,s);
    vfprintf(stderr,s,ap);
    va_end(ap);
}
//每次输出一行
void LineDebug(char* s,...)
{
    va_list ap;
    va_start(ap,s);
    fprintf(stderr,"Debug:");
    vfprintf(stderr,s,ap);
    va_end(ap);
    fprintf(stderr,"\n");
}

//__VA_ARGS__需要C99支持
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

//windows下的暂停
#ifdef _WINDOWS_
#define PAUSE() system("pause")
#else
#define PAUSE()
#endif

#define INT_MAX ~0x00;
//安全删除malloc指针
#define SAFE_FREE(x) if(x!=NULL){free(x);x=NULL;}

//定义C能用的bool
typedef int bool;
#define true  1
#define false 0

//定义状态
typedef int Status;

//定义图的性质类型
#define DIGRAPH      0X00000001  //有向图
#define UNDIGRAPH    0X00000010  //无向图
#define CYCLIC       0X00000100  //有环
#define ACYCLIC      0X00001000  //无环
#define CONNECTED    0X00010000  //连通
#define UNCONNECTED  0X00100000  //非连通
#define WEIGHTYES    0X01000000  //带权
#define WEIGHTNO     0X10000000  //不带权











#endif
