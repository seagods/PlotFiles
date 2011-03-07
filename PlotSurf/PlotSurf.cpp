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
#include "PlotSurf.h"

#include "/usr/local/include/XFiles/TrueType.h"

#include "/usr/local/include/XFiles/SetUp.h"  //loads of declarations and initialisations
#include "/usr/local/include/XFiles/Controls.h"
#include "/usr/local/include/XFiles/DrawLightPos.h"
#include "/usr/local/include/XFiles/DrawLightCol.h"
#include "/usr/local/include/XFiles/DrawMatCol.h"
#include "/usr/local/include/XFiles/DrawLogicBox.h"
#include "/usr/local/include/XFiles/DrawTextMove2.h"
#include "/usr/local/include/XFiles/DrawLegendsurf.h"

void EventLoop()
{
 CCam Camera1;
 bool quitit=false;
 SDL_Event event;
 SDL_MouseMotionEvent event2; //Not yet used
 SDL_keysym  *whatkey;

 bool verbose=false;

 if(hidemousecursor)SDL_ShowCursor(0);
      if(LIGHTS){
	      speed=5.0;
	      angspeed=0.01;}
      else
      {
	      speed=1.0;
	      angspeed=0.005;}

//Override Setup.h
//LIGHTS=false;


//  Go to while(!quitit) to see what happens once data set up

// Go to Render Scene for graphics bit

 //   if_stream opens for input
 //   of_stream opens for output
 //   f_stream opens for both
 //
 // Camera1 position and stare at point have defaults
 // in /usr/local/include/XFiles.
 // CamPos is in OpenGL y=0 plane, at x=0, z=-3000,
 // stare at origin. Also jprime=OpenGL j, iprime=OpenGL i
 // and kprime=OpenGL k.
 //
 // Be careful to adjust iprime jprime, jay, and kprime
 // if changed here (See Landscape and Camera.h)
 //
 // if you use SetPos here
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
    shift7=0.0;
    shift8=0.0;
    shift9=0.0;
    shift10=0.0;
    shift11=0.0;
    shift12=0.0;

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


    //read in data here
    //
    string filename;   //wierd C++ string and standard c string mash up
    ostringstream oss;   //don't really need the C++ string class here but...
    if(arg_count>=2){
    oss << *(arg_list+1);  //gets standard C string into C++ string object
    filename=oss.str();
    cout << filename << endl;
    }
    else
    {
	    filename="data.dat"; //default name
    }

    ifstream file_in;
    file_in.open(filename.c_str());  //c_str() is a member functio of the C++
                                     //string class, returns pointer to regular C string
    cout << "file_in=" << file_in << endl;
    if(!file_in){
	    cout <<"Data file does not exist!\n";
            exit(0);	
    }
    file_in >> nplots;   //number of curves to be plotted

    cout << "we are plotting " << nplots << " data sets \n";   
    cout << "argc=" << arg_count << endl;

    ndata=(int*)calloc(nplots,sizeof(int));
    ntype=(int*)calloc(nplots,sizeof(int));
    ncol=(int*)calloc(nplots,sizeof(int));

    ntri_or_point=(int*)calloc(nplots,sizeof(int));
    ntri=(int*)calloc(nplots,sizeof(int));
    npoint=(int*)calloc(nplots,sizeof(int));

    //ndata -- number of points
    //ntype, 1 for surfs, 0 for points
    //ncol  initial colour number, 0=black
    //could adapt to symbols for ntype=0 later

    x=(double**)calloc(nplots,sizeof(double*));
    y=(double**)calloc(nplots,sizeof(double*));
    z=(double**)calloc(nplots,sizeof(double*));

    triangles=(int**)calloc(nplots,sizeof(int*));

//   very inefficient for memory but...
//   what we should really do is make a class of line segments
//   and stuff'em into a list. Wanting to move on quickly
//   means that every triangle has three pairs of doubles

    contx1=(double**)calloc(nplots,sizeof(double*));
    conty1=(double**)calloc(nplots,sizeof(double*));
    contz1=(double**)calloc(nplots,sizeof(double*));

    contx2=(double**)calloc(nplots,sizeof(double*));
    conty2=(double**)calloc(nplots,sizeof(double*));
    contz2=(double**)calloc(nplots,sizeof(double*));

    cont=(bool**)calloc(nplots,sizeof(bool*));

    klines=(int**)calloc(nplots,sizeof(int*));

    xmin=1e300; xmax=-1e300; ymin=1e300; ymax=-1e300; zmin=1e300; zmax=-1e300;

    for(int i=0; i<nplots;i++){
            file_in  >> *(ndata+i) >> *(ntri_or_point+i) >> *(ntype+i) >> *(ncol+i) ;
 
             if(*(ntype+i)==0){
                   *(ntri+i)=*(ntri_or_point);}  //is no of tris

             if(*(ntype+i)==1){
                   *(npoint+i)=*(ntri_or_point);} // is point size
 
 
	    *(x+i)=(double*)calloc(*(ndata+i),sizeof(double));
	    *(y+i)=(double*)calloc(*(ndata+i),sizeof(double));
	    *(z+i)=(double*)calloc(*(ndata+i),sizeof(double));

            *(triangles+i)=(int*)calloc(*(ntri+i)*3,sizeof(int));

           //For each plot, we make room for the number of triangles for that
           //plot (*(ntri_i)) times the maximum number of lines a triangle
           //(for that plot) can have.

           *(contx1+i)=(double*)calloc(*(ntri+i),sizeof(double)*klinesmax);
           *(conty1+i)=(double*)calloc(*(ntri+i),sizeof(double)*klinesmax);
           *(contz1+i)=(double*)calloc(*(ntri+i),sizeof(double)*klinesmax);
           *(contx2+i)=(double*)calloc(*(ntri+i),sizeof(double)*klinesmax);
           *(conty2+i)=(double*)calloc(*(ntri+i),sizeof(double)*klinesmax);
           *(contz2+i)=(double*)calloc(*(ntri+i),sizeof(double)*klinesmax);

           *(cont+i)=(bool*)calloc(*(ntri+i),sizeof(bool));
           *(klines+i)=(int*)calloc(*(ntri+i),sizeof(int));

            for(int j=0; j<*(ntri+i);j++){
               file_in >> *(*(triangles+i)+j*3)
                       >> *(*(triangles+i)+j*3+1)
                       >> *(*(triangles+i)+j*3+2);
            }

	    for(int j=0; j < *(ndata+i); j++){
		    file_in >> *(*(x+i)+j) >> *(*(y+i)+j) >> *(*(z+i)+j);

		    if( *(*(x+i)+j)<xmin)xmin=*(*(x+i)+j);
		    if( *(*(y+i)+j)<ymin)ymin=*(*(y+i)+j);
		    if( *(*(z+i)+j)<zmin)zmin=*(*(z+i)+j);

		    if( *(*(x+i)+j)>xmax)xmax=*(*(x+i)+j);
		    if( *(*(y+i)+j)>ymax)ymax=*(*(y+i)+j);
		    if( *(*(z+i)+j)>zmax)zmax=*(*(z+i)+j);
	    }
   cout << "last z value was  " << *(*(z+i)+*(ndata+i)-1) << endl;
    } 

    //now deal with xy axis labels for what x and y are and what are the units
    char xchar,ychar,zchar;
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

    file_in >> LegendExists;


    if(LegendExists){
        LegendStrings=new string[nplots];
        for(int i=0; i<nplots;i++){
            file_in >> LegendStrings[i];
            for(int j=0; j<LegendStrings[i].length(); j++){
                xchar=LegendStrings[i][j];
                if(xchar=='@')LegendStrings[i].replace(j,1," ",1);
            }
        }
      }


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


    cout << " x axis label in data.dat is " << xtext << endl;
    cout << " y axis label in data.dat is " << ytext << endl;
    cout << " z axis label in data.dat is " << ztext << endl;
    cout << " x axis unit in data.dat is " << xunits << endl;
    cout << " y axis unit in data.dat is " << yunits << endl;
    cout << " z axis unit in data.dat is " << zunits << endl;

    cout << "xmin and xmax are " <<  xmin << "  " <<   xmax << endl;
    cout << "ymin and ymax are " <<ymin << "  " << ymax << endl;
    cout << "zmin and zmax are " <<zmin << "  " << zmax << endl;
    xrange=xmax-xmin; yrange=ymax-ymin; zrange=zmax-zmin;
    if(fabs(xrange)<1e-42){
	    cout << "xrange too small, exiting " << endl;
	    exit(0);}
    if(fabs(yrange)<1e-42){
	    cout << "yrange too small, exiting " << endl;
	    exit(0);}
    if(fabs(zrange)<1e-42){
	    cout << "zrange too small, exiting " << endl;
	    exit(0);}

    xexp=floor(log10(xrange)); yexp=floor(log10(yrange));
    zexp=floor(log10(zrange));
    xfact=pow(10.0,xexp); yfact=pow(10.0,yexp); zfact=pow(10.0,zexp);
    xrange_scale=xrange/xfact; yrange_scale=yrange/yfact;
    zrange_scale=zrange/zfact;

    //all the following  have been initialised false
    if(xmin >0.0)xmin_zero=true; if(ymin>0)ymin_zero=true;
    if(zmin>0)zmin_zero=true;
    if(xmax >0.0)xmax_zero=true; if(ymax>0)ymax_zero=true;
    if(zmax>0)zmax_zero=true;
    
    if(xmax >0.0 && xmin > 0.0)xboth=true; if(xmax <0.0 && xmin < 0.0)xboth=true; 
    if(ymax >0.0 && ymin > 0.0)yboth=true; if(ymax <0.0 && ymin < 0.0)yboth=true;
    if(zmax >0.0 && zmin > 0.0)zboth=true; if(zmax <0.0 && zmin < 0.0)zboth=true;

    cout << "xrange and xfact are " << xrange << "  " << xfact << endl;
    cout << "yrange and yfact are " << yrange << "  " << yfact << endl;
    cout << "zrange and zfact are " << zrange << "  " << zfact << endl;

    if(xmin>0)xmin_zero=true;  if(ymin>0)ymin_zero=true; if(zmin>0)zmin_zero=true;  
    if(xmax>0)xmax_zero=true;  if(ymax>0)ymax_zero=true; if(zmax>0)zmax_zero=true;

    if(xmin_zero==true && xmax_zero==true)xboth=true;
    if(xmin_zero==false && xmax_zero==false)xboth=true;

    if(ymin_zero==true && ymax_zero==true)yboth=true;
    if(ymin_zero==false && ymax_zero==false)yboth=true;

    if(zmin_zero==true && zmax_zero==true)zboth=true;
    if(zmin_zero==false && zmax_zero==false)zboth=true;
    
    //initialised at -1000 in header file
    if(xmin>0)xminexp=floor(log10(xmin)); 
    if(xmin<0)xminexp=floor(log10(-xmin)); 

    if(ymin>0)yminexp=floor(log10(ymin));
    if(ymin<0)yminexp=floor(log10(-ymin));

    if(zmin>0)zminexp=floor(log10(zmin));
    if(zmin<0)zminexp=floor(log10(-zmin));

    xminfact=pow(10.0,xminexp); yminfact=pow(10.0,yminexp); zminfact=pow(10.0,zminexp);
    if(xminfact>0){xmin_scale=xmin/xminfact;}else{xmin_scale=xmin*1000000.0;}
    if(yminfact>0){ymin_scale=ymin/yminfact;}else{ymin_scale=ymin*1000000.0;}
    if(zminfact>0){zmin_scale=zmin/zminfact;}else{zmin_scale=zmin*1000000.0;}



    numbers_xyz();

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

      zaxistext=zst.str();

      if(izunits==1){
        zst << ' ';
        zst << zunits;
      }

      } // endif z axis text


         //work out contour line segments

           for(int i=0; i<nplots;i++){
               for(int j=0; j<*(ntri+i);j++){
                   *(*(cont+i)+j)=false;}}

         for(int i=0; i< nplots; i++){
    
          for(int j=0; j< *(ntri+i); j++){
              double x1,y1,x2,y2,z1,z2,x3,y3,z3;

              int i1,i2,i3;

              i1=*(*(triangles+i)+j*3); i2=*(*(triangles+i)+j*3+1); i3=*(*(triangles+i)+j*3+2);

              x1=*(*(x+i)+i1); y1=*(*(y+i)+i1); z1=*(*(z+i)+i1);
              x2=*(*(x+i)+i2); y2=*(*(y+i)+i2); z2=*(*(z+i)+i2);
              x3=*(*(x+i)+i3); y3=*(*(y+i)+i3); z3=*(*(z+i)+i3);

              x1=xlow+(x1-xmin)/xrange*(xhigh-xlow);
              y1=ylow+(y1-ymin)/yrange*(yhigh-ylow);
              z1=zlow+(z1-zmin)/zrange*(zhigh-zlow);

              x2=xlow+(x2-xmin)/xrange*(xhigh-xlow);
              y2=ylow+(y2-ymin)/yrange*(yhigh-ylow);
              z2=zlow+(z2-zmin)/zrange*(zhigh-zlow);

              x3=xlow+(x3-xmin)/xrange*(xhigh-xlow);
              y3=ylow+(y3-ymin)/yrange*(yhigh-ylow);
              z3=zlow+(z3-zmin)/zrange*(zhigh-zlow);

                   double zc1=zlow+(z_start2-(zmin-zsubtract))/zrange*(zhigh-zlow);
                   double zc2=zstep2/zrange*(zhigh-zlow);  
                   double zc,zdiff;
                   double xc12,yc12,xc13,yc13,xc23,yc23;
                  //we assume surface cuts triangle only once! Ain't necessarily so.
                  //also assume contours are not close enough to have two cross one triangle
                  // per plot
                   bool cut12,cut13,cut23;

                *(*(klines+i)+j)=0;
                int kl=0;

               for(int k=0; k<iznumb2; k++){

                      cut12=false; cut13=false; cut23=false;
                      zc=zc1+k*zc2;

                      if(zc>=z1 &&  zc<=z2  ||  zc <=z1 && zc >= z2){
                             if(fabs(z1-z2)>1e-6){
                             cut12=true;
                             zdiff=fabs((z1-zc)/(z1-z2));
                             xc12=x1+zdiff*(x2-x1);
                             yc12=y1+zdiff*(y2-y1);
                             }
                            else{ cout << "rejected " << endl;}
                      }
                      if(zc>=z1 &&  zc<=z3  ||  zc <=z1 && zc >= z3){
                             if(fabs(z1-z3)>1e-6){
                             cut13=true;
                             zdiff=fabs((z1-zc)/(z1-z3));
                             xc13=x1+zdiff*(x3-x1);
                             yc13=y1+zdiff*(y3-y1);
                             }
                            else{ cout << "rejected " << endl;}
                      }
                      if(zc>=z2 &&  zc<=z3  ||  zc <=z2 && zc >= z3){
                             if(fabs(z3-z2)>1e-6){
                             cut23=true;
                             zdiff=fabs((z2-zc)/(z3-z2));
                             xc23=x2+zdiff*(x3-x2);
                             yc23=y2+zdiff*(y3-y2); 
                             }
                             else{ cout << "rejected " << endl;}
                      }

                      if(cut12 && cut13){
                        *(*(contx1+i)+j*klinesmax+kl)=xc12;
                        *(*(conty1+i)+j*klinesmax+kl)=yc12;
                        *(*(contz1+i)+j*klinesmax+kl)=zc;
                        *(*(contx2+i)+j*klinesmax+kl)=xc13;
                        *(*(conty2+i)+j*klinesmax+kl)=yc13;
                        *(*(contz2+i)+j*klinesmax+kl)=zc;
                        *(*(cont+i)+j)=true;
                        if(kl>klinesmax){cout << "increase klinesmax\n";exit(0);}
                        kl++;
                      }

                     if(cut12 && cut23){
                        *(*(contx1+i)+j*klinesmax+kl)=xc12;
                        *(*(conty1+i)+j*klinesmax+kl)=yc12;
                        *(*(contz1+i)+j*klinesmax+kl)=zc;
                        *(*(contx2+i)+j*klinesmax+kl)=xc23;
                        *(*(conty2+i)+j*klinesmax+kl)=yc23;
                        *(*(contz2+i)+j*klinesmax+kl)=zc;
                        *(*(cont+i)+j)=true;
                        if(kl>klinesmax){cout << "increase klinesmax\n";exit(0);}
                        kl++;
                      }

                     if(cut13 && cut23){
                        *(*(contx1+i)+j*klinesmax+kl)=xc13;
                        *(*(conty1+i)+j*klinesmax+kl)=yc13;
                        *(*(contz1+i)+j*klinesmax+kl)=zc;
                        *(*(contx2+i)+j*klinesmax+kl)=xc23;

                        *(*(conty2+i)+j*klinesmax+kl)=yc23;
                        *(*(contz2+i)+j*klinesmax+kl)=zc;
                        *(*(cont+i)+j)=true;
                        kl++;
                        if(kl>klinesmax){cout << "increase klinesmax\n";exit(0);}
                      }
                   }  //end k loop over contours
                   *(*(klines+i)+j)=kl;
              }  //end j loop over triangles
              } //end i loop over nplots

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


      glLineWidth(1.0);

      //LIGHTS ARE OFF  - KEEP CODE ANYWAY FOR NOW
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
      /***********************************************************************/
      /*            End Plots    Begin helpscreen and  Boxes Here            */
      /***********************************************************************/

      glEnable(GL_TEXTURE_2D);

      if(helpscreen){
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_LIGHTING);
	      //low top high bottom
	      //Matrix is diagonal
	      //  2/(high-low), 2/(top-bottom), -2/(far-near)
	      //  call in OrthMode is to glOrtho with near=0, far=1
	      //  Args are  low, top, high, bottom

      OrthoMode(-1, 1, 1, -1);
      glColor3ub(255,255,255);
      glBindTexture(GL_TEXTURE_2D,gl_Texture[0]);
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glBegin(GL_QUADS);
             // 0,0 is screen centre
             // -1,-1 is screen bottom low
	      glTexCoord2f(0.0,1.0);
	      glVertex2f(-1.0, 1.0); 
	      glTexCoord2f(0.0,0.0);
	      glVertex2f(-1.0, -1.0); // Bottom Left
	      glTexCoord2f(1.0,0.0);
	      glVertex2f(1.0, -1.0); // Bottom high
	      glTexCoord2f(1.0,1.0);
	      glVertex2f(1.0, 1.0); // Top high
      glEnd();

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_LIGHTING);
      PerspectiveMode();

       }  //endif for helpscreen

      //call draw functions twice
      // once to actually draw, and once in selection mode
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

              if(a_Pressed){
                  if(autoblend){
                      autoblend=false;}
                  else{ autoblend=true;}}
             if(b_Pressed){
                  if(blendon){
                      blendon=false;}
                  else{blendon=true;}}
             if(c_Pressed){
                  if(drawcontours){
                      drawcontours=false;}
                  else{drawcontours=true;}}
            if(g_Pressed){
                  if(drawgrid){
                      drawgrid=false;}
                  else{drawgrid=true;}}
	    if(t_Pressed){
		    if(Picking){
			    Picking=false;}
		    else{ Picking=true;}}

             if(legendplot && !helpscreen){

               bool  lite;
               lite=LIGHTS;
               bool drawbox;
               LIGHTS=false;
               glDisable(GL_DEPTH_TEST);
               glDisable(GL_LIGHTING);
	          drawbox=true;
	          DrawLegend(drawbox);  //draw
               glEnable(GL_DEPTH_TEST);
               LIGHTS=lite;
               if(LIGHTS)glEnable(GL_LIGHTING);
                

             // cout << post_Pressed << endl;
	       drawbox=false;   //pickmatrix
               lite=LIGHTS;
               LIGHTS=false;
	       if(!post_Pressed)DrawLegend(drawbox);
               LIGHTS=lite;
               
               //if you make a call to gl2ps where
                //selection mode is being switched
                // you get no output!

                }

              glDisable(GL_TEXTURE_2D);
	      SDL_GL_SwapBuffers();
}

#include "/usr/local/include/XFiles/Init.cpp"

void DrawScene(CCam & Camera1, bool drawscene)
{
      int viewport[4];
      SDL_GetMouseState(&mousex, &mousey);

      double xvals[5],yvals[5],zvals[5];
      double ex, why, zed;

      //Camera is at  (0,0,3000) OpenGL coords

          if(drawscene){
                   // X axis BOUNDING BOX
                   //numbers for x axis lower bounding box edge
                   glColor3ub(0,0,0);
                   glDisable(GL_LIGHTING);
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
                       exit(0);
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

             //       cout <<pi << endl;
                    
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


      //3-D bounding box
      glBegin(GL_LINES);
        glVertex3f(xlow,zlow,ylow); glVertex3f(xhigh,zlow,ylow);
        glVertex3f(xlow,zlow,yhigh); glVertex3f(xhigh,zlow,yhigh);
        glVertex3f(xlow,zlow,ylow); glVertex3f(xlow,zlow,yhigh);
        glVertex3f(xhigh,zlow,ylow); glVertex3f(xhigh,zlow,yhigh);

        glVertex3f(xlow,zhigh,ylow); glVertex3f(xhigh,zhigh,ylow);
        glVertex3f(xlow,zhigh,yhigh); glVertex3f(xhigh,zhigh,yhigh);
        glVertex3f(xlow,zhigh,ylow); glVertex3f(xlow,zhigh,yhigh);
        glVertex3f(xhigh,zhigh,ylow); glVertex3f(xhigh,zhigh,yhigh);

        glVertex3f(xlow,zlow,ylow); glVertex3f(xlow,zhigh,ylow);
        glVertex3f(xlow,zlow,yhigh); glVertex3f(xlow,zhigh,yhigh);
        glVertex3f(xhigh,zlow,ylow); glVertex3f(xhigh,zhigh,ylow);
        glVertex3f(xhigh,zlow,yhigh); glVertex3f(xhigh,zhigh,yhigh);
      glEnd();





      if(ixtext==1){

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

      //we are looking along +ve z (otherwise get mirror text)


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


      //we are looking along +ve z (otherwise get mirror text)

      float zt=zaxistext.length();
      zt=zt*40./2.0;

      if(printz3){
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
      } //end draw scene


  //Now plot the bloody graph!

      if(drawscene){

      for(int i=0; i<nplots; i++){

        if(*(ntype+i)==0 && (drawgrid || drawcontours)){ //plot surface grid

          glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
          glDisable(GL_LIGHTING);

          glColor3ub(0,0,0);
      
          for(int j=0; j< *(ntri+i); j++){
              double x1,y1,x2,y2,z1,z2,x3,y3,z3;

              int i1,i2,i3;

              i1=*(*(triangles+i)+j*3); i2=*(*(triangles+i)+j*3+1); i3=*(*(triangles+i)+j*3+2);

              x1=*(*(x+i)+i1); y1=*(*(y+i)+i1); z1=*(*(z+i)+i1);
              x2=*(*(x+i)+i2); y2=*(*(y+i)+i2); z2=*(*(z+i)+i2);
              x3=*(*(x+i)+i3); y3=*(*(y+i)+i3); z3=*(*(z+i)+i3);

              x1=xlow+(x1-xmin)/xrange*(xhigh-xlow);
              y1=ylow+(y1-ymin)/yrange*(yhigh-ylow);
              z1=ylow+(z1-zmin)/zrange*(zhigh-zlow);

              x2=xlow+(x2-xmin)/xrange*(xhigh-xlow);
              y2=ylow+(y2-ymin)/yrange*(yhigh-ylow);
              z2=zlow+(z2-zmin)/zrange*(zhigh-zlow);

              x3=xlow+(x3-xmin)/xrange*(xhigh-xlow);
              y3=ylow+(y3-ymin)/yrange*(yhigh-ylow);
              z3=zlow+(z3-zmin)/zrange*(zhigh-zlow);
          if(drawgrid){
          //draw grid slightly up and down
          glBegin(GL_TRIANGLES);
              glVertex3d(x1,z1+2,-y1);
              glVertex3d(x2,z2+2,-y2);
              glVertex3d(x3,z3+2,-y3);
              glVertex3d(x1,z1-2,-y1);
              glVertex3d(x2,z2-2,-y2);
              glVertex3d(x3,z3-2,-y3);
           glEnd();
           }
             glLineWidth(3.0); glColor3ub(0,0,0);
             if(drawcontours){
                        double xa,ya,za,xb,yb,zb;
                        if(  *(*(cont+i)+j)  ){
                        for(int kl=0; kl<*(*(klines+i)+j); kl++){
                           xa=*(*(contx1+i)+j*klinesmax+kl);
                           ya=*(*(conty1+i)+j*klinesmax+kl);
                           za=*(*(contz1+i)+j*klinesmax+kl);
                           xb=*(*(contx2+i)+j*klinesmax+kl);
                           yb=*(*(conty2+i)+j*klinesmax+kl);
                           zb=*(*(contz2+i)+j*klinesmax+kl);
                        glBegin(GL_LINES);
                           glVertex3d(xa,za+2,-ya);glVertex3d(xb,zb,-yb);
                           glVertex3d(xa,za-2,-ya);glVertex3d(xb,zb,-yb);
                        glEnd();}
                         }
                 }  //endif for drawcontours
                 glLineWidth(1.0); glColor3ub(0,0,0);
          }  //end triangles loop

      } //endif for draw grid or contours if type=surface

       //still inside if drawscene and nplots loop

      int matl=*(ncol+i);

      float amb[4],diff[4],spec[4];
      double ALPHA=1.0/((double)nplots);
      if(autoblend){

       float mat_amb[4]={RedM[matl][0],GreenM[matl][0],BlueM[matl][0],ALPHA};
       float mat_diff[4]={RedM[matl][1],GreenM[matl][1],BlueM[matl][1],ALPHA};
       float mat_spec[4]={RedM[matl][2],GreenM[matl][2],BlueM[matl][2],ALPHA};

       amb[0]=mat_amb[0];amb[1]=mat_amb[1];amb[2]=mat_amb[2];amb[3]=mat_amb[3];
       diff[0]=mat_diff[0];diff[1]=mat_diff[1];diff[2]=mat_diff[2];diff[3]=mat_diff[3];
       spec[0]=mat_spec[0];spec[1]=mat_spec[1];spec[2]=mat_spec[2];spec[3]=mat_spec[3];
       
      }
      else
      {
      float mat_amb[4]={RedM[matl][0],GreenM[matl][0],BlueM[matl][0],
		                AlphaM[matl][0] };
      float mat_diff[4]={RedM[matl][1],GreenM[matl][1],BlueM[matl][1],
		                AlphaM[matl][1] };
      float mat_spec[4]={RedM[matl][2],GreenM[matl][2],BlueM[matl][2],
		                AlphaM[matl][2] };
       amb[0]=mat_amb[0];amb[1]=mat_amb[1];amb[2]=mat_amb[2];amb[3]=mat_amb[3];
       diff[0]=mat_diff[0];diff[1]=mat_diff[1];diff[2]=mat_diff[2];diff[3]=mat_diff[3];
       spec[0]=mat_spec[0];spec[1]=mat_spec[1];spec[2]=mat_spec[2];spec[3]=mat_spec[3];
       }


      if(LIGHTS){ 


      float shine[]={ShineM[2][0]};
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
      glEnable(GL_LIGHTING);
        }
        else
	{
	glColor4ub( (int)(255*diff[0]),(int)(255*diff[1])
                    ,(int)(255*diff[2]),(int)(255*diff[3]) );
	}

      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

      glLineWidth((float)*(npoint+i));

     if(blendon){
      glDisable(GL_DEPTH_TEST);
     //don't exist gl2psDisable(GL2PS_DEPTH_TEST);
      glEnable(GL_BLEND);
      gl2psEnable(GL2PS_BLEND);
   //Note that DST is not supported on many platforms, can do anything with SRC
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      gl2psBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      }

        if(*(ntype+i)==0){ //plot surface

        //Completely weird fix for 64 bit
        //It appears as if lighting is off for the first triangles 0-383
        //I have no idea how data dependent this is or why it is
        //edit magicnumber bit if there is a problem later
        //Have a "Heath-Robinson" fix for this
        long int  test64;
        bool itis64=false;
        if(sizeof(test64)==8)itis64=true;
 
        if(itis64 && LIGHTS){
        
        int magicnumber;
        if(*(ntri+i)<384){
        magicnumber=*(ntri+i);}
        else{         
        magicnumber=384;}

          for(int j=0; j< magicnumber; j++){
              double x1,y1,x2,y2,z1,z2,x3,y3,z3;

              int i1,i2,i3;

              i1=*(*(triangles+i)+j*3); i2=*(*(triangles+i)+j*3+1);
              i3=*(*(triangles+i)+j*3+2);
              
              x1=*(*(x+i)+i1); y1=*(*(y+i)+i1); z1=*(*(z+i)+i1);
              x2=*(*(x+i)+i2); y2=*(*(y+i)+i2); z2=*(*(z+i)+i2);
              x3=*(*(x+i)+i3); y3=*(*(y+i)+i3); z3=*(*(z+i)+i3);

              x1=xlow+(x1-xmin)/xrange*(xhigh-xlow);
              y1=ylow+(y1-ymin)/yrange*(yhigh-ylow);
              z1=ylow+(z1-zmin)/zrange*(zhigh-zlow);

              x2=xlow+(x2-xmin)/xrange*(xhigh-xlow);
              y2=ylow+(y2-ymin)/yrange*(yhigh-ylow);
              z2=zlow+(z2-zmin)/zrange*(zhigh-zlow);


              x3=xlow+(x3-xmin)/xrange*(xhigh-xlow);
              y3=ylow+(y3-ymin)/yrange*(yhigh-ylow);
              z3=zlow+(z3-zmin)/zrange*(zhigh-zlow);

         D3Dvec  v1,v2,Normal;
         if(LIGHTS){//need normal vectors
            v1.SetVec(x2-x1,y2-y1,z2-z1);
            v2.SetVec(x3-x1,y3-y1,z3-z1);
            Normal=v1*v2;
            Normalise(Normal);
            }
          x1=x1/5000.; y1=y1/5000.0; z1=z1/5000.0;
          x2=x2/5000.; y2=y2/5000.0; z2=z2/5000.0;
          x3=x3/5000.; y3=y3/5000.0; z3=z3/5000.0;

          glBegin(GL_TRIANGLES);
              if(LIGHTS)glNormal3f(Normal.GetX(),Normal.GetZ(),-Normal.GetY());
              glVertex3d(x1,z1,-y1);
              glVertex3d(x2,z2,-y2);
              glVertex3d(x3,z3,-y3);
           glEnd();
          }  //end triangles loop

         } //endif for test64 and LIGHTS


          for(int j=0; j< *(ntri+i); j++){
              double x1,y1,x2,y2,z1,z2,x3,y3,z3;

              int i1,i2,i3;

              i1=*(*(triangles+i)+j*3); i2=*(*(triangles+i)+j*3+1);
              i3=*(*(triangles+i)+j*3+2);

              
              x1=*(*(x+i)+i1); y1=*(*(y+i)+i1); z1=*(*(z+i)+i1);
              x2=*(*(x+i)+i2); y2=*(*(y+i)+i2); z2=*(*(z+i)+i2);
              x3=*(*(x+i)+i3); y3=*(*(y+i)+i3); z3=*(*(z+i)+i3);


              x1=xlow+(x1-xmin)/xrange*(xhigh-xlow);
              y1=ylow+(y1-ymin)/yrange*(yhigh-ylow);
              z1=ylow+(z1-zmin)/zrange*(zhigh-zlow);

              x2=xlow+(x2-xmin)/xrange*(xhigh-xlow);
              y2=ylow+(y2-ymin)/yrange*(yhigh-ylow);
              z2=zlow+(z2-zmin)/zrange*(zhigh-zlow);


              x3=xlow+(x3-xmin)/xrange*(xhigh-xlow);
              y3=ylow+(y3-ymin)/yrange*(yhigh-ylow);
              z3=zlow+(z3-zmin)/zrange*(zhigh-zlow);

         D3Dvec  v1,v2,Normal;
         if(LIGHTS){//need normal vectors
            v1.SetVec(x2-x1,y2-y1,z2-z1);
            v2.SetVec(x3-x1,y3-y1,z3-z1);
            Normal=v1*v2;
            Normalise(Normal);
            }

          glBegin(GL_TRIANGLES);
              if(LIGHTS)glNormal3f(Normal.GetX(),Normal.GetZ(),-Normal.GetY());
              glVertex3d(x1,z1,-y1);
              glVertex3d(x2,z2,-y2);
              glVertex3d(x3,z3,-y3);
           glEnd();
           } //end triangles loop



       }//endif ntype=0;

          if(blendon){
          glDisable(GL_BLEND);
          gl2psDisable(GL2PS_BLEND);
          glEnable(GL_DEPTH_TEST);
          }

       if(*(ntype+i)==1){ //plot points

          glPointSize((float)*(npoint+i));

          glBegin(GL_POINTS);
          for(int j=0; j< *(ndata+i); j++){
              double x1,y1,z1;
              
              x1=*(*(x+i)+j); y1=*(*(y+i)+j); z1=*(*(z+i)+j);

              x1=xlow+(x1-xmin)/xrange*(xhigh-xlow);
              y1=ylow+(y1-ymin)/yrange*(yhigh-ylow);
              glVertex3d(x1,y1,-z1);
          }
          glEnd();
      }

       glDisable(GL_LIGHTING); //otherise get coulored text etc
       } // end nplots loop
       glColor3ub(0,0,0);


    } // endif drawscene

}

