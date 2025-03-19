#include "get_pid_lib.h"
/*
* procname: name of process to search
* pid: return pid, if not found 0
*/
BOOL GetPid(wchar_t* procname, DWORD& pid) {
    pid = 0;
#if GET_PID_METHOD == 0
    pid = GetPidEnumCall(procname);
    std::cout << "getPidEnumCall: " << pid << std::endl;

    pid = GetPidWmi(procname);
    std::cout << "getPidWmi: " << pid << std::endl;

    pid = GetPidBruteForce(procname);
    std::cout << "getPidBruteForce: " << pid << std::endl;

    pid = GetPidNtQueryInfo(procname);
    std::cout << "getPidNtQueryInfo: " << pid << std::endl;

    pid = GetPidNtGetNextProc(procname);
    std::cout << "getPidNGetNextProc: " << pid << std::endl;

    pid = GetPidWtsEnum(procname);
    std::cout << "getPidWtsEnum: " << pid << std::endl;

    pid = GetPidThelp32(procname);
    std::cout << "getPidThelp32: " << pid << std::endl;
#endif
#if GET_PID_METHOD == 1 // Brute Force
    pid = GetPidBruteForce(procname);
#endif

#if GET_PID_METHOD == 2 // EnumProcesses
    pid = GetPidEnumCall(procname);
#endif

#if GET_PID_METHOD == 3 // NtGetNextProcess
    pid = GetPidNtGetNextProc(procname); 
#endif

#if GET_PID_METHOD == 4 // NtQuerySystemInformation
    pid = GetPidNtQueryInfo(procname); 
#endif

#if GET_PID_METHOD == 5 // Thelp32
    pid = GetPidThelp32(procname);
#endif

#if GET_PID_METHOD == 6 // WMI
    pid = GetPidWmi(procname);
#endif

#if GET_PID_METHOD == 7 // WTSEnum
    pid = GetPidWtsEnum(procname);
#endif
	return TRUE;
}

/*
* processIds: list of PIDs
* pidsCount: number of processes found
* maxPids: list size, maximum number of PIDs to search
*/
BOOL MapProcPids(DWORD *pids, size_t &pCount) {
    size_t maxPids = pCount;
#if GET_PID_METHOD == 0
    MapPidsNtGetNextProc(pids, pCount);
    PrintPids("NtGetNext", pids, pCount);
    ResetPids(pids, pCount, maxPids);

    MapPidsWMI(pids, pCount);
    PrintPids("WMI", pids, pCount);
    ResetPids(pids, pCount, maxPids);

    MapPidsEnumProcesses(pids, pCount);
    PrintPids("EnumProcesses", pids, pCount);
    ResetPids(pids, pCount, maxPids);

    MapPidsThelp32(pids, pCount);
    PrintPids("Thelp32", pids, pCount);
    ResetPids(pids, pCount, maxPids);

    MapPidsWtsEnum(pids, pCount);
    PrintPids("WtsEnum", pids, pCount);
    ResetPids(pids, pCount, maxPids);

    MapPidsNtQuerySystemInfo(pids, pCount);
    PrintPids("NtQuerySystemInfo", pids, pCount);
    ResetPids(pids, pCount, maxPids);

    MapPidsBruteForce(pids, pCount);
    MapPidsNtQuerySystemInfo(pids, pCount);
    PrintPids("BruteForce", pids, pCount);
#endif

#if GET_PID_METHOD == 1 // BruteForce
    MapPidsBruteForce(pids, pCount);
#endif

#if GET_PID_METHOD == 2 // EnumProcesses
    MapPidsEnumProcesses(pids, pCount);
#endif

#if GET_PID_METHOD == 3 // NtGetNextProcess
    MapPidsNtGetNextProc(pids, pCount);
#endif

#if GET_PID_METHOD == 4 // NtQuerySystemInfo
    PrintPids("NtQuerySystemInfo", pids, pCount);
#endif

#if GET_PID_METHOD == 5 // Thelp32
    MapPidsThelp32(pids, pCount);
#endif

#if GET_PID_METHOD == 6 // WMI
    MapPidsWMI(pids, pCount);
#endif

#if GET_PID_METHOD == 7 // WtsEnum
    MapPidsWtsEnum(pids, pCount);
#endif
	return TRUE;
}

/*
* processIds: list of PIDs
* pid: return value of random pid
*/
BOOL GetRandomPidPull(DWORD *processIds, size_t &pidCount, DWORD &pid) {
	unsigned int choice = RandByte() % pidCount;

	// make choice the last item
	pid = processIds[choice];
    processIds[choice] = processIds[pidCount]; // save last item
    processIds[pidCount] = 0;
	pidCount--;
    return TRUE;
}