#include <iostream>

int** jordan(int **system,int row,int column,int iPivot,int jPivot);
void simplex();

int main()
{
    int *F;
    int **system;
    int row,column,iPivot,jPivot;
    std::cout<<"type size of system\n";
    std::cin>>row>>column;
    //std::cout<<"type pivot index\n";
    std::cin>>iPivot>>jPivot;
    system = new int*[row];
    for(int i = 0; i < row; ++i)
    {
        system[i] = new int[column];
        for(int j = 0; j < column; ++j)
        {
            std::cin>>system[i][j];
        }
    }
    for(int k=0;k<3;++k)
    {
        std::cout<<'\n';
        system = jordan(system,row,column,k,k);
        for(int i = 0; i < row; ++i)
        {
            for(int j = k; j < column; ++j)
            {
                std::cout<<system[i][j]<<' ';
            }
            std::cout<<'\n';
        }
    }

    return 0;
}
/*
0 0
1 1 7 -3 -7 -13
1 2 13 2 -14 -20
1 3 20 6 -23 -19

 */

int** jordan(int **system,int row,int column,int iPivot,int jPivot)
{
    int **result;
    result = new int*[row];
    for(int i = 0; i < row; ++i)
    {
        result[i] = new int[column];
    }


    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < column; ++j)
        {
            if(i != iPivot && j != jPivot)
            {
                result[i][j] = system[iPivot][jPivot] * system[i][j] - system[i][jPivot]*system[iPivot][j];
            } else
            {
                result[i][j] = system[i][j];
            }
        }
    }

    for(int j = 1; j < column; ++j)
    {
        result[iPivot][j] *= -1;
    }

    result[iPivot][jPivot] = 1;

    return result;
}

void simplex()
{

}
