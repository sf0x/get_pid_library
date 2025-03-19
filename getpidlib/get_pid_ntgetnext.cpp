#include "get_pid_ntgetnext.h"

DWORD GetPidNtGetNextProc(wchar_t* procname) {
	DWORD pid = 0;
	HANDLE hCurrent = NULL;
	wchar_t curProcName[MAX_PATH];

	while (!NTSTATUS(PsalmNtGetNextProcess(hCurrent, PROCESS_QUERY_LIMITED_INFORMATION, 0, 0, &hCurrent))) {
		GetProcessImageFileNameW(hCurrent, curProcName, MAX_PATH);
		if (!lstrcmpiW(procname, PathFindFileNameW(curProcName))) {
			pid = GetProcessId(hCurrent);
			CloseHandle(hCurrent);
			return pid;
		}
	}
	CloseHandle(hCurrent);
	return 0;
}

/*
* initialize pCount with maximum number of threads (size of *pids array)
* Check out MAX_PIDS macro
*/
BOOL MapPidsNtGetNextProc(DWORD *pids, size_t &pCount) { 
	if (pCount == 0)
		return FALSE;
	HANDLE hCurrent = NULL;
	DWORD maxPids = (DWORD)pCount;
	pCount = 0;
	while (!PsalmNtGetNextProcess(hCurrent, PROCESS_QUERY_LIMITED_INFORMATION, 0, 0, &hCurrent) && pCount < maxPids) {
		DWORD curPid = 0;
		if ((curPid = GetProcessId(hCurrent)) > 0) {
			pids[pCount] = curPid;
			pCount++;
		}
	}
	CloseHandle(hCurrent);
	return TRUE;
}