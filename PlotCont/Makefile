TARGET		=PlotCont

$(TARGET):	PlotCont.o   gl2ps.o  
	g++ -g -o $(TARGET) PlotCont.o  gl2ps.o  \
	 `sdl-config --libs` -lGL -lGLU -lOGLFT -lm -lmylib -lgfortran

PlotCont.o:   
	g++ -g  -c PlotCont.cpp `sdl-config --cflags` 

gl2ps.o:
	cc -g -c gl2ps.c 

clean:
	rm -f $(TARGET) *.o  core
