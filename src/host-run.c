#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uae_pragmas.h"

static const char __ver[40] = "$VER: Host-Run v1.6 (2024-08-23)";

int print_usage()
{
    printf("%s\nUsage: host-run <command> <argument1> <argument2> ...\n", __ver);
    return 0;
}

int main(int argc, char *argv[])
{
    BPTR lock;
    char command[2048];
    char filename[100];
    memset(command, '\0', 2048);
    memset(filename, '\0', 100);

    if (!InitUAEResource())
    {
        printf("UAEResource not found!\n");
        return 2;
    }

    if (argc <= 1)
    {
        printf("Missing argument\n");
        return print_usage();
    }

    if (strcmp(argv[1], "?") == 0)
    {
        return print_usage();
    }
    else
    {
        strncat(command, argv[1], sizeof(command) - strlen(command) - 1);
        strncat(command, " ", sizeof(command) - strlen(command) - 1);
    }

    for (int i = 2; i < argc; i++)
    {
        if (lock = Lock(argv[i], ACCESS_READ))
        {
            NativeDosOp((ULONG)0, (ULONG)lock, (ULONG)filename, (ULONG)100);
            UnLock(lock);
            strncat(command, "\"", sizeof(command) - strlen(command) - 1);
            strncat(command, filename, sizeof(command) - strlen(command) - 1);
            strncat(command, "\"", sizeof(command) - strlen(command) - 1);
            memset(filename, '\0', 100);      
        }
        else 
        {
            strncat(command, "\"", sizeof(command) - strlen(command) - 1);
            strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
            strncat(command, "\"", sizeof(command) - strlen(command) - 1);
        }

        if (i != argc - 1)
            strncat(command, " ", sizeof(command) - strlen(command) - 1);
    }

#ifdef DEBUG
    printf("DEBUG: argc=%d, command=%s\n", argc, command);
#endif
    ExecuteOnHost((UBYTE *)&command);
    memset(command, '\0', 2048);
}