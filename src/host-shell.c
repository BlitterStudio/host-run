#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uae_pragmas.h"

#include <proto/exec.h>
#include <proto/dos.h>

#define OUTBUFSIZE 4095

static const char version[] = "$VER: Host-Shell v1.0";
char outbuf[OUTBUFSIZE + 1];

int main(int argc, char *argv[])
{
    char command[1024] = "";
    char buffer[4096];
    BPTR in, out;
    long handle;
    BOOL brk = FALSE;
    long actual;

    if (!InitUAEResource())
    {
        printf("UAEResource not found!\n");
        return 2;
    }

    // Combine arguments into command string
    for (int i = 1; i < argc; i++)
    {
        if (i > 1) strncat(command, " ", sizeof(command) - strlen(command) - 1);
        strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
    }

    if (DOSBase = (struct DosLibrary *)OpenLibrary("dos.library", 0))
    {
        in = Input();
        out = Output();

        // Enable Raw Mode
        SetMode(in, 1);

        handle = HostShell_Open((UBYTE *)command);
        if (handle == 0) {
            printf("Failed to open host shell session.\n");
            SetMode(in, 0);
            CloseLibrary((struct Library *)DOSBase);
            return 10;
        }

        while (!brk)
        {
            // Check for output from host
            actual = HostShell_Read(handle, (UBYTE *)buffer, sizeof(buffer) - 1);
            if (actual > 0)
            {
                buffer[actual] = 0;
                Write(out, buffer, actual);
            }
            else if (actual < 0) // Error or closed
            {
                break;
            }

            // Check for input from Amiga user
            // Wait up to 20ms (20000 microseconds)
            if (WaitForChar(in, 20000)) 
            {
                actual = Read(in, buffer, sizeof(buffer));
                if (actual > 0)
                {
                    HostShell_Write(handle, (UBYTE *)buffer, actual);
                }
                else if (actual == 0) // EOF
                {
                    // Maybe break? Or just ignore?
                }
            }

            if (SetSignal(0, 0) & SIGBREAKF_CTRL_C)
            {
                brk = TRUE;
            }
        }

        HostShell_Close(handle);
        SetMode(in, 0); // Restore Cooked Mode
        CloseLibrary((struct Library *)DOSBase);
    }
    return 0;
}