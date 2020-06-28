#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uae_pragmas.h"

static const char version[] = "$VER: Host-Run v1.1";

int main(int argc, char *argv[])
{
    char command[255];

    if (argc <= 1)
    {
        printf("Missing argument\n");
        return 0;
    }

    if (!InitUAEResource())
    {
        printf("UAEResource not found!\n");
        return 2;
    }

    for (int i = 1; i < argc; i++)
    {
        strcat(command, argv[i]);

        if (i != argc - 1)
            strcat(command, " ");
        else
            strcat(command, " &\n");
    }

    // printf("DEBUG: %s", command);
    ExecuteOnHost((UBYTE*)&command);
    memset(command, '\0', 255);
}