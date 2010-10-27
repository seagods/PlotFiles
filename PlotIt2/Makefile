TARGET		=PlotIt2

$(TARGET):	PlotIt2.o   gl2ps.o  
	g++ -g -o $(TARGET) PlotIt2.o  gl2ps.o  \
	 `sdl-config --libs` -lGL -lGLU -lOGLFT  -lm

PlotIt2.o:   
	g++ -g  -c PlotIt2.cpp `sdl-config --cflags` 

gl2ps.o:
	cc -g -c gl2ps.c 

clean:
	rm -f $(TARGET) *.o  core
