CC			= gcc
STRIP		= strip
LINK		= gcc

CFLAGS		+= -DARCH=\"x86\"
CFLAGS		+= -DLOG_FILE_MAX_SIZE=134217728

INCFLAGS	+= -Isrc/arch/x86/inc
LDFLAGS		+= -Lsrc/arch/x86/lib

sampleobjs	+=	$(patsubst %.c,%.o, $(wildcard src/arch/x86/src/*.c))
