#include "get_pid_enum.h"

DWORD GetPidEnumCall(const wchar_t* procname) {
    DWORD aProcesses[MAX_PIDS], cbNeeded, cProcesses; 
    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
        return 1;
    } 
    cProcesses = cbNeeded / sizeof(DWORD); 
    for (UINT i = 0; i < cProcesses; i++) {
        if (aProcesses[i] != 0) {
            HMODULE hMod;
            DWORD cbNeeded;
            TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>"); 
            HANDLE hProcess;
            OBJECT_ATTRIBUTES oa;
            InitializeObjectAttributes(&oa, NULL, 0, NULL, NULL);
            CLIENT_ID cid;
            cid.UniqueProcess = (PVOID)aProcesses[i];
            cid.UniqueThread = (PVOID)0;

            if (NT_SUCCESS(PsalmNtOpenProcess(&hProcess, PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, &oa, &cid))) {
                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
                    GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
                    if (!lstrcmpiW(procname, szProcessName)) {
                        CloseHandle(hProcess);
                        return aProcesses[i];
                    }
                }
                CloseHandle(hProcess);
            } 
        }
    }
    return 0;
}

BOOL MapPidsEnumProcesses(DWORD *pids, size_t &pCount) {
    if (pCount == 0)
        return FALSE;
    size_t maxPids = pCount;
    pCount = 0;
    DWORD aProcesses[MAX_PIDS], cbNeeded, cProcesses;
    if (!EnumProcesses(pids, sizeof(aProcesses), &cbNeeded)) {
        return 1;
    }
    pCount = cbNeeded / sizeof(DWORD);
    return 0;
    for (UINT i = 0; i < cProcesses; i++) {
        if (aProcesses[i] != 0) {
            pids[pCount] = aProcesses[i];
            pCount++;
        }
        if (pCount >= maxPids) {
            return 1;
        }
    }
    return 0;

}