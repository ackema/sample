CFLAGS		:= -g -Wall -Werror
INCFLAGS	:= -Isrc/inc
LDFLAGS		:=
LIBS		:= -lpthread
LIBS		+= -lm
LIBS		+= -luci -lubox

CFLAGS		+= -D_VERSION_=\"A1\"
CFLAGS		+= -DPID_FILE=\"/var/run/sample.pid\"
CFLAGS		+= -D_DEBUG_

sampleobjs	:=	$(patsubst %.c,%.o, $(wildcard src/*.c))
sampleobjs	+=	$(patsubst %.c,%.o, $(wildcard src/utils/*.c))
