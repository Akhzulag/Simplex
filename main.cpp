#include <iostream>
#include <iomanip>
#include <cmath>



class fractional
{
    int gcd(int a, int b)
    {
        int d = 1;
        while(a % 2 == 0 && b % 2 == 0)
        {
            a = a >> 1;
            b = b >> 1;
            d = d << 1;
        }

        while(a % 2 == 0)
        {
            a = a >> 1;
        }

        while(b != 0)
        {
            while (b % 2 == 0)
            {
                b = b >> 1;
            }
            int tmpA = std::min(a,b);
            b = abs(a - b);
            a = tmpA;
        }
        d = d * a;
        return d;
    }
public:
    int denominator;
    int numerator;

    fractional() {}
    fractional(int numerator, int denominator)
    {
        if(numerator == 0)
        {
            this->numerator = 0;
            this->denominator =1;
            return;
        }
        int gcdAB = gcd(abs(numerator),abs(denominator));
        while(gcdAB != 1)
        {
            numerator = numerator / gcdAB;
            denominator = denominator / gcdAB;
            gcdAB = gcd(abs(numerator),abs(denominator));
        }
        if((numerator < 0 && denominator < 0) || (numerator > 0 && denominator < 0))
        {
            this->numerator = -1*numerator;
            this->denominator = -1*denominator;
            return;
        }
        this->numerator = numerator;
        this->denominator = denominator;

    }
    friend fractional operator * (const fractional& Left,const fractional& Right)
    {
        int numerator = Left.numerator * Right.numerator;
        int denominator = Left.denominator * Right.denominator;
        return fractional(numerator,denominator);
    }
    friend fractional operator - (const fractional& Left,const fractional& Right)
    {
        int numeratorL = Left.numerator * Right.denominator;
        int numeratorR = Right.numerator * Left.denominator;
        int numerator = numeratorL - numeratorR;
        int denominator = Left.denominator*Right.denominator;
        return fractional(numerator,denominator);
    }
    friend fractional operator / (const fractional& Left,const fractional& Right)// 1/0
    {
        int numerator = Left.numerator * Right.denominator;
        int denominator = Left.denominator * Right.numerator;
        return fractional(numerator,denominator);
    }
    friend std::ostream& operator << (std::ostream& os, const fractional& Right)
    {
        if(Right.denominator == 1 || Right.numerator == 0)
        {
            os << Right.numerator;
            return os;
        }
        os << Right.numerator << '/' << Right.denominator;
        return os;
    }

};

fractional** jordan(fractional **system,int row,int column,int iPivot,int jPivot);
int* simplex(int **system,int row,int column);

int main()
{
//     while(true)
//     {
//         int a,b,c,d;
//         std::cin>>a;
//
//         std::cin>>b;
//
//
//         std::cin>>c;
//
//         std::cin>>d;
//         fractional r(a,b);
//         fractional r1(c,d);
//         fractional res = r - r1;
//         std::cout<<res<<'\n';
//     }
//    int *F;
    fractional **system;
    int row,column,iPivot,jPivot;
    //std::cout<<"type size of system\n";
    std::cin>>row>>column;
    //std::cout<<"type pivot index\n";
    //std::cin>>iPivot>>jPivot;
    system = new fractional*[row];
    for(int i = 0; i < row; ++i)
    {
        system[i] = new fractional[column];
        for(int j = 0; j < column; ++j)
        {
            std::cin>>system[i][j].numerator;
            system[i][j].denominator = 1;
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
                std::cout<<system[i][j]<<std::setw(12)<<std::setfill(' ');
            }
            std::cout<<'\n';
        }
    }

    return 0;
}
/*
4 4
-3 -1 0 3
2 -1 -1 2
-1 2 0 1
1 -1 0 0
1 1
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

fractional** jordan(fractional **system,int row,int column,int iPivot,int jPivot)
{
    fractional **result;//double
    result = new fractional*[row];
    for(int i = 0; i < row; ++i)
    {
        result[i] = new fractional[column];
    }
    fractional pivotElement = system[iPivot][jPivot];

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
        result[iPivot][j].numerator *= -1;
    }

    result[iPivot][jPivot].numerator = 1;
    result[iPivot][jPivot].denominator = 1;
    return result;
}

void simplex()
{

}
