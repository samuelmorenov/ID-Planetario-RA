INC_DIR= ../../include
LIB_DIR= ../../lib
BIN_DIR= ../../bin

LDFLAG=-L/usr/X11R6/lib -L$(LIB_DIR)
LIBS= -lARgsub_lite -lARvideo -lAR -lglut -lGLU -lGL -lXi -lXmu -lX11 -lm -ljpeg
CFLAG= -O -I/usr/X11R6/include -DUSE_EYETOY -I/usr/src/linux/include -I$(INC_DIR)


all: $(BIN_DIR)/calib_camera2

$(BIN_DIR)/calib_camera2: main.o calib_dist.o calib_inp.o
	cc -o $(BIN_DIR)/calib_camera2 main.o calib_dist.o calib_inp.o\
	   $(LDFLAG) $(LIBS)

main.o: main.c calib_camera.h
	cc -c $(CFLAG) main.c

calib_dist.o: calib_dist.c calib_camera.h
	cc -c $(CFLAG) calib_dist.c

calib_inp.o: calib_inp.c calib_camera.h
	cc -c $(CFLAG) calib_inp.c

clean:
	rm -f main.o calib_dist.o calib_inp.o
	rm -f $(BIN_DIR)/calib_camera2

allclean:
	rm -f main.o calib_dist.o calib_inp.o
	rm -f $(BIN_DIR)/calib_camera2
	rm -f Makefile
