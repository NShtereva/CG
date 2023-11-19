#include <iostream>
#include <vector>

#include "../vecta.h"

typedef vecta::vec2d<double> Point;

void readPoints(std::vector<Point>& points, const unsigned int n)
{
    std::cout << "Enter points:\n";
    for(unsigned i = 0; i < n; i++)
    {
        Point P;
        std::cin >> P;

        points.push_back(P);
    }
}

unsigned basePointIndex(const std::vector<Point>& points, const unsigned int n)
{
    unsigned min = 0;
    for(unsigned i = 1; i < n; i++)
    {
        if(points[i].x < points[min].x)
        {
            min = i;
        }
    }
    return min;
}

void initIndices(bool* indices, const unsigned int n, const unsigned int baseIndex)
{
    for(unsigned i = 0; i < n; i++)
    {
        if(i != baseIndex)
        {
            indices[i] = 1;
        }
    }
}

void convexHull(const std::vector<Point>& points, bool* indices, const unsigned int n, const unsigned int baseIndex)
{
    unsigned int currIndex = baseIndex;
    do
    {
        unsigned int nextIndex = (currIndex + 1) % n;
        indices[nextIndex] = 0;

        for(unsigned i = 0; i < n; i++)
        {
            if(!indices[i])
                continue;

            if(((points[nextIndex] - points[currIndex]) ^ (points[i] - points[currIndex])) < 0)
            {
                indices[nextIndex] = 1;
                nextIndex = i;
                indices[nextIndex] = 0;
                i = -1;
            }
        }

        currIndex = nextIndex;
    } while(currIndex != baseIndex);
}

void printConvexHull(const bool* indices, const unsigned int n)
{
    std::cout << "Convex hull indices:" << std::endl;
    for(int i = 0; i < n; i++)
    {
        if(!indices[i])
        {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;
}

int main()
{
    const unsigned int MAX_SIZE = 100;
    unsigned int n;
    do
    {
        std::cout << "Enter n: ";
        std::cin >> n;
    } while(n < 3 || n > MAX_SIZE);

    std::vector<Point> points;
    readPoints(points, n);

    unsigned int baseIndex = basePointIndex(points, n);

    bool indices[MAX_SIZE] = {0,};
    initIndices(indices, n, baseIndex);

    convexHull(points, indices, n, baseIndex);
    printConvexHull(indices, n);    
    return 0;
}

/*
Enter n: 10
Enter points:
0 0  
10 -5
10 0
5 5 
20 0
15 5
20 10
17 20
14 20
0 10
Convex hull indices:
0 1 4 6 7 8 9 
*/
