#include "get_pid_thelp32.h"

DWORD GetPidThelp32(wchar_t* procname) {
	HANDLE hSnapshot;
	PROCESSENTRY32W pe;
	DWORD pid = 0;
	BOOL hResult; 
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
	pe.dwSize = sizeof(PROCESSENTRY32W); 
	hResult = Process32FirstW(hSnapshot, &pe); 
	while (hResult) {
		if (!lstrcmpiW(procname, pe.szExeFile)) {
			pid = pe.th32ProcessID;
			CloseHandle(hSnapshot);
			return pid;
		}
		hResult = Process32NextW(hSnapshot, &pe);
	} 
	CloseHandle(hSnapshot);
	return 0;
}

BOOL MapPidsThelp32(DWORD* pids, size_t& pCount) {
	if (pCount == 0)
		return FALSE;
	size_t maxPids = pCount;
	pCount = 0;
	HANDLE hSnapshot;
	PROCESSENTRY32W pe;
	DWORD pid = 0;
	BOOL hResult; 
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32W); 
	hResult = Process32FirstW(hSnapshot, &pe);
	while (hResult && pCount < maxPids) {
		if (pe.th32ProcessID > 0) {
			pids[pCount] = pe.th32ProcessID;
			pCount++;
		}
		hResult = Process32NextW(hSnapshot, &pe);
	}
	CloseHandle(hSnapshot);
	return TRUE;
}