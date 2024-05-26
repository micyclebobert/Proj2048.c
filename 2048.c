#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>


#define n 4




int values[n][n];






void Up();
void Down();
void Left();
void Right();
void Print();
void Spawn();
void GameWon();
void GameOver();
void KeyPress();
void CheckState();
void InitNewGame();
void InitProperties();
int  PlayAnotherGame();
int  CountEmptyTiles();







void KeyPress()
{
    switch(getch())
    {
    case 224:
    case 0:
        switch(getch())
        {
        case 72: //Up
            Up();
            break;
        case 80: //Down
            Down();
            break;
        case 77: //Right
            Right();
            break;
        case 75: //Left
            Left();
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

void InitProperties()
{
    SetConsoleOutputCP(65001);
    system("mode 80,40");
}

void InitNewGame()
{
    for(int row=0; row<n; row++) for(int col=0; col<n; col++) values[row][col]=0;
    Spawn();
    Print();
    KeyPress();
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
                if(rand==0)
                {
                    if(seed/100<=6) values[row][col]=2;
                    else            values[row][col]=4;
                    return;
                }
                rand--;
            }
        }
    }
}





void Up()
{
    for(int col=0; col<n; col++)
    {
        int temp[n];
        for(int i=0; i<n; i++) temp[i]=0;
        int idx=0;
        for(int row=0; row<n; row++)
        {
            if(values[row][col]!=0)
            {
                temp[idx]=values[row][col];
                idx++;
            }
        }
        for(int row=0; row<n; row++)
        {
            values[row][col]=temp[row];
        }
    }


    for(int col=0; col<n; col++)
    {
        for(int row=0; row<n-1; row++)
        {
            if(values[row][col]==values[row+1][col])
            {
                values[row][col]*=2;
                values[row+1][col]=0;
                row++;
            }
        }
    }


    for(int col=0; col<n; col++)
    {
        int temp[n];
        for(int i=0; i<n; i++) temp[i]=0;
        int idx=0;
        for(int row=0; row<n; row++)
        {
            if(values[row][col]!=0)
            {
                temp[idx]=values[row][col];
                idx++;
            }
        }
        for(int row=0; row<n; row++)
        {
            values[row][col]=temp[row];
        }
    }
    CheckState();
}


void Down()
{
    for(int col=0; col<n; col++)
    {
        int temp[n];
        for(int i=0; i<n; i++) temp[i]=0;
        int idx=3;
        for(int row=n-1; row>=0; row--)
        {
            if(values[row][col]!=0)
            {
                temp[idx]=values[row][col];
                idx--;
            }
        }
        for(int row=0; row<n; row++)
        {
            values[row][col]=temp[row];
        }
    }


    for(int col=0; col<n; col++)
    {
        for(int row=n-1; row>0; row--)
        {
            if(values[row][col]==values[row-1][col])
            {
                values[row][col]*=2;
                values[row-1][col]=0;
                row--;
            }
        }
    }


    for(int col=0; col<n; col++)
    {
        int temp[n];
        for(int i=0; i<n; i++) temp[i]=0;
        int idx=3;
        for(int row=n-1; row>=0; row--)
        {
            if(values[row][col]!=0)
            {
                temp[idx]=values[row][col];
                idx--;
            }
        }
        for(int row=0; row<n; row++)
        {
            values[row][col]=temp[row];
        }
    }
    CheckState();
}


void Left()
{
    for(int row=0; row<n; row++)
    {
        int temp[n];
        for(int i=0; i<n; i++) temp[i]=0;
        int idx=0;
        for(int col=0; col<n; col++)
        {
            if(values[row][col]!=0)
            {
                temp[idx]=values[row][col];
                idx++;
            }
        }
        for(int col=0; col<n; col++)
        {
            values[row][col]=temp[col];
        }
    }


    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n-1; col++)
        {
            if(values[row][col]==values[row][col+1])
            {
                values[row][col]*=2;
                values[row][col+1]=0;
                col++;
            }
        }
    }


    for(int row=0; row<n; row++)
    {
        int temp[n];
        for(int i=0; i<n; i++) temp[i]=0;
        int idx=0;
        for(int col=0; col<n; col++)
        {
            if(values[row][col]!=0)
            {
                temp[idx]=values[row][col];
                idx++;
            }
        }
        for(int col=0; col<n; col++)
        {
            values[row][col]=temp[col];
        }
    }
    CheckState();
}


void Right()
{
    for(int row=0; row<n; row++)
    {
        int temp[n];
        for(int i=0; i<n; i++) temp[i]=0;
        int idx=3;
        for(int col=n-1; col>=0; col--)
        {
            if(values[row][col]!=0)
            {
                temp[idx]=values[row][col];
                idx--;
            }
        }
        for(int col=0; col<n; col++)
        {
            values[row][col]=temp[col];
        }
    }


    for(int row=0; row<n; row++)
    {
        for(int col=n-1; col>0; col--)
        {
            if(values[row][col]==values[row][col-1])
            {
                values[row][col]*=2;
                values[row][col-1]=0;
                col--;
            }
        }
    }


    for(int row=0; row<n; row++)
    {
        int temp[n];
        for(int i=0; i<n; i++) temp[i]=0;
        int idx=3;
        for(int col=n-1; col>=0; col--)
        {
            if(values[row][col]!=0)
            {
                temp[idx]=values[row][col];
                idx--;
            }
        }
        for(int col=0; col<n; col++)
        {
            values[row][col]=temp[col];
        }
    }
    CheckState();
}

int CountEmptyTiles()
{
    int count=0;
    for(int row=0; row<n; row++) for(int col=0; col<n; col++) if(values[row][col]==0) count++;
    return count;
}

void CheckState()
{
    for(int row=0; row<n; row++) for(int col=0; col<n; col++) if(values[row][col]==2048) return GameWon();
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            if(values[row][col]==0)
            {
                Spawn();
                Print();
                if(CountEmptyTiles()!=1) return KeyPress();
            }
        }
    }
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n-1; col++)
        {
            if(values[row][col]==values[row][col+1])
            {
                Print();
                return KeyPress();
            }
        }
    }
    for(int col=0; col<n; col++)
    {
        for(int row=0; row<n-1; row++)
        {
            if(values[row][col]==values[row+1][col])
            {
                Print();
                return KeyPress();
            }
        }
    }
    return GameOver();
}

void GameWon()
{
    Print();
    printf("\n\nGame Won");
}

void GameOver()
{
    Print();
    printf("\n\nGame Over");
}

int PlayAnotherGame()
{
    switch(toupper(getch()))
    {
    case 'Y':
        return 1;
        break;
    case 'N':
        return 0;
        break;
    default:
        return PlayAnotherGame();
        break;
    }
}


int main()
{
    InitProperties();

    do
    {
        InitNewGame();
        printf("\n\nWould you like to play again? Y/N");
    }
    while(PlayAnotherGame());

    printf("Thank you for playing!!!");
}
