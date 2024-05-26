void Spawn()
{
    int count=0;
    for(int row=0; row<n; row++) for(int col=0; col<n; col++) if(values[row][col]==0) count++;
    int seed=clock();
    int rand=seed%count;
    for(int row=0; row<n; row++)
    {
        for(int col=0; col<n; col++)
        {
            if (values[row][col]==0)
            {
                if(rand==0)
                {
                    if(seed%10<=6) values[row][col]=2;
                    else           values[row][col]=4;
                    return;
                }
                rand--;
            }
        }
    }
}
