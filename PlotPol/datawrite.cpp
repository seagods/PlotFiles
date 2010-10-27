#include  <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int main(){

	ofstream  file_out;
	file_out.open("data.dat", ios::out);
	int ndata, ntri;
	double theta,phi,z;
	int ntheta, nphi;
        int includezero=1;  //actually, must always be 1.
        int include90=1;
        int include360=1;  //shall be lazy and treat 0 and 360 as if separate

        double  three_sixty, one_eighty, one, two, minus;
        one=1.0; two=2.0; one_eighty=180.0; three_sixty=360.0; minus=-1.0;
        double five, fourtyfive, eighteen;
        eighteen=18.0; five=5.0; fourtyfive=45.0;

        const double pi=acos(minus);
        const double piover2=pi/two;
        const double twopi=pi*two;
        const double convert=one_eighty/pi;
        const double phispan=twopi;
        const double thetaspan=piover2;

        //MUST FIX TO GO INTO 90 AND 360!
	double deltatheta=five/convert, deltaphi=five/convert;  
	//double deltatheta=eighteen/convert, deltaphi=fourtyfive/convert;  

        double thetan, phin;
        thetan=thetaspan/deltatheta;
        ntheta=(int)thetan;
        phin=phispan/deltaphi;
        nphi=(int)phin;
        if(include90==1)ntheta=ntheta+1;
        if(include360==1)nphi=nphi+1;
        
     //   cout << "ntheta=" << ntheta << endl;
     //   cout << "nphi=" << nphi << endl;


        double thetavec[ntheta];
        double phivec[nphi];
        thetavec[0]=-1.;  //test for errors
      
        if(includezero==1){
           for(int i=0;i<ntheta;i++){
             // cout << "theta=" << i*deltatheta*convert << endl;
              thetavec[i]=i*deltatheta;
           }
        }
        else{
           for(int i=1;i<ntheta;i++){
            //  cout << "theta=" << i*deltatheta*convert << endl;
              thetavec[i]=i*deltatheta;
           }
        }
        
       for(int i=0;i<nphi;i++){
         // cout << "phi=" << i*deltaphi*convert << endl;
          phivec[i]=i*deltaphi;
       }

       ndata=ntheta*nphi;
       //assumes include350==1
       //quads split into two triangles --hence nphi-2 not nphi-1
       //too lazy to to do checks
       if(includezero==0){
       ntri=(ntheta-1)*(nphi-1)*2; //aint gonna happen
       }
       if(includezero==1){
          ntri=(ntheta-2)*(nphi-1)*2+nphi-1;
       }

       int trinodes[ntri][3];

       //we shall be lazy, and treat the origin as though it 
       // were nphi separate points, with node numbers 0,ntheta,2ntheta a and so on
       // also treat 360 and 0 as if different.
       int kount=0;
       int i1,i2,i3,i4;
       int istart;
       int jstop;
       if(includezero==0)istart=1;
       if(includezero==1)istart=0;
       if(include360==1)jstop=nphi-1;

       file_out << ndata << "  " << ntri <<  endl;
       for(int i=istart; i<ntheta-1;i++){
           for(int j=0; j<jstop; j++){
            // quad is i+j*theta, i+1+j*ntheta, i+(j+1)*ntheta, i+1+(j+1)*ntheta
            i1=i+j*ntheta; i2=i+1+j*ntheta;
            i3=i+(j+1)*ntheta; i4=i+1+(j+1)*ntheta;
            if(i>0){
            if(j<jstop/2){
            trinodes[kount][0]=i1; 
            trinodes[kount][1]=i2; 
            trinodes[kount][2]=i3; }
            else{
            trinodes[kount][0]=i4; 
            trinodes[kount][1]=i3; 
            trinodes[kount][2]=i1; }

            file_out << trinodes[kount][0] << " " << trinodes[kount][1] 
                     << " " << trinodes[kount][2]  << endl;
            kount++;
            }
            if(j<jstop/2){
            trinodes[kount][0]=i3; 
            trinodes[kount][1]=i2; 
            trinodes[kount][2]=i4;}
            else{
            trinodes[kount][0]=i4; 
            trinodes[kount][1]=i1; 
            trinodes[kount][2]=i2;}
            file_out << trinodes[kount][0] << " " << trinodes[kount][1] 
                     << " " << trinodes[kount][2]  << endl;
            kount++;
       }}
       double x, y;
       kount=0;
       double datavecx[ndata]; //datavecs for testing
       double datavecy[ndata];
       double datavecz[ndata];
       for(int i=0; i<nphi;i++){
           for(int j=istart; j<ntheta; j++){
             x=thetavec[j]; y=phivec[i];
             //function discontinuous at origin, make sure its close to zero at origin
             z=5.*exp( -(x-1.5)*(x-1.5)*4.0 )*(
             cos(y)+cos(2*y)/2.0+cos(3*y)/4.0
            +cos(4*y)/8.0+cos(5*y)/16.0+cos(6*y)/32.0+cos(7*y)/64.0+cos(8*y)/128.0
            +cos(9*y)/256.0+cos(10*y)/512.+cos(11*y)/1024.0+cos(13*y)/2048.);
           // file_out << x*convert << "  " << y*convert << "  " <<  z << "  " << kount <<  endl;
           // No! Must be in radians
            file_out << x<< "  " << y<< "  " <<  z << endl;
            datavecx[kount]=x*convert;  // datavecs for testing
            datavecy[kount]=y*convert;
            datavecz[kount]=z;
            kount++;
       }}



	int ixtext=0,  iytext=0, iztext=1;
	int ixunits=0, iyunits=0, izunits=1;

	file_out << ixtext << "  " << ixunits<< endl;
	file_out << iytext<< "  " << iyunits<< endl;
	file_out << iztext<< "  " << izunits<< endl;
	file_out << "Giraffes" << "  " << "per@season" << endl;
/**************************FOR TESTING **************************************
       for(int i=0; i<ntri;i++){
            i1=trinodes[i][0];
            i2=trinodes[i][1];
            i3=trinodes[i][2];
            cout << i1 << " " << i2 << " " << i3 << endl;
            cout << datavecx[i1] << " " << datavecy[i1] << endl;
            cout << datavecx[i2] << " " << datavecy[i2] << endl;
            cout << datavecx[i3] << " " << datavecy[i3] << endl;
            cout << "********************************************\n";
       }
**************************FOR TESTING **************************************/
      // LINES
      int nplots=2;
      ndata=90;
      int ntype=0;  // 0 for lines, 1 for points
      int ncol=0;   // zero for black
      int nstyle=0;  //line stippled, (no stipple=0)
      int npoint=1;  //point size for lines

      file_out << nplots << endl;

      double rho;
      // Archimedian Spiral;
      file_out << ndata << " " << ntype << "  "<<  ncol <<" " << nstyle << " " << npoint << endl;
      for(int i=0; i<ndata; i++){
        phi=((double) i)/convert;      
        rho=phi;
        file_out <<  rho << " " << phi << endl;
      }
      ndata=360;
      //Polar Rose
      file_out << ndata << " " << ntype << "  "<<  ncol <<" " << nstyle << " " << npoint << endl;
      for(int i=0; i<ndata; i++){
        phi=((double) i)/convert;      
        rho=fabs(piover2*sin(4.0*phi));
        file_out <<  rho << " " << phi << endl;
      }
      int nsuns=1;
      file_out << nsuns << endl;
      rho=.75; phi=0.0;
      file_out <<  rho << " " << phi << endl;
      int nsats=2;
      file_out << nsats << endl;
      rho=1.15; phi=0.75;
      file_out <<  rho << " " << phi << endl;
      rho=0.85; phi=1.75;
      file_out <<  rho << " " << phi << endl;
      
	
}
