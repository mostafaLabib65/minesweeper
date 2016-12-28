#ifndef GETINFO_H_INCLUDED
#define GETINFO_H_INCLUDED

int getint(void)//Get int number from the user .
{
    char *end;
    char buf[100];
    int n;
    fflush(stdin);
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return -2;
    buf[strlen(buf) - 1] = 0;

    n = strtol(buf, &end, 10);
    if(end != buf + strlen(buf)||buf[0] == '\0')
    {
        return -2;
    }
    else
    {
        return n;
    }
}
//-----------------------------------------------------------------------------------------------------------------------------
char getAction()//Get a single char from the user (Action) .
{
    char x[100];
    int i = 0,n;
    do
    {
        x[i] = getchar();
        if (x[0] != '\n')
        {
            i++;
        }
    }
    while ( x[i -1] != '\n');
    if (x[1] != '\n')
    {
        n = -2 ;
        return n;
    }
    else
    {
        if((x[0] >='a' && x[0]<='z' )||(x[0] >='A' && x[0]<='Z' ))
        {
            return x[0];
        }
        else
        {
            return -2;
        }
    }

}
//----------------------------------------------------------------------------------------------------------------------------
int getName(char str[], int n)//Get a name from the user .
{
    fflush(stdin);
    int ch, i=0;
    while((ch=getchar()) != '\n')
    {
        ch = tolower(ch);
        if(i<n)
        {
            if(i == 0 && ch == ' ')
            {
                continue;
            }
            else if((i != 0 )&& (str[i-1] == ' '|| str[i-1] == '\t') && (ch == ' ' || ch == '\t'))
            {
                continue;
            }
            else if(ch == '\t')
            {
                ch = ' ';
            }
            else
            {
                str[i++]=ch;
            }
        }
        else if(i >= 100)
        {
            return -10;
            break;
        }
    }
    str[i]='\0';
    if(i == 0)
    {
        return -11;
    }
    else if(i >= 100)
    {
        return -12;
    }
    else if(str[0] >= '0' && str[0] <= '9')
    {
        printf("\t\t\t\t\t\t\t\t\t\tcan't start with a number");
        return -13;
    }
    else
    {
        return 0;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------
int countlines(char *filename)    // count the number of lines in the file called filename .
{
    FILE *fp = fopen(filename,"r");
    int ch=0;
    int lines=0;

    if (fp == NULL)
        return 0;

    lines++;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            lines++;
    }
    fclose(fp);
    return lines;
}

#endif // GETINFO_H_INCLUDED
