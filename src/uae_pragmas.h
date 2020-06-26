#include <proto/exec.h>
#include <proto/dos.h>

struct uaebase
{
	struct Library uae_lib;
	UWORD uae_version;
	UWORD uae_revision;
	UWORD uae_subrevision;
	UWORD zero;
	APTR uae_rombase;
};

static struct uaebase *UAEResource;

static int (*calltrap)(int arg0, ...) = (int (*)(int arg0, ...))0xF0FF60;

static int InitUAEResource(void)
{
	UAEResource = (struct uaebase *)OpenResource("uae.resource");
	if (UAEResource)
	{
		calltrap = (int (*)(int arg0, ...))((BYTE *)UAEResource->uae_rombase + 0xFF60);
		return 1;
	}
	return 0;
}

static int GetVersion(void)
{
    return calltrap (0);
}
static int GetUaeConfig(struct UAE_CONFIG *a)
{
    return calltrap (1, a);
}
static int SetUaeConfig(struct UAE_CONFIG *a)
{
    return calltrap (2, a);
}
static int HardReset(void)
{
    return calltrap (3);
}
static int Reset(void)
{
    return calltrap (4);
}
static int EjectDisk(ULONG drive)
{
    return calltrap (5, "", drive);
}
static int InsertDisk(UBYTE *name, ULONG drive)
{
    return calltrap (5, name, drive);
}
static int EnableSound(void)
{
    return calltrap (6, 2);
}
static int DisableSound(void)
{
    return calltrap (6, 1);
}
static int EnableJoystick(void)
{
    return calltrap (7, 1);
}
static int DisableJoystick(void)
{
    return calltrap (7, 0);
}
static int SetFrameRate(ULONG rate)
{
    return calltrap (8, rate);
}
static int ChgCMemSize(ULONG mem)
{
    return calltrap (9, mem);
}
static int ChgSMemSize(ULONG mem)
{
    return calltrap (10, mem);
}
static int ChgFMemSize(ULONG mem)
{
    return calltrap (11, mem);
}
static int ChangeLanguage(ULONG lang)
{
    return calltrap (12, lang);
}
static int ExitEmu(void)
{
    return calltrap (13);
}
static int GetDisk(ULONG drive, UBYTE *name)
{
    return calltrap (14, drive, name);
}
static int DebugFunc(void)
{
    return calltrap (15);
}
static int ExecuteOnHost(UBYTE *name)
{
    return calltrap (88, name);
}