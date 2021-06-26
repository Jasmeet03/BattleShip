#include "BattleShip.c"

int level1(int **comShip_ptr,int **playerShip_ptr,char **comGui_ptr, char **playerGui_ptr,struct BattleShipCo co){
    int firstShoot;

    srand(time(NULL));

    co.x = rand/11;
    co.y = rand%11;
}