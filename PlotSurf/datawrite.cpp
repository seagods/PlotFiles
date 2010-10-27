#include  <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

int main(){

	ofstream  file_out;

	file_out.open("data.dat", ios::out);

	/*
	 * The Plot routine knows nothing!
	 * you might want to have a cloud of points in 3D
	 * with complely random positions. (ntype=1)
	 * or plot a smooth surface (ntype=0)
	 *
	 * For ntype=0, the plot routine needs a triangulation,
	 * It doesn't know if you have a regular grid
	 * It needs the number of points, the number of triangles
	 * and the vertex numbers in each triangle.
	 * If you have a regular grid, this is easy to do.
	 *
	 * If you have data at irregular xy points but don't
	 * have a triangular structure to go with it, you can
	 * use a Delaunay triangulation routine to give you 
	 * the triangulation. Plotsurf doesn't do the triangulation
	 * for you.
	 * There are Delaunay triangulation routines available
	 * in the TOMS library. Also, there are Delaunay 
	 * routines in Barry Joe's GeomPack. */ 

	//NB: The triangles all have to be counter clocwise viewed 
	//from above
	//
	//It isn't efficient on space, but for mutiple surfaces, each
	// one could be on a different set of points and a
	// different triangulation. If they are on the same set of
	// points, the truiangulation data is at present still
	// must be written out with each surface
	//
	// If you only want to plot points, Plotit2 will do fine
	// however, we might have a cloud of points and a surface
	//
	// Finally, the surfaces are not necessarily single valued
	// because the same x,y an be repeated with a different z and
	// triangle node number.

	int nplots=2;
	file_out << nplots << endl;

	int ndata, ntri, ntype, ncol, npoint;

	npoint=1;

	int irefine=2;
	double ref=(double)irefine;

	int nx, ny;
	nx=30;  ny=30;
	double x,y,z;
	double deltax=0.1, deltay=0.1;
        deltax=deltax/ref;  deltay=deltay/ref;

	nx=nx*irefine; ny=ny*irefine;
	ndata=nx*ny;
	ntri=(nx-1)*(ny-1)*2;

	ntype=0;  //surface not points
	if(ntype !=0)ntri=0;  //no triangulation
	ncol=2;    //preset colour

	if(ntype==0){
	file_out << ndata << "  " << ntri << "  "  << ntype << "  " << ncol << endl;}
	if(ntype==1){
	file_out << ndata << "  " << npoint << "  "  << ntype << "  " << ncol << endl;}


	if(ntri!=0){
	   for(int j=0; j<ny-1; j++){
             for(int i=0; i<nx-1; i++){
		 // output rectangle to standard out to check
		 /*
		     cout << j*nx+i <<  "  " << j*nx+i+1 << "  "
		 	     << (j+1)*nx+i << "  " <<  (j+1)*nx+i+1<< endl;
			     */
		     file_out << j*nx+i <<  "  " << j*nx+i+1 << "  "
		 	     << (j+1)*nx+i  <<  endl;
		     file_out << j*nx+i+1 <<  "  " << (j+1)*nx+i+1 << "  "
		 	     <<   (j+1)*nx+i << endl;
		 
	     }}
	}

	for(int j=0; j< ny; j++){
	  for(int i=0; i<nx; i++){
	  x=deltax*i; y=deltay*j;
	 // z=5.0*cos( ((x-2.0)*(x-2.0)+(y-2.0)*(y-2.0)) );
	  z=5.0*exp(-(x-1.0)*(x-1.0)-(y-1.0)*(y-1.0));
	  file_out << x << "  " << y << "  " << z << endl;
	}}



	nx=30;  ny=30;

	nx=nx*irefine; ny=ny*irefine;

	ndata=nx*ny;

	ntri=(nx-1)*(ny-1)*2;

	ntype=0;  //surface not points
	if(ntype !=0)ntri=0;  //no triangulation
	ncol=4; //preset colour 4

	file_out << ndata << "  " << ntri << "  "  << ntype << "  " << ncol << endl;

	if(ntri!=0){
	   for(int j=0; j<ny-1; j++){
             for(int i=0; i<nx-1; i++){
		 // output rectangle to standard out to check
		 /*
		     cout << j*nx+i <<  "  " << j*nx+i+1 << "  "
		 	     << (j+1)*nx+i << "  " <<  (j+1)*nx+i+1<< endl;
			     */
		     file_out << j*nx+i <<  "  " << j*nx+i+1 << "  "
		 	     << (j+1)*nx+i  <<  endl;
		     file_out << j*nx+i+1 <<  "  " << (j+1)*nx+i+1 << "  "
		 	     <<   (j+1)*nx+i << endl;
		 
	     }}
	}

	for(int j=0; j< ny; j++){
	  for(int i=0; i<nx; i++){
	  x=deltax*i; y=deltay*j;
	  z=5.0*cos( ((x-2.0)*(x-2.0)+(y-2.0)*(y-2.0)) );
	 // z=5.0*exp(-(x-1.0)*(x-1.0)-(y-1.0)*(y-1.0));
	  file_out << x << "  " << y << "  " << z << endl;
	}}


	int ixtext=1,  iytext=1, iztext=1;
	int ixunits=1, iyunits=1, izunits=1;

	file_out << ixtext << "  " << ixunits<< endl;
	file_out << "daily@quota"  << "  " << "Kg@per@year" << endl;
	file_out << iytext<< "  " << iyunits<< endl;
	file_out << "yearly@loss" << "  " << "per@tonne" << endl;
	file_out << iztext<< "  " << izunits<< endl;
	file_out << "Giraffes" << "  " << "per@season" << endl;

	int ilegend=1;
	file_out << ilegend;

	file_out <<" lions\n" << endl;
	file_out <<" bears\n" << endl;
	
}
