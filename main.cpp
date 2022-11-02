#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>


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
fractional** simplex(fractional **system,int row,int column, std::vector<std::string> &X, std::vector<std::string> &Y);
fractional** deleteEquals(fractional **system,int &row,int &column,std::vector<int>& Ysign,std::vector<std::string> &X,std::vector<std::string> &Y);

void printMatrix(fractional **system,int &row,int &column,std::vector<std::string> &X,std::vector<std::string> &Y)
{
    int maxSize = 0;
    std::string c[row][column];
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < column; ++j)
        {
            if(system[i][j].denominator == 1 || system[i][j].numerator == 0)
                c[i][j] = std::to_string(system[i][j].numerator);
            else
                c[i][j] = std::to_string(system[i][j].numerator) + '/' + std::to_string(system[i][j].denominator);
            if(c[i][j].size() > maxSize)
                maxSize = c[i][j].size();
        }
    }
    std::cout<<"   ";
    for(int i = 0; i < column;++i)
    {
        std::cout<<X[i]<<std::setw(maxSize - X[i].size() + 12)<<std::setfill(' ');
    }
    std::cout<<"\n";
    for(int i = 0; i < row; ++i)
    {
        std::cout<<Y[i]<<": ";
        for(int j = 0; j < column; ++j)
        {
            std::cout<<c[i][j]<<std::setw(maxSize-c[i][j].size()+12)<<std::setfill(' ');
        }
        std::cout<<'\n';
    }
}

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
    std::cout<<"System must have only = or ≥,\nif you want type = you must type 0,\nif you want type ≥ you must type 1,\n";

    std::vector<std::string> X,Y;
    std::vector<int> Ysign;

    fractional **system;
    int row,column,iPivot,jPivot;
    std::cin>>row>>column;
    system = new fractional*[row];
    for(int j = 0; j < column; ++j)
    {
        if(j != column - 1)
            X.push_back("X"+std::to_string(j+1));
        else
            X.push_back("B");
    }
    for(int i = 0; i < row; ++i)
    {
        int sign;
        system[i] = new fractional[column];
        if(i != row - 1)
            Y.push_back("Y"+std::to_string(i+1));
        else
            Y.push_back("F");
        for(int j = 0; j < column; ++j)
        {
            std::cin>>system[i][j].numerator;
            system[i][j].denominator = 1;
        }
        if(i != row - 1)
        {
            std::cin>>sign;
            Ysign.push_back(sign);
        }
    }
    printMatrix(system,row,column,X,Y);
    system = deleteEquals(system,row,column,Ysign,X,Y);
    if(system == nullptr)
        return 0;
    std::cout<<"Simplex\n";
    system = simplex(system,row,column,X,Y);
    for(int i = 0; i < row; ++i)
        {

            for(int j = 0; j < column; ++j)
            {
                std::cout<<system[i][j]<<std::setw(12)<<std::setfill(' ');
            }
            std::cout<<'\n';
        }
    while(true)
    {
        std::cin>>iPivot>>jPivot;
        std::cout<<'\n';
        system = jordan(system,row,column,iPivot,jPivot);
        std::cout<<"   ";
        for(int j = 0; j < column; ++j)
        {
            std::cout<<"X"<<j+1<<std::setw(12)<<std::setfill(' ');
        }
        std::cout<<'\n';
        printMatrix(system,row,column,X,Y);

    }

    return 0;
}
/*
4 7
2 -1 0 -2 1 0 -16 0
3 2 1 -3 0 0 -18 0
-1 3 0 4 0 1 -24 0
-2 -3 0 1 0 0 0

3 4
1 2 3 -5 0
1 3 4 -6 0
2 -1 -1 -1

 */

fractional** deleteEquals(fractional **system,int& row,int& column,std::vector<int>& Ysign,std::vector<std::string> &X,std::vector<std::string> &Y)
{
    for(int i = 0; i < Ysign.size(); ++i)
    {
        if(Ysign[i] == 0)
        {
            int jPivot = -1;
            for(int j = 0; j < X.size();++j)
            {
                if(X[j][0] == 'X' && system[i][j].numerator != 0)
                {
                    jPivot = j;
                    break;
                }
            }
            if(jPivot!=-1)
            {
                system = jordan(system,row,column,i,jPivot);
                for(int k = jPivot;k < column-1; ++k)
                {
                    for(int j = 0; j < row; ++j)
                    {
                        system[j][k] = system[j][k+1];
                    }
                }
                std::cout<<"swap("<<X[jPivot]<<", "<<Y[i]<<')'<<'\n';
                --column;
                swap(X[jPivot],Y[i]);
                X.erase(X.begin()+jPivot);

                printMatrix(system,row,column,X,Y);
                Ysign[i] = 1;
                std::cout<<'\n';

            }
            else
            {
                std::cout<<"System has no solutions\n";
                return nullptr;
            }
        }
    }
    return system;
}

fractional** simplex(fractional **system,int row,int column,std::vector<std::string> &X,std::vector<std::string> &Y)
{
    bool isReady = true;
    for(int j = 0; j < column -1; ++j)
    {
        if(system[row - 1][j].numerator < 0)
        {
            isReady *= false;
        }
    }

    while(!isReady)
    {
        std::cout<<"max = {";
        double max = INTMAX_MIN;
        int maxI,maxJ;
        for(int j = 0; j < column - 1; ++j)
        {
            if(system[row - 1][j].numerator < 0)
            {
                for(int i = 0; i < row - 1; ++i)
                {
                    if(system[i][j].numerator < 0)
                    {
                        fractional tmp = system[i][column - 1]/system[i][j];
                        double local = tmp.numerator/tmp.denominator;
                        std::cout<<local<<',';
                        if(local > max)
                        {
                            max = local;
                            maxI = i;
                            maxJ = j;
                        }

                    }
                }
            }
        }
        std::cout<<"} = "<<max<<'\n';
        if(max == INTMAX_MIN)
        {
            std::cout<<"System has no solutions\n";
            return nullptr;
        }
        system = jordan(system,row,column,maxI,maxJ);

        isReady = true;
        for(int j = 0; j < column -1; ++j)
        {
            if(system[row - 1][j].numerator < 0)
            {
                isReady *= false;
            }
        }

        std::cout<<"swap("<<X[maxJ]<<", "<<Y[maxI]<<')'<<'\n';
        swap(X[maxJ],Y[maxI]);
        printMatrix(system,row,column,X,Y);

    }


    return system;
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

