#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <math.h>

#include "graphics.h"
#include "genlib.h"
#include "conio.h"
#include "imgui.h"
#include "name.h"
#include "extgraph.h"
#include "shoot.h"
#include "fail.h"
#include "pause.h" 
#include "ABout.h"
#include "BEGIN.h"
#include "Victory.h"
#include "Battle.h"

#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define maxn 1005
#define equal(a, b) (fabs((a) - (b)) < (eps))


Monster_Wave wave[10];
static int now_wave;
static const int wave_cnt = 5;

/* Below is the properties of different types of towers */
static double Atkr[] = {0, 0.005, 0.03, 0.00, 0.015};
static double Atkg[] = {0, 0.005, 0.03, 0.00, 0.015};
static double Atkb[] = {0, 0.005, 0.03, 0.00, 0.015};
static int Period[] = {1, 3, 1, 3, 3}; // to be editied
static double atk_range[] = {0, 3, 3, 3, 3};

static int TIMERID = 0;
static int dx[] = {1, 0, 0, -1}; // right down up left
static int dy[] = {0, -1, 1, 0};
static const int P = 100;                // fresh time
static const int monster_limit = 80; // Maximum number of monsters
static const double eps = 1e-7;
static bool is_Pause = 0;
static bool flagx = 0;
static double sequencer[maxn], sequenceg[maxn], sequenceb[maxn];
static double scopex = -1, scopey = -1;
bool Tower_Exist[30][30];
static int cost[] = {10, 10, 10, 10, 10};
static int Chosen_type = 0;
static unsigned int Round = 0;
static int Status;
static int Click_cnt = 0; 

int Map[21][22];
int monster_cnt, tower_cnt, path_cnt;
int HP, MONEY;
static int Gameid;
static bool if_load;
MONSTER monster_track[maxn];
PMONS monster_head, monster_tail;
TOWER tower[maxn];
PATH path[maxn];

void Refresh();
bool Load_Information(int mapid);
void Record_Information(int mapid);
void Load_Map(int mapid);
void Load_Path();
void init(int Gameid, bool if_load);
void Tower_Attack();
void Monster_Generator();
void Tower_Generator(double x, double y, int type);
bool At_EndPoint(MONSTER t);
bool At_Crossroad(MONSTER t);
void Monster_Move();
void LosingHPCheck();
void MouseEventProcess(int x, int y, int button, int event);

void Process(int Gameid, bool if_load);

Monster_Wave init_Monster_Wave(int _cnt, double _v, int _hp, int b_hp, int _appear, int b_time);

Monster_Wave init_Monster_Wave(int _cnt, double _v, int _hp, int b_hp, int _appear, int b_time){
	Monster_Wave t;
	t.cnt = _cnt;
	t.v = _v; 
	t.hp_limit = _hp;
	t.hp_base = b_hp;
	t.blank_time = b_time;
	t.appear_itvl = _appear;
	return t;
}
void Main(){
	int i; 
	InitGraphics();
	SetWindowTitle("The War of Elements");

	draw_begin(); Status = 1;
	registerMouseEvent(MouseEventProcess);
}
void Refresh(){
	double cx, cy;
	cx = GetWindowWidth() ;
	cy = GetWindowHeight() ; 
	double row_width=cy/21;
	double colum_width=cx/22;
	DefineColor("stagecolor",43.0/255,40.0/255,39.0/255);
    SetPenColor("stagecolor");
	drawRectangle(colum_width, 4 * row_width, cx - 2 * colum_width, cy - 5 * row_width, 1);
	Re_Brush(Map);
	drawshadow();
}
bool Load_Information(int mapid){
	FILE *fp;
	switch(mapid){
		case 1: fp = fopen(".\\record\\1","r"); break;
		case 2: fp = fopen(".\\record\\2","r"); break;
		case 3: fp = fopen(".\\record\\3","r"); break;
		case 4: fp = fopen(".\\record\\4","r"); break;
	}
	if (fp == NULL) return 0;
	fscanf(fp, "%d%d%d%d%d", &HP, &MONEY, &Round, &now_wave, &monster_cnt);
	while (1){
		double _x, _y, _v, _hpr, _hpg, _hpb;
		int  _s_cnt, _b_cnt, _road, _swerve_cnt, _is_a;
		fscanf(fp, "%lf%lf%lf%lf%lf%lf%d%d%d%d%d", &_x, &_y, &_v, &_hpr, &_hpg, &_hpb, &_s_cnt, &_b_cnt, &_road, &_swerve_cnt, &_is_a);
		if (equal(_x, 0) && equal(_y, 0) && equal(_v, 0)) break;
		monster_tail->nxt = (PMONS)malloc(sizeof(MONSTER));
  		PMONS pm = monster_tail->nxt;
  		pm->road = _road;
  		pm->x = _x;
  		pm->y = _y;
  		pm->v = _v;
  		pm->hpr = _hpr;
  		pm->hpg = _hpg;
  		pm->hpb = _hpb;
  		pm->is_alive = _is_a;
  		pm->slowdown_cnt = _s_cnt;
  		pm->burnt_cnt = _b_cnt;
  		pm->swerve_cnt = _swerve_cnt;
  		pm->nxt = NULL;
  		monster_tail = pm;
	}
	fscanf(fp, "%d", &tower_cnt);
	int i;
	for (i = 1; i <= tower_cnt; i++){
		fscanf(fp, "%d%d%lf%lf", &tower[i].type, &tower[i].cool_down, &tower[i].x, &tower[i].y);
	}
	fclose(fp);
	return 1;
}
void Record_Information(int mapid){
	FILE *fp;
	switch(mapid){
		case 1: fp = fopen(".\\record\\1","w"); break;
		case 2: fp = fopen(".\\record\\2","w"); break;
		case 3: fp = fopen(".\\record\\3","w"); break;
		case 4: fp = fopen(".\\record\\4","w"); break;
	}
	fprintf(fp, "%d %d %d %d %d\n", HP, MONEY, Round, now_wave, monster_cnt);
	PMONS p;
	for (p = monster_head; p->nxt; p = p->nxt){
  		PMONS pm = p->nxt;
  		fprintf(fp, "%lf %lf %lf %lf %lf %lf %d %d %d %d %d\n", pm->x, pm->y, pm->v, pm->hpr, pm->hpg, pm->hpb, pm->slowdown_cnt, pm->burnt_cnt, pm->road, pm->swerve_cnt, pm->is_alive);
	}
	fprintf(fp, "0 0 0 0 0 0 0 0 0 0 0\n");
	fprintf(fp, "%d\n", tower_cnt);
	int i;
	for (i = 1; i <= tower_cnt; i++){
		fprintf(fp, "%d %d %lf %lf\n", tower[i].type, tower[i].cool_down, tower[i].x, tower[i].y);
		Tower_Exist[(int)tower[i].x][(int)tower[i].y] = 1;
	}
	fclose(fp);
}
void Load_Path(){
	int i;
	for (i = 1; i <= path_cnt; i++) {
		int dir = path[i].Direction[0];
		monster_track[i].x = path[i].STx - 0.5 * dx[dir];
		monster_track[i].y = path[i].STy - 0.5 * dy[dir];
		monster_track[i].road = i;
		monster_track[i].swerve_cnt = 0;
		monster_track[i].is_alive = 1;
		monster_track[i].v = 0.5;
	}
	
   	TIMERID = 2;

}
void Load_Map(int mapid){
	FILE *fp;
	switch(mapid){
		case 1: fp = fopen(".\\map\\1","r"); break;
		case 2: fp = fopen(".\\map\\2","r"); break;
		case 3: fp = fopen(".\\map\\3","r"); break;
		case 4: fp = fopen(".\\map\\4","r"); break;
	}
	fscanf(fp, "%d", &path_cnt); 
	static int i, j;
	memset(path, 0, sizeof(path));
	for (i = 1; i <= path_cnt; i++){
		fscanf(fp, "%lf%lf%lf%lf", &path[i].STx, &path[i].STy, &path[i].Endx, &path[i].Endy);
		fscanf(fp, "%d", &path[i].Crossroad_cnt);
		for (j = 0; j < path[i].Crossroad_cnt; j++) fscanf(fp, "%lf", &path[i].Crossroadx[j]);
		for (j = 0; j < path[i].Crossroad_cnt; j++) fscanf(fp, "%lf", &path[i].Crossroady[j]);
		for (j = 0; j <= path[i].Crossroad_cnt; j++) fscanf(fp, "%d", &path[i].Direction[j]);
	}
	for (i = 2; i <= path_cnt; i++) if (path[i].Endx != path[i - 1].Endx) flagx = 0;
	else flagx = 1;
	for (i = 0; i < 21; i++)
		for (j = 0; j < 22; j++) fscanf(fp, "%d", &Map[i][j]);
	TowerPlace_Generator(fp);
	fclose(fp);
	drawpath(Map);
	drawmenu();
	Load_Path(); 
}
void init(int Gameid, bool if_load){

  Load_Map(Gameid);
  
  wave[1] = init_Monster_Wave(10, 0.06, trunc(255 * 0.3), 0, 15, 5000);
  wave[2] = init_Monster_Wave(27, 0.1, trunc(255 * 0.3), trunc(255 * 0.2), 15, 5000);
  wave[3] = init_Monster_Wave(45, 0.15,trunc(255 * 0.3), trunc(255 * 0.4), 10, 5000);
  wave[4] = init_Monster_Wave(65, 0.2, trunc(255 * 0.2), trunc(255 * 0.6), 10, 5000);
  wave[5] = init_Monster_Wave(80, 0.25,trunc(255 * 0.2), trunc(255 * 0.8), 15, 5000);
  
  monster_head = (PMONS)malloc(sizeof(MONSTER));
  monster_head->nxt = NULL;
  monster_tail = monster_head;
  bool flag = 1;
  is_Pause = 0;
  Click_cnt = 0;
  if (if_load){
  	flag = Load_Information(Gameid); 
  }
  if (!flag || !if_load){
  		now_wave = 1;
		memset(Tower_Exist, 0, sizeof(Tower_Exist));
		monster_cnt = 0;
		tower_cnt = 0;
  		HP = 9;
  		MONEY = 20;
	} 
}
const double slowdown_coef = 0.5;
double velo(MONSTER m) {
	return m.slowdown_cnt ? m.v * slowdown_coef : m.v;
}

static int Blank;
void Monster_Generator(){
  srand(time(0));
  int temp = rand()%path_cnt + 1;
  if (monster_cnt == wave[now_wave].cnt){
  	Blank = Blank + P;
  
  	if (Blank <= wave[now_wave].blank_time) return;
  	Blank = 0;
	now_wave++;
  }

  if (Round % wave[now_wave].appear_itvl != 1) return;
  ++monster_cnt;
  
  monster_tail->nxt = (PMONS)malloc(sizeof(MONSTER));
  PMONS pm = monster_tail->nxt;
  pm->road = temp;
  pm->x = path[temp].STx;
  pm->y = path[temp].STy;
  pm->v = wave[now_wave].v;
  pm->hpr = (wave[now_wave].hp_base + (double)(rand()%wave[now_wave].hp_limit)) / 255.0;
  pm->hpg = (wave[now_wave].hp_base + (double)(rand()%wave[now_wave].hp_limit)) / 255.0;
  pm->hpb = (wave[now_wave].hp_base + (double)(rand()%wave[now_wave].hp_limit)) / 255.0;
  pm->is_alive = 1;
  pm->slowdown_cnt = 0;
  pm->burnt_cnt = 0;
  pm->swerve_cnt = 0;
  pm->nxt = NULL;
  monster_tail = pm;
  
}
void Tower_Generator(double x, double y, int type){
  Tower_Exist[(int)x][(int)y] = 1;
  tower_cnt ++;
  tower[tower_cnt].x = x;
  tower[tower_cnt].y = y;
  tower[tower_cnt].type = type;
  tower[tower_cnt].cool_down = 0;
}
bool At_EndPoint(MONSTER t){
  if (flagx) {if (equal(t.y, path[t.road].Endy) && t.x >= path[t.road].Endx) return 1;}
  else if (equal(t.x, path[t.road].Endx) && t.y <= path[t.road].Endy) return 1;
  return 0;
}
int Pass_Crossroad(MONSTER t){
	
  int temp = t.road, n = t.swerve_cnt;
  if (equal(t.x, path[temp].Crossroadx[n]) && equal(t.y, path[temp].Crossroady[n])) return 1;
  
  int dir = path[temp].Direction[n];
  double newx = velo(t) * dx[dir] + t.x, newy = velo(t) * dy[dir] + t.y;
  if ((equal(t.x, path[temp].Crossroadx[n]) && equal(t.x, newx) && path[temp].Crossroady[n] >= min(t.y, newy) && path[temp].Crossroady[n] <= max(t.y,newy)) ||
     (equal(t.y, path[temp].Crossroady[n]) && equal(t.y, newy) && path[temp].Crossroadx[n] >= min(t.x, newx) && path[temp].Crossroadx[n] <= max(t.x,newx))){
     	return 2;
	 }
  
  return 0;
}
void Monster_Move(){
	PMONS p;
	for (p = monster_head; p->nxt; p = p->nxt){
		PMONS pm = p->nxt;
		int t = Pass_Crossroad(*pm), temp = pm->road, n = pm->swerve_cnt;
		if (t == 1){
			pm->swerve_cnt++;
			int dir = path[pm->road].Direction[pm->swerve_cnt];
			pm->x += velo(*pm) * dx[dir];
			pm->y += velo(*pm) * dy[dir];
		}else if(t==2){
			double d = path[temp].Crossroadx[n] - pm->x + path[temp].Crossroady[n] - pm->y;
			pm->swerve_cnt++;
			int dir = path[temp].Direction[pm->swerve_cnt];
			pm->x = path[temp].Crossroadx[n];
			pm->y = path[temp].Crossroady[n];
			if (dx[dir]) pm->x += velo(*pm) * dx[dir] - d;
			if (dy[dir]) pm->y += velo(*pm) * dy[dir] - d;
		}else{
			int dir = path[pm->road].Direction[pm->swerve_cnt];
			pm->x += velo(*pm) * dx[dir];
			pm->y += velo(*pm) * dy[dir];
		}
	}
}
bool At_Crossroad(MONSTER t){
  int temp = t.road, n = t.swerve_cnt;
  if (equal(t.x, path[temp].Crossroadx[n]) && equal(t.y, path[temp].Crossroady[n])) return 1;
  return 0;
}
void Track_Move(){
	int i;
  	for (i = 1; i <= path_cnt; i++) if(monster_track[i].is_alive){
		if (At_Crossroad(monster_track[i])) monster_track[i].swerve_cnt++;
    	int dir = path[i].Direction[monster_track[i].swerve_cnt];
    	monster_track[i].x += monster_track[i].v * dx[dir];
    	monster_track[i].y += monster_track[i].v * dy[dir];
  	}
}

void one_to_one_atk(TOWER *pt, MONSTER *pm) {
	pm->hpr = max(pm->hpr - Atkr[pt->type], 0);
	pm->hpg = max(pm->hpg - Atkg[pt->type], 0);
	pm->hpb = max(pm->hpb - Atkb[pt->type], 0);
	if (pm->hpr + pm->hpg + pm->hpb == 0)
		pm->is_alive = 0;
}

void LosingHPCheck(){
	PMONS p;
	for (p = monster_head; p->nxt; p = p->nxt){
  		PMONS pm = p->nxt;
  		if (pm->is_alive && At_EndPoint(*pm)) {
  	  		HP--;
  	  		pm->is_alive = 0;
  	  		p->nxt = pm->nxt;
  	  		if (p->nxt == NULL){
  	      		monster_tail = p;
  	      		break;
  	  		}
  	  		free(pm);
		}
  }
}

double sqr(double x) {
	return x * x;
}

const int W1 = 1, W2 = 3;

double dist_tm(TOWER t, MONSTER m) {
	return sqrt(sqr(t.x - m.x) + sqr(t.y - m.y));
}

double calc_weight(TOWER t, MONSTER m) {
	double dist = dist_tm(t, m);
	if (dist > atk_range[t.type]) return -10; // out of range
	int dir = path[m.road].Direction[m.swerve_cnt];
	// (m.x + t * m.v * dx[dir] - t.x) ^ 2 + (m.y + t * m.v * dy[dir] - t.y) ^ 2 = atk_range[m.type] ^ 2;
	double l = 0, r = 10;
	int i;
	for (i = 1; i <= 30; ++i) {
		double mid = (l + r) / 2;
		if (sqr(m.x + mid * velo(m) * dx[dir] - t.x) + sqr(m.y + mid * velo(m) * dy[dir] - t.y) < sqr(atk_range[t.type]))
			l = mid;
		else r = mid;
	} // use b-search to solve the quadratic equation
	double shoot_cnt = ceil(m.hpr / Atkr[t.type]) + ceil(m.hpg / Atkg[t.type]) + ceil(m.hpb / Atkb[t.type]);
	return W1 / l + W2 * shoot_cnt;
}

const int BURN_PERIOD = 10;

void tower1_attack(TOWER *pt) { // Fire tower
	
	if (pt->cool_down){
		pt->cool_down += 1;
		pt->cool_down %= Period[pt->type];
		return;
	}
	PMONS chosen_p = NULL;
	double chosen_w = 0;
	PMONS p;
	for (p = monster_head; p->nxt; p = p->nxt){
		PMONS pm = p->nxt;
		
		if (pm->burnt_cnt > 0) continue;
		double cw = calc_weight(*pt, *pm);
		if (cw > chosen_w) {
			chosen_p = p;
			chosen_w = cw;
		}
	}
	
	// first try to find an unburnt monster
	
	if (chosen_p == NULL) {	// if cannot found, chose a burnt monster with maximal weight
		for (p = monster_head; p->nxt; p = p->nxt){
			double cw = calc_weight(*pt, *(p->nxt));
			if (cw > chosen_w){
				chosen_p = p;
				chosen_w = cw;
			}
		}
	}
	
	if (chosen_p != NULL) { // if found an ememy to attack
		PMONS pm = chosen_p->nxt;
		Fire_Shoot(Transformx(pt->x), Transformy(pt->y), Transformx(pm->x), Transformy(pm->y));
		pm->burnt_cnt = BURN_PERIOD;
		pt->cool_down += 1;
		pt->cool_down %= Period[pt->type];
	}
}

void tower2_attack(TOWER *pt) { // Air tower
	if (pt->cool_down){
		pt->cool_down += 1;
		pt->cool_down %= Period[pt->type];
		return;
	}
	
	PMONS chosen_p = NULL, p;
	double chosen_w = 0;
	for (p = monster_head; p->nxt; p = p->nxt){
		PMONS pm = p -> nxt;

		double cw = calc_weight(*pt, *(p->nxt));
		if (cw > chosen_w){
			chosen_p = p;
			chosen_w = cw;
		}
	}	
	
	if (chosen_p != NULL) {
		PMONS pm = chosen_p->nxt;
		one_to_one_atk(pt, pm);
		if (pm->is_alive == 0){
			chosen_p->nxt = pm->nxt;
			if (chosen_p->nxt == NULL)
			    monster_tail = chosen_p;
			free(pm);
			MONEY ++;
		}
		pt->cool_down += 1;
		pt->cool_down %= Period[pt->type];
	}
}

void tower4_attack(TOWER *pt) { // earth
	if (pt->cool_down){
		pt->cool_down += 1;
		pt->cool_down %= Period[pt->type];
		return;
	}
	
	int flag = 0;
	PMONS p;
	for (p = monster_head; p->nxt; p = p->nxt){
		PMONS pm = p->nxt;

		if (dist_tm(*pt, *pm) > atk_range[pt->type])
			continue;
		one_to_one_atk(pt, pm);
		if (pm->is_alive == 0){
			p->nxt = pm->nxt;
			if (p->nxt == NULL){ 
			    monster_tail = p;
			    break;
			}
			free(pm);
			MONEY ++;
		}
		flag = 1;
	}
	
	if (flag) {
		pt->cool_down += 1;
		pt->cool_down %= Period[pt->type];
	}
}

const int SLOWDOWN_PERIOD = 7;

void tower3_attack(TOWER *pt) { // Ice tower

	if (pt->cool_down){
		pt->cool_down += 1;
		pt->cool_down %= Period[pt->type];
		return;
	}
	
	int flag = 0;
	PMONS p;
	for (p = monster_head; p->nxt; p = p->nxt){
		PMONS pm = p->nxt;
		if (dist_tm(*pt, *pm) > atk_range[pt->type])
			continue;
		one_to_one_atk(pt, pm);
		pm->slowdown_cnt = SLOWDOWN_PERIOD;
		flag = 1;
	}
	
	if (flag) {
		pt->cool_down += 1;
		pt->cool_down %= Period[pt->type];
	}
}

void Tower_Attack() {
	int i;
	for (i = 1; i <= tower_cnt; ++i){
		switch (tower[i].type) {
			case 1:
				tower1_attack(&tower[i]);
				break;
			case 2:
				tower2_attack(&tower[i]);
				break;
			case 3:
				tower3_attack(&tower[i]);
				break;
			case 4:
				tower4_attack(&tower[i]);
				break;
		}
	}
}

void Monster_Burn(){
	PMONS p;
	for(p = monster_head; p->nxt; p = p->nxt) {
		PMONS pm = p->nxt;
		if(pm->burnt_cnt > 0) {
			--(pm->burnt_cnt);
			pm->hpr = max(pm->hpr - Atkr[1], 0);
			pm->hpg = max(pm->hpg - Atkg[1], 0);
			pm->hpb = max(pm->hpb - Atkb[1], 0);
			if (equal(pm->hpr + pm->hpg + pm->hpb, 0)){
				pm->is_alive = 0;
			}
		}
		if (pm->slowdown_cnt > 0) --(pm->slowdown_cnt);
		if (pm->is_alive == 0){
			p->nxt = pm->nxt;
			if (p->nxt == NULL){
			    monster_tail = p;
			    break;
			} 
			free(pm);
			MONEY++;
		}
	}
}

void TimerEventProcess(int timerID){
	if (TIMERID == 1){
		if (Status == 4){
			Round = Round + 1; 
			
	  		Re_Brush(Map);
			if (scopex != -1){
				Draw_Tower_Scope(scopex, scopey, atk_range[Chosen_type]);
			} 
	  		Repaint(monster_head, monster_cnt, tower, tower_cnt, HP, MONEY);
	  		Monster_Burn();
	  		Tower_Attack();
	  		Monster_Move();
	  		LosingHPCheck();
			if (monster_cnt < monster_limit) Monster_Generator(); 
	  		if (HP <= 0){
	    		cancelTimer(1);
	    		fail_surface();
	    		Status = 7;
			}
			else if (monster_cnt == monster_limit && monster_head ->nxt == NULL){
				cancelTimer(1);
				switch(Gameid){
					case 1: remove(".//record//1"); break;
					case 2: remove(".//record//2"); break;
					case 3: remove(".//record//3"); break;
					case 4: remove(".//record//4"); break;
				}
				draw_victory();
				Status = 6;
  			}
  		}
  	}
  	if (TIMERID == 2){
  		double cx, cy;
		cx = GetWindowWidth() ;
   		cy = GetWindowHeight() ; 
   		double row_width=cy/21;
   		double colum_width=cx/22;
		Track_Move();
		bool flag = 0;
		int i;
		for (i = 1; i <= path_cnt; i++) if (monster_track[i].is_alive){
			flag = 1;
			DefineColor("pathcolor",65.0/255,64.0/255,65.0/255);
   			SetPenColor("pathcolor");
			drawRectangle(trunc(monster_track[i].x)*row_width,trunc(monster_track[i].y)*row_width,row_width,colum_width,1);
			if (At_EndPoint(monster_track[i])) monster_track[i].is_alive = 0;
		}
		if (!flag) {
			TIMERID = 1;
  			drawshadow();
  			double cx = GetWindowWidth();
  			double cy = GetWindowHeight();
  			SetPenColor("White");
		}
	}
}
int lastpx = 0, lastpy = 0;

void MouseEventProcess(int x, int y, int button, int event){        
 	double mx, my;
  	mx = ScaleXInches(x);
  	my = ScaleYInches(y);
  	if (Status == 0){ // Exit
		ExitGraphics();
  	}
  	else if (Status == 1){ // Home Page
  		switch(event){
  			case BUTTON_DOWN:
   			if (button == LEFT_BUTTON){
   				int t = Begin_Available(mx, my);
   				switch(t){
   					case 0: break;
   					case 1: Status = 3; draw_Battle(); break;
   					case 2: Status = 2; draw_about(); break;
   					case 3: Status = 0; break;
   				}
  			}
  			break;
  		}
  	}
  	else if (Status == 2){  // About Page
  		switch(event){
  		case BUTTON_DOWN:
   			if (button == LEFT_BUTTON){
   				if (Back_Available(mx, my)) {Status = 1; draw_begin(); break;} 
  			}
  		break;
  		}
  	}
  	else if (Status == 3){ // Battle Page
  		switch(event){
  		case BUTTON_DOWN:
   			if (button == LEFT_BUTTON){
   				if (Battle_Back_Available(mx, my)){
   					Status = 1;
   					draw_begin();
   					break;
   				}
   				Gameid = choose_circle(mx, my);
				if_load = 1 - choose_new_load(mx, my, Gameid);
				
				if (Gameid) {
					Status = 4;
					Process(Gameid, if_load);
   					
   				}
  			}
  			break;
  		}
  	}
  	else if (Status == 4){ // -- Game  	
 		int px = Calc_Idx(mx), py = Calc_Idy(my);
		switch (event){
    	case BUTTON_DOWN:                                          
     	if(button==LEFT_BUTTON){   
      		int t = Choose_Tower(mx, my);
	  		if (t){
	  			Click_cnt = 0;
	  			SetPenColor("menucolor");
      			Out_Line(Chosen_type);
      			if (scopex != -1){
      				Refresh();
				}
				//scopex = px, scopey = py;
		  		Chosen_type = t;
   	   			if (cost[Chosen_type] > MONEY) Chosen_type = 0;
      			if (Chosen_type){
      				SetPenColor("Red");
      				Out_Line(Chosen_type);
		  		}
	  		}
	  		else{	
				if (Click_cnt != 0 && (px == lastpx && py == lastpy)) {
          				scopex = -1, scopey = -1;
						Tower_Generator((double)px + 0.5, (double) py + 0.5, Chosen_type);
         				MONEY -= cost[Chosen_type];
	  					SetPenColor("menucolor");
      					Out_Line(Chosen_type);
      					Refresh();
      					Chosen_type = 0;
        				Click_cnt = 0;
				}
				else{
					if (!Tower_Exist[px][py] && Available(mx, my) && Chosen_type){
						if (scopex != -1){
							Refresh();
						}
						Click_cnt = 1;
						lastpx = px; lastpy = py;
						scopex = px, scopey = py;
						Draw_Tower_Scope(px, py, atk_range[Chosen_type]);
					}
				}
	  		
		  	}
	 	}
	  	else if(button == RIGHT_BUTTON){
	  		SetPenColor("menucolor");
      		Out_Line(Chosen_type);
      		Chosen_type = 0;
      		if (scopex != -1 && scopey != -1) Refresh();
      		scopex = -1, scopey = -1;
	  		
	  	}
      	break;
		}
	}
  	else if (Status == 5){ //pause
  		switch(event){
  		case BUTTON_DOWN:
   			if (button == LEFT_BUTTON){
   				int t = Pause_available(mx, my);
   				switch(t){
   					case 1: cancelTimer(1);  draw_Battle(); Status = 3; break;
   					case 2: Refresh(); is_Pause = 0; Status = 4; break;
   					case 3: Record_Information(Gameid); draw_save_successfully(); break;
   				}
  			}
  		break;
  		}
  	}
  	else if (Status == 6){ // Victory
  		switch(event){
		case BUTTON_DOWN:
   			if (button == LEFT_BUTTON){
   				int t = victory_continue_available(mx, my);
   				if (t){
   					cancelTimer(1); 
   					Status = 3; 
   					draw_Battle(); 
   					break;
   				}
  			}
  		break;
		} 
  	}
  	else if (Status == 7){ // Failure
  		switch(event){ 
	  		case BUTTON_DOWN:
   				if (button == LEFT_BUTTON){
   					int t = fail_available(mx, my);
   					switch(t){
   						case 0: cancelTimer(1); Status = 3; draw_Battle(); break;
   						case 1: Status = 4; Process(Gameid, 0); break;
   					}
  				}
  			break;
		}
	}
}
void KeyboardEventProcess(int key,int event){
	static bool control_pressed = 0;
	if (Status == 5){
		switch (event) {
		case KEY_DOWN:
			switch (key) {
			    case VK_SPACE:
			    	control_pressed = 0;
			        if (TIMERID == 1){
					 	is_Pause = !is_Pause; 
			         	if (is_Pause){
			         		Status = 5;
			         		draw_pause();
					 	}
					 	else{
					 		Status = 4;
					 		Refresh();
					 	}
					 	break;
					 }
			    case VK_ESCAPE:
			    	control_pressed = 0;
			        if (TIMERID == 1) {
						Status = 4;
						is_Pause = 0;
						Refresh();
					}
                    break;
                case VK_CONTROL:{
                	control_pressed = 1;
					break;
				}
				case 'S':{
					if (control_pressed) {
						Record_Information(Gameid); 
						draw_save_successfully(); 
						control_pressed = 0;
					}
					break;
				}
			}
			break;
		}
	}
    if (Status == 4){
    	switch (event) {
		case KEY_DOWN:
			switch (key) {
			    case VK_SPACE:
			        if (TIMERID == 1){
					 	is_Pause = !is_Pause; 
			         	if (is_Pause){
			         		Status = 5;
			         		draw_pause();
					 	}
					 	else{
					 		Status = 4;
					 		Refresh();
					 	}
					 	break;
					 }
			    case VK_ESCAPE:
			        if (TIMERID == 1) {
						Status = 4;
						is_Pause = 0;
						Refresh();
					}
                    break;
			}
			break;
		}
	}
	if (Status == 4){
		switch (event) {
		case KEY_DOWN:
			if (key == 'A' || key == 'S' || key == 'D' || key == 'F'){
		        int t = 0;
				switch(key){
		        	case 'A': t = 1; break;
		        	case 'S': t = 2; break;
		        	case 'D': t = 3; break;
		        	case 'F': t = 4; break; 
				}
  					Click_cnt = 0;
  					SetPenColor("menucolor");
   					Out_Line(Chosen_type);
   					if (scopex != -1){
   						Refresh();
					}
					//scopex = px, scopey = py;
	  				Chosen_type = t;
   					if (cost[Chosen_type] > MONEY) Chosen_type = 0;
   					if (Chosen_type){
						SetPenColor("Red");
						Out_Line(Chosen_type);
					}
 			
			}
			break;
		}
	}
	if (Status == 6){
		switch (event) {
			case KEY_DOWN:
			switch (key) {
				case VK_RETURN: case VK_ESCAPE:{
					cancelTimer(1); Status = 3; draw_Battle(); 
					break;
				}
			}
		}
	}
	
	if (Status == 7){
		switch (event) {
			case KEY_DOWN:
			switch (key) {
				case VK_ESCAPE:{
					cancelTimer(1); Status = 3; draw_Battle(); 
					break;
				}
				case VK_RETURN:{
					Status = 4; Process(Gameid, 0); 
					break;
				}
			}
		}
	}
}
void Process(int Gameid, bool if_load){
	
	init(Gameid, if_load);
 	registerTimerEvent(TimerEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	startTimer(1, P);
}
