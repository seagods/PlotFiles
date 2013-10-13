TARGET		=PlotGlobe

$(TARGET):	PlotGlobe.o   gl2ps.o  
	g++ -g -o $(TARGET) PlotGlobe.o  gl2ps.o  \
	 `sdl-config --libs` -lGL -lGLU -lOGLFT  -lm -lmylib -lgfortran

PlotGlobe.o:   
	g++ -g  -c PlotGlobe.cpp `sdl-config --cflags` 

gl2ps.o:
	cc -g -c gl2ps.c 

clean:
	rm -f $(TARGET) *.o  core
