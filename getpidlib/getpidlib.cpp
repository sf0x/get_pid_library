#include <iostream>
#include "get_pid_lib.h"


int main()
{
    wchar_t searchProcess[] = L"sihost.exe";
    DWORD pid; 
    GetPid(searchProcess, pid);

    std::cout << "Returned PID: " << pid << std::endl;

    DWORD pids[MAX_PIDS];
    size_t pCount = MAX_PIDS;
    MapProcPids(pids, pCount);

    std::cout << "Returned PID-List Count: " << pCount << std::endl;
    return 0;
}
