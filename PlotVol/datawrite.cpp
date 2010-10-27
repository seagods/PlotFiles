#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

#include "../../XFiles/D3Dvec.h"
#include "../../XFiles/MeshNode.h"
#include "../../XFiles/RayMeshTet.h"

using namespace std;

int main(){

   fstream file_in;
   file_in.open("basicCube.dat",ios::in);

   int inodes,itets;
   bool periodicx,periodicy,periodicz,periodic;

   file_in >> inodes >> itets;
   file_in >> periodicx >> periodicy >> periodicz;

   cout <<"We have " << inodes << " nodes and " << itets << " tetrahedra "<< endl;
   cout <<"periodics x y and z are " << periodicx << " " << periodicy << " " << periodicz << endl; 

   double x, y, z;
   int ifree,mytet;
   int n_aliases;
   int alias[3];

   D3Dvec* NodeVec;  RayMeshTet* Tets;  MeshNode* Nodes;
   NodeVec=new D3Dvec[inodes]; Tets=new RayMeshTet[itets]; Nodes=new MeshNode[inodes];

   if(periodicx || periodicy || periodicz)periodic=true;

   if(periodic){
      for(int i=0; i< inodes; i++){
      file_in >> x >> y >> z >> mytet >> ifree >> n_aliases;
      Nodes[i].SetPos(x,y,z,NodeVec+i); 
      Nodes[i].SetMyTet(mytet);
      Nodes[i].SetFreedom(ifree);
      for(int ia=0; ia<n_aliases; ia++){
          file_in >> alias[ia];
          }
      if(n_aliases==1)Nodes[i].SetID(alias[0]);
      if(n_aliases==2)Nodes[i].SetID(alias[0], alias[1]);
      if(n_aliases==3)Nodes[i].SetID(alias[0], alias[1], alias[2]);
      }
   }
   else
   {
      for(int i=0; i< inodes; i++){
      file_in >> x >> y >> z >> mytet >> ifree;
      Nodes[i].SetPos(x,y,z,NodeVec+i); //meshnode holds Nodevec address only, it sets NodeVec to x,y,z
      Nodes[i].SetMyTet(mytet);
      Nodes[i].SetFreedom(ifree);
      }
   }
   //now read in tetrahedra
    int i1,i2,i3,i4,j1,j2,j3,j4,c1,c2,c3,c4;
    for(int i=0; i<itets;i++){
       file_in >> i1 >> i2 >> i3 >> i4 >> j1 >> j2 >> j3 >> j4 >> c1 >> c2 >> c3 >> c4;
       Tets[i].SetTet(i1,i2,i3,i4,j1,j2,j3,j4,(char)c1, (char)c2, (char)c3, (char)c4);
    }

     double wval[inodes];

     for(int i=0; i < inodes; i++){
          x=NodeVec[i].GetX(); y=NodeVec[i].GetY(); z=NodeVec[i].GetZ();

       //   wval[i]=2.0*exp(-((x-4)*(x-4)+(y-4)*(y-4)+(z-1)*(z-1))/32.0)
        //         +2.0*exp(-((x+4)*(x+4)+(y+2)*(y+2)+(z+3)*(z+3))/32.0);
          wval[i]=2.0*exp(-((x-4)*(x-4)+(y-4)*(y-4)+(z-3)*(z-3))/32.0)
                 +2.0*exp(-((x+4)*(x+4)+(y+4)*(y+4)+(z+3)*(z+3))/32.0);

        //13 test surfaces
  //  1        wval[i]=z;
  //  2        wval[i]=y;
  //  3        wval[i]=x;
   // 4        wval[i]=(x+y)/sqrt(2.0);
    //5      wval[i]=(x-y)/sqrt(2.0);
    //6       wval[i]=(x+z)/sqrt(2.0);
     //7     wval[i]=(x-z)/sqrt(2.0);  
   // 8      wval[i]=(y+z)/sqrt(2.0);  
    //9      wval[i]=(y-z)/sqrt(2.0);  
    //10      wval[i]=(x+y+z)/sqrt(3.0);
     //11     wval[i]=(x+y-z)/sqrt(3.0);
      //12    wval[i]=(x-y+z)/sqrt(3.0);
       //13   wval[i]=(x-y-z)/sqrt(3.0);
     }




     ofstream  file_out;
     file_out.open("VolData.dat");
     file_out << inodes << " " << itets << endl;
     file_out << periodicx <<" " << periodicy << " " << periodicz << endl;
     char charstop;
     if(periodicx || periodicy || periodicz)periodic=true;
     //program must store nodes in array with SAME ivalues 
     //or do something to get back the aliasing numbers

     for(int i=0; i<inodes; i++){
        file_out <<NodeVec[i].GetX() << " " << NodeVec[i].GetY() << "  " <<NodeVec[i].GetZ();
        file_out << " " << Nodes[i].GetMyTet() <<" " << (int)Nodes[i].GetFreedom() << "  ";
        if(periodic){
        charstop=Nodes[i].GetAlias();
        file_out << "  " << (int)charstop;
        int* TempID=Nodes[i].GetID();
        for(int ichar=0; ichar<(int)charstop;ichar++){
           file_out << " " << (int)*(TempID+ichar);}
            file_out << endl;}
     }

     int n1,n2,n3, n4; //remember GetN returns a pointer so as it can be NULL
     int *p1,*p2,*p3,*p4;

     for(int i=0; i<itets;i++){
        file_out << (Tets+i)->Get1() << " " << (Tets+i)->Get2()
             << " " << (Tets+i)->Get3() << " " << (Tets+i)->Get4();

        p1=(Tets+i)->GetN1();p2=(Tets+i)->GetN2();p3=(Tets+i)->GetN3();p4=(Tets+i)->GetN4();

        if(p1){n1=*p1;} else {n1=-1;}
        if(p2){n2=*p2;} else {n2=-1;}
        if(p3){n3=*p3;} else {n3=-1;}
        if(p4){n4=*p4;} else {n4=-1;}
        file_out << " " << n1 << " " << n2 <<" " << n3<< " " << n4;
        file_out << " " << (int)((Tets+i)->GetC1()) << " " << (int)((Tets+i)->GetC2())
             << " " << (int)((Tets+i)->GetC3()) << " " << (int)((Tets+i)->GetC4()) << endl;
     }
     for(int i=0; i< inodes; i++){
         file_out << wval[i] << " ";
         }
     cout << endl;

	int ixtext=1,  iytext=1, iztext=1, iwtext=1;
	int ixunits=1, iyunits=1, izunits=1, iwunits=1;

	file_out << ixtext << "  " << ixunits<< endl;
	file_out << "daily@quota"  << "  " << "Kg@per@year" << endl;
	file_out << iytext<< "  " << iyunits<< endl;
	file_out << "yearly@loss" << "  " << "per@tonne" << endl;
	file_out << iztext<< "  " << izunits<< endl;
	file_out << "Giraffes" << "  " << "per@season" << endl;
        file_out << iwtext << "  " << iwunits << endl;
	file_out <<"Lions" << "  " << "Bears@per@acre" << endl;
     file_out.close();




   return 0;

}
