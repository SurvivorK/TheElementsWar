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
//sleep
int Battle_Back_Available(double x,double y)//  back to the main console
{  drawRectangle(10,0.8,1.2, 0.8, 1);
  if(x>=10&&x<=10+1.2&&y>=0.8&&y<=0.8+0.8) return 1;
return 0;
}
int choose_circle(double x,double y)
{  double cx = GetWindowWidth() ;
   double cy = GetWindowHeight() ;  
   double ox1=cx/2-2-1.6,oy1=3*(cy/4)-1,r1=1.6;
   double ox2=cx/2-0.6,oy2=3*(cy/4)-2,r2=1.3;
   double ox3=cx/2+1.4,oy3=3*(cy/4)-4,r3=1.0;
   double ox4=cx/2+1.6,oy4=3*(cy/4)-6.2,r4=0.8;
   if(fabs(ox1-x)*fabs(ox1-x)+fabs(oy1-y)*fabs(oy1-y)<=r1*r1)  return 1;
   if(fabs(ox2-x)*fabs(ox2-x)+fabs(oy2-y)*fabs(oy2-y)<=r2*r2)  return 2;
   if(fabs(ox3-x)*fabs(ox3-x)+fabs(oy3-y)*fabs(oy3-y)<=r3*r3)  return 3;       
   if(fabs(ox4-x)*fabs(ox4-x)+fabs(oy4-y)*fabs(oy4-y)<=r4*r4)  return 4;
return 0;	
}
int choose_new_load(double x,double y,int fl)// 1 new  0 laod
{  double cx = GetWindowWidth() ;
   double cy = GetWindowHeight() ;  
   double ox1=cx/2-2-1.6,oy1=3*(cy/4)-1,r1=1.6;
   double ox2=cx/2-0.6,oy2=3*(cy/4)-2,r2=1.3;
   double ox3=cx/2+1.4,oy3=3*(cy/4)-4,r3=1.0;
   double ox4=cx/2+1.6,oy4=3*(cy/4)-6.2,r4=0.8;
   if(fl==1)  return  y>=oy1;
   if(fl==2)  return  y>=oy2;
   if(fl==3)  return  y>=oy3;
   if(fl==4)  return  y>=oy4; 
   return 0;

}
static void draw_circle1()
{ double r=1.6;
  double cx = GetWindowWidth() ;
  double cy = GetWindowHeight() ; 
  double ox=cx/2-2-1.6;
  double oy=3*(cy/4)-1;
  DefineColor("fire1",238.0/255,126.0/255,98.0/255);//tot 462
  SetPenColor("fire1");
  MovePen(ox+r,oy) ;// O:cx/2-2-1.6,3*(cy/4)-1
  StartFilledRegion(1); 
  DrawArc(r, 0, 360);
  EndFilledRegion();
  
  DefineColor("fire2",246.0/255,178.0/255,118.0/255);
  SetPenColor("fire2");
  MovePen(ox+r,oy) ;// O:cx/2-2-1.6,3*(cy/4)-1
  StartFilledRegion(1); 
  DrawArc(1.6, 0, 180);
  EndFilledRegion();
  SetPenColor("backcolor");
  SetPointSize(25);
  drawLabel(ox-0.3, oy+0.5, "New");	
  drawLabel(ox-0.3, oy-0.8, "Load");
  
}
static void draw_circle2()
{ double r=1.3;
  double cx = GetWindowWidth() ;
  double cy = GetWindowHeight() ; 
  double ox=cx/2-0.6;
  double oy=3*(cy/4)-2;
  DefineColor("Air1",34.0/255,146.0/255,145.0/255); //  fire 462
  SetPenColor("Air1");
  MovePen(ox+r,oy) ;// O:cx/2-2-1.6,3*(cy/4)-1
  StartFilledRegion(1); 
  DrawArc(r, 0, 360);
  EndFilledRegion();
  
  DefineColor("Air2",130.0/255,200.0/255,196.0/255);
  SetPenColor("Air2");
  MovePen(ox+r,oy) ;// O:cx/2-2-1.6,3*(cy/4)-1
  StartFilledRegion(1); 
  DrawArc(r, 0, 180);
  EndFilledRegion();
  SetPenColor("backcolor");
  SetPointSize(22);
  drawLabel(ox-0.3, oy+0.4, "New");	
  drawLabel(ox-0.3, oy-0.6, "Load");
  
}
static void draw_circle3()
{ double r=1.0;
  double cx = GetWindowWidth() ;
  double cy = GetWindowHeight() ; 
  double ox=cx/2+1.4;
  double oy=3*(cy/4)-4;
  DefineColor("Water1",56.0/255,147.0/255,189.0/255);
  SetPenColor("Water1");
  MovePen(ox+r,oy) ;// O:cx/2-2-1.6,3*(cy/4)-1
  StartFilledRegion(1); 
  DrawArc(r, 0, 360);
  EndFilledRegion();
  
  DefineColor("Water2",156.0/255,199.0/255,219.0/255);
  SetPenColor("Water2");
  MovePen(ox+r,oy) ;// O:cx/2-2-1.6,3*(cy/4)-1
  StartFilledRegion(1); 
  DrawArc(r, 0, 180);
  EndFilledRegion();
  SetPenColor("backcolor");
  SetPointSize(19);
  drawLabel(ox-0.3, oy+0.5, "New");	
  drawLabel(ox-0.3, oy-0.8, "Load");
  
}
static void draw_circle4()
{ double r=0.8;
  double cx = GetWindowWidth() ;
  double cy = GetWindowHeight() ; 
  double ox=cx/2+1.6;
  double oy=3*(cy/4)-6.2;
  DefineColor("Earth1",108.0/255,90.0/255,89.0/255);//tot 287
  SetPenColor("Earth1");
  MovePen(ox+r,oy) ;// O:cx/2-2-1.6,3*(cy/4)-1
  StartFilledRegion(1); 
  DrawArc(r, 0, 360);
  EndFilledRegion();
  
  DefineColor("Earth2",170.0/255,137.0/255,135.0/255);
  SetPenColor("Earth2");
  MovePen(ox+r,oy) ;// O:cx/2-2-1.6,3*(cy/4)-1
  StartFilledRegion(1); 
  DrawArc(r, 0, 180);
  EndFilledRegion();
  SetPenColor("backcolor");
  SetPointSize(15);
  drawLabel(ox-0.2, oy+0.3, "New");	
  drawLabel(ox-0.2, oy-0.5, "Load");
  
}
void draw_Battle()
{ double cx = GetWindowWidth() ;
  double cy = GetWindowHeight() ;  
  DefineColor("backcolor",52.0/255,51.0/255,53.0/255);
  SetPenColor("backcolor");
  drawRectangle(0, 0, cx, cy,1); 
  DefineColor("tmp",200.0/255,200.0/255,200.0/255);
  SetPenColor("tmp");
  SetPointSize(35);
  drawLabel(cx/2-3.0, cy/2+3.5, "Choose A Battle");	
  draw_circle1();
  draw_circle2();
  draw_circle3();
  draw_circle4();
  DefineColor("tmp",80.0/255,80.0/255,80.0/255);
  SetPenColor("tmp");
  drawRectangle(10,0.8,1.2, 0.8, 1);
  drawBox(10,0.8,1.2, 0.8, 0,"Back", 'M', "White");
}

