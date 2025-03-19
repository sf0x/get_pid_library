#pragma once

#define _WIN32_DCOM
#include "get_pid_lib.h"
#include <Windows.h>
#include <Wbemidl.h>
#include <comutil.h>
#include <string>
#include <UserEnv.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "comsuppw.lib")

DWORD GetPidWmi(const wchar_t* targetProcName);
DWORD MapPidsWMI(DWORD* pids, size_t& pCount);