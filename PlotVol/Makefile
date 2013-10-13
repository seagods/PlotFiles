TARGET1		=basicCube
TARGET2		=PlotVol

$(TARGET1):	basicCube.o   gl2ps.o  
	g++ -g -o $(TARGET1) basicCube.o  gl2ps.o  \
	 `sdl-config --libs` -lGL -lGLU -lOGLFT  -lm -lmylib -lgfortran

$(TARGET2):	PlotVol.o   gl2ps.o  
	g++ -g -o $(TARGET2) PlotVol.o  gl2ps.o  \
	 `sdl-config --libs` -lGL -lGLU -lOGLFT -lm -lmylib -lgfortran

basicCube.o:   
	g++ -g  -c basicCube.cpp `sdl-config --cflags`

PlotVol.o:   
	g++ -g  -c PlotVol.cpp `sdl-config --cflags`

gl2ps.o:
	cc -g -c gl2ps.c 

clean:
	rm -f $(TARGET1) *.o  core
