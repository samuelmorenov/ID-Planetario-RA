#
# For instalation. Change this to your settings.
#
INC_DIR = ../../../include
LIB_DIR = ../..
#
#  compiler
#
# Note we hard code in -O3 here because the Bayer decoder needs to be highly
# optimised otherwise it runs so slow you can't use it!
CC= cc
CFLAG= -O -I/usr/X11R6/include -DUSE_EYETOY -I/usr/src/linux/include -I$(INC_DIR) -O3
#
# For making the library
#
AR= ar
ARFLAGS= rs
#
#   products
#
LIB= ${LIB_DIR}/libARvideo.a
INCLUDE=  ${INC_DIR}/AR/config.h \
          ${INC_DIR}/AR/video.h
#
#   compilation control
#
LIBOBJS= ${LIB}(video.o conversions.o)

all:		${LIBOBJS}

${LIBOBJS}:	${INCLUDE}

.c.a:
	${CC} -c ${CFLAG} $<
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

clean:
	rm -f *.o
	rm -f ${LIB}

allclean:
	rm -f *.o
	rm -f ${LIB}
	rm -f Makefile
