#ifndef GET_PID_BRUTEFORCE_H
#define GET_PID_BRUTEFORCE_H
#pragma once

#include "helper_getpidlib.h"
#include "psalm.h"
#include <Windows.h>
#include <psapi.h>
#include <shlwapi.h>

DWORD GetPidBruteForce(wchar_t* procname);
BOOL MapPidsBruteForce(DWORD* pids, size_t& pCount);
#endif