#include "get_pid_wtsenum.h"

DWORD GetPidWtsEnum(wchar_t* procname) {
	DWORD pid;
	WTS_PROCESS_INFOW* pinfo; 
	DWORD count = 0; 
	if (!WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pinfo, &count))
		return 0;

	for (int i = 0; i < count; i++) {
		if (!lstrcmpiW(procname, pinfo[i].pProcessName)) {
			pid = pinfo[i].ProcessId;
			WTSFreeMemory(pinfo);
			return pid;
		}
	}
	WTSFreeMemory(pinfo);
	return 0;
}

BOOL MapPidsWtsEnum(DWORD* pids, size_t& pCount) {
	if (pCount == 0)
		return FALSE;
	size_t maxPids = pCount;
	pCount = 0;
	WTS_PROCESS_INFOW* pinfo;
	DWORD count = 0;
	if (!WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, 0, 1, &pinfo, &count))
		return 0;
	pCount = static_cast<size_t>(count);
	if (pCount > maxPids)
		return FALSE;
	for (int i = 0; i < pCount; i++) {
		pids[i] = pinfo[i].ProcessId;
	}
	WTSFreeMemory(pinfo);
	return 0;
}