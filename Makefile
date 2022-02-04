#LibSDL 1.2.9
#DS porting by Troy Davis(GPF)


ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif


SRCS = \
	src/audio/nds/SDL_ndsaudio.c \
	src/audio/SDL_audio.c \
	src/audio/SDL_audiocvt.c \
	src/audio/SDL_audiodev.c \
	src/audio/SDL_audiomem.c \
	src/audio/SDL_mixer.c \
	src/audio/SDL_wave.c \
	src/audio/nds/sound9.c \
	src/cdrom/nds/SDL_syscdrom.c \
	src/cdrom/SDL_cdrom.c \
	src/endian/SDL_endian.c \
	src/events/SDL_active.c \
	src/events/SDL_events.c \
	src/events/SDL_expose.c \
	src/events/SDL_keyboard.c \
	src/events/SDL_mouse.c \
	src/events/SDL_quit.c \
	src/events/SDL_resize.c \
	src/file/SDL_rwops.c \
	src/joystick/nds/SDL_sysjoystick.c \
	src/joystick/SDL_joystick.c \
	src/SDL.c \
	src/SDL_error.c \
	src/SDL_fatal.c \
	src/SDL_getenv.c \
	src/SDL_loadso.c \
	src/thread/nds/SDL_syscond.c \
	src/thread/nds/SDL_sysmutex.c \
	src/thread/nds/SDL_syssem.c \
	src/thread/nds/SDL_systhread.c \
	src/thread/SDL_thread.c \
	src/timer/nds/SDL_systimer.c \
	src/timer/SDL_timer.c \
	src/video/nds/SDL_ndsevents.c \
	src/video/nds/SDL_ndsvideo.c \
	src/video/SDL_blit.c \
	src/video/SDL_blit_0.c \
	src/video/SDL_blit_1.c \
	src/video/SDL_blit_A.c \
	src/video/SDL_blit_N.c \
	src/video/SDL_bmp.c \
	src/video/SDL_cursor.c \
	src/video/SDL_gamma.c \
	src/video/SDL_pixels.c \
	src/video/SDL_RLEaccel.c \
	src/video/SDL_stretch.c \
	src/video/SDL_surface.c \
	src/video/SDL_video.c \
	src/video/SDL_yuv.c \
	src/video/SDL_yuv_sw.c \
	src/cpuinfo/SDL_cpuinfo.c

OBJS = $(SRCS:.c=.o) 
	

SUBDIRS=

CC=arm-eabi-gcc
CXX=arm-eabi-g++ 
LDSHARED=$(CXX)
AR=arm-eabi-ar rc
RANLIB=arm-eabi-ranlib 

CFLAGS	=	-mthumb -mthumb-interwork \
		-march=armv5te -mtune=arm946e-s \
		-O2 -Wall -Wwrite-strings -Wpointer-arith -Wconversion \
		-DARM9 -D__NDS__ -I$(DEVKITPRO)/libnds/include -DENABLE_NDS -DNO_SIGNAL_H -DDISABLE_THREADS -DPACKAGE=\"SDL\" -DVERSION=\"1.2.9\" -DHAVE_ALLOCA_H=1 -DHAVE_ALLOCA=1 \
		-Iinclude -Isrc -Isrc/audio -Isrc/cdrom -Isrc/endian -Isrc/events -Isrc/joystick -Isrc/thread/nds -Isrc/thread -Isrc/timer -Isrc/video


CXXFLAGS +=$(CFLAGS)

all: $(DEVKITPRO)/libnds/lib/libSDL.a       


$(DEVKITPRO)/libnds/lib/libSDL.a:		$(OBJS)
	$(AR) $@ $(OBJS)
	-@ ($(RANLIB) $@ || true) >/dev/null 2>&1 	

clean: 
	find . -name "*.o" |xargs rm -f
	find . -name "*.d" |xargs rm -f
	-rm -f *.elf
	-rm -f *.nds
	-rm -f *.gba
	-rm -f *.arm9
	-rm -f *.map
	-rm -f *.img
	-rm -Rf *.d


subdirs: $(patsubst %, _dir_%, $(SUBDIRS))

$(patsubst %, _dir_%, $(SUBDIRS)):
	$(MAKE) -C $(patsubst _dir_%, %, $@)

clean_subdirs: $(patsubst %, _clean_dir_%, $(SUBDIRS))

$(patsubst %, _clean_dir_%, $(SUBDIRS)):
	$(MAKE) -C $(patsubst _clean_dir_%, %, $@) clean

#include $(DEVKITARM)/ds_rules

