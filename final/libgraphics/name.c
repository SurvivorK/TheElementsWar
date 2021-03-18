#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MONSTER{
  double x, y;
  double v;
  double hpr, hpg, hpb;
  int slowdown_cnt;
  int burnt_cnt;
  int road;
  int swerve_cnt;
  int is_alive;
  struct MONSTER *nxt;
};

struct TOWER{
  double x, y;
  int cool_down;
  int type;
};
struct PATH{
	double STx, STy, Endx, Endy;
	double Crossroadx[10];
	double Crossroady[10];
	int Direction[20], Crossroad_cnt;
};
