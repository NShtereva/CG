#include <iostream>
#include "../vecta.h"

double S(const vecta::vec2d<double>& A, const vecta::vec2d<double>& B, const vecta::vec2d<double>& C)
{
    return (B - A) ^ (C - A); // AB x AC
}

int main()
{
    vecta::vec2d<double> A, B, C, P;
    std::cin >> A >> B >> C >> P;

    double SPAB = S(P, A, B),
           SPBC = S(P, B, C),
           SPCA = S(P, C, A);

    if((SPAB < 0 && SPBC < 0 && SPCA < 0) || (SPAB > 0 && SPBC > 0 && SPCA > 0)) // in
    {
        std::cout << 1 << std::endl;
    }
    else if(SPAB == 0 && SPCA == 0) // P == A
    {
        std::cout << 2 << std::endl;
    }
    else if(SPAB == 0 && SPBC == 0) // P == B
    {
        std::cout << 3 << std::endl;
    }
    else if(SPBC == 0 && SPCA == 0) // P == C
    {
        std::cout << 4 << std::endl;
    }
    else if((SPAB == 0 && SPBC < 0 && SPCA < 0) || (SPAB == 0 && SPBC > 0 && SPCA > 0)) // P e AB
    {
        std::cout << 5 << std::endl;
    }
    else if((SPBC == 0 && SPAB < 0 && SPCA < 0) || (SPBC == 0 && SPAB > 0 && SPCA > 0)) // P e BC
    {
        std::cout << 6 << std::endl;
    }
    else if((SPCA == 0 && SPAB < 0 && SPBC < 0) || (SPCA == 0 && SPAB > 0 && SPBC > 0)) // P e AC
    {
        std::cout << 7 << std::endl;
    }
    else 
    {
        std::cout << 8 << std::endl;
    }
    return 0;
}

/*
// Interior point:
1 1
3 1
2 3
1
// P == A:
1 1 
3 1
2 3
2
// P == B:
1 1 
3 1
2 3
3
// P == C:
1 1
3 1
2 3
4
// P e AB:
1 1
3 1
2 3
5
// P e BC:
  1 1
  3 1
  2 3
2.5 2
6
// P e AC:
  1 1
  3 1
  2 3
1.5 2
7
// Exterior point:
1 1 
3 1
2 3
0 0
8
*/
