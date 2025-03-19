#ifndef HELPER_H
#define HELPER_H
#pragma once
#define _CRT_RAND_S
#include <Windows.h>
#include <new>


bool MyMemCopy(PBYTE out, PBYTE in, size_t len);
bool MySecureZeroMemory(PBYTE in, size_t inLen);
BYTE RandByte();
wchar_t* CharToWchar(const char* str);
char* WcharToChar(const wchar_t* wstr);

#endif // HELPER_H