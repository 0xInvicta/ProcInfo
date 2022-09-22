#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE


#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <errno.h>
#include "procInfo.h"



int main() {
    BOOL exitFlag = FALSE;
    int userInt;
    int userPID;
    int menuInstance = 1;
    while (!exitFlag) {
        puts("\n_________________________________________________________________");
        printf("\n[MENU:%d]            ----- OPTIONS ----- \n\n", menuInstance);
        puts("\033[32m[1] - List Running Proccess\033[0m");
        puts("(This option will show the running processes and baisc Information)\n");

        puts("\033[32m[2] - List Running Proccess Advanced \033[31m[TERMINAL] [Not Recommended]\033[0m");
        puts("(This option will show the running processes and more Information)");
        puts("(including thread information and attached .DLLs)");
        puts("(This option will print output to the terminal \033[33m[Large Output]\033[0m)\n");

        puts("\033[32m[3] - List Running Proccess Advanced \033[31m[FILE] [Recommended]\033[0m");
        puts("(This option will show the running processes and more Information)");
        puts("(including thread information and attached .DLLs)");
        puts("(This option will print output to the terminal \033[33m[Large Output]\033[0m)\n");

        puts("\033[32m[4] - Show Live Information For A Process\033[0m");
        puts("(This option will show advanced information for a process based on PID)\n"); 

        puts("\033[31m[5] - EXIT");
        printf("\033[32m> \033[0m");
        scanf_s("%d", &userInt);
        switch (userInt)
        {
        case 1:
            returnProc();
            break;
        case 2:
            returnProcAdvanced();
            break;
        case 3:
            saveToFile();
            break;
        case 4:
            puts("Enter PID: ");
            printf("\033[32m> \033[0m");
            scanf_s("%d", &userPID);
            singleProcData(userPID);
            break;
        case 5:
            exit(0);
            break;
        default:
            puts("\033[31mERORR - INVALID INPUT \n\033[0m ");
            exitFlag = TRUE;
            break;
        }
        userPID = NULL;
        menuInstance++;
    }
    
	return 0;
}
