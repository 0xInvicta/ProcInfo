#ifndef ProcInfo
#define ProcInfo


#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <errno.h>

// Function Declaration for Compiler

/// <summary>
/// This function will create the main process snapshot using tlhelp32.h and display basic information of running processes
/// </summary>
/// <param name=""></param>
/// <returns></returns>
BOOL returnProc(void);

/// <summary>
/// This function will create the main process snapshot using tlhelp32.h and display more detailed information of running processes
/// Note: The output of this can be very big
/// </summary>
/// <param name=""></param>
/// <returns></returns>
BOOL returnProcAdvanced(void);


/// <summary>
/// Displays modules information for a given process
/// </summary>
/// <param name="dwPID"></param>
/// <returns></returns>
BOOL ListProcessModules(DWORD dwPID);


/// <summary>
/// Displays thread information for a given process
/// </summary>
/// <param name="dwOwnerPID"></param>
/// <returns></returns>
BOOL ListProcessThreads(DWORD dwOwnerPID);

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
void saveToFile(void);

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
/// <returns></returns>
BOOL write_returnProcAdvanced(void);

/// <summary>
/// 
/// </summary>
/// <param name="dwOwnerPID"></param>
/// <returns></returns>
BOOL write_ListProcessThreads(DWORD dwOwnerPID);

/// <summary>
/// 
/// </summary>
/// <param name="dwPID"></param>
/// <returns></returns>
BOOL write_ListProcessModules(DWORD dwPID);

/// <summary>
/// This function will display all information for a given process
/// </summary>
/// <param name="dwPID"></param>
/// <returns></returns>
BOOL singleProcData(DWORD dwPID);


#endif