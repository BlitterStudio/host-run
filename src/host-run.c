#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uae_pragmas.h"

static const char __ver[40] = "$VER: Host-Run v1.7 (2024-08-24)";

int print_usage()
{
    printf("Host-Run v1.7\n");
    printf("Host-Run is a command line tool to run host commands from within UAE.\n");
    printf("%s\nUsage: host-run <command> <argument1> <argument2> ...\n", __ver);
    return 0;
}

int main(int argc, char *argv[])
{
    BPTR lock;
    char command[4096];
    char filename[256];
    char escaped_filename[512];
    memset(command, '\0', 4096);
    memset(filename, '\0', 256);
    memset(escaped_filename, '\0', 512);

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
            NativeDosOp((ULONG)0, (ULONG)lock, (ULONG)filename, (ULONG)256);
            UnLock(lock);

            // Escape spaces in filename
            int j = 0;
            for (int k = 0; k < strlen(filename); k++)
            {
                if (filename[k] == ' ')
                {
                    escaped_filename[j++] = '\\';
                }
                escaped_filename[j++] = filename[k];
            }
            escaped_filename[j] = '\0';

            strncat(command, escaped_filename, sizeof(command) - strlen(command) - 1);
            memset(filename, '\0', 256);
            memset(escaped_filename, '\0', 512);
        }
        else 
        {
            strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
        }

        if (i != argc - 1)
            strncat(command, " ", sizeof(command) - strlen(command) - 1);
    }

#ifdef DEBUG
    printf("DEBUG: argc=%d, command=%s\n", argc, command);
#endif
    ExecuteOnHost((UBYTE *)&command);
    memset(command, '\0', 4096);
}