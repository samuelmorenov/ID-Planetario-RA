INC_DIR= ../../include
LIB_DIR= ../../lib
BIN_DIR= ../../bin

LDFLAG=-L/usr/X11R6/lib -L$(LIB_DIR)
LIBS= -lARgsub_lite -lARvideo -lAR -lglut -lGLU -lGL -lXi -lXmu -lX11 -lm -ljpeg
CFLAG= -O -I/usr/X11R6/include -DUSE_EYETOY -I/usr/src/linux/include -I$(INC_DIR)


all: $(BIN_DIR)/calib_cparam

$(BIN_DIR)/calib_cparam: calib_cparam.o calib_cparam_sub.o
	cc -o $(BIN_DIR)/calib_cparam calib_cparam.o calib_cparam_sub.o\
	   $(LDFLAG) $(LIBS)

calib_cparam.o: calib_cparam.c calib_cparam.h
	cc -c $(CFLAG) calib_cparam.c

calib_cparam_sub.o: calib_cparam_sub.c calib_cparam.h
	cc -c $(CFLAG) calib_cparam_sub.c

clean:
	rm -f calib_cparam.o calib_cparam_sub.o
	rm -f $(BIN_DIR)/calib_cparam

allclean:
	rm -f calib_cparam.o calib_cparam_sub.o
	rm -f $(BIN_DIR)/calib_cparam
	rm -f Makefile
