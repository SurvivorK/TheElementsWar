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
#include "shoot.h"
#define KMOD_SHIFT 0x01
#define KMOD_CTRL  0x02



/* 画一个矩形 */
void drawRectangle(double x, double y, double w, double h, int fillflag)
{
	MovePen(x, y);
	if( fillflag ) StartFilledRegion(1); 
	{
		DrawLine(0, h);
		DrawLine(w, 0);
		DrawLine(0, -h);
		DrawLine(-w, 0);
	}
	if( fillflag ) EndFilledRegion();
}

/* 画一个矩形，并在其内部居中显示一个字符串标签label */
void drawBox(double x, double y, double w, double h, int fillflag, char *label, char labelAlignment, char *labelColor)
{
	double fa = GetFontAscent();
	// rect
	drawRectangle(x,y,w,h,fillflag);
	// text

	if( label && strlen(label)>0 ) {
		SetPenColor(labelColor);
		if( labelAlignment=='L' )
			MovePen(x+fa/2, y+h/2-fa/2);
		else if( labelAlignment=='R' )
			MovePen(x+w-fa/2-TextStringWidth(label), y+h/2-fa/2);
		else // if( labelAlignment=='C'
			MovePen(x+(w-TextStringWidth(label))/2, y+h/2-fa/2);
		DrawTextString(label);
	}
}

/* 显示字符串标签 */
void drawLabel(double x, double y, char *label)
{
	if( label && strlen(label)>0 ) {
		MovePen(x,y);
		DrawTextString(label);
	}
}
/////////////////

void drawTower1(double x,double y,double Scale)
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
	double  tx=x-row_width*Siz/2;
	double  ty=y-row_width*Siz/(2*1.7171);
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, height*Siz);
    DrawLine(-base*Siz / 2, -height*Siz);
    EndFilledRegion();
    
  Siz=0.4*Scale;  
    
    DefineColor("fire2",246.0/255,178.0/255,118.0/255);
    SetPenColor("fire2");
	  tx=x-row_width*Siz/2;
	  ty=y-row_width*Siz/(2*1.7171);
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, height*Siz);
    DrawLine(-base*Siz / 2, -height*Siz);
    EndFilledRegion();
 
}

void drawTower2(double x,double y,double Scale)
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

    DefineColor("Air1",34.0/255,146.0/255,145.0/255); //  fire 462
    SetPenColor("Air1");
	double  tx=x-row_width*Siz/2;
	double  ty=y-row_width*Siz/(2*1.7171);
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, height*Siz);
    DrawLine(-base*Siz / 2, -height*Siz);
    EndFilledRegion();
    
  Siz=0.4*Scale;  
    
    DefineColor("Air2",130.0/255,200.0/255,196.0/255);
    SetPenColor("Air2");
	  tx=x-row_width*Siz/2;
	  ty=y-row_width*Siz/(2*1.7171);
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, height*Siz);
    DrawLine(-base*Siz / 2, -height*Siz);
    EndFilledRegion();
 
}

void drawTower3(double x,double y,double Scale)
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

   // DefineColor("Water1",26.0/255,107.0/255,139.0/255);// tot 272
    DefineColor("Water1",56.0/255,147.0/255,189.0/255);
    SetPenColor("Water1");
	double  tx=x-row_width*Siz/2;
	double  ty=y+row_width*Siz/(2*1.7171)+row_width*0.33*Siz;
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, -height*Siz);
    DrawLine(-base*Siz / 2, height*Siz);
    EndFilledRegion();
    
  Siz=0.4*Scale;  
    
   // DefineColor("Water2",106.0/255,169.0/255,189.0/255);
    DefineColor("Water2",156.0/255,199.0/255,219.0/255);
    SetPenColor("Water2");
	  tx=x-row_width*Siz/2;
	  ty=y+row_width*Siz/(2*1.7171)+row_width*0.68*Siz;
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, -height*Siz);
    DrawLine(-base*Siz / 2, height*Siz);
    EndFilledRegion();
 
}
void drawTower4(double x,double y,double Scale)
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

    DefineColor("Earth1",108.0/255,90.0/255,89.0/255);//tot 287
    SetPenColor("Earth1");
	double  tx=x-row_width*Siz/2;
	double  ty=y+row_width*Siz/(2*1.7171)+row_width*0.33*Siz;
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, -height*Siz);
    DrawLine(-base*Siz / 2, height*Siz);
    EndFilledRegion();
    
  Siz=0.4*Scale;  
    
    DefineColor("Earth2",170.0/255,137.0/255,135.0/255);
    SetPenColor("Earth2");
	  tx=x-row_width*Siz/2;
	  ty=y+row_width*Siz/(2*1.7171)+row_width*0.68*Siz;
	MovePen(tx, ty);
	StartFilledRegion(1); 
    DrawLine(base*Siz, 0);
    DrawLine(-base*Siz / 2, -height*Siz);
    DrawLine(-base*Siz / 2, height*Siz);
    EndFilledRegion();
 
}
void drawmonster1(double x,double y,double hpr,double hpg,double hpb)
{   double r=0.2;
    DefineColor("Tmp",hpr,hpg,hpb);
    SetPenColor("Tmp");
    MovePen(x + r, y);
    StartFilledRegion(1); 
    DrawArc(r, 0, 360);
    EndFilledRegion();
}
void drawheart(double x,double y)
{
  double Siz=0.25;
  double width=1.5,height=1.0;
  double i,j;
  int cnt=0;
   DefineColor("Heart",188.0/255,70.0/255,70.0/255);
   SetPenColor("Heart");
    SetPenSize(1); 
   for(i=-1;i<=1;i=i+0.01)
   { 
   	 for(j=-1;j<=1.5;j=j+0.01)
   	   { //double t1=j/150.0-2,t2=-(i/100.0-2.5);
		  if(pow(i,2)+pow(j-pow(i*i,1/3.0),2)<=1) 
		   { SetPenSize(2);
		     MovePen(i*Siz*width+x,j*Siz*height+y);
             DrawLine(0,0);
		   }
		}
   }
	
}

static double stage_bottom;
static double stage_bottom, stage_lb, stage_rb;

void drawpath(int a[][22])
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22;
   DefineColor("backcolor",52.0/255,51.0/255,53.0/255);
   SetPenColor("backcolor");
   drawRectangle(0, 0, cx, cy,1); 
   
   
   DefineColor("stagecolor",43.0/255,40.0/255,39.0/255);
   SetPenColor("stagecolor");
   drawRectangle(1*row_width, 4*colum_width, cx-2*row_width, cy-5*colum_width,1); 
   stage_lb = 1*row_width;
   stage_rb = 1*row_width + cx - 2*row_width;
   stage_bottom = 4*colum_width; 
   
   /*DefineColor("pathcolor",65.0/255,64.0/255,65.0/255);
   SetPenColor("pathcolor");
   for(int i=0;i<=21;i++)
   for(int j=0;j<=20;j++)
   { if(a[i][j])   drawRectangle(j*row_width,i*row_width,row_width,colum_width,1);
   }*/ 
  /* drawRectangle(1*row_width,15*colum_width,16*row_width,2*colum_width,1);
   drawRectangle(15*row_width,11*colum_width,2*row_width,4*colum_width,1);
   drawRectangle(4*row_width,11*colum_width,11*row_width,2*colum_width,1);
   drawRectangle(4*row_width,6*colum_width,2*row_width,5*colum_width,1);
   drawRectangle(6*row_width,6*colum_width,14*row_width,2*colum_width,1);
   drawRectangle(18*row_width,4*colum_width,2*row_width,2*colum_width,1);*/
   
   //drawRectangle(15*row_width,1*colum_width,16*row_width,2*colum_width,1);
   DefineColor("menucolor",70.0/255,68.0/255,70.0/255);
   SetPenColor("menucolor");
   drawRectangle(1.5*row_width,0*colum_width,11*row_width,3.5*colum_width,1);
   drawRectangle(13*row_width,0*colum_width,4*row_width,3.5*colum_width,1);
   drawRectangle(17.5*row_width,0*colum_width,3*row_width,3.5*colum_width,1);
}


void drawmenu()
{  
   SetPenSize(1);
   SetPointSize(1);
   double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22;
   
   
   drawTower1(3*row_width,1.5*row_width,1.5);
   drawTower2(5.3*row_width,1.5*row_width,1.5);
   drawTower3(7.6*row_width,1.5*row_width,1.5);
   drawTower4(9.9*row_width,1.5*row_width,1.5);
   SetPenColor("White");
   drawLabel(2.6*row_width, 0.5*row_width, "Fire");
   drawLabel(5*row_width, 0.5*row_width, "Air");
   drawLabel(7.0*row_width, 0.5*row_width, "Water");
   drawLabel(9.3*row_width, 0.5*row_width, "Earth");
   DefineColor("Grey",160.0/255,160.0/255,160.0/255);
   SetPenColor("Grey");
   drawLabel(2.3*row_width, 2.7*row_width, "CHOOSE AN ELEMNET TO FIGHT");
   drawLabel(13.4*row_width, 2.7*row_width, "HP");
   drawLabel(17.9*row_width, 2.7*row_width, "$");
   
   drawheart(14.9*row_width,1.3*row_width);
   
}

static int  a[550][2]={0};
static int cnt;
void TowerPlace_Generator(FILE *fp)// 
{ 
  fscanf(fp, "%d", &cnt);
  int i;
  for(i = 1;i <= cnt; i++) fscanf(fp, "%d%d", &a[i][0], &a[i][1]);
  
}
void drawshadow()
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22;
   DefineColor("AGrey",50.0/255,50.0/255,50.0/255);
   SetPenColor("AGrey");
   int i;
   for(i=1;i<=cnt;i++)   
    {  int x=a[i][0],y=a[i][1];
       drawRectangle(x*row_width+0.1,y*colum_width+0.1,0.5*row_width,0.5*colum_width,1);
    	
	}
	
}
void Repaint(MONSTER *monster,int number_M,TOWER *tower,int number_T,int HP,int  MONEY)
{  	//InitConsole();
	//printf("%d %d\n",HP,MONEY);
   	double cx, cy;
   	cx = GetWindowWidth() ;
   	cy = GetWindowHeight() ; 
   	double row_width=cy/21;
   	double colum_width=cx/22;
   	char hp[10]; hp[0]=HP+'0'; hp[1]=0;
   	int wei0=MONEY/100,wei1=(MONEY%100)/10,wei2=MONEY%10; 
   	char money[10]; money[0]=wei0+'0';money[1]=wei1+'0';money[2]=wei2+'0';money[3]=0;
   	DefineColor("Heart",188.0/255,70.0/255,70.0/255);
   	SetPenColor("Heart");
   	drawRectangle(14.5*row_width,1.2*colum_width,0.8*row_width,0.7*colum_width,1);
   	DefineColor("menucolor",70.0/255,68.0/255,70.0/255);
   	SetPenColor("menucolor");
   	drawRectangle(18.15*row_width,1.2*colum_width,0.8*row_width+0.8,0.7*colum_width+0.8,1);
   	SetPenColor("White"); 
   	drawLabel(14.75*row_width,1.3*row_width,hp);
   	drawLabel(18.3*row_width,1.3*row_width,money);     
   	int i;PMONS p;
	for (p = monster; p->nxt; p = p->nxt){
		PMONS pm = p->nxt;
		double x = pm->x, y = pm->y;
		drawmonster1(colum_width*x,row_width*y,pm->hpr,pm->hpg,pm->hpb); 
	 	if (pm->burnt_cnt) Draw_firing(colum_width*x, row_width*y);
	 	if (pm->slowdown_cnt) Draw_frozing(colum_width*x, row_width*y);
	}
   for(i=1;i<=number_T;i++)
     { int ty=tower[i].type; 
       double nowx=tower[i].x,nowy=tower[i].y;
	   if(ty==1)   drawTower1(row_width*nowx,row_width*nowy,1.0); 
	   if(ty==2)   drawTower2(row_width*nowx,row_width*nowy,1.0);
	   if(ty==3)   drawTower3(row_width*nowx,row_width*nowy,1.0);
	   if(ty==4)   drawTower4(row_width*nowx,row_width*nowy,1.0);
	 } 
   	 	 	
}
int Calc_Idx(double x) 
{ double cx, cy;
  cx = GetWindowWidth() ;
  cy = GetWindowHeight() ; 
  double row_width=cy/21;
  double colum_width=cx/22; 
 return (int)(x/row_width) ;
}
int Calc_Idy(double y) 
{ double cx, cy;
  cx = GetWindowWidth() ;
  cy = GetWindowHeight() ; 
  double row_width=cy/21;
  double colum_width=cx/22; 
 return (int)(y/row_width);
}
int Available(double x,double y)
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22; 
   int tx=(int)(x/row_width) ,ty=(int) (y/row_width);
   int i;
   for(i = 1;i<=cnt;i++) if(a[i][0]==tx&&a[i][1]==ty) return 1;
   return 0;
}
int Choose_Tower(double x,double y)
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22; 
   if(x>=2.5*row_width&&x<=3.5*row_width&&y>=1*row_width&&y<=1.8*row_width)  return 1;
   if(x>=4.9*row_width&&x<=5.9*row_width&&y>=1*row_width&&y<=1.8*row_width)  return 2;
   if(x>=7.0*row_width&&x<=8.0*row_width&&y>=1*row_width&&y<=1.8*row_width)  return 3;
   if(x>=9.5*row_width&&x<=10.5*row_width&&y>=1*row_width&&y<=1.8*row_width)  return 4;
	return 0;
}
void Out_Line(int fl)
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22; 
   if(fl==1)
     {  drawRectangle(2.0*row_width,0.1*colum_width,2.0*row_width,2.2*colum_width,0);
	    return;
	 }
  if(fl==2)  
     {  drawRectangle(4.3*row_width,0.1*colum_width,2.0*row_width,2.2*colum_width,0);
	  return;
	 }	 
  if(fl==3)
     {  drawRectangle(6.5*row_width,0.1*colum_width,2.0*row_width,2.2*colum_width,0);
      return;
	 }
  if(fl==4)
     {  drawRectangle(9.0*row_width,0.1*colum_width,2.0*row_width,2.2*colum_width,0);
      return;	
	 }
}
void Re_Brush(int a[][22])
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22;
   SetPenColor("pathcolor");
   SetPenSize(1);
   int i, j;
   for(i=0;i<=21;i++)
   for(j=0;j<=20;j++)
   { if(a[i][j])   drawRectangle(j*row_width,i*row_width,row_width,colum_width,1);
   }
}

const double pi = acos(-1);
void Draw_Tower_Scope(double x,double y, double r)
{  double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22;
   SetPenColor("Green");
   r = r * row_width;
   double xx = (x + 0.5)* colum_width;
   double yy = (y + 0.5) * row_width;
   
   double banl[3], banr[3];
   int cur = 0;
   
   if (yy - stage_bottom < r) {
   	  double dy = yy - stage_bottom;
      double t = acos(dy / r);
      banl[cur] = -pi / 2 - t;
      banr[cur] = -pi / 2 + t;
  	  ++cur;
   }
   
   int flag = 0;
   if (stage_rb - xx < r){
   	  double dx = stage_rb - xx;
   	  double t = acos(dx / r);
   	  banl[cur] = -t;
   	  banr[cur] =  t;
   	  ++cur;
   	  flag = 1;
   }
   
   if (xx - stage_lb < r){
      double dx = xx - stage_lb;
      double t = acos(dx / r);
      banl[cur] = pi - t;
      banr[cur] = pi + t;
      ++cur;
      flag = 2;
   }
   int i;
   for (i = 0; i < cur; ++i){
      if (banl[i] < 0) banl[i] += 2*pi;
      if (banr[i] < 0) banr[i] += 2*pi;
   }
   
   if (cur == 1) {
   	  double angl = banl[0] / pi * 180;
   	  double angr = banr[0] / pi * 180;
   	  double dr = angl - angr;
   	  while (dr < 0) dr += 360;
   	  MovePen(xx + r * cos(banr[0]), yy + r * sin(banr[0]));
   	  DrawArc(r, angr, dr);
   } else { // cur == 2, cannot be 3
   	  if (flag == 1){
   	  	 if (banr[0] < banl[1]){
   	  		MovePen(xx + r * cos(banr[0]), yy + r * sin(banr[0]));
   	  		double tl = banr[0] / pi * 180;
   	  		double tr = banl[1] / pi * 180;
   	  		DrawArc(r, tl, tr - tl);
		}
		MovePen(xx + r * cos(banr[1]), yy + r * sin(banr[1]));
		double tl = banr[1] / pi * 180;
		double tr = banl[0] / pi * 180;
		DrawArc(r, tl, tr - tl);
	  }else{ // flag == 2
	  	 if (banr[1] < banl[0]){
	  	 	MovePen(xx + r * cos(banr[1]), yy + r * sin(banr[1]));
	  	 	double tl = banr[1] / pi * 180;
		  	double tr = banl[0] / pi * 180;
	   	  	double dr = tr - tl;
	   	  	while (dr < 0) dr += 360;
	  	 	DrawArc(r, tl, dr);
		 }
		 MovePen(xx + r * cos(banr[0]), yy + r * sin(banr[0]));
   	  	double tl = banr[0] / pi * 180;
   	  	double tr = banl[1] / pi * 180;
   	  	double dr = tr - tl;
   	  	while (dr < 0) dr += 360;
   	  	DrawArc(r, tl, dr);
   	  }
   }
}

double Transformx(double x){
	 double cx, cy;
   cx = GetWindowWidth() ;
   cy = GetWindowHeight() ; 
   double row_width=cy/21;
   double colum_width=cx/22;
   return (x) * colum_width; 
}
double Transformy(double y){
	 double cx, cy;
     cy = GetWindowHeight() ; 
   double row_width=cy/21;
   return (y) * row_width; 
}  
