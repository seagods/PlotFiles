//unless followed by glGetMaterial! 
//-------------------------------------------------------------------------------
// Copyright 2009 Christopher Godsalve.
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
#include "PlotVol.h"
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
#include "../../XFiles/DrawFlipperBox.h"
#include "../../XFiles/DrawWaxis.h"
#include "../../XFiles/DrawTextMove2.h"


double W=50000;     //global mesh dimensions OpenGL
double H=50000;
double D=50000;
double xx1=-W;
double xx2=W;
double yy1=-H;
double yy2=H;
double zz1=-D;
double zz2=D;

double Tol;

MeshNode *Node; RayMeshTet *Tets;

bool**  Done;  //has a tetrahedron been done?
int** tetcuts;  // trinodes in each tetrahedron
char**  tettrinodes;  // trinodes are between which tetraheron nodes?
int id;
const int idmax=8;


int currentsurf, currentid; //bit crazy, but we make these global

int inodes,itets,tetstart;

int current_depth;
int maxdepth=5000;

void EventLoop()
{
 CCam Camera1;
 bool quitit=false;
 SDL_Event event;
 SDL_MouseMotionEvent event2; //Not yet used
 SDL_keysym  *whatkey;

 bool verbose=false;

 //LIGHTS=false;  //don't need it

 if(hidemousecursor)SDL_ShowCursor(0);
      if(LIGHTS){
	      speed=10.0;
	      angspeed=0.05;}
      else
      {
	      speed=5.0;
	      angspeed=0.005;}


    if(staked){
	    Camera1.SetPos(0.0,0.0,0.0);
	    Camera1.SetView(0.0,0.0,1000.0);
    }

    shift1=0.0;  //  x leftright
    shift2=0.0;   // in/out
    shift3=0.0;   // z up/down
    shift4=0.0;    //  x in/out
    shift5=0.0;    //  y left/right
    shift6=0.0;    //  radial+-
    shift7=0.0; shift8=0.0; shift9=0.0; shift10=0.0; shift11=0.0; shift12=0.0;


    int pointsize=45; // for camera coordinates in perspective mode
 
    font1=new OGLFT::Filled("/usr/share/fonts/times/Timeg.ttf",pointsize);
     if(font1==0 || !font1->isValid()){
        cout << "Font1 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 1 is fine!" << endl;  }

     font2=new OGLFT::Filled("/usr/share/fonts/times/Timegi.ttf",pointsize);
     if(font2==0 || !font2->isValid()){
        cout << "Font2 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 2 is fine!" << endl;  }

     font3=new OGLFT::Filled("/usr/share/fonts/times/Timegbd.ttf",pointsize);
     if(font3==0 || !font3->isValid()){
        cout << "Font3 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 3 is fine!" << endl;  }

     font4=new OGLFT::Filled("/usr/share/fonts/times/Timegibd.ttf",pointsize);
     if(font4==0 || !font4->isValid()){
        cout << "Font4 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 4 is fine!" << endl;  }

     font5=new OGLFT::Filled("/usr/share/fonts/Fonts-Linux/slgrrg__.ttf",pointsize);
     if(font5==0 || !font5->isValid()){
        cout << "Font5 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 5 is fine!" << endl;  }

     font6=new OGLFT::Filled("/usr/share/fonts/texcm/cmex10.ttf",pointsize);
     if(font6==0 || !font6->isValid()){
        cout << "Font6 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 6 is fine!" << endl;  }

     font7=new OGLFT::Filled("/usr/share/fonts/texcm/cmmi10.ttf",pointsize);
     if(font7==0 || !font7->isValid()){
        cout << "Font7 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 7 is fine!" << endl;  }

     font8=new OGLFT::Filled("/usr/share/fonts/texcm/cmr10.ttf",pointsize);
     if(font8==0 || !font8->isValid()){
        cout << "Font8 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 8 is fine!" << endl;  }

     font9=new OGLFT::Filled("/usr/share/fonts/texcm/cmsy10.ttf",pointsize);
     if(font9==0 || !font9->isValid()){
        cout << "Font9 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 9 is fine!" << endl;  }
     
     //rasterised bitmap font
     pointsize=12;
     font10=new OGLFT::Monochrome("/usr/share/fonts/times/Timeg.ttf",pointsize);

     if(font10==0 || !font10->isValid()){
        cout << "Font10 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 10 is fine!" << endl;  }
    
     pointsize=6;  // for orthomode with scalefac 100.
     font11=new OGLFT::Filled("/usr/share/fonts/times/Timeg.ttf",pointsize);
     if(font11==0 || !font11->isValid()){
        cout << "Font11 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 11 is fine!" << endl;  }

     pointsize=60;   //  other sizes for perspective mode and cam coord system
     font12=new OGLFT::Filled("/usr/share/fonts/times/Timeg.ttf",pointsize);
     if(font12==0 || !font12->isValid()){
        cout << "Font12 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 12 is fine!" << endl;  }

     pointsize=75;
     font13=new OGLFT::Filled("/usr/share/fonts/times/Timeg.ttf",pointsize);
     if(font13==0 || !font13->isValid()){
        cout << "Font13 Failed" << endl;
        exit(1);
     }
     else{
        cout << "Font 13 is fine!" << endl;  }


     font1->setForegroundColor(0.0, 0.0, 0.0);
     font2->setForegroundColor(0.0, 0.0, 0.0);
     font3->setForegroundColor(0.0, 0.0, 0.0);
     font4->setForegroundColor(0.0, 0.0, 0.0);
     font5->setForegroundColor(0.0, 0.0, 0.0);
     font6->setForegroundColor(0.0, 0.0, 0.0);
     font7->setForegroundColor(0.0, 0.0, 0.0);
     font8->setForegroundColor(0.0, 0.0, 0.0);
     font9->setForegroundColor(0.0, 0.0, 0.0);
     font10->setForegroundColor(0.0, 0.0, 0.0);
     font11->setForegroundColor(0.0, 0.0, 0.0);
     font12->setForegroundColor(0.0, 0.0, 0.0);
     font13->setForegroundColor(0.0, 0.0, 0.0);


     glPixelStorei( GL_UNPACK_ALIGNMENT, 1);


  // testplot=13927;
   string filename;
   ostringstream oss;
   if(arg_count>=2){
        oss << *(arg_list+1);
        filename=oss.str();
        cout << filename << endl;
   }
   else{
      filename="VolData.dat";
   }
    
   testplot=-1;
   fstream file_in;
   file_in.open(filename.c_str(),ios::in);

   if(!file_in){
       cout << "Input file does not exist!\n";
       exit(1);}

    //This code does NOT want periodic BCs!

   bool periodicx,periodicy,periodicz,periodic;

   file_in >> inodes >> itets;
   file_in >> periodicx >> periodicy >> periodicz;

   cout <<"We have " << inodes << " nodes and " << itets << " tetrahedra "<< endl;
   cout <<"periodics x y and z are " << periodicx << " " << periodicy << " " << periodicz << endl; 

   double xval, yval, zval;
   int ifree,mytet;
   int n_aliases;
   int alias[3];

   D3Dvec* NodeVec; // Nodes and Tets are global
   NodeVec=new D3Dvec[inodes]; Tets=new RayMeshTet[itets];
   Node=new MeshNode[inodes];
   Done=new bool*[itets];
   tetcuts=new int*[itets];
   tettrinodes=new char*[itets];

   //weird to use calloc I know, but I just thought I'd try it this way
   //remember to used free on Done[i] and delete[] on Done;
   for(int i=0; i<itets; i++){
       Done[i]=(bool*)calloc(idmax,sizeof(bool));
      // or  Done[itets]=new bool[idmax];
     // for a particular tet, keep up to 4 trinode numbers
       tetcuts[i]=(int*)calloc(4,sizeof(int)); 
     //  tetcuts[X][0] is between tet nodes tettrinodes[X][0] and tettrinodes[X}[1]
     //  tetcuts[X][1] is between tet nodes tettrinodes[X][2] and tettrinodes[X}[3]
       tettrinodes[i]=(char*)calloc(8,sizeof(char));
   }
   periodic=false;
   if(periodicx || periodicy || periodicz)periodic=true;

    xmin=1e300; xmax=-1e300; ymin=1e300; ymax=-1e300; 
    zmin=1e300; zmax=-1e300; wmin=1e300; wmax=-1e300;

   if(periodic){  //leave this code block, but we bomb out if it is periodic
      
      for(int i=0; i< inodes; i++){
      file_in >> xval >> yval >> zval >> mytet >> ifree >> n_aliases;
       if(xval<xmin)xmin=xval;  //looks daft, but isn't necessarily a rectangular block
       if(yval<ymin)ymin=yval;
       if(zval<zmin)zmin=zval;

       if(xval>xmax)xmax=xval;
       if(yval>ymax)ymax=yval;
       if(zval>zmax)zmax=zval;


      Node[i].SetPos(xval,yval,zval,NodeVec+i); 
      Node[i].SetMyTet(mytet);
      Node[i].SetFreedom(ifree);
      for(int ia=0; ia<n_aliases; ia++){
          file_in >> alias[ia];
          }
      if(n_aliases==1)Node[i].SetID(alias[0]);
      if(n_aliases==2)Node[i].SetID(alias[0], alias[1]);
      if(n_aliases==3)Node[i].SetID(alias[0], alias[1], alias[2]);
      }
   }
   else
   {
      for(int i=0; i< inodes; i++){
      file_in >> xval >> yval >> zval >> mytet >> ifree;
       if(xval<xmin)xmin=xval;  //looks daft, but isn't necessarily a rectangular block
       if(yval<ymin)ymin=yval;
       if(zval<zmin)zmin=zval;

       if(xval>xmax)xmax=xval;
       if(yval>ymax)ymax=yval;
       if(zval>zmax)zmax=zval;
      Node[i].SetPos(xval,yval,zval,NodeVec+i); //meshnode holds Nodevec address only, it sets NodeVec to x,y,z
      Node[i].SetMyTet(mytet);
      Node[i].SetFreedom(ifree);
      }
   }
   if(periodic){
         //bomb out here
         cout << "PlotVol is not designed to handle periodic BC's " << endl;
         cout << "It needs pointers to null at the boundaries of the mesh " << endl;
         exit(1);
   }
   //now read in tetrahedra
    int i1,i2,i3,i4,j1,j2,j3,j4,c1,c2,c3,c4;
    for(int i=0; i<itets;i++){
       file_in >> i1 >> i2 >> i3 >> i4 >> j1 >> j2 >> j3 >> j4 >> c1 >> c2 >> c3 >> c4;
       Tets[i].SetTet(i1,i2,i3,i4,j1,j2,j3,j4,(char)c1, (char)c2, (char)c3, (char)c4);
    }

    wval=new double[inodes];

     for(int i=0; i < inodes; i++){
          file_in >> wval[i];
          if(wval[i]<wmin)wmin=wval[i];
          if(wval[i]>wmax)wmax=wval[i];
     }

     cout << "x min and max " << xmin << " " << xmax << endl;
     cout << "y min and max " << ymin << " " << ymax << endl;
     cout << "z min and max " << zmin << " " << zmax << endl;
     cout << "w min and max " << wmin << " " << wmax << endl;

    //now deal with xy axis labels for what x and y are and what are the units
    char xchar,ychar,zchar,wchar;
 //   int ixtext, ixunits, iytext, iyunits;
    int strlength;


    file_in >> ixtext >> ixunits;  //=1 if any text or any units
    if(ixtext==1 && ixunits==1)file_in >>   xtext >> xunits;
    if(ixtext==1 && ixunits==0)file_in >> xtext;
    file_in >> iytext >> iyunits;  //=1 if any text or any units
    if(iytext==1 && iyunits==1)file_in >>   ytext >> yunits;
    if(iytext==1 && iyunits==0)file_in >> ytext;
    file_in >> iztext >> izunits;  //=1 if any text or any units
    if(iztext==1 && izunits==1)file_in >>   ztext >> zunits;
    if(iztext==1 && izunits==0)file_in >> ztext;
    file_in >> iwtext >> iwunits;  //=1 if any text or any units
    if(iwtext==1 && iwunits==1)file_in >>   wtext >> wunits;
    if(iwtext==1 && iwunits==0)file_in >> wtext;


    //any intended spaces in the line of text in data.dat must be an ampersand
    //all ampersands are stripped out of the string.
    if(ixtext==1){
    strlength=xtext.length();
    for(int i=0; i<strlength; i++){
        xchar=xtext[i];
        if(xchar=='@')xtext.replace(i,1," ",1);
     }}
    if(ixunits==1){
    strlength=xunits.length();
    for(int i=0; i<strlength; i++){
        xchar=xunits[i];
        if(xchar=='@')xunits.replace(i,1," ",1);
     }}
    if(iytext==1){
    strlength=ytext.length();
    for(int i=0; i<strlength; i++){
        ychar=ytext[i];
        if(ychar=='@')ytext.replace(i,1," ",1);
     }}
    if(iyunits==1){
    strlength=yunits.length();
    for(int i=0; i<strlength; i++){
        ychar=yunits[i];
        if(ychar=='@')yunits.replace(i,1," ",1);
     }}

    if(iztext==1){
    strlength=ztext.length();
    for(int i=0; i<strlength; i++){
        zchar=ztext[i];
        if(zchar=='@')ztext.replace(i,1," ",1);
     }}
    if(izunits==1){
    strlength=zunits.length();
    for(int i=0; i<strlength; i++){
        zchar=zunits[i];
        if(zchar=='@')zunits.replace(i,1," ",1);
     }}

    if(iwtext==1){
    strlength=wtext.length();
    for(int i=0; i<strlength; i++){
        wchar=wtext[i];
        if(wchar=='@')wtext.replace(i,1," ",1);
     }}
    if(iwunits==1){
    strlength=wunits.length();
    for(int i=0; i<strlength; i++){
        wchar=wunits[i];
        if(wchar=='@')wunits.replace(i,1," ",1);
     }}



    cout << " x axis label in data.dat is " << xtext << endl;
    cout << " y axis label in data.dat is " << ytext << endl;
    cout << " z axis label in data.dat is " << ztext << endl;
    cout << " w axis label in data.dat is " << wtext << endl;
    cout << " x axis unit in data.dat is " << xunits << endl;
    cout << " y axis unit in data.dat is " << yunits << endl;
    cout << " z axis unit in data.dat is " << zunits << endl;
    cout << " w axis unit in data.dat is " << wunits << endl;

    xrange=xmax-xmin; yrange=ymax-ymin;
    zrange=zmax-zmin; wrange=wmax-wmin;
    Tol=fabs(wrange/1e6);
    if(fabs(xrange)<1e-42){
	    cout << "xrange too small, exiting " << endl;
	    exit(1);}
    if(fabs(yrange)<1e-42){
	    cout << "yrange too small, exiting " << endl;
	    exit(1);}
    if(fabs(zrange)<1e-42){
	    cout << "zrange too small, exiting " << endl;
	    exit(1);}
    if(fabs(wrange)<1e-42){
	    cout << "wrange too small, exiting " << endl;
	    exit(1);}


    xexp=floor(log10(xrange)); yexp=floor(log10(yrange));
    zexp=floor(log10(zrange)); wexp=floor(log10(wrange));
    xfact=pow(10.0,xexp); yfact=pow(10.0,yexp);
    zfact=pow(10.0,zexp); wfact=pow(10.0,wexp);
    xrange_scale=xrange/xfact; yrange_scale=yrange/yfact;
    zrange_scale=zrange/zfact; wrange_scale=wrange/wfact;

    //all the following  have been initialised false
    if(xmin >0.0)xmin_zero=true; if(ymin>0)ymin_zero=true;
    if(zmin>0)zmin_zero=true; if(wmin>0)wmin_zero=true;
    if(xmax >0.0)xmax_zero=true; if(ymax>0)ymax_zero=true;
    if(zmax>0)zmax_zero=true; if(wmax>0)wmax_zero=true;
    
    if(xmax >0.0 && xmin > 0.0)xboth=true; if(xmax <0.0 && xmin < 0.0)xboth=true; 
    if(ymax >0.0 && ymin > 0.0)yboth=true; if(ymax <0.0 && ymin < 0.0)yboth=true;
    if(zmax >0.0 && zmin > 0.0)zboth=true; if(zmax <0.0 && zmin < 0.0)zboth=true;
    if(wmax >0.0 && wmin > 0.0)wboth=true; if(wmax <0.0 && wmin < 0.0)wboth=true;


    cout << "xrange and xfact are " << xrange << "  " << xfact << endl;
    cout << "yrange and yfact are " << yrange << "  " << yfact << endl;
    cout << "zrange and zfact are " << zrange << "  " << zfact << endl;
    cout << "wrange and wfact are " << wrange << "  " << wfact << endl;

    if(xmin>0)xmin_zero=true; if(xmax>0)xmax_zero=true;
    if(ymin>0)ymin_zero=true; if(ymax>0)ymax_zero=true;
    if(zmax>0)zmax_zero=true; if(zmin>0)zmin_zero=true;
    if(wmax>0)wmax_zero=true; if(wmin>0)wmin_zero=true;

    if(xmin_zero==true && xmax_zero==true)xboth=true;
    if(xmin_zero==false && xmax_zero==false)xboth=true;

    if(ymin_zero==true && ymax_zero==true)yboth=true;
    if(ymin_zero==false && ymax_zero==false)yboth=true;

    if(zmin_zero==true && zmax_zero==true)zboth=true;
    if(zmin_zero==false && zmax_zero==false)zboth=true;

    if(wmin_zero==true && wmax_zero==true)wboth=true;
    if(wmin_zero==false && wmax_zero==false)wboth=true;


//  These are all initialised to -1000 in the header file;
    
    if(xmin>0)xminexp=floor(log10(xmin)); 
    if(xmin<0)xminexp=floor(log10(-xmin)); 

    if(ymin>0)yminexp=floor(log10(ymin));
    if(ymin<0)yminexp=floor(log10(-ymin));

    if(zmin>0)zminexp=floor(log10(zmin));
    if(zmin<0)zminexp=floor(log10(-zmin));

    if(wmin>0)wminexp=floor(log10(wmin));
    if(wmin<0)wminexp=floor(log10(-wmin));

    xminfact=pow(10.0,xminexp); yminfact=pow(10.0,yminexp);
    zminfact=pow(10.0,zminexp); wminfact=pow(10.0,wminexp);
    if(xminfact>0){xmin_scale=xmin/xminfact;}else{xmin_scale=xmin*1000000.0;}
    if(xminfact>0){ymin_scale=ymin/yminfact;}else{ymin_scale=ymin*1000000.0;}
    if(xminfact>0){zmin_scale=zmin/zminfact;}else{zmin_scale=zmin*1000000.0;}
    if(xminfact>0){wmin_scale=wmin/wminfact;}else{wmin_scale=wmin*1000000.0;}


    numbers_wxyz();

     ostringstream xmod;
      if(xtimesdiv){
       if(xexp<0){
        xmod << '*';  xmod << '1'; xmod << 'e'; xmod << '+';
        xmod << fabs(xexp);}
        else{
        xmod << '/';  xmod << '1'; xmod << 'e'; xmod << '+';
        xmod << fabs(xexp);}
        }
        else{xmod << ' ';}

        xtextmod=xmod.str();

      ostringstream ymod;
      if(ytimesdiv){
       if(yexp<0){
        ymod << '*';  ymod << '1'; ymod << 'e'; ymod << '+';
        ymod << fabs(yexp);}
        else{
        ymod << '/';  ymod << '1'; ymod << 'e'; ymod << '+';
        ymod << fabs(yexp);}
        }
        else{ymod << ' ';}

        ytextmod=ymod.str();

      ostringstream zmod;
      if(ztimesdiv){
       if(zexp<0){
        zmod << '*';  zmod << '1'; zmod << 'e'; zmod << '+';
        zmod << fabs(zexp);}
        else{
        zmod << '/';  zmod << '1'; zmod << 'e'; zmod << '+';
        zmod << fabs(zexp);}
        }
        else{zmod << ' ';}

        ztextmod=zmod.str();

      ostringstream wmod;
      if(wtimesdiv){
       if(wexp<0){
        wmod << '*';  wmod << '1'; wmod << 'e'; wmod << '+';
        wmod << fabs(wexp);}
        else{
        wmod << '/';  wmod << '1'; wmod << 'e'; wmod << '+';
        wmod << fabs(wexp);}
        }
        else{wmod << ' ';}

        wtextmod=wmod.str();

      if(ixtext==1){
      ostringstream xst;
      if(xaddsubtract){
         xst << '(';
         xst << xtext << xtextmod;
         if(xsubtract<0){
             xst << '+';
             xst << -xsubtract;
             }
         if(xsubtract>0){
           xst << '-';
           xst << xsubtract;
           }
          xst << ')';
      }
      if(!xaddsubtract)xst << xtext << xtextmod;

      if(ixunits==1){
        xst << ' ';
        xst << xunits;
      }

      xaxistext=xst.str();
      }  //endif ixtext==1


     if(iytext==1){
      ostringstream yst;
      if(yaddsubtract){
         yst << '(';
         yst << ytext << ytextmod;
         if(ysubtract<0){
             yst << '+';
             yst << -ysubtract;
             }
         if(ysubtract>0){
           yst << '-';
           yst << ysubtract;
           }
          yst << ')';
      }
      if(!yaddsubtract)yst << ytext << ytextmod;

      if(iyunits==1){
        yst << ' ';
        yst << yunits;
      }

      yaxistext=yst.str();
      } // endif y axis text

     if(iztext==1){
      ostringstream zst;
      if(zaddsubtract){
         zst << '(';
         zst << ztext << ztextmod;
         if(zsubtract<0){
             zst << '+';
             zst << -zsubtract;
             }
         if(zsubtract>0){
           zst << '-';
           zst << zsubtract;
           }
          zst << ')';
      }
      if(!zaddsubtract)zst << ztext << ztextmod;


      if(izunits==1){
        zst << ' ';
        zst << zunits;
      }
      zaxistext=zst.str();


      } // endif z axis text


     if(iwtext==1){
      ostringstream wst;
      if(waddsubtract){
         wst << '(';
         wst << wtext << wtextmod;
         if(wsubtract<0){
             wst << '+';
             wst << -wsubtract;
             }
         if(wsubtract>0){
           wst << '-';
           wst << wsubtract;
           }
          wst << ')';
      }
      if(!waddsubtract)wst << wtext << wtextmod;

      waxistext=wst.str();

      if(iwunits==1){
        wst << ' ';
        wst << wunits;
      }

      } // endif w axis text




    // In Plotsurf we stored line segment data for up to klinesmax
    // segments for each triangle (not stored in the triangle objects themselves
    // but stored "in parallel" to the triangles.

    //Here, we take an entirely different approach. We shall have a vector 
    //of lists of triangles and quadrangles for each contour level.

    //We have one function, and we find a the first tetrahedron that has an 
    //intersection with the iso value worked out in numbers_wxyz. This
    //gives us the first triangle in the list. We then "grow" the isosurface
    //from that tetrahedron. Clearly, there can be many isosurfaces for the same
    //value of wc. So, for each wc, we have a list of triangle lists and a list
    //of quadrangle lists.

    //In Plotsurf, we had a contour at all the minor tickmark positions,
    //Here we only have isosurfaces at the major tickmark values

    // to start off, we assume waddsubtract=0;

    //NOW, we use the std::vector standard C++ vector template
    // and add new vectors to IsoVecs as they come in.

    //Note, as in Plotsurf, we have linear interpolation across
    //the nodes, so there cannot be two iso

     newvecs=0;  // the number of new vectors in total 
                     //over all isosurfaces for all levels of wc
     newtris=0;  //Total number of all triangles over all isosurfs

     //edge 1 = 1-2, edge 2 = 1-3, edge 3= 1-4, edge 4 = 2-3, edge 5 = 2-4, edge 6 = 3-4

//   Cycle through wc values
     double wc;

     
     flippit=new bool*[iwnumb];
     idtotal=new int[iwnumb];
     wred=new double[iwnumb];
     wgreen=new double[iwnumb];
     wblue=new double[iwnumb];
     double wcol;
     for(int i=0; i<iwnumb; i++){
          wcol=(wnumbers[i]-wmin)/wrange;
          wcol=(wnumbers[i]-wnumbers[0])/(wnumbers[iwnumb]-wnumbers[0]);
          if(wcol<.5){
             wred[i]=1.0; wgreen[i]=2*wcol; wblue[i]=0.0;
             }
             else{

             wred[i]=2*(1.0-wcol); 
             if(wcol <0.7){
             wgreen[i]=1.0;}
             else{
             wgreen[i]=1.0-(wcol-0.7)/0.3;}             
             wblue[i]= 2.0*(wcol-0.5);
            }
            //  cout << wred[i]+wgreen[i]+wblue[i] << endl;
      }

    // globcount=0;

    
     for(int isurfs=0; isurfs<iwnumb; isurfs++){
         cout << isurfs << " " << wnumbers[isurfs] << endl;
         testsurf=isurfs;
         flippit[isurfs]=new bool[idmax];
         for(int k=0;k<idmax;k++){
               flippit[isurfs][k]=false;
          }
          idtotal[isurfs]=0;

         wc=wnumbers[isurfs];

         int itri1, itri2, itri3;  //new triangle node numbers

         int icut1, icut2, ifacecut;
         //xScale etc all global
         xScale=(xhigh-xlow)/xrange;yScale=(yhigh-ylow)/yrange;zScale=(zhigh-zlow)/zrange;

         // NewVec pointer, NewTri Pointer, and their iterators are global

         // print a message if the vector is initially empty
         if(IsoVecs.empty() )
         {
         //    cout << endl << "Iso Surface Vectors are empty at start" << endl;
          }

         for(int i=0; i<itets;i++){
            for(int j=0;j<idmax;j++){
             Done[i][j]=false; 
             }
              }

         for(int i=0; i<itets;i++){
            for(int j=0;j<4;j++){
               tetcuts[i][j]=-1;}}

         for(int i=0; i<itets;i++){
            for(int j=0;j<8;j++){
               tettrinodes[i][j]=-1;}}
         int ia1=-1,ia2=-1,ib1=-1,ib2=-1;  //only dummy values on first call

         int iret;
         bool dunnit;
         id=0;


         for(int it=0; it<itets; it++){
      //   for(int it=0; it<637; it++){
       //
        //        cout << it << endl;
                icut1=-1; icut2=-1; ifacecut=-1;
                currentsurf=isurfs;  //these are global as well as id
                currentid=id;
                dunnit=false;
                for(int k=0; k<id; k++){
                   if(Done[it][k]){
                         dunnit=true; }}
                if(!dunnit){
                current_depth=0;
                iret=SurfGrow(it, icut1, icut2, ifacecut, wc, ia1, ia2, ib1, ib2);
                if(iret==0){
                cout << "called surfgrow from main with it=" <<it
                     <<"  wc=" <<wc << " id=" << id << " newtris=" << newtris 
                     << "  newvecs=" << newvecs <<  endl;
               // exit(10);
                id++;  //new surface for this id
                idtotal[isurfs]=id;
                cout << "idtotal is " << idtotal[isurfs] << endl;
                if(id==idmax){
                     cout << "Run out of contours! increase idmax" <<endl; exit(1);}}
                }   //endif !dunnit
         }   //loop over tets
     }  //loop over isurfs (wc)


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
		    if(b_Pressed){
                         if(blendon){
                            blendon=false;}
                          else{
                            blendon=true;}
                            b_Pressed=false;
		    }

              RenderScene(Camera1); 
	      //(does picking in DrawLightPos etc)
            } //end of outer loop
            delete[] NodeVec; NodeVec=NULL;
            delete[] Tets;  Tets=NULL;
            delete[] Node; Node=NULL;
            for(int i=0; i<itets; i++){
               free(Done[i]); Done[i]=NULL; 
               free(tettrinodes[i]); tettrinodes[i]=NULL; 
               free(tetcuts[i]); tetcuts[i]=NULL; }
            delete[] Done;  Done=NULL;
            delete[] tetcuts; tetcuts=NULL;
            delete[] tettrinodes; tettrinodes=NULL;
            delete[] wval; wval=NULL;
            for(int i=0; i<iwnumb; i++){
               delete[] flippit[i];   flippit[i]=NULL;}
            delete[] flippit; flippit=NULL;
            delete[] idtotal;  idtotal=NULL;
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

     if(blendon)glEnable(GL_BLEND);

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
	      DrawScene(Camera1, drawscene);
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

      if(legendplot){
              LIGHTS=false;
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	          DrawWaxis(drawbox);  //draw the box
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;
	      DrawWaxis(drawbox);  //use pickmatrix instead
              LIGHTS=true;
	       }

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

     if(movetext){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	          DrawTextMove2(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;   //pickmatrix
	      DrawTextMove2(drawbox);
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
      if(flipperbox){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	          DrawFlipperBox(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;   //pickmatrix
	      DrawFlipperBox(drawbox);
	       }


	      SDL_GL_SwapBuffers();
}

#include "../../XFiles/Init.cpp"

void DrawScene(CCam & Camera1, bool drawscene)
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

      float shine=100.0;
      int matl=3;

      D3Dvec *Vec1, *Vec2, *Vec3, *Vec4;
      double *V1, *V2, *V3, *V4;
      int trilength, wsurflength, idlength,tritetlength;
      trilength=IsoTris.size();
      wsurflength=wclev.size();
      idlength=idlev.size();
      tritetlength=tritetvec.size();
      Triangle* TempTri;
      float gotmaterial[4];
      float mat_amb[4], mat_spec[4], mat_diff[4];

      drawlines=false;
      if(drawlines && drawscene){
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	     if(LIGHTS){
      float mat_amb[4]={RedM[matl][0], GreenM[matl][0],BlueM[matl][0],
		                AlphaM[matl][0] };
      float mat_diff[4]={RedM[matl][1], GreenM[matl][1],BlueM[matl][1],
		                AlphaM[matl][1] };
      float mat_spec[4]={RedM[matl][2], GreenM[matl][2],BlueM[matl][2],
		                AlphaM[2][2] };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
      glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	     }
	     else
	     {
	glColor3ub((int)(255*RedM[matl][1]),(int)(255*GreenM[matl][1]),(int)(255*BlueM[matl][1]));
	}  //endif for LIGHTS
       for(int i=0; i<itets; i++){
       DrawTet=(Tets+i);

       n1=DrawTet->Get1(); n2=DrawTet->Get2();
       n3=DrawTet->Get3(); n4=DrawTet->Get4();

       Vec1=(Node+n1)->GetVec(); Vec2=(Node+n2)->GetVec();
       Vec3=(Node+n3)->GetVec(); Vec4=(Node+n4)->GetVec();

       V1=Vec1->GetV();  V2=Vec2->GetV(); V3=Vec3->GetV(); V4=Vec4->GetV();

       x1=(float)*(V1); y1=(float)*(V1+1); z1=(float)*(V1+2);
       x2=(float)*(V2); y2=(float)*(V2+1); z2=(float)*(V2+2);
       x3=(float)*(V3); y3=(float)*(V3+1); z3=(float)*(V3+2);
       x4=(float)*(V4); y4=(float)*(V4+1); z4=(float)*(V4+2);

       x1=xlow+(x1-xmin)*xScale;x2=xlow+(x2-xmin)*xScale;
       x3=xlow+(x3-xmin)*xScale;x4=xlow+(x4-xmin)*xScale;
       y1=ylow+(y1-xmin)*yScale;y2=ylow+(y2-xmin)*yScale;
       y3=ylow+(y3-xmin)*yScale;y4=ylow+(y4-xmin)*yScale;
       z1=zlow+(z1-xmin)*zScale;z2=zlow+(z2-xmin)*zScale;
       z3=zlow+(z3-xmin)*zScale;z4=zlow+(z4-xmin)*zScale;
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

            }  // end loop over all tets
       }  //endif drawlines and drawscene

         if(drawscene){
          //  draw triangles newtris++
          TriIter=IsoTris.begin();  //TriIter is a pointer to the content of the vector
                                    //In this case *TriIter is a pointer to a triangle
          TriIter=IsoTris.end();    // The end of the vector is NULL;
          //do it this way here, but will access by IsoTris.at(i) in a "normal" loop
         //  for(TriIter=IsoTris.begin(); TriIter != IsoTris.end(); TriIter++){
         // }
         //
         int oldmatl=-1;
         D3Dvec v1,v2,Normal;
          for(int i=0; i< trilength;  i++){
        //  for(int i=0; i< 1628;  i++){
          //  cout << "isotri=" << i << endl;
            TempTri=IsoTris.at(i);
            n1=TempTri->Get1(); n2=TempTri->Get2(); n3=TempTri->Get3();
            x1=(IsoVecs.at(n1))->GetX();y1=(IsoVecs.at(n1))->GetY();z1=(IsoVecs.at(n1))->GetZ();
            x2=(IsoVecs.at(n2))->GetX();y2=(IsoVecs.at(n2))->GetY();z2=(IsoVecs.at(n2))->GetZ();
            x3=(IsoVecs.at(n3))->GetX();y3=(IsoVecs.at(n3))->GetY();z3=(IsoVecs.at(n3))->GetZ();
            matl=wclev.at(i);
         /*
                  cout << i << " " << matl <<  "  " 
                  << wred[matl] << " " <<  wgreen[matl] << " " << wblue[matl]
                  << "  " <<  LIGHTS << endl;
          */
	    if(LIGHTS){
            v1.SetVec(x2-x1,y2-y1,z2-z1);
            v2.SetVec(x3-x1,y3-y1,z3-z1);
            if(flippit[wclev.at(i)][idlev.at(i)]){
            Normal=v2*v1;}
            else{
            Normal=v1*v2;}
            Normalise(Normal);
      if(oldmatl != matl){
      mat_amb[0]=wred[iwnumb-1-matl]; mat_amb[1]=wgreen[iwnumb-1-matl];
      mat_amb[2]=wblue[iwnumb-1-matl]; mat_amb[3]=1.0/((double)(iwnumb-3));
      mat_diff[0]=wred[iwnumb-1-matl]; mat_diff[1]=wgreen[iwnumb-1-matl];
      mat_diff[2]=wblue[iwnumb-1-matl]; mat_diff[3]=1.0/((double)(iwnumb-3));
      mat_spec[0]=wred[iwnumb-1-matl]; mat_spec[1]=wgreen[iwnumb-1-matl];
      mat_spec[2]=wblue[iwnumb-1-matl]; mat_spec[3]=1.0/((double)(iwnumb-3));

      mat_amb[0]=wred[iwnumb-1-matl]; mat_amb[1]=wgreen[iwnumb-1-matl];
      mat_amb[2]=wblue[iwnumb-1-matl]; mat_amb[3]=1.0/2.0;
      mat_diff[0]=wred[iwnumb-1-matl]; mat_diff[1]=wgreen[iwnumb-1-matl];
      mat_diff[2]=wblue[iwnumb-1-matl]; mat_diff[3]=1.0/2.0;
      mat_spec[0]=wred[iwnumb-1-matl]; mat_spec[1]=wgreen[iwnumb-1-matl];
      mat_spec[2]=wblue[iwnumb-1-matl]; mat_spec[3]=1.0/2.0;
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
      glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);

      glGetMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,gotmaterial);
      glGetMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,gotmaterial);
      glGetMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,gotmaterial);
      }
     // cout << blendon << endl;
          if(!blendon){
          glDisable(GL_BLEND);
          gl2psDisable(GL2PS_BLEND);
          glEnable(GL_DEPTH_TEST);
          }
      if(blendon){
      glDisable(GL_DEPTH_TEST);
     //don't exist gl2psDisable(GL2PS_DEPTH_TEST);
      glEnable(GL_BLEND);
      gl2psEnable(GL2PS_BLEND);
   //Note that DST is not supported on many platforms, can do anything with SRC
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      gl2psBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      }
      oldmatl=matl;
            glNormal3f(Normal.GetX(),Normal.GetZ(),-Normal.GetY());
            glBegin(GL_TRIANGLES);
              glVertex3f(x1,z1,-y1);
              glVertex3f(x2,z2,-y2);
              glVertex3f(x3,z3,-y3); 
            glEnd(); 
	     }
	     else
	     {
	glColor3ub((int)(255*wred[matl]),(int)(255*wgreen[matl]),(int)(255*wblue[matl]));
           if(wclev.at(i) < iwnumb){
           if(LIGHTS)glNormal3f(Normal.GetX(),Normal.GetZ(),-Normal.GetY());
            glBegin(GL_TRIANGLES);
              glVertex3f(x1,z1,-y1);
              glVertex3f(x2,z2,-y2);
              glVertex3f(x3,z3,-y3); 
            glEnd(); }
          if(blendon){
          glDisable(GL_BLEND);
          gl2psDisable(GL2PS_BLEND);
          glEnable(GL_DEPTH_TEST);
          }
	}  //endif for LIGHTS


          }  //end loop over triangles
    } // endif lines and drawscene
    //  cout << "trilength=" << trilength << endl;
    //
    //  DRAW TEST TRIANGLE
      if(testplot>-1 && testplot < trilength && testsurf==1){
      int   matl=5;
	     if(LIGHTS){
      float mat_amb[4]={RedM[matl][0], GreenM[matl][0],BlueM[matl][0],
		                AlphaM[matl][0] };
      float mat_diff[4]={RedM[matl][1], GreenM[matl][1],BlueM[matl][1],
		                AlphaM[matl][1] };
      float mat_spec[4]={RedM[matl][2], GreenM[matl][2],BlueM[matl][2],
		                AlphaM[2][2] };
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
      glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	     }
	     else
	     {
	glColor3ub((int)(255*RedM[matl][1]),(int)(255*GreenM[matl][1]),(int)(255*BlueM[matl][1]));
	}  //endif for LIGHTS

      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            TempTri=IsoTris.at(testplot);
            n1=TempTri->Get1(); n2=TempTri->Get2(); n3=TempTri->Get3();
            x1=(IsoVecs.at(n1))->GetX();y1=(IsoVecs.at(n1))->GetY();z1=(IsoVecs.at(n1))->GetZ();
            x2=(IsoVecs.at(n2))->GetX();y2=(IsoVecs.at(n2))->GetY();z2=(IsoVecs.at(n2))->GetZ();
            x3=(IsoVecs.at(n3))->GetX();y3=(IsoVecs.at(n3))->GetY();z3=(IsoVecs.at(n3))->GetZ();
            glBegin(GL_TRIANGLES);
              glVertex3f(x1,z1,-y1);
              glVertex3f(x2,z2,-y2);
              glVertex3f(x3,z3,-y3); 
            glEnd(); 
            cout << testplot << " " << tritetvec.at(testplot) << endl;
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
       int tetplotz=tritetvec.at(testplot);
       DrawTet=(Tets+tetplotz);

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

       x1=xlow+(x1-xmin)*xScale;x2=xlow+(x2-xmin)*xScale;
       x3=xlow+(x3-xmin)*xScale;x4=xlow+(x4-xmin)*xScale;
       y1=ylow+(y1-xmin)*yScale;y2=ylow+(y2-xmin)*yScale;
       y3=ylow+(y3-xmin)*yScale;y4=ylow+(y4-xmin)*yScale;
       z1=zlow+(z1-xmin)*zScale;z2=zlow+(z2-xmin)*zScale;
       z3=zlow+(z3-xmin)*zScale;z4=zlow+(z4-xmin)*zScale;
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

            }  //endif for testplot

      //BLACK BOUNDING BOX
       glDisable(GL_LIGHTING);
       if(LIGHTS){
      float mat_amb[4]={0, 0 , 0, 1};
      float mat_diff[4]={0, 0 , 0, 1};
      float mat_spec[4]={0, 0 , 0, 1};
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
      glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
      }
      else
      {
         glColor3ub(0,0,0);
      } 
         glColor3ub(0,0,0);
       glBegin(GL_LINES);
          glVertex3f(xlow,zlow,-ylow); glVertex3f(xhigh,zlow,-ylow);       
          glVertex3f(xlow,zlow,-yhigh); glVertex3f(xhigh,zlow,-yhigh);       
          glVertex3f(xlow,zlow,-ylow); glVertex3f(xlow,zlow,-yhigh);       
          glVertex3f(xhigh,zlow,-ylow); glVertex3f(xhigh,zlow,-yhigh);       
          glVertex3f(xlow,zhigh,-ylow); glVertex3f(xhigh,zhigh,-ylow);       
          glVertex3f(xlow,zhigh,-yhigh); glVertex3f(xhigh,zhigh,-yhigh);       
          glVertex3f(xlow,zhigh,-ylow); glVertex3f(xlow,zhigh,-yhigh);       
          glVertex3f(xhigh,zhigh,-ylow); glVertex3f(xhigh,zhigh,-yhigh);       
          glVertex3f(xlow,zlow,-ylow); glVertex3f(xlow,zhigh,-ylow);       
          glVertex3f(xhigh,zlow,-ylow); glVertex3f(xhigh,zhigh,-ylow);       
          glVertex3f(xlow,zlow,-yhigh); glVertex3f(xlow,zhigh,-yhigh);       
          glVertex3f(xhigh,zlow,-yhigh); glVertex3f(xhigh,zhigh,-yhigh);       
       glEnd();

       //Now we have real FUN with the text and tickmarks
                   double xt,yt,zt;
                   double longtick=70.0; double shorttick=longtick/2.0;

                   //xyz refer to normal xyz coordinates


                   D2Dvec Cam;
                   Cam.SetVec(Camera1.CamPos.GetX(),-Camera1.CamPos.GetZ()); //not OpenGL coords
                   D2Dvec Centre;

                   Centre.SetVec((xhigh+xlow)/2.0,(yhigh+ylow)/2.0);
                   D2Dvec Corner1, Corner2, Corner3, Corner4;
                   Corner1.SetVec(xlow,ylow); Corner2.SetVec(xhigh,ylow); // two near, left and right
                   Corner3.SetVec(xlow,yhigh); Corner4.SetVec(xhigh, yhigh);

                   D2Dvec vec0,vec1,vec2,vec3,vec4;

                   vec0=Cam-Centre; vec1=Corner1-Centre; vec2=Corner2-Centre;
                   vec3=Corner3-Centre; vec4=Corner4-Centre;

                   double Mod0,Mod1,Mod2,Mod3,Mod4;
                   Mod0=GetMod(vec0);
                   double ang0,ang1,ang2,ang3,ang4;
                   double dot1,dot2,dot3,dot4;

                   //probably dont need Mods or normalisation
                   if(Mod0>1.e-3){
                      dot1=vec0.Dot(vec1);dot2=vec0.Dot(vec2);dot3=vec0.Dot(vec3); dot4=vec0.Dot(vec4);
                   }

                    bool quad1=false,quad2=false,quad3=false,quad4=false;

                    if(dot1>0 && dot2>0)quad1=true; if(dot1>0 && dot3>0)quad2=true;
                    if(dot3>0 && dot4>0)quad3=true; if(dot4>0 && dot2>0)quad4=true; 

                    int iquad=0;
                    if(quad1)iquad++;if(quad2)iquad++;if(quad3)iquad++;if(quad4)iquad++;
                 //   cout << "quads are " << quad1 << quad2 << quad3 << quad4 << endl;

                    if(iquad!=1){
                       cout << " need to alter quadrant testing in DrawScene, iquad=" << iquad << endl;
                       exit(1);
                    }
                    D2Dvec Cam2Corn1,Cam2Corn2,Cam2Corn3,Cam2Corn4;

                    Cam2Corn1=vec1-vec0;Cam2Corn2=vec2-vec0;
                    Cam2Corn3=vec3-vec0;Cam2Corn4=vec4-vec0;

                    Mod1=GetMod(Cam2Corn1); Mod2=GetMod(Cam2Corn2);
                    Mod3=GetMod(Cam2Corn3); Mod2=GetMod(Cam2Corn4);

                    Normalise(Cam2Corn1); Normalise(Cam2Corn2);
                    Normalise(Cam2Corn3); Normalise(Cam2Corn4);
                    Normalise(vec0);   //dots will now be cosines

                    dot1=-vec0.Dot(Cam2Corn1); dot2=-vec0.Dot(Cam2Corn2);
                    dot3=-vec0.Dot(Cam2Corn3); dot4=-vec0.Dot(Cam2Corn4);

                    bool all, silly, tom, cats;

                    double cosine, sine, angle;
                    cosine=-vec0.GetY();
                    sine=vec0.GetX();
                    angle=asin(sine)*180.0/pi;
              //      cout << dot5 << "  " << sine5 << endl;
                    all=false; silly=false; tom=false; cats=false;
                    if(sine>=0.0){ if(cosine >=0.0){all=true;} else {silly=true;} };
                    if(sine<0.0){ if(cosine < 0.0){tom=true;} else {cats=true;} };

                    //all in quadrant 1, do nothing
                    if(silly)angle=180.0-angle;  //quadrant 2 angle decreasing from 90 to 0
                    if(tom)angle=180.0-angle;  //quadrant3   angle increasing 0 to -90 
                    if(cats)angle=360.0+angle;   //quadrant 4 angle1 negative 0 to -90
 
                    bool printz1=false,printz2=false,printz3=false,printz4=false;
                    
                    if(quad1){
                       if(dot1<dot3){printz1=true; } 
                             else {  printz3=true; }
                       if(dot2<dot4){printz2=true; }
                               else{ printz4=true; }}
                   if(quad2){


                       if(dot3<dot4){printz3=true; }
                              else{  printz4=true; }
                       if(dot1<dot2){printz1=true; }
                               else{ printz2=true; }}
                   if(quad3){
                       if(dot2<dot4){printz2=true; }
                              else{  printz4=true; }
                       if(dot1<dot3){printz1=true; }
                               else{ printz3=true; }}
                  if(quad4){
                       if(dot1<dot2){printz1=true; }
                              else{  printz2=true; }
                       if(dot3<dot4){printz3=true; }
                               else{ printz4=true; }}

//                  Near x numbers
                   glPushMatrix();
                   //The rotation is counter clockwise
                   // of the vector points TOWARDS the viewer
                   glRotatef(-90.0,1.0,0.0,0.0);
                   // in/out now openGL -+y,  up/down now openGL -+z
                   xt=xlow+(x_start-(xmin-xsubtract))/xrange*(xhigh-xlow);
                   yt=-ylow;
                   zt=-zlow;
                   glTranslated(xt-shift1,-yt-shift4-150,-zt);  //initial translation with shift

                   xt=xstep/xrange*(xhigh-xlow);  //for subsequent translations
                   yt=0.0;
                   zt=0.0;
                   for(int i=0; i< ixnumb; i++){
                      glPushMatrix();
		      font1->draw(xstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();

//                 Far x numbers
                   glPushMatrix();
                   //The rotation is counter clockwise
                   // of the vector points TOWARDS the viewer
                   glRotatef(-90.0,1.0,0.0,0.0);
                   glRotatef(180.0,0.0,0.0,1.0);
                   //left/right now openGL -+xm in/out now openGL +iy,up/down now openGL -+z

                   xt=xhigh-(x_start-(xmin-xsubtract))/xrange*(xhigh-xlow);
                   yt=-ylow;
                   zt=-zlow;
                   glTranslated(xt-shift1,-yt-shift4-150,-zt);  //initial translation with shift

                   xt=xstep/xrange*(xhigh-xlow);  //for subsequent translations
                   yt=0.0;
                   zt=0.0;
                   for(int i=0; i< ixnumb; i++){
                      glPushMatrix();
		      font1->draw(xstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(-xt,yt,zt);
                    }
                   glPopMatrix();


                   //major tick marks for x axis bounding box and x axis if required
                   xt=xlow+(x_start-(xmin-xsubtract))/xrange*(xhigh-xlow); yt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   xt=xstep/xrange*(xhigh-xlow);  //for subsequent translations
                   for(int i=0; i<ixnumb; i++){
                      glBegin(GL_LINES);
                          glVertex3f(0.0,zlow,ylow-longtick); glVertex3f(0.0,zlow,ylow);
                          glVertex3f(0.0,zlow,yhigh); glVertex3f(0.0,zlow,yhigh+longtick);
                      glEnd();
                      glTranslated(xt,yt,zt);
                    }
                    glPopMatrix();

                   //minor tick marks for x axis bounding box and x axis if required
                   xt=xlow+(x_start2-(xmin-xsubtract))/xrange*(xhigh-xlow); yt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   xt=xstep2/xrange*(xhigh-xlow);  //for subsequent translations
                   for(int i=0; i<ixnumb2; i++){
                      if(xnumbers2[i]+xsubtract>=xmin && xnumbers2[i]+xsubtract<=xmax){
                      glBegin(GL_LINES);
                          glVertex3f(0.0,zlow,ylow-shorttick); glVertex3f(0.0,zlow,ylow);
                          glVertex3f(0.0,zlow,yhigh+shorttick); glVertex3f(0.0,zlow,yhigh);
                      glEnd();
                      }
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();



                   //Y BOUNDING BOX NUMBERS AND TICKMARKS

                   //numbers for y axis left and right bounding box edge

                   yt=ylow-(y_start-(ymin-ysubtract))/yrange*(yhigh-ylow);
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glRotatef(-90.0,1.0,0.0,0.0);
                   glRotatef(-90.0,0.0,0.0,1.0);
                   // openGL in/out=-+x, left/right=+-y, up/down =+-z
                   glTranslated(-yt-shift5,xlow-150.0-shift2,zlow);  //initial translation with shift
                   yt=ystep/yrange*(yhigh-ylow);  //for subsequent translations
                   for(int i=0; i< iynumb; i++){
                      glPushMatrix();
		      font1->draw(ystrings[i].c_str());
                      glPopMatrix();
                      glTranslated(-yt,xt,zt);
                    }
                   glPopMatrix();

                   yt=ylow+(y_start-(ymin-ysubtract))/yrange*(yhigh-ylow);
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glRotatef(-90.0,1.0,0.0,0.0);
                   glRotatef(90.0,0.0,0.0,1.0);
                   // openGL in/out=+-x, left/right=-+y, up/down =+-z
                   glTranslated(yt-shift5,-xhigh-150.0-shift2,zlow);  //initial translation with shift
                   yt=ystep/yrange*(yhigh-ylow);  //for subsequent translations
                   for(int i=0; i< iynumb; i++){
                      glPushMatrix();
		      font1->draw(ystrings[i].c_str());
                      glPopMatrix();
                      glTranslated(yt,xt,zt);
                    }
                   glPopMatrix();

 

                   //major tick marks for y axis bounding box and y axis 
                   yt=ylow+(y_start-(ymin-ysubtract))/yrange*(yhigh-ylow);
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,yt); //initial translation step
                   yt=ystep/yrange*(yhigh-ylow);  //for subsequent translation
                   for(int i=0; i<iynumb; i++){
                      glBegin(GL_LINES);
                        glVertex3f(xlow,zlow,0.0); glVertex3f(xlow-longtick,zlow,0.0);
                        glVertex3f(xhigh,zlow,0.0); glVertex3f(xhigh+longtick,zlow,0.0);
                      glEnd();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();

                   //minor tick marks for y axis bounding box and y axis 
                   yt=ylow+(y_start2-(ymin-ysubtract))/yrange*(yhigh-ylow);
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,yt); //initial translation step
                   yt=ystep2/yrange*(yhigh-ylow);  //for subsequent translation
                   for(int i=0; i<iynumb2; i++){
                      if(ynumbers2[i]+ysubtract>=ymin && ynumbers2[i]+ysubtract<=ymax){
                      glBegin(GL_LINES);
                        glVertex3f(xlow,zlow,0.0); glVertex3f(xlow-shorttick,zlow,0.0);
                        glVertex3f(xhigh,zlow,0.0); glVertex3f(xhigh+shorttick,zlow,0.0);
                      glEnd();
                      }
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();

                   //Z BOUNDING BOX NUMBERS AND TICKMARKS
                   //numbers for 4 vertical z axes

                   double xtrans,ytrans;

                   if(printz3){
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   xtrans=xlow; ytrans=ylow;
                   if(quad1 || quad2){
                     xtrans=xtrans-(180.0+shift6)*cosine;  ytrans=ytrans+(180.0+shift6)*sine;}
                   else{
                     xtrans=xtrans+(120.0+shift6)*cosine;  ytrans=ytrans-(120.0+shift6)*sine;}

                   glPushMatrix();
                   glRotatef(angle,0.0,1.0,0.0);

                   glTranslated(xtrans*cosine-ytrans*sine
                                ,zt-shift3,ytrans*cosine+xtrans*sine);
                   //initial translation with shift
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translations
                   xt=0.0; yt=0.0;
                   for(int i=0; i< iznumb; i++){
                      glPushMatrix();
		      font1->draw(zstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();
                   }  //corner3

                   if(printz4){
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   xtrans=xhigh;   ytrans=ylow;
                   if(quad1 || quad4 ){
                     xtrans=xtrans+(100.0+shift6)*cosine; ytrans=ytrans-(100.0+shift6)*sine;}
                   else{
                     xtrans=xtrans-(180.0+shift6)*cosine; ytrans=ytrans+(180.0+shift6)*sine;}
                   glPushMatrix();
                   glRotatef(angle,0.0,1.0,0.0);
                   glTranslated(xtrans*cosine-ytrans*sine
                                ,zt-shift3,ytrans*cosine+xtrans*sine);  
                   //initial translation with shift
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translations
                   xt=0.0; yt=0.0;
                   for(int i=0; i< iznumb; i++){
                      glPushMatrix();
		      font1->draw(zstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();
                   } //corner4

                   if(printz1){
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   xtrans=xlow;  ytrans=yhigh;
                  if(quad1 || quad4){
                     xtrans=xtrans-(180.0+shift6)*cosine; ytrans=ytrans+(180.0+shift6)*sine;}
                   else{
                     xtrans=xtrans+(100.0+shift6)*cosine; ytrans=ytrans-(100.0+shift6)*sine;}
                   glPushMatrix();
                   glRotatef(angle,0.0,1.0,0.0);
                   glTranslated(xtrans*cosine-ytrans*sine
                                 ,zt-shift3,ytrans*cosine+xtrans*sine);
                    //initial translation with shift
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translations
                   xt=0.0; yt=0.0;
                   for(int i=0; i< iznumb; i++){
                      glPushMatrix();
		      font1->draw(zstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();
                   }  //corner1

 
                  if(printz2){
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   xtrans=xhigh; ytrans=yhigh;
                   if(quad1 || quad2){
                        xtrans=xtrans+(100.0+shift6)*cosine; ytrans=ytrans-(100+shift6)*sine;}
                      else{
                        xtrans=xtrans-(180.0+shift6)*cosine; ytrans=ytrans+(180+shift6)*sine;}
                   glPushMatrix();
                   glRotatef(angle,0.0,1.0,0.0);
                   glTranslated(xtrans*cosine-ytrans*sine,
                                zt-shift3,ytrans*cosine+xtrans*sine); 
                    //initial translation with shift
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translations
                   xt=0.0; yt=0.0;
                   for(int i=0; i< iznumb; i++){
                      glPushMatrix();
		      font1->draw(zstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();
                  }  //corner2

                   //major tick marks for  4 z axis axes
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,ylow); //initial translation step
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translation
                   for(int i=0; i<iznumb; i++){
                      glBegin(GL_LINES);
                        if(quad1 || quad2){
                          glVertex3f(xlow,0.0,0.0); glVertex3f(xlow-longtick*cosine,0.0,longtick*sine);
                        } else {
                          glVertex3f(xlow,0.0,0.0); glVertex3f(xlow+longtick*cosine,0.0,-longtick*sine);}
                       if(quad1 || quad4){
                         glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh+longtick*cosine,0.0,-longtick*sine);}
                       else{
                         glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh-longtick*cosine,0.0,+longtick*sine);}
                      glEnd();
                      glTranslated(xt,zt,yt);
                    }

                   glPopMatrix();
                   zt=zlow+(z_start-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,yhigh); //initial translation step
                   zt=zstep/zrange*(zhigh-zlow);  //for subsequent translation
                   for(int i=0; i<iznumb; i++){
                      glBegin(GL_LINES);
                         if(quad1 || quad4){
                         glVertex3f(xlow,0.0,0.0); glVertex3f(xlow-longtick*cosine,0.0,longtick*sine);}
                         else{
                         glVertex3f(xlow,0.0,0.0); glVertex3f(xlow+longtick*cosine,0.0,-longtick*sine);}
                       if(quad1 || quad2){
                          glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh+longtick*cosine,0.0,-longtick*sine);}
                          else{
                          glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh-longtick*cosine,0.0,longtick*sine);}
                      glEnd();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();
                   //minor z tickmarks
                   zt=zlow+(z_start2-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,ylow); //initial translation step
                   zt=zstep2/zrange*(zhigh-zlow);  //for subsequent translation
                   for(int i=0; i<iznumb2; i++){
                      if(znumbers2[i]+zsubtract>=zmin && znumbers2[i]+zsubtract<=zmax){
                      glBegin(GL_LINES);
                        if(quad1 || quad2){
                          glVertex3f(xlow,0.0,0.0); glVertex3f(xlow-shorttick*cosine,0.0,shorttick*sine);}
                        else{
                          glVertex3f(xlow,0.0,0.0); glVertex3f(xlow+shorttick*cosine,0.0,-shorttick*sine);}
                        if(quad1 || quad4){
                          glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh+shorttick*cosine,0.0,-shorttick*sine);}
                        else{
                          glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh-shorttick*cosine,0.0,+shorttick*sine);}
                      glEnd();
                      }
                      glTranslated(xt,zt,yt);
                    }
                    glPopMatrix();
                   zt=zlow+(z_start2-(zmin-zsubtract))/zrange*(zhigh-zlow);
		   xt=0.0; yt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,yhigh); //initial translation step
                   zt=zstep2/zrange*(zhigh-zlow);  //for subsequent translation
                   for(int i=0; i<iznumb2; i++){
                      if(znumbers2[i]+zsubtract>=zmin && znumbers2[i]+zsubtract<=zmax){
                      glBegin(GL_LINES);
                         if(quad1 || quad4){
                           glVertex3f(xlow,0.0,0.0); glVertex3f(xlow-shorttick*cosine,0.0,shorttick*sine);}
                         else{
                           glVertex3f(xlow,0.0,0.0); glVertex3f(xlow+shorttick*cosine,0.0,-shorttick*sine);}

                        if(quad1 || quad2){
                           glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh+shorttick*cosine,0.0,-shorttick*sine);}
                        else{
                          glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh-shorttick*cosine,0.0,+shorttick*sine);}
                      glEnd();
                      }
                      glTranslated(xt,zt,yt);
                    }
                    glPopMatrix();



      if(ixtext==1){
      ostringstream xst;
      if(xaddsubtract){
         xst << '(';
         xst << xtext;
         if(xsubtract<0){
             xst << '+';
             xst << -xsubtract;
             }
         if(xsubtract>0){
           xst << '-';
           xst << xsubtract;
           }
          xst << ')';
      }
      if(!xaddsubtract)xst << xtext;

      if(ixunits==1){
        xst << ' ';
        xst << xunits;
      }

      xaxistext=xst.str();

      float xt=(float)xaxistext.length();
      xt=xt*40/2.0;  //pointsize 45

      glPushMatrix();
      glRotatef(-90.0,1.0,0.0,0.0);
         //Opengl in out now +-y, up/down=+-z
         glTranslated(-xt-shift7, ylow-250-shift8 , zlow);
         font12->draw(xaxistext.c_str());
      glPopMatrix();


      glPushMatrix();
      glRotatef(-90.0,1.0,0.0,0.0);
      glRotatef(180.0,0.0,0.0,1.0);
         //Opengl in out now -+y, up/down=+-z, leftright=-+x
         glTranslated(-xt-shift7, ylow-250-shift8 , zlow);
         font12->draw(xaxistext.c_str());
      glPopMatrix();

      }   //endif for is there any x axis text

     if(iytext==1){
      ostringstream yst;
      if(yaddsubtract){
         yst << '(';
         yst << ytext;
         if(ysubtract<0){
             yst << '+';
             yst << -ysubtract;
             }
         if(ysubtract>0){
           yst << '-';
           yst << ysubtract;
           }
          yst << ')';
      }
      if(!yaddsubtract)yst << ytext;

      if(iyunits==1){
        yst << ' ';
        yst << yunits;
      }

      //we are looking along +ve z (otherwise get mirror text)


      yaxistext=yst.str();
      float yt=(float)yaxistext.length();
      yt=yt*40./2.0;


      glPushMatrix();
         glRotatef(-90.0,1.0,0.0,0.0);  //rotate anticlock
         glRotatef(90.0,0.0,0.0,1.0);
         //openGL in out now -+x, openGL left/right now -+y  i[down +0z
         glTranslated(-yt-shift10,-xhigh-220.0+shift9,zlow);
         font12->draw(yaxistext.c_str());
      glPopMatrix();


      glPushMatrix();
         glRotatef(-90.0,1.0,0.0,0.0);  //rotate clock
         glRotatef(-90.0,0.0,0.0,1.0);
         //openGL in out now +-x, openGL left/right now +-y up/down +=z
         glTranslated(-yt-shift10, xlow-240.0+shift9,zlow);//remember xlow is negative, and that after rotation y is towards old -x
         font12->draw(yaxistext.c_str());
      glPopMatrix();

      }   //endif for is there any y axis text


     if(iztext==1){
      ostringstream zst;
      if(zaddsubtract){
         zst << '(';
         zst << ytext;
         if(zsubtract<0){
             zst << '+';
             zst << -ysubtract;
             }
         if(zsubtract>0){
           zst << '-';
           zst << zsubtract;
           }
          zst << ')';
      }
      if(!zaddsubtract)zst << ztext;

      if(izunits==1){
        zst << ' ';
        zst << zunits;
      }

      //we are looking along +ve z (otherwise get mirror text)

      float zt=zaxistext.length();
      zt=zt*40./2.0;

      if(printz3){
      zaxistext=zst.str();
      glPushMatrix();
         glRotatef(90.0,0.0,0.0,1.0);
         //openGL in/out now +-z, openGL left/right now +-y, openGL up down now +-x
         glRotatef(angle,1.0,0.0,0.0);
         xtrans=-xlow; ytrans=zlow;
         if(quad3 || quad4){
            xtrans=xtrans-(300.0-shift12)*cosine;  ytrans=ytrans-(300.0-shift12)*sine;}
            else{
            xtrans=xtrans+(250.0-shift12)*cosine;  ytrans=ytrans+(250.0-shift12)*sine;}
         glTranslated(-zt-shift11,xtrans*cosine+ytrans*sine,ytrans*cosine-xtrans*sine);
         font12->draw(zaxistext.c_str());
      glPopMatrix();
       }    //corner3

      if(printz4){
      glPushMatrix();
         glRotatef(90.0,0.0,0.0,1.0);
         //openGL in/out now +-z, openGL left/right now +-y, openGL up down now +-x
         glRotatef(angle,1.0,0.0,0.0);
         xtrans=-xhigh; ytrans=zlow;
         if( quad1 || quad4){
             xtrans=xtrans-(250.0-shift12)*cosine, ytrans=ytrans-(250.0-shift12)*sine; }
            else{
             xtrans=xtrans+(250.0-shift12)*cosine, ytrans=ytrans+(250.0-shift12)*sine; }
         glTranslated(-zt-shift11,xtrans*cosine+ytrans*sine,ytrans*cosine-xtrans*sine);
        font12->draw(zaxistext.c_str());
       glPopMatrix();
       }  //corner 4


      if(printz1){
      zaxistext=zst.str();
      glPushMatrix();
         glRotatef(90.0,0.0,0.0,1.0);
         //openGL in/out now +-z, openGL left/right now +-y, openGL up down now +-x
         glRotatef(angle,1.0,0.0,0.0);
         xtrans=-xlow; ytrans=zhigh;
         if(quad1 || quad4){
            xtrans=xtrans+(250.0-shift12)*cosine; ytrans=ytrans+(250.0-shift12)*sine;}
          else{
            xtrans=xtrans-(250.0-shift12)*cosine; ytrans=ytrans-(250.0-shift12)*sine;}
         glTranslated(-zt-shift11,xtrans*cosine+ytrans*sine,ytrans*cosine-xtrans*sine);
         font12->draw(zaxistext.c_str());
      glPopMatrix();
     } //corner1


      if(printz2){
      glPushMatrix();
         glRotatef(90.0,0.0,0.0,1.0);
         //openGL in/out now +-z, openGL left/right now +-y, openGL up down now +-x
         glRotatef(angle,1.0,0.0,0.0);
         xtrans=-xhigh;  ytrans=zhigh;
         if(quad1 || quad2){
                 xtrans=xtrans-(250.0-shift12)*cosine; ytrans=ytrans-(250.0-shift12)*sine;}
                 else{
                 xtrans=xtrans+(250.0-shift12)*cosine; ytrans=ytrans+(250.0-shift12)*sine;}
         glTranslated(-zt-shift11,xtrans*cosine+ytrans*sine,ytrans*cosine-xtrans*sine);
         font12->draw(zaxistext.c_str());
      glPopMatrix();
      } // corner2



      }   //endif for is there any z axis text



       glEnable(GL_LIGHTING);


}
int SurfGrow(int it, int icut1,int icut2, int ifacelook, double wc, int ix1, int ix2, int iy1, int iy2){
         current_depth++;
         if(current_depth>maxdepth){
           cout << "depth is now " << current_depth << endl;
           cout << "increase maxdepth, if it crashes you have blown the stack\n";
           exit(1);
         }
         int ireturn=-1;
         if(it<0)return ireturn;  //have hit the boundary
      /*  
         if(it==717){
             cout << "Here We Are, Tet=" << it << endl;}
         if(newtris==1626){
             cout << "HERE  tet=" << it  <<endl;}
       */

         if(Done[it][id]){
              return ireturn;}
         
         Done[it][id]=true;
         
         int i1,i2,i3,i4;

         int in1,in2,in3,in4;  //neighbours which must be cut as well
         int if1,if2,if3,if4;

         in1=-1; in2=-1; in3=-1; in4=-1;

         double xc1,yc1,zc1,xc2,yc2,zc2,xc3,yc3,zc3
               ,xc4,yc4,zc4,xc5,yc5,zc5,xc6,yc6,zc6;  // x, y, z of 6 possible edge cuts

         double wdiff;

         double x1,x2,x3,x4; double y1,y2,y3,y4;    //w, x, y, z of four tet nodes
         double z1,z2,z3,z4; double w1,w2,w3,w4;

         D3Dvec* currentV;

         i1=Tets[it].Get1();i2=Tets[it].Get2();
         i3=Tets[it].Get3();i4=Tets[it].Get4();

         int *bf1, *bf2, *bf3, *bf4;
         bf1=Tets[it].GetN1();bf2=Tets[it].GetN2();
         bf3=Tets[it].GetN3();bf4=Tets[it].GetN4();

         if(bf1){in1=*bf1;}
         if(bf2){in2=*bf2;}
         if(bf3){in3=*bf3;}
         if(bf4){in4=*bf4;}
        
         //These four characters are initialised to zero in RayMeshTet constructor
         // set by SetTet with whichface in basicCube
         if1=(int)(Tets[it].GetC1());if2=(int)(Tets[it].GetC2());
         if3=(int)(Tets[it].GetC3());if4=(int)(Tets[it].GetC4());

         //For edge info
         int ia1=-1, ia2=-1, ib1=-1, ib2=-1;

         int iface1,iface2,iface3,iface4;

         currentV=Node[i1].GetVec();
         x1=currentV->GetX(); y1=currentV->GetY(); z1=currentV->GetZ();
         currentV=Node[i2].GetVec();
         x2=currentV->GetX(); y2=currentV->GetY(); z2=currentV->GetZ();
         currentV=Node[i3].GetVec();
         x3=currentV->GetX(); y3=currentV->GetY(); z3=currentV->GetZ();
         currentV=Node[i4].GetVec();
         x4=currentV->GetX(); y4=currentV->GetY(); z4=currentV->GetZ();

         x1=xlow+(x1-xmin)*xScale;x2=xlow+(x2-xmin)*xScale;
         x3=xlow+(x3-xmin)*xScale;x4=xlow+(x4-xmin)*xScale;
         y1=ylow+(y1-ymin)*yScale;y2=ylow+(y2-ymin)*yScale;
         y3=ylow+(y3-ymin)*yScale;y4=ylow+(y4-ymin)*yScale;
         z1=zlow+(z1-zmin)*zScale;z2=zlow+(z2-zmin)*zScale;
         z3=zlow+(z3-zmin)*zScale;z4=zlow+(z4-zmin)*zScale;


         w1=wval[i1]; w2=wval[i2]; w3=wval[i3]; w4=wval[i4];

         bool cuts[6];
         cuts[0]=false; cuts[1]=false; cuts[2]=false;
         cuts[3]=false; cuts[4]=false; cuts[5]=false; 
         int ncuts=0;

         //triangle nodes 1 to 3

         int t1,t2,t3,t4;
         // only work out all cuts if first call
         // don't want unnecessary new vectors
         //
         bool bed1=false; bool bed2=false; bool bed3=false; bool bed4=false;
         int ibed=0;

         if(icut1<0 || icut2 <0 || ifacelook<0){
              //This is a first call, No tet has been cut and called here
              if(fabs(w1-wc)<Tol){
                   bed1=true; ibed++;}
              if(fabs(w2-wc)<Tol){
                   bed2=true; ibed++;}
              if(fabs(w3-wc)<Tol){
                   bed3=true; ibed++;}
              if(fabs(w4-wc)<Tol){
                   bed4=true; ibed++;}
              bool bededge1, bededge2, bededge3, bededge4, bededge5, bededge6;
              int ibededge=-1;
              if(bed1 && bed2){bededge1=true;} else {bededge1=false;}
              if(bed1 && bed3){bededge2=true;} else {bededge2=false;}
              if(bed1 && bed4){bededge3=true;} else {bededge3=false;}
              if(bed2 && bed3){bededge4=true;} else {bededge4=false;}
              if(bed2 && bed4){bededge5=true;} else {bededge5=false;}
              if(bed3 && bed4){bededge6=true;} else {bededge6=false;}
              if(ibed==2){
                 if(bededge1)ibededge=1; if(bededge2)ibededge=2; if(bededge3)ibededge=3;
                 if(bededge4)ibededge=4; if(bededge5)ibededge=5; if(bededge6)ibededge=6;
              }

              //Note the if(fabs(wa-wb)>Tol) 
              //If wa=wb, this is usually fine, because there won't be a cut
              //on ia to ib, but if wa=wc as well, the edge is embedded the isosurface
              //this is what the bools bed 1 to 6 are for...
              //if ibed=1 or 2

             // work out cuts for all edges 1 to 6
             //
             // we have to leave some out because of embedded edges
             if( ((wc<=w1-Tol) && (wc >=w2+Tol)) || ((wc>=w1+Tol) && (wc<=w2-Tol)) ){
                   //edge 1
                   wdiff=fabs((w1-wc)/(w1-w2));
                   xc1=x1+wdiff*(x2-x1);yc1=y1+wdiff*(y2-y1);zc1=z1+wdiff*(z2-z1);
                   if(!bededge6){
                   if(ibed !=1){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc1,yc1,zc1);
                   IsoVecs.push_back(NewVec);
                   tetcuts[it][ncuts]=newvecs;
                   tettrinodes[it][2*ncuts]=1;  //cut between nodes 1 and 2
                   tettrinodes[it][2*ncuts+1]=2;  //(numbered 1 to 4)
                   newvecs++;
                   }}
                   cuts[0]=true;
                   ncuts++;
             }
             if( ((wc<=w1-Tol) && (wc >=w3+Tol)) || ((wc>=w1+Tol) && (wc<=w3-Tol)) ){
                  // edge2
                   wdiff=fabs((w1-wc)/(w1-w3));
                   xc2=x1+wdiff*(x3-x1);yc2=y1+wdiff*(y3-y1);zc2=z1+wdiff*(z3-z1);
                   if(!bededge5){
                   if(ibed !=1){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc2,yc2,zc2);
                   IsoVecs.push_back(NewVec);
                   tetcuts[it][ncuts]=newvecs;
                   tettrinodes[it][2*ncuts]=1;  //cut between nodes 1 and 3
                   tettrinodes[it][2*ncuts+1]=3;  //(numbered 1 to 4)
                   newvecs++;
                   }}
                   cuts[1]=true;
                   ncuts++;
             }
             if( ((wc<=w1-Tol) && (wc >=w4+Tol)) || ((wc>=w1+Tol) && (wc<=w4-Tol)) ){
                   //edge 3
                   wdiff=fabs((w1-wc)/(w1-w4));
                   xc3=x1+wdiff*(x4-x1);yc3=y1+wdiff*(y4-y1);zc3=z1+wdiff*(z4-z1);
                   if(!bededge4){
                   if(ibed !=1){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc3,yc3,zc3);
                   IsoVecs.push_back(NewVec);
                   tetcuts[it][ncuts]=newvecs;
                   tettrinodes[it][2*ncuts]=1;  //cut between nodes 1 and 4
                   tettrinodes[it][2*ncuts+1]=4;  //(numbered 1 to 4)
                   newvecs++;
                   }}
                   cuts[2]=true;
                   ncuts++;
             }
             if( ((wc<=w2-Tol) && (wc >=w3+Tol)) || ((wc>=w2+Tol) && (wc<=w3-Tol)) ){
                   //edge 4
                   wdiff=fabs((w2-wc)/(w3-w2));
                   xc4=x2+wdiff*(x3-x2);yc4=y2+wdiff*(y3-y2);zc4=z2+wdiff*(z3-z2);
                   if(!bededge3){
                   if(ibed !=1){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc4,yc4,zc4);
                   IsoVecs.push_back(NewVec);
                   tetcuts[it][ncuts]=newvecs;
                   tettrinodes[it][2*ncuts]=2;  //cut between nodes 2 and 3
                   tettrinodes[it][2*ncuts+1]=3;  //(numbered 1 to 4)
                   newvecs++;
                   }}
                   cuts[3]=true;
                   ncuts++;
             }
             if( ((wc<=w2-Tol) && (wc >=w4+Tol)) || ((wc>=w2+Tol) && (wc<=w4-Tol)) ){
                  //edge 5
                   wdiff=fabs((w2-wc)/(w4-w2));
                   xc5=x2+wdiff*(x4-x2);yc5=y2+wdiff*(y4-y2);zc5=z2+wdiff*(z4-z2);
                   if(!bededge2){
                   if(ibed !=1){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc5,yc5,zc5);
                   IsoVecs.push_back(NewVec);
                   tetcuts[it][ncuts]=newvecs;
                   tettrinodes[it][2*ncuts]=2;  //cut between nodes 2 and 4
                   tettrinodes[it][2*ncuts+1]=4;  //(numbered 1 to 4)
                   newvecs++;
                   }}
                   cuts[4]=true;
                   ncuts++;
             }
             if( ((wc<=w3-Tol) && (wc >=w4+Tol)) || ((wc>=w3+Tol) && (wc<=w4-Tol)) ){
                 //  edge6
                   wdiff=fabs((w3-wc)/(w4-w3));
                   xc6=x3+wdiff*(x4-x3);yc6=y3+wdiff*(y4-y3);zc6=z3+wdiff*(z4-z3);
                   if(!bededge1){
                   if(ibed !=1){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc6,yc6,zc6);
                   IsoVecs.push_back(NewVec);
                   tetcuts[it][ncuts]=newvecs;
                   tettrinodes[it][2*ncuts]=3;  //cut between nodes 3 and 4
                   tettrinodes[it][2*ncuts+1]=4;  //(numbered 1 to 4)
                   newvecs++;
                   }}
                   cuts[5]=true;
                   ncuts++;
              }
              if(ibed>=3){
                   if(ibed==4){
                   cout << "Sorry- I haven't coded that up yet\n";
                   cout <<"Comment out this exit(1) to carry on anyway\n";
                   exit(1);
                   }
                   cout << "ibed=" << ibed << endl;
                   cout << "wc=" << wc << endl;
                   cout << "ws are " << w1 << " " << w2 << " " << w3 << " " << w4 << endl;
                   cout << "Tetrahedron facet embedded in isosurface\n";
                   if( fabs(w1-wc) > Tol){
                     // face 1 embedded
                     cuts[0]=true; cuts[1]=true; cuts[2]=true;
                     NewVec=new D3Dvec;  NewVec->SetVec(x2,y2,z2);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][0]=newvecs;
                     tettrinodes[it][0]=1; tettrinodes[it][1]=2;
                     ncuts++; newvecs++;
                     NewVec=new D3Dvec;  NewVec->SetVec(x3,y3,z3);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][1]=newvecs;
                     tettrinodes[it][2]=1; tettrinodes[it][3]=3;
                     ncuts++; newvecs++;
                     NewVec=new D3Dvec;  NewVec->SetVec(x4,y4,z4);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][2]=newvecs;
                     tettrinodes[it][4]=1; tettrinodes[it][5]=4;
                     if(in1>=0)Done[in1][id]=true;
                     ncuts++; newvecs++;
                   }
                   if( fabs(w2-wc) > Tol){
                     // face 2 embedded
                     cuts[0]=true; cuts[3]=true; cuts[4]=true;
                     NewVec=new D3Dvec;  NewVec->SetVec(x1,y1,z1);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][0]=newvecs;
                     tettrinodes[it][0]=1; tettrinodes[it][1]=2;
                     ncuts++; newvecs++;
                     NewVec=new D3Dvec;  NewVec->SetVec(x3,y3,z3);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][1]=newvecs;
                     tettrinodes[it][2]=2; tettrinodes[it][3]=3;
                     ncuts++; newvecs++;
                     NewVec=new D3Dvec;  NewVec->SetVec(x4,y4,z4);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][2]=newvecs;
                     tettrinodes[it][4]=2; tettrinodes[it][5]=4;
                     if(in2>=0)Done[in2][id]=true;
                     ncuts++; newvecs++;
                   }
                   if(fabs(w3-wc) > Tol){
                     // face 3 embedded
                     cuts[1]=true; cuts[3]=true; cuts[5]=true;
                     NewVec=new D3Dvec;  NewVec->SetVec(x1,y1,z1);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][0]=newvecs;
                     tettrinodes[it][0]=1; tettrinodes[it][1]=3;
                     ncuts++; newvecs++;
                     NewVec=new D3Dvec;  NewVec->SetVec(x2,y2,z2);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][1]=newvecs;
                     tettrinodes[it][2]=2; tettrinodes[it][3]=3;
                     ncuts++; newvecs++;
                     NewVec=new D3Dvec;  NewVec->SetVec(x4,y4,z4);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][2]=newvecs;
                     tettrinodes[it][4]=3; tettrinodes[it][5]=4;
                     if(in3>=0)Done[in3][id]=true;
                     ncuts++; newvecs++;
                   }
                   if(fabs(w4-wc) > Tol){
                     // face 4 embedded
                     cuts[2]=true; cuts[4]=true; cuts[5]=true;
                     NewVec=new D3Dvec;  NewVec->SetVec(x1,y1,z1);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][0]=newvecs;
                     tettrinodes[it][0]=1; tettrinodes[it][1]=4;
                     ncuts++; newvecs++;
                     NewVec=new D3Dvec;  NewVec->SetVec(x2,y2,z2);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][1]=newvecs;
                     tettrinodes[it][2]=2; tettrinodes[it][3]=4;
                     ncuts++; newvecs++;
                     NewVec=new D3Dvec;  NewVec->SetVec(x3,y3,z3);
                     IsoVecs.push_back(NewVec);
                     tetcuts[it][2]=newvecs;
                     tettrinodes[it][4]=3; tettrinodes[it][5]=4;
                     if(in4>=0)Done[in4][id]=true;
                     ncuts++; newvecs++;
                   }
              }

              if(ncuts==0 && ibed<2)return ireturn;

              if(ncuts==0 && ibed==2){
                   //have an edge embedded, but no cut,
                   //might need to spin around an edge on a first call
                   //Don't think it is necessary to do so, so we don't... 
                   //need to free Done for when we arrive back
                   Done[it][id]=false;
                   return ireturn;
              }

              //if tetrahedron is cut we grow a surface
              ireturn=0;

              Triangle*  NewTri;

              if(ncuts+ibed <3){
                   cout << "Wot? Only " 
                   << ncuts  << " cuts on tetrahedron edges" << endl;
                   cout << "Tetrahedron = " << it << endl;
                   exit(1);
              }
              //Remember cuts MUST ARRIVE IN EDGE ORDER
              bool TriDone=false;
              if(ibed==1 &&  ncuts==2){
                  //cuts on face 1
                 if(!TriDone){
                 if(cuts[3] && cuts[4]){   //cuts edge 4 and 5
                    cuts[0]=true;  //bed=i1, put i1 on e1
                        NewVec=new D3Dvec;  NewVec->SetVec(x1,y1,z1);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=2; //edge 1
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc4,yc4,zc4);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=3; //edge 4
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc5,yc5,zc5);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=2; tettrinodes[it][5]=4; //edge 5
                        newvecs++;
                   TriDone=true;}}
                 if(!TriDone){
                 if(cuts[3] && cuts[5]){   //cuts edge 4 and 6
                      cuts[1]=true; //bed=i1, put i1 on e2
                        NewVec=new D3Dvec;  NewVec->SetVec(x1,y1,z1);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=3; //edge 2
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc4,yc4,zc4);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=3; //edge 4
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc6,yc6,zc6);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=3; tettrinodes[it][5]=4; //edge 6
                        newvecs++;
                   TriDone=true;}}
                 if(!TriDone){
                 if(cuts[4] && cuts[5]){   //cuts edge 5 and 6
                      cuts[2]=true; //bed=i1, put i1 on e3
                        NewVec=new D3Dvec;  NewVec->SetVec(x1,y1,z1);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=4; //edge 3
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc5,yc5,zc5);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=4; //edge 5
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc6,yc6,zc6);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=3; tettrinodes[it][5]=4; //edge 6
                        newvecs++;
                   TriDone=true;}}
                  //cuts on face 2
                 if(!TriDone){
                 if(cuts[1] && cuts[2]){   //cuts edge 2 and 3
                      cuts[0]=true; //bed=i2, put i2 on e1
                        NewVec=new D3Dvec;  NewVec->SetVec(x2,y2,z2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=2; //edge 1
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc2,yc2,zc2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=1; tettrinodes[it][3]=3; //edge 2
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc3,yc3,zc3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=1; tettrinodes[it][5]=4; //edge 3
                        newvecs++;
                   TriDone=true;}}
                 if(!TriDone){
                 if(cuts[1] && cuts[5]){   //cuts edge 2 and 6
                      cuts[3]=true; //bed=i2, put i2 on e4
                        NewVec=new D3Dvec;  NewVec->SetVec(xc2,yc2,zc2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=3; //edge 2
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x2,y2,z2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=3; //edge 4
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc6,yc6,zc6);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=3; tettrinodes[it][5]=4; //edge 6
                        newvecs++;
                   TriDone=true;}}
                 if(!TriDone){
                 if(cuts[2] && cuts[5]){   //cuts edge 3 and 6
                      cuts[4]=true; //bed=i2, put i2 on e5
                        NewVec=new D3Dvec;  NewVec->SetVec(xc3,yc3,zc3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=4; //edge 3
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x2,y2,z2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=4; //edge 5
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc6,yc6,zc6);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=3; tettrinodes[it][5]=4; //edge 6
                        newvecs++;
                   TriDone=true;}}
                  //cuts on face 3
                 if(!TriDone){
                 if(cuts[0] && cuts[2]){   //cuts edge 1 and 3
                      cuts[1]=true; //bed=i3, put i3 on e2
                        NewVec=new D3Dvec;  NewVec->SetVec(xc1,yc1,zc1);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=2; //edge 1
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x3,y3,z3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=1; tettrinodes[it][3]=3; //edge 2
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc3,yc3,zc3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=1; tettrinodes[it][5]=4; //edge 3
                        newvecs++;
                   TriDone=true;}}
                 if(!TriDone){
                 if(cuts[0] && cuts[4]){   //cuts edge 1 and 5
                      cuts[3]=true; //bed=i3, put i3 on e4
                        NewVec=new D3Dvec;  NewVec->SetVec(xc1,yc1,zc1);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=2; //edge 1
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x3,y3,z3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=3; //edge 4
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc5,yc5,zc5);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=2; tettrinodes[it][5]=4; //edge 5
                        newvecs++;
                   TriDone=true;}}
                 if(!TriDone){
                 if(cuts[2] && cuts[4]){   //cuts edge 3 and 5
                      cuts[5]=true; //bed=i3, put i3 on e6
                        NewVec=new D3Dvec;  NewVec->SetVec(xc3,yc3,zc3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=4; //edge 3
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc5,yc5,zc5);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][4]=4; //edge 5
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x3,y3,z3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=3; tettrinodes[it][5]=4; //edge 6
                        newvecs++;
                   TriDone=true;}}
                  //cuts on face 4
                 if(!TriDone){
                 if(cuts[0] && cuts[1]){   //cuts edge 1 and 2
                      cuts[2]=true; //bed=i4, put i4 on e3
                        NewVec=new D3Dvec;  NewVec->SetVec(xc1,yc1,zc1);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=2; //edge 1
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc2,yc2,zc2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=1; tettrinodes[it][4]=3; //edge 2
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x4,y4,z4);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=1; tettrinodes[it][5]=4; //edge 3
                        newvecs++;
                   TriDone=true;}}
                 if(!TriDone){
                 if(cuts[0] && cuts[3]){   //cuts edge 1 and 4
                      cuts[4]=true; //bed=i4, put i4 on e5
                        NewVec=new D3Dvec;  NewVec->SetVec(xc1,yc1,zc1);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=2; //edge 1
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc4,yc4,zc4);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][4]=3; //edge 4
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x4,y4,z4);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=2; tettrinodes[it][5]=4; //edge 5
                        newvecs++;
                   TriDone=true;}}
                 if(!TriDone){
                 if(cuts[1] && cuts[3]){   //cuts edge 2 and 4
                      cuts[5]=true; //bed=i4, put i4 on e6
                        NewVec=new D3Dvec;  NewVec->SetVec(xc2,yc2,zc2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=2; //edge 2
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(xc4,yc4,zc4);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][4]=3; //edge 4
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x4,y4,z4);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=3; tettrinodes[it][5]=4; //edge 6
                   TriDone=true;}}
                 ncuts=3;
              }

              //Remember cuts MUST ARRIVE IN EDGE ORDER
              if(ibed==2 &&  ncuts==1){
                    if(bededge1){  //edge 1 embeded, cut edge 6
                        NewVec=new D3Dvec;  NewVec->SetVec(x1,y1,z1);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=4; //edge 3
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x2,y2,z2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=4;  //edge 5
                        newvecs++;
                        NewVec=new D3Dvec; NewVec->SetVec(xc6,yc6,zc6);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=3; tettrinodes[it][5]=4;  //edge 6
                        newvecs++;
                        cuts[2]=true;  cuts[4]=true;  //cut edges 3 and 5
                     }
                    if(bededge2){  //edge 2
                        NewVec=new D3Dvec;  NewVec->SetVec(x1,y1,z1);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=4; //edge 3
                        newvecs++;
                        NewVec=new D3Dvec; NewVec->SetVec(xc5,yc5,zc5);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=4;  //edge 5
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x3,y3,z3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=3; tettrinodes[it][5]=4;  //edge 6
                        newvecs++;
                        cuts[2]=true;  cuts[5]=true;  //cut edges 3 and 6
                     }
                    if(bededge3){  //edge 3
                        NewVec=new D3Dvec;  NewVec->SetVec(x1,y1,z1);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=2;  //edge 1
                        newvecs++;
                        NewVec=new D3Dvec; NewVec->SetVec(xc4,yc4,zc4);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=3;  //edge 4
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x4,y4,z4); //  edge 5
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=4;  //edge 5
                        newvecs++;
                        cuts[0]=true;  cuts[4]=true;  //cut edges 1 and 5
                     }
                    if(bededge4){  //edge 4
                        NewVec=new D3Dvec; NewVec->SetVec(xc3,yc3,zc3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=4;  //edge 3
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x2,y2,z2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=4;  //edge 5
                        newvecs++;
                        NewVec=new D3Dvec;  NewVec->SetVec(x3,y3,z3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=3; tettrinodes[it][5]=4; //edge 6
                        newvecs++;
                        cuts[4]=true;  cuts[5]=true;  //cut edges 5 and 6
                     }
                    if(bededge5){  //edge 5
                        NewVec=new D3Dvec;  NewVec->SetVec(x2,y2,z2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=2; //edge 1
                        newvecs++;

                        NewVec=new D3Dvec; NewVec->SetVec(xc2,yc2,zc2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=1; tettrinodes[it][3]=3;  //edge 2
                        newvecs++;

                        NewVec=new D3Dvec;  NewVec->SetVec(x4,y4,z4);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=1; tettrinodes[it][5]=4;  //edge 3
                        newvecs++;

                        cuts[0]=true;  cuts[2]=true;  //cut edges 1 and 3
                     }
                    if(bededge6){  //edge 6

                        NewVec=new D3Dvec; NewVec->SetVec(xc2,yc2,zc2);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][0]=newvecs;
                        tettrinodes[it][0]=1; tettrinodes[it][1]=2;  //edge 1
                        newvecs++;

                        NewVec=new D3Dvec;  NewVec->SetVec(x3,y3,z3);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][1]=newvecs;
                        tettrinodes[it][2]=2; tettrinodes[it][3]=3; //edge 4
                        newvecs++;

                        NewVec=new D3Dvec;  NewVec->SetVec(x4,y4,z4);
                        IsoVecs.push_back(NewVec);
                        tetcuts[it][2]=newvecs;
                        tettrinodes[it][4]=2; tettrinodes[it][5]=4; //edge 5
                        newvecs++;
                        cuts[3]=true;  cuts[4]=true;  //cut edges 4 and 5
                     }
                     ncuts=3;
              }

              //  we either have ncuts=3, one triangle, or ncuts=4, two triangles

              //  First call with ncuts=3, remember newvecs has been incremented
              if(ncuts==3){
                  t1=newvecs-3; t2=newvecs-2; t3=newvecs-1;
                  NewTri=new Triangle;
                  NewTri->SetTri(t1,t2,t3);
                  IsoTris.push_back(NewTri);
                  tritetvec.push_back(it);
                  wclev.push_back(currentsurf); idlev.push_back(currentid);
                  newtris++;
//                OK, we have a triangle t1 t2 t3.
                    if(cuts[0] && cuts[1] && cuts[2]){
                        //No cut on face 1
                        icut1=newvecs-2;  icut2=newvecs-1;  //edge 2 to  3
                        ia1=i1; ia2=i3; ib1=i1; ib2=i4;
                        if(in2>=0 && ibededge>0){
                         Swapper(in2, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in2>=0)ireturn=SurfGrow(in2, icut1, icut2, if2, wc, ia1, ia2, ib1, ib2);
                        icut1=newvecs-1;    icut2=newvecs-3;  //edge 3 to 1
                        ia1=i1; ia2=i4; ib1=i1; ib2=i2;
                         if(in3>=0 && ibededge>0){
                         Swapper(in3, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in3>=0)ireturn=SurfGrow(in3, icut1, icut2, if3, wc, ia1, ia2, ib1, ib2);
                        icut1=newvecs-3;  icut2=newvecs-2;   //edge 1 to 2
                        ia1=i1; ia2=i2; ib1=i1; ib2=i3;
                        if(in4>=0 && ibededge>0){
                         Swapper(in4, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in4>=0)ireturn=SurfGrow(in4, icut1, icut2, if4, wc, ia1, ia2, ib1, ib2);
                        return(0);
                     }
                    if(cuts[0] && cuts[3] && cuts[4]){
                         //No no cuts on face 2
                        icut1=newvecs-2;  icut2=newvecs-1; //edge 4 to 5
                        ia1=i2; ia2=i3; ib1=i2; ib2=i4;
                        if(in1>=0 && ibededge>0){
                         Swapper(in1, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in1>=0)ireturn=SurfGrow(in1, icut1, icut2, if1, wc, ia1, ia2, ib1, ib2);
                        icut1=newvecs-1;    icut2=newvecs-3; //edge 5 to 1
                        ia1=i2; ia2=i4; ib1=i1; ib2=i2;
                        if(in3>=0 && ibededge>0){
                         Swapper(in3, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in3>=0)ireturn=SurfGrow(in3, icut1, icut2, if3, wc, ia1, ia2, ib1, ib2);
                        icut1=newvecs-3;  icut2=newvecs-2;  //edge 1 to 4
                        ia1=i1; ia2=i2; ib1=i2; ib2=i3;
                        if(in4>=0 && ibededge>0){
                         Swapper(in4, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in4>=0)ireturn=SurfGrow(in4, icut1, icut2, if4, wc, ia1, ia2, ib1, ib2);
                        return(0);
                     }
                    if(cuts[1] && cuts[3] && cuts[5]){
                         //No cuts on face 3
                        icut1=newvecs-2;  icut2=newvecs-1;  // edge 4 to 6
                        ia1=i2; ia2=i3; ib1=i3; ib2=i4;
                        if(in1>=0 && ibededge>0){
                         Swapper(in1, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in1>=0)ireturn=SurfGrow(in1, icut1, icut2, if1, wc, ia1, ia2, ib1, ib2);
                        icut1=newvecs-1;    icut2=newvecs-3;  //edge 6 to 2
                        ia1=i3; ia2=i4; ib1=i1; ib2=i3;
                        if(in2>=0 && ibededge>0){
                         Swapper(in2, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in2>=0)ireturn=SurfGrow(in2, icut1, icut2, if2, wc, ia1, ia2, ib1, ib2);
                        icut1=newvecs-3;  icut2=newvecs-2;  //edge 2 to 4
                        ia1=i1; ia2=i3; ib1=i2; ib2=i3;
                        if(in4>=0 && ibededge>0){
                         Swapper(in4, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in4>=0)ireturn=SurfGrow(in4, icut1, icut2, if4, wc, ia1, ia2, ib1, ib2);
                        return(0);
                     }
                    if(cuts[2] && cuts[4] && cuts[5]){
                         //no cuts on face 4
                        icut1=newvecs-2;  icut2=newvecs-1; //edge 5 to 6
                        ia1=i2; ia2=i4; ib1=i3; ib2=i4;
                        if(in1>=0 && ibededge>0){
                         Swapper(in1, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in1>=0)ireturn=SurfGrow(in1, icut1, icut2, if1, wc, ia1, ia2, ib1, ib2);
                        icut1=newvecs-1;    icut2=newvecs-3; // edge 6 to 3
                        ia1=i3; ia2=i4; ib1=i1; ib2=i4;
                        if(in2>=0 && ibededge>0){
                         Swapper(in2, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in2>=0)ireturn=SurfGrow(in2, icut1, icut2, if2, wc, ia1, ia2, ib1, ib2);
                        icut1=newvecs-3;  icut2=newvecs-2;  //edge 3 to 5
                        ia1=i1; ia2=i4; ib1=i2; ib2=i4;
                        if(in3>=0 && ibededge>0){
                         Swapper(in3, ibededge,  
                                 ia1, ia2, ib1, ib2, i1, i2, i3, i4, cuts); }
                        if(in3>=0)ireturn=SurfGrow(in3, icut1, icut2, if3, wc, ia1, ia2, ib1, ib2);
                        return(0);
                     }
              }  //endif ncuts=3

              //first call four cuts
              if(ncuts==4){
                  t1=newvecs-4; t2=newvecs-3; t3=newvecs-2, t4=newvecs-1;
                  NewTri=new Triangle;
                  NewTri->SetTri(t1,t2,t3);
                  IsoTris.push_back(NewTri);
                  tritetvec.push_back(it);
                  wclev.push_back(currentsurf); idlev.push_back(currentid);
                  newtris++;
                  NewTri=new Triangle;
                  NewTri->SetTri(t3,t2,t4);
                  IsoTris.push_back(NewTri);
                  tritetvec.push_back(it);
                  wclev.push_back(currentsurf); idlev.push_back(currentid);
                  newtris++;
                 //edge 1 separated from edge 6.
                  if(!cuts[0] && !cuts[5]){
                       icut1=t4; icut2=t3;  //edge 5 to 4
                       ia1=i2; ia2=i4; ib1=i2; ib2=i3;
                       if(in1>=0)ireturn=SurfGrow(in1, icut1, icut2, if1, wc, ia1, ia2, ib1, ib2);
                       icut1=t1; icut2=t2;  //edge 2 to 3
                       ia1=i1; ia2=i3; ib1=i1; ib2=i4;
                       if(in2>=0)ireturn=SurfGrow(in2, icut1, icut2, if2, wc, ia1, ia2, ib1, ib2);
                       icut1=t2; icut2=t4;  //edge 3 to 5
                       ia1=i1; ia2=i4; ib1=i2; ib2=i4;
                       if(in3>=0)ireturn=SurfGrow(in3, icut1, icut2, if3, wc, ia1, ia2, ib1, ib2);
                       icut1=t3; icut2=t1;  //edge 4 to 2
                       ia1=i2; ia2=i3; ib1=i1; ib2=i3;
                       if(in4>=0)ireturn=SurfGrow(in4, icut1, icut2, if4, wc, ia1, ia2, ib1, ib2);
                       return(0);
                  }
                 //edge 2 separated from edge 5
                  if(!cuts[1] && !cuts[4]){
                       icut1=t4; icut2=t3;  //edge 6 to 4
                       ia1=i3; ia2=i4; ib1=i2;  ib2=i3;
                       if(in1>=0)ireturn=SurfGrow(in1, icut1, icut2, if1, wc, ia1, ia2, ib1, ib2);
                       icut1=t2; icut2=t4;  //edge 3 to 6
                       ia1=i1; ia2=i4; ib1=i3; ib2=i4;
                       if(in2>=0)ireturn=SurfGrow(in2, icut1, icut2, if2, wc, ia1, ia2, ib1, ib2);
                       icut1=t1; icut2=t2;  //edge 1 to 3
                       ia1=i1; ia2=i2; ib1=i1; ib2=i4;
                       if(in3>=0)ireturn=SurfGrow(in3, icut1, icut2, if3, wc, ia1, ia2, ib1, ib2);
                       icut1=t3; icut2=t1;  //edge 4 to 1
                       ia1=i2; ia2=i3; ib1=i1; ib2=i2;
                       if(in4>=0)ireturn=SurfGrow(in4, icut1, icut2, if4, wc, ia1, ia2, ib1, ib2);
                       return(0);
                  }
                 //edge 3 separated from edge  4
                  if(!cuts[2] && !cuts[3]){
                       icut1=t4; icut2=t3;  //edge 6 to 5
                       ia1=i3; ia2=i4; ib1=i2; ib2=i4;
                       if(in1>=0)ireturn=SurfGrow(in1, icut1, icut2, if1, wc, ia1, ia2, ib1, ib2);
                       icut1=t2; icut2=t4;  //edge 2 to 6
                       ia1=i1; ia2=i3; ib1=i3; ib2=i4;
                       if(in2>=0)ireturn=SurfGrow(in2, icut1, icut2, if2, wc, ia1, ia2, ib1, ib2);
                       icut1=t3; icut2=t1;  //edge 5 to 1
                       ia1=i2; ia2=i4; ib1=i1; ib2=i2;
                       if(in3>=0)ireturn=SurfGrow(in3, icut1, icut2, if3, wc, ia1, ia2, ib1, ib2);
                       icut1=t1; icut2=t2;  //edge 1 to 2
                       ia1=i1; ia2=i2; ib1=i1; ib2=i3;
                       if(in4>=0)ireturn=SurfGrow(in4, icut1, icut2, if4, wc, ia1, ia2, ib1, ib2);
                       return(0);
                  }

               }
         }     //end test for first call and calc all edges
         //six edges;


         //note we can no longer rely on order
         //we need to know which edges icut1 and icut2 are on!
         //RECURSIVE STARTS HERE
         //

         int returnEx, returnEx2, iedge1=-1, iedge2=-1; 
         //edge3 and possibly edge4 have new cuts
         int ic1,ic2,id1,id2;

         //we are given two nodes (ix1 and ix2) for the icut1, and two nodes (iy1 and iy2) for icut2
         if( ((ix1==i1) && (ix2==i2)) || ((ix1==i2) && (ix2==i1)) )iedge1=1;
         if( ((ix1==i1) && (ix2==i3)) || ((ix1==i3) && (ix2==i1)) )iedge1=2;
         if( ((ix1==i1) && (ix2==i4)) || ((ix1==i4) && (ix2==i1)) )iedge1=3;
         if( ((ix1==i2) && (ix2==i3)) || ((ix1==i3) && (ix2==i2)) )iedge1=4;
         if( ((ix1==i2) && (ix2==i4)) || ((ix1==i4) && (ix2==i2)) )iedge1=5;
         if( ((ix1==i3) && (ix2==i4)) || ((ix1==i4) && (ix2==i3)) )iedge1=6;
         if( ((iy1==i1) && (iy2==i2)) || ((iy1==i2) && (iy2==i1)) )iedge2=1;
         if( ((iy1==i1) && (iy2==i3)) || ((iy1==i3) && (iy2==i1)) )iedge2=2;
         if( ((iy1==i1) && (iy2==i4)) || ((iy1==i4) && (iy2==i1)) )iedge2=3;
         if( ((iy1==i2) && (iy2==i3)) || ((iy1==i3) && (iy2==i2)) )iedge2=4;
         if( ((iy1==i2) && (iy2==i4)) || ((iy1==i4) && (iy2==i2)) )iedge2=5;
         if( ((iy1==i3) && (iy2==i4)) || ((iy1==i4) && (iy2==i3)) )iedge2=6;

         ncuts=0;
         tetcuts[it][0]=icut1;
         if(iedge1==1){tettrinodes[it][0]=1;tettrinodes[it][1]=2;}
         if(iedge1==2){tettrinodes[it][0]=1;tettrinodes[it][1]=3;}
         if(iedge1==3){tettrinodes[it][0]=1;tettrinodes[it][1]=4;}
         if(iedge1==4){tettrinodes[it][0]=2;tettrinodes[it][1]=3;}
         if(iedge1==5){tettrinodes[it][0]=2;tettrinodes[it][1]=4;}
         if(iedge1==6){tettrinodes[it][0]=3;tettrinodes[it][1]=4;}

         tetcuts[it][1]=icut2;
         if(iedge2==1){tettrinodes[it][2]=1;tettrinodes[it][3]=2;}
         if(iedge2==2){tettrinodes[it][2]=1;tettrinodes[it][3]=3;}
         if(iedge2==3){tettrinodes[it][2]=1;tettrinodes[it][3]=4;}
         if(iedge2==4){tettrinodes[it][2]=2;tettrinodes[it][3]=3;}
         if(iedge2==5){tettrinodes[it][2]=2;tettrinodes[it][3]=4;}
         if(iedge2==6){tettrinodes[it][2]=3;tettrinodes[it][3]=4;}

         //we might have a tet node embedded in w=wc
         //indeed icut1 and icut2 might be embedded also
          if(fabs(w1-wc)<Tol){
               bed1=true; ibed++;}
          if(fabs(w2-wc)<Tol){
               bed2=true; ibed++;}
          if(fabs(w3-wc)<Tol){
               bed3=true; ibed++;}
          if(fabs(w4-wc)<Tol){
               bed4=true; ibed++;}
         // we need to know which icut corresponds to which tet nodes
         // must be a better way, moved this check up from if  ncuts==0
         double ex1, why1, zed1;
         double ex2, why2, zed2;

         int corry1=-1; int  corry2=-1;
         if(ibed>0){
         ex1=(IsoVecs.at(icut1))->GetX();
         why1=(IsoVecs.at(icut1))->GetY();
         zed1=(IsoVecs.at(icut1))->GetZ();
         ex2=(IsoVecs.at(icut2))->GetX();
         why2=(IsoVecs.at(icut2))->GetY();
         zed2=(IsoVecs.at(icut2))->GetZ();

         if( (fabs(ex1-x1)<Tol) && (fabs(why1-y1)<Tol)
                && (fabs(zed1-z1)<Tol)   )corry1=i1;
         if( (fabs(ex1-x2)<Tol) && (fabs(why1-y2)<Tol)
                && (fabs(zed1-z2)<Tol)   )corry1=i2;
         if( (fabs(ex1-x3)<Tol) && (fabs(why1-y3)<Tol)
                && (fabs(zed1-z3)<Tol)   )corry1=i3;
         if( (fabs(ex1-x4)<Tol) && (fabs(why1-y4)<Tol)
                && (fabs(zed1-z4)<Tol)   )corry1=i4;

         if( (fabs(ex2-x1)<Tol) && (fabs(why2-y1)<Tol)
                && (fabs(zed2-z1)<Tol)   )corry2=i1;
         if( (fabs(ex2-x2)<Tol) && (fabs(why2-y2)<Tol)
                && (fabs(zed2-z2)<Tol)   )corry2=i2;
         if( (fabs(ex2-x3)<Tol) && (fabs(why2-y3)<Tol)
                && (fabs(zed2-z3)<Tol)   )corry2=i3;
         if( (fabs(ex2-x4)<Tol) && (fabs(why2-y4)<Tol)
                && (fabs(zed2-z4)<Tol)   )corry2=i4;
         }
         // NotCallEdge is true if the calling edge icut1 icut2 is NOT embeded
         bool NotCallEdge=false;
         int ec=-1;  int ic=-1; int cor=-1; int excut; int mycut=-1;
         int GoToNext=-1; int eF=-1; int iF=-1; 
         if(corry1 < 0){
            if(corry2>=0){
                NotCallEdge=true;
                ec=iedge2;  excut=iedge1;
                cor=corry2; mycut=icut1;
         }}
         if(corry2 < 0){
            if(corry1>=0){
                NotCallEdge=true;
                ec=iedge1;  excut=iedge2;
                cor=corry1;  mycut=icut2;
         }} 

/******************************  WORK OUT CUTS ******************************************/

         cuts[0]=false;cuts[1]=false;cuts[2]=false;
         cuts[3]=false;cuts[4]=false;cuts[5]=false;
         if(ifacelook==1){
              //possible cuts on edges 1,2,3
             if( ((wc<=w1-Tol) && (wc >=w2+Tol)) || ((wc>=w1+Tol) && (wc<=w2-Tol)) ){
                   if(fabs(w1-w2)>Tol){
                   wdiff=fabs((w1-wc)/(w2-w1));
                   xc1=x1+wdiff*(x2-x1);yc1=y1+wdiff*(y2-y1);zc1=z1+wdiff*(z2-z1);
                   ncuts++;
                   cuts[0]=true;}}
             if( ((wc<=w1-Tol) && (wc >=w3+Tol)) || ((wc>=w1+Tol) && (wc<=w3-Tol)) ){
                   if(fabs(w3-w1)>Tol){
                   wdiff=fabs((w1-wc)/(w3-w1));
                   xc2=x1+wdiff*(x3-x1);yc2=y1+wdiff*(y3-y1);zc2=z1+wdiff*(z3-z1);
                   ncuts++;
                   cuts[1]=true;}}
             if( ((wc<=w1-Tol) && (wc >=w4+Tol)) || ((wc>=w1+Tol) && (wc<=w4-Tol)) ){
                   if(fabs(w1-w4)>Tol){
                   wdiff=fabs((w1-wc)/(w4-w1));
                   xc3=x1+wdiff*(x4-x1);yc3=y1+wdiff*(y4-y1);zc3=z1+wdiff*(z4-z1);
                   ncuts++;
                   cuts[2]=true;}}
             }
         if(ifacelook==2){
              //possible cuts on edges 1,4,5
             if( ((wc<=w1-Tol) && (wc >=w2+Tol)) || ((wc>=w1+Tol) && (wc<=w2-Tol)) ){
                   if(fabs(w1-w2)>Tol){
                   wdiff=fabs((w1-wc)/(w1-w2));
                   xc1=x1+wdiff*(x2-x1);yc1=y1+wdiff*(y2-y1);zc1=z1+wdiff*(z2-z1);
                   ncuts++;
                   cuts[0]=true;}}
             if( ((wc<=w2-Tol) && (wc >=w3+Tol)) || ((wc>=w2+Tol) && (wc<=w3-Tol)) ){
                   if(fabs(w2-w3)>Tol){
                   wdiff=fabs((w2-wc)/(w2-w3));
                   xc4=x2+wdiff*(x3-x2);yc4=y2+wdiff*(y3-y2);zc4=z2+wdiff*(z3-z2);
                   ncuts++;
                   cuts[3]=true;}}
             if( ((wc<=w2-Tol) && (wc >=w4+Tol)) || ((wc>=w2+Tol) && (wc<=w4-Tol)) ){
                   if(fabs(w2-w4)>Tol){
                   wdiff=fabs((w2-wc)/(w2-w4));
                   xc5=x2+wdiff*(x4-x2);yc5=y2+wdiff*(y4-y2);zc5=z2+wdiff*(z4-z2);
                   ncuts++;
                   cuts[4]=true;}}
             }
         if(ifacelook==3){
              //possible cuts on edges 2,4,6
             if( ((wc<=w1-Tol) && (wc >=w3+Tol)) || ((wc>=w1+Tol) && (wc<=w3-Tol)) ){
                   if(fabs(w1-w3)>Tol){
                   wdiff=fabs((w1-wc)/(w1-w3));
                   xc2=x1+wdiff*(x3-x1);yc2=y1+wdiff*(y3-y1);zc2=z1+wdiff*(z3-z1);
                   ncuts++;
                   cuts[1]=true;}}
             if( ((wc<=w2-Tol) && (wc >=w3+Tol)) || ((wc>=w2+Tol) && (wc<=w3-Tol)) ){
                   if(fabs(w2-w3)>Tol){
                   wdiff=fabs((w2-wc)/(w2-w3));
                   xc4=x2+wdiff*(x3-x2);yc4=y2+wdiff*(y3-y2);zc4=z2+wdiff*(z3-z2);
                   ncuts++;
                   cuts[3]=true;}}
             if( ((wc<=w3-Tol) && (wc >=w4+Tol)) || ((wc>=w3+Tol) && (wc<=w4-Tol)) ){
                   if(fabs(w3-w4)>Tol){
                   wdiff=fabs((w3-wc)/(w3-w4));
                   xc6=x3+wdiff*(x4-x3);yc6=y3+wdiff*(y4-y3);zc6=z3+wdiff*(z4-z3);
                   ncuts++;
                   cuts[5]=true;}}
             }
         if(ifacelook==4){
              //possible cuts on edges 3,5,6
             if( ((wc<=w1-Tol) && (wc >=w4+Tol)) || ((wc>=w1+Tol) && (wc<=w4-Tol)) ){
                   if(fabs(w1-w4)>Tol){
                   wdiff=fabs((w1-wc)/(w1-w4));
                   xc3=x1+wdiff*(x4-x1);yc3=y1+wdiff*(y4-y1);zc3=z1+wdiff*(z4-z1);
                   ncuts++;
                   cuts[2]=true;}}
             if( ((wc<=w2-Tol) && (wc >=w4+Tol)) || ((wc>=w2+Tol) && (wc<=w4-Tol)) ){
                   if(fabs(w2-w4)>Tol){
                   wdiff=fabs((w2-wc)/(w2-w4));
                   xc5=x2+wdiff*(x4-x2);yc5=y2+wdiff*(y4-y2);zc5=z2+wdiff*(z4-z2);
                   ncuts++;
                   cuts[4]=true;}}
             if( ((wc<=w3-Tol) && (wc >=w4+Tol)) || ((wc>=w3+Tol) && (wc<=w4-Tol)) ){
                   if(fabs(w3-w4)>Tol){
                   wdiff=fabs((w3-wc)/(w3-w4));
                   xc6=x3+wdiff*(x4-x3);yc6=y3+wdiff*(y4-y3);zc6=z3+wdiff*(z4-z3);
                   ncuts++;
                   cuts[5]=true;}}
             }
         //cut1 is between ix1 and ix2 etc, using local ia1 and ia2 etc
         ia1=ix1; ia2=ix2; ib1=iy1; ib2=iy2;
         if(ncuts==0){
              bool bededge1, bededge2, bededge3, bededge4, bededge5, bededge6;
              if(bed1 && bed2){bededge1=true;} else {bededge1=false;}
              if(bed1 && bed3){bededge2=true;} else {bededge2=false;}
              if(bed1 && bed4){bededge3=true;} else {bededge3=false;}
              if(bed2 && bed3){bededge4=true;} else {bededge4=false;}
              if(bed2 && bed4){bededge5=true;} else {bededge5=false;}
              if(bed3 && bed4){bededge6=true;} else {bededge6=false;}
              if(ibed==0){
                cout << "Lost in surfgrow" << endl;  exit(1);
              }
              if(ibed==4){
                cout << "Special case not done  in surfgrow" << endl;  exit(1);
              }


                  if(ibed==2){
                    if(NotCallEdge){

                    if(cor==i1)ic=1; if(cor==i2)ic=2;
                    if(cor==i3)ic=3; if(cor==i4)ic=4;
                    if(ifacelook==1)iF=1; if(ifacelook==2)iF=2;
                    if(ifacelook==3)iF=3; if(ifacelook==4)iF=4;
                    GoToNext=-1;
                    if(iF==1){
                    if(excut==4)GoToNext=in4; if(excut==5)GoToNext=in3;
                    if(excut==6)GoToNext=in2;}
                    if(iF==2){
                    if(excut==2)GoToNext=in4; if(excut==3)GoToNext=in3;
                    if(excut==6)GoToNext=in1;}
                    if(iF==3){
                    if(excut==1)GoToNext=in4; if(excut==3)GoToNext=in2;
                    if(excut==5)GoToNext=in1;}
                    if(iF==4){
                    if(excut==1)GoToNext=in3; if(excut==2)GoToNext=in2;
                    if(excut==4)GoToNext=in1;}
                    VarTests(ic, ec, iF, eF);

                        //only one of icut1 icut2 embedded
                        ncuts=0; 
                        bool moved;
                        if(ifacelook==1){
                          moved=false;
                          if(eF==1){
                          xc1=x1; yc1=y1; zc1=z1; cuts[0]=true; moved=true;}
                          if(eF==2){
                          xc2=x1; yc2=y1; zc2=z1; cuts[1]=true; moved=true;} 
                          if(eF==3){
                          xc3=x1; yc3=y1; zc3=z1; cuts[2]=true; moved=true;}
                          if(!moved){cout <<" Failed Move 1\n"; exit(1);}
                        } 
                        if(ifacelook==2){
                          moved=false;
                          if(eF==1){
                          xc1=x2; yc1=y2; zc1=z2; cuts[0]=true; moved=true;}  
                          if(eF==4){
                          xc4=x2; yc4=y2; zc4=z2; cuts[3]=true; moved=true;} 
                          if(eF==5){
                          xc5=x2; yc5=y2; zc5=z2; cuts[4]=true; moved=true;}
                          if(!moved){cout <<" Failed Move 2\n"; exit(1);}
                        }
                        if(ifacelook==3){
                          moved=false;
                          if(eF==2){
                          xc2=x3; yc2=y3; zc2=z3; cuts[1]=true; moved=true;}
                          if(eF==4){
                          xc4=x3; yc4=y3; zc4=z3; cuts[3]=true; moved=true;}
                          if(eF==6){
                          xc6=x3; yc6=y3; zc6=z3; cuts[5]=true; moved=true;}
                          if(!moved){cout <<" Failed Move 3\n"; exit(1);}
                        }
                        if(ifacelook==4){
                          moved=false;
                          if(eF==3){
                          xc3=x4; yc3=y4; zc3=z4; cuts[2]=true; moved=true;}
                          if(eF==5){
                          xc5=x4; yc5=y4; zc5=z4; cuts[4]=true; moved=true;}
                          if(eF==6){
                          xc6=x4; yc6=y4; zc6=z4; cuts[5]=true; moved=true;}
                        }
                        ncuts=1;
                    }}  //endif ibed=2, NotCallEdge
              if(ibed==3){
              //All we need to do is set ncuts to one,
              //and give the new vector and triangle code that follows
              //later values for cuts[] and  (xc,yc,zc)
              //face 1 cut
              
              ncuts=1;

              if(ifacelook==1){
              if( (iedge1==4 && iedge2==5) ||  (iedge1==5 && iedge2==4) ){
                  cuts[0]=true;  //edge 1
                  xc1=x1; yc1=y1; zc1=z1;  //new triangle on face face 2
                  if(in2>=0)Done[in2][id]=true;
              } 
              if( (iedge1==4 && iedge2==6) ||  (iedge1==6 && iedge2==4) ){
                  cuts[1]=true;  //  edge 2
                  xc2=x1; yc2=y1; zc2=z1;  //new triangle on face face 3
                  if(in3>=0)Done[in3][id]=true;
              } 
              if( (iedge1==5 && iedge2==6) ||  (iedge1==6 && iedge2==5) ){
                  cuts[2]=true; //  edge 3
                  xc3=x1; yc3=y1; zc3=z1;  //new triangle on face face 4
                  if(in4>=0)Done[in4][id]=true;
                  
              } } 
               
              //face 2 cut
              if(ifacelook==2){
              if( (iedge1==2 && iedge2==3) ||  (iedge1==3 && iedge2==2) ){
                  cuts[0]=true;  //edge 1
                  xc1=x2; yc1=y2; zc1=z2; //new triangle on face face 1
                  if(in2>=0)Done[in2][id]=true;
              } 
              if( (iedge1==2 && iedge2==6) ||  (iedge1==6 && iedge2==2) ){
                  cuts[3]=true;  //edge 4
                  xc4=x2; yc4=y2; zc4=z2;  //new triangle on face face 3
                  if(in3>=0)Done[in3][id]=true;
              } 
              if( (iedge1==3 && iedge2==6) ||  (iedge1==6 && iedge2==3) ){
                  cuts[4]=true;  //edge 5
                  xc5=x2; yc5=y2; zc5=z2;  //new triangle on face face 4
                  if(in4>=0)Done[in4][id]=true;
              } }
               
              //face 3 cut
              if(ifacelook==3){
              if( (iedge1==1 && iedge2==3) ||  (iedge1==3 && iedge2==1) ){
                  cuts[1]=true;  //edge 2
                  xc2=x3; yc2=y3; zc2=z3;  //new triangle on face face 1
                  if(in1>=0)Done[in1][id]=true;
              } 
              if( (iedge1==1 && iedge2==5) ||  (iedge1==5 && iedge2==1) ){
                  cuts[3]=true;  //edge 4
                  xc4=x3; yc4=y3; zc4=z3;  //new triangle on face face 2
                  if(in2>=0)Done[in2][id]=true;
              } 
              if( (iedge1==3 && iedge2==5) ||  (iedge1==5 && iedge2==3) ){
                  cuts[5]=true;  //edge 6
                  xc6=x3; yc6=y3; zc6=z3;  //new triangle on face face 4
                  if(in4>=0)Done[in4][id]=true;
              } }
              //face 4 cut
              if(ifacelook==4){
              if( (iedge1==1 && iedge2==2) ||  (iedge1==2 && iedge2==1) ){
                  cuts[2]=true;  //edge 3
                  xc3=x4; yc3=y4; zc3=z4; //new triangle on face face 1
                  if(in1>=0)Done[in1][id]=true;
              } 
              if( (iedge1==1 && iedge2==4) ||  (iedge1==4 && iedge2==1) ){
                  cuts[4]=true;  //edge 5
                  xc5=x4; yc5=y4; zc5=z4; //new triangle on face face 2
                  if(in2>=0)Done[in2][id]=true;
              } 
              if( (iedge1==2 && iedge2==4) ||  (iedge1==4 && iedge2==2) ){
                  cuts[5]=true;  //edge 6
                  xc6=x4; yc6=y4; zc6=z4; //new triangle on face face 3
                  if(in3>=0)Done[in3][id]=true;
              } }
              }  //endif ibed=3

              if(ibed==1){
                bool TriDone=false;
               //cuts on face 1
                if(!TriDone){
                if( ((iedge1==4) && (iedge2==5)) || ((iedge1==5) && (iedge2==4)) ){
                  cuts[0]=true;
                  xc1=x1; yc1=y1; zc1=z1;
                  TriDone=true;  }}
                if(!TriDone){
                if( ((iedge1==4) && (iedge2==6)) || ((iedge1==6) && (iedge2==4)) ){
                  cuts[1]=true;
                  xc2=x1; yc2=y1; zc2=z1;
                  TriDone=true;  }}
                if(!TriDone){
                if( ((iedge1==5) && (iedge2==6)) || ((iedge1==6) && (iedge2==5)) ){
                  cuts[2]=true;
                  xc3=x1; yc3=y1; zc3=z1;
                  TriDone=true;  }}
               //cuts on face 2
                if(!TriDone){
                if( ((iedge1==2) && (iedge2==3)) || ((iedge1==3) && (iedge2==2)) ){
                  cuts[0]=true;
                  xc1=x2; yc1=y2; zc1=z2;
                  TriDone=true;  }}
                if(!TriDone){
                if( ((iedge1==2) && (iedge2==6)) || ((iedge1==6) && (iedge2==2)) ){
                  cuts[3]=true;
                  xc4=x2; yc4=y2; zc4=z2;
                  TriDone=true;  }}
                if(!TriDone){
                if( ((iedge1==3) && (iedge2==6)) || ((iedge1==6) && (iedge2==3)) ){
                  cuts[4]=true;
                  xc5=x2; yc5=y2; zc5=z2;
                  TriDone=true;  }}
               //cuts on face 3
                if(!TriDone){
                if( ((iedge1==1) && (iedge2==3)) || ((iedge1==3) && (iedge2==1)) ){
                  cuts[1]=true;
                  xc2=x3; yc2=y3; zc2=z3;
                  TriDone=true;  }}
                if(!TriDone){
                if( ((iedge1==1) && (iedge2==5)) || ((iedge1==5) && (iedge2==1)) ){
                  cuts[3]=true;
                  xc4=x3; yc4=y3; zc4=z3;
                  TriDone=true;  }}
                if(!TriDone){
                if( ((iedge1==3) && (iedge2==5)) || ((iedge1==5) && (iedge2==3)) ){
                  cuts[5]=true;
                  xc6=x3; yc6=y3; zc6=z3;
                  TriDone=true;  }}
               //cuts on face 4
                if(!TriDone){
                if( ((iedge1==1) && (iedge2==2)) || ((iedge1==2) && (iedge2==1)) ){
                  cuts[2]=true;
                  xc3=x4; yc3=y4; zc3=z4;
                  TriDone=true;  }}
                if(!TriDone){
                if( ((iedge1==1) && (iedge2==4)) || ((iedge1==4) && (iedge2==1)) ){
                  cuts[4]=true;
                  xc5=x4; yc5=y4; zc5=z4;
                  TriDone=true;  }}
                if(!TriDone){
                if( ((iedge1==2) && (iedge2==4)) || ((iedge1==4) && (iedge2==2)) ){
                  cuts[5]=true;
                  xc6=x4; yc6=y4; zc6=z4;
                  TriDone=true;  }}
                  ncuts=1;
              }  //endif ibed==1



              if(ibed==2){
                 // need to roll about axis til we find a cut
                 if( (corry1>=0) && corry2>=0){
                   //This means there are no cuts, AND no third embedded node
                   //There MUST be a triangle in a neighbour instead!
                   if(ifacelook==1){
                      if( (iedge1==4 && iedge2==5) || (iedge1==5 && iedge2==4)){
                         if1=(int)Tets[it].GetC2();
                         // edge 4, 5-> 2, 3
                         if(iedge1==4){
                            ia1=i1; ia2=i3; ib1=i1, ib2=i4;}
                            else{
                            ia1=i1; ia2=i4; ib1=i1, ib2=i3;}
                            ireturn=SurfGrow(in2,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                      if( (iedge1==4 && iedge2==6) || (iedge1==6 && iedge2==4)){
                         if1=(int)Tets[it].GetC3();
                         // edge 4, 6-> 1, 3
                         if(iedge1==4){
                            ia1=i1; ia2=i2; ib1=i1, ib2=i4;}
                            else{
                            ia1=i1; ia2=i4; ib1=i1, ib2=i2;}
                            ireturn=SurfGrow(in3,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                      if( (iedge1==5 && iedge2==6) || (iedge1==6 && iedge2==5)){
                         if1=(int)Tets[it].GetC4();
                         // edge 5, 6-> 1, 2
                         if(iedge1==5){
                            ia1=i1; ia2=i2; ib1=i1, ib2=i3;}
                            else{
                            ia1=i1; ia2=i3; ib1=i1, ib2=i2;}
                            ireturn=SurfGrow(in4,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                   }  //endif ifacelook=1

                   if(ifacelook==2){
                      if( (iedge1==2 && iedge2==3) || (iedge1==3 && iedge2==2)){
                         if1=(int)Tets[it].GetC1();
                         // edge 2, 3-> 4, 5
                         if(iedge1==2){
                            ia1=i2; ia2=i3; ib1=i2, ib2=i4;}
                            else{
                            ia1=i2; ia2=i4; ib1=i2, ib2=i3;}
                            ireturn=SurfGrow(in1,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                      if( (iedge1==2 && iedge2==6) || (iedge1==6 && iedge2==2)){
                         if1=(int)Tets[it].GetC3();
                         // edge 2, 6-> 1, 5
                         if(iedge1==2){
                            ia1=i1; ia2=i2; ib1=i2, ib2=i4;}
                            else{
                            ia1=i2; ia2=i4; ib1=i1, ib2=i2;}
                            ireturn=SurfGrow(in3,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                      if( (iedge1==3 && iedge2==6) || (iedge1==6 && iedge2==3)){
                         if1=(int)Tets[it].GetC4();
                         // edge 3, 6-> 1, 4
                         if(iedge1==3){
                            ia1=i1; ia2=i2; ib1=i2, ib2=i3;}
                            else{
                            ia1=i2; ia2=i3; ib1=i1, ib2=i2;}
                            ireturn=SurfGrow(in4,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                   }  //endif ifacelook=2

                   if(ifacelook==3){
                      if( (iedge1==1 && iedge2==3) || (iedge1==3 && iedge2==1)){
                        if1=(int)Tets[it].GetC1();
                         // edge 1, 3-> 4, 6
                         if(iedge1==1){
                            ia1=i2; ia2=i3; ib1=i3, ib2=i4;}
                            else{
                            ia1=i3; ia2=i4; ib1=i2, ib2=i3;}
                            ireturn=SurfGrow(in1,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                      if( (iedge1==1 && iedge2==5) || (iedge1==5 && iedge2==1)){
                         if1=(int)Tets[it].GetC2();
                         // edge 1, 5-> 2, 6
                         if(iedge1==1){
                            ia1=i1; ia2=i3; ib1=i3, ib2=i4;}
                            else{
                            ia1=i3; ia2=i4; ib1=i1, ib2=i3;}
                            ireturn=SurfGrow(in2,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                      if( (iedge1==3 && iedge2==5) || (iedge1==5 && iedge2==3)){
                         if1=(int)Tets[it].GetC4();
                         // edge 3, 5-> 2, 4
                         if(iedge1==3){
                            ia1=i1; ia2=i3; ib1=i2, ib2=i3;}
                            else{
                            ia1=i2; ia2=i3; ib1=i1, ib2=i3;}
                            ireturn=SurfGrow(in4,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                   }  //endif ifacelook=3

                   if(ifacelook==4){
                      if( (iedge1==1 && iedge2==2) || (iedge1==2 && iedge2==1)){
                         if1=(int)Tets[it].GetC1();
                         // edge 1, 2-> 5, 6
                         if(iedge1==1){
                            ia1=i2; ia2=i4; ib1=i3, ib2=i4;}
                            else{
                            ia1=i3; ia2=i4; ib1=i2, ib2=i4;}
                            ireturn=SurfGrow(in1,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                      if( (iedge1==1 && iedge2==4) || (iedge1==4 && iedge2==1)){
                         if1=(int)Tets[it].GetC2();
                         // edge 1, 4-> 3, 6
                         if(iedge1==1){
                            ia1=i1; ia2=i4; ib1=i3, ib2=i4;}
                            else{
                            ia1=i3; ia2=i4; ib1=i1, ib2=i4;}
                            ireturn=SurfGrow(in2,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                      if( (iedge1==2 && iedge2==4) || (iedge1==4 && iedge2==2)){
                         if1=(int)Tets[it].GetC3();
                         // edge 2, 4-> 3, 5
                         if(iedge1==2){
                            ia1=i1; ia2=i4; ib1=i2, ib2=i4;}
                            else{
                            ia1=i2; ia2=i4; ib1=i1, ib2=i4;}
                            ireturn=SurfGrow(in3,icut1,icut2,if1,wc,ia1,ia2,ib1,ib2);
                      }
                   }  //endif ifacelook=4
                 } //endif both corry > 0
              }  //endif ibed=2
         }  //endif for ncuts=0

         if(ncuts==1){

             if(ibed==1){
                // in this case the corresponding iedge might need to be changed
                if( (corry1 >0) || (corry2>0) ){
                //two genuine cuts on face 1 
                if( (cuts[3] && (excut==5)) || ((excut==4) && cuts[4])){  // edge 4 edge 5
                     if(corry1 !=-1){iedge1=1;} else {iedge2=1;}}
                if( (cuts[3] && (excut==6)) || ((excut==4) && cuts[5]) ){  // edge 4 edge 6
                     if(corry1 !=-1){iedge1=2;} else {iedge2=2;}}
                if( (cuts[4] && (excut==6)) || ((excut==5) && cuts[5]) ){  // edge 5 edge 6
                     if(corry1 !=-1){iedge1=3;} else {iedge2=3;}}
                //two genuine cuts on face 2
                if( (cuts[1] && (excut==3)) || ((excut==2) && cuts[2]) ){  // edge 2 edge 3
                     if(corry1 !=-1){iedge1=1;} else {iedge2=1;}}
                if( (cuts[1] && (excut==6)) || ((excut==2) && cuts[5]) ){  // edge 2 edge 6
                     if(corry1 !=-1){iedge1=4;} else {iedge2=4;}}
                if( (cuts[2] && (excut==6)) || ((excut==3) && cuts[5]) ){  // edge 3 edge 6
                     if(corry1 !=-1){iedge1=5;} else {iedge2=5;}}
                //two genuine cuts on face 3
                if( (cuts[0] && (excut==3)) || ((excut==1) && cuts[2]) ){  // edge 1 edge 3
                     if(corry1 !=-1){iedge1=2;} else {iedge2=2;}}
                if( (cuts[0] && (excut==5)) || ((excut==1) && cuts[4]) ){  // edge 1 edge 5
                     if(corry1 !=-1){iedge1=4;} else {iedge2=4;}}
                if( (cuts[2] && (excut==5)) || ((excut==3) && cuts[4]) ){  // edge 3 edge 5
                     if(corry1 !=-1){iedge1=6;} else {iedge2=6;}}
                //two genuine cuts on face 4
                if( (cuts[0] && (excut==2)) || ((excut==1) && cuts[1]) ){  // edge 1 edge 2
                     if(corry1 !=-1){iedge1=3;} else {iedge2=3;}}
                if( (cuts[0] && (excut==4)) || ((excut==1) && cuts[3]) ){  // edge 1 edge 4
                     if(corry1 !=-1){iedge1=5;} else {iedge2=5;}}
                if( (cuts[1] && (excut==4)) || ((excut==2) && cuts[3]) ){  // edge 2 edge 4
                     if(corry1 !=-1){iedge1=6;} else {iedge2=6;}}

                if(iedge1==1){ia1=i1; ia2=i2;} if(iedge2==1){ib1=i1; ib2=i2;}
                if(iedge1==2){ia1=i1; ia2=i3;} if(iedge2==2){ib1=i1; ib2=i3;}
                if(iedge1==3){ia1=i1; ia2=i4;} if(iedge2==3){ib1=i1; ib2=i4;}
                if(iedge1==4){ia1=i2; ia2=i3;} if(iedge2==4){ib1=i2; ib2=i3;}
                if(iedge1==5){ia1=i2; ia2=i4;} if(iedge2==5){ib1=i2; ib2=i4;}
                if(iedge1==6){ia1=i3; ia2=i4;} if(iedge2==6){ib1=i3; ib2=i4;}
             }}  //endif ibed==1  and one of corrys not -1

/**************************    FACE 1 ALREADY CUT       ***********************************/
             if(ifacelook==1){  //This face is already cut, possible cuts on edge 1 2 and 3.
                if(cuts[0]){
                   //new cut is on face 4 face 3  
                   ic1=i1; ic2=i2; iface1=4; iface2=3;
                   if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC3();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   //GetExists looks on the two neighbours iface1 and iface2
                   //it makes a triangle icut2 icut1 returnEx of returnEx
                   //exists. The order of faces does NOT matter
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc1,yc1,zc1);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==4){
                   ireturn=SurfGrow(in4,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2 );
                   ireturn=SurfGrow(in3,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2 );
                   }
                   else{
                   ireturn=SurfGrow(in3,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2 );
                   ireturn=SurfGrow(in4,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2 );
                   }
                }
                if(cuts[1]){
                   //new cut is on face 4 face 2
                   ic1=i1; ic2=i3; iface1=4; iface2=2;
                   if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC2();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc2,yc2,zc2);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==4){
                   ireturn=SurfGrow(in4,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in2,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2);
                    }
                   else{
                   ireturn=SurfGrow(in2,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in4,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }
                }
                if(cuts[2]){
                   //new cut is on face 3 face 2
                   ic1=i1; ic2=i4; iface1=3;  iface2=2;
                   if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC2();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc3,yc3,zc3);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==5){
                   ireturn=SurfGrow(in3,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in2,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2);
                   }
                   else{
                   ireturn=SurfGrow(in2,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in3,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }
                }
             }  //endif face one already cut
/**************************    FACE 2 ALREADY CUT       ***********************************/
            if(ifacelook==2){  //This face is already cut.  
                //possibles are one more cut on edge 1, 4, or 5.
                if(cuts[0]){
                   //new cut is on face 4 face 3
                   ic1=i1; ic2=i2; iface1=4; iface2=3;
                   if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC3();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc1,yc1,zc1);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==2){
                   ireturn=SurfGrow(in4,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in3,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2);
                   }
                   else{
                   ireturn=SurfGrow(in3,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in4,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }
                }
                if(cuts[3]){
                   //new cut is on face 4 face 1
                   ic1=i2; ic2=i3; iface1=4; iface2=1;
                   if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC1();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc4,yc4,zc4);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==2){
                   ireturn=SurfGrow(in4,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in1,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2);
                   }
                   else{
                   ireturn=SurfGrow(in1,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in4,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }
                }
                if(cuts[4]){
                   //new cut is on face 3 face 1
                   ic1=i2; ic2=i4; iface1=3;  iface2=1;
                   if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC1();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc5,yc5,zc5);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==3){
                   ireturn=SurfGrow(in3,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in1,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2); 
                   }
                   else{
                   ireturn=SurfGrow(in1,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in3,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }
                }
             }  //endif face two already cut
/**************************    FACE 3 ALREADY CUT       ***********************************/
            if(ifacelook==3){  //This face is already cut. 
                //possibles are one more cut on edge 2, 4, or 6.
                if(cuts[1]){
                   //new cut is on face 4 face 2
                   ic1=i1; ic2=i3; iface1=4; iface2=2;
                   if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC2();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc2,yc2,zc2);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==1){
                   ireturn=SurfGrow(in4,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in2,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2);
                   }
                   else{
                   ireturn=SurfGrow(in2,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in4,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }
                }
                if(cuts[3]){
                   //new cut is on face 4 face 1
                   ic1=i2; ic2=i3; iface1=4; iface2=1;
                   if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC1();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc4,yc4,zc4);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==1){
                   ireturn=SurfGrow(in4,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in1,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2);
                   }
                   else{
                   ireturn=SurfGrow(in1,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in4,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }
                }
                if(cuts[5]){
                   //new cut is on face 2 face 1
                   ic1=i3; ic2=i4; iface1=2;  iface2=1;
                   if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC1();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc6,yc6,zc6);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==3){
                   ireturn=SurfGrow(in2,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in1,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2);
                   }
                   else{
                   ireturn=SurfGrow(in1,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in2,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }
                }
             }  //endif face three already cut

/**************************    FACE 4 ALREADY CUT       ***********************************/
            if(ifacelook==4){  //This face is already cut.  
                //possibles are one more cut on edge 3, 5, or 6.
                if(cuts[2]){
                   //new cut is on face 3 face 2
                   ic1=i1; ic2=i4; iface1=3; iface2=2;
                   if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC2();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc3,yc3,zc3);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==1){
                   ireturn=SurfGrow(in3,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in2,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2);
                   }
                   else{
                   ireturn=SurfGrow(in2,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in3,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }
                }
                if(cuts[4]){
                   //new cut is on face 3 face 1
                   ic1=i2; ic2=i4; iface1=3; iface2=1;
                   if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC1();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc5,yc5,zc5);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                   if(iedge1==1){
                   ireturn=SurfGrow(in3,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in1,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2);
                   }
                   else{
                   ireturn=SurfGrow(in1,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in3,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }
                }
                if(cuts[5]){
                   //new cut is on face 2 face 1
                   ic1=i3; ic2=i4; iface1=2;  iface2=1;
                   if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC1();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                   if(returnEx<0){
                   NewVec=new D3Dvec;
                   NewVec->SetVec(xc6,yc6,zc6);  IsoVecs.push_back(NewVec);
                   newvecs++; 
                   NewTri=new Triangle;   NewTri->SetTri(icut2,icut1,newvecs-1);
                   IsoTris.push_back(NewTri);
                   tritetvec.push_back(it);
                   wclev.push_back(currentsurf); idlev.push_back(currentid);
                   newtris++;
                   returnEx=newvecs-1;}
                    if(iedge1==2){
                   ireturn=SurfGrow(in2,icut1,returnEx,if1,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in1,returnEx,icut2,if2,wc, ic1, ic2, ib1, ib2);
                   }
                   else{
                   ireturn=SurfGrow(in1,icut1,returnEx,if2,wc, ia1, ia2, ic1, ic2);
                   ireturn=SurfGrow(in2,returnEx,icut2,if1,wc, ic1, ic2, ib1, ib2);
                   }

                }
             }  //endif face four already cut



          }  //endif ncuts=1
          //   Two new triangles needed!
          if(ncuts==2){  //see Fig 6
                  if(ifacelook==1){
                  //FACE 1 ALREADY CUT  (See Fig 6 as well as 3 4 and 5)
                  if(cuts[1] && cuts[2]){  //edges 2 and 3  (Fig3)
                   ic1=i1; ic2=i3; iface1=4; iface2=2;
                   if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC2();
                   tetstart=it;
                   returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                   if(returnEx==-2){  //failed to get round!
                      returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc2,yc2,zc2);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i1; id2=i4; iface1=2; iface2=3;
                     if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC3();
                     if(iedge1==4){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                     }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc3,yc3,zc3);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==4){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC3(); if3=(int)Tets[it].GetC4();
                     if(iedge1==4){
                     ireturn=SurfGrow(in2,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in3,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in4,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in2,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in3,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in4,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                  } //endif edges  2 & 3 
                  if(cuts[0] && cuts[2]){  //edges 1 and 3  (Fig4)
                     ic1=i1; ic2=i2; iface1=4; iface2=3;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC3();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc1,yc1,zc1);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i1; id2=i4; iface1=2; iface2=3;
                     if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC3();
                     if(iedge1==4){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                     }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc3,yc3,zc3);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==4){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC2(); if3=(int)Tets[it].GetC4();
                     if(iedge1==4){
                     ireturn=SurfGrow(in3,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in2,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in4,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in3,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in2,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in4,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                  } // endif edges 1 & 3

                  if(cuts[0] && cuts[1]){  //edges 1 and 2   Fig5
                     ic1=i1; ic2=i2; iface1=4; iface2=3;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC3();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc1,yc1,zc1);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i1; id2=i3; iface1=4; iface2=2;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC2();
                     if(iedge1==5){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                     }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc2,yc2,zc2);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==5){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC2(); if3=(int)Tets[it].GetC3();
                     if(iedge1==5){
                     ireturn=SurfGrow(in4,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in2,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in3,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in4,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in2,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in3,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                     }  //endif  edges   1 & 2
                  }  //endif for ifacelook==1
      //***************************************************************************************
                  //FACE 2 ALREADY CUT  (See Fig 6 as well as 3 4 and 5)
                  if(ifacelook==2){
                  if(cuts[3] && cuts[4]){  //edges 4 and 5  Fig3
                     ic1=i2; ic2=i3; iface1=4; iface2=1;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC1();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc4,yc4,zc4);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i2; id2=i4; iface1=3; iface2=1;
                     if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC1();
                     if(iedge1==2){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                     }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc5,yc5,zc5);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==2){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC1(); if2=(int)Tets[it].GetC3(); if3=(int)Tets[it].GetC4();
                     if(iedge1==2){
                     ireturn=SurfGrow(in1,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in3,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in4,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in1,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in3,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in4,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);
                     }
                  }  //endif edges  4 & 5
                  if(cuts[0] && cuts[3]){  //edges 1 and 4  Fig4
                     ic1=i1; ic2=i2; iface1=4; iface2=3;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC3();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc1,yc1,zc1);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i2; id2=i3; iface1=4; iface2=1;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC1();
                     if(iedge1==3){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                     }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc4,yc4,zc4);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==3){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC1(); if3=(int)Tets[it].GetC3();
                     if(iedge1==3){
                     ireturn=SurfGrow(in4,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in1,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in3,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in4,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in1,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in3,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                  }  //endif edges  1 & 4
                  if(cuts[0] && cuts[4]){  //edges 1 and 5  Fig5
                     ic1=i1; ic2=i2; iface1=4; iface2=3;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC3();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc1,yc1,zc1);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i2; id2=i4; iface1=3; iface2=1;
                     if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC1();
                     if(iedge1==2){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                     }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc5,yc5,zc5);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==2){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC1(); if3=(int)Tets[it].GetC4();
                     if(iedge1==2){
                     ireturn=SurfGrow(in3,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in1,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in4,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in3,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in1,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in4,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                  }  //endif edges  1 & 5
                  }  //endif ifacelook==2
      //***************************************************************************************
                  //FACE 3 ALREADY CUT  (See Fig 6 as well as 3 4 and 5)
                  if(ifacelook==3){
                  if(cuts[1] && cuts[3]){  //edges 2 and 4  Fig3
                     ic1=i1; ic2=i3; iface1=4; iface2=2;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC2();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc2,yc2,zc2);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i2; id2=i3; iface1=4; iface2=1;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC1();
                     if(iedge1==3){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                     }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc4,yc4,zc4);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==3){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC1(); if3=(int)Tets[it].GetC2();
                     if(iedge1==3){
                     ireturn=SurfGrow(in4,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in1,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in2,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in4,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in1,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in2,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                  }  //endif edges  2 & 4
                  if(cuts[3] && cuts[5]){  //edges 4 and 6  Fig4
                     ic1=i2; ic2=i3; iface1=4; iface2=1;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC1();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc4,yc4,zc4);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i3; id2=i4; iface1=2; iface2=1;
                     if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC1();
                     if(iedge1==1){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                      }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                      }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc6,yc6,zc6);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==1){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC1(); if2=(int)Tets[it].GetC2(); if3=(int)Tets[it].GetC4();
                     if(iedge1==1){
                     ireturn=SurfGrow(in1,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in2,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in4,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in1,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in2,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in4,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                  }  //endif edges  4 & 6
                  if(cuts[1] && cuts[5]){  //edges 2 and 6  Fig5
                     ic1=i1; ic2=i3; iface1=4; iface2=2;
                     if1=(int)Tets[it].GetC4(); if2=(int)Tets[it].GetC2();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc2,yc2,zc2);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i3; id2=i4; iface1=2; iface2=1;
                     if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC1();
                     if(iedge1==1){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                      }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc6,yc6,zc6);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==1){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC1(); if3=(int)Tets[it].GetC4();
                     if(iedge1==1){
                     ireturn=SurfGrow(in2,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in1,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in4,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in2,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in1,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in4,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                  }  //endif edges 2 & 6
                  }  //endif ifacelook==3
      //***************************************************************************************
                  //FACE 4 ALREADY CUT  (See Fig 6 as well as 3 4 and 5)
                  if(ifacelook==4){
                  if(cuts[2] && cuts[4]){  //edges 3 and 5  Fig3
                     ic1=i1; ic2=i4; iface1=3; iface2=2;
                     if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC2();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc3,yc3,zc3);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i2; id2=i4; iface1=3; iface2=1;
                     if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC1();
                     if(iedge1==2){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                     }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc5,yc5,zc5);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==2){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC1(); if3=(int)Tets[it].GetC2();
                     if(iedge1==2){
                     ireturn=SurfGrow(in3,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in1,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in2,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in3,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in1,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in2,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                  }  //endif edges  3 & 5
                  if(cuts[2] && cuts[5]){  //edges 3 and 6  Fig4
                     ic1=i1; ic2=i4; iface1=3; iface2=2;
                     if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC2();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc3,yc3,zc3);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i3; id2=i4; iface1=2; iface2=1;
                     if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC1();
                     if(iedge1==1){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                     }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc6,yc6,zc6);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==1){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC1(); if3=(int)Tets[it].GetC3();
                     if(iedge1==1){
                     ireturn=SurfGrow(in2,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in1,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in3,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in2,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in1,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in3,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                  }  //endif edges  3 & 6
                  if(cuts[4] && cuts[5]){  //edges 5 and 6  Fig5
                     ic1=i2; ic2=i4; iface1=3; iface2=1;
                     if1=(int)Tets[it].GetC3(); if2=(int)Tets[it].GetC1();
                     tetstart=it;
                     returnEx=GetExists(it, if1, iface1, ic1, ic2, icut1, icut2);
                     if(returnEx==-2){  //failed to get round!
                        returnEx=GetExists(it, if2, iface2, ic1, ic2, icut1, icut2);}
                     //if returnEx already exists, GetExists will set a new
                     //triangle icut2,icut1,returnEx, if not we make one!
                     if(returnEx<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc5,yc5,zc5);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     NewTri->SetTri(icut2,icut1,newvecs-1);
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx=newvecs-1;}
                     id1=i3; id2=i4; iface1=2; iface2=1;
                     if1=(int)Tets[it].GetC2(); if2=(int)Tets[it].GetC1();
                     if(iedge1==1){
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, returnEx, icut2);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, returnEx, icut2);}
                      }
                     else{
                       tetstart=it;
                       returnEx2=GetExists(it, if1, iface1, id1, id2, icut1, returnEx);
                       if(returnEx2==-2){  //failed to get round!
                       returnEx2=GetExists(it, if2, iface2, id1, id2, icut1, returnEx);}
                     }
                     if(returnEx2<0){
                     NewVec=new D3Dvec;
                     NewVec->SetVec(xc6,yc6,zc6);  IsoVecs.push_back(NewVec);
                     newvecs++; 
                     NewTri=new Triangle;
                     if(iedge1==1){
                     NewTri->SetTri(icut2,returnEx,newvecs-1);}
                     else{
                     NewTri->SetTri(returnEx,icut1,newvecs-1);}
                     IsoTris.push_back(NewTri);
                     tritetvec.push_back(it);
                     wclev.push_back(currentsurf); idlev.push_back(currentid);
                     newtris++;
                     returnEx2=newvecs-1;}
                     if1=(int)Tets[it].GetC1(); if2=(int)Tets[it].GetC2(); if3=(int)Tets[it].GetC3();
                     if(iedge1==1){
                     ireturn=SurfGrow(in1,returnEx,returnEx2,if1,wc, ic1, ic2, id1, id2);
                     ireturn=SurfGrow(in2,returnEx2,icut2,   if2,wc, id1, id2, ib1, ib2);
                     ireturn=SurfGrow(in3,icut1,returnEx,    if3,wc, ia1, ia2, ic1, ic2);
                     return(0);}
                     else{
                     ireturn=SurfGrow(in1,returnEx2,returnEx,if1,wc, id1, id2, ic1, ic2);
                     ireturn=SurfGrow(in2,icut1,returnEx2,   if2,wc, ia1, ia2, id1, id2);
                     ireturn=SurfGrow(in3,returnEx,icut2,    if3,wc, ic1, ic2, ib1, ib2);
                     return(0);}
                  }  //endif edges 5 & 6
                  }  //endif ifacelook==4
                  
             }  //endif ncuts=2

      return(0);
}
int GetExists(int it, int ifacecall, int iface, int  iend1, int iend2, int icut1, int icut2){
    int tet;
    int *ptrN; 
    tet=-1; ptrN=NULL;
    int myreturn=-1100;

    if(iface==1)ptrN=Tets[it].GetN1();if(iface==2)ptrN=Tets[it].GetN2();
    if(iface==3)ptrN=Tets[it].GetN3();if(iface==4)ptrN=Tets[it].GetN4();
    if(!ptrN){
        myreturn=-2;
        return(myreturn);}
    tet=*ptrN; 
    if(tet<0){ 
          myreturn=-2;
          return(myreturn);}
    if(tet==tetstart){
        myreturn=-1;
        return(myreturn);
        }
    int i1, i2, i3, i4, iedge, ichar1, ichar2;
    int if1, if2, ifc, ifacec, iend1a, iend2a;
    i1=Tets[tet].Get1(); i2=Tets[tet].Get2();
    i3=Tets[tet].Get3(); i4=Tets[tet].Get4();
    
       //look at all four possible cuts in this
       //tetrahedron and see if they match the end pairs
       //
       iend1a=-1; iend2a=-1;
         if(Done[tet][id]){
            for(int ic=0;ic<4;ic++){
              if(tetcuts[tet][ic]>0){
                ichar1=(int)tettrinodes[tet][2*ic];
                ichar2=(int)tettrinodes[tet][2*ic+1];
                if(ichar1==1)iend1a=i1; if(ichar1==2)iend1a=i2;
                if(ichar1==3)iend1a=i3; if(ichar1==4)iend1a=i4;
                if(ichar2==1)iend2a=i1; if(ichar2==2)iend2a=i2;
                if(ichar2==3)iend2a=i3; if(ichar2==4)iend2a=i4;

                if( ((iend1==iend1a) && (iend2==iend2a))
                   ||  ((iend2==iend1a) && (iend1==iend2a)) ){
                  NewTri=new Triangle;
                  NewTri->SetTri(icut2,icut1,tetcuts[tet][ic]);
                  IsoTris.push_back(NewTri);
                  tritetvec.push_back(it);
                  wclev.push_back(currentsurf); idlev.push_back(currentid);
                  newtris++;
                  myreturn=tetcuts[tet][ic];
                  return myreturn;
         //         return tetcuts[tet][ic];
                }
                 }}}

    
       iedge=-1;
       if((i1==iend1 && i2==iend2) || (i2==iend1 && i1==iend2))iedge=1;
       if((i1==iend1 && i3==iend2) || (i3==iend1 && i1==iend2))iedge=2;
       if((i1==iend1 && i4==iend2) || (i4==iend1 && i1==iend2))iedge=3;
       if((i2==iend1 && i3==iend2) || (i3==iend1 && i2==iend2))iedge=4;
       if((i2==iend1 && i4==iend2) || (i4==iend1 && i2==iend2))iedge=5;
       if((i3==iend1 && i4==iend2) || (i4==iend1 && i3==iend2))iedge=6;
       if1=-1; if2=-1;
       if(iedge==1){ if1=4; if2=3;}
       if(iedge==2){ if1=4; if2=2;}
       if(iedge==3){ if1=3; if2=2;}
       if(iedge==4){ if1=4; if2=1;}
       if(iedge==5){ if1=3; if2=1;}
       if(iedge==6){ if1=2; if2=1;}
       if( (if1 != ifacecall) && (if2 !=ifacecall)){ 
          cout << "Programme broke in GetExists\n"; exit(1);}
       if(if1==ifacecall)ifacec=if2;
       if(if2==ifacecall)ifacec=if1;
       int *ptrf; ptrf=NULL;
       if(ifacec==1)ptrf=Tets[tet].GetN1(); if(ifacec==2)ptrf=Tets[tet].GetN2();
       if(ifacec==3)ptrf=Tets[tet].GetN3(); if(ifacec==4)ptrf=Tets[tet].GetN4();
       if(ifacec==1)ifc=(int)Tets[tet].GetC1(); if(ifacec==2)ifc=(int)Tets[tet].GetC2();
       if(ifacec==3)ifc=(int)Tets[tet].GetC3(); if(ifacec==4)ifc=(int)Tets[tet].GetC4();

       if(!ptrf){
          myreturn=-2;
          return myreturn;}
       myreturn=GetExists(tet, ifc, ifacec, iend1, iend2, icut1, icut2);

 //      cout << "Got Back From recursive GetExists, still in GetExists\n";
       return(myreturn);
}

void VarTests( int ic, int ec, int iF, int &eF){

               eF=-1;

               if( (ic==1) && (iF==2) ){
                   if( (ec !=2) && (ec !=3) ){
                     cout <<" Hoped this couldn't happen a\n"; exit(1);}
                   if(ec==2)eF=4; if(ec==3)eF=5;  }
               if( (ic==1) && (iF==3) ){
                   if( (ec !=1) && (ec !=3) ){
                     cout <<" Hoped this couldn't happen b\n"; exit(1);}
                   if(ec==1)eF=4; if(ec==3)eF=6; }
               if( (ic==1) && (iF==4) ){
                   if( (ec !=1) && (ec !=2) ){
                     cout <<" Hoped this couldn't happen c\n"; exit(1);}
                   if(ec==1)eF=5; if(ec==2)eF=6; }

               if( (ic==2) && (iF==1) ){
                   if( (ec !=4) && (ec !=5) ){
                     cout <<" Hoped this couldn't happen d\n"; exit(1);}
                   if(ec==4)eF=2; if(ec==5)eF=3;  }
               if( (ic==2) && (iF==3) ){
                   if( (ec !=1) && (ec !=5) ){
                     cout <<" Hoped this couldn't happen e\n"; exit(1);}
                   if(ec==1)eF=2; if(ec==5)eF=6; }
               if( (ic==2) && (iF==4) ){
                   if( (ec !=1) && (ec !=4) ){
                     cout <<" Hoped this couldn't happen f\n"; exit(1);}
                   if(ec==1)eF=3; if(ec==4)eF=6; }

               if( (ic==3) && (iF==1) ){
                   if( (ec !=4) && (ec !=6) ){
                     cout <<" Hoped this couldn't happen g\n"; exit(1);}
                   if(ec==4)eF=1; if(ec==6)eF=3;  }
               if( (ic==3) && (iF==2) ){
                   if( (ec !=2) && (ec !=6) ){
                     cout <<" Hoped this couldn't happen h\n"; exit(1);}
                   if(ec==2)eF=1; if(ec==6)eF=5; }
               if( (ic==3) && (iF==4) ){
                   if( (ec !=4) && (ec !=2) ){
                     cout <<" Hoped this couldn't happen i\n"; exit(1);}
                   if(ec==4)eF=5; if(ec==2)eF=3; }

               if( (ic==4) && (iF==1) ){
                   if( (ec !=5) && (ec !=6) ){
                     cout <<" Hoped this couldn't happen j\n"; exit(1);}
                   if(ec==5)eF=1; if(ec==6)eF=2;  }
               if( (ic==4) && (iF==2) ){
                   if( (ec !=3) && (ec !=6) ){
                     cout <<" Hoped this couldn't happen k\n"; exit(1);}
                   if(ec==3)eF=1; if(ec==6)eF=4; }
               if( (ic==4) && (iF==3) ){
                   if( (ec !=3) && (ec !=5) ){
                     cout <<" Hoped this couldn't happen l\n"; exit(1);}
                   if(ec==3)eF=2; if(ec==5)eF=4; }
}
void  Swapper(int &GoToNext,int &ibededge, int &ia1, int &ia2, int &ib1, int &ib2, 
              int& i1, int& i2, int &i3, int &i4, bool* cuts){
                       bool swap=false;
                       int g1,g2,g3,g4,t1,t2,t3,t4;

                       int iedge1=-1, iedge2=-1;
                       int eF=-1, ec=-1;
                        //OK, the two embeded nodes have edge numbers eF and ec.
                        // ONE of these HAS to correspond to (ia1,ia2) or (ib1,ib2)
                        // and maybe icut1 icut2 =ibededge, so MAYBE BOTH

                       if( ((ia1==i1) && (ia2==i2)) || ((ia1==i2) && (ia2==i1)))iedge1=1;
                       if( ((ia1==i1) && (ia2==i3)) || ((ia1==i3) && (ia2==i1)))iedge1=2;
                       if( ((ia1==i1) && (ia2==i4)) || ((ia1==i4) && (ia2==i1)))iedge1=3;
                       if( ((ia1==i2) && (ia2==i3)) || ((ia1==i3) && (ia2==i2)))iedge1=4;
                       if( ((ia1==i2) && (ia2==i4)) || ((ia1==i4) && (ia2==i2)))iedge1=5;
                       if( ((ia1==i3) && (ia2==i4)) || ((ia1==i4) && (ia2==i3)))iedge1=6;

                       if( ((ib1==i1) && (ib2==i2)) || ((ib1==i2) && (ib2==i1)))iedge2=1;
                       if( ((ib1==i1) && (ib2==i3)) || ((ib1==i3) && (ib2==i1)))iedge2=2;
                       if( ((ib1==i1) && (ib2==i4)) || ((ib1==i4) && (ib2==i1)))iedge2=3;
                       if( ((ib1==i2) && (ib2==i3)) || ((ib1==i3) && (ib2==i2)))iedge2=4;
                       if( ((ib1==i2) && (ib2==i4)) || ((ib1==i4) && (ib2==i2)))iedge2=5;
                       if( ((ib1==i3) && (ib2==i4)) || ((ib1==i4) && (ib2==i3)))iedge2=6;

                       if(ibededge==1){
                           bool garbage=true;
                           if(cuts[2] && cuts[4]){ //edge 3 edge 5
                              ec=3; eF=5; garbage=false;}
                           if(cuts[1] && cuts[3]){ //edge 2 edge 4
                              ec=2; eF=4; garbage=false;}
                           if(garbage)cout << "garbage in Swapper\n";
                           }
                       if(ibededge==2){
                           bool garbage=true;
                           if(cuts[2] && cuts[5]){ //edge 3 edge 6
                              ec=3; eF=6; garbage=false;}
                           if(cuts[0] && cuts[3]){ //edge 1 edge 4
                              ec=1; eF=4; garbage=false;}
                           if(garbage)cout << "garbage in Swapper\n";
                           }
                       if(ibededge==3){
                           bool garbage=true;
                           if(cuts[1] && cuts[5]){ //edge 2 edge 6
                              ec=2; eF=6; garbage=false;}
                           if(cuts[0] && cuts[4]){ //edge 1 edge 5
                              ec=1; eF=5; garbage=false;}
                           if(garbage)cout << "garbage in Swapper\n";
                           }
                       if(ibededge==4){
                           bool garbage=true;
                           if(cuts[4] && cuts[5]){ //edge 5 edge 6
                              ec=5; eF=6; garbage=false;}
                           if(cuts[0] && cuts[1]){ //edge 1 edge 2
                              ec=1; eF=2; garbage=false;}
                           if(garbage)cout << "garbage in Swapper\n";
                           }
                       if(ibededge==5){
                           bool garbage=true;
                           if(cuts[0] && cuts[2]){ //edge 1 edge 3
                              ec=1; eF=3; garbage=false;}
                           if(cuts[3] && cuts[5]){ //edge 4 edge 6
                              ec=4; eF=6; garbage=false;}
                           if(garbage)cout << "garbage in Swapper\n";
                           }
                       if(ibededge==6){
                           bool garbage=true;
                           if(cuts[1] && cuts[2]){ //edge 2 edge 3
                              ec=2; eF=3; garbage=false;}
                           if(cuts[3] && cuts[4]){ //edge 4 edge 5
                              ec=4; eF=5; garbage=false;}
                           if(garbage)cout << "garbage in Swapper\n";
                           }


                        g1=Tets[GoToNext].Get1(); g2=Tets[GoToNext].Get2();
                        g3=Tets[GoToNext].Get3(); g4=Tets[GoToNext].Get4();


                        if(eF==1){t1=i1; t2=i2;} if(eF==2){t1=i1; t2=i3;}
                        if(eF==3){t1=i1; t2=i4;} if(eF==4){t1=i2; t2=i3;}
                        if(eF==5){t1=i2; t2=i4;} if(eF==6){t1=i3; t2=i4;}

                        if( (t1!=g1) && (t1!=g2) && (t1!=g3) && (t1!=g4)){
                        if( (t2!=g1) && (t2!=g2) && (t2!=g3) && (t2!=g4)){
                              swap=true; //neither t1 or t2 in neighbour
                              cout <<"Swapping means there is something wrong somehere\n";
                              cout <<"Swapping anyway!\n";
                              }}
                        


       /**************************Edge 1 *******************************************/
                        if(swap){

                        //if firtscut_is_cut1, swap ibs since second node
                        //must be embedded. Othwerise, the first node must be
                        //embedded
                        //
                        // ibededge=1
                        //pair starts e3 e5 go to e2 e4
                        if( ((ec==3) && (eF==5)) || ((ec==5) && (eF==3)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==3){ia1=i1; ia2=i3;}  //e3 to e2                      
                           if(iedge1==5){ia1=i2; ia2=i3;} } //e5 to e4                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==3){ib1=i1; ib2=i3;}  //e3 to e2                      
                           if(iedge2==5){ib1=i2; ib2=i3;} } //e5 to e4                      
                        }
                        //pair starts e2 e4 go to e3 e5
                        if( ((ec==2) && (eF==4)) || ((ec==4) && (eF==2)) ){
                           if( (ec==iedge1) || (eF==iedge1)){
                           if(iedge1==2){ia1=i1; ia2=i4;}  //e2 to e3                      
                           if(iedge1==4){ia1=i2; ia2=i4;}}  //e4 to e5                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==2){ib1=i1; ib2=i4;}  //e2 to e3                      
                           if(iedge2==4){ib1=i2; ib2=i4;}}  //e4 to e5                      
                          }
       /**************************Edge 2 *******************************************/
                        //pair starts e3 e6 go to e1 e4
                        if( ((ec==3) && (eF==6)) || ((ec==6) && (eF==3)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==3){ia1=i1; ia2=i2;}  //e3 to e1                      
                           if(iedge1==6){ia1=i2; ia2=i3;}}  //e6 to e4                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==3){ib1=i1; ib2=i2;}  //e3 to e1                      
                           if(iedge2==6){ib1=i2; ib2=i3;}}  //e6 to e4                      
                          }
                        //pair starts e1 e4 go to e3 e6
                        if( ((ec==1) && (eF==4)) || ((ec==4) && (eF==1)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==1){ia1=i1; ia2=i4;}  //e1 to e3                      
                           if(iedge1==4){ia1=i3; ia2=i4;}}  //e4 to e6                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==1){ib1=i1; ib2=i4;}  //e1 to e3                      
                           if(iedge2==4){ib1=i3; ib2=i4;}}  //e4 to e6                      
                          }
       /**************************Edge 3 *******************************************/
                        //pair starts e1 e5 go to e2 e6
                        if( ((ec==1) && (eF==5)) || ((ec==5) && (eF==1)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==1){ia1=i1; ia2=i3;}  //e1 to e2                      
			   if(iedge1==5){ia1=i3; ia2=i4;}}  //e5 to e6                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==1){ib1=i1; ib2=i3;}  //e1 to e2                      
                           if(iedge2==5){ib1=i3; ib2=i4;}}  //e5 to e6                      
                          }
                        //pair starts e2 e6 go to e1 e5
                        if( ((ec==2) && (eF==6)) || ((ec==6) && (eF==2)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==2){ia1=i1; ia2=i2;}  //e2 to e1                      
                           if(iedge1==6){ia1=i2; ia2=i4;}}  //e6 to e5                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==2){ib1=i1; ib2=i2;}  //e2 to e1                      
                           if(iedge2==6){ib1=i2; ib2=i4;}}  //e6 to e5                      
                          }
       /**************************Edge 4 *******************************************/
                        //pair starts e5 e6 go to e1 e2
                        if( ((ec==5) && (eF==6)) || ((ec==6) && (eF==5)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==5){ia1=i1; ia2=i2;}  //e5 to e1                      
                           if(iedge1==6){ia1=i1; ia2=i3;}}  //e6 to e2                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==5){ib1=i1; ib2=i2;}  //e5 to e1                      
                           if(iedge2==6){ib1=i1; ib2=i3;}}  //e6 to e2                      
                          }
                        //pair starts e1 e2 go to e5 e6
                        if( ((ec==1) && (eF==2)) || ((ec==2) && (eF==1)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==1){ia1=i2; ia2=i4;}  //e1 to e5                      
                           if(iedge1==2){ia1=i3; ia2=i4;}}  //e2 to e6                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==1){ib1=i2; ib2=i4;}  //e1 to e5                      
                           if(iedge2==2){ib1=i3; ib2=i4;}}  //e2 to e6                      
                          }
       /**************************Edge 5 *******************************************/
                        //pair starts e1 e3 go to e4 e6
                        if( ((ec==1) && (eF==3)) || ((ec==3) && (eF==1)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==1){ia1=i2; ia2=i3;}  //e1 to e4                      
                           if(iedge1==3){ia1=i3; ia2=i4;}}  //e3 to e6                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==1){ib1=i2; ib2=i3;}  //e1 to e4                      
                           if(iedge2==3){ib1=i3; ib2=i4;}}  //e3 to e6                      
                          }
                        //pair starts e4 e6 go to e1 e3
                        if( ((ec==4) && (eF==6)) || ((ec==6) && (eF==4)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==4){ia1=i1; ia2=i2;}  //e4 to e1                      
                           if(iedge1==6){ia1=i1; ia2=i4;}}  //e6 to e3                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==4){ib1=i1; ib2=i2;}  //e4 to e1                      
                           if(iedge2==6){ib1=i1; ib2=i4;}}  //e6 to e3                      
                          }
       /**************************Edge 6 *******************************************/
                        //pair starts e4 e5 go to e2 e3
                        if( ((ec==4) && (eF==5)) || ((ec==5) && (eF==4)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==4){ia1=i1; ia2=i2;}  //e4 to e2                      
                           if(iedge1==5){ia1=i1; ia2=i4;}}  //e5 to e3                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==4){ib1=i1; ib2=i2;}  //e4 to e2                      
                           if(iedge2==5){ib1=i1; ib2=i4;}}  //e5 to e3                      
                          }
                        //pair starts e2 e3 go to e4 e5
                        if( ((ec==2) && (eF==3)) || ((ec==3) && (eF==2)) ){
                           if( (ec==iedge1) || (eF=iedge1) ){
                           if(iedge1==2){ia1=i2; ia2=i3;}  //e2 to e4                      
                           if(iedge1==3){ia1=i2; ia2=i4;}}  //e3 to e5                      
                           if( (ec==iedge2) || (eF=iedge2) ){
                           if(iedge2==2){ib1=i2; ib2=i3;}  //e2 to e4                      
                           if(iedge2==3){ib1=i2; ib2=i4;}}  //e3 to e5                      
                          }

                        } //endif swap
 } 
             
