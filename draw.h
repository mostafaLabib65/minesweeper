#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
extern int Replay,flagcounter,LoseCheck,Moves,remember,Flags,threadpause;
extern double score ;
extern long long starttime,savetime,timer,counter,minutes;
extern COORD coord;
//Original Grid values : 0 ==> Empty , From 1 to 8 ==> number of mines beside , 9 ==> Mine .
//Playing Grid values : -1 ==> Empty cell Opened , -2 ==> a cell with a Number opened , -3 ==> Flagged cell.
// , -4 ==> a cell with ? , -5 ==> Opened Mine .
void draw1(int a,int b)
{
    //draw the starting Grid borders and style .
    textcolor(8);
    printf("\n\n\t\t\t\t\t\t\t\tMoves: %d\t Flags: %d\t Question mark: %d\t Time: \n\n",Moves,Flags,remember);
    for(int i = 0; i < b; i++)
    {
        if(i == 0)
        {
            printf("\t\t\t\t\t\t\t\t\t\t     %2d",i);
        }
        else
        {
            printf("    %2d",i);
        }
    }
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    for(int i = 0; i < b*6+2; i++)
    {
        if(i < 4)
        {
            printf(" ");
        }
        else
        {
            printf("-");
        }
    }
    printf("\n");
    for(int i = 0; i < a; i++)
    {
        for(int j = 0; j < b; j++)
        {
            if(j == 0)
            {
                printf("\t\t\t\t\t\t\t\t\t\t%2d |  X  |",i);
            }
            else
            {
                printf("  X  |");
            }
        }
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        for(int g = 0; g < b*6+2; g++)
        {
            if(g < 4)
            {
                printf(" ");
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n\t\t\t\t\t\t\t\tF: Flag , U: Unflag , O: Open , N: ? , P:Parameter  ,  S:  Save\n");
}
//--------------------------------------------------------------------------------------------------------------------------------
void draw2(int rows,int colums,int OriginalGrid[rows][colums],int PlayingGrid[rows][colums])
{
    //draw the current playing game .
    threadpause = 1; //pause the time .
    int mine = 1 + ((rows*colums)/10); //Mines number .
    Flags = mine - flagcounter;
    textcolor(10);
    printf("\n\n\t\t\t\t\t\t\t\tMoves: %d\t Flags: %d\t Question mark: %d\t Time: \n\n",Moves,Flags,remember);
    for(int i = 0; i < colums; i++)
    {
        if(i == 0)
        {
            printf("\t\t\t\t\t\t\t\t\t\t     %2d",i);
        }
        else
        {
            printf("    %2d",i);
        }
    }
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    for(int i = 0; i < colums*6+2; i++)
    {
        if(i < 4)
        {
            printf(" ");
        }
        else
        {
            textcolor(10);
            printf("-");
            textcolor(15);
        }
    }
    printf("\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < colums; j++)
        {
            if(j == 0)
            {

                printf("\t\t\t\t\t\t\t\t\t\t%2d ",i);
                textcolor(10);
                printf("|");
                textcolor(15);
                if(PlayingGrid[i][j] > -1)
                {
                    printf("  X  ");
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
                else if(PlayingGrid[i][j] == -1)
                {
                    textbackground(15);
                    printf("     ");
                    textbackground(0);
                    textcolor(10);
                    printf("|");
                    textcolor(15);

                }
                else if(PlayingGrid[i][j] == -2)
                {
                    textcolor(14);
                    printf("  %d  ",OriginalGrid[i][j]);
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
                else if(PlayingGrid[i][j] == -3)
                {
                    textcolor(9);
                    printf("  F  ");
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
                else if (PlayingGrid[i][j] == -4)
                {
                    textcolor(9);
                    printf("  ?  ");
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
                else if (PlayingGrid[i][j] == -5)
                {
                    textcolor(9);
                    printf("  !  ");
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
            }
            else
            {
                if(PlayingGrid[i][j]> -1)
                {
                    printf("  X  ");
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
                else if(PlayingGrid[i][j] == -1)
                {
                    textbackground(15);
                    printf("     ");
                    textbackground(0);
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
                else if(PlayingGrid[i][j] == -2)
                {
                    textcolor(14);
                    printf("  %d  ",OriginalGrid[i][j]);
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
                else if(PlayingGrid[i][j] == -3)
                {
                    textcolor(9);
                    printf("  F  ");
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
                else if(PlayingGrid[i][j] == -4)
                {
                    textcolor(9);
                    printf("  ?  ");
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
                else if (PlayingGrid[i][j] == -5)
                {
                    textcolor(9);
                    printf("  !  ");
                    textcolor(10);
                    printf("|");
                    textcolor(15);
                }
            }
        }
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        for(int d = 0; d < colums*6+2; d++)
        {
            if(d < 4)
            {
                printf(" ");
            }
            else
            {
                textcolor(10);
                printf("-");
                textcolor(15);
            }
        }
        printf("\n");
    }
    textcolor (10);
    printf("\n\t\t\t\t\t\t\t\tF: Flag , U: Unflag , O: Open , N: ? , P:Parameter  ,  S:  Save\n");
    FILE *Currentgame ;
    Currentgame = fopen("CurrentGame.txt","w");
    for ( int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < colums ; j++)
        {
            fprintf(Currentgame,"%2i ",OriginalGrid[i][j]);
        }
        fprintf(Currentgame,"\n");
    }
    fprintf(Currentgame,"\n");
    for ( int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < colums ; j++)
        {
            fprintf(Currentgame,"%2i ",PlayingGrid[i][j]);
        }
        fprintf(Currentgame,"\n");
    }
    fclose(Currentgame);
    textcolor(7);

    threadpause = 0;//Resume the time .
}
//-------------------------------------------------------------------------------------------------------------------------------
void drawlose(int rows,int colums, int OriginalGrid[rows][colums],int PlayingGrid[rows][colums])
{
    //draw the loosing Grid .
    int mine = 1 + ((rows*colums)/10) ;
    textcolor(14);
    printf("\n\n\t\t\t\t\t\t\t\tMoves: %d\t Flags: %d\t Question mark: %d\t Time: \n\n",Moves,mine -flagcounter,remember);
    for(int i = 0; i < colums; i++)
    {
        if(i == 0)
        {
            printf("\t\t\t\t\t\t\t\t\t     %2d",i);
        }
        else
        {
            printf("    %2d",i);
        }
    }
    printf("\n\t\t\t\t\t\t\t\t\t");
    for(int i = 0; i < colums*6+2; i++)
    {
        if(i < 4)
        {
            printf(" ");
        }
        else
        {
            printf("-");
        }
    }
    printf("\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < colums; j++)
        {
            if(j == 0)
            {
                printf("\t\t\t\t\t\t\t\t\t%2d |",i);
                if(OriginalGrid[i][j] == 0 && PlayingGrid[i][j] != -3)
                {
                    printf("     |");
                }
                else if(OriginalGrid[i][j] > 0 && OriginalGrid[i][j] < 9 && PlayingGrid[i][j] != -3)
                {
                    printf("  %d  |",OriginalGrid[i][j]);
                }
                else if (OriginalGrid[i][j] >=0 && OriginalGrid[i][j] < 9 && PlayingGrid[i][j] == -3)
                {
                    printf("  -  |");
                }
                else if (OriginalGrid[i][j] == 9 && PlayingGrid[i][j] == -3)
                {
                    printf("  *  |");
                }
                else if (OriginalGrid[i][j] == 9 && PlayingGrid[i][j] == -5)
                {
                    textcolor(12);
                    printf("  !  ");
                    textcolor(14);
                    printf("|");
                }
                else if (OriginalGrid[i][j] == 9 && PlayingGrid[i][j] != -5 && OriginalGrid[i][j] != -3)
                {
                    printf("  M  |");
                }
            }

            else
            {

                if(OriginalGrid[i][j] == 0 && PlayingGrid[i][j] != -3)
                {
                    printf("     |");
                }
                else if(OriginalGrid[i][j] > 0 && OriginalGrid[i][j] < 9 && PlayingGrid[i][j] != -3)
                {
                    printf("  %d  |",OriginalGrid[i][j]);
                }
                else if (OriginalGrid[i][j] >=0 && OriginalGrid[i][j] < 9 && PlayingGrid[i][j] == -3)
                {
                    printf("  -  |");
                }
                else if (OriginalGrid[i][j] == 9 && PlayingGrid[i][j] == -3)
                {
                    printf("  *  |");
                }
                else if (OriginalGrid[i][j] == 9 && PlayingGrid[i][j] == -5)
                {
                    textcolor(12);
                    printf("  !  ");
                    textcolor(14);
                    printf("|");
                }
                else if (OriginalGrid[i][j] == 9 && PlayingGrid[i][j] != -5 && OriginalGrid[i][j] != -3)
                {
                    printf("  M  |");
                }
            }
        }
        printf("\n\t\t\t\t\t\t\t\t\t");
        for(int d = 0; d < colums*6+2; d++)
        {
            if(d < 4)
            {
                printf(" ");
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n\n\t\t\t\t\t\t\t\tOps you Missed . Better luck next time\n\t\t\t\t\t\t\t\t To try again Press T\n\t\t\t\t\t\t\t\t Press any key to exit\n");

    char c;//choose if the user wants to play again .
    scanf("%c",&c);
    if (c >96 && c < 123)
    {
        c = c - 32 ;
    }

    if (c == 'T')
    {
        Replay = 0 ;
    }
    textcolor(7);
}
//------------------------------------------------------------------------------------------------------------------------------
void drawwin(int rows,int colums, int OriginalGrid[rows][colums],int PlayingGrid[rows][colums])
{
    //Draw the winning Grid /
    int mine = 1 + ((rows*colums)/10) ;
    textcolor(10);
    printf("\n\n\t\t\t\t\t\t\t\tMoves: %d\t Flags: %d\t Question mark: %d\t Time: \n\n",Moves,mine -flagcounter,remember);
    for(int i = 0; i < colums; i++)
    {
        if(i == 0)
        {
            printf("\t\t\t\t\t\t\t\t\t    %2d",i);
        }
        else
        {
            printf("   %2d",i);
        }
    }
    printf("\n\t\t\t\t\t\t\t\t\t");
    for(int i = 0; i < colums*6+2; i++)
    {
        if(i < 4)
        {
            printf(" ");
        }
        else
        {
            printf("-");
        }
    }
    printf("\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < colums; j++)
        {
            if(j == 0)
            {
                printf("\t\t\t\t\t\t\t\t\t %d  |",i);
                if(OriginalGrid[i][j] == 0 )
                {
                    printf("     |");
                }
                else if(OriginalGrid[i][j] > 0 && OriginalGrid[i][j] < 9)
                {
                    printf("  %d  |",OriginalGrid[i][j]);
                }
                else if (OriginalGrid[i][j] == 9 )
                {
                    printf("  *  |");
                }
            }

            else
            {

                if(OriginalGrid[i][j] == 0 )
                {
                    printf("     |");
                }
                else if(OriginalGrid[i][j] > 0 && OriginalGrid[i][j] < 9 )
                {
                    printf("  %d  |",OriginalGrid[i][j]);
                }
                else if (OriginalGrid[i][j] == 9 )
                {
                    printf("  *  |");
                }
            }
        }
        printf("\n\t\t\t\t\t\t\t\t\t");
        for(int d = 0; d < colums*6+2; d++)
        {
            if(d < 4)
            {
                printf(" ");
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
    }
    score =(pow(rows,4)*pow(colums,4))/(Moves*(timer + minutes*60));//calculate the score .
    printf("\n\t\t\t\t\t\t\t\tCongratulation ,you won\n\t\t\t\t\t\t\t\t Your score is %.2f \n\t\t\t\t\t\t\t\t please enter your name to save the score\n",score);
    int d;
    char *name1[100];
    do
    {
        printf("\t\t\t\t\t\t\t\tEnter name please: \n\t\t\t\t\t\t\t\t");
        d = getName(name1,100);
    }
    while(d != 0);
    savescore(name1,score);
    //get the score and add it to the list .
    printf("\t\t\t\t\t\t\t\tWould you like to play again(Y/N)\n\t\t\t\t\t\t\t\t");
    //ask the user to play again .
    char c;
    scanf("%c",&c);
    if (c >96 && c < 123)
    {
        c = c - 32 ;
    }

    if (c == 'Y')
    {
        Replay = 0 ;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------
void clear(void)
{
    system("cls");
}

void gotxy(int x,int y)//a function to print the time and return the cursor to it's place again .
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
#endif // DRAW_H_INCLUDED
