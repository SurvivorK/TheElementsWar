#ifndef _name_h
#define _name_h
struct MONSTER{
  double x, y;
  double v;
  double hpr, hpg, hpb;
  int slowdown_cnt;
  int burnt_cnt;
  int road;
  int swerve_cnt;
  bool is_alive;
  struct MONSTER* nxt;
};

typedef struct MONSTER MONSTER;
typedef MONSTER* PMONS;

typedef struct{
	int cnt;
	double v;
	int hp_limit;
	int hp_base;
	int blank_time;
	int appear_itvl;
	//Monster_Wave(int _cnt = 0, int _v = 0, int _hp = 0, int _appear = 0):cnt(_cnt), v(_v), hp_limit(_hp), appear_itvl(_appear){}
}Monster_Wave;
//extern MONSTER MONSTER;
typedef struct{
  double x, y;
  int cool_down;
  int type;
}TOWER;
typedef struct{
	double STx, STy, Endx, Endy;
	double Crossroadx[10];
	double Crossroady[10];
	int Direction[20], Crossroad_cnt;
}PATH;
//extern TOWER TOWER;
#endif
