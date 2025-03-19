#ifndef GET_PID_NTGETNEXT_H
#define GET_PID_NTGETNEXT_H
#pragma once

#include "psalm.h"
#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include <shlwapi.h>
#include "helper_getpidlib.h" 
 
#pragma comment(lib, "shlwapi.lib")

DWORD GetPidNtGetNextProc(wchar_t* procname);
BOOL MapPidsNtGetNextProc(DWORD *pids, size_t &pCount);

#endif