#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <windows.h>
#include "procInfo.h"

void title(void);

int main() {
    SYSTEMTIME time;
    BOOL exitFlag = FALSE;
    int userInt;
    int userPID;
    int menuInstance = 1;
    title();
    GetLocalTime(&time);
    puts("\n_________________________________________________________________");
    printf("\n[MENU:%d]             ----- OPTIONS -----                     \033[36m%02d:%02d\033[0m\n\n", menuInstance, time.wHour, time.wMinute);
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
    while (!exitFlag) {
        GetLocalTime(&time);
        puts("\n\n________________________\033[31m ^OUTPUT ABOVE^\033[0m _______________________");
        printf("\n[MENU:%d]             ----- OPTIONS -----                    \033[36m%02d:%02d\033[0m\n\n", menuInstance, time.wHour, time.wMinute);
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

void title(void) {
    printf("\033[33m  _____                _____        __      \r\n |  __ \\              |_   _|      / _|     \r\n | |__) | __ ___   ___  | |  _ __ | |_ ___  \r\n |  ___/ '__/ _ \\ / __| | | | '_ \\|  _/ _ \\ \r\n | |   | | | (_) | (__ _| |_| | | | || (_) |\r\n |_|   |_|  \\___/ \\___|_____|_| |_|_| \\___/\n\033[0m");
    printf(" Author: Mateusz Peplinski");
    
}
