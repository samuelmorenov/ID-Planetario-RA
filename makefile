# Ruta absoluta o relativa (cuidado con espacios en blanco al final del path!)
ARTOOLKITDIR = ARToolKit
INC_DIR      = $(ARTOOLKITDIR)/include
LIB_DIR      = $(ARTOOLKITDIR)/lib

LIBS   = -lARgsub -lARvideo -lAR -lglut  -lGL -lGLU 

NAMEEXEC     = Planetario

ejecutar: $(NAMEEXEC)
	chmod 777 $(NAMEEXEC)
	./$(NAMEEXEC)

$(NAMEEXEC): *.cpp 
	g++ -I $(INC_DIR) -o $(NAMEEXEC) *.cpp -L$(LIB_DIR) $(LIBS) 
clean:
	rm -f *.o $(NAMEEXEC) *~ *.*~

