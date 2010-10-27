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
#include "PlotWorld.h"

#include "../../XFiles/TrueType.h"

#include "../../XFiles/SetUp.h"  //loads of declarations and initialisations
#include "../../XFiles/Controls.h"
#include "../../XFiles/DrawTextMove2.h"
#include "../../XFiles/DrawWaxis.h"

#define LINE0 0xFFFF
#define LINE1 0x0101
#define LINE2 0x00FF
#define LINE3 0x1C47
#define LINE4 0x3F07

void EventLoop()
{
 CCam Camera1;
 bool quitit=false;
 SDL_Event event;
 SDL_MouseMotionEvent event2; //Not yet used
 SDL_keysym  *whatkey;

 bool verbose=false;

 if(hidemousecursor)SDL_ShowCursor(0);
      speed=5.0;
      angspeed=0.05;

//Override Setup.h
      LIGHTS=false;
      glDisable(GL_LIGHTING);
      MouseOn=false;
      SDL_ShowCursor(1);


//  Go to while(!quitit) to see what happens once data set up

// Go to Render Scene for graphics bit

 //   if_stream opens for input
 //   of_stream opens for output
 //   f_stream opens for both
 //
 // Camera1 position and stare at point have defaults
 // in ../../XFiles.
 // CamPos is in OpenGL y=0 plane, at x=0, z=-3000,
 // stare at origin. Also jprime=OpenGL j, iprime=OpenGL i
 // and kprime=OpenGL k.
 //
 // Be careful to adjust iprime jprime, jay, and kprime
 // if changed here (See Landscape and Camera.h)
 //
 // if you use SetPos here
    double newview;
    newview=pi/2.0*.999;
    Camera1.CamRotatePos2(newview);

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
    font1.create(pointsize);
    font2.create(pointsize);
    font3.create(pointsize);
    font4.create(pointsize);
    font5.create(pointsize);
    font6.create(pointsize);
    font7.create(pointsize);
    font8.create(pointsize);
    font9.create(pointsize);
    pointsize=12;      //for bitmap font in ortho mode
    font10.create(pointsize);
    pointsize=6;      // for orthomode with scalefac 100.
    font11.create(pointsize);
    pointsize=60;     //  other sizes for perspective mode and cam coord system
    font12.create(pointsize);
    pointsize=75;
    font13.create(pointsize);


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
    nplots=1;
    cout << "argc=" << arg_count << endl;

    ndata=(int*)calloc(nplots,sizeof(int));
    ntype=(int*)calloc(nplots,sizeof(int));
    ncol=(int*)calloc(nplots,sizeof(int));

    ntri_or_point=(int*)calloc(nplots,sizeof(int));
    ntri=(int*)calloc(nplots,sizeof(int));
    npoint=(int*)calloc(nplots,sizeof(int));

    //ndata -- number of points
    //ntype, 1 for surfs, 0 for points
    //ncol  initial coloure number, 0=black
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
            file_in  >> *(ndata+i) >> *(ntri+i);
 
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
    wtext=ztext; wunits=zunits;


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

    wtext=zaxistext; wunits=zunits;

    xScale=(xhigh-xlow)/xrange;yScale=(yhigh-ylow)/yrange;zScale=(zhigh-zlow)/zrange;


    //Have nicked DrawWaxis from PlotVol, so...
    for(int i=0; i<13; i++){
       wstrings[i]=zstrings[i];}
    double wcol,wrange,wmin;
    iwnumb=iznumb;
    wrange=zrange;
    wmin=zmin;
    wred=new double[iwnumb]; 
    wgreen=new double[iwnumb]; 
    wblue=new double[iwnumb]; 
   // we are nicking PlotVol's legend code so need w's
    for(int i=0; i<iwnumb;i++){
      wnumbers[i]=znumbers[i]; 
      wcol=(wnumbers[i]-wmin)/wrange;
      if(wcol < 0.5){
         wred[i]=1.0;
         wgreen[i]=2*wcol;
         wblue[i]=0.0;
         }
        else{
         wred[i]=1.0-wcol;
      // original   wgreen[i]=2*(1.0-wcol);
        if(wcol <0.7){
            wgreen[i]=1.0;}
            else{
            wgreen[i]=1.0-(wcol-0.7)/0.3;}
         wblue[i]=2.0*(wcol-0.5);
         }
    }
    // remember --- wnumbers can be beyond the range!
    if(wgreen[0]<0)wgreen[0]=0;
    if(wred[iwnumb-1]<0)wred[iwnumb-1]=0;
    if(wgreen[iwnumb-1]<0)wgreen[iwnumb-1]=0;
    if(wblue[iwnumb-1]>1.0)wblue[iwnumb-1]=1.0;
    
    filename="../../XFiles/MyWorld.dat";
    file_in.close(); 
    file_in.open(filename.c_str());   
    double xlat,xlong;
    file_in >> nlines;
    WorldLat =new double*[nlines];
    WorldLong =new double*[nlines];
    linelong=new int[nlines];
    for(int i=0; i<nlines; i++){   //just do a wc on the file to get the number
         file_in >> linelong[i];
    //     cout << "line " << i << "  line= length=" << linelong[i] << endl;
         *(WorldLat+i)=new double[linelong[i]];
         *(WorldLong+i)=new double[linelong[i]];
         for(int j=0; j<linelong[i]; j++){
          file_in >> xlat >> xlong;
           *(*(WorldLat+i)+j)=xlat;
           *(*(WorldLong+i)+j)=xlong;
       }}
     cout << "Total number of lines in map is " << nlines << endl;

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

              x1=xlow+(x1-xmin)*xScale;
              y1=ylow+(y1-ymin)*yScale;
              z1=zlow+(z1-zmin)*zScale;

              x2=xlow+(x2-xmin)*xScale;
              y2=ylow+(y2-ymin)*yScale;
              z2=zlow+(z2-zmin)*zScale;

              x3=xlow+(x3-xmin)*xScale;
              y3=ylow+(y3-ymin)*yScale;
              z3=zlow+(z3-zmin)*zScale;

                   double zc1=zlow+(z_start2-(zmin-zsubtract))*zScale;
                   double zc2=zstep2*zScale;
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
                } //end of SDL POLL
                leftPressed=false; rightPressed=false;
                shift_leftPressed=false; shift_rightPressed=false;
                shift_upPressed=false; shift_downPressed=false;
                MouseOn=false; SDL_ShowCursor(1);
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
                 if(ctrl_upPressed)Camera1.CamStrafe2(-speed);
                 if(ctrl_downPressed)Camera1.CamStrafe2(speed);

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
      PerspectiveMode();

       }  //endif for helpscreen

      //call draw functions twice
      // once to actually draw, and once in selection mode

              if(movetext){
              glDisable(GL_DEPTH_TEST);
                  bool drawbox;
	          drawbox=true;
	          DrawTextMove2(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);

	      drawbox=false;   //pickmatrix
	      DrawTextMove2(drawbox);
              }

             if(c_Pressed){
                  if(drawcontours){
                      drawcontours=false;}
                  else{drawcontours=true;}}
            if(g_Pressed){
                  if(drawgrid){
                      drawgrid=false;}
                  else{drawgrid=true;}}

             if(legendplot && !helpscreen){

               bool drawbox;
               glDisable(GL_DEPTH_TEST);
	          drawbox=true;
	          DrawWaxis(drawbox);  //draw
               glEnable(GL_DEPTH_TEST);
                

             // cout << post_Pressed << endl;
	       drawbox=false;   //pickmatrix
	      if(!post_Pressed)DrawWaxis(drawbox);
               
               //if you make a call to gl2ps where
                //selection mode is being switched
                // you get no output!

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

      LIGHTS=false;
      glDisable(GL_LIGHTING);

          if(drawscene){

                   // X axis BOUNDING BOX
                   //numbers for x axis lower bounding box edge
                   glColor3ub(0,0,0);
                   double xt,yt,zt;
                   double longtick=70.0; double shorttick=longtick/2.0;

                   //xyz refer to normal xyz coordinates

                    zlow=0;
//                  Near x numbers
                   glPushMatrix();
                   //The rotation is counter clockwise
                   // of the vector points TOWARDS the viewer
                   glRotatef(-90.0,1.0,0.0,0.0);
                   // in/out now openGL -+y,  up/down now openGL -+z
                   xt=xlow+(x_start-(xmin-xsubtract))*xScale;
                   yt=-ylow;
                   zt=-zlow;
                   glTranslated(xt-shift1,-yt+shift4-150,-zt);  //initial translation with shift

                   xt=xstep*xScale;  //for subsequent translations
                   yt=0.0;
                   zt=0.0;
                   for(int i=0; i< ixnumb; i++){
		      font1.output(xstrings[i].c_str());
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();
//                 Far x numbers
                   glPushMatrix();
                   //The rotation is counter clockwise
                   // of the vector points TOWARDS the viewer
                   //
                   // Now this takes the biscuit --- now we have
                   // to translate to half way between xlow and xhigh
                   glTranslated((xlow+xhigh)/2.0,0.0,0.0);
                   glRotatef(-90.0,1.0,0.0,0.0);
                   glRotatef(180.0,0.0,0.0,1.0);
                   //left/right now openGL -+xm in/out now openGL +iy,up/down now openGL -+z

                   xt=xhigh-(x_start-(xmin-xsubtract))*xScale;
                        -(xlow+xhigh)/2.0;
                   yt=-ylow;
                   zt=-zlow;
                   glTranslated(xt-shift1+150,-yt+shift4-150,-zt);  //initial translation with shift

                   xt=xstep*xScale;  //for subsequent translations
                   yt=0.0;
                   zt=0.0;
                   for(int i=0; i< ixnumb; i++){
		      font1.output(xstrings[i].c_str());
                      glTranslated(-xt,yt,zt);
                    }
                   glPopMatrix();

                   //major tick marks for x axis bounding box and x axis if required
                   xt=xlow+(x_start-(xmin-xsubtract))*xScale; yt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   xt=xstep*xScale;  //for subsequent translations
                   for(int i=0; i<ixnumb; i++){
                      glBegin(GL_LINES);
                          glVertex3f(0.0,zlow,ylow-longtick); glVertex3f(0.0,zlow,ylow);
                          glVertex3f(0.0,zlow,yhigh); glVertex3f(0.0,zlow,yhigh+longtick);
                      glEnd();
                      glTranslated(xt,yt,zt);
                    }
                    glPopMatrix();

                   //minor tick marks for x axis bounding box and x axis if required
                   xt=xlow+(x_start2-(xmin-xsubtract))*xScale; yt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   xt=xstep2*xScale;  //for subsequent translations
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

                   yt=ylow-(y_start-(ymin-ysubtract))*yScale;
                   yt=ylow+(y_start-(ymin-ysubtract))*yScale;
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glRotatef(-90.0,1.0,0.0,0.0);
                   glRotatef(-90.0,0.0,0.0,1.0);
                   // openGL in/out=-+x, left/right=+-y, up/down =+-z
                   glTranslated(-yt-shift5,xlow-150.0-shift2,zlow);  //initial translation with shift
                   yt=ystep*yScale;;  //for subsequent translations
                   for(int i=0; i< iynumb; i++){
		      font1.output(ystrings[i].c_str());
                      glTranslated(-yt,xt,zt);
                    }
                   glPopMatrix();

                   yt=ylow+(y_start-(ymin-ysubtract))*yScale;
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glRotatef(-90.0,1.0,0.0,0.0);
                   glRotatef(90.0,0.0,0.0,1.0);
                   // openGL in/out=+-x, left/right=-+y, up/down =+-z
                   glTranslated(yt-shift5,-xhigh-150.0-shift2,zlow);  //initial translation with shift
                   yt=ystep*yScale;  //for subsequent translations
                   for(int i=0; i< iynumb; i++){
		      font1.output(ystrings[i].c_str());
                      glTranslated(yt,xt,zt);
                    }
                   glPopMatrix();

 

                   //major tick marks for y axis bounding box and y axis 
                   yt=ylow+(y_start-(ymin-ysubtract))*yScale;
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,yt); //initial translation step
                   yt=ystep*yScale;  //for subsequent translation
                   for(int i=0; i<iynumb; i++){
                      glBegin(GL_LINES);
                        glVertex3f(xlow,zlow,0.0); glVertex3f(xlow-longtick,zlow,0.0);
                        glVertex3f(xhigh,zlow,0.0); glVertex3f(xhigh+longtick,zlow,0.0);
                      glEnd();
                      glTranslated(xt,zt,yt);
                    }
                   glPopMatrix();

                   //minor tick marks for y axis bounding box and y axis 
                   yt=ylow+(y_start2-(ymin-ysubtract))*yScale;
		   xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,zt,yt); //initial translation step
                   yt=ystep2*yScale;  //for subsequent translation
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


                  double xtrans,ytrans;

     // bounding box
      glBegin(GL_LINES);
        glVertex3f(xlow,zlow,ylow); glVertex3f(xhigh,zlow,ylow);
        glVertex3f(xlow,zlow,yhigh); glVertex3f(xhigh,zlow,yhigh);
        glVertex3f(xlow,zlow,ylow); glVertex3f(xlow,zlow,yhigh);
        glVertex3f(xhigh,zlow,ylow); glVertex3f(xhigh,zlow,yhigh);
      glEnd();





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
         font12.output(xaxistext.c_str());
      glPopMatrix();


      glPushMatrix();
      glRotatef(-90.0,1.0,0.0,0.0);
      glRotatef(180.0,0.0,0.0,1.0);
         //Opengl in out now -+y, up/down=+-z, leftright=-+x
         glTranslated(-xt+shift7, ylow-250-shift8 , zlow);
         font12.output(xaxistext.c_str());
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
         font12.output(yaxistext.c_str());
      glPopMatrix();


      glPushMatrix();
         glRotatef(-90.0,1.0,0.0,0.0);  //rotate clock
         glRotatef(-90.0,0.0,0.0,1.0);
         //openGL in out now +-x, openGL left/right now +-y up/down +=z
         glTranslated(-yt-shift10, xlow-240.0+shift9,zlow);//remember xlow is negative, and that after rotation y is towards old -x
         font12.output(yaxistext.c_str());
      glPopMatrix();

      }   //endif for is there any y axis text

      } //end draw scene


  //Now plot the bloody graph!

      if(drawscene){

          float zred1, zgreen1, zblue1;
          float zred2, zgreen2, zblue2;
          float zred3, zgreen3, zblue3;
          float zcol1,zcol2,zcol3;

             glLineWidth(1.0); glColor3ub(0,0,0);
//           Draw World!

             for(int k=0; k<nlines; k++){
                double xa,ya,za,xb,yb,zb;

                for(int l=1; l<linelong[k]; l++){
                   xa=*(*(WorldLat+k)+l-1);
                   ya=*(*(WorldLong+k)+l-1);
                   xb=*(*(WorldLat+k)+l);
                   yb=*(*(WorldLong+k)+l);
                   xa=xlow+(xa-xmin)*xScale;
                   ya=ylow+(ya-ymin)*yScale;
                   xb=xlow+(xb-xmin)*xScale;
                   yb=ylow+(yb-ymin)*yScale;
                   glBegin(GL_LINES);
                     glVertex3d(xa,2,-ya);glVertex3d(xb,2,-yb);
                   glEnd();
                }
             }


      for(int i=0; i<nplots; i++){

        if(*(ntype+i)==0 && (drawgrid || drawcontours)){ //plot surface grid or contours

          glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

          glColor3ub(0,0,0);
      
          for(int j=0; j< *(ntri+i); j++){
              double x1,y1,x2,y2,z1,z2,x3,y3,z3;

              int i1,i2,i3;

              i1=*(*(triangles+i)+j*3); i2=*(*(triangles+i)+j*3+1); i3=*(*(triangles+i)+j*3+2);

              x1=*(*(x+i)+i1); y1=*(*(y+i)+i1); z1=*(*(z+i)+i1);
              x2=*(*(x+i)+i2); y2=*(*(y+i)+i2); z2=*(*(z+i)+i2);
              x3=*(*(x+i)+i3); y3=*(*(y+i)+i3); z3=*(*(z+i)+i3);

              x1=xlow+(x1-xmin)*xScale;
              y1=ylow+(y1-ymin)*yScale;
              z1=ylow+(z1-zmin)*zScale;

              x2=xlow+(x2-xmin)*xScale;
              y2=ylow+(y2-ymin)*yScale;
              z2=zlow+(z2-zmin)*zScale;

              x3=xlow+(x3-xmin)*xScale;
              y3=ylow+(y3-ymin)*yScale;
              z3=zlow+(z3-zmin)*zScale;
              z1=0; z2=0; z3=0;
          if(drawgrid){
          //draw grid slightly up and down
          glBegin(GL_TRIANGLES);
              glVertex3d(x1,z1+2,-y1);
              glVertex3d(x2,z2+2,-y2);
              glVertex3d(x3,z3+2,-y3);
           glEnd();
           }



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
                           za=0; zb=0;
                        glBegin(GL_LINES);
                           glVertex3d(xa,za+2,-ya);glVertex3d(xb,zb+2,-yb);
                           glVertex3d(xa,za+2,-ya);glVertex3d(xb,zb+2,-yb);
                        glEnd();}  //end kl loop
                         }   //endif for if cont
                 }  //endif for drawcontours

          }  //end triangles loop

      } //endif for draw grid or contours if type=surface

       //still inside if drawscene and nplots loop

      glColor3ub( 255, 0, 0);

      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

      glLineWidth((float)*(npoint+i));
          glShadeModel(GL_SMOOTH);
          for(int j=0; j< *(ntri+i); j++){
              float x1,y1,x2,y2,z1,z2,x3,y3,z3;

              int i1,i2,i3;

              i1=*(*(triangles+i)+j*3); i2=*(*(triangles+i)+j*3+1); i3=*(*(triangles+i)+j*3+2);

              
              x1=*(*(x+i)+i1); y1=*(*(y+i)+i1); z1=(*(*(z+i)+i1));
              x2=*(*(x+i)+i2); y2=*(*(y+i)+i2); z2=*(*(z+i)+i2);
              x3=*(*(x+i)+i3); y3=*(*(y+i)+i3); z3=*(*(z+i)+i3);

              zcol1=(z1-zmin)/zrange; zcol2=(z2-zmin)/zrange; zcol3=(z3-zmin)/zrange;
              zcol1=1.0-zcol1; zcol2=1.0-zcol2; zcol3=1.0-zcol3;
             if(zcol1<0.5){zred1=1.0; zgreen1=2.0*zcol1; zblue1=0.0;}
                         else {zred1=1.0-zcol1; 
                               if(zcol1<-.7){zgreen1=1.0;}
                                  else{zgreen1=(1.0-(zcol1-0.7)/0.3);}
                               zblue1=2.0*(zcol1-0.5);}
              if(zcol2<0.5){zred2=1.0; zgreen2=2.0*zcol2; zblue2=0.0;}
                         else {zred2=1.0-zcol2;
                               if(zcol2<-.7){zgreen2=1.0;}
                                  else{zgreen2=(1.0-(zcol2-0.7)/0.3);}
                               zblue2=2.0*(zcol2-0.5);}
              if(zcol3<0.5){zred3=1.0; zgreen3=2.0*zcol3; zblue3=0.0;}
                         else {zred3=1.0-zcol3;
                               if(zcol3<-.7){zgreen3=1.0;}
                                  else{zgreen3=(1.0-(zcol3-0.7)/0.3);}
                               zblue3=2.0*(zcol3-0.5);}

              /*
              if(zcol1<0.5){zred1=1.0; zgreen1=2.0*zcol1; zblue1=0.0;}
                         else {zred1=2*(1.0-zcol1); zgreen1=2*(1.0-zcol1); zblue1=2.0*(zcol1-0.5);}
              if(zcol2<0.5){zred2=1.0; zgreen2=2.0*zcol2; zblue2=0.0;}
                         else {zred2=2*(1.0-zcol2); zgreen2=2*(1.0-zcol2); zblue2=2.0*(zcol2-0.5);}
              if(zcol3<0.5){zred3=1.0; zgreen3=2.0*zcol3; zblue3=0.0;}
                         else {zred3=2*(1.0-zcol3); zgreen3=2*(1.0-zcol3); zblue3=2.0*(zcol3-0.5);}
              */
/*
              if(zcol1<0.5){zred1=1.0; zgreen1=2.0*zcol1; zblue1=0.0;}
                         else {zred1=(1.0-zcol1); zgreen1=2*(1.0-zcol1); zblue1=2.0*(zcol1-0.5);}
              if(zcol2<0.5){zred2=1.0; zgreen2=2.0*zcol2; zblue2=0.0;}
                         else {zred2=(1.0-zcol2); zgreen2=2*(1.0-zcol2); zblue2=2.0*(zcol2-0.5);}
              if(zcol3<0.5){zred3=1.0; zgreen3=2.0*zcol3; zblue3=0.0;}
                         else {zred3=(1.0-zcol3); zgreen3=2*(1.0-zcol3); zblue3=2.0*(zcol3-0.5);}
*/
              x1=xlow+(x1-xmin)*xScale;
              y1=ylow+(y1-ymin)*yScale;
              z1=ylow+(z1-zmin)*zScale;

              x2=xlow+(x2-xmin)*xScale;
              y2=ylow+(y2-ymin)*yScale;
              z2=zlow+(z2-zmin)*zScale;


              x3=xlow+(x3-xmin)*xScale;
              y3=ylow+(y3-ymin)*yScale;
              z3=zlow+(z3-zmin)*zScale;
               
              z1=0; z2=0; z3=0;
          glBegin(GL_TRIANGLES);
              glColor3f(zred1,zgreen1,zblue1);
              glVertex3f((float)x1,(float)z1,-(float)y1);
              glColor3f(zred2,zgreen2,zblue2);
              glVertex3f((float)x2,(float)z2,-(float)y2);
              glColor3f(zred3,zgreen3,zblue3);
              glVertex3f((float)x3,(float)z3,-(float)y3);
           glEnd();
          }  //end triangles loop


       } // end nplots loop
       glColor3ub(0,0,0);

       glPopMatrix();


    } // endif drawscene

}

