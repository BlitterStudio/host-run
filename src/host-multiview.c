#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uae_pragmas.h"

static const char __ver[40] = "$VER: Host-MultiView v1.0 (2021-09-17)";

int print_usage()
{
    printf("%s\nUsage: host-multiview <filename>\n", __ver);
    return 0;
}

int main(int argc, char *argv[])
{
    BPTR lock;
    char command[100];
    char filename[4095];
    memset(command, '\0', 100);
    memset(filename, '\0', 4095);

    if (!InitUAEResource())
    {
        printf("UAEResource not found!\n");
        return 2;
    }

    if (argc <= 1)
    {
        printf("Missing filename argument\n");
        return print_usage();
    }

    if (strcmp(argv[1], "?") == 0)
    {
        return print_usage();
    }
    else
    {
        strcat(command, "xdg-open");
        strcat(command, " ");
    }

    for (int i = 1; i < argc; i++)
    {
        if (lock = Lock(argv[i], ACCESS_READ))
        {
            NativeDosOp((ULONG)0, (ULONG)lock, (ULONG)filename, (ULONG)100);
            UnLock(lock);
            strcat(command, filename);
            memset(filename, '\0', 4095);
        }
        else 
        {
            strcat(command, argv[i]);
        }

        if (i != argc - 1)
            strcat(command, " ");
    }

#ifdef DEBUG
    printf("DEBUG: argc=%d, command=%s\n", argc, command);
#endif
    ExecuteOnHost((UBYTE *)&command);
    memset(command, '\0', 100);
}