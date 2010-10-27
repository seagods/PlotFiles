TARGET		=PlotSurf

$(TARGET):	PlotSurf.o   gl2ps.o  
	g++ -g -o $(TARGET) PlotSurf.o  gl2ps.o  \
	 `sdl-config --libs` -lGL -lGLU -lOGLFT  -lm

PlotSurf.o:   
	g++ -g  -c PlotSurf.cpp `sdl-config --cflags` 

gl2ps.o:
	cc -g -c gl2ps.c 

clean:
	rm -f $(TARGET) *.o  core
