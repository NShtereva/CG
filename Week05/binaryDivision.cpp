#include <iostream>
#include <vector>

#include "../vecta.h"

typedef vecta::vec2d<double> Point;

double S(const Point& A, const Point& B, const Point& C)
{
    return (B - A) ^ (C - A); // AB x AC
}

bool isInTriangle(const Point& A, const Point& B, const Point& C, const Point& P)
{
    double SPAB = S(P, A, B),
           SPBC = S(P, B, C),
           SPCA = S(P, C, A);

    return ((SPAB < 0 && SPBC < 0 && SPCA < 0) || (SPAB > 0 && SPBC > 0 && SPCA > 0));
}

int main()
{
    unsigned int n;
    std::cout << "Enter n: ";
    std::cin >> n;

    std::vector<Point> vertices;

    std::cout << "Enter vertices:\n";
    for(unsigned i = 0; i < n; i++)
    {
        Point Vi;
        std::cin >> Vi;

        vertices.push_back(Vi);
    }

    Point P;
    std::cout << "Enter point: ";
    std::cin >> P;

    unsigned short base = 0, l = n - 1, r = 1;

    double SBLP = S(vertices[base], vertices[l], P), 
           SBRP = S(vertices[base], vertices[r], P);

    if(SBLP > 0 || SBRP < 0)
    {
        std::cout << "external point" << std::endl;
        return 0;
    }

    if(SBRP == 0 && ((P - vertices[base]) * (P - vertices[r])) <= 0)
    {
        std::cout << "on the contour" << std::endl;
        return 0;
    }

    if(SBLP == 0 && ((P - vertices[base]) * (P - vertices[l])) <= 0)
    {
        std::cout << "on the contour" << std::endl;
        return 0;
    }

    while(l - r != 1)
    {
        unsigned int middle = r + (l - r) / 2;
        double SBMP = S(vertices[base], vertices[middle], P);
        
        if(SBMP <= 0)
        {
            l = middle;
        }
        else
        {
            r = middle;
        }
    }

    if(S(vertices[l], vertices[r], P) == 0 && ((P - vertices[l]) * (P - vertices[r])) <= 0)
    {
        std::cout << "on the contour" << std::endl;
        return 0;
    }

    if(isInTriangle(vertices[base], vertices[l], vertices[r], P) || 
       (S(vertices[base], vertices[l], P) == 0 && ((P - vertices[base]) * (P - vertices[l])) <= 0) ||
       (S(vertices[base], vertices[r], P) == 0 && ((P - vertices[base]) * (P - vertices[r])) <= 0))
    {
        std::cout << "interior point" << std::endl;
        return 0;
    }

    std::cout << "external point" << std::endl;
    return 0;
}
