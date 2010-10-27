#include  <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int main(){

	ofstream  file_out;
	file_out.open("data.dat", ios::out);
	int ndata, ntri, npoint;
	npoint=1;
	double x,y,z;
	int nx, ny;

        //make x longitude going from -180 t0 +180
        //make y longitude going from -90 t0 +90
        const double latspan=360;
        const double longspan=180;
        const double halflatspan=180;
        const double halflongspan=90;

	double deltax=12.0, deltay=12.0;

        double xn, yn;
        xn=latspan/deltax;
        nx=(int)xn;
        yn=longspan/deltay;
        ny=(int)yn;
        
        if(latspan-nx*deltax !=0){
                 cout << " delta x must go into 360\n";
                 cout << "nx=" << nx << " " << "deltax=" << deltax << endl;
                 exit(0);}
        if(longspan-ny*deltay !=0){
                 cout << " delta y must go into 180\n";
                 cout << "ny=" << ny << " " << "deltay=" << deltay << endl;
                 exit(0);}
        cout << "nx=" << nx << endl;
        cout << "ny=" << ny << endl;
        nx=nx+1;
        ny=ny+1;

	ndata=nx*ny;
	ntri=(nx-1)*(ny-1)*2;

	file_out << ndata << "  " << ntri <<  endl;

	if(ntri!=0){
	   for(int j=0; j<ny-1; j++){
             for(int i=0; i<nx-1; i++){
		     file_out << j*nx+i <<  "  " << j*nx+i+1 << "  "
		 	     << (j+1)*nx+i  <<  endl;
		     file_out << j*nx+i+1 <<  "  " << (j+1)*nx+i+1 << "  "
		 	     <<   (j+1)*nx+i << endl;
	     }}
	}

	for(int j=0; j< ny; j++){
	  for(int i=0; i<nx; i++){
	  x=-halflatspan+deltax*i; y=-halflongspan+deltay*j;
	 // z=5.0*cos( ((x-2.0)*(x-2.0)+(y-2.0)*(y-2.0)) );
	  z=5.0*exp(-((x-1.0)*(x-1.0)+(y-1.0)*(y-1.0))/10000. );
	  file_out << x << "  " << y << "  " << z << endl;
	}}


	int ixtext=0,  iytext=0, iztext=1;
	int ixunits=0, iyunits=0, izunits=1;

	file_out << ixtext << "  " << ixunits<< endl;
	//file_out << "daily@quota"  << "  " << "Kg@per@year" << endl;
	file_out << iytext<< "  " << iyunits<< endl;
//	file_out << "yearly@loss" << "  " << "per@tonne" << endl;
	file_out << iztext<< "  " << izunits<< endl;
	file_out << "Giraffes" << "  " << "per@season" << endl;
	
}
