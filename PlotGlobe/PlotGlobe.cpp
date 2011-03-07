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
// seagods@btinternet.com.
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

#include "PlotGlobe.h"

#include <time.h>
clock_t Time1;
time_t rawtime1;
time_t rawtime2;


#include "/usr/local/include/XFiles/TrueType.h"

#include "/usr/local/include/XFiles/SetUp.h"  //loads of declarations and initialisations
#include "/usr/local/include/XFiles/Controls.h"
#include "/usr/local/include/XFiles/DrawLightPos.h"
#include "/usr/local/include/XFiles/DrawLightCol.h"
#include "/usr/local/include/XFiles/DrawMatCol.h"
#include "/usr/local/include/XFiles/DrawLogicBox.h"

#define LINE0 0xFFFF
#define LINE1 0x0101
#define LINE2 0x00FF
#define LINE3 0x1C47
#define LINE4 0x3F07

int g_RenderMode; 

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
      if(LIGHTS){
	      speed=5.0;
	      angspeed=0.01;}
      else
      {
	      speed=1.0;
	      angspeed=0.005;}

//Override Setup.h
LIGHTS=true;
g_RenderMode=GLU_FILL; // this is for quadrics only


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

    string filename;
    ifstream file_in;
    filename="/usr/local/include/XFiles/MyWorld.dat";
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

#include "/usr/local/include/XFiles/Init.cpp"
//
void RenderScene(CCam & Camera1)
{
 //  glClearColor(RedM[0][0],GreenM[0][0],BlueM[0][0] ,AlphaM[0][0]); 
   glClearColor(RedM[1][0],GreenM[1][0],BlueM[1][0] ,AlphaM[0][0]); //black background
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
	      glShadeModel(GL_SMOOTH);
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

      if(matcol){
              glDisable(GL_DEPTH_TEST);
              glDisable(GL_LIGHTING);
                  bool drawbox;
	          drawbox=true;
	      //    DrawMatCol(drawbox);  //draw
              glEnable(GL_DEPTH_TEST);
              glEnable(GL_LIGHTING);

	      drawbox=false;   //pickmatrix
	    //  DrawMatCol(drawbox);
	       }


 
	      SDL_GL_SwapBuffers();
}


void DrawScene(bool drawscene)
{
      int viewport[4];
      SDL_GetMouseState(&mousex, &mousey);

       if(!LIGHTS){
       glColor3ub(255,255,255);  //(without lighting enabled)
       }
       else{
       float mat_spec[]={1.0, 1.0, 1.0, 1.0};  //polygon's ref of specular light
       float mat_diff[]={1.0, 1.0, 1.0, 0.0};  //polygon's ref of diffuse light
       float mat_amb[]={1.0, 1.0, 1.0, 0.0};  //polygon's ref of ambient light

       float mat_shine[]= {2.0};  //polygon's specular reflection
	      // 0.0 to 128, small values give sharper specular reflection

       glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
       glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
       glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);
       glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shine);
       }
      
/*
       //camera  pos      view     up vector
       gluLookAt(
        Camera1.CamPos.GetX(),   Camera1.CamPos.GetY(),  Camera1.CamPos.GetZ(),
        Camera1.CamView.GetX(), Camera1.CamView.GetY(), Camera1.CamView.GetZ(),
        Camera1.jay.GetX(),   Camera1.jay.GetY(),   Camera1.jay.GetZ());   
*/
       // gluQuadObj is FOR WINDOWS USING glaux.h (doesn't exist in Linux)
       // In Linux, GLUquadric is defined in glu.h
       //gluQuadricObj *Quadric1=gluNewQuadric();
       
       GLUquadric *Quadric1= gluNewQuadric();

       glEnable(GL_TEXTURE_2D);
       gluQuadricTexture(Quadric1,true);

       gluQuadricDrawStyle(Quadric1, GL_FILL);

       Time1=clock();   //returns time since start in micro seconds.

       time(&rawtime1);
       struct tm* timeinfo;
       timeinfo=localtime(&rawtime1);
       timeinfo->tm_year=2008  ;
       timeinfo->tm_mon= 7 ;
       timeinfo->tm_mday= 1;

       mktime(timeinfo);   //timeinfo->wday will now contain the week day number

       //tm_sec, tm_min, tm_hour  all integers  + there is function difftime
                              

       float EarthRot,SunRot;
       //  One Day in Ten Seconds
       EarthRot=((float)Time1)/(1000000.0) *360.0/10.0;
       //  One Day in 100 Seconds
       EarthRot=((float)Time1)/(1000000.0) *360.0/100.0;
     //  EarthRot=((float)Time1)/( (float)CLOCKS_PER_SEC)*360.0/10.0;
     //



       SunRot=EarthRot/365.25*pi/180.;

   //    EarthRot=0.0;

       gLightPosition[0]=sin(SunRot);
       gLightPosition[1]=0;
       gLightPosition[2]=cos(SunRot);
       gLightPosition[3]=0;    //infinity    
       glLightfv(GL_LIGHT0,GL_POSITION,gLightPosition);
    //   glColor3ub(0,0,0);

       // Earth maps are Textures 18, 19, and 20
       glBindTexture(GL_TEXTURE_2D,gl_Texture[20]);

       glPushMatrix();

             glRotatef(-90.0, 1.0, 0.0, 0.0);  //rotate so North Pole is on GL y axis 

             glRotatef( 23.5, 0.0, 1.0, 0.0);  //rotate again

             glRotatef( EarthRot, 0.0, 0.0, 1.0);  //rotate again

             gluSphere(Quadric1,  1000.0, 600, 600); //   radius, then
            // "latitude and longitude  style slices and stacks
	
       glPopMatrix();


     if(!LIGHTS){
       glColor3ub(0,0,0);  // if lighting is disabled
     }
     else{

      float line_spec[]={0.0,0.0,0.0,1.0};  //line's ref of specular light
      float line_amb[]={0.0,0.0,0.0,1.0};  //line's ref of specular light
      float line_diff[]={0.0,0.0,0.0,0.0};  //line's ref of diffuse light
      float line_shine[]= {0.0};  //lines's sharpness of specular ref 

      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, line_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, line_amb);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, line_spec);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, line_shine);
      }


             glLineWidth(1.0); glColor3ub(0,0,0);
//           Draw vector shoreline World!
             glPushMatrix();
    //         glRotatef(-90.0, 1.0, 0.0, 0.0);  //rotate so North Pole is on GL y axis 
             glRotatef(-90., 0.0, 1.0, 0.0);  //rotate again
             glRotatef(-23.5, 1.0, 0.0, 0.0);  //rotate again
             glRotatef( EarthRot, 0.0, 1.0, 0.0);  //rotate again

             for(int k=0; k<nlines; k++){
                double xa,ya,za,xb,yb,zb;
                double tempx,tempy,tempz;

                for(int l=1; l<linelong[k]; l++){
                   ya=*(*(WorldLat+k)+l-1);
                   xa=*(*(WorldLong+k)+l-1);
                   yb=*(*(WorldLat+k)+l);
                   xb=*(*(WorldLong+k)+l);
                   xa=xa/convert; ya=ya/convert;
                   tempx=xa; tempy=ya; 
                   xa=1001.*cos(tempx)*cos(tempy);
                   ya=1001.*cos(tempx)*sin(tempy);
                   za=1001.*sin(tempx);
                   xb=xb/convert; yb=yb/convert;
                   tempx=xb; tempy=yb; 
                   xb=1001.*cos(tempx)*cos(tempy);
                   yb=1001.*cos(tempx)*sin(tempy);
                   zb=1001.*sin(tempx);
                   glBegin(GL_LINES);
                     glVertex3d(xa,za,-ya);glVertex3d(xb,zb,-yb);
                   glEnd();
                }
             }
           glPopMatrix();
       //

}

