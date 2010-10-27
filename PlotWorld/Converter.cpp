#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <iomanip>  
#include <fstream> 
#include <string>
#include <sstream>  
#include <vector>

using namespace std;

//Converts data from the World.dat file to what we can plot (goes into MyWorld.dat)

int main()
{


    string filename;   //wierd C++ string and standard c string mash up

    vector <double> **WorldLat; vector <double> **WorldLong; //pointer to vector
    vector <int> linelong;
    int nlines;


    ifstream file_in;

    filename="World.dat";
    file_in.close(); 
    file_in.open(filename.c_str());   
    double xlat,xlong;
    int kounter=0;
    nlines=0;
    //grep 1000 World.dat > outfile then wc outfile to get number
    WorldLat =new vector<double>*[1915];
    WorldLong =new vector<double>*[1915];
    for(int i=0; i<61632; i++){   //just do a wc on the file to get the number
         file_in >> xlat >> xlong;
         if( xlat > 999.0){
           if(i != 0){
               linelong.push_back(kounter);
               nlines++;
           //    cout <<"line " << nlines << " was " << kounter << " long " << endl;
               }
           WorldLat[nlines]=new vector<double>;
           WorldLong[nlines]=new vector<double>;
           kounter=0;
           }
           else
           {
           WorldLat[nlines]->push_back(xlat);
           WorldLong[nlines]->push_back(xlong);
           kounter++;
         }
    }
     cout << "Total number of lines in map is " << nlines << endl;
     int worldlines=nlines;

     ofstream file_out;
     file_out.open("MyWorld.dat", ios::out);
     double x,y;


     file_out <<  worldlines << endl;
     for(int iline=0; iline<worldlines; iline++){

        file_out << linelong.at(iline) << endl;         
        double minlong=-90., minlat=-180.;
        for(int i=0; i<linelong.at(iline); i++){
             x=WorldLat[iline]->at(i);
             y=WorldLong[iline]->at(i);
             file_out << x << "    " << y << endl;
      }}
}

