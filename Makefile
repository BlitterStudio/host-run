# m68k-amigaos-gcc -Isrc -noixemul -fomit-frame-pointer -Os -std=c99 -o host-run src/host-run.c
all: host-run

CC			= m68k-amigaos-gcc
INCLUDES	= -Isrc
CFLAGS		= -mcpu=68020 -noixemul -Os -fomit-frame-pointer -std=c99
SOURCE		= src/host-run.c

host-run: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCE) -o $@

clean:
	rm host-run
