#include  <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

int main(){

	ofstream  file_out;

	file_out.open("input.dat", ios::out);


	double x,y,z;

	double theta,pi;

	int istop;
	istop=180;
	pi=acos(-1.0);

	int nplots=2;
	file_out << nplots << endl;

	int ndata, ntype, ncol, nstyle, npoint;
	ndata=istop;  //number of points
	ntype=0;   //line not point
	ncol=3;    //preset colour 3
	nstyle=1;  // line stipple, write even if ntype=1 for points
	npoint=2;  //line width or point size

	file_out << ndata << "  " << ntype << "  " << ncol
		<< "  " << nstyle << "  " << npoint << endl;

	for(int i=0; i< istop; i++){
	  theta=((float)i*2)*pi/180.0;
	  x=cos(theta); y=sin(theta);
	  z=-pi+theta;
	  file_out << x << "  " << y << "  " << z << endl;
	}
	ndata=istop;  //number of points
	ntype=0;   //line not point
	ncol=6;    //preset colour 6
	nstyle=2;  // line stipple, write even if ntype=1 for points
	npoint=4;  //line width or point size
	file_out << ndata << "  " << ntype << "  " << ncol
		<< "  " << nstyle << "  " << npoint << endl;

	for(int i=0; i< istop; i++){
	  theta=((float)i*2)*pi/180.0+pi;
	  x=cos(theta); y=sin(theta);
	  z=-pi+theta-pi;
	  file_out << x << "  " << y << "  " << z << endl;
	}

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
