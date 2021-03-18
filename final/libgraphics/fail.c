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
//restart: (0.5,0.5)  (2.5,1.7) ;  quit: (8.5,0.5) (10.5,1.7).
int  fail_available(double x,double y)
{ if(x>=0.5&&x<=2.5&&y>=0.5&&y<=1.7) return 1;
  if(x>=8.5&&x<=10.5&&y>=0.5&&y<=1.7) return 0;
return 0;
}
static  Draw_Tri_Rec(double sx,double sy)
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21.0/3.0;
   double colum_width=cx/22.0/3.0;
   SetPenColor("Black");
   drawRectangle(sx,sy,7*row_width,7*row_width,1);
   SetPenColor("White");
   drawRectangle(sx+row_width,sy+row_width,5*row_width,5*row_width,1);
   SetPenColor("Black");
   drawRectangle(sx+2*row_width,sy+2*row_width,3*row_width,3*row_width,1);
}
static void QRcode_generator()
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21.0/3.0;
   double colum_width=cx/22.0/3.0;
   double sx=3.5,sy=3.5;
   int i, j;
   for(i=0;i<21;i++)
   for(j=0;j<21;j++)
     { if(rand()%2)
         {SetPenColor("Black");
		  drawRectangle(sx+i*row_width, sy+j*row_width, row_width,row_width,1);  
		 }
	   else
	     { SetPenColor("White");
		  drawRectangle(sx+i*row_width, sy+j*row_width, row_width,row_width,1);  
		 }
	 }
   Draw_Tri_Rec(sx,sy);
   Draw_Tri_Rec(sx,sy+14*row_width);	
   Draw_Tri_Rec(sx+14*row_width,sy+14*row_width); 
   	  
}
void fail_surface()//restart: (0.5,0.5)  (2.5,1.7) ;  quit: (8.5,0.5) (10.5,1.7).
{  SetPenSize(1);
   double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   DefineColor("backcolor",72.0/255,71.0/255,73.0/255);
   SetPenColor("backcolor");
   drawRectangle(0, 0, cx, cy,1); 
   //DefineColor("backcolor",52.0/255,51.0/255,53.0/255);
   SetPenColor("White");
   drawRectangle(0.5, 0.5, 2, 1.2,1); 
   SetPointSize(20);
   SetPenColor("Black");
   drawLabel(1.0, 1.0, "Restart");
   
   SetPenColor("White");
   drawRectangle(8.5, 0.5, 2, 1.2,1); 
   SetPointSize(20);
   SetPenColor("Black");
   drawLabel(9.0, 1.0, "Quit");
   
   QRcode_generator();  
   SetPenColor("Red");
   SetPointSize(30);
   drawLabel(3.5, 9, "You play this game like CXK!");
   drawLabel(3.5, 8, "Just pay for it!");
   
    //drawRectangle(0, 0, cx, cy,1);    
}
