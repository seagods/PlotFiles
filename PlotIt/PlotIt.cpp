//-------------------------------------------------------------------------------
// Copyright 2008-2011 Christopher Godsalve.
// All Rights Reserved.
//
// Permission to use, copy, modify and distribute this software (if not modified) and its
// documentation for educational, research and non-profit purposes, without fee,
// and without a written agreement is hereby granted, provided that the above
// copyright notice and the following three paragraphs appear in all copies.
// A
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
#include "PlotIt.h"

#include "../../XFiles/TrueType.h"

#include "../../XFiles/SetUp.h"  //loads of declarations and initialisations
#include "../../XFiles/Controls.h"
#include "../../XFiles/DrawTextMove.h"
#include "../../XFiles/DrawCurveCol.h"
#include "../../XFiles/DrawLegend.h"

#define LINE0 0xFFFF
#define LINE1 0x0101
#define LINE2 0x00FF
#define LINE3 0x1C47
#define LINE4 0x3F07


void EventLoop()
{
 MouseOn=false;  //override initial value of MouseOn in SetUp.h
 CCam Camera1;
 bool quitit=false;
 SDL_Event event;
 SDL_MouseMotionEvent event2; //Not yet used
 SDL_keysym  *whatkey;

 bool verbose=false;

 if(hidemousecursor)SDL_ShowCursor(0);

//Override Setup.h
LIGHTS=false;


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
    if(staked){
	    Camera1.SetPos(0.0,0.0,0.0);
	    Camera1.SetView(0.0,0.0,1000.0);
    }
    cout << Camera1.CamPos.GetX();
    cout << "  " << Camera1.CamPos.GetY();
    cout << "  " << Camera1.CamPos.GetZ() << endl;
    cout << Camera1.CamView.GetX();
    cout << "  " << Camera1.CamView.GetY();
    cout << "  " << Camera1.CamView.GetZ() << endl;

    shift1=0.0;
    shift2=0.0;
    shift3=0.0;
    shift4=0.0;
    shift5=150.0;
    shift6=-100.0;
    shift7=0.0;
    shift8=0.0;
    shift9=0.0;
    shift10=0.0;

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
    nstyle=(int*)calloc(nplots,sizeof(int));
    npoint=(int*)calloc(nplots,sizeof(int));

    //ndata -- number of points
    //ntype, 1 for lines, 0 for points
    //ncol  initial colour number, 0=black
    //nstyle  select line style if lines
    //could adapt to symbols for ntype=0 later

    x=(double**)calloc(nplots,sizeof(double*));
    y=(double**)calloc(nplots,sizeof(double*));

    xmin=1e300; xmax=-1e300;
    ymin=1e300; ymax=-1e300;

    for(int i=0; i<nplots;i++){
     //       double xtemp,ytemp;
            file_in  >> *(ndata+i) >> *(ntype+i) >> *(ncol+i) >> *(nstyle+i) >> *(npoint+i);
            if(*(ncol+i)>imats){
               cout << "colour code for curve " << i << " exceeds number of material colours " << imats <<endl;
               exit(1);
           }
            cout << "ndata=" << *(ndata+i) << "  ";
            cout << "ntype=" << *(ntype+i) << "  ";
            cout << "ncol=" << *(ncol+i) <<  "  ";
            cout << "nstyle=" << *(nstyle+i) <<   "  ";
            cout << "point size=" << *(npoint+i) << endl;
	    *(x+i)=(double*)calloc(*(ndata+i),sizeof(double));
	    *(y+i)=(double*)calloc(*(ndata+i),sizeof(double));
	    for(int j=0; j < *(ndata+i); j++){
		    file_in >> *(*(x+i)+j) >> *(*(y+i)+j);
            //        xtemp=*(*(x+i)+j);
             //       ytemp=*(*(y+i)+j);
             //       xtemp=xtemp*5000.0;
             //       ytemp=ytemp*50000.0;
             //       *(*(x+i)+j)=xtemp;
             //       *(*(y+i)+j)=ytemp;

		    if( *(*(x+i)+j)<xmin)xmin=*(*(x+i)+j);
		    if( *(*(y+i)+j)<ymin)ymin=*(*(y+i)+j);
		    if( *(*(x+i)+j)>xmax)xmax=*(*(x+i)+j);
		    if( *(*(y+i)+j)>ymax)ymax=*(*(y+i)+j);
	    }
    } 


    //now deal with xy axis labels for what x and y are and what are the units
    char xchar,ychar;
 //   int ixtext, ixunits, iytext, iyunits;
    int strlength;

 //   declared as strings in the header file
 //   string xtext,ytext,xunits,yunits;  //what's read in - 'x' for istance
 //   string xaxistext,yaxistext;        //what appears on the axis    (x-40000) per cm for instance
 //   string xtextmod,ytextmod;   

    file_in >> ixtext >> ixunits;  //=1 if any text or any units
    if(ixtext==1 && ixunits==1)file_in >>   xtext >> xunits;
    if(ixtext==1 && ixunits==0)file_in >> xtext;
    file_in >> iytext >> iyunits;  //=1 if any text or any units
    if(iytext==1 && iyunits==1)file_in >>   ytext >> yunits;
    if(iytext==1 && iyunits==0)file_in >> ytext;

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


    cout << " x axis label in data.dat is " << xtext << endl;
    cout << " y axis label in data.dat is " << ytext << endl;
    cout << " x axis unit in data.dat is " << xunits << endl;
    cout << " y axis unit in data.dat is " << yunits << endl;

//
//    put test values for xmin and xmax here, set verbose=true in numbers_xy
//    xmin=1234543.005; xmax=1234543.200;
//    xmin=-300.0;  xmax=-299.5;
//    xmin=1234543.000;  xmax=1234543.200;
//    xmin=1.50673;  xmax=1.50675;
//    xmin=-1.50675;  xmax=-1.50674;
//    xmin=-1.345; xmax=4.567;
//    ymin=-3.3333; ymax=1.232;


    cout << "xmin and xmax are " <<  xmin << "  " <<   xmax << endl;
    cout << "ymin and ymax are " <<ymin << "  " << ymax << endl;
    xrange=xmax-xmin; yrange=ymax-ymin;
    if(fabs(xrange)<1e-42){
	    cout << "xrange too small, exiting " << endl;
	    exit(0);}
    if(fabs(yrange)<1e-42){
	    cout << "yrange too small, exiting " << endl;
	    exit(0);}

    xexp=floor(log10(xrange)); yexp=floor(log10(yrange));
    xfact=pow(10.0,xexp); yfact=pow(10.0,yexp);
    xrange_scale=xrange/xfact; yrange_scale=yrange/yfact;

    //all the following  have been initialised false
    if(xmin >0.0)xmin_zero=true; if(ymin>0)ymin_zero=true;
    if(xmax >0.0)xmax_zero=true; if(ymax>0)ymax_zero=true;
    if(xmax >0.0 && xmin > 0.0)xboth=true; if (ymax >0.0 && ymin>0.0)yboth=true;
    if(xmax <0.0 && xmin < 0.0)xboth=true; if (ymax <0.0 && ymin<0.0)yboth=true;


    cout << "xrange and xfact are " << xrange << "  " << xfact << endl;
    cout << "yrange and yfact are " << yrange << "  " << yfact << endl;

    if(xmin>0)xmin_zero=true;  if(ymin>0)ymin_zero=true;  
    if(xmax>0)xmax_zero=true;  if(ymax>0)ymax_zero=true;  

    if(xmin_zero==true && xmax_zero==true)xboth=true;
    if(xmin_zero==false && xmax_zero==false)xboth=true;

    if(ymin_zero==true && ymax_zero==true)yboth=true;
    if(ymin_zero==false && ymax_zero==false )yboth=true;
    
    xminexp=-1000.;  // in case xmin is exactly zero
    if(xmin>0)xminexp=floor(log10(xmin)); 
    if(xmin<0)xminexp=floor(log10(-xmin)); 

    if(ymin>0)yminexp=floor(log10(ymin));
    if(ymin<0)yminexp=floor(log10(-ymin));

    xminfact=pow(10.0,xminexp); yminfact=pow(10.0,yminexp);
    xmin_scale=xmin/xminfact;   ymin_scale=ymin/yminfact;

    numbers_xy();
      ostringstream xmod;
      if(xtimesdiv){
        if(xexp<0){
           xmod << '*'; xmod << '1'; xmod << 'e'; xmod << '+';
           xmod << fabs(xexp);}
           else{
           xmod << '/'; xmod << '1'; xmod << 'e'; xmod << '+';
           xmod << fabs(xexp);}
        }
         else {xmod <<' ';}

        xtextmod=xmod.str();

      ostringstream ymod;
      if(ytimesdiv){
        if(yexp<0){
           ymod << '*'; ymod << '1'; ymod << 'e'; ymod << '+';
           ymod << fabs(yexp);}
           else{
           ymod << '/'; ymod << '1'; ymod << 'e'; ymod << '+';
           ymod << fabs(yexp);}
        }
         else {ymod <<' ';}

        ytextmod=ymod.str();

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
      if(!yaddsubtract)yst << ytext << ytextmod;
      if(iyunits==1){
        yst << ' ';
        yst << yunits;
      }

      yaxistext=yst.str();
      } //endif iytext

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
			    speed=speed+0.01;
			    angspeed=angspeed+0.001;
			    if(speed > 60)speed=60;
			    if(angspeed  > 0.15)angspeed=0.15;
		    }
		    if(z_Pressed){
			    speed=speed-0.01;
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
   //

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

      float xgl;
      int igl;
      glLineWidth(1.0);
      xgl=1.0;
      igl=gl2psLineWidth(xgl);

      //LIGHTS ARE OFF  - KEEP CODE ANYWAY FOR NOW
      if(LIGHTS)
	      glEnable(GL_LIGHTING);
      else
	      glDisable(GL_LIGHTING);
     if(LIGHTS){



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
	      igl=gl2psPointSize(2.0);
	      xgl=2.0;
	      glPointSize(xgl);
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

              if(movetext){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	          DrawTextMove(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;   //pickmatrix
	      DrawTextMove(drawbox);
              }
              MouseOn=false;

             if(stylechange){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
              glEnable(GL_BLEND);
                  bool drawbox;
	          drawbox=true;
	          DrawCurveCol(drawbox);  //draw
              glDisable(GL_BLEND);
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;   //pickmatrix
	      DrawCurveCol(drawbox);
              }
              MouseOn=false;

             if(legendplot){
               bool drawbox;
               glDisable(GL_DEPTH_TEST);
               glDisable(GL_LIGHTING);
	          drawbox=true;
	          DrawLegend(drawbox);  //draw
               glEnable(GL_DEPTH_TEST);
               glEnable(GL_LIGHTING);

	       drawbox=false;   //pickmatrix
	       if(!post_Pressed)DrawLegend(drawbox);
               
               //if you make a call to gl2ps where
                //selection mode is being switched
                // you get no output!
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

      if(drawscene){
      int matl=2;

      if(LIGHTS){ //no lights but keep for now
      float mat_amb[4]={RedM[matl][0], GreenM[matl][0],BlueM[matl][0],
		                AlphaM[matl][0] };
      float mat_diff[4]={RedM[matl][1], GreenM[matl][1],BlueM[matl][1],
		                AlphaM[matl][1] };
      float mat_spec[4]={RedM[matl][2], GreenM[matl][2],BlueM[matl][2],
		                AlphaM[matl][2] };

      float shine[]={ShineM[2][0]};
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
        }
        else
	{
	glColor3ub((int)(255*RedM[matl][0]),(int)(255*GreenM[matl][0])
			,(int)(255*BlueM[matl][0]));
	}

      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      }  //endif drawscene 


 //     glLineStipple(1,LINE0);

      int igl;
      float xgl;

      double xlow,ylow,xhigh,yhigh; 
      //Camera is at  (0,0,3000) OpenGL coords
      xlow=-1200.0; ylow=-800.0;  //keep 2d bounding box the same
      xhigh=800.0; yhigh=800.0;
      zed=0.0; 
      bool stipple=false;

          if(drawscene){
                   // X axis BOUNDING BOX AND TICKMARKS
                   //shift3 and 4 both zero
                   //numbers for x axis lower bounding box edge
                   glColor3ub(0,0,0);
                   double xt,yt,zt;
                   double longtick=70.0; double shorttick=longtick/2.0;

                   xt=xlow+(x_start-(xmin-xsubtract))/xrange*(xhigh-xlow)-shift1; yt=shift4; zt=0.0;
                   glPushMatrix();
                   glTranslated(xt-shift1,ylow-150.0+yt,zt);  //initial translation with shift
                   xt=xstep/xrange*(xhigh-xlow);  //for subsequent translations
                   yt=0.0;
                   for(int i=0; i< ixnumb; i++){
                      glPushMatrix();
		      font1->draw(xstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();

                  //numbers for x axis upper bounding box edge
                   xt=xlow+(x_start-(xmin-xsubtract))/xrange*(xhigh-xlow)-shift1; yt=shift3; zt=0.0;
                   glPushMatrix();
                   glTranslated(xt-shift1,yhigh+150.0+yt,zt);  //initial translation including shift
                   xt=xstep/xrange*(xhigh-xlow); //for subsequent translations
                   yt=0.0;
                   for(int i=0; i< ixnumb; i++){
                      glPushMatrix();
                      font1->draw(xstrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();

                   //major tick marks for x axis bounding box and x axis if required
                   xt=xlow+(x_start-(xmin-xsubtract))/xrange*(xhigh-xlow); yt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   xt=xstep/xrange*(xhigh-xlow);  //for subsequent translations
                   for(int i=0; i<ixnumb; i++){
                      glBegin(GL_LINES);
                          glVertex3f(0.0,ylow-longtick,0.0); glVertex3f(0.0,ylow,0.0);
                          glVertex3f(0.0,yhigh,0.0); glVertex3f(0.0,yhigh+longtick,0.0);
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
                          glVertex3f(0.0,ylow-shorttick,0.0); glVertex3f(0.0,ylow,0.0);
                          glVertex3f(0.0,yhigh,0.0); glVertex3f(0.0,yhigh+shorttick,0.0);
                      glEnd();
                      }
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();


                   //Y BOUNDING BOX NUMBERS AND TICKMARKS

                   //numbers for y axis low bounding box edge
                   yt=ylow+(y_start-(ymin-ysubtract))/yrange*(yhigh-ylow)-shift2; xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xlow-shift5,yt-shift2,zt);  //initial translation with shift
                   yt=ystep/yrange*(yhigh-ylow);  //for subsequent translations
                   for(int i=0; i< iynumb; i++){
                      glPushMatrix();
		      font1->draw(ystrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();

                  //numbers for y axis high bounding box edge
                   yt=ylow+(y_start-(ymin-ysubtract))/yrange*(yhigh-ylow)-shift2; xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xhigh-shift6,yt-shift2,zt);  //initial translation including shift
                   yt=ystep/yrange*(yhigh-ylow); //for subsequent translations
                   for(int i=0; i< iynumb; i++){
                      glPushMatrix();
		      font1->draw(ystrings[i].c_str());
                      glPopMatrix();
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();

                   //major tick marks for y axis bounding box and y axis 
                   yt=ylow+(y_start-(ymin-ysubtract))/yrange*(yhigh-ylow); xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   yt=ystep/yrange*(yhigh-ylow);  //for subsequent translation
                   for(int i=0; i<iynumb; i++){
                      glBegin(GL_LINES);
                        glVertex3f(xlow,0.0,0.0); glVertex3f(xlow-longtick,0.0,0.0);
                        glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh+longtick,0.0,0.0);
                      glEnd();
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();

                   //minor tick marks for y axis bounding box and y axis 
                   yt=ylow+(y_start2-(ymin-ysubtract))/yrange*(yhigh-ylow); xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   yt=ystep2/yrange*(yhigh-ylow);  //for subsequent translation
                   for(int i=0; i<iynumb2; i++){
                      if(ynumbers2[i]+ysubtract>=ymin && ynumbers2[i]+ysubtract<=ymax){
                      glBegin(GL_LINES);
                        glVertex3f(xlow,0.0,0.0); glVertex3f(xlow-shorttick,0.0,0.0);
                        glVertex3f(xhigh,0.0,0.0); glVertex3f(xhigh+shorttick,0.0,0.0);
                      glEnd();
                      }
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();


      //2-D bounding box
      glBegin(GL_LINES);
        glVertex3f(xlow,ylow,zed); glVertex3f(xhigh,ylow,zed);
        glVertex3f(xlow,yhigh,zed); glVertex3f(xhigh,yhigh,zed);
        glVertex3f(xlow,ylow,zed); glVertex3f(xlow,yhigh,zed);
        glVertex3f(xhigh,ylow,zed); glVertex3f(xhigh,yhigh,zed);
      glEnd();


       if(!xboth){
          double shifter;
          shifter=xmax/(xmax-xmin)*(xhigh-xlow);
          glBegin(GL_LINES);
             glVertex3f(xhigh-shifter,ylow,zed); glVertex3f(xhigh-shifter,yhigh,zed);
          glEnd();

             //major y tick marks
                   yt=ylow+(y_start-(ymin-ysubtract))/yrange*(yhigh-ylow); xt=0.0; zt=0.0; //initial translation
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   yt=ystep/yrange*(yhigh-ylow);  //for subsequent translations
 
                   for(int i=0; i<iynumb; i++){
                      glBegin(GL_LINES);
                        glVertex3f(xhigh-shifter+35.0,0.0,0.0);
		       	glVertex3f(xhigh-shifter-35.0,0.0,0.0);
                      glEnd();
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();

                  //minor tick marks for y 
                   yt=ylow+(y_start2-(ymin-ysubtract))/yrange*(yhigh-ylow); xt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   yt=ystep2/yrange*(yhigh-ylow);  //for subsequent translation
                   for(int i=0; i<iynumb2; i++){
                      if(ynumbers2[i]+ysubtract>=ymin && ynumbers2[i]+ysubtract<=ymax){
                      glBegin(GL_LINES);
                        glVertex3f(xhigh-shifter-shorttick/2.0,0.0,0.0); 
                        glVertex3f(xhigh-shifter+shorttick/2.0,0.0,0.0);
                      glEnd();
                      }
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();

          }

          if(!yboth){
            double shifter;
            shifter=ymax/(ymax-ymin)*(yhigh-ylow);
            glBegin(GL_LINES);
               glVertex3f(xlow,yhigh-shifter,zed); glVertex3f(xhigh,yhigh-shifter,zed);
            glEnd();

            //major x tick marks 
            xt=xlow+(x_start-(xmin-xsubtract))/xrange*(xhigh-xlow); yt=0.0; zt=0.0; 
            glPushMatrix();
            glTranslated(xt,yt,zt); //initial translation step
            xt=xstep/xrange*(xhigh-xlow);  //for subsequent translations
            for(int i=0; i<ixnumb; i++){
               glBegin(GL_LINES);
                  glVertex3f(0.0,yhigh-shifter+35.0,0.0); glVertex3f(0.0,yhigh-shifter-35.0,0.0);
               glEnd();
               glTranslated(xt,yt,zt);
           }
           glPopMatrix();
                   //minor x tickmarks
                   xt=xlow+(x_start2-(xmin-xsubtract))/xrange*(xhigh-xlow); yt=0.0; zt=0.0; 
                   glPushMatrix();
                   glTranslated(xt,yt,zt); //initial translation step
                   xt=xstep2/xrange*(xhigh-xlow);  //for subsequent translations
                   for(int i=0; i<ixnumb2; i++){
                      if(xnumbers2[i]+xsubtract>=xmin && xnumbers2[i]+xsubtract<=xmax){
                      glBegin(GL_LINES);
                          glVertex3f(0.0,yhigh-shifter-shorttick/2.0,0.0); 
                          glVertex3f(0.0,yhigh-shifter+shorttick/2.0,0.0); 
                      glEnd();
                      }
                      glTranslated(xt,yt,zt);
                    }
                   glPopMatrix();
           }
      if(ixtext==1){
      glPushMatrix();
         glTranslated(-500.0-shift7,ylow-250.0-shift8,0.0);
         font12->draw(xaxistext.c_str());
      glPopMatrix();
      }   //endif for is there any x axis text

      if(iytext==1){
      glPushMatrix();
         glRotatef(90.0,0.0,0.0,1.0);  //rotate anticlock
         glTranslated(-200.0-shift10,-xlow+180.0-shift9,0.0);//remember xlow is negative, and that after rotation y is towards old -x
         font12->draw(yaxistext.c_str());
      glPopMatrix();

      }   //endif for is there any y axis text



	  } //end draw scene


  //Now plot the bloody graph!

      if(drawlines && drawscene){


      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

      for(int i=0; i<nplots; i++){

 	     if(LIGHTS){
              //aint gonna happen
               cout << "LIGHTS MUST BE SET TO FALSE FOR PLOTIT" << endl;
               exit(0);
	     }
	     else
	     {
	glColor3ub((int)(255*RedPC1[*(ncol+i)][1]),
                   (int)(255*GreenPC1[*(ncol+i)][1]),(int)(255*BluePC1[*(ncol+i)][1]));
	}  //endif for LIGHTS

         glLineWidth((float)*(npoint+i));
	 igl=gl2psLineWidth((float)*(npoint+i));

        if(*(ntype+i)==0){ //plot lines

          if(*(nstyle+i)==0)glLineStipple(1,LINE0);
          if(*(nstyle+i)==1)glLineStipple(1,LINE1);
          if(*(nstyle+i)==2)glLineStipple(1,LINE2);
          if(*(nstyle+i)==3)glLineStipple(1,LINE3);
          if(*(nstyle+i)==4)glLineStipple(1,LINE4);

//  the 1 is a stretch factor (dont strectch)
          if(*(nstyle+i)>0){
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
          for(int j=0; j< *(ndata+i)-1; j++){
              double x1,y1,x2,y2;
              
              x1=*(*(x+i)+j); y1=*(*(y+i)+j);
              x2=*(*(x+i)+j+1); y2=*(*(y+i)+j+1);

// cout << i << " " << j <<  "  " << x1  << "  " << y1 << "  " << x2 << "  " << y2 << endl;

              x1=xlow+(x1-xmin)/xrange*(xhigh-xlow);
              y1=ylow+(y1-ymin)/yrange*(yhigh-ylow);
              x2=xlow+(x2-xmin)/xrange*(xhigh-xlow);
              y2=ylow+(y2-ymin)/yrange*(yhigh-ylow);
              glVertex3d(x1,y1,0.0);
              glVertex3d(x2,y2,0.0);
          }
          glEnd();
	  if(stipple){
          gl2psDisable(GL2PS_LINE_STIPPLE);
	  gl2psDisable(GL2PS_BLEND);
          glDisable(GL_LINE_STIPPLE);
	  stipple=false;
	  }
      }
       if(*(ntype+i)==1){ //plot points

         glPointSize((float)*(npoint+i));
	 igl=gl2psPointSize((float)*(npoint+i));


          glBegin(GL_POINTS);
          for(int j=0; j< *(ndata+i); j++){
              double x1,y1,x2,y2;
              
              x1=*(*(x+i)+j); y1=*(*(y+i)+j);

              x1=xlow+(x1-xmin)/xrange*(xhigh-xlow);
              y1=ylow+(y1-ymin)/yrange*(yhigh-ylow);
              glVertex3d(x1,y1,0.0);
          }
          glEnd();
      }

       } // end nplots loop


    } // endif lines and drawscene



}

