#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
//#include "Level1.h"


void buff_clr(void)
{
    char junk;
    do{
        junk=getchar();
    }while(junk!='\n');
}

//for better understanding of ship placement and to shoot
struct BattleShipCo
{
    char x;
    int y;
};
void shipPtrSet(int **ship_Ptr){

    for (int k = 0; k < 11; k++)
    {
        for (int l = 1; l < 11; l++)
        {
            ship_Ptr[k][l] = 2;
        }
        
    }

}
//gernerating board with pointers
void boardGui(char **gui_Ptr){

    int i,j;


    gui_Ptr[0][0]=' ';
    for (i = 1; i < 11; i++)
    {
        gui_Ptr[0][i] = i+47;
        gui_Ptr[i][0] = i+64;
    }
    for (int k = 1; k < 11; k++)
    {
        for (int l = 1; l < 11; l++)
        {
            gui_Ptr[k][l] = '*';
        }
        
    }
}


void drawGui(char **gui_Ptr){

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            printf("%6lc",gui_Ptr[i][j]);
        }
        printf("\n\n");
    }
}

int shipInit(int *shipp){
    int count = 5;
    for (int i = 0; i < 4; i++)
    {
        shipp[i] = count;
        count--;
    }
    
}



int checkCorners(int shipPointer,int s){
    int shipLen = 0;
    shipLen = shipPointer+s-1;
    printf("\nShipLen %d",shipLen);
    if (shipLen > 10){
        return 0;
    }else return 1;
    
    //if the ship is placed at 4 courners of the board give error msg to the user and let him place the ship again
}
int checkAllot(int **ship_ptr,int x,int y,int s,int c){
    int tvalue,count,scount,shipVBlock,shipHBlock;
    shipVBlock =0;
    shipHBlock =0;
    scount =0;
    if (c == 1){
        tvalue = checkCorners(x,s);
        count = s;
        if (tvalue == 1)
        {
            for (int i = 0; i < count; i++)
            {
                if (ship_ptr[x+i][y] != 1 )
                {
                    scount = scount+1;
                }  
            }
            for (int i = 0; i < count; i++)
            {
                if (ship_ptr[x+i][y-1] != 1 && ship_ptr[x+i][y+1] != 1 && ship_ptr[x-1][y] != 1 && ship_ptr[x+count][y] != 1)
                {
                    shipHBlock = shipHBlock+1;
                }
                
            }
            
            
            
            if (scount == s && shipHBlock == count)
            {
                return 1;
            }else return 0;
                    
        }   
    }
    if (c == 2){
        tvalue = checkCorners(y,s);
        count = s;
        if (tvalue == 1)
        {
            for (int i = 0; i < count; i++)
            {
                if (ship_ptr[x][y+i] != 1)
                {
                    scount = scount+1;
                }   
            }
            for (int i = 0; i < count; i++)
            {
                printf("\n letss see wtf");
                if (ship_ptr[x-1][y+i] != 1 && ship_ptr[x+1][y+i] != 1 && ship_ptr[x][y-1] != 1 && ship_ptr[x][y+count] != 1)
                {
                    shipVBlock =shipVBlock+1;
                }
                
            }
            
            
            if (scount == s && shipVBlock ==count)
            {
                return 1;
            }else return 0;
                    
        }   
    }
    
}

/*


int checkCorners(int len,int s){
    int shipLenCheck = 0;
    shipLenCheck = len+s;
    if (shipLenCheck >= 10){
        return 0;
    }else return 1;
    
    //if the ship is placed at 4 courners of the board give error msg to the user and let him place the ship again
}
int checkVerAllot(int **ship_ptr,int x,int y,int s){
    int tvalue,count,scount;
    scount = 0;
    tvalue = checkCorners(y,s);
    count = s;
    if (tvalue == 1)
    {
        for (int i = 0; i < count; i++)
        {
            if (ship_ptr[x+i][y] != 1)
            printf("\n %lc",ship_ptr[x+i][y]);
            {
                scount = scount+1;
            }
            
        }
        if (scount == s)
        {
            return 1;
        }else return 0;
                
    }   
}
   
int checkHorAllot(int **ship_ptr,int x,int y,int s){
    int tvalue,count,scount;
    scount =0;
    tvalue = checkCorners(y,s);
    count = s;
    printf("\nPlacing Ship Horizontally");
    if (tvalue == 1)
    {
        for (int i = 0; i < count; i++)
        {
            if (ship_ptr[x][y+i] != 1)
            printf("\n %lc",ship_ptr[x+i][y]);
            {
                scount = scount+1;
            }
            
        }
        if (scount == s)
        {
            return 1;
        }else return 0;
                
    }   
}
*/

int placingShip(int **shipp_ptr,char **guii_Ptr,int *shipp_def ,int n){
    int xpos,ypos,svalue,tvalue,axis;
    char dir;
    struct BattleShipCo s;
    
    // I need to do something to get it on repeat
    printf("enter co-ordinates(x,y) example A,4  where you want to place the ship **Remember there are no Do-Over**\n");
    scanf("%c,%d",&s.x,&s.y);
    for (int i = 0; i < 11; i++)
    {
        if (guii_Ptr[i][0]==toupper(s.x))
        {
            xpos=i;
            printf("\nxpos:%d",xpos);
        }
        if (guii_Ptr[0][i]==s.y+48)
        {
            ypos=i;
            printf("\nypos:%d",ypos);
        }
        
    }
    svalue = shipp_def[n-1];
    printf("\n Ship Number/Type %d",svalue);
    printf("\nTo place ship vertically enter V to place it horizontally enter H");
    scanf(" %c",&dir);
    buff_clr();
    switch (dir)
    {
    case 'v':
    case 'V':
        tvalue = checkAllot(shipp_ptr,xpos,ypos,svalue,1);
        if (tvalue == 1){
            for (int i = 0; i < svalue; i++)
            {
                shipp_ptr[xpos+i][ypos] = 1;
                guii_Ptr[xpos+i][ypos] = 'X';                
            }
            /*for (int i = 0; i < svalue; i++)
            {
                shipp_ptr[xpos+i][ypos-1] =3;
                shipp_ptr[xpos+i][ypos+1] =3;
            }*/
            printf("\n");
            for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < 12; j++)
                {
                    printf("%6d",shipp_ptr[i][j]);
                }
                printf("\n");
            }
            
            printf("\n\n");
            drawGui(guii_Ptr);
            return 1;
        }else if(tvalue == 0){
            printf("\nAfter Placing the ship at your coridnate either ship goes beond board size or there is another ship parked at same posi :D");
            return 0;
        }// I need to run Repeat 1 again
        break;
    case 'h':
    case 'H':
        tvalue = checkAllot(shipp_ptr,xpos,ypos,svalue,2);
        if (tvalue == 1){
            for (int i = 0; i < svalue; i++)
            {
                shipp_ptr[xpos][ypos+i] = 1;
                guii_Ptr[xpos][ypos+i] = 'X';
            }

            printf("\n");
            for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < 12; j++)
                {
                    printf("%6d",shipp_ptr[i][j]);
                }
                printf("\n");
            }

            printf("\n\n");
            drawGui(guii_Ptr);
            return 1;
        }else if(tvalue == 0){
            printf("\nAfter Placing the ship at your coridnate either ship goes beond board size or fit exactly at corner therefore reenter the coords :D");
            return 0;
        }// I need to Run Reapat 1 again        
        break;

    default:
        printf("You didn't enter correct value");
        return 0;
        break;
    }
}


void shipPlacement(int **ship_Ptr,char **gui_ptr,int *ship_def){
    int i,j,k;
    srand(time(NULL));
    int count = 10;
    int type;
    int des =1;
    int sub =2; 
    int xyz =3;
    int abc =4;
    while (count>0)
    {
        printf("\nEnter the Type of Ship for type 1 type 1 for type 2 type 2 for type 3 type 3 for type 4 type 4 ");
        scanf("%d",&type);
        buff_clr();  
        // ship to be placed on board
        switch (type)// call placingship function while passing down ship ptr
        {
        case 1:
            if (des >0)
            {
                k=placingShip(ship_Ptr,gui_ptr,ship_def,type);
                printf("\n shipVal %d",k);
                if (k ==1){
                    des = des -1;
                    count--;
                }
                k = 0;

            }else(printf("\n You have already place the Ship or entered Wrong board value"));
            break;
        case 2:
            if (sub >0)
            {
                k=placingShip(ship_Ptr,gui_ptr,ship_def,type);
                printf("\n shipVal %d",k);
                if (k ==1){
                    sub = sub -1;
                    count--;
                }
                k = 0;
            }else(printf("\n You have already place the Ship"));
            break;
        case 3:
            if (xyz >0)
            {
                k=placingShip(ship_Ptr,gui_ptr,ship_def,type);
                if (k ==1){
                    xyz = xyz -1;
                    count--;
                }
                k =0;
            }else(printf("\n You have already place the Ship"));
            break;
        case 4:
            if (abc >0)
            {
                k=placingShip(ship_Ptr,gui_ptr,ship_def,type);
                if (k ==1){
                    abc = abc -1;
                    count--;
                }
                k=0;
            }else(printf("\n You have already place the Ship"));
            break;
        
        default:
            printf("\n Please enter Default Value");
            break;
        }
    }
    
}
/*

int getPosValue(char **comGui_Ptr){
    int xpos,ypos;

    srand(time(NULL));
    co.x = (char)(64+(rand()%10));
    co.y = rand()%10;
    for (int i = 0; i < 11; i++)
    {
        if (comGui_Ptr[i][0]==toupper(co.x))
        {
            xpos=i;
        }
        if (comGui_Ptr[0][i]==co.y+48)
        {
            ypos=i;
        }
    }
    return (xpos,ypos);
}
*/

void shipPlacementComputer(int **shipCom_Ptr,int *ship_def,char **comGui_Ptr){
    struct BattleShipCo co;
    int allignment;
    int xpos,ypos,svalue,count,tvalue;
    
    count = 1;
    tvalue = 0;
    srand(time(NULL));
    allignment = ((rand()%2)+1);
    /*
    co.x = (char)(64+(rand()%10));
    co.y = rand()%10;
    for (int i = 0; i < 11; i++)
    {
        if (comGui_Ptr[i][0]==toupper(co.x))
        {
            xpos=i;
        }
        if (comGui_Ptr[0][i]==s.y+48)
        {
            ypos=i;
        }
    }*/
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < count; j++)
        {
            svalue = ship_def[i];
            while (tvalue != 1)
            {
                //xpos,ypos = getPosValue(comGui_Ptr);
                co.x = (char)(64+(rand()%10));
                co.y = rand()%10;
                for (int i = 0; i < 11; i++)
                {
                    if (comGui_Ptr[i][0]==toupper(co.x))
                    {
                        xpos=i;
                    }
                    if (comGui_Ptr[0][i]==co.y+48)
                    {
                        ypos=i;
                    }
                }
                printf("\n xposINSHIPCOM:%d\nyposINSHIPCOM%d",xpos,ypos);
                tvalue = checkAllot(shipCom_Ptr,xpos,ypos,svalue,allignment);
                if (tvalue == 1 && allignment == 1){
                    for (int i = 0; i < svalue; i++)
                    {
                        shipCom_Ptr[xpos+i][ypos] = 1;   
                        comGui_Ptr[xpos+i][ypos] = 'X';             
                    }
                    printf("\n\n");
                }
                if (tvalue == 1 && allignment == 2)
                {
                    for (int i = 0; i < svalue; i++)
                    {
                        shipCom_Ptr[xpos][ypos+i] = 1;
                        comGui_Ptr[xpos][ypos+i] = 'X';
                    }
                    printf("\n\n");
                }   
            }
            allignment = ((rand()%2)+1);
            tvalue = 0;
        }
        count = count +1;
        printf("\nCount=%d",count);
    }
    printf("\nDone Placing Computer Ship");
    printf("\n\n");
    drawGui(comGui_Ptr);
}

/*

int comShipShooting(int **oppShip_Ptr,char **oppGui_Ptr,int *score_Ptr){
    int xpos,ypos;
    srand(time(NULL));

    co.x = (char)(64+(rand()%10));
    co.y = rand()%10;
    for (int i = 0; i < 11; i++)
    {
        if (oppGui_Ptr[i][0]==(co.x))
        {
            xpos=i;
        }
        if (oppGui_Ptr[0][i]==co.y+48)
        {
            ypos=i;
        }
    }
    if (oppShip_Ptr[xpos][ypos] == 1 && oppGui_Ptr[xpos][ypos]=='*')
    {
        // Need to make it reshoot
        printf("\nHit From Computer");
        oppGui_Ptr[xpos][ypos] == 'X';
        score_Ptr[0] = score_Ptr[0] +1;
        return 2;

    }
    else if (oppShip_Ptr[xpos][ypos] == 1 && oppGui_Ptr[xpos][ypos] == 'X')
    {
        //printf("\nYou have Already hitted here please re enter the coords and rehit");
        return 2;
        // Bad input Need to rewrite coords

    }
    else if (oppShip_Ptr[xpos][ypos] != 1 && oppGui_Ptr[xpos][ypos] == 'O')
    {
        //Bad input need to reshoot

        //printf("\nYou have Already hitted here please re enter the coords and rehit");
        return 2;
    }
    
    else if (oppShip_Ptr[xpos][ypos] != 1 && oppGui_Ptr[xpos][ypos]== '*')
    {
        printf("\nMiss From Computer");
        oppGui_Ptr[xpos][ypos] = 'O';
        return 1;
    }

}
int playerShoot(int **oppShip_Ptr,char **oppGui_Ptr,int *score_Ptr){
    int xpos,ypos;
    char xCord;
    int yCord;
    int j=0;

    drawGui(oppGui_Ptr);

    printf("\n\nEnter Coordinate you want to attack on opponent board\n");
    
    scanf("%c,%d",&co.x,&co.y);
    buff_clr();
    for (j = 0; j < 11; j++)
    {
        //printf("Alphabets: %c\nNumbers: %c\n",oppGui_Ptr[j][0],oppGui_Ptr[0][j]);
        if (oppGui_Ptr[j][0] == toupper(co.x))
        {
            printf("x.i %c\n",oppGui_Ptr[j][0]);
            printf("value j: %d",j);
            xpos=j;
        }
        if (oppGui_Ptr[0][j]==co.y+48)
        {
            ypos=j;
        }
    }
    //scanf("%c,%d",&xCord,&yCord);
    printf("S.X: %c\n",co.x);*/
    /*
    for (int i = 0; i < 11; i++)
    {
        if (oppGui_Ptr[i][0]==(char)toupper(xCord))
        {
            xpos=i;
            printf("\nxpos:%d",xpos);
        }
        if (oppGui_Ptr[0][i]==yCord+48)
        {
            ypos=i;
            printf("\nypos:%d",ypos);
        }
        
    }*//*
    printf("XPOS: %c\nYPOS: %d\n",xpos,ypos);
    if (oppShip_Ptr[xpos][ypos] == 1 && oppGui_Ptr[xpos][ypos]=='*')
    {
        // Need to make it reshoot
        printf("\nHit");
        oppGui_Ptr[xpos][ypos] == 'X';
        score_Ptr[0] = score_Ptr[0] +1;
        return 1;

    }
    else if (oppShip_Ptr[xpos][ypos] == 1 && oppGui_Ptr[xpos][ypos] == 'X')
    {
        printf("\nYou have Already hitted here please re enter the coords and rehit");
        return 1;
        // Bad input Need to rewrite coords
    }
    else if (oppShip_Ptr[xpos][ypos] != 1 && oppGui_Ptr[xpos][ypos] == 'O')
    {
        //Bad input need to reshoot
        printf("\nYou have Already hitted here please re enter the coords and rehit");
        return 1;
    }
    
    else if (oppShip_Ptr[xpos][ypos] != 1 && oppGui_Ptr[xpos][ypos]== '*')
    {
        printf("\nMiss");
        oppGui_Ptr[xpos][ypos] = 'O';
        return 2;
    }
    

}
int level1(int **comShip_ptr,int **playerShip_ptr,char **comGui_ptr, char **playerGui_ptr)
{
    int firstShoot,changeShooter;
    int xPos,yPos;
    //,comPoints,player1Points;
    int *comScorePointer;
    int *playerScorePointer;

    comScorePointer = (int*)malloc(1*sizeof(int));
    playerScorePointer = (int*)malloc(1*sizeof(int));

    comScorePointer[0]=0;
    playerScorePointer[0]=0;
    //flipCoinToNum = 2;
    /*
    comPoints =0;
    player1Points =0;
    *comScorePointer = &comPoints;
    *playerScorePointer = &player1Points;*//*
    srand(time(NULL));


    firstShoot = rand()%2;
    printf("\nfirstshoot %d\n",firstShoot);
  
  /*


    do
    {
        printf("\nTO DECIDE WETHER COMPUTER SHOOTS 1ST OR YOU WE ARE GOING TO FLIP A COIN");
        printf("\nYou have the option to select heads or tails\nFor Head enter 'h' or 'H' and for Tails enter 't' or 'T'\n");
        //flipCoin = getchar();
        scanf("%c",&flipCoin);
        buff_clr();
        /*
        switch (flipCoin)
        {
        case 'h':
        case 'H':
            int flipCoinToNum = 1;
            break;
        case 't':
        case 'T':
            int flipCoinToNum = 0;
            break;
        default:
            printf("wrong value re enter");
            break;
        }
        if (flipCoin == "h" || flipCoin == "H")
        {
            flipCoinToNum =1;
        }
        else if (flipCoin == "t" || flipCoin == "T")
        {
            flipCoinToNum =0;
        }
        else{
            printf("\nEnter Correct Value\n");  
        }
        }while (flipCoinToNum != 1 || flipCoinToNum != 0);

    *//*
    //printf("\n%c",flipCoin);
    //if (flipCoinToNum == 1 && firstShoot == 1) 
    if(firstShoot ==1)
    {
        printf("we in if statement\n");
        printf("%d\n",comScorePointer[0]);
        changeShooter = 1;
        while (comScorePointer[0] != 30 || playerScorePointer[0] !=30)
        {
            if (changeShooter == 1){
                changeShooter = playerShoot(comShip_ptr,comGui_ptr,playerScorePointer);
            }
            if (changeShooter == 2)
            {
                changeShooter = comShipShooting(playerShip_ptr,playerGui_ptr,comScorePointer);
            }
        }
        
    }/*
    else if (flipCoinToNum == 0 && firstShoot == 0)
    {
        //Let Plater shoot First
        changeShooter = 1;
        while (comScorePointer[0] == 30 || playerScorePointer[0] ==30)
        {
            /* code 
            if (changeShooter == 1){
                changeShooter = playerShoot(comShip_ptr,comGui_ptr,playerScorePointer);
            }
            if (changeShooter == 2)
            {
                changeShooter = comShipShooting(playerShip_ptr,playerGui_ptr,comScorePointer);
            }

        }
        
    }*//*
    else if(firstShoot == 0){
        printf("we in else if statement\n");
        //computer shoot first
        changeShooter = 2;
        while (playerScorePointer[0] !=30 || comScorePointer[0] != 30)
        {
            /* code *//*
            if (changeShooter == 1){
                changeShooter = playerShoot(comShip_ptr,comGui_ptr,playerScorePointer);
                printf("\n Com Board:\n\n");
                drawGui(comGui_ptr);
                printf("\n");
            }
            if (changeShooter == 2)
            {
                printf("Change shooter = 2\n");
                changeShooter = comShipShooting(playerShip_ptr,playerGui_ptr,comScorePointer);
                printf("\n Player Board:\n\n");
                drawGui(playerGui_ptr);
                printf("\n");
            }

        }
        
    }

}*/



//void shipBattleCom(int **ship_Ptr,char **gui_Ptr)


int shootShip(char **gui_ptr,int **ship_ptr,int *score_ptr){
    int xpos,ypos,score,toShoot;
    struct BattleShipCo s;
    toShoot = 1;
    score =0;
    while (toShoot != 0)
    {
    
        printf("enter coords\n");
        scanf("%c,%d",&s.x,&s.y);
        buff_clr();
        //if (toupper(s.x) >63 && toupper(s.x) < 75 && s.y <11)
        //{
            
            for (int i = 0; i < 11; i++)
            {
                if (gui_ptr[i][0] == toupper(s.x))
                {
                    xpos =i;
                }
                if (gui_ptr[0][i]== s.y+48)
                {
                    ypos = i;
                }
            }

            if (ship_ptr[xpos][ypos] == 1 && gui_ptr[xpos][ypos]=='*')
            {
                // Need to make it reshoot
                printf("\nHit\n\n ");
                gui_ptr[xpos][ypos] = 'X';
                score_ptr[0] = score_ptr[0]+1;
                score = score +1;
                drawGui(gui_ptr);
                //score_Ptr[0] = score_Ptr[0] +1;
                //return 1;

            }
            else if (ship_ptr[xpos][ypos] == 1 && gui_ptr[xpos][ypos] == 'X')
            {
                printf("\nYou have Already hitted here please re enter the coords and rehit\n\n");
                drawGui(gui_ptr);
                //return 1;
                // Bad input Need to rewrite coords
            }
            else if (ship_ptr[xpos][ypos] != 1 && gui_ptr[xpos][ypos] == 'O')
            {
                //Bad input need to reshoot
                printf("\nYou have Already hitted here please re enter the coords and rehit\n\n");
                drawGui(gui_ptr);
                //return 1;
            }
            
            else if (ship_ptr[xpos][ypos] != 1 && gui_ptr[xpos][ypos]== '*')
            {
                printf("\nMiss\n\n");
                gui_ptr[xpos][ypos] = 'O';
                toShoot = 0;
                drawGui(gui_ptr);
                //return 2;
            }
        /*}else{
            shootShip(gui_ptr,ship_ptr,score_ptr);
            printf("\nWrong Input of coords\n\n");

        }*/
    }
}



int comShootShip(char **gui_ptr,int **ship_ptr,int *score_ptr){
    int xpos,ypos,score,toShoot;
    struct BattleShipCo s;
    srand(time(NULL));


    toShoot = 1;
    score =0;
    while (toShoot != 0)
    {
    
        //printf("enter coords\n");
        //scanf("%c,%d",&s.x,&s.y);
        //buff_clr();
        s.x = (char)((rand()%10)+63);
        s.y = rand()%10;
        for (int i = 0; i < 11; i++)
        {
            if (gui_ptr[i][0] == toupper(s.x))
            {
                xpos =i;
            }
            if (gui_ptr[0][i]== s.y+48)
            {
                ypos = i;
            }
        }

        if (ship_ptr[xpos][ypos] == 1 && gui_ptr[xpos][ypos]=='*')
        {
            // Need to make it reshoot
            printf("\nHit\n \n");
            gui_ptr[xpos][ypos] = 'X';
            score_ptr[0] = score_ptr[0]+1;
            score = score +1;
            drawGui(gui_ptr);
            //score_Ptr[0] = score_Ptr[0] +1;
            //return 1;

        }
        else if (ship_ptr[xpos][ypos] == 1 && gui_ptr[xpos][ypos] == 'X')
        {
            printf("\nYou have Already hitted here please re enter the coords and rehit\n\n");
            drawGui(gui_ptr);
            //return 1;
            // Bad input Need to rewrite coords
        }
        else if (ship_ptr[xpos][ypos] != 1 && gui_ptr[xpos][ypos] == 'O')
        {
            //Bad input need to reshoot
            printf("\nYou have Already hitted here please re enter the coords and rehit\n\n");
            drawGui(gui_ptr);
            //return 1;
        }
        
        else if (ship_ptr[xpos][ypos] != 1 && gui_ptr[xpos][ypos]== '*')
        {
            printf("\nMiss\n\n");
            gui_ptr[xpos][ypos] = 'O';
            toShoot = 0;
            drawGui(gui_ptr);
            //return 2;
        }
    }
}



int main(){
    char **guiComPtr,**guiPlayer1Ptr,**guiPlayer2Ptr;
    int *shipDefCom,*shipDefPlayer1,*shipDefPlayer2;
    int **shipCom,**shipPlayer1,**shipPlayer2;
    int modeSelection,placeShipSelection;
    int *comScore,*playerScore,*player2Score;
    int comScoreCounter,playerScoreCounter;
    char levelSelection;
    int i,j,errorHandler,score;


    shipCom = (int**)malloc(11*sizeof(int*));// to know where computer has placed their ship
    for (int i = 0; i < 12; i++)
    {
        shipCom[i]=(int*)malloc(11*sizeof(int));
    }

    guiComPtr = (char**)malloc((11)*sizeof(char*));// the gui board of our game
    for(i=0;i<12;i++)
    {
        guiComPtr[i]=(char*)malloc((11)*sizeof(char));
    }

    shipPlayer1 =(int**)malloc((11)*sizeof(int*));
    for (int i = 0; i < 12; i++)
    {
        shipPlayer1[i] = (int*)malloc((11)*sizeof(int));
    }
    guiPlayer1Ptr = (char**)malloc((11)*sizeof(char*));// the gui board of our game
    for(i=0;i<12;i++)
    {
        guiPlayer1Ptr[i]=(char*)malloc((11)*sizeof(char));
    }
    shipPlayer2 = (int**)malloc(11*sizeof(int*));// to know where computer has placed their ship
    for (int i = 0; i < 12; i++)
    {
        shipPlayer2[i]=(int*)malloc(11*sizeof(int));
    }

    guiPlayer2Ptr = (char**)malloc((11)*sizeof(char*));// the gui board of our game
    for(i=0;i<12;i++)
    {
        guiPlayer2Ptr[i]=(char*)malloc((11)*sizeof(char));
    }

    shipDefCom = (int*)malloc(5*sizeof(int));//ship pointer as we have 4 types of ship
    shipInit(shipDefCom);

    shipDefPlayer1 = (int*)malloc(5*sizeof(int));
    shipInit(shipDefPlayer1);

    shipDefPlayer2 = (int*)malloc(5*sizeof(int));//ship pointer as we have 4 types of ship
    shipInit(shipDefPlayer2);

    comScore = (int*)malloc(1*sizeof(int));
    playerScore = (int*)malloc(1*sizeof(int));
    player2Score = (int*)malloc(1*sizeof(int));

    boardGui(guiComPtr);
    boardGui(guiPlayer1Ptr);
    boardGui(guiPlayer2Ptr);

    printf("\nTo play with computer enter 1 to play with player enter 2\n");
    scanf("%d",&modeSelection);
    if (modeSelection == 1)
    {
        printf("\nSelect Level\nFor Easy enter 'e' or 'E' for Hard enter 'h' or 'H'\n");
        scanf("%c",&levelSelection);
        buff_clr();
        if (levelSelection == 'e' || 'E')
        {
            
            shipPlacementComputer(shipCom,shipDefCom,guiComPtr);
            time(NULL);
            shipPlacementComputer(shipPlayer1,shipDefPlayer1,guiPlayer1Ptr);
            //shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
            boardGui(guiComPtr);
            boardGui(guiPlayer1Ptr);

            while (comScore[0] != 30 && playerScore[0] != 30)
            {
                shootShip(guiComPtr,shipCom,playerScore);
                printf("\nPlayer Score %d\n\n",playerScore[0]);
                if (comScore[0] == 30)
                {
                    break;
                }
                
                comShootShip(guiPlayer1Ptr,shipPlayer1,comScore);
                printf("\nComScore %d\n\n",comScore[0]);
                printf("\n");
                drawGui(guiComPtr);
                if (playerScore[0] == 30)
                {
                    break;
                }        
            }   


        }else if (levelSelection == 'h' || 'H')
        {
            /* code */
        }
        else{
            printf("Wrong Input :(");
        }
        
        
    }
    else if (modeSelection == 2)
    {
        
        shipPlacementComputer(shipPlayer2,shipDefPlayer2,guiPlayer2Ptr);
        time(NULL);
        shipPlacementComputer(shipPlayer1,shipDefPlayer1,guiPlayer1Ptr);
        //shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
        boardGui(guiPlayer2Ptr);
        boardGui(guiPlayer1Ptr);

        while (player2Score[0] != 30 && playerScore[0] != 30)
        {
            shootShip(guiPlayer2Ptr,shipPlayer2,playerScore);
            printf("\nPlayer Score %d\n\n",playerScore[0]);
            printf("\n\n");
            //drawGui(guiPlayer2Ptr);
            if (playerScore[0] == 30)
            {
                break;
            }
            
            shootShip(guiPlayer1Ptr,shipPlayer1,player2Score);
            printf("\nComScore %d\n\n",player2Score[0]);
            printf("\n\n");
            //drawGui(guiPlayer1Ptr);
            if (player2Score[0] == 30)
            {
                break;
            }        
        }

    }
    else{
        printf("Wrong Value Exiting Code..... :(");
    }
    
    





    /*
    printf("\n\nDo you want to Place Ship Randomly ?? if Yes Enter 1 or else Enter 2");
    scanf("%d",&placeShipSelection);
    if (placeShipSelection == 1)
    {
        shipPlacementComputer(shipPlayer1,shipDefPlayer1,guiPlayer1Ptr);
    }
    else{
        shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
    }
    boardGui(guiPlayer1Ptr);*/










/*
    boardGui(guiComPtr);
    shipPtrSet(shipCom);
    drawGui(guiComPtr);
    shipPlacement(shipCom,guiComPtr,ship);
*/

    /*
    printf("\nTo play with Player Enter 1\nTo play with computer enter 2");
    scanf("%d",&modeSelection);
    buff_clr();
    if (modeSelection == 1){
        printf("\n Player Vs PLayer");
        /*
        shipPlayer2 = (int**)malloc(11*sizeof(int*));// to know where computer has placed their ship
        for (int i = 0; i < 12; i++)
        {
            shipPlayer2[i]=(int*)malloc(11*sizeof(int));
        }

        guiPlayer2Ptr = (char**)malloc((11)*sizeof(char*));// the gui board of our game
        for(i=0;i<12;i++)
        {
            guiPlayer2Ptr[i]=(char*)malloc((11)*sizeof(char));
        }

        shipPlayer1 =(int**)malloc((11)*sizeof(int*));
        for (int i = 0; i < 12; i++)
        {
            shipPlayer1[i] = int(*)malloc((11)*sizeof(int));
        }
        guiPLayer1Ptr = (char**)malloc((11)*sizeof(char*));// the gui board of our game
        for(i=0;i<12;i++)
        {
            guiPLayer1Ptr[i]=(char*)malloc((11)*sizeof(char));
        }*//*
    }
    if(modeSelection ==2){

        shipCom = (int**)malloc(11*sizeof(int*));// to know where computer has placed their ship
        for (int i = 0; i < 12; i++)
        {
            shipCom[i]=(int*)malloc(11*sizeof(int));
        }

        guiComPtr = (char**)malloc((11)*sizeof(char*));// the gui board of our game
        for(i=0;i<12;i++)
        {
            guiComPtr[i]=(char*)malloc((11)*sizeof(char));
        }

        shipPlayer1 =(int**)malloc((11)*sizeof(int*));
        for (int i = 0; i < 12; i++)
        {
            shipPlayer1[i] = (int*)malloc((11)*sizeof(int));
        }
        guiPlayer1Ptr = (char**)malloc((11)*sizeof(char*));// the gui board of our game
        for(i=0;i<12;i++)
        {
            guiPlayer1Ptr[i]=(char*)malloc((11)*sizeof(char));
        }

        shipDefCom = (int*)malloc(5*sizeof(int));//ship pointer as we have 4 types of ship
        shipInit(shipDefCom);

        shipDefPlayer1 = (int*)malloc(5*sizeof(int));
        shipInit(shipDefPlayer1);

        boardGui(guiComPtr);
        boardGui(guiPlayer1Ptr);



        printf("\nEnter 'E' for Easy level or Enter 'M' for Medium Level");
        scanf("%c",&levelSelection);
        buff_clr();
        levelSelection = toupper(levelSelection);
        switch (levelSelection)
        {
        case 'E':
            shipPlacementComputer(shipCom,shipDefCom,guiComPtr);
            boardGui(guiComPtr);
            printf("\n\nDo you want to Place Ship Randomly ?? if Yes Enter 1 or else Enter 2");
            scanf("%d",&placeShipSelection);
            if (placeShipSelection == 1)
            {
                shipPlacementComputer(shipPlayer1,shipDefPlayer1,guiPlayer1Ptr);
            }
            else{
                shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
            }
            boardGui(guiPlayer1Ptr);
            level1(shipCom,shipPlayer1,guiComPtr,guiPlayer1Ptr);
            break;
        
        default:
            break;
        }
        
    }
    */

    return 0;
}