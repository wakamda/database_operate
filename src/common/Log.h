#ifndef _LOG_H
#define _LOG_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static bool _bfirst_ = true;

inline void print2windows(const char *pfile, const char *pfunname, int line, const char *args, ...)
{
	int	second = 0;
	time_t timep;
	struct tm *st;
	timep = clock();
	second = (timep % 1000) * 1000;
	time(&timep);
	st = localtime(&timep);	/* 获取本地时间 */
	/*(1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday,
		p->tm_hour, p->tm_min, p->tm_sec, second)*/
	if (_bfirst_)
	{
		_bfirst_ = false;
		printf("==========================================================\n");
		printf("==                     %02d-%02d-%02d                       ==\n", 1900 + st->tm_year, 1 + st->tm_mon, st->tm_mday);
		printf("==========================================================\n");
	}
	char message[1024];
	memset(message, 0, 1024);
	va_list ap;
	va_start(ap, args);
	vsnprintf(message, 1024, args, ap);
	va_end(ap);

	char file[256] = { 0 };
	strcpy(file, strrchr(pfile, '\\') == 0 ? pfile : strrchr(pfile, '\\') + 1);
	printf("[%02d:%02d:%02d:%03d] [%s] [Line in %d] [%s] : %s\n", st->tm_hour, st->tm_min, st->tm_sec, second, file, line, pfunname, message);
}

#define Tprint(...) print2windows(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);

#endif //_LOG_H