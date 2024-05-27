#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>




#define n 4


struct val
{
    int values[n][n];
} v;
FILE *f;


//v.values

//int values[n][n];




void Up();
void Down();
void Left();
void Right();
void Print();
void Spawn();
void Illegal();
void GameWon();
void GameOver();
void GameSaver();
void GameLoader();
void CheckState();
void InitNewGame();
void InitProperties();
void GameKeyPresses();
int  PlayAnotherGame();
int  CountEmptyTiles();






void InitProperties()
{
    SetConsoleOutputCP(65001);
    system("mode 37,20");
}

void InitNewGame()
{
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            v.values[row][col]=0;
        }
    }
    Spawn();
    Print();
    GameKeyPresses();
}





void Illegal()
{
    Print();
    printf("\nIllegal Input!!");
}




void GameSaver()
{
    f=fopen("2048.bin","wb");
    if(f!=0)
    {
        int x=fwrite(&v,sizeof(v),1,f);
        fclose(f);
        Print();
        if(x==1) printf("\nFile saved successfully");
        else     printf("\nError saving the file");
    }
    else
    {
        Print();
        printf("\nUnable to create file");
    }
    GameKeyPresses();
}


void GameLoader()
{
    f=fopen("2048.bin","rb");
    if(f!=0)
    {
        int x=fread(&v,sizeof(v),1,f);
        fclose(f);
        Print();
        if(x==1) printf("\nGame loaded successfully");
        else     printf("\nError loading the file");
    }
    else
    {
        Print();
        printf("\nFile not found");
    }
    GameKeyPresses();
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
            if(col==0)
            {
                printf("║");
            }
            if(v.values[row][col]!=0)
            {
                if(v.values[row][col]<=99)
                {
                    printf("   %2d   ", v.values[row][col]);
                }
                else
                {
                    printf("  %4d  ", v.values[row][col]);
                }
            }
            else
            {
                printf("        ");
            }
            if(col==n-1)
            {
                printf("║\n");
            }
            else
            {
                printf("│");
            }
        }
        if(row!=n-1)
        {
            printf("║        │        │        │        ║\n");
            printf("╟────────┼────────┼────────┼────────╢\n");
            printf("║        │        │        │        ║\n");
        }
        else
        {
            printf("║        │        │        │        ║\n");
            printf("╚════════╧════════╧════════╧════════╝\n");
        }
    }
}


void GameKeyPresses()
{
    switch(getch())
    {
    case 19: //Ctrl+S
        GameSaver();
        break;
    case 12: //Ctrl+L
        GameLoader();
        break;
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
            Illegal();
            GameKeyPresses();
            break;
        }
        break;
    default:
        Illegal();
        GameKeyPresses();
        break;
    }
}


void Spawn()
{
    int count=0;
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            if(v.values[row][col]==0)
            {
                count++;
            }
        }
    }
    int seed=clock();
    int rand=seed%count;
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            if (v.values[row][col]==0)
            {
                if(rand==0)
                {
                    if(seed%10<=6)
                    {
                        v.values[row][col]=2;
                    }
                    else
                    {
                        v.values[row][col]=4;
                    }
                    return;
                }
                rand--;
            }
        }
    }
}

int CountEmptyTiles()
{
    int count=0;
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            if(v.values[row][col]==0)
            {
                count++;
            }
        }
    }
    return count;
}

void CheckState()
{
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            if(v.values[row][col]==2048)
            {
                return GameWon();
            }
        }
    }
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            if(v.values[row][col]==0)
            {
                Spawn();
                Print();
                if(CountEmptyTiles()!=0)
                {
                    return GameKeyPresses();
                }
            }
        }
    }
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n-1; col++)
        {
            if(v.values[row][col]==v.values[row][col+1])
            {
                Print();
                return GameKeyPresses();
            }
        }
    }
    for(int col=0; col<n; col++)
    {
        for(int row=0; row<n-1; row++)
        {
            if(v.values[row][col]==v.values[row+1][col])
            {
                Print();
                return GameKeyPresses();
            }
        }
    }
    return GameOver();
}


void Up()
{
    for(int col=0; col<n; col++)
    {
        int temp[n];
        for(int i=0; i<n; i++)
        {
            temp[i]=0;
        }
        int idx=0;
        for(int row=0; row<n; row++)
        {
            if(v.values[row][col]!=0)
            {
                temp[idx]=v.values[row][col];
                idx++;
            }
        }
        for(int row=0; row<n; row++)
        {
            v.values[row][col]=temp[row];
        }
    }
    for(int col=0; col<n; col++)
    {
        for(int row=0; row<n-1; row++)
        {
            if(v.values[row][col]==v.values[row+1][col])
            {
                v.values[row][col]*=2;
                v.values[row+1][col]=0;
                row++;
            }
        }
    }
    for(int col=0; col<n; col++)
    {
        int temp[n];
        for(int i=0; i<n; i++)
        {
            temp[i]=0;
        }
        int idx=0;
        for(int row=0; row<n; row++)
        {
            if(v.values[row][col]!=0)
            {
                temp[idx]=v.values[row][col];
                idx++;
            }
        }
        for(int row=0; row<n; row++)
        {
            v.values[row][col]=temp[row];
        }
    }
    CheckState();
}

void Down()
{
    for(int col=0; col<n; col++)
    {
        int temp[n];
        for(int i=0; i<n; i++)
        {
            temp[i]=0;
        }
        int idx=3;
        for(int row=n-1; row>=0; row--)
        {
            if(v.values[row][col]!=0)
            {
                temp[idx]=v.values[row][col];
                idx--;
            }
        }
        for(int row=0; row<n; row++)
        {
            v.values[row][col]=temp[row];
        }
    }
    for(int col=0; col<n; col++)
    {
        for(int row=n-1; row>0; row--)
        {
            if(v.values[row][col]==v.values[row-1][col])
            {
                v.values[row][col]*=2;
                v.values[row-1][col]=0;
                row--;
            }
        }
    }
    for(int col=0; col<n; col++)
    {
        int temp[n];
        for(int i=0; i<n; i++)
        {
            temp[i]=0;
        }
        int idx=3;
        for(int row=n-1; row>=0; row--)
        {
            if(v.values[row][col]!=0)
            {
                temp[idx]=v.values[row][col];
                idx--;
            }
        }
        for(int row=0; row<n; row++)
        {
            v.values[row][col]=temp[row];
        }
    }
    CheckState();
}

void Left()
{
    for(int row=0; row<n; row++)
    {
        int temp[n];
        for(int i=0; i<n; i++)
        {
            temp[i]=0;
        }
        int idx=0;
        for(int col=0; col<n; col++)
        {
            if(v.values[row][col]!=0)
            {
                temp[idx]=v.values[row][col];
                idx++;
            }
        }
        for(int col=0; col<n; col++)
        {
            v.values[row][col]=temp[col];
        }
    }
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n-1; col++)
        {
            if(v.values[row][col]==v.values[row][col+1])
            {
                v.values[row][col]*=2;
                v.values[row][col+1]=0;
                col++;
            }
        }
    }
    for(int row=0; row<n; row++)
    {
        int temp[n];
        for(int i=0; i<n; i++)
        {
            temp[i]=0;
        }
        int idx=0;
        for(int col=0; col<n; col++)
        {
            if(v.values[row][col]!=0)
            {
                temp[idx]=v.values[row][col];
                idx++;
            }
        }
        for(int col=0; col<n; col++)
        {
            v.values[row][col]=temp[col];
        }
    }
    CheckState();
}

void Right()
{
    for(int row=0; row<n; row++)
    {
        int temp[n];
        for(int i=0; i<n; i++)
        {
            temp[i]=0;
        }
        int idx=3;
        for(int col=n-1; col>=0; col--)
        {
            if(v.values[row][col]!=0)
            {
                temp[idx]=v.values[row][col];
                idx--;
            }
        }
        for(int col=0; col<n; col++)
        {
            v.values[row][col]=temp[col];
        }
    }
    for(int row=0; row<n; row++)
    {
        for(int col=n-1; col>0; col--)
        {
            if(v.values[row][col]==v.values[row][col-1])
            {
                v.values[row][col]*=2;
                v.values[row][col-1]=0;
                col--;
            }
        }
    }
    for(int row=0; row<n; row++)
    {
        int temp[n];
        for(int i=0; i<n; i++)
        {
            temp[i]=0;
        }
        int idx=3;
        for(int col=n-1; col>=0; col--)
        {
            if(v.values[row][col]!=0)
            {
                temp[idx]=v.values[row][col];
                idx--;
            }
        }
        for(int col=0; col<n; col++)
        {
            v.values[row][col]=temp[col];
        }
    }
    CheckState();
}


void GameWon()
{
    Print();
    printf("\nGame Won");
}

void GameOver()
{
    Print();
    printf("\nGame Over");
}


int main()
{
    InitProperties();

    do
    {
        InitNewGame();
        printf("\nWould you like to play again? Y/N");
    }
    while(PlayAnotherGame());

    system("cls");
    printf("\n\n\n\n\n\n\n       Thank you for playing!!       \n\n\n\n\n\n\n\n");
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
    case 224:
    case 0:
        getch();
        return PlayAnotherGame();
        break;
    default:
        return PlayAnotherGame();
        break;
    }
}
