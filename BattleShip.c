#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>

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

int checkCorners(int x,int s){
    int y = 0;
    y = x+s;
    if (y >= 10){
        return 0;
    }else return 1;
    
    //if the ship is placed at 4 courners of the board give error msg to the user and let him place the ship again
}
int checkAllot(int **ship_ptr,int x,int y,int s,int c){
    int tvalue,count,scount;
    scount =0;
    if (c == 1){
        tvalue = checkCorners(x,s);
        count = s;
        if (tvalue == 1)
        {
            for (int i = 0; i < count; i++)
            {
                if (ship_ptr[x+i][y] != 1)
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
            if (scount == s)
            {
                return 1;
            }else return 0;
                    
        }   
    }
    
}

int placingShip(int **shipp_ptr,char **guii_Ptr,int *shipp_def ,int n){
    int xpos,ypos,svalue,tvalue;
    char dir;
    struct BattleShipCo s;
    struct BattleShipCo e;
    
    // I need to do something to get it on repeat
    printf("enter co-ordinates(x,y) example A,4  where you want to place the ship **Remember there are no Do-Over**\n");
    scanf("%c,%d",&s.x,&s.y);
    for (int i = 0; i < 10; i++)
    {
        if (guii_Ptr[i][0]==toupper(s.x))
        {
            xpos=i;
        }
        if (guii_Ptr[0][i]==s.y)
        {
            ypos=i;
        }
        
    }
    svalue = shipp_def[n-1];
    printf("\nTo place ship vertically enter V to place it horizontally enter H");
    scanf("%c",&dir);
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
            }
        }else if(tvalue == 0){
            printf("\nAfter Placing the ship at your coridnate either ship goes beond board size or there is another ship parked at same posi :D");
        }// I need to run Repeat 1 again
        break;
    case 'h':
    case 'H':
        tvalue = checkAllot(shipp_ptr,xpos,ypos,svalue,2);
        if (tvalue == 1){
            for (int i = 0; i < svalue; i++)
            {
                shipp_ptr[xpos][ypos+i] = 1;
            }
        }else if(tvalue == 0){
            printf("\nAfter Placing the ship at your coridnate either ship goes beond board size or fit exactly at corner therefore reenter the coords :D");
        }// I need to Run Reapat 1 again        
        break;

    default:
        printf("You didn't enter correct value");
        break;
    }
}


void shipPlacementCom(int **ship_Ptr,char **gui_ptr,int *ship_def){
    int i,j;
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
                placingShip(ship_Ptr,gui_ptr,ship_def,type);
                des = des -1;
                count--;
            }else(printf("\n You have already place the Ship"));
            break;
        case 2:
            if (sub >0)
            {
                placingShip(ship_Ptr,gui_ptr,ship_def,type);
                sub=sub-1;
                count--;
            }else(printf("\n You have already place the Ship"));
            break;
        case 3:
            if (xyz >0)
            {
                placingShip(ship_Ptr,gui_ptr,ship_def,type);
                xyz=xyz-1;
                count--;
            }else(printf("\n You have already place the Ship"));
            break;
        case 4:
            if (abc >0)
            {
                placingShip(ship_Ptr,gui_ptr,ship_def,type);
                abc=abc-1;
                count--;
            }else(printf("\n You have already place the Ship"));
            break;
        
        default:
            printf("\n Please enter Default Value");
            break;
        }
    }
    
}


//void shipBattleCom(int **ship_Ptr,char **gui_Ptr)


int main(){
    char **guiPtr;
    int *ship;
    int **shipCom;
//    int **shipPlayer1; //for player1
//    int **shipPlayer2; //for player2
    int i,j;

    ship = (int*)malloc(5*sizeof(int));//ship pointer as we have 4 types of ship
    shipInit(ship);

    shipCom = (int**)malloc(10*sizeof(int*));// to know where computer has placed their ship
    for ( i = 0; i < 11; i++)
    {
        shipCom[i]=(int*)malloc(10*sizeof(int));
    }

    guiPtr = (char**)malloc((10)*sizeof(char*));// the gui board of our game
    for(i=0;i<11;i++){
        guiPtr[i]=(char*)malloc((10)*sizeof(char));
    }
    boardGui(guiPtr);
    shipPtrSet(shipCom);
    drawGui(guiPtr);
    shipPlacementCom(shipCom,guiPtr,ship);

    return 0;
}