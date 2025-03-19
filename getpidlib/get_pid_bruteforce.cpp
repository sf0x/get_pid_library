#include "get_pid_bruteforce.h"

DWORD GetPidBruteForce(wchar_t* procname) {
    // PIDs are always a multiple of 4 and are created iteratly
	for (int i = 4; i < 40000; i=i+4) {
        HANDLE hProcess;
        OBJECT_ATTRIBUTES oa;
        InitializeObjectAttributes(&oa, NULL, 0, NULL, NULL);
        CLIENT_ID cid;
        cid.UniqueProcess = (PVOID)i;
        cid.UniqueThread = (PVOID)0;
        if (NT_SUCCESS(PsalmNtOpenProcess(&hProcess, PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, &oa, &cid))) {
            TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
            K32GetProcessImageFileNameW(hProcess, szProcessName, MAX_PATH);
            if (!lstrcmpiW(procname, PathFindFileName(szProcessName))) {
                CloseHandle(hProcess);
                return i;
            }
            CloseHandle(hProcess);
        }
	}
    return 0;
}

BOOL MapPidsBruteForce(DWORD* pids, size_t& pCount) {
    if (pCount == 0)
        return FALSE;
    size_t maxPids = pCount;
    pCount = 0;
    size_t maxBound = maxPids * 4;
    for (int i = 0; i < maxBound; i = i + 4) {
        HANDLE hProcess;
        OBJECT_ATTRIBUTES oa;
        InitializeObjectAttributes(&oa, NULL, 0, NULL, NULL);
        CLIENT_ID cid;
        cid.UniqueProcess = (PVOID)i;
        cid.UniqueThread = (PVOID)0;
        if (NT_SUCCESS(PsalmNtOpenProcess(&hProcess, PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, &oa, &cid))) {
            pids[pCount] = i;
            pCount++;
            CloseHandle(hProcess);
        } 
        if (pCount >= maxPids)
            break;
    }
    return TRUE;
}