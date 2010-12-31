//surface.dat MUST ALWAYS BE SQUARE!
//-------------------------------------------------------------------------------
// Copyright 2009-2011 Christopher Godsalve.
// All Rights Reserved.
//
// Permission to use, copy, modify and distribute this software (if not modified) and its
// documentation for educational, research and non-profit purposes, without fee,
// and without a written agreement is hereby granted, provided that the above
// copyright notice and the following three paragraphs appear in all copies.
// 
//
// To request permission to incorporate this software into commercial products
// contact Dr C. Godsalve, 42 Swainstone Road, Reading, Berks, UK or by email at
// seagods@btinternet.com or seagods@hotmail.com.
//
// IN NO EVENT SHALL CHRISTOPHER GODSALVE BE LIABLE TO ANY PARTY FOR
// DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING 
// LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
// EVEN IF CHRITOPHER GODSALVE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
// CHRISTOPHER GODSALVE SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON AN `AS IS' BASIS, AND CHRISTOPHER 
// GODSALVE HAS NO OBLIGATIONS TO PROVIDE MAINTAINANCE, SUPPORT, UPDATES, 
// ENHANCEMENTS, OR MODIFICATIONS IF HE CHOOSES NOT TO DO SO.
//--------------------------------------------------------------------------------
#include "basicCube.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>  //read and write to string

#include "../../XFiles/SetUp.h"  //loads of declarations and initialisations
#include "../../XFiles/TrueType.h"
#include "../../XFiles/Controls.h"
#include "../../XFiles/DrawLightPos.h"
#include "../../XFiles/DrawLightCol.h"
#include "../../XFiles/DrawMatCol.h"
#include "../../XFiles/DrawLogicBox.h"

int isidex, isidey, isidez;   //global  mesh integer parameters
int igapx, igapy, igapz;
int edgetotal, nodetotal,tetstotal;

double W=50000;     //global mesh dimensions OpenGL
double H=50000;
double D=50000;
double xx1=-W;
double xx2=W;
double yy1=-H;
double yy2=H;
double zz1=-D;
double zz2=D;

double X,Y,Z;               //mesh dimensions

double xunit,yunit,zunit;

//For 3D Points
int*  npoint3Darray;
double **xarray,**yarray,**zarray;

MeshNode *Node; RayMeshTet *Tets;

void EventLoop()
{
 CCam Camera1;
 bool quitit=false;
 SDL_Event event;
 SDL_MouseMotionEvent event2; //Not yet used
 SDL_keysym  *whatkey;

 bool verbose=false;

 LIGHTS=false;  //don't need it

 if(hidemousecursor)SDL_ShowCursor(0);
      if(LIGHTS){
	      speed=50.0;
	      angspeed=0.05;}
      else
      {
	      speed=5.0;
	      angspeed=0.005;}


    if(staked){
	    Camera1.SetPos(0.0,0.0,0.0);
	    Camera1.SetView(0.0,0.0,1000.0);
    }

    bool exitnow=false;
    isidex=17; isidey=15; isidez=13;
              //mesh dimensions

    X=-8.0;Y=-8.0;Z=-8.0;
    xunit=1.0;yunit=1.0;zunit=1.0;

    igapx=(isidex-1);igapy=(isidey-1);igapz=(isidez-1);
    if(isidex%2==0)exitnow=true;
    if(isidey%2==0)exitnow=true;
    if(isidez%2==0)exitnow=true;
    if(exitnow){cout << "Must have odd side values!\n"; exit(1);}


    edgetotal=igapx*isidey*isidez
                 +isidex*igapy*isidez
                 +isidex*isidey*igapz
                 +igapx*igapy*isidez   // now the zigzags
                 +igapx*isidey*igapz   
                 +isidex*igapy*igapz;  

    nodetotal=isidex*isidey*isidez;

    cout << "nodes=" << nodetotal << endl;
    cout << "edges=" << edgetotal << endl;

    int nx,ny,nz,nxy,nxz,nyz;

    nx=igapx*isidey*isidez;
    ny=igapy*isidex*isidez;
    nz=igapz*isidex*isidey;

    nxy=igapx*igapy*isidez;
    nxz=igapx*isidey*igapz;
    nyz=isidex*igapy*igapz;

    tetstotal=igapx*igapy*igapz*5;

    Node=new MeshNode[nodetotal];
       if(!Node){cout << "Node Memory failed  " << endl;  exit(1);}
    NodeV=new D3Dvec[nodetotal];
       if(!NodeV){cout << "Node Memory failed  " << endl;  exit(1);}
    Tets=new RayMeshTet[tetstotal];
       if(!Tets){cout << "Tets Memory failed  " << endl;  exit(1);}

    MeshNode* current;
    D3Dvec* currentV;

    int inodes,iedge,itets;
    int irectxy,irectxy2,irectxy3;

    irectxy=isidex*isidey; 
    irectxy2=igapx*igapy;
    irectxy3=igapx*(igapy-1);

    double xval,yval,zval;

    double *pos1, *pos2;

    //for testing only
/*
    isidex=3; igapx=2; isidey=4; igapy=3; isidez=5, igapz=4;
    irectxy=isidex*isidey; 
    irectxz=isidex*isidez; 
    irectyz=isidey*isidez; 
    irectxy2=igapx*igapy; 
    irectxz2=igapx*igapz; 
    irectyz2=igapy*igapz; 
*/

    bool evenk;
    bool even;
    inodes=0; itets=0;

    int icube=-1;
    int icube1, icube2, icube3, icube4, icube5, icube6;
    //p for periodic bc
    int icubep1, icubep2, icubep3, icubep4, icubep5, icubep6;


    bool xsurf1,xsurf2,ysurf1,ysurf2,zsurf1,zsurf2;

    int neighb1,neighb2,neighb3,neighb4;
    char whichface1,whichface2,whichface3,whichface4;

//  We are doing iside*iside*iside nodes,
//  but are also doing  igap*igap*igap cubes
//  xsurf,ysurf and zsurf tell us whether the CUBE
//  is on the surface, not the node! hence the zsurf if igapz

//  Repeat, xsurf does NOT refer to a node on the surface
    neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;

    for(int k=0; k< isidez; k++){
      int i1, i2, i3,i4;
      if(k%2==0){evenk=true;} else {evenk=false;}
      zval=Z+k*zunit;
      if(k==0){zsurf1=true;} else {zsurf1=false;}
      if(k==igapz-1){zsurf2=true;} else {zsurf2=false;}
      for(int j=0; j< isidey; j++){
        yval=Y+j*yunit;
        if(j==0){ysurf1=true;} else {ysurf1=false;}
        if(j==igapy-1){ysurf2=true;} else {ysurf2=false;}
        for(int i=0; i< isidex; i++){
	   xval=X+i*xunit;

           if(i==0){xsurf1=true;} else {xsurf1=false;}
           if(i==igapx-1){xsurf2=true;} else {xsurf2=false;}


           if(i==0 && j==0){
               if(evenk){even=true;} else {even=false;}
            }

           current=Node+inodes;
           currentV=NodeV+inodes;

           Node[inodes].SetPos(xval,yval,zval, currentV);

           if(periodicx){
              if(i==0){
                Node[inodes].SetID(inodes+igapx);}
              if(i==igapx){
                  Node[inodes].SetID(inodes-igapx);}
           }
           if(periodicy){
              bool setperiod=false;
              int ialias;
              if(j==0){ialias=inodes+irectxy-1-igapx; setperiod=true;}
              if(j==igapy){ialias=inodes-irectxy+1+igapx; setperiod=true;}
              if(setperiod){
              char AliasNo=Node[inodes].GetAlias();
              if(AliasNo==1){
                  //so far the node has an ID and a periodic x alias
                  int ispare=Node[inodes].GetID1();
                  //now it will have the same ID and a periodic x and a periodic y alias
                  Node[inodes].SetID(ispare,ialias);
              }
              else{
                  //so far it can only be 1 or zero
                  Node[inodes].SetID(ialias);
              }
              }}
           if(periodicz){
              bool setperiod=false;
              int ialias;
              if(k==0){ialias=inodes+irectxy*igapz; setperiod=true;}
              if(k==igapz){ialias=inodes-irectxy*igapz; setperiod=true;}
              if(setperiod){
              char AliasNo=Node[inodes].GetAlias();
                  //so far the node has an ID and a periodic x or y 
                  //alias, or  possibly both
              if(AliasNo==2){
                  int ispare1=Node[inodes].GetID1();
                  int ispare2=Node[inodes].GetID2();
                  Node[inodes].SetID(ispare1,ispare2,ialias);
              }
              if(AliasNo==1){
                  int ispare1=Node[inodes].GetID1();
                  Node[inodes].SetID(ispare1,ialias);
              }
              if(AliasNo==0){
                  Node[inodes].SetID(ialias);
              }
           }}

           unsigned char free=255;
           if(i==0 && j==0 && k==0)free=0;
           if(i==igapx && j==0 && k==0)free=0;
           if(i==0 && j==igapy && k==0)free=0;
           if(i==igapx && j==igapy && k==0)free=0;
           if(i==0 && j==0 && k==igapz)free=0;
           if(i==igapx && j==0 && k==igapz)free=0;
           if(i==0 && j==igapy && k==igapz)free=0;
           if(i==igapx && j==igapy && k==igapz)free=0;

           if(free!=0){ //not on a corner
              if( k==0 && j==0)free=2;  //can only move in x
              if( k==0 && j==igapy)free=2;
              if( k==igapz && j==0)free=2;  
              if( k==igapz && j==igapy)free=2;
              if( k==0 && i==0)free=3;  //can only move in y
              if( k==0 && i==igapx)free=3;
              if( k==igapz && i==0)free=3; 
              if( k==igapz && i==igapx)free=3;
              if(i==0 && j==0)free=4;   //can only move in z
              if(i==0 && j==igapy)free=4; 
              if(i==igapx && j==0)free=4; 
              if(i==igapx && j==igapy)free=4; 
           }
           if(free > 4){   //not on corner or edge
           if(k==0)free=6;  //can move xy
           if(k==igapz)free=6; 
           if(j==0)free=7;  //can move xz
           if(j==igapy)free=7; 
           if(i==0)free=8; //can move yz
           if(i==igapx)free=8;
           }

           if(free==255)free=1;   //can move in xyz

           Node[inodes].SetFreedom(free);

        if(k<igapz){
             if(j<igapy){
               if(i<igapx){
                 icube++;



//               We later multiply by 5, but this gives us
                 if(xsurf1){
                 icubep1=icube+igapx-1;}
                 icube1=icube-1;
                 if(xsurf2){
                 icubep2=icube-igapx+1;}
                 icube2=icube+1;

                 if(ysurf1){
                 icubep3=icube+irectxy3;}
                 icube3=icube-igapx;
                 if(ysurf2){
                 icubep4=icube-irectxy3;}
                 icube4=icube+igapx;

                 if(zsurf1){
                 icubep5=icube+irectxy2*(igapz-1);}
                 icube5=icube-irectxy2; 
                 if(zsurf2){
                 icubep6=icube-irectxy2*(igapz-1);}
                 icube6=icube+irectxy2; 

                 if(even){
                      i1=inodes; i2=i1+1; i3=i1+isidex; i4=i1+irectxy;
                                                       //Tet1
                      neighb1=icube*5+4;  whichface1=4;  //Face 1 goes to Tet5 face 4
                      if(!xsurf1){
                      neighb2=icube1*5;   whichface2=3; }

                      else{
                      neighb2=icubep1*5;   whichface2=3;}//Face 2 goes to Tet1 face 3
                      if(!ysurf1){
                      neighb3=icube3*5+1; whichface3=2; }
                      else{
                      neighb3=icubep3*5+1; whichface3=2; }  //Face 3 goes to Tet2 face 2
                      if(!zsurf1){
                      neighb4=icube5*5+2; whichface4=4;}
                      else{
                      neighb4=icubep5*5+2; whichface4=4;}  //Face 4 goes to Tet3 face 4

            if(itets==1840){
                 cout << "Here\n";
            }
                      (Tets+itets)->SetTet(i1,i2,i3,i4,
                                           neighb1,neighb2,neighb3,neighb4,
                                           whichface1,whichface2,whichface3,whichface4);
                      //we have set with periodic bcs, but there might not be any
                      if(!periodicx && xsurf1)(Tets+itets)->SetNULL2();
                      if(!periodicy && ysurf1)(Tets+itets)->SetNULL3();
                      if(!periodicz && zsurf1)(Tets+itets)->SetNULL4();
                      neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;
                      itets++;

                      i1=inodes+1+isidex; i2=i1-1; i3=i1-isidex; i4=i1+irectxy;
                                                      //Tet2
                      neighb1=icube*5+4;  whichface1=3;  //Face 1 goes to Tet5 face 3
                      if(!xsurf2){
                      neighb2=icube2*5+1; whichface2=3;}
                      else{  
                      neighb2=icubep2*5+1; whichface2=3;} //Face 2 goes to Tet2 face 3
                      if(!ysurf2){
                      neighb3=icube4*5;   whichface3=2;}
                      else{
                      neighb3=icubep4*5;   whichface3=2;}  //Face 3 goes to Tet1 face 2 
                      if(!zsurf1){
                      neighb4=icube5*5+3; whichface4=4;}
                      else{
                      neighb4=icubep5*5+3; whichface4=4;} //Face 4 goes to Tet4 face 4

            if(itets==1840){
                 cout << "Here\n";
            }
                      (Tets+itets)->SetTet(i1,i2,i3,i4,
                                           neighb1,neighb2,neighb3,neighb4,
                                           whichface1,whichface2,whichface3,whichface4);
                      //we have set with periodic bcs, but there might not be any
                      if(!periodicx && xsurf2)(Tets+itets)->SetNULL2();
                      if(!periodicy && ysurf2)(Tets+itets)->SetNULL3();
                      if(!periodicz && zsurf1)(Tets+itets)->SetNULL4();
                      neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;
                      itets++;

                      i1=inodes+1+irectxy; i2=i1-1; i3=i1+isidex; i4=i1-irectxy;
                                                      //Tet3
                      neighb1=icube*5+4;  whichface1=2;  //Face 1 goes to Tet5 face 2
                      if(!xsurf2){
                      neighb2=icube2*5+2; whichface2=3;}
                      else{
                      neighb2=icubep2*5+2; whichface2=3;}  //Face 2 goes to Tet3 face 3
                      if(!ysurf1){
                      neighb3=icube3*5+3; whichface3=2; }
                      else{
                      neighb3=icubep3*5+3; whichface3=2; }  //Face 3 goes to Tet4 face 2
                      if(!zsurf2){
                      neighb4=icube6*5;   whichface4=4; }
                      else{
                      neighb4=icubep6*5;   whichface4=4; }   //Face 4 goes to Tet1 face 4

            if(itets==1840){
                 cout << "Here\n";
            }
                      (Tets+itets)->SetTet(i1,i2,i3,i4,
                                           neighb1,neighb2,neighb3,neighb4,
                                           whichface1,whichface2,whichface3,whichface4);
                      if(!periodicx && xsurf2)(Tets+itets)->SetNULL2();
                      if(!periodicy && ysurf1)(Tets+itets)->SetNULL3();
                      if(!periodicz && zsurf2)(Tets+itets)->SetNULL4();
                      neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;
                      itets++;

                      i1=inodes+isidex+irectxy; i2=i1+1; i3=i1-isidex; i4=i1-irectxy;
                                                     //Tet4
                      neighb1=icube*5+4;  whichface1=1;  //Face 1 goes to Tet5 face 1
                      if(!xsurf1){
                      neighb2=icube1*5+3; whichface2=3;}
                      else{
                      neighb2=icubep1*5+3; whichface2=3;}//Face 2 goes to Tet4 face 3
                      if(!ysurf2){
                      neighb3=icube4*5+2; whichface3=2;}
                      else{
                      neighb3=icubep4*5+2; whichface3=2;}  //Face 3 goes to Tet3 face 2
                      if(!zsurf2){
                      neighb4=icube6*5+1; whichface4=4; }
                      else{
                      neighb4=icubep6*5+1; whichface4=4; } //Face 4 goes to Tet2 face 4

            if(itets==1840){
                 cout << "Here\n";
            }
                      (Tets+itets)->SetTet(i1,i2,i3,i4,
                                           neighb1,neighb2,neighb3,neighb4,
                                           whichface1,whichface2,whichface3,whichface4);
                      if(!periodicx && xsurf1)(Tets+itets)->SetNULL2();
                      if(!periodicy && ysurf2)(Tets+itets)->SetNULL3();
                      if(!periodicz && zsurf2)(Tets+itets)->SetNULL4();
                      neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;
                      itets++;

                      i1=inodes+1; i2=i1+isidex-1; i3=i1-1+irectxy; i4=i1+isidex+irectxy;
                                                     //Tet5
                      neighb1=icube*5+3; whichface1=1;  //Face 1 goes to Tet4 face 1
                      neighb2=icube*5+2; whichface2=1;  //Face 2 goes to Tet3 face 1
                      neighb3=icube*5+1; whichface3=1;  //Face 3 goes to Tet2 face 1
                      neighb4=icube*5;   whichface4=1;  //Face 4 goes to Tet1 face 1

            if(itets==1840){
                 cout << "Here\n";
            }
                      (Tets+itets)->SetTet(i1,i2,i3,i4,
                                           neighb1,neighb2,neighb3,neighb4,
                                           whichface1,whichface2,whichface3,whichface4);
                      neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;
                      itets++;

                 }
                 else
                 {
                      i1=inodes+1; i2=i1+isidex; i3=i1-1; i4=i1+irectxy;
                                                      //Tet1
                      neighb1=icube*5+4;  whichface1=3;  //Face 1 goes to Tet5 face 3
                      if(!ysurf1){
                      neighb2=icube3*5+1; whichface2=3;}
                      else{
                      neighb2=icubep3*5+1; whichface2=3;}  //Face 2 goes to Tet2 face 3
                      if(!xsurf2){
                      neighb3=icube2*5; whichface3=2;}
                      else{
                      neighb3=icubep2*5; whichface3=2;} //Face 3 goes to   Tet1 face 2
                      if(!zsurf1){
                      neighb4=icube5*5+2; whichface4=4; }
                      else{
                      neighb4=icubep5*5+2; whichface4=4; } //Face 4 goes to Tet3 face 4

            if(itets==1840){
                 cout << "Here\n";
            }
                      (Tets+itets)->SetTet(i1,i2,i3,i4,
                                           neighb1,neighb2,neighb3,neighb4,
                                           whichface1,whichface2,whichface3,whichface4);
                      if(!periodicy && ysurf1)(Tets+itets)->SetNULL2();
                      if(!periodicx && xsurf2)(Tets+itets)->SetNULL3();
                      if(!periodicz && zsurf1)(Tets+itets)->SetNULL4();
                      neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;
                      itets++;
                      

                      i1=inodes+isidex; i2=i1-isidex; i3=i1+1; i4=i1+irectxy;
                                                      //Tet2
                      neighb1=icube*5+4;  whichface1=4;  //Face 1 goes to Tet5 face 4
                      if(!ysurf2){
                      neighb2=icube4*5; whichface2=3;}
                      else{
                      neighb2=icubep4*5; whichface2=3;}  //Face 2 goes to Tet1 face 3
                      if(!xsurf1){
                      neighb3=icube1*5+1;   whichface3=2;}
                      else{
                      neighb3=icubep1*5+1;   whichface3=2;}  //Face 3 goes to Tet2 face 2
                      if(!zsurf1){
                      neighb4=icube5*5+3; whichface4=4; }
                      else{
                      neighb4=icubep5*5+3; whichface4=4; }  //Face 4 goes to Tet4 face 4

            if(itets==1840){
                 cout << "Here\n";
            }
                      (Tets+itets)->SetTet(i1,i2,i3,i4,
                                           neighb1,neighb2,neighb3,neighb4,
                                           whichface1,whichface2,whichface3,whichface4);
                      if(!periodicy && ysurf2)(Tets+itets)->SetNULL2();
                      if(!periodicx && xsurf1)(Tets+itets)->SetNULL3();
                      if(!periodicz && zsurf1)(Tets+itets)->SetNULL4();
                      neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;
                      itets++;

                      i1=inodes+irectxy; i2=i1+isidex; i3=i1+1; i4=i1-irectxy;
                                                     //Tet3
                      neighb1=icube*5+4;  whichface1=2;  //Face 2 goes to Tet5 face 2
                      if(!ysurf1){
                      neighb2=icube3*5+3; whichface2=3;}
                      else{
                      neighb2=icubep3*5+3; whichface2=3;} //Face 4 goes to Tet4 face 3
                      if(!xsurf1){
                      neighb3=icube1*5+2; whichface3=2;}
                      else{
                      neighb3=icubep1*5+2; whichface3=2;}  //Face 3 goes to Tet3 face 2
                      if(!zsurf2){
                      neighb4=icube6*5; whichface4=4;}
                      else{
                      neighb4=icubep6*5; whichface4=4;}    //Face 1 goes to Tet1 face 4

            if(itets==1840){
                 cout << "Here\n";
            }
                      (Tets+itets)->SetTet(i1,i2,i3,i4,
                                           neighb1,neighb2,neighb3,neighb4,
                                           whichface1,whichface2,whichface3,whichface4);
                      if(!periodicy && ysurf1)(Tets+itets)->SetNULL2();
                      if(!periodicx && xsurf1)(Tets+itets)->SetNULL3();
                      if(!periodicz && zsurf2)(Tets+itets)->SetNULL4();
                      neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;
                      itets++;

                      i1=inodes+1+isidex+irectxy; i2=i1-isidex; i3=i1-1; i4=i1-irectxy;
                                                     //Tet4
                      neighb1=icube*5+4;  whichface1=1;  //Face 2 goes to Tet5 face 1
                      if(!ysurf2){
                      neighb2=icube4*5+2; whichface2=3;}
                      else{
                      neighb2=icubep4*5+2; whichface2=3;}  //Face 4 goes to Tet3 face 3
                      if(!xsurf2){
                      neighb3=icube2*5+3; whichface3=2;}
                      else{
                      neighb3=icubep2*5+3; whichface3=2;} //Face 3 goes to Tet4 face 2
                      if(!zsurf2){
                      neighb4=icube6*5+1; whichface4=4;}
                      else{
                      neighb4=icubep6*5+1; whichface4=4;}  //Face 1 goes to Tet2 face 4
                      
            if(itets==1840){
                 cout << "Here\n";
            }
                      (Tets+itets)->SetTet(i1,i2,i3,i4,
                                           neighb1,neighb2,neighb3,neighb4,
                                           whichface1,whichface2,whichface3,whichface4);
                      if(!periodicy && ysurf2)(Tets+itets)->SetNULL2();
                      if(!periodicx && xsurf2)(Tets+itets)->SetNULL3();
                      if(!periodicz && zsurf2)(Tets+itets)->SetNULL4();
                      neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;
                      itets++;

                      

                      i1=inodes; i2=i1+1+isidex; i3=i1+isidex+irectxy; i4=i1+1+irectxy;
                                                    //Tet5
                      neighb1=icube*5+3; whichface1=1;  //Face 2 goes to Tet4 face 1
                      neighb2=icube*5+2; whichface2=1;  //Face 4 goes to Tet3 face 1
                      neighb3=icube*5;   whichface3=1;  //Face 3 goes to Tet1 face 1
                      neighb4=icube*5+1; whichface4=1;  //Face 1 goes to Tet2 face 1

            if(itets==1840){
                 cout << "Here\n";
            }
                      (Tets+itets)->SetTet(i1,i2,i3,i4,
                                           neighb1,neighb2,neighb3,neighb4,
                                           whichface1,whichface2,whichface3,whichface4);
                      neighb1=-1; neighb2=-1; neighb3=-1; neighb4=-1;
                      itets++;
                   
                 }

               Node[inodes].SetMyTet(itets-5);

               

           }}}  //endif i<igapx, j<igapy,k < igapz

           //if i=igapx, last cube to be set was on x=X
           //if j=igapy, last cube to be set was on y=Y

           if(k<igapz){
               if(i==igapx){
                   Node[inodes].SetMyTet(itets-5);}
               //for j==igapy, last to be created was the last cube on this level!
               if(j==igapy){
                   Node[inodes].SetMyTet(itets-(igapx-1-i)*5-4);}
               if(j==igapy && i==igapx)Node[inodes].SetMyTet(itets-4);
            }
           if(k==igapz){
               //if k==igapz, last cube to be set was last cube
               if(i<igapx && j < igapx){
                   Node[inodes].SetMyTet(
                        itets-irectxy2*5+5*i+5*j*igapx+2);
                      } 
               if(i==igapx){
                   Node[inodes].SetMyTet(itets-irectxy2*5+(1+j)*igapx*5-3);}
               //for j==igapy, last to be created was the last cube on this level!
               if(j==igapy){
                   Node[inodes].SetMyTet(itets-(igapx-1-i)*5-2);}
               if(i==igapx && j==igapy)Node[inodes].SetMyTet(itets-2);
            }
 //           cout <<inodes << endl;


           inodes++;  
           if(even){even=false;} else {even=true;}

         }    //end iloop
       }   //end j loop
     }  //end k loop

//  THIS LOOP TESTS ALL THE FACE CONNECTIONS

     for(int i=0; i<itets; i++){
     int m1,m2,m3,n1,n2,n3,iface,ineighb;
     int m4,m5,m6,m7,m8,m9,m10,m11,m12; // for aliases in periodic bcs
     int* neighb;
     char malias1, malias2, malias3; //number of aliases for each node in the face of the current tet

        m4=-1,m5=-1,m6=-1,m7=-1,m8=-1,m9=-1,m10=-1,m11=-1,m12=-1;
        //face 1
        m1=(Tets+i)->Get2(); m2=(Tets+i)->Get3(); m3=(Tets+i)->Get4();
        neighb=(Tets+i)->GetN1();

        if(neighb){
          iface=(Tets+i)->GetC1();

          if(iface==1){
          n1=(Tets+*neighb)->Get2(); n2=(Tets+*neighb)->Get3(); n3=(Tets+*neighb)->Get4();}
          if(iface==2){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get3(); n3=(Tets+*neighb)->Get4();}
          if(iface==3){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get2(); n3=(Tets+*neighb)->Get4();}
          if(iface==4){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get2(); n3=(Tets+*neighb)->Get3();}

          malias1=Node[m1].GetAlias(); malias2=Node[m2].GetAlias(); malias3=Node[m3].GetAlias();

          m4=-1,m5=-1,m6=-1,m7=-1,m8=-1,m9=-1,m10=-1,m11=-1,m12=-1;
          if(malias1==1)m4=Node[m1].GetID1();
          if(malias1==2){m4=Node[m1].GetID1(); m5=Node[m1].GetID2();}
          if(malias1==3){m4=Node[m1].GetID1(); m5=Node[m1].GetID2();m6=Node[m1].GetID3();}
          if(malias2==1)m7=Node[m2].GetID1();
          if(malias2==2){m7=Node[m2].GetID1(); m8=Node[m2].GetID2();}
          if(malias2==3){m7=Node[m2].GetID1(); m8=Node[m2].GetID2();m9=Node[m2].GetID3();}
          if(malias3==1)m10=Node[m3].GetID1();
          if(malias3==2){m10=Node[m3].GetID1(); m11=Node[m3].GetID2();}
          if(malias3==3){m10=Node[m3].GetID1(); m11=Node[m3].GetID2();m12=Node[m3].GetID3();}


        int kount=0;
        if(m1==n1 || m1==n2 || m1==n3)kount++;
        if(m2==n1 || m2==n2 || m2==n3)kount++;
        if(m3==n1 || m3==n2 || m3==n3)kount++;
        if(m4==n1 || m4==n2 || m4==n3)kount++;
        if(m5==n1 || m5==n2 || m5==n3)kount++;
        if(m6==n1 || m6==n2 || m6==n3)kount++;
        if(m7==n1 || m7==n2 || m7==n3)kount++;
        if(m8==n1 || m8==n2 || m8==n3)kount++;
        if(m9==n1 || m9==n2 || m9==n3)kount++;
        if(m10==n1 || m10==n2 || m10==n3)kount++;
        if(m11==n1 || m11==n2 || m11==n3)kount++;
        if(m12==n1 || m12==n2 || m12==n3)kount++;

        
        if(kount !=3 ){
           cout << "Houston, we have a problem...\n";
           cout << "No match for Tetrahedron " << i << "  nodes face 1 << kount=" << kount;
           exit(0);
         }
         } //endif for neighbour exists
       //face 2
        m1=(Tets+i)->Get1(); m2=(Tets+i)->Get3(); m3=(Tets+i)->Get4();
        neighb=(Tets+i)->GetN2();

        if(neighb){
          iface=(Tets+i)->GetC2();
          if(iface==1){
          n1=(Tets+*neighb)->Get2(); n2=(Tets+*neighb)->Get3(); n3=(Tets+*neighb)->Get4();}
          if(iface==2){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get3(); n3=(Tets+*neighb)->Get4();}
          if(iface==3){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get2(); n3=(Tets+*neighb)->Get4();}
          if(iface==4){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get2(); n3=(Tets+*neighb)->Get3();}

          malias1=Node[m1].GetAlias(); malias2=Node[m2].GetAlias(); malias3=Node[m3].GetAlias();

          m4=-1,m5=-1,m6=-1,m7=-1,m8=-1,m9=-1,m10=-1,m11=-1,m12=-1;
          if(malias1==1)m4=Node[m1].GetID1();
          if(malias1==2){m4=Node[m1].GetID1(); m5=Node[m1].GetID2();}
          if(malias1==3){m4=Node[m1].GetID1(); m5=Node[m1].GetID2();m6=Node[m1].GetID3();}
          if(malias2==1)m7=Node[m2].GetID1();
          if(malias2==2){m7=Node[m2].GetID1(); m8=Node[m2].GetID2();}
          if(malias2==3){m7=Node[m2].GetID1(); m8=Node[m2].GetID2();m9=Node[m2].GetID3();}
          if(malias3==1)m10=Node[m3].GetID1();
          if(malias3==2){m10=Node[m3].GetID1(); m11=Node[m3].GetID2();}
          if(malias3==3){m10=Node[m3].GetID1(); m11=Node[m3].GetID2();m12=Node[m3].GetID3();}


        int kount=0;

        if(m1==n1 || m1==n2 || m1==n3)kount++;
        if(m2==n1 || m2==n2 || m2==n3)kount++;
        if(m3==n1 || m3==n2 || m3==n3)kount++;
        if(m4==n1 || m4==n2 || m4==n3)kount++;
        if(m5==n1 || m5==n2 || m5==n3)kount++;
        if(m6==n1 || m6==n2 || m6==n3)kount++;
        if(m7==n1 || m7==n2 || m7==n3)kount++;
        if(m8==n1 || m8==n2 || m8==n3)kount++;
        if(m9==n1 || m9==n2 || m9==n3)kount++;
        if(m10==n1 || m10==n2 || m10==n3)kount++;
        if(m11==n1 || m11==n2 || m11==n3)kount++;
        if(m12==n1 || m12==n2 || m12==n3)kount++;

        if(kount !=3 ){
           cout << "Houston, we have a problem...\n";
           cout << "No match for Tetrahedron " << i << "  face 2  kount=" << kount << endl;
           exit(0);
         }
         } //endif for neighbour exists
       //face 3
        m1=(Tets+i)->Get1(); m2=(Tets+i)->Get2(); m3=(Tets+i)->Get4();
        neighb=(Tets+i)->GetN3();

        if(neighb){
          iface=(Tets+i)->GetC3();
          if(iface==1){
          n1=(Tets+*neighb)->Get2(); n2=(Tets+*neighb)->Get3(); n3=(Tets+*neighb)->Get4();}
          if(iface==2){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get3(); n3=(Tets+*neighb)->Get4();}
          if(iface==3){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get2(); n3=(Tets+*neighb)->Get4();}
          if(iface==4){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get2(); n3=(Tets+*neighb)->Get3();}

          malias1=Node[m1].GetAlias(); malias2=Node[m2].GetAlias(); malias3=Node[m3].GetAlias();

          m4=-1,m5=-1,m6=-1,m7=-1,m8=-1,m9=-1,m10=-1,m11=-1,m12=-1;
          if(malias1==1)m4=Node[m1].GetID1();
          if(malias1==2){m4=Node[m1].GetID1(); m5=Node[m1].GetID2();}
          if(malias1==3){m4=Node[m1].GetID1(); m5=Node[m1].GetID2();m6=Node[m1].GetID3();}
          if(malias2==1)m7=Node[m2].GetID1();
          if(malias2==2){m7=Node[m2].GetID1(); m8=Node[m2].GetID2();}
          if(malias2==3){m7=Node[m2].GetID1(); m8=Node[m2].GetID2();m9=Node[m2].GetID3();}
          if(malias3==1)m10=Node[m3].GetID1();
          if(malias3==2){m10=Node[m3].GetID1(); m11=Node[m3].GetID2();}
          if(malias3==3){m10=Node[m3].GetID1(); m11=Node[m3].GetID2();m12=Node[m3].GetID3();}


        int kount=0;
        if(m1==n1 || m1==n2 || m1==n3)kount++;
        if(m2==n1 || m2==n2 || m2==n3)kount++;
        if(m3==n1 || m3==n2 || m3==n3)kount++;
        if(m4==n1 || m4==n2 || m4==n3)kount++;
        if(m5==n1 || m5==n2 || m5==n3)kount++;
        if(m6==n1 || m6==n2 || m6==n3)kount++;
        if(m7==n1 || m7==n2 || m7==n3)kount++;
        if(m8==n1 || m8==n2 || m8==n3)kount++;
        if(m9==n1 || m9==n2 || m9==n3)kount++;
        if(m10==n1 || m10==n2 || m10==n3)kount++;
        if(m11==n1 || m11==n2 || m11==n3)kount++;
        if(m12==n1 || m12==n2 || m12==n3)kount++;

        if(kount !=3 ){
           cout << "Houston, we have a problem...\n";
           cout << "No match for Tetrahedron " << i << "  face 3\n  kount=" << kount;
           exit(0);
         }
         } //endif for neighbour exists
       //face 4
        m1=(Tets+i)->Get1(); m2=(Tets+i)->Get2(); m3=(Tets+i)->Get3();
        neighb=(Tets+i)->GetN4();

        if(neighb){
          iface=(Tets+i)->GetC4();
          if(iface==1){
          n1=(Tets+*neighb)->Get2(); n2=(Tets+*neighb)->Get3(); n3=(Tets+*neighb)->Get4();}
          if(iface==2){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get3(); n3=(Tets+*neighb)->Get4();}
          if(iface==3){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get2(); n3=(Tets+*neighb)->Get4();}
          if(iface==4){
          n1=(Tets+*neighb)->Get1(); n2=(Tets+*neighb)->Get2(); n3=(Tets+*neighb)->Get3();}

          malias1=Node[m1].GetAlias(); malias2=Node[m2].GetAlias(); malias3=Node[m3].GetAlias();

          m4=-1,m5=-1,m6=-1,m7=-1,m8=-1,m9=-1,m10=-1,m11=-1,m12=-1;
          if(malias1==1)m4=Node[m1].GetID1();
          if(malias1==2){m4=Node[m1].GetID1(); m5=Node[m1].GetID2();}
          if(malias1==3){m4=Node[m1].GetID1(); m5=Node[m1].GetID2();m6=Node[m1].GetID3();}
          if(malias2==1)m7=Node[m2].GetID1();
          if(malias2==2){m7=Node[m2].GetID1(); m8=Node[m2].GetID2();}
          if(malias2==3){m7=Node[m2].GetID1(); m8=Node[m2].GetID2();m9=Node[m2].GetID3();}
          if(malias3==1)m10=Node[m3].GetID1();
          if(malias3==2){m10=Node[m3].GetID1(); m11=Node[m3].GetID2();}
          if(malias3==3){m10=Node[m3].GetID1(); m11=Node[m3].GetID2();m12=Node[m3].GetID3();}


        int kount=0;
        if(m1==n1 || m1==n2 || m1==n3)kount++;
        if(m2==n1 || m2==n2 || m2==n3)kount++;
        if(m3==n1 || m3==n2 || m3==n3)kount++;
        if(m4==n1 || m4==n2 || m4==n3)kount++;
        if(m5==n1 || m5==n2 || m5==n3)kount++;
        if(m6==n1 || m6==n2 || m6==n3)kount++;
        if(m7==n1 || m7==n2 || m7==n3)kount++;
        if(m8==n1 || m8==n2 || m8==n3)kount++;
        if(m9==n1 || m9==n2 || m9==n3)kount++;
        if(m10==n1 || m10==n2 || m10==n3)kount++;
        if(m11==n1 || m11==n2 || m11==n3)kount++;
        if(m12==n1 || m12==n2 || m12==n3)kount++;

        if(kount !=3 ){
           cout << "Houston, we have a problem...\n";
           cout << "No match for Tetrahedron " << i << "  face 4  kount=" << kount << endl;
           exit(0);
         }
         } //endif for neighbour exists
     }

     //THIS LOOP TESTS THAT THE Node's MyTet contains the node
     int test_tet;
     for(int i=0; i <inodes; i++){
         test_tet=Node[i].GetMyTet();
         if(test_tet==-1){
             cout << "Node has not been set\n"; exit(0);
         }
         if(i != (Tets+test_tet)->Get1() && i !=(Tets+test_tet)->Get2()
          &&i != (Tets+test_tet)->Get3() && i !=(Tets+test_tet)->Get4()){
                  cout <<"Node "<< i << "  NOT IN TET "<< test_tet << endl;
                  cout << (Tets+test_tet)->Get1() << " " 
                       << (Tets+test_tet)->Get2() << " " 
                       << (Tets+test_tet)->Get3() << " " 
                       << (Tets+test_tet)->Get4() << endl; 
                  exit(0);}
     }


     ofstream  file_out;
     file_out.open("basicCube.dat");
     file_out << inodes << " " << itets << endl;
     file_out << periodicx <<" " << periodicy << " " << periodicz << endl;
     bool periodic;
     char charstop;
     if(periodicx || periodicy || periodicz)periodic=true;
     //program must store nodes in array with SAME ivalues 
     //or do something to get back the aliasing numbers

     for(int i=0; i<inodes; i++){
        file_out <<NodeV[i].GetX() << " " << NodeV[i].GetY() << "  " <<NodeV[i].GetZ();
        file_out << " " << Node[i].GetMyTet() <<" " << (int)Node[i].GetFreedom() << "  ";
  //      cout << NodeV[i].GetX() << " " << NodeV[i].GetY() << "  " <<NodeV[i].GetZ();
   //     cout << " " << Node[i].GetMyTet() <<" " << (int)Node[i].GetFreedom() << endl;
        if(periodic){
        charstop=Node[i].GetAlias();
        file_out << "  " << (int)charstop;
        int* TempID=Node[i].GetID();
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
     file_out.close();



 while(!quitit){
        
       while(SDL_PollEvent(&event)){

          switch(event.type){
               case SDL_QUIT:
                 quitit=true;
                 break;
                 case SDL_MOUSEBUTTONDOWN:
		    if(!mousedown)
			    firstmousedown=true;
		    else
		            firstmousedown=false;
                    mousedown=true;
                 break;
                 case SDL_MOUSEBUTTONUP:
                    mousedown=false;   //mousedown remains true untill mouse up
                 break;

                 case SDL_MOUSEMOTION:
                  if(mousedown){
                         if(MouseOn)
				 if(tethered || staked)
					Camera1.MouseView();
					else
					Camera1.MouseLookAt();

		  }  //MouseView: change view direction
                  else{
                         if(MouseOn)
				 if(tethered || staked)
					Camera1.MouseLookAt();
					else
					Camera1.MouseView();
		  }  //MouseLookat: change point from where camera "looks at" scene
                 break;  


               case SDL_KEYDOWN:
                   whatkey=&event.key.keysym;
                   HandleKeyPress(whatkey);
                   break;
               case SDL_KEYUP:
                   whatkey=&event.key.keysym;
                   HandleKeyRelease(whatkey);
               default:
                 break;
                     } // end of case
                } //end of inner loop
       /************************************************************/
              CheckMove(Camera1);
		    if(a_Pressed){
			    speed=speed+0.1;
			    angspeed=angspeed+0.001;
			    if(speed > 60)speed=60;
			    if(angspeed  > 0.15)angspeed=0.15;
		    }
		    if(z_Pressed){
			    speed=speed-0.1;
			    angspeed=angspeed-0.001;
			    if(speed  < 0)speed=0;
			    if(angspeed  < 0)angspeed=0;
		    }

              RenderScene(Camera1); 
	      //(does picking in DrawLightPos etc)
            } //end of outer loop

}
void RenderScene(CCam & Camera1)
{
   glClearColor(RedM[0][0],GreenM[0][0],BlueM[0][0] ,AlphaM[0][0]);
	float fogColor[4]= 
	{RedM[0][0],GreenM[0][0],BlueM[0][0],AlphaM[0][0]};
	glFogfv(GL_FOG_COLOR, fogColor);
   //background colour initialised

       glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
       glLoadIdentity();

       int ix,iz;

       //
       //camera  pos      view     up vector
       if(exwhyzed){
       gluLookAt(
        Camera1.CamPos.GetX(),   Camera1.CamPos.GetY(),  Camera1.CamPos.GetZ(),
        Camera1.CamView.GetX(), Camera1.CamView.GetY(), Camera1.CamView.GetZ(),
        Camera1.jay.GetX(),   Camera1.jay.GetY(),   Camera1.jay.GetZ());   
        }
       if(boom || aeroplane){
        gluLookAt(
        Camera1.CamPos.GetX(),   Camera1.CamPos.GetY(),  Camera1.CamPos.GetZ(),
        Camera1.CamView.GetX(), Camera1.CamView.GetY(), Camera1.CamView.GetZ(),
        Camera1.jprime.GetX(),   Camera1.jprime.GetY(),   Camera1.jprime.GetZ());   
        }


      glLineWidth(0.1);


      if(LIGHTS)
	      glEnable(GL_LIGHTING);
      else
	      glDisable(GL_LIGHTING);
     if(LIGHTS){

     glEnable(GL_BLEND);

     for(int il=0; il<ilights; il++){

     CosZen=cos(Zen[il]/convert);
     SinZen=sin(Zen[il]/convert);
     SinAz=sin(Az[il]/convert);
     CosAz=cos(Az[il]/convert);

     //check initial for Pesky openGL coordinates too
     gLightPosition[0]=Rho[il]*SinZen*CosAz;
     gLightPosition[2]=-Rho[il]*SinZen*SinAz;
     gLightPosition[1]=Rho[il]*CosZen;
     if(Rho[il] >  L_Inf)
	     gLightPosition[3]=0.0; // at infinity if =0 
     else   
             gLightPosition[3]=1.0;   // xyzw, pos= x/w,y/w,z/w

     float ambient[4]={RedL[il][0], GreenL[il][0], BlueL[il][0], AlphaL[il][0]}; 
     float diffuse[4]={RedL[il][1], GreenL[il][1], BlueL[il][1], AlphaL[il][1]}; 
     float specular[4]={RedL[il][2], GreenL[il][2], BlueL[il][2], AlphaL[il][2]}; 
     glLightfv(MYLIGHTS[il],GL_AMBIENT,ambient);
     glLightfv(MYLIGHTS[il],GL_DIFFUSE,diffuse);
     glLightfv(MYLIGHTS[il],GL_SPECULAR,specular);
     glLightfv(MYLIGHTS[il],GL_POSITION,gLightPosition);
      }
      }

      if(!helpscreen && drawback){
	      glDisable(GL_TEXTURE_2D); //Otherwise Colors get messed
	      glPointSize(2.0);
	      glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	      glEnable(GL_POINT_SMOOTH);
	      if(Gouraud){
	      glShadeModel(GL_SMOOTH);
	      }
	      else
	      {
	      glShadeModel(GL_FLAT);
	      }
	      bool drawscene=true;     //by last call to glBindTexture
	      DrawScene(drawscene);
      }// endif for !helpscreen

      glEnable(GL_TEXTURE_2D);
      if(helpscreen){

      glDisable(GL_DEPTH_TEST);
      glDisable(GL_LIGHTING);
	      //left top right bottom
	      //Matrix is diagonal
	      //  2/(right-left), 2/(top-bottom), -2/(far-near)
	      //  call in OrthMode is to glOrtho with near=0, far=1
	      //  Args are  left, top, right, bottom

      OrthoMode(-1, 1, 1, -1);
      glColor3ub(255,255,255);
      glBindTexture(GL_TEXTURE_2D,gl_Texture[0]);
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glBegin(GL_QUADS);
             // 0,0 is screen centre
             // -1,-1 is screen bottom left
	      glTexCoord2f(0.0,1.0);
	      glVertex2f(-1.0, 1.0); 
	      glTexCoord2f(0.0,0.0);
	      glVertex2f(-1.0, -1.0); // Bottom Left
	      glTexCoord2f(1.0,0.0);
	      glVertex2f(1.0, -1.0); // Bottom right
	      glTexCoord2f(1.0,1.0);
	      glVertex2f(1.0, 1.0); // Top right
      glEnd();

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_LIGHTING);
      PerspectiveMode();

       }  //endif for helpscreen

      if(lightpos){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	          DrawLightPos(drawbox);  //draw the box
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;
	      DrawLightPos(drawbox);  //use pickmatrix instead
	       }
      if(lightcol){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	          DrawLightCol(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;   //pickmatrix
	      DrawLightCol(drawbox);
	       }
      if(matcol){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	          DrawMatCol(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;   //pickmatrix
	      DrawMatCol(drawbox);
	       }
      if(logicbox){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	          DrawLogicBox(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;   //pickmatrix
	      DrawLogicBox(drawbox);
	       }

	      SDL_GL_SwapBuffers();
}

#include "../../XFiles/Init.cpp"

void DrawScene(bool drawscene)
{
      int viewport[4];
      SDL_GetMouseState(&mousex, &mousey);

      double xvals[5],yvals[5],zvals[5];
      double ex, why, zed;
      RayMeshTet *DrawTet;
      bool EvenTet;
      MeshNode *N1, *N2, *N3, *N4;
      int n1,n2,n3,n4;

      float x1,y1,z1;
      float x2,y2,z2;
      float x3,y3,z3;
      float x4,y4,z4;

      D3Dvec *Vec1, *Vec2, *Vec3, *Vec4;
      double *V1, *V2, *V3, *V4;




      if(drawlines && drawscene){
 
      int   matl=1;

	     if(LIGHTS){
      float mat_amb[4]={RedM[1][0], GreenM[1][0],BlueM[1][0],
		                AlphaM[1][0] };
      float mat_diff[4]={RedM[1][1], GreenM[1][1],BlueM[1][1],
		                AlphaM[1][1] };
      float mat_spec[4]={RedM[1][2], GreenM[1][2],BlueM[1][2],
		                AlphaM[1][2] };
      float shine[]={ShineM[1][0]};
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	     }
	     else
	     {
	glColor3ub((int)(255*RedM[1][1]),(int)(255*GreenM[1][1]),(int)(255*BlueM[1][1]));
	}  //endif for LIGHTS

      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);


       for(int i=0; i<tetstotal; i++){



       DrawTet=(Tets+i);

       n1=DrawTet->Get1();
       n2=DrawTet->Get2();
       n3=DrawTet->Get3();
       n4=DrawTet->Get4();

       Vec1=(Node+n1)->GetVec();
       Vec2=(Node+n2)->GetVec();
       Vec3=(Node+n3)->GetVec();
       Vec4=(Node+n4)->GetVec();

       V1=Vec1->GetV();
       V2=Vec2->GetV();
       V3=Vec3->GetV();
       V4=Vec4->GetV();

       x1=(float)*(V1);
       y1=(float)*(V1+1);
       z1=(float)*(V1+2);

       x2=(float)*(V2);
       y2=(float)*(V2+1);
       z2=(float)*(V2+2);

       x3=(float)*(V3);
       y3=(float)*(V3+1);
       z3=(float)*(V3+2);

       x4=(float)*(V4);
       y4=(float)*(V4+1);
       z4=(float)*(V4+2);

       x1=x1*100.0;y1=y1*100.0; z1=z1*100.0;
       x2=x2*100.0;y2=y2*100.0; z2=z2*100.0;
       x3=x3*100.0;y3=y3*100.0; z3=z3*100.0;
       x4=x4*100.0;y4=y4*100.0; z4=z4*100.0;
/*
       cout << "tet=" <<  i << "  nodes=" << n1 << " " << n2 <<" " << n3 << " " << n4 << endl;
       cout <<"orig=" << x1 << " " << y1 << "  " << z1 << endl;
       cout <<"  a=(" << x2-x1 << " " << y2-y1 << " " << z2-z1 << ")" << endl;
       cout <<"  b=(" << x3-x1 << " " << y3-y1 << " " << z3-z1 << ")" << endl;
       cout <<"  c=(" << x4-x1 << " " << y4-y1 << " " << z4-z1 << ")" << endl;
*/
       glBegin(GL_TRIANGLES);
          glVertex3f(x1,z1,-y1);
          glVertex3f(x2,z2,-y2);
          glVertex3f(x3,z3,-y3);
       glEnd();
       glBegin(GL_TRIANGLES);
          glVertex3f(x1,z1,-y1);
          glVertex3f(x2,z2,-y2);
          glVertex3f(x4,z4,-y4);
       glEnd();
       glBegin(GL_TRIANGLES);
          glVertex3f(x1,z1,-y1);
          glVertex3f(x3,z3,-y3);
          glVertex3f(x4,z4,-y4);
       glEnd();
       glBegin(GL_TRIANGLES);
          glVertex3f(x2,z2,-y2);
          glVertex3f(x3,z3,-y3);
          glVertex3f(x4,z4,-y4);
       glEnd();

            }




    } // endif lines and drawscene


}

