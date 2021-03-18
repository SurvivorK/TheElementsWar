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
int Back_Available(double x,double y)//  back to the main console
{  drawRectangle(10,0.8,1.2, 0.8, 1);
  if(x>=10&&x<=10+1.2&&y>=0.8&&y<=0.8+0.8) return 1;
return 0;
}
void draw_about()
{ double cx = GetWindowWidth() ;
  double cy = GetWindowHeight() ; 
  double row_width=cy/21;
  double colum_width=cx/22;
  DefineColor("backcolor",52.0/255,51.0/255,53.0/255);
  SetPenColor("backcolor");
  drawRectangle(0, 0, cx, cy,1); 
  SetPointSize(35);
  DefineColor("tmp",200.0/255,200.0/255,200.0/255);
  SetPenColor("tmp");
  drawLabel(cx/2-1, cy/2+4, "About");	
  SetPointSize(10);
  drawmonster1(cx/2-3.5,cy/2+2,1,1,1);
  SetPenColor("BLACK");
  drawLabel(cx/2-3.5-0.10, cy/2+2-0.16, "?");	
  
  SetPenColor("White");
  drawLabel(cx/2-3.5+0.5, cy/2+2-0.16, "Monsters have three dimensions of HP and will change color ");
  drawLabel(cx/2-3.5+0.5, cy/2+2-1.16,"according to their health change.");
  drawTower1(cx/2-3.5,cy/2+2-2.16,1.5);
  SetPenColor("White");
  drawLabel(cx/2-3.5+0.5, cy/2+2-2.16,"Fire towers attack a monster and make it burn.");
  drawTower2(cx/2-3.5,cy/2+2-3.16,1.5);
  SetPenColor("White");
  drawLabel(cx/2-3.5+0.5, cy/2+2-3.16,"Air towers attack a single monster with a high frequency.");
  drawTower3(cx/2-3.5,cy/2+2-4.16,1.5);
  SetPenColor("White");
  drawLabel(cx/2-3.5+0.5, cy/2+2-4.16,"Water towers slow all the monsters in range down.");
  drawTower4(cx/2-3.5,cy/2+2-5.16,1.5);
  SetPenColor("White");
  drawLabel(cx/2-3.5+0.5, cy/2+2-5.16,"Earth towers attack all the monsters in range.");
  
   DefineColor("tmp",80.0/255,80.0/255,80.0/255);
   SetPenColor("tmp");
  drawRectangle(10,0.8,1.2, 0.8, 1);
  drawBox(10,0.8,1.2, 0.8, 0,"Back", 'M', "White");

  
}
