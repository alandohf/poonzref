#include <stdio.h>

/* type, position coordinates and armament */
struct _ship
{
  int type;
  int x;
  int y;
  int missiles;
};

typedef struct _ship ship;

int
main()
{
  ship battle_ship_1;
  ship battle_ship_2 = {1, 60, 66, 8};

  battle_ship_1.type = 63;
  battle_ship_1.x = 54;
  battle_ship_1.y = 98;
  battle_ship_1.missiles = 12;

  /* More code to actually use this data would go here */

  return 0;
}

