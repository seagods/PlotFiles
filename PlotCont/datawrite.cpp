#include  <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

int main(){

	ofstream  file_out;
	file_out.open("data.dat", ios::out);
	int ndata, ntri, npoint;
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

	file_out << ndata << "  " << ntri <<  endl;

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


	int ixtext=1,  iytext=1, iztext=1;
	int ixunits=1, iyunits=1, izunits=1;

	file_out << ixtext << "  " << ixunits<< endl;
	file_out << "daily@quota"  << "  " << "Kg@per@year" << endl;
	file_out << iytext<< "  " << iyunits<< endl;
	file_out << "yearly@loss" << "  " << "per@tonne" << endl;
	file_out << iztext<< "  " << izunits<< endl;
	file_out << "Giraffes" << "  " << "per@season" << endl;
	
}
