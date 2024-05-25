#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>


#define n 4



HANDLE outputHandle;
CONSOLE_CURSOR_INFO invisiCursor = { 5, FALSE };



int values[n][n]= {0};
int len=0;



void KeyPress()
{
    switch(getch())
    {
    case 224:
    case 0:
        switch(getch())
        {
        case 72: //Up
            break;
        case 80: //Down
            break;
        case 77: //Right
            break;
        case 75: //Left
            break;
        default:
            KeyPress();
            break;
        }
        break;
    default:
        KeyPress();
        break;
    }
}

void Print()
{
    system("cls");
    printf("╔════════╤════════╤════════╤════════╗\n");
    printf("║        │        │        │        ║\n");
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            if(col==0) printf("║");
            if(values[row][col]!=0)
            {
                if(values[row][col]<=99) printf("   %2d   ", values[row][col]);
                else printf("  %4d  ", values[row][col]);
            }
            else printf("        ");
            if(col==n-1) printf("║\n");
            else         printf("│");
        }
        if(row==n-1)
        {
            printf("║        │        │        │        ║\n");
            printf("╚════════╧════════╧════════╧════════╝\n");
        }
        else
        {
            printf("║        │        │        │        ║\n");
            printf("╟────────┼────────┼────────┼────────╢\n");
            printf("║        │        │        │        ║\n");
        }
    }
}

void Init()
{
    SetConsoleOutputCP(65001);
    system("mode 80,40");
    outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(outputHandle, &invisiCursor);
    Spawn();
}

void Spawn()
{
    int count=0;
    for(int row=0; row<n; row++) for(int col=0; col<n; col++) if(values[row][col]==0) count++;
    int seed=clock()%1000;
    int rand=seed%count;
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            if (values[row][col]==0)
            {
                rand--;
                if(rand==0)
                {
                    if(seed/100<=6) values[row][col]=2;
                    else            values[row][col]=4;
                }
            }
        }
    }

}
/*
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
        }
    }
*/




void Up()
{
}


void Down()
{
}


void Left()
{
    for(int row=0;row<n;row++)
    {
        int temp[n]={0}; //shortcut to fill array of any length with 0s //only works with 0
        int x=0;
        for(int col=0;col<n;col++)
        {
            if(values[row][col]!=0)
            {
                temp[x]=values[row][col];
                x++;
            }
        }
        for(int col=0;col<n;col++)
        {
            values[row][col]=temp[col];
        }
    }


    for(int row=0;row<n;row++)
    {
        for(int col=0;col<n-1;col++)
        {
            if(values[row][col]==values[row][col+1])
            {
                values[row][col]*=2;
                values[row][col+1]=0;
                col++;
            }
        }
    }


    for(int row=0;row<n;row++)
    {
        int temp[n]={0}; //shortcut to fill array of any length with 0s //only works with 0
        int x=0;
        for(int col=0;col<n;col++)
        {
            if(values[row][col]!=0)
            {
                temp[x]=values[row][col];
                x++;
            }
        }
        for(int col=0;col<n;col++)
        {
            values[row][col]=temp[col];
        }
    }
}


void Right()
{
}



int main()
{
    Init();
    Print();

}
