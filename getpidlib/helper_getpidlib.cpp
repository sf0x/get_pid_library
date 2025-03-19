#include "helper_getpidlib.h"

void PrintPids(const char *method, DWORD *pids, size_t pCount) {
    std::cout << "PID Map, found " << pCount << " processes via " << method << ": [";
    for (int i = 0; i < pCount; i++) {
        std::cout << pids[i] << ", ";
    }
    std::cout << "]" << std::endl;
    return;
}

void ResetPids(DWORD *pids, size_t &pCount, size_t maxPids) {
    for (int i = 0; i < maxPids; i++) {
        pids[i] = 0;
    }
    pCount = maxPids;
}

LPWSTR GetCurrentSID() {
    HANDLE hToken;
    PsalmNtOpenProcessToken((HANDLE)-1, TOKEN_QUERY, &hToken);
    DWORD dwLength;
    PsalmNtQueryInformationToken(hToken, TokenUser, nullptr, 0, &dwLength);
    TOKEN_USER* pTokenUser = (TOKEN_USER*)malloc(dwLength);
    PsalmNtQueryInformationToken(hToken, TokenUser, pTokenUser, dwLength, &dwLength);
    LPWSTR pSidString;
    ConvertSidToStringSidW(pTokenUser->User.Sid, &pSidString);
    free(pTokenUser);
    CloseHandle(hToken);
    return pSidString;
}