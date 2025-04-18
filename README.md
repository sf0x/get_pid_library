# getpidlib
Proof of concept for techniques to find a PID to a process name in Windows.

# Index 

[[_TOC_]]
# Information

During my research in malware development I was annoyed that every time I wrote an injection the PID of a target process was required and to get that I had to remember how to do that properly with opsec in mind. Therefor this library was created to have a quick-to-use collection of all proper techniques, which can be applied to any project. The collection was made with evasion of enumeration detection on mind, but does currently not implement additional evasion techniques, since it is only meant to be able to make research on which is the proper one to use against a specific target.

The methods will return **the first** occurrence of the searched process. Some of the methods are only able to return PIDs of the same user, whereas some others use Windows APIs that will return the PIDs of processes run by other users too. 

Each technique has two functions, one returns the PID of a process searched by name and one returns a list of all processes running that were found by this technique.

## Why is this no c++ class?

This library is designed to be as modular as possible. I could also have created a class that performs these actions, but the code should be as easy as possible to integrate into other code bases where it has potentially to be modified to prevent signature detection. Libraries that provide their techniques as classes are from my experience only usable as poc.

## Unhooking 

This code is making use of *SysWhispers3* to perform user based EDR unhooking, but additionally followed the modularity idea to be easy integrated into projects. This was just the quick and dirty choice and can be replaced by any other technique - it's not important for this lib.

The syscalls that need to be generated by SysWhisper3 or another unhooking mechanisms of your choice are:

```
NtGetNextProcess,NtQuerySystemInformation,NtAllocateVirtualMemory,NtFreeVirtualMemory,NtOpenProcess,NtOpenProcessToken,NtQueryInformationToken
```

## Modularity

In the `get_pid_lib.h` file you can find two macros, **DEBUG_GET_PID** enables or disables *stdout* responses and **GET_PID_METHOD** specifies the used method to receive a processes PID, the config can be chosen as followed:

```
0: ALL - Debug
1: Brute Force
2: EnumProcesses
3: NtGetNextProcess
4: NtQuerySystemInformation
5: Thelp32
6: WMI
7: WTSEnum
```

If you decide your application needs only one of these methods, you can easily extract the code following the precompiler settings.

# Get PID Techniques

### Brute Force

Iterates through 0x10000 PIDs (can be adjusted in the header file) and uses `OpenProcess()` and `K32GetProcessImageFileNameW()` to read the process name. This is not very stealthy, but also there are no critical monitored syscalls used, which can make it quite useful.

### EnumProcesses

- [x] Is able to retrieve PIDs of all users, but **disabled** in this library

Kind of the official way to enumerate all running processes, suggested to be used by [Microsoft themselves](https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-enumprocesses). The usage of the functions will most likely be monitored by EDRs and alerted by static scans.

### WMI

- [x] Is able to retrieve PIDs of all users, but **disabled** in this library

Uses WMI interface to identify processes PIDs accessible for the current user.

### NtQueryInformation

- [x] Is able to retrieve PIDs of all users

Retrieves a kernel created information struct that contains all required data.

### NtGetNextProcess

Several popular malware and c2 frameworks use this method. It makes a lot of sense to stick to this, since it can easily be unhooked and it searches only processes accessible by the current user, which makes it great for automation.

### CreateToolhelp32Snapshot

- [x] Is able to retrieve PIDs of all users

For some year, this was the standard way to make process enumeration. This call stores a snapshot of all process information in a linked list where you can easily iterate through and search for the desired name. Today it is highly monitored and even static analysis by standard antivirus software is alerting its presence in a PE.

### WTSEnumerateProcesses

- [x] Is able to retrieve PIDs of all users

Makes use of the `WtsApi32` API call to list all processes. Requires `SeTcbPrivilege` to be enabled and direct linking against `wtsapi32.lib`.

### Discarded

List of (currently) discarded techniques:
| Method | Info | Reason |
|--------|------|--------|
|[process-enumeration-stealth](https://github.com/LloydLabs/process-enumeration-stealth) | Creates a NTFS handle to to `\\NTFS\\` and reads the PIDs from the NTFS file infos. | Queries [NtQueryInformationFile](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntqueryinformationfile) for `FileProcessIdsUsingFileInformation` but this is not a valid FILE_INFORMATION_CLASS value (anymore at least). Macro resolves to 0x2f (47) which is not listed in the values. |
| Process Enumeration by Named Pipes |I tried to open all named pipes, retrieve their owners PID and read their name. | Not applicable for all processes, since the opening of pipes mostly failes due to access privileges and there weren't pipes for all processes, which makes this feasible for only retrieving the PID of `LSASS`, see [this link](https://web.archive.org/web/20240623231705/https://www.mdsec.co.uk/2022/08/fourteen-ways-to-read-the-pid-for-the-local-security-authority-subsystem-service-lsass/) for reference. |
| [Windows kernel driver](https://github.com/danielkrupinski/KernelPID) |Driver to read out the PID of a process. | Requires admin privs - if I as an attacker has obtained these, there are hundreds of ways to get the PID more stealthy than with a driver. |

# References

* [Find PID via NtGetNextProcess](https://web.archive.org/web/20240623133838/https://cocomelonc.github.io/malware/2023/05/26/malware-tricks-30.html)
* [Find PID by NtQuerySystemInformation](https://web.archive.org/web/20240623134346/https://medium.com/@s12deff/find-pid-by-ntquerysysteminformation-e21f46bcea3d)
* [NtQuerySystemInformation (MS)](https://learn.microsoft.com/de-de/windows/win32/api/winternl/nf-winternl-ntquerysysteminformation)
* [Find PID by EnumProcesses](https://web.archive.org/web/20240623134538/https://medium.com/@s12deff/find-processes-with-enumprocesses-52ef3c07446a)
* [Enumerating Processes with WTSEnumerateProcesses](https://web.archive.org/web/20240623235702/https://dmfrsecurity.com/2021/04/17/enumerating-processes-with-wtsenumerateprocesses/)
* [Find PID by WTSEnumerateProcesses](https://web.archive.org/web/20240623210831/https://cocomelonc.github.io/malware/2023/07/07/malware-tricks-34.html)
* [Toolhelp32Snapshot](https://learn.microsoft.com/de-de/windows/win32/api/tlhelp32/nf-tlhelp32-createtoolhelp32snapshot)
* [Find PID by Name](https://web.archive.org/web/20240623212544/https://cocomelonc.github.io/pentest/2021/09/29/findmyprocess.html)
* [Fourteen ways to read the PID of LSASS](https://web.archive.org/web/20240623234437/https://www.mdsec.co.uk/2022/08/fourteen-ways-to-read-the-pid-for-the-local-security-authority-subsystem-service-lsass/)
