#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <errno.h>


BOOL returnProc(void) {
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        puts("\033[31mERORR - UNABLE TO MAKE PROCESS SNAPSHOT \n\033[0m ");
        return(FALSE);
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Check if able to get first proccess if Error is Spawned exit [return(FALSE)].
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return(FALSE);
    }

    do
    {
        _tprintf(TEXT("\n-------------------- [PID:\033[31m%d\033[0m] --------------------"), pe32.th32ProcessID);
        _tprintf(TEXT("\nProccess Name:  \033[36m%s\033[0m    "), pe32.szExeFile);
        _tprintf(TEXT("\n  Process ID        = \033[32m 0x%08X\033[0m"), pe32.th32ProcessID);
        _tprintf(TEXT("\n  Thread count      = \033[32m %d\033[0m"), pe32.cntThreads);
        _tprintf(TEXT("\n  Parent process ID = \033[32m 0x%08X\033[0m"), pe32.th32ParentProcessID);

    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return(TRUE);
}
BOOL ListProcessModules(DWORD dwPID)
{
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    // Take a snapshot of all modules in the specified process.
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
    {
        puts("\033[31mERORR - UNABLE TO MAKE PROCESS SNAPSHOT \n\033[0m ");
        return(FALSE);
    }

    me32.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(hModuleSnap, &me32))
    {
        puts("\033[31mERORR - UNABLE TO GET MODULE DATA \n\033[0m ");  // show cause of failure
        CloseHandle(hModuleSnap);           // clean the snapshot object
        return(FALSE);
    }

    do
    {
        _tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
        _tprintf(TEXT("\n     Executable     = %s"), me32.szExePath);
        _tprintf(TEXT("\n     Process ID     = 0x%08X"), me32.th32ProcessID);
        _tprintf(TEXT("\n     Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
        _tprintf(TEXT("\n     Ref count (p)  = 0x%04X"), me32.ProccntUsage);
        _tprintf(TEXT("\n     Base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
        _tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize);

    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return(TRUE);
}
BOOL returnProcAdvanced(void) {
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        puts("\033[31mERORR - UNABLE TO MAKE PROCESS SNAPSHOT \n\033[0m ");
        return(FALSE);
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Check if able to get first proccess if Error is Spawned exit [return(FALSE)].
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return(FALSE);
    }

    do
    {
        _tprintf(TEXT("\n-------------------- [PID:\033[31m%d\033[0m] --------------------"), pe32.th32ProcessID);
        _tprintf(TEXT("\nProccess Name:  \033[36m%s\033[0m    "), pe32.szExeFile);
        _tprintf(TEXT("\n  Process ID        = \033[32m 0x%08X\033[0m"), pe32.th32ProcessID);
        _tprintf(TEXT("\n  Thread count      = \033[32m %d\033[0m"), pe32.cntThreads);
        _tprintf(TEXT("\n  Parent process ID = \033[32m 0x%08X\033[0m"), pe32.th32ParentProcessID);


        ListProcessModules(pe32.th32ProcessID);
        ListProcessThreads(pe32.th32ProcessID);
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return(TRUE);
}
BOOL ListProcessThreads(DWORD dwOwnerPID)
{
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;

    // Take a snapshot of all running threads  
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE) {
        return(FALSE);
    }


    te32.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hThreadSnap, &te32))
    {
        puts("\033[31mERORR - UNABLE TO GET THREAD DATA \n\033[0m ");
        CloseHandle(hThreadSnap);
        return(FALSE);
    }


    do
    {
        if (te32.th32OwnerProcessID == dwOwnerPID)
        {
            _tprintf(TEXT("\n\n     THREAD ID      = 0x%08X"), te32.th32ThreadID);
            _tprintf(TEXT("\n     Base priority  = %d"), te32.tpBasePri);
            _tprintf(TEXT("\n     Delta priority = %d"), te32.tpDeltaPri);
            _tprintf(TEXT("\n"));
        }
    } while (Thread32Next(hThreadSnap, &te32));

    CloseHandle(hThreadSnap);
    return(TRUE);
}
void saveToFile(void) {

    write_returnProcAdvanced();

}

// WRITE FUNCTIONS NEED WORK
// FIX NULL ERRORS
// FIX CHANGE _tprintf() TO fputs() OR fprintf() FOR THREAD AND MODULE FUNCTIONS
#define TO_STRING(val) #val
BOOL write_returnProcAdvanced(void) {
    FILE* fPtr;

    fPtr = fopen("fileOut.txt", "w");

    if (fPtr == NULL) {
        puts("\033[31mERORR - UNABLE TO OPEN FILE \n\033[0m ");
        exit(EXIT_FAILURE);
    }
    else
    {
        HANDLE hProcessSnap;
        HANDLE hProcess;
        PROCESSENTRY32 pe32;
        DWORD dwPriorityClass;

        // Take a snapshot of all processes in the system.
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hProcessSnap == INVALID_HANDLE_VALUE)
        {
            puts("\033[31mERORR - UNABLE TO MAKE PROCESS SNAPSHOT \n\033[0m ");
            return(FALSE);
        }
        pe32.dwSize = sizeof(PROCESSENTRY32);

        // Check if able to get first proccess if Error is Spawned exit [return(FALSE)].
        if (!Process32First(hProcessSnap, &pe32))
        {
            CloseHandle(hProcessSnap);
            return(FALSE);
        }

        do
        {
            //WCHAR test = pe32.th32ProcessID;
            //printf("%s \n", TO_STRING(test));
            //wchar_t wstr[256] = (pe32.th32ProcessID);

            fputs("%s", (pe32.th32ProcessID), fPtr);
            //fputs("\n-------------------- [PID:%d] --------------------", pe32.th32ProcessID,fPtr);      
            //fputs("\nProccess Name:  %s   ", pe32.szExeFile, fPtr);
            //fputs(("\n  Process ID        =  0x%08X", pe32.th32ProcessID), fPtr);
            //fputs(("\n  Thread count      =  %d", pe32.cntThreads),fPtr);
            //fputs(("\n  Parent process ID =  0x%08X", pe32.th32ParentProcessID), fPtr);


            ListProcessModules(pe32.th32ProcessID);
            ListProcessThreads(pe32.th32ProcessID);
        } while (Process32Next(hProcessSnap, &pe32));
        fclose(fPtr);
        CloseHandle(hProcessSnap);
        return(TRUE);

    }
}
BOOL write_ListProcessThreads(DWORD dwOwnerPID) {
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;

    // Take a snapshot of all running threads  
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE) {
        return(FALSE);
    }


    te32.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hThreadSnap, &te32))
    {
        puts("\033[31mERORR - UNABLE TO GET THREAD DATA \n\033[0m ");
        CloseHandle(hThreadSnap);
        return(FALSE);
    }


    do
    {
        if (te32.th32OwnerProcessID == dwOwnerPID)
        {
            _tprintf(TEXT("\n\n     THREAD ID      = 0x%08X"), te32.th32ThreadID);
            _tprintf(TEXT("\n     Base priority  = %d"), te32.tpBasePri);
            _tprintf(TEXT("\n     Delta priority = %d"), te32.tpDeltaPri);
            _tprintf(TEXT("\n"));
        }
    } while (Thread32Next(hThreadSnap, &te32));

    CloseHandle(hThreadSnap);
    return(TRUE);
}
BOOL write_ListProcessModules(DWORD dwPID) {
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    // Take a snapshot of all modules in the specified process.
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
    {
        puts("\033[31mERORR - UNABLE TO MAKE PROCESS SNAPSHOT \n\033[0m ");
        return(FALSE);
    }

    me32.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(hModuleSnap, &me32))
    {
        puts("\033[31mERORR - UNABLE TO GET MODULE DATA \n\033[0m ");  // show cause of failure
        CloseHandle(hModuleSnap);           // clean the snapshot object
        return(FALSE);
    }

    do
    {
        _tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
        _tprintf(TEXT("\n     Executable     = %s"), me32.szExePath);
        _tprintf(TEXT("\n     Process ID     = 0x%08X"), me32.th32ProcessID);
        _tprintf(TEXT("\n     Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
        _tprintf(TEXT("\n     Ref count (p)  = 0x%04X"), me32.ProccntUsage);
        _tprintf(TEXT("\n     Base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
        _tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize);

    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return(TRUE);
}
BOOL singleProcData(DWORD dwPID) {

    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        puts("\033[31mERORR - UNABLE TO MAKE PROCESS SNAPSHOT \n\033[0m ");
        return(FALSE);
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Check if able to get first proccess if Error is Spawned exit [return(FALSE)].
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return(FALSE);
    }

    do
    {
        if (dwPID == pe32.th32ProcessID) {
            _tprintf(TEXT("\n-------------------- [PID:\033[31m%d\033[0m] --------------------"), pe32.th32ProcessID);
            _tprintf(TEXT("\nProccess Name:  \033[36m%s\033[0m    "), pe32.szExeFile);
            _tprintf(TEXT("\n  Process ID        = \033[32m 0x%08X\033[0m"), pe32.th32ProcessID);
            _tprintf(TEXT("\n  Thread count      = \033[32m %d\033[0m"), pe32.cntThreads);
            _tprintf(TEXT("\n  Parent process ID = \033[32m 0x%08X\033[0m"), pe32.th32ParentProcessID);
            
        }
        

    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    // Take a snapshot of all modules in the specified process.
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
    {
        puts("\033[31mERORR - UNABLE TO MAKE PROCESS SNAPSHOT \n\033[0m ");
        return(FALSE);
    }

    me32.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(hModuleSnap, &me32))
    {
        puts("\033[31mERORR - UNABLE TO GET MODULE DATA \n\033[0m ");  // show cause of failure
        CloseHandle(hModuleSnap);           // clean the snapshot object
        return(FALSE);
    }

    do
    {
        _tprintf(TEXT("\n\n     MODULE NAME:     \033[36m%s\033[0m"), me32.szModule);
        _tprintf(TEXT("\n     Executable     = \033[32m%s\033[0m"), me32.szExePath);
        _tprintf(TEXT("\n     Process ID     =\033[32m 0x%08X\033[0m"), me32.th32ProcessID);
        _tprintf(TEXT("\n     Ref count (g)  =\033[32m 0x%04X\033[0m"), me32.GlblcntUsage);
        _tprintf(TEXT("\n     Ref count (p)  =\033[32m 0x%04X\033[0m"), me32.ProccntUsage);
        _tprintf(TEXT("\n     Base address   =\033[32m 0x%08X\033[0m"), (DWORD)me32.modBaseAddr);
        _tprintf(TEXT("\n     Base size      = \033[32m%d\033[0m"), me32.modBaseSize);
        

    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return(TRUE);
}