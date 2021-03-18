#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include <time.h>

#include "imgui.h"
#include "name.h"
static void Tower1(double x,double y,double Scale)
{y=y-0.1;
 double cx = GetWindowWidth() ;
 double cy = GetWindowHeight() ; 
 double row_width=cy/21;
 double colum_width=cx/22;
 double Siz=0.8*Scale;
 double base=1.0*row_width;
 double height=(1.717/2)*colum_width;
  //  SetPenColor("White");
    //MovePen(x-row_width/2,y-row_width/2);

    DefineColor("Earth1",108.0/255,90.0/255,89.0/255);//tot 287
    SetPenColor("Earth1");
	double  tx=x-row_width*Siz/2;
	double  ty=y-row_width*Siz/(2*1.7171);
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, height*Siz);
    DrawLine(-base*Siz / 2, -height*Siz);
    EndFilledRegion();
    
  Siz=0.4*Scale;  
    
    DefineColor("Earth2",170.0/255,137.0/255,135.0/255);
    SetPenColor("Earth2");
	  tx=x-row_width*Siz/2;
	  ty=y-row_width*Siz/(2*1.7171);
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, height*Siz);
    DrawLine(-base*Siz / 2, -height*Siz);
    EndFilledRegion();
 
}
static void Tower2(double x,double y,double Scale)
{y=y-0.1;
 double cx = GetWindowWidth() ;
 double cy = GetWindowHeight() ; 
 double row_width=cy/21;
 double colum_width=cx/22;
 double Siz=0.8*Scale;
 double base=1.0*row_width;
 double height=(1.717/2)*colum_width;
  //  SetPenColor("White");
    //MovePen(x-row_width/2,y-row_width/2);
    DefineColor("Water1",56.0/255,147.0/255,189.0/255);
    SetPenColor("Water1");
	double  tx=x-row_width*Siz/(2*1.7171);
	double  ty=y-row_width*Siz/2;
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(0,base*Siz);
    DrawLine(height*Siz,-base*Siz / 2);
    DrawLine( -height*Siz,-base*Siz / 2);
    EndFilledRegion();
    
  Siz=0.3*Scale;  
    
    DefineColor("Water2",156.0/255,199.0/255,219.0/255);
    SetPenColor("Water2");   
	tx=x-row_width*Siz/(2*1.7171);
	ty=y-row_width*Siz/2;
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(0,base*Siz);
    DrawLine(height*Siz,-base*Siz / 2);
    DrawLine( -height*Siz,-base*Siz / 2);
    EndFilledRegion();
 
}
static void Tower3(double x,double y,double Scale)
{y=y-0.15;
 double cx = GetWindowWidth() ;
 double cy = GetWindowHeight() ; 
 double row_width=cy/21;
 double colum_width=cx/22;
 double Siz=0.8*Scale;
 double base=1.0*row_width;
 double height=(1.717/2)*colum_width;
  //  SetPenColor("White");
    //MovePen(x-row_width/2,y-row_width/2);
    DefineColor("Air1",34.0/255,146.0/255,145.0/255); //  fire 462
    SetPenColor("Air1");
	double  tx=x-row_width*Siz/2;
	double  ty=y+row_width*Siz/(2*1.7171)+row_width*0.33*Siz;
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, -height*Siz);
    DrawLine(-base*Siz / 2, height*Siz);
    EndFilledRegion();
    
  Siz=0.4*Scale;  
    
    DefineColor("Air2",130.0/255,200.0/255,196.0/255);
    SetPenColor("Air2");
	tx=x-row_width*Siz/2;
	ty=y+row_width*Siz/(2*1.7171)+row_width*0.68*Siz;
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, -height*Siz);
    DrawLine(-base*Siz / 2, height*Siz);
    EndFilledRegion();
 
}
static void Tower4(double x,double y,double Scale)
{y=y-0.1;
 double cx = GetWindowWidth() ;
 double cy = GetWindowHeight() ; 
 double row_width=cy/21;
 double colum_width=cx/22;
 double Siz=0.8*Scale;
 double base=1.0*row_width;
 double height=(1.717/2)*colum_width;
  //  SetPenColor("White");
    //MovePen(x-row_width/2,y-row_width/2);
    DefineColor("fire1",238.0/255,126.0/255,98.0/255);//tot 462
    SetPenColor("fire1");
	double  tx=x+row_width*Siz/(2*1.7171);
	double  ty=y-row_width*Siz/2;
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(0,base*Siz);
    DrawLine(-height*Siz,-base*Siz / 2);
    DrawLine( height*Siz,-base*Siz / 2);
    EndFilledRegion();
    
  Siz=0.3*Scale;  
    
    DefineColor("fire2",246.0/255,178.0/255,118.0/255);
    SetPenColor("fire2");
	tx=x+row_width*Siz/(2*1.7171);
	ty=y-row_width*Siz/2;
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(0,base*Siz);
    DrawLine(-height*Siz,-base*Siz / 2);
    DrawLine( height*Siz,-base*Siz / 2);
    EndFilledRegion();
 
}
int Begin_Available(double x,double y)// start 1, about 2, exit 3
{  double cx = GetWindowWidth() ;
   double cy = GetWindowHeight() ; 
   //drawRectangle(cx/2-1.2, cy/2-0.2, 2.6, 0.6,0);
   //drawRectangle(cx/2-1.2, cy/2-1, 2.6, 0.6,0);
   //drawRectangle(cx/2-1.2, cy/2-1.8, 2.6, 0.6,0);
  if(x>=cx/2-1.2&&x<=cx/2-1.2+2.6&&y>=cy/2-0.2&&y<=cy/2-0.2+0.6) return 1;
  if(x>=cx/2-1.2&&x<=cx/2-1.2+2.6&&y>=cy/2-1&&y<=cy/2-1+0.6) return 2;
  if(x>=cx/2-1.2&&x<=cx/2-1.2+2.6&&y>=cy/2-1.8&&y<=cy/2-1.8+0.6) return 3;
 

return 0;
}
void  draw_begin()
{  double cx = 11.5 ;
   double cy = 11.0 ; 
   double row_width=cy/21;
   double colum_width=cx/22;
   DefineColor("backcolor",52.0/255,51.0/255,53.0/255);
   SetPenColor("backcolor");
   drawRectangle(0, 0, cx, cy,1); 
   Tower1(cx/2,0,15);
   Tower2(0,cy/2,12);
   Tower3(cx/2,cy-1.8,15);	
   Tower4(cx,cy/2,12);
   SetPointSize(35);
   DefineColor("tmp",200.0/255,200.0/255,200.0/255);
   SetPenColor("tmp");
   SetPointSize(1);
   int i;int which=1;double cmin=fabs(7.1165-TextStringWidth("THE WAR OF ELEMENT"));
   for(i=2;i<=100;i++)
      { SetPointSize(i);
 	   // double tmp=TextStringWidth("THE WAR OF ELEMENT");
 	     if(fabs(7.1165-TextStringWidth("THE WAR OF ELEMENT"))<cmin)  
		  {cmin=fabs(7.1165-TextStringWidth("THE WAR OF ELEMENT"));
		   which=i;
		  }
      }
    SetPointSize(which);

   drawLabel(cx/2-3.5, cy/2+1.5, "THE WAR OF ELEMENT");	
   
   SetPointSize(20);
   SetPenColor("White");
   drawLabel(cx/2-1, cy/2, "Start The War");
   drawLabel(cx/2-0.5, cy/2-0.8, "About");	
   drawLabel(cx/2-0.3, cy/2-1.6, "Exit");	
   
  /* SetPenColor("Red");
   drawRectangle(cx/2-1.2, cy/2-0.2, 2.6, 0.6,0);
   drawRectangle(cx/2-1.2, cy/2-1, 2.6, 0.6,0);
   drawRectangle(cx/2-1.2, cy/2-1.8, 2.6, 0.6,0);*/
   
}

