#include "name.h"
#ifndef ____ui_button_h______
#define ____ui_button_h______
#define GenUIID(N) ( ((__LINE__<<16) | ( N & 0xFFFF))^((long)&__FILE__) )

/* 显示字符串标签 */
void drawLabel(double x, double y, char *label);

/* 画一个矩形 */
void drawRectangle(double x, double y, double w, double h, int fillflag);

/* 显示带字符串标签的矩形
 * 
 * xalignment - 标签和矩形的对齐方式
 *              'L' - 靠左
 *			    'R' - 靠右
 *              其他- 居中
 *
 * fillflag - 1 填充
 *            0 不填充
 */
void drawBox(double x, double y, double w, double h, int fillflag, char *label, char xalignment, char *labelColor);


void drawTower1(double x,double y,double Scale);
void drawTower2(double x,double y,double Scale);
void drawTower3(double x,double y,double Scale);
void drawTower4(double x,double y,double Scale);
void drawmonster1(double x,double y,double hpr,double hpg,double hpb);
void drawheart(double x,double y);
void drawpath(int a[][22]);
void drawmenu();
void Repaint(MONSTER *monster,int number_M,TOWER *tower,int number_T,int HP,int  MONEY);
void TowerPlace_Generator(FILE *fp);
void Re_Brush(int a[][22]);
void drawshadow();
int Calc_Idx(double x);
int Calc_Idy(double y); 
int Available(double x,double y); 
int Choose_Tower(double x, double y);
void Out_Line(int fl);
void Draw_Tower_Scope(double x,double y, double r);
void Shoot(double sx,double sy,double tx,double ty);
double Transformx(double x);
double Transformy(double y);
#endif // define ____ui_button_h______
