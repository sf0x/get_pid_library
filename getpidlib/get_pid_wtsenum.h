#ifndef GET_PID_WTSENUM_H
#define GET_PID_WTSENUM_H
#pragma once

#include <Windows.h>
#include <WtsApi32.h>

#pragma comment(lib, "wtsapi32.lib")

DWORD GetPidWtsEnum(wchar_t*);
BOOL MapPidsWtsEnum(DWORD* pids, size_t& pCount);
#endif