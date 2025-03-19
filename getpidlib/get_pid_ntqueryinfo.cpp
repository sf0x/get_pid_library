#include "get_pid_ntqueryinfo.h"

DWORD GetPidNtQueryInfo(wchar_t* procname) {
	DWORD pid = 0;
	LPVOID data = NULL;
	size_t bufSize = 0;

	PsalmNtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)SystemProcessInformation, 0, 0, (PULONG)&bufSize);
	if (bufSize == 0)
		return 0;

	if(NT_SUCCESS(PsalmNtAllocateVirtualMemory((HANDLE)-1, &data, NULL, &bufSize, MEM_COMMIT, PAGE_READWRITE))){
		SYSTEM_PROCESS_INFORMATION* sysproc_info = (SYSTEM_PROCESS_INFORMATION*)data;
		if (NT_SUCCESS(PsalmNtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)SystemProcessInformation, data, bufSize, (PULONG)&bufSize))) {
			while (TRUE) {
				if (!lstrcmpiW(procname, sysproc_info->ImageName.Buffer)) {
					pid = (DWORD)sysproc_info->UniqueProcessId;
					PsalmNtFreeVirtualMemory((HANDLE)-1, &data, (PSIZE_T)bufSize, MEM_RELEASE);
					return pid;
				}
				if (!sysproc_info->NextEntryOffset) {
					break;
				}
				sysproc_info = (SYSTEM_PROCESS_INFORMATION*)((ULONG_PTR)sysproc_info + sysproc_info->NextEntryOffset);
			}
		}
	}
	PsalmNtFreeVirtualMemory((HANDLE)-1, &data, &bufSize, MEM_RELEASE);
	return pid;
}

BOOL MapPidsNtQuerySystemInfo(DWORD* pids, size_t& pCount) {
	if (pCount == 0)
		return FALSE;
	size_t maxPids = pCount;
	pCount = 0;
	LPVOID data = NULL;
	size_t bufSize = 0;

	PsalmNtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)SystemProcessInformation, 0, 0, (PULONG)&bufSize);
	if (bufSize == 0)
		return 0;

	if (NT_SUCCESS(PsalmNtAllocateVirtualMemory((HANDLE)-1, &data, NULL, &bufSize, MEM_COMMIT, PAGE_READWRITE))) {
		SYSTEM_PROCESS_INFORMATION* sysproc_info = (SYSTEM_PROCESS_INFORMATION*)data;
		if (NT_SUCCESS(PsalmNtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)SystemProcessInformation, data, bufSize, (PULONG)&bufSize))) {
			while (TRUE) {
				pids[pCount] = (size_t)sysproc_info->UniqueProcessId;
				pCount++;
				if (!sysproc_info->NextEntryOffset || pCount >= maxPids) {
					break;
				}
				sysproc_info = (SYSTEM_PROCESS_INFORMATION*)((ULONG_PTR)sysproc_info + sysproc_info->NextEntryOffset);
			}
		}
	}
	PsalmNtFreeVirtualMemory((HANDLE)-1, &data, &bufSize, MEM_RELEASE);
	return TRUE;
}