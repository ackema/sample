include mks/macro.mk
include mks/board.mk

sampledeps=$(sampleobjs:.o=.d)

.PHONY: all clean

all: sample

-include $(sampledeps)

sample: $(sampleobjs)
	@echo -n "\tLink "$@"...." 
	@$(LINK) $(LDFLAGS) -o $@ $^ $(LIBS)
	@echo -n "\n"

.c.o:
	@echo -n "\tCompile" $<"...." 
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@ -MMD -MF $*.d -MP
	@echo -n "\n"

strip:
	@$(STRIP) sample

clean:
	@echo -n "\tClean..."
	@/bin/rm -f $(sampleobjs) $(sampledeps) sample
	@echo -n "...Done!\n"

c:clean

# 交叉编译调试比较有用的一个小技巧
ins: sample
	@sshpass -p "admin" scp sample 192.168.1.1:/sample/cgi-bin/sample

