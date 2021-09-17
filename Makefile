# m68k-amigaos-gcc -Isrc -noixemul -fomit-frame-pointer -Os -std=c99 -o host-run src/host-run.c
all: host-run host-multiview

CC			= m68k-amigaos-gcc
INCLUDES	= -Isrc
CFLAGS		= -mcpu=68020 -noixemul -Os -fomit-frame-pointer -std=c99

host-run: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) src/host-run.c -o $@

host-multiview: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) src/host-multiview.c -o $@

clean:
	rm host-run host-multiview
