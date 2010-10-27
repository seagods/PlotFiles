TARGET		=PlotWorld

$(TARGET):	PlotWorld.o   gl2ps.o  
	g++ -g -o $(TARGET) PlotWorld.o  gl2ps.o  \
	 `sdl-config --libs` -lGL -lGLU -lOGLFT  -lm

PlotWorld.o:   
	g++ -g  -c PlotWorld.cpp `sdl-config --cflags` 

gl2ps.o:
	cc -g -c gl2ps.c 

clean:
	rm -f $(TARGET) *.o  core
