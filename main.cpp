#include <iostream>
#include <iomanip>

double** jordan(double **system,int row,int column,int iPivot,int jPivot);
int* simplex(int **system,int row,int column);

int main()
{
    int *F;
    double **system;
    int row,column,iPivot,jPivot;
    //std::cout<<"type size of system\n";
    std::cin>>row>>column;
    //std::cout<<"type pivot index\n";
    //std::cin>>iPivot>>jPivot;
    system = new double*[row];
    for(int i = 0; i < row; ++i)
    {
        system[i] = new double[column];
        for(int j = 0; j < column; ++j)
        {
            std::cin>>system[i][j];
        }
    }
    while(true)
    {
        std::cin>>iPivot>>jPivot;
        std::cout<<'\n';
        system = jordan(system,row,column,iPivot,jPivot);
        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < column; ++j)
            {
                std::cout<<system[i][j]<<std::setw(15)<<std::setfill(' ');
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

double* simplex(double **system,int row,int column)
{
    int* x = new int[column];
    //шукаємо допустимий базисний розвязок
    bool isAdmissBase = false;
    while(!isAdmissBase)
    {
        for(int i = 0; i < row - 1; ++i)//на останньому рядку у нас записана цільова функція, тому проходимо на 1 рядок меньше
        {
            if(system[i][column-1] < 0)
            {
                isAdmissBase *= false;
            }
        }
    }

}

double** jordan(double **system,int row,int column,int iPivot,int jPivot)
{
    double **result;//double
    result = new double*[row];
    for(int i = 0; i < row; ++i)
    {
        result[i] = new double[column];
    }
    double pivotElement = system[iPivot][jPivot];

    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < column; ++j)
        {
            if(i != iPivot && j != jPivot)
            {
                result[i][j] = (system[iPivot][jPivot] * system[i][j] - system[i][jPivot]*system[iPivot][j])/pivotElement;

            } else
            {
                result[i][j] = system[i][j]/pivotElement;
            }
        }
    }

    for(int j = 0; j < column; ++j)
    {
        result[iPivot][j] *= -1;
    }

    result[iPivot][jPivot] = 1;

    return result;
}

void simplex()
{

}
