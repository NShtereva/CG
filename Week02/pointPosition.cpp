#include <iostream>
#include "../vecta.h"

typedef vecta::vec2d<double> Point;

double S(const Point& A, const Point& B, const Point& C)
{
    return (B - A) ^ (C - A); // AB x AC
}

void pointPosition(const Point& A, const Point& B, const Point& C, const Point& P)
{
    double SPAB = S(P, A, B),
           SPBC = S(P, B, C),
           SPCA = S(P, C, A);

    if((SPAB < 0 && SPBC < 0 && SPCA < 0) || (SPAB > 0 && SPBC > 0 && SPCA > 0))
    {
        std::cout << "\nInterior point." << std::endl;
    }
    else if(SPAB == 0 && SPCA == 0) // P == A
    {
        std::cout << "\nP coincides with A." << std::endl;
    }
    else if(SPAB == 0 && SPBC == 0) // P == B
    {
        std::cout << "\nP coincides with B." << std::endl;
    }
    else if(SPBC == 0 && SPCA == 0) // P == C
    {
        std::cout << "\nP coincides with C." << std::endl;
    }
    else if((SPAB == 0 && SPBC < 0 && SPCA < 0) || (SPAB == 0 && SPBC > 0 && SPCA > 0)) // P e AB
    {
        std::cout << "\nP lies on AB." << std::endl;
    }
    else if((SPBC == 0 && SPAB < 0 && SPCA < 0) || (SPBC == 0 && SPAB > 0 && SPCA > 0)) // P e BC
    {
        std::cout << "\nP lies on BC." << std::endl;
    }
    else if((SPCA == 0 && SPAB < 0 && SPBC < 0) || (SPCA == 0 && SPAB > 0 && SPBC > 0)) // P e AC
    {
        std::cout << "\nP lies on AC." << std::endl;
    }
    else 
    {
        std::cout << "\nExterior point." << std::endl;
    }
}

int main()
{
    Point A, B, C, P;
    std::cin >> A >> B >> C >> P;

    pointPosition(A, B, C, P);
    return 0;
}
