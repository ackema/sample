#export STAGING_DIR=/home/sdks/ramips/staging_dir 
CC			= /home/sdks/ramips/staging_dir/toolchain-mipsel_24kc_gcc-5.4.0_musl-1.1.16/bin/mipsel-openwrt-linux-gcc
STRIP		= /home/sdks/ramips/staging_dir/toolchain-mipsel_24kc_gcc-5.4.0_musl-1.1.16/bin/mipsel-openwrt-linux-strip
LINK		= /home/sdks/ramips/staging_dir/toolchain-mipsel_24kc_gcc-5.4.0_musl-1.1.16/bin/mipsel-openwrt-linux-gcc


CFLAGS		+= -DARCH=\"ramips\"
INCFLAGS	+= -Isrc/arch/ramips/inc
LDFLAGS		+= -Lsrc/arch/ramips/lib

sampleobjs	+=	$(patsubst %.c,%.o, $(wildcard src/arch/ramips/src/*.c))
