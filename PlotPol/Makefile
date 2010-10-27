TARGET		=PlotPol

$(TARGET):	PlotPol.o   gl2ps.o  
	g++ -g -o $(TARGET) PlotPol.o  gl2ps.o  \
	 `sdl-config --libs` -lGL -lGLU -lOGLFT -lm

PlotPol.o:   
	g++ -g  -c PlotPol.cpp `sdl-config --cflags` 

gl2ps.o:
	cc -g -c gl2ps.c 

clean:
	rm -f $(TARGET) *.o  core
