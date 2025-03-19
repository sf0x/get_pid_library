#ifndef GET_PID_THELP32_H
#define GET_PID_THELP32_H
#pragma once

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlhelp32.h>

DWORD GetPidThelp32(wchar_t*);
BOOL MapPidsThelp32(DWORD* pids, size_t& pCount); 
#endif
