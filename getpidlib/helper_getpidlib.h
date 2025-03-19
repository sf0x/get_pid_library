#ifndef helper_getpidlib_H
#define helper_getpidlib_H
#pragma once

#include "psalm.h"
#include <cwchar>
#include <cstring>
#include <stdexcept>
#include <new>
#include <iostream>
#include <Windows.h>
#include <sddl.h>

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

void PrintPids(const char* method, DWORD* pids, size_t pCount);
void ResetPids(DWORD* pids, size_t& pCount, size_t maxPids);
LPWSTR GetCurrentSID();
#endif