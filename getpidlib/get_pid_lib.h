// Syscalls used: NtGetNextProcess,NtQuerySystemInformation,NtAllocateVirtualMemory,NtFreeVirtualMemory,NtOpenProcess,NtOpenProcessToken,NtQueryInformationToken

#ifndef GET_PID_LIB_H
#define GET_PID_LIB_H
#pragma once

#include "helper_getpid.h"
#include "helper_getpidlib.h"
#include <Windows.h>

#define DEBUG_GET_PID 0

/*
* PID Search Methods:
* 0: ALL - Debug
* 1: Brute Force
* 2: EnumProcesses
* 3: NtGetNextProcess
* 4: NtQuerySystemInformation
* 5: Thelp32
* 6: WMI
* 7: WTSEnum
*/
#define GET_PID_METHOD 0

#if GET_PID_METHOD == 0
#include "get_pid_bruteforce.h"
#include "get_pid_enum.h" 
#include "get_pid_ntgetnext.h"
#include "get_pid_ntqueryinfo.h"
#include "get_pid_thelp32.h" 
#include "get_pid_wmi.h"
#include "get_pid_wtsenum.h"
#endif
#if GET_PID_METHOD == 1
#include "get_pid_bruteforce.h"
#endif
#if GET_PID_METHOD == 2
#include "get_pid_enum.h" 
#endif
#if GET_PID_METHOD == 3
#include "get_pid_ntgetnext.h"
#endif
#if GET_PID_METHOD == 4
#include "get_pid_ntqueryinfo.h"
#endif
#if GET_PID_METHOD == 5
#include "get_pid_thelp32.h" 
#endif
#if GET_PID_METHOD == 6
#include "get_pid_wmi.h"
#endif
#if GET_PID_METHOD == 7
#include "get_pid_wtsenum.h"
#endif 
 
#define MAX_PIDS 2048

BOOL GetPid(wchar_t *procname, DWORD &pid);
BOOL MapProcPids(DWORD *pids, size_t &pidsCount);
BOOL GetRandomPidPull(DWORD *processIds, size_t &pidCount, DWORD &pid);
#endif