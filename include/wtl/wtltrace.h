// Windows Template Library - WTL trace helpers
// Copyright (C) Microsoft Corporation, WTL Team. All rights reserved.
//
// This file is a part of the Windows Template Library.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __WTLTRACE_H__
#define __WTLTRACE_H__

#pragma once

#ifndef __cplusplus
	#error wtltrace.h requires C++ compilation (use a .cpp suffix)
#endif

#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <tchar.h>

#ifndef WTL_TRACE_ENABLE
  #ifdef _DEBUG
    #define WTL_TRACE_ENABLE 1
  #else
    #define WTL_TRACE_ENABLE 0
  #endif
#endif

#ifndef WTL_TRACE_LEVEL
  #define WTL_TRACE_LEVEL 0
#endif

#ifndef WTL_TRACE_BUFFER_SIZE
  #define WTL_TRACE_BUFFER_SIZE 1024
#endif

namespace WTL
{

#if WTL_TRACE_ENABLE

inline void __cdecl WtlTraceV(LPCSTR pszFileName, int nLine, LPCSTR pszFormat, va_list args)
{
	char szMessage[WTL_TRACE_BUFFER_SIZE];
	int nCount = _vsnprintf_s(szMessage, _countof(szMessage), _TRUNCATE, pszFormat, args);
	if(nCount < 0)
		szMessage[_countof(szMessage) - 1] = '\0';

	char szOutput[WTL_TRACE_BUFFER_SIZE + 256];
	_snprintf_s(szOutput, _countof(szOutput), _TRUNCATE, "%s(%d): %s", pszFileName, nLine, szMessage);
	::OutputDebugStringA(szOutput);
}

inline void __cdecl WtlTraceV(LPCSTR pszFileName, int nLine, LPCWSTR pszFormat, va_list args)
{
	WCHAR szMessage[WTL_TRACE_BUFFER_SIZE];
	int nCount = _vsnwprintf_s(szMessage, _countof(szMessage), _TRUNCATE, pszFormat, args);
	if(nCount < 0)
		szMessage[_countof(szMessage) - 1] = L'\0';

	WCHAR szOutput[WTL_TRACE_BUFFER_SIZE + 256];
	_snwprintf_s(szOutput, _countof(szOutput), _TRUNCATE, L"%S(%d): %s", pszFileName, nLine, szMessage);
	::OutputDebugStringW(szOutput);
}

inline void __cdecl WtlTrace(LPCSTR pszFileName, int nLine, LPCSTR pszFormat, ...)
{
	va_list args;
	va_start(args, pszFormat);
	WtlTraceV(pszFileName, nLine, pszFormat, args);
	va_end(args);
}

inline void __cdecl WtlTrace(LPCSTR pszFileName, int nLine, LPCWSTR pszFormat, ...)
{
	va_list args;
	va_start(args, pszFormat);
	WtlTraceV(pszFileName, nLine, pszFormat, args);
	va_end(args);
}

#endif // WTL_TRACE_ENABLE

}; // namespace WTL

#if WTL_TRACE_ENABLE
  #define WTLTRACE(...) WTL::WtlTrace(__FILE__, __LINE__, __VA_ARGS__)
  #define WTLTRACE2(category, level, ...) do { if((level) <= WTL_TRACE_LEVEL) WTL::WtlTrace(__FILE__, __LINE__, __VA_ARGS__); } while(0)
#else
  #define WTLTRACE __noop
  #define WTLTRACE2 __noop
#endif

#endif // __WTLTRACE_H__
