#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include "draw.h"
#include "GetInfo.h"
#include "initialization.h"
int great(void); // main menu
int loadlist(); //Get informations from the files

//Taking actions and playing the game
void play(int rows,int colums,int OriginalGrid[rows][colums],int PlayingGrid[rows][colums]);
//check if the user wins
void win();
//save the Grid
void save(int raws,int colums,int OriginalGrid[raws][colums],int PlayingGrid[raws][colums]);
//game time
void *thread(void *x);
//Starting and preparing the game
void playgame();
//hight scores
void savescore(char names[100],double score);

int Replay = 0,flagcounter,LoseCheck = 1,Moves,remember,Flags,Savecheck = 0,StoppingTime = 0,threadpause = 0;
double score ;
long long timer = 0,minutes = 0;
//thread initialization
pthread_t thread0;
//scores struct
struct score
{
    double score ;
    char *name[100];
};
struct score scores[100];
//score swapping for sorting
void swapping(int first,int second,struct score[100]);
//coordinates
COORD coord= {0,0};
int main()
{
    playgame();

}

int great(void)
{
    char x[100];
    int i = 0;
    clear();
    textcolor(12);
    usleep(60000*16+6000*6);
    printf(" \t\t\t\t\t\t      .----------------.  .----------------.  .-----------------. .----------------.\n\
\t\t\t\t\t\t     | .--------------. || .--------------. || .--------------. || .--------------. |\n\
\t\t\t\t\t\t     | | ____    ____ | || |     _____    | || | ____  _____  | || |  _________   | |\n\
\t\t\t\t\t\t     | ||_   \\  /   _|| || |    |_   _|   | || ||_   \\|_   _| | || | |_   ___  |  | |\n\
\t\t\t\t\t\t     | |  |   \\/   |  | || |      | |     | || |  |   \\ | |   | || |   | |_  \\_|  | |\n\
\t\t\t\t\t\t     | |  | |\\  /| |  | || |      | |     | || |  | |\\ \\| |   | || |   |  _|  _   | |\n\
\t\t\t\t\t\t     | | _| |_\\/_| |_ | || |     _| |_    | || | _| |_\\   |_  | || |  _| |___/ |  | |\n\
\t\t\t\t\t\t     | ||_____||_____|| || |    |_____|   | || ||_____|\\____| | || | |_________|  | |\n\
\t\t\t\t\t\t     | |              | || |              | || |              | || |              | |\n\
\t\t\t\t\t\t     | '--------------' || '--------------' || '--------------' || '--------------' |\n\
\t\t\t\t\t\t      '----------------'  '----------------'  '----------------'  '----------------'\n");
    usleep(60000*16+6000*6);
    printf("\t\t\t .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.\n\
\t\t\t| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n\
\t\t\t| |    _______   | || | _____  _____ | || |  _________   | || |  _________   | || |   ______     | || |  _________   | || |  _______     | |\n\
\t\t\t| |   /  ___  |  | || ||_   _||_   _|| || | |_   ___  |  | || | |_   ___  |  | || |  |_   __ \\   | || | |_   ___  |  | || | |_   __ \\    | |\n\
\t\t\t| |  |  (__ \\_|  | || |  | | /\\ | |  | || |   | |_  \\_|  | || |   | |_  \\_|  | || |    | |__) |  | || |   | |_  \\_|  | || |   | |__) |   | |\n\
\t\t\t| |   '.___`-.   | || |  | |/\  \\| |  | || |   |  _|  _   | || |   |  _|  _   | || |    |  ___/\   | || |   |  _|  _   | || |   |  __ /\    | |\n\
\t\t\t| |  |`\\____) |  | || |  |   /\\   |  | || |  _| |___/\ |  | || |  _| |___/\ |  | || |   _| |_      | || |  _| |___/\ |  | || |  _| |  \\ \\_  | |\n\
\t\t\t| |  |_______.'  | || |  |__/\  \\__|  | || | |_________|  | || | |_________|  | || |  |_____|     | || | |_________|  | || | |____| |___| | |\n\
\t\t\t| |              | || |              | || |              | || |              | || |              | || |              | || |              | |\n\
\t\t\t| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n\
\t\t\t '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n \n \n");
    textcolor(10);
    usleep(60000*16+6000*6);
    printf("\t\t\t\t\t\t\t\t\t\t 1- Start New game.\n\n\t\t\t\t\t\t\t\t\t\t 2- Load game\n\n\t\t\t\t\t\t\t\t\t\t 3- High Scores.\n\n");
    printf("\t\t\t\t\t\t\t\t\t\t choose %d or %d or %d: ",1,2,3);
    textcolor(7);
    //get char and convert it to an int
    do
    {
        x[i] = getchar();
        if (x[0] != '\n')
        {
            i++;
        }
    }
    while ( x[i -1] != '\n');
    int n = atoi(x);
    if (n == 1 || n == 2 || n == 3 )
    {
        if (x[1] != '\n')
        {
            n = 0 ;
        }
    }
    return n;

}
void save(int raws,int colums,int OriginalGrid[raws][colums],int PlayingGrid[raws][colums])
{
    StoppingTime++; // stop game timing when the user is saving .
    int c,find_result = 0,check= 0;
    char name[100];
    FILE *loads2;
    if ((loads2 = fopen("load.txt", "r")) == NULL)
    {
        check++;
    }
    do
    {
        printf("\n\t\t\t\t\t\t\t\tEnter name please: \n\t\t\t\t\t\t\t\t");
        c = getName(name,100);
        if(check == 0)
        {
            char temp[100];
            while(fgets(temp, 100, loads2) != NULL)//the file exists .
            {
                strtok(temp,"\n");
                if(((strstr(temp, name)) != NULL) &&(strcmp(temp,name) == 0) )//compare the two names .
                {
                    find_result++;
                    break;
                }

                fflush(stdin);
            }

            if(find_result == 0)
            {
                printf("\t\t\t\t\t\t\t\t\t\tchoose another name\n");
            }
        }
    }
    while(c != 0 || find_result != 0); //c = 0 when the name is right.

    //create a list of names  and save the names in it.
    char *load1 = "loadList.txt";
    FILE *loads1 = fopen(load1,"a");
    int i = countlines(load1);
    fprintf(loads1,"\t\t\t\t\t\t\t\t\t\t%d- %s\n",i,name);
    fclose(loads1);
    //create a file and save the information of the grid in it .
    loads2 = fopen("load.txt","a");
    fprintf(loads2,"%s\n%d %d\n%d %d %d %lld\n",name,raws,colums,Moves-1,Flags,remember,timer);
    for (int i = 0; i < raws; i++)
    {
        for (int j = 0; j < colums; j++)
        {
            fprintf(loads2, "%i ", OriginalGrid[i][j]);
        }
        fprintf(loads2,"\n");
    }
    for (int i = 0; i < raws; i++)
    {
        for (int j = 0; j < colums; j++)
        {
            fprintf(loads2, "%i ", PlayingGrid[i][j]);
        }
        fprintf(loads2,"\n");
    }
    fclose(loads2);
    StoppingTime = 0; //Resume game time when the save is over.
    pthread_create(&thread0,NULL,thread,1);
}
int loadlist(char *filename)
{
    int checker = 0 ; // check if there is a file .
    FILE *load;
    if ((load = fopen(filename, "r")) == NULL)
    {
        textcolor(13);
        printf("\n\t\t\t\t\t\t\t\t\t\tThere is nothing to show");
        checker = 1 ; //no file found.
        return checker ;
        // Program exits if file pointer returns NULL.
    }
    // reads text until newline
    char c[10000];
    fscanf(load,"%[^\0]", c);
    clear();
    printf("\n\n\n\n\n\n");
    textcolor(14);
    printf("%s", c);
    fclose(load);
    StoppingTime = 0;//Resume time if paused .
    return checker ;
}

void play(int rows,int colums,int OriginalGrid[rows][colums],int PlayingGrid[rows][colums])
{
    //get number of row and column .
    int x1,y1;
    char action = '\0';
    textcolor(10);
    do
    {
        printf("\n\t\t\t\t\t\t\t\tEnter number of row: ");
        x1 = getint();
    }
    while(x1>rows-1||x1<0);
    do
    {
        printf("\n\t\t\t\t\t\t\t\tEnter number of colum: ");
        y1 = getint();
    }
    while(y1>colums-1||y1<0);
    //get action .
    while(action != 'F' && action != 'P' && action != 'O' && action != 'N' && action != 'U' && action != '?' && action != 'S')
    {
        printf("\n\t\t\t\t\t\t\t\tAction: ");
        action = getAction();//Get the Action in lower case .
        if (action >96 && action < 123)
        {
            action = action - 32 ;
        }
    }
    Moves++;
    if(action == 'O')
    {
        if(OriginalGrid[x1][y1] == 0)
        {
            if(PlayingGrid[x1][y1] == -1)
            {
                printf("\t\t\t\t\t\t\t\tIt's already opened\n press C to continue\n\t\t\t\t\t\t\t\t");
                char c ;
                int xc= wherex(xc);
                int yc = wherey(yc);
                do
                {
                    gotxy(xc-1,yc-1);
                    textbackground(0);
                    scanf("%c",&c);
                    printf("   ");
                    if (c >96 && c < 123)
                    {
                        c = c - 32 ;
                    }
                }
                while (c != 'C');

            }
            else
            {
                if (PlayingGrid[x1][y1] == -3)//if the cell is flagged .
                {
                    flagcounter -- ;
                }
                DFS(x1,y1,rows,colums,PlayingGrid,OriginalGrid);
            }
        }
        else if(OriginalGrid[x1][y1] != 0 &&OriginalGrid[x1][y1] != 9)
        {
            if(PlayingGrid[x1][y1] == -2)
            {
                Moves--;
                printf("\t\t\t\t\t\t\t\tIt's already opened\n\t\t\t\t\t\t\t\t press C to continue\n\t\t\t\t\t\t\t\t");
                char c ;
                int xc= wherex(xc);
                int yc = wherey(yc);
                do
                {
                    gotxy(xc-1,yc-1);
                    textbackground(0);
                    scanf("%c",&c);
                    printf("   ");
                    if (c >96 && c < 123)
                    {
                        c = c - 32 ;
                    }
                }
                while (c != 'C');
            }
            else
            {
                if (PlayingGrid[x1][y1] == -3)
                {
                    flagcounter -- ;
                }
                PlayingGrid[x1][y1] = -2;

            }
        }
        else if(OriginalGrid[x1][y1] == 9)//The user hit a mine
        {
            PlayingGrid[x1][y1] = -5 ;
            LoseCheck = 0 ;
        }

    }
    else if(action == 'N')
    {
        if(PlayingGrid[x1][y1] == -4)
        {
            PlayingGrid[x1][y1] = OriginalGrid[x1][y1];
            remember--;// ?? counter
        }
        else
        {
            PlayingGrid[x1][y1] = -4;
            remember++;
        }
    }
    else if(action == 'F')
    {
        if (flagcounter < (1 + ((rows*colums)/10)))//Flags max number
        {
            if (PlayingGrid[x1][y1] == -1 || PlayingGrid[x1][y1] == -2)
            {
                Moves--;
                char c = '\n' ;
                printf("\t\t\t\t\t\t\t\tOpened cell can't be flagged\n\t\t\t\t\t\t\t\t press C to continue\n\t\t\t\t\t\t\t\t");
                int xc= wherex(xc);
                int yc = wherey(yc);
                do
                {
                    gotxy(xc-1,yc-1);
                    textbackground(0);
                    scanf("%c",&c);
                    printf("   ");
                    if (c >96 && c < 123)
                    {
                        c = c - 32 ;
                    }
                }
                while (c != 'C');
            }
            else if (PlayingGrid[x1][y1] == -3)
            {
                Moves--;
                printf("\n\t\t\t\t\t\t\t\tIt's already flagged\n\t\t\t\t\t\t\t\t press C to continue\n\t\t\t\t\t\t\t\t");
                char c;
                int xc= wherex(xc);
                int yc = wherey(yc);
                do
                {
                    gotxy(xc-1,yc-1);
                    textbackground(0);
                    scanf("%c",&c);
                    printf("   ");
                    if (c >96 && c < 123)
                    {
                        c = c - 32 ;
                    }
                }
                while (c != 'C');
            }
            else
            {
                PlayingGrid[x1][y1] = -3;
                flagcounter++;
            }
        }
        else
        {
            Moves--;
            char c;
            printf("\t\t\t\t\t\t\t\tFlag reached the maximum number\n\t\t\t\t\t\t\t\t Please remove a flag to put another\n\t\t\t\t\t\t\t\t Press C to continue");
            int xc= wherex(xc);
            int yc = wherey(yc);
            do
            {
                gotxy(xc-1,yc-1);
                textbackground(0);
                scanf("%c",&c);
                printf("   ");
                if (c >96 && c < 123)
                {
                    c = c - 32 ;
                }
            }
            while (c != 'C');
        }
    }
    else if (action == 'U')
    {
        if(PlayingGrid[x1][y1] == -3)
        {
            PlayingGrid[x1][y1] = OriginalGrid[x1][y1];
            flagcounter--;
        }
    }
    else if (action == '?')
    {
        if (PlayingGrid[x1][y1] != -1 && PlayingGrid[x1][y1] != -2 && PlayingGrid[x1][y1] != -3 )
        {
            PlayingGrid[x1][y1] = -6 ;
        }
    }
    else if (action == 'P')//Open the Parameter
    {
        if (PlayingGrid[x1][y1] == -2)//if Flags = the number in cell .
        {
            int counter = 0;
            for(int p = x1-1; p <=x1+1; p++)
            {
                for(int i = y1-1; i <=y1+1; i++)
                {
                    if(p<0||p >=rows||i<0||i>=colums||(p == x1&& i == y1))
                    {
                        continue;
                    }
                    else
                    {
                        if(PlayingGrid[p][i] == -3)
                        {
                            counter++;
                        }
                    }
                }
            }
            if (counter == OriginalGrid[x1][y1])
            {
                for(int p = x1-1; p <=x1+1; p++)
                {
                    for(int i = y1-1; i <=y1+1; i++)
                    {
                        if(p<0||p >=rows||i<0||i>=colums||(p == x1&& i == y1))
                        {
                            continue;
                        }
                        else
                        {
                            if(PlayingGrid[p][i] != -1 && PlayingGrid[p][i] != -2 && PlayingGrid[p][i] != -3 )
                            {
                                if (OriginalGrid[p][i] == 0)
                                {
                                    DFS(p,i,rows,colums,PlayingGrid,OriginalGrid);
                                }
                                else if (OriginalGrid[p][i] > 0 && OriginalGrid[p][i] < 9)
                                {
                                    PlayingGrid[p][i] = -2;
                                }
                                else if (OriginalGrid[p][i] == 9)
                                {
                                    PlayingGrid[p][i] = -5 ;
                                    LoseCheck = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else if(action == 'S')//Saving
    {
        save(rows,colums,OriginalGrid,PlayingGrid);
        Savecheck++;
    }
}

void win(int rows,int colums, int OriginalGrid[rows][colums],int PlayingGrid[rows][colums])
{
    //check if every Mine is flagged and every other cells is opened.
    int flag1 = 2 ;//If any thing wrong change the value .
    for (int i = 0 ; i < rows; i++)
    {
        for (int j = 0 ; j < colums; j++)
        {
            if (OriginalGrid[i][j] == 0 && PlayingGrid[i][j] != -1)
            {
                flag1 = 1 ;
            }
            if (OriginalGrid[i][j] > 0 && OriginalGrid[i][j] < 9 && PlayingGrid[i][j] != -2)
            {
                flag1 = 1 ;
            }
        }
    }
    LoseCheck = flag1 ;
}

void *thread(void *x)
{
    //time printing second by second .
    int xp,yp;
    while (1)
    {
        usleep(60000*16+6000*5);
        timer++;
        xp = wherex(xp);
        yp = wherey(yp);
        if(timer == 60)
        {
            minutes++;
            timer = 0;
        }
        if(threadpause == 0)
        {
            gotxy(128,2);
            textcolor(10);
            printf("%lld m %lld  s",minutes,timer);
            textbackground(0);
            printf("             ");
            gotxy(xp-1,yp-1);
        }
        if(StoppingTime != 0)
        {
            textbackground(0);
            printf("             ");
            gotxy(xp,yp);
            StoppingTime = 0;
            break;
        }
    }
}
void load()
{
    //open file and read informations .
    FILE* load;
    load = fopen("load.txt", "r");
    char name[100];
    int i;
    int find_result;

    int line_num;
    do
    {
        fseek(load, 0, SEEK_SET);//Get the cursor at the begging of the line .
        do
        {
            printf("\n\t\t\t\t\t\t\t\t\t\tEnter name: ");
            i = getName(name,100);
        }
        while(i != 0);
        line_num = 1;
        find_result = 0;
        char temp[100];
        while(fgets(temp, 100, load) != NULL)//the file exists .
        {
            strtok(temp,"\n");
            if(((strstr(temp, name)) != NULL) &&(strcmp(temp,name) == 0) )//compare the two names .
            {
                find_result++;
                break;
            }
            line_num++;
            fflush(stdin);
        }
        if(find_result == 0)
        {
            printf("\t\t\t\t\t\t\t\t\t\tno save with that name");
        }
    }
    while(find_result != 1);

    fclose(load);
    //open the file and read the grids
    load = fopen("load.txt", "r");
    int ch, newlines = 0;
    while ((ch = getc(load)) != EOF)
    {
        if (ch == '\n')
        {
            newlines++;
            if (newlines == line_num)
                break;
        }
    }
    int raws,colums;
    fscanf(load,"%d %d %d %d %d %d",&raws,&colums,&Moves,&Flags,&remember,&timer);
    int OriginalGrid[raws][colums];
    int PlayingGrid[raws][colums];
    for(int i = 0; i < raws; i++)
    {
        for(int j = 0; j < colums; j++)
        {
            fscanf(load,"%d",&OriginalGrid[i][j]);
        }
    }
    for(int i = 0; i < raws; i++)
    {
        for(int j = 0; j < colums; j++)
        {
            fscanf(load,"%d",&PlayingGrid[i][j]);
        }
    }
    clear();
    StoppingTime = 0;
    pthread_create(&thread0,NULL,thread,1);
    draw2(raws,colums,OriginalGrid,PlayingGrid);//print the Playing grid .
    while(LoseCheck == 1)
    {
        //continue playing a saved game .
        play(raws,colums,OriginalGrid,PlayingGrid);
        if(Savecheck != 0)
        {
            Moves = Moves - 1;
            Savecheck = 0 ;
        }
        clear();
        if (LoseCheck == 0 )
        {
            break;
        }
        win(raws,colums,OriginalGrid,PlayingGrid);
        draw2(raws,colums,OriginalGrid,PlayingGrid);
    }
    if (LoseCheck == 0)
    {
        StoppingTime++;
        drawlose(raws,colums,OriginalGrid,PlayingGrid);
    }
    else if (LoseCheck == 2)
    {
        StoppingTime++;
        clear();
        drawwin(raws,colums,OriginalGrid,PlayingGrid);
    }
}
void playgame()
{
    int choose; // choose from the main menu .
    do
    {
        choose = great();
    }
    while(choose != 1 && choose != 2 && choose != 3);
        if(choose == 1)
        {
            timer = 0;
            flagcounter =0;
            Moves = 1;
            remember = 0;
            LoseCheck = 1 ;
            Replay = 1;
            clear();
            int x,y;
            textcolor(10);
            //get the grid dimensional .
            printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter the width : ");
            x = getint();
            while(!(x>=2 && x <= 100))
            {
                printf("\t\t\t\t\t\tThe width must be between 2 & 100 :");
                x = getint();
            }
            printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter the height : ");
            y = getint();
            while(!(y>=2 && y <= 100))
            {
                printf("\t\t\t\t\t\tThe height must be between 2 & 100 :");
                y = getint();
            }
            textcolor(7);
            clear();
            int Grid[x][y],PGrid[x][y];
            draw1(x,y);
            int x1 =0,y1 = 0;
            //get the starting position .
            do
            {
                printf("\n\t\t\t\t\t\t\t\tEnter number of raw: ");
                x1 = getint();
            }
            while(x1>x-1||x1<0);
            do
            {
                printf("\n\t\t\t\t\t\t\t\tEnter number of colum: ");
                y1=getint();
            }
            while(y1>y-1||y1<0);
            clear();
            init(x1,y1,x,y,Grid,PGrid);//put the mines and numbers .
            pthread_create(&thread0,NULL,thread,1);//start the time .
            DFS(x1,y1,x,y,PGrid,Grid); // open parameter .
            draw2(x,y,Grid,PGrid);//print the playing grid .
            while(LoseCheck == 1)//not lose yet .
            {
                play(x,y,Grid,PGrid);
                if(Savecheck != 0)
                {
                    Moves = Moves - 1;
                    Savecheck = 0 ;
                }
                clear();
                if (LoseCheck == 0 )
                {
                    break;
                }
                win(x,y,Grid,PGrid);
                draw2(x,y,Grid,PGrid);
            }
            if (LoseCheck == 0)//If lose .
            {
                StoppingTime = 1;
                drawlose(x,y,Grid,PGrid);
                StoppingTime = 0;
            }
            else if (LoseCheck == 2)//If win .
            {
                StoppingTime = 1;
                clear();
                drawwin(x,y,Grid,PGrid);
                StoppingTime = 0;
            }
            if (Replay == 0)
            {
                playgame();
            }
        }
    if(choose == 2)//Load .
    {
        char *s = "loadList.txt";
        int checker = loadlist(s);
        if (checker != 0 )//there is not load list .
        {
            printf("\n\n\t\t\t\t\t\t\t\t\t\tpress any key to continue : ");
            char v ;
            scanf("%c",&v);
            playgame();
        }
        load(s);//load .
    }
    if(choose == 3)//show scores .
    {
        char *s = "scores.txt";
        int checker = loadlist(s);
        if (checker != 0)
        {
            printf("\n\n\t\t\t\t\t\t\t\t\t\tpress any key to continue : ");
            char v;
            scanf("%c",&v);
            playgame();
        }
        loadlist(s);
        printf("\n\n\t\t\t\t\t\t\t\t\t\tpress any key to go back : ");

        char v;
        scanf("%c",&v);
        playgame();
    }
}
void savescore(char names[100],double score)
{
    //open a file and write the score in it .
    FILE *scorelist ;
    if ((scorelist = fopen("scores.txt", "r")) == NULL)//if it is the first score .
    {
        scorelist =fopen("scores.txt","w");
        fprintf(scorelist,"\t\t\t\t\t\t\t\t\t\t%-30s %.2f",names,score);
        fclose(scorelist);
    }
    else
    {
        //if it is not the first score get the previous scores in array of structs and sort it .
        int i ;
        scorelist = fopen("scores.txt","r");
        int lines = countlines("scores.txt");
        for ( i = 0 ; i < lines ; i ++)
        {
            fscanf(scorelist,"%s",&scores[i].name);
            fscanf(scorelist,"%lf",&scores[i].score);
        }
        fclose(scorelist);
        int found = 0 ;
        for (int j = 0 ; j < i ; j++)//Sorting the list .
        {
            if  (strstr(scores[j].name,names) !=NULL )//if the name already exists .
            {
                if (strcmp(scores[j].name,names) == 0)
                {
                    found = 1 ;
                    lines -- ;//the file size won't change .
                    if ((score > scores[j].score))//compare the old and the new score .
                    {
                        scores[j].score = score ;
                        while ((scores[j].score > scores[j-1].score) && (j > 0 ))
                        {
                            swapping(j,j-1,scores);
                            j-- ;
                        }
                    }
                    break ;
                }
            }
        }
        if (found == 0)//if the name is new .
        {
            strncpy(scores[i].name, names,100);//copy the name to the struct .
            scores[i].name[100] = '\0';
            scores[i].score = score ;
            while ((scores[i].score > scores[i-1].score) && (i > 0 ))//Sorting the array .
            {
                swapping(i,i-1,scores);
                i-- ;
            }
        }
        textcolor(12);
        printf("\n\t\t\t\t\t\t\t\t\t\t High score is %s %.2f \n\n",scores[0].name,scores[0].score);
        textcolor(10);
        scorelist = fopen("scores.txt","w");//saving the scores in the file .
        for (i = 0 ; i <= lines ; i++)
        {
            if (i == lines)
            {
                fprintf(scorelist,"\t\t\t\t\t\t\t\t\t\t%-30s %.2f",scores[i].name,scores[i].score);
            }
            else
            {
                fprintf(scorelist,"\t\t\t\t\t\t\t\t\t\t%-30s %.2f\n",scores[i].name,scores[i].score);
            }
        }
        fclose(scorelist);
    }
}
void swapping(int first,int second,struct score A[100])//Swapping two structures .
{
    struct score temp = A[first] ;
    A[first] = A[second];
    A[second] =temp ;

}

