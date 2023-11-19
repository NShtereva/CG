#include <iostream>
#include <vector>
#include <stack>

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

void initIndices(unsigned int* indices, const unsigned int n, const unsigned int baseIndex)
{
    indices[0] = baseIndex;
    
    for(unsigned i = 0, j = 1; i < n; i++)
    {
        if(i != baseIndex)
        {
            indices[j++] = i;
        }
    }
}

double orientation(const Point& A, const Point& B, const Point& C)
{
    return (B - A) ^ (C - A); // AB x AC
}

// TODO: quickSort
void sort(const std::vector<Point>& points, unsigned int* indices, const unsigned int n)
{
    for(int i = 1; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(orientation(points[indices[0]], points[indices[i]], points[indices[j]]) < 0)
            {
                unsigned int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
}

unsigned int nextToTop(std::stack<unsigned int> S)
{
    S.pop();
    return S.top();
}

void convexHull(const std::vector<Point>& points, unsigned int* indices, const unsigned int n)
{
    sort(points, indices, n);

    std::stack<unsigned int> S;
    S.push(indices[0]);
    S.push(indices[1]);
    S.push(indices[2]);
 
    for(int i = 3; i < n; i++)
    {
        while(orientation(points[nextToTop(S)], points[S.top()], points[indices[i]]) < 0)
        {
            S.pop();
        }
        S.push(indices[i]);
    }

    std::cout << "Convex hull indices:" << std::endl;
    while(!S.empty())
    {
        std::cout << S.top() << ' ';
        S.pop();
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

    unsigned int indices[MAX_SIZE] = {0,};
    initIndices(indices, n, baseIndex);

    convexHull(points, indices, n);
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
9 8 7 6 4 1 0 
*/
