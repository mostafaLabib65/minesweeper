#ifndef INITIALIZATION_H_INCLUDED
#define INITIALIZATION_H_INCLUDED
extern int flagcounter;

void init(int a,int b,int rows,int colums,int OriginalGrid[rows][colums],int PlayingGrid[rows][colums])
{
    //put the Mines and the numbers .
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < colums; j++)
        {
            OriginalGrid[i][j] = 0;
        }
    }
    int mines = 1 + ((rows*colums)/10);
    OriginalGrid[a][b] = -1;//the starting cell to prevent putting a mine .
    int k = 0,counter=0;
    do
    {

        int row = rnd(rows),colum = rnd(colums);//randomly put the mines .
        if((OriginalGrid[row][colum] != 9)&&OriginalGrid[row][colum] != -1)
        {
            k++;
            OriginalGrid[row][colum] = 9;
        }


    }
    while(k < mines);
    for(int i = 0; i < rows; i++)// Putting the numbers around the mines .
    {
        for(int j = 0; j < colums; j++)
        {
            if(OriginalGrid[i][j] != 9)
            {
                for(int p = i-1; p <=i+1; p++)
                {
                    for(int m = j-1; m <=j+1; m++)
                    {
                        if(p<0||p >=rows||m<0||m>=colums||(p == i&& m == j))
                        {
                            continue;
                        }
                        else
                        {
                            if(OriginalGrid[p][m] == 9)
                            {
                                counter++;
                            }
                        }
                    }
                }
                OriginalGrid[i][j] = counter;
                counter = 0;
            }
        }
    }
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < colums; j++)
        {
            PlayingGrid[i][j] = OriginalGrid[i][j];//copy the Grid to another one to play on it and compare the 2 Grids .
        }
    }
    if(OriginalGrid[a][b] != 0)
    {
        PlayingGrid[a][b] = -2;//if the first cell has a Number .
    }
}
//-------------------------------------------------------------------------------------------------------------------------------
int rnd(int x)//Generate a random numbers .
{
    srand(time(NULL)*rand()*1000);
    int r = ( rand() % (x-1) );
    return r;
}
//-------------------------------------------------------------------------------------------------------------------------------
void DFS(int i,int j,int rows,int colums,int PlayingGrid[rows][colums],int Originalgrid[rows][colums])
{//open the parameter around the cell .
    if(PlayingGrid[i][j] == 0 || ((PlayingGrid[i][j] == -3 || PlayingGrid[i][j] == -4)&&Originalgrid[i][j] == 0))
    {
        PlayingGrid[i][j] = -1;
        if(PlayingGrid[i][j] == -3&&(Originalgrid[i][j] >= 0 &&Originalgrid[i][j] < 9))
        {
            flagcounter--;
        }
        if((PlayingGrid[i-1][j-1] != 9) &&(i>0)&&(j>0))
        {
            if(PlayingGrid[i-1][j-1] != 0 && PlayingGrid[i-1][j-1] != 9 && PlayingGrid[i-1][j-1] != -2 && PlayingGrid[i-1][j-1] != -1)
            {
                PlayingGrid[i-1][j-1] = -2;
            }
            else
            {
                DFS(i-1,j-1,rows,colums,PlayingGrid,Originalgrid);
            }
        }
        if((PlayingGrid[i-1][j] != 9) && (i>0))
        {
            if(PlayingGrid[i-1][j] != 0 && PlayingGrid[i-1][j] != 9 && PlayingGrid[i-1][j] != -2 && PlayingGrid[i-1][j] != -1)
            {
                PlayingGrid[i-1][j] = -2;
            }
            else
            {
                DFS(i-1,j,rows,colums,PlayingGrid,Originalgrid);
            }
        }
        if((PlayingGrid[i-1][j+1] != 9)&&(i>0)&&(j<colums-1))
        {
            if(PlayingGrid[i-1][j+1] != 0 && PlayingGrid[i-1][j+1] != 9 && PlayingGrid[i-1][j+1] != -2 && PlayingGrid[i-1][j+1] != -1)
            {
                PlayingGrid[i-1][j+1] = -2;
            }
            else
            {
                DFS(i-1,j+1,rows,colums,PlayingGrid,Originalgrid);
            }
        }
        if((PlayingGrid[i][j-1]!= 9)&& (j > 0))
        {
            if( PlayingGrid[i][j-1] != 0 && PlayingGrid[i][j-1] != 9 && PlayingGrid[i][j-1] != -2 && PlayingGrid[i][j-1] != -1)
            {
                PlayingGrid[i][j-1] = -2;
            }
            else
            {
                DFS(i,j-1,rows,colums,PlayingGrid,Originalgrid);
            }
        }
        if((PlayingGrid[i][j+1]!= 9 )&& (j < colums-1))
        {
            if(PlayingGrid[i][j+1] != 0 && PlayingGrid[i][j+1] != 9 && PlayingGrid[i][j+1] != -2 && PlayingGrid[i][j+1] != -1)
            {
                PlayingGrid[i][j+1] = -2;
            }
            else
            {
                DFS(i,j+1,rows,colums,PlayingGrid,Originalgrid);
            }
        }
        if((PlayingGrid[i+1][j-1] != 9)&& (i < rows-1)&& (j > 0))
        {
            if( PlayingGrid[i+1][j-1] != 0 && PlayingGrid[i+1][j-1] != 9 && PlayingGrid[i+1][j-1] != -2 && PlayingGrid[i+1][j-1] != -1)
            {
                PlayingGrid[i+1][j-1] = -2;
            }
            else
            {
                DFS(i+1,j-1,rows,colums,PlayingGrid,Originalgrid);
            }
        }
        if((PlayingGrid[i+1][j] != 9)&& (i < rows-1))
        {
            if(PlayingGrid[i+1][j] != 0 && PlayingGrid[i+1][j] != 9 && PlayingGrid[i+1][j] != -2 && PlayingGrid[i+1][j] != -1)
            {
                PlayingGrid[i+1][j] = -2;
            }
            else
            {
                DFS(i+1,j,rows,colums,PlayingGrid,Originalgrid);
            }
        }
        if((PlayingGrid[i+1][j+1] != 9)&&(i < rows-1)&& (j < colums-1))
        {
            if(PlayingGrid[i+1][j+1] != 0 && PlayingGrid[i+1][j+1] != 9 && PlayingGrid[i+1][j+1] != -2 && PlayingGrid[i+1][j+1] != -1)
            {
                PlayingGrid[i+1][j+1] = -2;
            }
            else
            {
                DFS(i+1,j+1,rows,colums,PlayingGrid,Originalgrid);
            }
        }
    }
}

#endif // INITIALIZATION_H_INCLUDED
