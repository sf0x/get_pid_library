#ifndef GET_PID_ENUM_H
#define GET_PID_ENUM_H
#pragma once

#include "psalm.h"
#include "get_pid_lib.h"
#include "helper_getpidlib.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

DWORD GetPidEnumCall(const wchar_t* procname);
BOOL MapPidsEnumProcesses(DWORD* pids, size_t& pCount);
#endif