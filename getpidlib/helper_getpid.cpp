#include "helper_getpid.h"

#pragma optimize("", off)
bool MyMemCopy(PBYTE out, PBYTE in, size_t len) {
    if (!in || !out || len < 1)
        return false;
    for (size_t i = 0; i < len; i++) {
        out[i] = in[i];
    }
    return true;
}
#pragma optimize( "", on ) 


#pragma optimize( "", off ) 
bool MySecureZeroMemory(PBYTE in, size_t inLen) {
    if (inLen < 1)
        return FALSE;
    for (int i = 0; i < inLen; i++) {
        in[i] = '\0';
    }
    return TRUE;
}
#pragma optimize( "", on ) 

BYTE RandByte() {
    unsigned int s1;
    unsigned int s2;
    unsigned int s3;
    unsigned int s4;
    rand_s(&s1);
    rand_s(&s2);
    rand_s(&s3);
    rand_s(&s4);

    BYTE i1;
    BYTE i2;
    BYTE i3;
    BYTE i4;

    BYTE tmp = 0x00;
    BYTE k = 0x01;

    i1 = (BYTE)s1;
    i2 = (BYTE)s2;
    i3 = (BYTE)s3;
    i4 = (BYTE)s4;

    k = s1;
    k = k << 4;

    tmp = s3;
    tmp = tmp << 2;
    k = k ^ tmp;
    tmp = s4;
    tmp = tmp << 1;
    k = k ^ s2;
    k = k ^ tmp;

    return k;
}


wchar_t* CharToWchar(const char* str) {
    // Handle null or empty input
    if (str == nullptr || *str == '\0') {
        wchar_t* emptyStr = new(std::nothrow) wchar_t[1];
        if (emptyStr) emptyStr[0] = L'\0';
        return emptyStr;
    }

    try {
        size_t outSize = strlen(str) + 1;
        wchar_t* outStr = new(std::nothrow) wchar_t[outSize];
        if (!outStr) throw std::bad_alloc();

        size_t count = 0;
        errno_t err = mbstowcs_s(&count, outStr, outSize, str, outSize - 1);
        if (err != 0) {
            delete[] outStr;
            wchar_t* emptyStr = new(std::nothrow) wchar_t[1];
            if (emptyStr) emptyStr[0] = L'\0';
            return emptyStr;
        }
        return outStr;
    }
    catch (...) {
        wchar_t* emptyStr = new(std::nothrow) wchar_t[1];
        if (emptyStr) emptyStr[0] = L'\0';
        return emptyStr;
    }
}

char* WcharToChar(const wchar_t* wstr) {
    // Handle null or empty input
    if (wstr == nullptr || *wstr == L'\0') {
        char* emptyStr = new(std::nothrow) char[1];
        if (emptyStr) emptyStr[0] = '\0';
        return emptyStr;
    }

    try {
        size_t outSize = wcslen(wstr) + 1;
        char* outStr = new(std::nothrow) char[outSize];
        if (!outStr) throw std::bad_alloc();

        size_t count = 0;
        errno_t err = wcstombs_s(&count, outStr, outSize, wstr, outSize - 1);
        if (err != 0) {
            delete[] outStr;
            char* emptyStr = new(std::nothrow) char[1];
            if (emptyStr) emptyStr[0] = '\0';
            return emptyStr;
        }
        return outStr;
    }
    catch (...) {
        char* emptyStr = new(std::nothrow) char[1];
        if (emptyStr) emptyStr[0] = '\0';
        return emptyStr;
    }
}
