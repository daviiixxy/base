#ifndef GTP_LOG_H_
#define GTP_LOG_H_

#include <stdarg.h>
#include "debug_log.h"

/* Error Logging */
#define LOC_LOGE0(s) V4_LogErr((s),0)//HT_STRING(UNILOG_GTPLITE, V4Err_0, P_ERROR, "%s", (s))
#define LOC_LOGE1(fmt,a1) V4_LogErr((fmt),1,(a1))//HT_TRACE(UNILOG_GTPLITE, V4Err_1, P_ERROR, 1, (fmt), (a1))
#define LOC_LOGE3(fmt,a1,a2,a3) V4_LogErr((fmt),3,(a1),(a2),(a3))//HT_TRACE(UNILOG_GTPLITE, V4Err_3, P_ERROR, 3, (fmt), (a1),(a2),(a3))
#define LOC_LOGSE1(fmt,s1) V4_LogErr((fmt),1,(s1))
#define LOC_LOGE2(fmt,a1,a2) V4_LogErr((fmt),2,(a1),(a2))

/* Info Logging */
#define LOC_LOGM0(fmt) V4_LogInfo((fmt),0)
#define LOC_LOGH0(fmt) V4_LogInfo((fmt),0)
#define LOC_LOGH1(fmt,a1) V4_LogInfo((fmt),1,(a1))//HT_TRACE(UNILOG_GTPLITE, V4Info_1, P_VALUE, 1, (fmt), (a1))
#define LOC_LOGH2(fmt,a1,a2) V4_LogInfo((fmt),2,(a1),(a2))
#define LOC_LOGSH1(fmt,s1) V4_LogInfo((fmt),1,(s1))

/* Debug Logging */
#define LOC_LOGL0(fmt) V4_LogDbg((fmt),0)
#define LOC_LOGL1(fmt,a1) V4_LogDbg((fmt),1,(a1))
#define LOC_LOGL2(fmt,a1,a2) V4_LogDbg((fmt),2,(a1),(a2))

static inline void V4_LogErr(char *fmt, uint8_t n, ...)
{
	if (n == 0) 
	{
		HT_STRING(UNILOG_GTP_LITE, V4Err_0, P_ERROR, "%s", fmt);
	}
	else
	{
		char buf[256] = {0};
		va_list ap;
		va_start(ap, n);
		vsnprintf(buf,256,fmt,ap);
		HT_STRING(UNILOG_GTP_LITE, V4Err_1, P_ERROR, "%s", buf);
	}
}

static inline void V4_LogInfo(char *fmt, uint8_t n, ...)
{
	if (n == 0)
	{
		HT_STRING(UNILOG_GTP_LITE, V4Info_0, P_VALUE, "%s", fmt);
	}
	else
	{
		char buf[256]= {0};
		va_list ap;
		va_start(ap, n);
		vsnprintf(buf,256,fmt,ap);
		HT_STRING(UNILOG_GTP_LITE, V4Info_1, P_VALUE, "%s", buf);
	}
}

static inline void V4_LogDbg(char *fmt, uint8_t n, ...)
{
	if (n == 0)
	{
		HT_STRING(UNILOG_GTP_LITE, V4Dbg_0, P_DEBUG, "%s", fmt);
	}
	else
	{
		char buf[256]= {0};
		va_list ap;
		va_start(ap, n);
		vsnprintf(buf,256,fmt,ap);
		HT_STRING(UNILOG_GTP_LITE, V4Dbg_1, P_DEBUG, "%s", buf);
	}
}

#endif GTP_LOG_H_
