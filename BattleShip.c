#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_RANDOM ((1 << 31) - 1)


//#include "Level1.h"

//To Remove Junk value
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
/*
void shipPtrSet(int **ship_Ptr){

    for (int k = 0; k < 11; k++)
    {
        for (int l = 1; l < 11; l++)
        {
            ship_Ptr[k][l] = 2;
        }
        
    }
}*/

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

// Drawing Board on terminal
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
// There are 4 type of ship with Different Value Such as Destroyer / Submarine etc etc I am not good at naming :P
// Creating Different Ship with Different Value
int shipInit(int *shipp){
    int count = 5;
    for (int i = 0; i < 4; i++)
    {
        shipp[i] = count;
        count--;
    }
    
}


// To Check if placing a ship at specific pos will go out of bounds for example placing a ship of length 5 at 7,7 cords od 10*10 board (horiz or verti) will get it out of board
int checkCorners(int shipPointer,int s){
    int shipLen = 0;
    shipLen = shipPointer+s-1;
    //printf("\nShipLen %d",shipLen);
    if (shipLen > 10){
        return 0;
    }else if(shipLen <= 10){
        return 1;
    }
    //if the ship is placed at 4 courners of the board give error msg to the user and let him place the ship again
}

// to check if there is 1 unit of block between two ship and to check if there are ships on that posi or not
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
            }else if (scount != s && shipHBlock != count){
                return 0;
            }
                    
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
                //printf("\n letss see");
                if (ship_ptr[x-1][y+i] != 1 && ship_ptr[x+1][y+i] != 1 && ship_ptr[x][y-1] != 1 && ship_ptr[x][y+count] != 1)
                {
                    shipVBlock =shipVBlock+1;
                }
                
            }
            
            
            if (scount == s && shipVBlock ==count)
            {
                return 1;
            }else if(scount != s && shipVBlock != count){
                return 0;
            }
                    
        }   
    }
    
}

// To place the Ship on Board
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
            //printf("\nxpos:%d",xpos);
        }
        if (guii_Ptr[0][i]==s.y+48)
        {
            ypos=i;
            //printf("\nypos:%d",ypos);
        }
        
    }
    svalue = shipp_def[n-1];
    printf("\nShip length: %d",svalue);
    printf("\nTo place ship vertically enter V to place it horizontally enter H  ");
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
            /*
            for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < 12; j++)
                {
                    printf("%6d",shipp_ptr[i][j]);
                }
                printf("\n");
            }*/
            
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
            /*
            for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < 12; j++)
                {
                    printf("%6d",shipp_ptr[i][j]);
                }
                printf("\n");
            }*/

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

//The actual call of Ship Placement which is like controll unit for rest of the fn which helps placing ship
void shipPlacement(int **ship_Ptr,char **gui_ptr,int *ship_def){
    int i,j,k;
    int count = 10;//Total number of ship on board is 10 which total occupies 30 unit of square or 30 data size out of 121 data size 
    int type;
    int des =1;//this are four type of ship as i mentioned earlier i am noot good at naming 
    int sub =2; 
    int xyz =3;
    int abc =4;
    while (count>0)
    {
        printf("\nEnter the Type of Ship \nFor DEstroyer of Size 5 Qty 1 enter 1\nFor Submarine Size 4 Qty 2 enter 2\nFor Little Bird Size 3 Qty 3 enter 3\nFor type Scout Size 2 Qty 4 enter 4 ");
        scanf("%d",&type);
        buff_clr();  
        // ship to be placed on board
        switch (type)// call placingship function while passing down ship ptr
        {
        case 1:
            if (des >0)
            {
                k=placingShip(ship_Ptr,gui_ptr,ship_def,type);
                //printf("\n shipVal %d",k);
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
                //printf("\n shipVal %d",k);
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

    srandom(time(NULL));
    co.x = (char)(64+(random()%10));
    co.y = random()%10;
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

// computer placing Ship randomly
void shipPlacementComputer(int **shipCom_Ptr,int *ship_def,char **comGui_Ptr){
    struct BattleShipCo co;
    int allignment;
    int xpos,ypos,svalue,count,tvalue;
    //long n;
    //u_int32_t n = arc4random_uniform(10);
    //printf("%d",n);

    count = 1;
    tvalue = 0;
    srand(time(NULL));
    rand();
    allignment = ((rand()%2)+1);
    /*
    co.x = (char)(64+(random()%10));
    co.y = random()%10;
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
                rand();
                co.x = (char)(64+(rand()%10));
                rand();
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
                //printf("\n xposINSHIPCOM:%d\nyposINSHIPCOM%d",xpos,ypos);
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
            rand();
            allignment = ((rand()%2)+1);
            tvalue = 0;
        }
        count = count +1;
        //printf("\nCount=%d",count);
    }
    printf("\nDone Placing Computer Ship");
    //printf("\n\n");
    //drawGui(comGui_Ptr);
}


// Shooting the ship
int shootShip(char **gui_ptr,int **ship_ptr,int *score_ptr){
    int xpos,ypos,score,toShoot;
    struct BattleShipCo s;
    toShoot = 1;
    score =0;
    while (toShoot != 0)
    {
        if (score_ptr[0] == 30)
        {
            toShoot = 0;
            break;
        }
        do{
            printf("enter coords\n");
            scanf("%c,%d",&s.x,&s.y);
            buff_clr();
        }while(toupper(s.x) <63 || toupper(s.x) > 75 || s.y >10);
    /*
        printf("enter coords\n");
        scanf("%c,%d",&s.x,&s.y);
        buff_clr();
        if (toupper(s.x) <63 || toupper(s.x) > 75 || s.y >10)
        {   do{
            printf("enter coords\n");
            scanf("%c,%d",&s.x,&s.y);
            buff_clr();
            }while(toupper(s.x) <63 || toupper(s.x) > 75 || s.y >10)
        }
    */
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
                printf("\nHit\n\n\n");
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


// Function for automatic shooting as level 1 as probability of shooting ship is 1/100
int comShootShip(char **gui_ptr,int **ship_ptr,int *score_ptr){
    int xpos,ypos,score,toShoot,i;
    struct BattleShipCo s;


    srand(time(NULL));


    toShoot = 1;
    score =0;
    while (toShoot != 0)
    {

        if (score_ptr[0] == 30)
        {
            toShoot = 0;
        }
        //printf("enter coords\n");
        //scanf("%c,%d",&s.x,&s.y);
        //buff_clr();
        s.x = (char)((rand()%10)+65);
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
        i = 0;


        if (ship_ptr[xpos][ypos] == 1 && gui_ptr[xpos][ypos]=='*')
        {
            // Need to make it reshoot
            printf("\nHit\n\n\n");
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




// computer shooting ship with accuracy of 25percent + getting 1 out of rest randly 
int comShootShip_Lvl2(char **gui_ptr,int **ship_ptr,int *score_ptr){
    int xpos,ypos,score,toShoot,shootProb,j,k,i;
    struct BattleShipCo s;

    srand(time(NULL));

    shootProb = rand()%3+1;
    //printf("*********Level 2*************\n");
    //printf("\nShootProb: %d",shootProb);
    toShoot = 1;
    score =0;

    while (toShoot != 0)
    {
        if (score_ptr[0] == 30)
        {
            toShoot = 0;
        }
    
        if (shootProb == 1)
        {
            for (j = 0; j < 11; j++)
            {
                for (k = 0; k < 11; k++)
                {
                    if (ship_ptr[j][k] == 1 && gui_ptr[j][k] != 'X')
                    {
                        xpos = j;
                        ypos = k;
                    }
                    
                }
                
            }
            
        }else if(shootProb != 1){
            s.x = (char)((rand()%10)+65);
            s.y = rand()%10;

            //printf("\n in else if after prob s.x: %c",s.x);

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
            i = 0;
        }
        //printf("Level 2 Xpos: %d Ypos: %d\n",xpos,ypos);
        
        

        if (ship_ptr[xpos][ypos] == 1 && gui_ptr[xpos][ypos]=='*')
        {
            // Need to make it reshoot
            printf("\nHit\n\n");
            gui_ptr[xpos][ypos] = 'X';
            score_ptr[0] = score_ptr[0]+1;
            score = score +1;
            drawGui(gui_ptr);
            shootProb = rand()%3+1;
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
            shootProb = rand()%3+1;
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
    int i,j,errorHandler,score,inputHandler;
    char player1Name[50],player2Name[50];


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
    shipDefCom = (int*)malloc(5*sizeof(int));//ship pointer as we have 4 types of ship
    shipInit(shipDefCom);
    comScore = (int*)malloc(1*sizeof(int));
    boardGui(guiComPtr);


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
    shipDefPlayer1 = (int*)malloc(5*sizeof(int));
    shipInit(shipDefPlayer1);
    playerScore = (int*)malloc(1*sizeof(int));
    boardGui(guiPlayer1Ptr);


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
    shipDefPlayer2 = (int*)malloc(5*sizeof(int));//ship pointer as we have 4 types of ship
    shipInit(shipDefPlayer2);
    player2Score = (int*)malloc(1*sizeof(int));
    boardGui(guiPlayer2Ptr);



    printf("\nTo play with computer enter 1 to play with player enter 2 To know the Rules Enter 3\n");
    scanf("%d",&modeSelection);
    if (modeSelection == 1)
    {
        printf("\nPLease Enter Your Name:  ");
        scanf("%s",player1Name);   
        printf("\n\nSelect Level\nFor Easy enter 'e' or 'E' for Hard enter 'h' or 'H'\n\n");
        scanf("%s",&levelSelection);
        buff_clr();
        /*
        switch (levelSelection)
        {
        case 'e':
        case 'E':

            printf("\nWould You Like to Plcae ship Randomly or do you want to place it your self ?\nTo place randly enter 1 \nTo PLace it your self enter 2\n");
            scanf("%d",&inputHandler);
            if (inputHandler <= 1)
            {
                shipPlacementComputer(shipPlayer1,shipDefPlayer1,guiPlayer1Ptr);
            }
            if (inputHandler >= 2)
            {
                shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
            }
            
            
            
            shipPlacementComputer(shipCom,shipDefCom,guiComPtr);
            //shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
            boardGui(guiComPtr);
            boardGui(guiPlayer1Ptr);

            printf("\nDone PLacing %s Ship",player1Name);
            printf("\n%s is Shooting First\n\n",player1Name);
            drawGui(guiPlayer1Ptr);
            printf("LEVEL 1\n");
            while (comScore[0] != 30 && playerScore[0] != 30)
            {
                shootShip(guiComPtr,shipCom,playerScore);
                printf("\nPlayer Score %d\n\n",playerScore[0]);
                if (comScore[0] == 30 && playerScore[0] < 30)
                {   
                    printf("\nOpps! Computer Won The Game\n\n");
                    break;
                }
                
                comShootShip(guiPlayer1Ptr,shipPlayer1,comScore);
                printf("\nComScore %d\n\n",comScore[0]);
                printf("\n");
                drawGui(guiComPtr);
                if (playerScore[0] == 30 && comScore[0] < 30)
                {
                    printf("\nCongo!! %s Won The Game :D",player1Name);
                    break;
                }        
            }   


            break;
        case 'h':
        case 'H':

            printf("\nWould You Like to Plcae ship Randomly or do you want to place it your self ?\nTo place randomly enter 1 \nTo PLace it your self enter 2\n");
            scanf("%d",&inputHandler);
            if (inputHandler <= 1)
            {
                shipPlacementComputer(shipPlayer1,shipDefPlayer1,guiPlayer1Ptr);
            }
            if (inputHandler >= 2)
            {
                shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
            }

            shipPlacementComputer(shipCom,shipDefCom,guiComPtr);
            time(NULL);
            shipPlacementComputer(shipPlayer1,shipDefPlayer1,guiPlayer1Ptr);
            //shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
            boardGui(guiComPtr);
            boardGui(guiPlayer1Ptr);

            printf("\nDone PLacing %s Ship",player1Name);
            printf("\n%s is Shooting First\n\n",player1Name);
            drawGui(guiPlayer1Ptr);
            printf("LEVEL 2\n");

            while (comScore[0] != 30 && playerScore[0] != 30)
            {
                shootShip(guiComPtr,shipCom,playerScore);
                printf("\nPlayer Score %d\n\n",playerScore[0]);
                if (comScore[0] == 30)
                {
                    break;
                }
                
                comShootShip_Lvl2(guiPlayer1Ptr,shipPlayer1,comScore);
                printf("\nComScore %d\n\n",comScore[0]);
                printf("\n");
                drawGui(guiComPtr);
                if (playerScore[0] == 30)
                {
                    break;
                }        
            }   



            break;
        
        default:
            printf("Wrong Input :(");
            main();
            break;
        }
        */
        if (levelSelection == 'e' || levelSelection == 'E')
        {   
            printf("\nWould You Like to Plcae ship Randomly or do you want to place it your self ?\nTo place randomly enter 1 \nTo PLace it your self enter 2\n");
            scanf("%d",&inputHandler);
            if (inputHandler <= 1)
            {
                shipPlacementComputer(shipPlayer1,shipDefPlayer1,guiPlayer1Ptr);
            }
            if (inputHandler >= 2)
            {
                shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
            }
            
            
            
            shipPlacementComputer(shipCom,shipDefCom,guiComPtr);
            //shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
            boardGui(guiComPtr);
            boardGui(guiPlayer1Ptr);

            printf("\nDone PLacing %s Ship",player1Name);
            printf("\n%s is Shooting First\n\n",player1Name);
            drawGui(guiPlayer1Ptr);
            printf("LEVEL 1\n");
            while (comScore[0] != 30 && playerScore[0] != 30)
            {
                shootShip(guiComPtr,shipCom,playerScore);
                printf("\nPlayer Score %d\n\n",playerScore[0]);
                if (comScore[0] == 30 && playerScore[0] < 30)
                {   
                    printf("\nOpps! Computer Won The Game\n\n");
                    break;
                }
                
                comShootShip(guiPlayer1Ptr,shipPlayer1,comScore);
                printf("\nComScore %d\n\n",comScore[0]);
                printf("\n");
                drawGui(guiComPtr);
                if (playerScore[0] == 30 && comScore[0] < 30)
                {
                    printf("\nCongo!! %s Won The Game :D\n",player1Name);
                    break;
                }        
            }   


        }else if (levelSelection == 'h' ||levelSelection == 'H')
        {

            printf("\nWould You Like to Plcae ship Randomly or do you want to place it your self ?\nTo place randomly enter 1 \nTo PLace it your self enter 2\n");
            scanf("%d",&inputHandler);
            if (inputHandler <= 1)
            {
                shipPlacementComputer(shipPlayer1,shipDefPlayer1,guiPlayer1Ptr);
            }
            if (inputHandler >= 2)
            {
                shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
            }

            shipPlacementComputer(shipCom,shipDefCom,guiComPtr);
            //shipPlacementComputer(shipPlayer1,shipDefPlayer1,guiPlayer1Ptr);
            //shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
            boardGui(guiComPtr);
            boardGui(guiPlayer1Ptr);

            printf("\nDone PLacing %s Ship",player1Name);
            printf("\n%s is Shooting First\n\n",player1Name);
            drawGui(guiPlayer1Ptr);

            printf("LEVEL 2\n");

            while (comScore[0] != 30 && playerScore[0] != 30)
            {
                shootShip(guiComPtr,shipCom,playerScore);
                printf("\nPlayer Score %d\n\n",playerScore[0]);
                if (comScore[0] == 30 && playerScore[0] < 30)
                {
                    printf("\nOpps! Computer Won The Game\n\n");
                    break;
                }
                
                comShootShip_Lvl2(guiPlayer1Ptr,shipPlayer1,comScore);
                printf("\nComScore %d\n\n",comScore[0]);
                printf("\n");
                drawGui(guiComPtr);
                if (playerScore[0] == 30 && comScore[0] < 30)
                {
                    printf("\nCongo!! %s Won The Game :D\n",player1Name);
                    break;
                }        
            }
            if (playerScore[0] == 30 && comScore[0] < 30)
            {
                printf("\nCongo!! %s Won The Game :D",player1Name);
            }   
            if (comScore[0] == 30 && playerScore[0] < 30)
            {
                printf("\nOpps! Computer Won The Game\n\n");
            }
        }
        else{
            printf("Wrong Input :(");
            main();
        }
        
        
    }
    else if (modeSelection == 2)
    {
        printf("\nEnter Player 1 Name:  ");
        scanf("%s",player1Name);
        printf("\nEnter Player 2 Name:  ");
        scanf("%s",player2Name);

        printf("\n**********%s Will Place Ship First**********\n",player2Name);
        shipPlacement(shipPlayer2,guiPlayer2Ptr,shipDefPlayer2);
        printf("\n*************%s Will Place Ship Now*********\n",player1Name);    
        shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
        //shipPlacement(shipPlayer1,guiPlayer1Ptr,shipDefPlayer1);
        boardGui(guiPlayer2Ptr);
        boardGui(guiPlayer1Ptr);


        printf("\n\n");
        drawGui(guiPlayer1Ptr);

        while (player2Score[0] != 30 && playerScore[0] != 30)
        {
            //shootShip
            printf("\n%s Will Shoot Now\n",player1Name);
            shootShip(guiPlayer2Ptr,shipPlayer2,playerScore);
            printf("\n%s Score %d\n\n",player1Name,playerScore[0]);
            printf("\n\n");
            //drawGui(guiPlayer2Ptr);
            if (playerScore[0] == 30 && player2Score[0] < 30)
            {
                printf("\nCongo ! %s Won The Game\n%s Better Luck Next tine\n",player1Name,player2Name);
                break;
            }

            //shootShip
            printf("\n%s Will Shoot Now\n",player2Name);
            shootShip(guiPlayer1Ptr,shipPlayer1,player2Score);
            printf("\n%s %d\n\n",player2Name,player2Score[0]);
            printf("\n\n");
            //drawGui(guiPlayer1Ptr);
            if (player2Score[0] == 30 && playerScore[0] < 30)
            {
                printf("\nCongo ! %s Won The Game\n%s Better Luck Next tine\n",player2Name,player1Name);
                break;
            }        
        }

    }
    else if (modeSelection == 3)
    {
        printf("\n***********************RULES************************************\n");
        printf("\nTotal: 10 Ships -----\n************ 4 ships over 2 boxes **************\n************* 3 ships over 3 boxes **************\n******************* 2 ships over 4 boxes**********\n***************** 1 ship over 5 boxes ************\n");
        printf("***************Must remain in a line (not around a corner) At least one box must remain between the ships***************\n");
        printf("If a player has hit a piece of a ship, he may guess again. As soon as all pieces of a ship have been found, one says 'sunk'.\n");
        printf("The game continues until one of the two players has found or 'sunk' all of his opponent's ships\n\n");
        //printf("\nTo play with computer enter 1 to play with player enter 2 To know the Rules Enter 3\n");
        //scanf("%d",&modeSelection);
        main();
    }
    else{
        printf("Wrong Value Try Again Code..... :(");
        main();
    }
    
    
    return 0;
}