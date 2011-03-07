#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <iomanip>  //stuff like set precision
#include <fstream>   //file read write
#include <string>
#include <sstream>  //read and write to string

/*
 * In  /usr/include/GL/  */

#include <GL/gl.h>
#include <GL/glu.h>

#include "/usr/include/SDL/SDL.h"
#include "/usr/local/include/XFiles/D3Dvec.h"
#include "/usr/local/include/XFiles/D2Dvec.h"
#include "/usr/local/include/XFiles/Triangle.h"
#include "/usr/local/include/XFiles/throwcatch.h"

double speed=50.0, angspeed=0.05;


typedef unsigned char byte;
typedef unsigned short int USHORT;
typedef unsigned int UINT;
typedef unsigned int DWORD;  //yep, a DWORD is the same as a UINT...
                             //we use it for stuff that has DWORD
			     //or glEnum types.

const USHORT WIDTH=800, HEIGHT=600;
const USHORT SCREEN_DEPTH=16;

const char* WindowTitle="Plot Contours";
bool picking=false;

extern const double twopi,pi;  //initialised externally

/*********************************************************/
/*           for periodic boundary condition special case */
bool startoffx=true;
bool startoffy=true;
bool launch=true;
/*************************************************************/
bool periodic_xz=false;  //periodiv in PRESENTATION and in OpenGL coords
bool periodicbcs=false;  //actual periodic boundary conditions in xy
bool collisiontest=false;
bool foggy=false;
bool drawlines=true;
bool drawback=true;  // draw background when controls are up
bool PickTri=false;  //if false, we pick nodes and not triangles
bool Gouraud=false;  //smooth Gouraud shading
bool Picking=false;  //don't pick anyithing if false
/********************MODES***********************************/
bool twodee=false;  // camera moves in xz only

                      //One, but ONE ONLY  of these three
		      //MUST be true
bool freedom=true;      // if true viewer is free to move anywhere
bool tethered=false;   //  if true viewer is attached to fixed point by a boom
bool staked=false;    //   if true viewer is not free to move, but can look about

bool wander=true;    //one of these must be set true if free is true
bool flight=false;

bool aeroplane=false;   // if true we have aeroplane roll - pitch control

                        
bool boom=false;      //  needed for tethered only 
                      //  if boom true  make exwhyzed false
bool exwhyzed=true;   //  if tethered make boom false if exwhyzed is true
                      //  if wander must always be true
		      //  if flight can be true or false
		      //  make false if aeroplane true
	      
bool hidemousecursor=true;      

/*************************************************************/
int iside, ihalfside;   // iside is the number of segments per side
             //not the number of nodes!
double xlength, xside, scalefac;
int ix, iz;
int ixold, izold; 
int diffx, diffz;
int diffoldx, diffoldz;
int yshiftedge, xshiftedge;
double **xshift, **yshift;
int **index1, **index2;

void SetShiftX(int);
void SetShiftY(int);

/**********************************************************************/
D3Dvec *NodeV;
Triangle* Triangles;
D3Dvec* edges1;
D3Dvec* edges2;
D3Dvec* Normals;
D3Dvec* NormalsG;
#include "/usr/local/include/XFiles/List.h"
#include "/usr/local/include/XFiles/Node1.h"
typedef CMyNode1<int>  ListNode;
typedef CMyNode1<char>  ListNode_char;
typedef CMyLinkedList<ListNode> intList;
typedef CMyLinkedList<ListNode_char> charList;
int const MD=4;  //MAXIMUM DEPTH OF TREE (depth ranges from 0 to MD
    intList** CollideTri; 
    int nlists;
    intList*  NodeList;  
    charList*  WhichList;  
//intList hangs is attached to a tree branch, iNodeList is attatched to a node.



#include "/usr/local/include/XFiles/TriOctNode.h" 
#include "/usr/local/include/XFiles/TriOctTree.h"
typedef CMyOctNode <D3Dvec> ONode; //An ONode shall hold a vector
                                   //describing the compare point
				   // and a list of integers
				   // (Triangle array indexes)
typedef CMyTriOctTree<ONode> OTree;   //OctTree consists of nodes
        OTree* CollideTree;
/**********************************************************************/
#include "/usr/local/include/XFiles/Dmatrix.h" 
#include "/usr/local/include/XFiles/Solver.h" 
/**********************************************************************/
void Solver(int &dim, double &maxerr, Dmatrix& Matrix, Dvector& rhs, Dvector& SolveVec);  
/**********************************************************************/

D3Dvec RealCamPos;  //periodic boundary conditions
                    //CamPos thinks it  wanders in infinite space
		    //But RealCamPos knows about the pbc.
double X1, X2, Y1, Y2, Z1, Z2;
#include "/usr/local/include/XFiles/Camera.h"
#include "/usr/local/include/XFiles/gl2ps.h"

extern int VideoFlags;
extern SDL_Surface * MainWindow;

extern double speed;
extern const double convert;


// Prototypes for functions
//void EventLoop(CCam  & Camera1);
void EventLoop();
void RenderScene(CCam  & Camera1);
void PickObjects();
void ProcessHitsLP(int, UINT *);
void ProcessHitsLC(int, UINT *);
void ProcessHitsLB(int, UINT *);
void ProcessHitsMC(int, UINT *);
void ProcessHitsDT(int, UINT *);
void ProcessHitsPC1(int, UINT *);
void ProcessHitsLeg(int, UINT *);
void ProcessHitsW(int, UINT *);
void ProcessTriangleHits(int, UINT *);
void ProcessNodeHits(int, UINT *);
void SetUp();
void ToggleWindow(void);
void MakeWindow(const char *Name, 
		const USHORT WIDTH,
	        const USHORT HEIGHT,
		int VideoFlags);
void SizeOpenGLScreen(const USHORT, const USHORT);
void Init();
void InitialiseGL(int, int);
void HandleKeyPress(SDL_keysym * );
void HandleKeyRelease(SDL_keysym *);
void CheckMove(CCam &);
void CamStrafe2(double );
int Screenshot(SDL_Surface *screen, char *filename);

void CreateTexture(unsigned int textureArray[], char *strFilename, int textureID);

void OrthoMode(double , double , double, double);
void PerspectiveMode();
void DrawLightPos(bool);
void DrawLightCol(bool);
void DrawMatCol(bool);
void DrawLogicBox(bool);
void DrawTextMove2(bool);
void DrawCurveCol(bool);
//void DrawLegend(bool);
void DrawWaxis(bool);

extern UINT base;
//bitmap font functions
void buildFont(void); 
void QuitFont(int );    
void KillFont();
void glPrint( char *);

void SetShiftX(int);
void SetShiftY(int);

void DrawScene(CCam &, bool);


int arg_count;
char **arg_list;

#include "/usr/local/include/XFiles/Init.h"
int nplots;   
const int nplotsmax=40;
int *ndata, *ntri, *ntype, *ncol, *npoint, *ntri_or_point;
// ntype=1 for line 0 for point, npoint is the line thickness or pointsize

double **x;  //the data
double **y;
double **z;
int **triangles;

double xmin,xmax,xrange;
double ymin,ymax,yrange;
double zmin,zmax,zrange;

double xexp,yexp,zexp;
double xfact,yfact,zfact;
double xrange_scale, yrange_scale, zrange_scale;
bool xmin_zero=false, xmax_zero=false;
bool ymin_zero=false, ymax_zero=false;
bool zmin_zero=false, zmax_zero=false;
bool xboth=false, yboth=false, zboth=false;

double xminexp=-1000.0,yminexp=-1000.0,zminexp=-1000.0;
double xminfact,yminfact,zminfact;
double xmin_scale,ymin_scale,zmin_scale;

bool  xaddsubtract=false, yaddsubtract=false,zaddsubtract=false;

int ixnumb, iynumb, iznumb;  //number of major tick marks and axis numbers
int ixnumb2,iynumb2, iznumb2;  //number of minor tickmarks
int iwnumb;  //Nicked DrawWaxis from PlotVol, the w's shadow the zeds
double *wred, *wgreen, *wblue;

double xminshift,xstep,xstep_scale,x_start,xsubtract;  //different to xstart in SetUp.h
double yminshift,ystep,ystep_scale,y_start,ysubtract;
double zminshift,zstep,zstep_scale,z_start,zsubtract;  
double x_start2,y_start2, z_start2,xstep2,ystep2,zstep2; //minor tickmarks

double xnumbers[13], ynumbers[13], znumbers[13], wnumbers[13];
double xnumbers2[130], ynumbers2[130], znumbers2[130]; //for minor ticks algorithm
string xstrings[13], ystrings[13], zstrings[13], wstrings[13];

//keep 2d bounding box the same
//Camera is at  (0,0,3000) OpenGL coords
double xlow=-800.0,zlow=-800.,ylow=-800.,xhigh=800.0,yhigh=800,zhigh=800.0;

int smallticksx,smallticksy,smallticksz;

string xtext,xunits,xaxistext,ytext,yunits,yaxistext,ztext,zunits,zaxistext;
int ixtext,ixunits,iytext,iyunits,iztext,izunits;
string wtext,wunits;
string xtextmod,ytextmod,ztextmod,wtextmod;
bool xtimesdiv,ytimesdiv,ztimesdiv;

double shift1;  // shift all x axis numbers left  x 1&4, y 2&5, z 3&6
double shift2;  // shift all y axis numbers out
double shift3;  // shift all z axis numbers down
double shift4;  // shift all x numbers  out/in
double shift5;  // shift all y numbers  left/right
double shift6;  // shift all z  numbers  up/down
double shift7;  // shift x axis text left
double shift8;  // shift x axis text in/out
double shift9; // shift y axis text in/out
double shift10; // shift y axis text  left/right
double shift11; // shift z axis text  up/down
double shift12; // shift z axis text  radially

bool LegendExists;
string *LegendStrings;

bool blendon=true, autoblend=true;
bool drawgrid=false, drawcontours=true;



double **contx1, **conty1, **contz1,  **contx2, **conty2, **contz2;
bool  **cont;  // true if a contour line segment is in triangle

int klinesmax=3; //maxium of three contours per triangle
int **klines;

//blendon means we do blending of surfaces, if
//autoblend, then the alpha factors are chosen
//automatically by the number of surfaces and
//values on the material colour control are
//overriden

#include "/usr/local/include/XFiles/numbers_xyz.h"
