TARGET		=PlotIt

$(TARGET):	PlotIt.o   gl2ps.o  
	g++ -g -o $(TARGET) PlotIt.o  gl2ps.o  \
	 `sdl-config --libs` -lGL -lGLU -lOGLFT -lm -lmylib -lgfortran

PlotIt.o:   
	g++ -g  -c PlotIt.cpp `sdl-config --cflags` 

gl2ps.o:
	cc -g -c gl2ps.c 

clean:
	rm -f $(TARGET) *.o  core
