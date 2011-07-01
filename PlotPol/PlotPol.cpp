//-------------------------------------------------------------------------------
// Copyright 2009-2011 Christopher Godsalve.
// All Rights Reserved.
//
// Permission to use, copy, modify and distribute this software (if not modified) and its
// documentation for educational, research and non-profit purposes, without fee,
// and without a written agreement is hereby granted, provided that the above
// copyright notice - this paragraph - and the following three paragraphs appear in all copies.
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
#include "PlotPol.h"

#include "/usr/local/include/XFiles/TrueType.h"

#include "/usr/local/include/XFiles/SetUp.h"  //loads of declarations and initialisations
#include "/usr/local/include/XFiles/Controls.h"
#include "/usr/local/include/XFiles/DrawWaxis.h"


void EventLoop()
{
 CCam Camera1;
 bool quitit=false;
 SDL_Event event;
 SDL_MouseMotionEvent event2; //Not yet used
 SDL_keysym  *whatkey;

 bool verbose=false;
 piover2=pi/2.0;

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
 // in /usr/local/include/XFiles.
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

            double xtemp, ytemp, radtemp;
	    for(int j=0; j < *(ndata+i); j++){
		    file_in >> *(*(x+i)+j) >> *(*(y+i)+j) >> *(*(z+i)+j);
                    xtemp=*(*(x+i)+j);
                    ytemp=*(*(y+i)+j);
                    radtemp=xtemp*convert;
                    xtemp=radtemp*cos(ytemp);
                    ytemp=radtemp*sin(ytemp);
                    *(*(x+i)+j)=xtemp;
                    *(*(y+i)+j)=ytemp;
          //          cout << "x=" <<  *(*(x+i)+j) <<  " y=" << *(*(y+i)+j) << endl;
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

//   Now we read any polar curves to overlay the contour plot with
//   use subscript p for "polar curve"
    file_in >> nplots_p;   //number of curves to be plotted

    cout << "we are plotting " << nplots_p << " data sets \n";
    ndata_p=(int*)calloc(nplots,sizeof(int));
    ntype_p=(int*)calloc(nplots,sizeof(int));
    ncol_p=(int*)calloc(nplots,sizeof(int));
    nstyle_p=(int*)calloc(nplots,sizeof(int));
    npoint_p=(int*)calloc(nplots,sizeof(int));
    x_p=(double**)calloc(nplots,sizeof(double*));
    y_p=(double**)calloc(nplots,sizeof(double*));

    for(int i=0; i<nplots_p;i++){
            file_in  >> *(ndata_p+i) >> *(ntype_p+i) >> *(ncol_p+i) >> *(nstyle_p+i) >>*(npoint_p+i);
	    *(x_p+i)=(double*)calloc(*(ndata_p+i),sizeof(double));
	    *(y_p+i)=(double*)calloc(*(ndata_p+i),sizeof(double));
	    for(int j=0; j < *(ndata_p+i); j++){
		    file_in >> *(*(x_p+i)+j) >> *(*(y_p+i)+j);
	    }
    } 
    file_in >> nsuns;
        thetasuns=(double*)calloc(nsuns,sizeof(double));
        phisuns=(double*)calloc(nsuns,sizeof(double));
        for(int i=0; i<nsuns;i++){
           file_in >> *(thetasuns+i) >> *(phisuns+i);}
        thetasats=(double*)calloc(nsats,sizeof(double));
        phisats=(double*)calloc(nsats,sizeof(double));
     file_in >> nsats;
        for(int i=0; i<nsats;i++){
           file_in >> *(thetasats+i) >> *(phisats+i);}
    file_in.close(); 
     

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
     //    wgreen[i]=2*(1.0-wcol);
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

         //work out contour line segments

           for(int i=0; i<nplots;i++){
               for(int j=0; j<*(ntri+i);j++){
                   *(*(cont+i)+j)=false;}}

         for(int i=0; i< nplots; i++){
    
          for(int j=0; j< *(ntri+i); j++){
              double x1,y1,x2,y2,z1,z2,x3,y3,z3;

              int i1,i2,i3;

              i1=*(*(triangles+i)+j*3); i2=*(*(triangles+i)+j*3+1);
              i3=*(*(triangles+i)+j*3+2);

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

/*         No text to move in PlotPol!    
              if(movetext){
              glDisable(GL_DEPTH_TEST);
                  bool drawbox;
	          drawbox=true;
	          DrawTextMove2(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);

	      drawbox=false;   //pickmatrix
	      DrawTextMove2(drawbox);
              }
*/

             if(c_Pressed){
                  if(drawcontours){
                      drawcontours=false;}
                  else{drawcontours=true;}}
            if(g_Pressed){
                  if(drawgrid){
                      drawgrid=false;}
                  else{drawgrid=true;}}
	    if(l_Pressed){
		    if(legendplot){
			    legendplot=false;}
		    else{ legendplot=true;}}

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

#include "/usr/local/include/XFiles/Init.cpp"

void DrawScene(CCam & Camera1, bool drawscene)
{
      int viewport[4];
      SDL_GetMouseState(&mousex, &mousey);

      double xvals[5],yvals[5],zvals[5];
      double ex, why, zed;

      LIGHTS=false;
      glDisable(GL_LIGHTING);

          if(drawscene){
                   glColor3ub(0,0,0);
                   double xt,yt,zt;
                   double longtick=70.0; double shorttick=longtick/2.0;

                   //xyz refer to normal xyz coordinates
                   zlow=4;  //z goes -800 to 800
                   //draw circles
                   double radius=xhigh; double  arg, argold;
                   double exold,whyold;
                   for(int irad=1; irad <7; irad++){
                   radius=xhigh/6.0*irad;
                   argold=0.0;
                   exold=radius*cos(argold); whyold=radius*sin(argold);
                   if(irad==6)glLineWidth(thickline);
                   //note we rotated the original
                   //view vector so that we're looking down
                   //the y axis, our 'y' axis is actually the negative z axis
                   glBegin(GL_LINES);
                   for(int i=0; i<360; i++){
                       arg=double(i+1)/convert;
                       ex=radius*cos(arg); why=radius*sin(arg);
                       glVertex3f(exold,zlow,-whyold);
                       glVertex3f(ex,zlow,-why);
                       exold=ex; whyold=why;
                   }
                   glEnd();
                   } //end irad loop //last radius was xhigh
                   glLineWidth(1.0);
                   glBegin(GL_LINES);
                   for(int i=0; i<6; i++){
                      arg=360.0/12.0/convert*i;
                      exold=-radius*cos(arg); whyold=-radius*sin(arg);
                      ex=radius*cos(arg); why=radius*sin(arg);
                   //note we rotated the original
                   //view vector so that we're looking down
                   //the y axis, our 'y' axis is actually the negative z axis
                      glVertex3f(exold,zlow,-whyold);
                      glVertex3f(ex,zlow,-why);
                   }
                   glEnd();
                   for(int i=0; i<12; i++){
                     phinumbers[i]=(double)i*30;
                     ostringstream phiout;
                     phiout << phinumbers[i];
                     phistrings[i]=phiout.str();
                    }
                   for(int i=0; i<12; i++){
                      arg=360.0/12.0/convert*i;
                      ex=radius*1.15*cos(arg); why=1.15*radius*sin(arg);
                      glPushMatrix();
                      glRotatef(-90.0, 1.0, 0.0, 0.0);
                      glTranslated(-20.0,0,0);
                      glTranslated(ex,why,0.0);

                      font1->draw(phistrings[i].c_str());
                      glPopMatrix();
                   }
      } //end draw scene


  //Now plot the bloody graph!

      if(drawscene){

          float zred1, zgreen1, zblue1;
          float zred2, zgreen2, zblue2;
          float zred3, zgreen3, zblue3;
          float zcol1,zcol2,zcol3;

          glLineWidth(1.0); glColor3ub(0,0,0);

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
                   //note we rotated the original
                   //view vector so that we're looking down
                   //the y axis, our 'y' axis is actually the negative z axis
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

       //now draw any polar curves
        bool stipple;

        for(int i=0; i<nplots_p; i++){

       	glColor3ub((int)(255*RedPC1[i][1]),
                   (int)(255*GreenPC1[i][1]),(int)(255*BluePC1[i][1]));
        if(*(ntype_p+i)==0){ //plot lines

          if(*(nstyle_p+i)==0)glLineStipple(1,LINE0);
          if(*(nstyle_p+i)==1)glLineStipple(1,LINE1);
          if(*(nstyle_p+i)==2)glLineStipple(1,LINE2);
          if(*(nstyle_p+i)==3)glLineStipple(1,LINE3);
          if(*(nstyle_p+i)==4)glLineStipple(1,LINE4);

//  the 1 is a stretch factor (dont strectch)
          if(*(nstyle_p+i)>0){
	       stipple=true;
               }
               else
	       {
	       stipple=false;
               }	       
	   if(stipple){
      glEnable(GL_LINE_STIPPLE);
      gl2psEnable(GL2PS_BLEND);
      gl2psEnable(GL2PS_LINE_STIPPLE);  //has to be called AFTER glLineStipple
           }

          glBegin(GL_LINES);
          for(int j=0; j< *(ndata_p+i)-1; j++){
              double x1,y1,x2,y2,radius,phi;
              
              x1=*(*(x_p+i)+j); y1=*(*(y_p+i)+j);
              x2=*(*(x_p+i)+j+1); y2=*(*(y_p+i)+j+1);
              radius=x1*convert; phi=y1;
              x1=radius*cos(phi); y1=radius*sin(phi);
              radius=x2*convert; phi=y2;
              x2=radius*cos(phi); y2=radius*sin(phi);

              x1=xlow+(x1+90.0)/180.0*(xhigh-xlow);
              y1=ylow+(y1+90.0)/180.0*(yhigh-ylow);
              x2=xlow+(x2+90.0)/180.0*(xhigh-xlow);
              y2=ylow+(y2+90.0)/180.0*(yhigh-ylow);
                   //note we rotated the original
                   //view vector so that we're looking down
                   //the y axis, our 'y' axis is actually the negative z axis
              glVertex3d(x1,3.0,-y1);
              glVertex3d(x2,3.0,-y2);
          }
          glEnd();
	  if(stipple){
          gl2psDisable(GL2PS_LINE_STIPPLE);
	  gl2psDisable(GL2PS_BLEND);
          glDisable(GL_LINE_STIPPLE);
	  stipple=false;
	  }
      }
       if(*(ntype_p+i)==1){ //plot points

         glPointSize((float)*(npoint_p+i));

          glBegin(GL_POINTS);
          for(int j=0; j< *(ndata_p+i); j++){
              double x1,y1,radius,phi;
              x1=*(*(x_p+i)+j); y1=*(*(y_p+i)+j);
              radius=x1*convert; phi=y1;
              x1=radius*cos(phi); y1=radius*sin(phi);
              x1=xlow+(x1+90.)/180.0*(xhigh-xlow);
              y1=ylow+(y1+90)/180.0*(yhigh-ylow);
                   //note we rotated the original
                   //view vector so that we're looking down
                   //the y axis, our 'y' axis is actually the negative z axis
              glVertex3d(x1,3.0,-y1);
          }
          glEnd();
      }
        }//end nplots_p loop
   
        for(int i=0; i<nsuns;i++){
           double x1,y1,radius,phi;
           x1=*(thetasuns+i); y1=*(phisuns+i);
           radius=x1*convert; phi=y1;
           x1=radius*cos(phi); y1=radius*sin(phi);
           x1=xlow+(x1+90.)/180.0*(xhigh-xlow);
           y1=ylow+(y1+90)/180.0*(yhigh-ylow);
           glPushMatrix();
                   //note we rotated the original
                   //view vector so that we're looking down
                   //the y axis, our 'y' axis is actually the negative z axis
           glTranslatef(x1,0.0,-y1);
           DrawSun();
           glPopMatrix();
           }
        for(int i=0; i<nsats;i++){
           double x1,y1,radius,phi;
           x1=*(thetasats+i); y1=*(phisats+i);
           radius=x1*convert; phi=y1;
           x1=radius*cos(phi); y1=radius*sin(phi);
           x1=xlow+(x1+90.)/180.0*(xhigh-xlow);
           y1=ylow+(y1+90)/180.0*(yhigh-ylow);
           glPushMatrix();
                   //note we rotated the original
                   //view vector so that we're looking down
                   //the y axis, our 'y' axis is actually the negative z axis
           glTranslatef(x1,0.0,-y1);
           DrawSat();
           glPopMatrix();
           }

        glColor3ub(0,0,0);

    } // endif drawscene

}
void DrawSun(){
   double rho,phi,x,y;
   int npoly=20;
   rho=1.5;
   glColor3ub(255,255,0);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   glBegin(GL_POLYGON);
   for(int i=0; i<npoly; i++){
      phi=twopi/20.0*i;
      x=rho*cos(phi); y=rho*sin(phi);
      x=xlow+(x+90.)/180.0*(xhigh-xlow);
      y=ylow+(y+90)/180.0*(yhigh-ylow);
      glVertex3d(x,3.0,y);
   }
   glEnd();
   glColor3ub(0,0,0);
   glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   glBegin(GL_POLYGON);
   for(int i=0; i<npoly; i++){
      phi=twopi/20.0*i;
      x=rho*cos(phi); y=rho*sin(phi);
      x=xlow+(x+90.)/180.0*(xhigh-xlow);
      y=ylow+(y+90)/180.0*(yhigh-ylow);
      glVertex3d(x,4.0,y);
   }
   glEnd();
}

void DrawSat(){
   double rho,phi,x,y;
   int npoly=4;
   rho=1.5;
   glColor3ub(255,255,255);
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   glBegin(GL_POLYGON);
   for(int i=0; i<npoly; i++){
      phi=twopi/4.0*i;
      x=rho*cos(phi); y=rho*sin(phi);
      x=xlow+(x+90.)/180.0*(xhigh-xlow);
      y=ylow+(y+90)/180.0*(yhigh-ylow);
      glVertex3d(x,3.0,y);
   }
   glEnd();
   glColor3ub(0,0,0);
   glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   glBegin(GL_POLYGON);
   for(int i=0; i<npoly; i++){
      phi=twopi/4.0*i;
      x=rho*cos(phi); y=rho*sin(phi);
      x=xlow+(x+90.)/180.0*(xhigh-xlow);
      y=ylow+(y+90)/180.0*(yhigh-ylow);
      glVertex3d(x,4.0,y);
   }
   glEnd();
}
