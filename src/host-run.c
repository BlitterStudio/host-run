#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uae_pragmas.h"

static const char __ver[40] = "$VER: Host-Run v1.4 (2021-02-01)";

int print_usage()
{
    printf("%s\nUsage: host-run <command> <argument1> <argument2> ...\n", __ver);
    return 0;
}

int main(int argc, char *argv[])
{
    char command[255];
    memset(command, '\0', 255);

    if (argc <= 1)
    {
        printf("Missing argument\n");
        return print_usage();
    }

    if (!InitUAEResource())
    {
        printf("UAEResource not found!\n");
        return 2;
    }

    if (strcmp(argv[1], "?") == 0)
    {
        return print_usage();
    }

    for (int i = 1; i < argc; i++)
    {
#ifdef DEBUG
        printf("DEBUG: argv[%d]=%s\n", i, argv[i]);
#endif
        strcat(command, argv[i]);

        if (i != argc - 1)
            strcat(command, " ");
    }

#ifdef DEBUG
    printf("DEBUG: argc=%d, command=%s\n", argc, command);
#endif
    ExecuteOnHost((UBYTE *)&command);
    memset(command, '\0', 255);
}