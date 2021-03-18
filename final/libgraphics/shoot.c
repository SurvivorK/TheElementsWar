#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include "shoot.h"
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

void Air_Shoot(double sx,double sy,double tx,double ty)
{ MovePen(sx,sy);
  DefineColor("air1",238.0/255,126.0/255,98.0/255);//tot 462
  SetPenColor("air1");
  //DrawLine(tx-sx,ty-sy);
}
void Earth_shoot(double sx,double sy)
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22;
   double r=2*row_width;
   DefineColor("Earth1",108.0/255,90.0/255,89.0/255);//tot 287
   SetPenColor("Earth1");
   MovePen(sx,sy);
   DrawArc(r, 0, 360);
}
static void Draw_Tri(double tx,double ty)
{	double Siz=0.67;
    double base=1.0*0.2;
    double height=(1.717/2)*0.2;
    MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, height*Siz);
    DrawLine(-base*Siz / 2, -height*Siz);
    EndFilledRegion();
}
void Draw_firing(double tx,double ty)
{ 
	DefineColor("Fire1",238.0/255,126.0/255,98.0/255);
	SetPenColor("Fire1");
	double firex=tx-0.2,firey=ty+0.1+0.01;
  double duan=0.2*2/3.0;
  Draw_Tri(firex,firey);
  Draw_Tri(firex+duan,firey);
  Draw_Tri(firex+2*duan,firey);
}
void Draw_frozing(double tx,double ty)
{  DefineColor("Water2",156.0/255,199.0/255,219.0/255);
  SetPenColor("Water2");
	double waterx=tx-0.2,watery=ty-0.2+0.01;
  double duan=0.2*2/5.0;
  int i;
  for(i=0;i<5;i++)
  {MovePen(waterx+i*duan,watery); DrawLine(0.1,0.1);}
  
}
void Fire_Shoot(double sx,double sy,double tx,double ty)
{ MovePen(sx,sy);
  DefineColor("Fire1",238.0/255,126.0/255,98.0/255);//tot 462
  SetPenColor("Fire1");
  //DrawLine(tx-sx,ty-sy);
  Draw_firing(tx,ty);
}
void Water_Shoot(double sx,double sy,double tx,double ty)
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22;
   double r=2*row_width;
   DefineColor("Water1",108.0/255,90.0/255,89.0/255);//tot 287
   SetPenColor("Water1");
   MovePen(sx,sy);
   DrawArc(r, 0, 360);
  MovePen(sx,sy);
  DefineColor("Water2",156.0/255,199.0/255,219.0/255);
  SetPenColor("Water2");
  //Draw_frozing(tx,ty);
}
