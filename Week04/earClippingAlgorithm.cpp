#include <iostream>
#include <vector>

#include "../vecta.h"

typedef vecta::vec2d<double> Point;

void readVertices(std::vector<Point>& vertices, const unsigned int n)
{
    for(unsigned i = 0; i < n; i++)
    {
        Point Vi;
        std::cin >> Vi;

        vertices.push_back(Vi);
    }
}

void initIndexList(unsigned int* indexList, const unsigned int n)
{
    for(unsigned int i = 0; i < n; i++)
    {
        indexList[i] = i;
    }
}

double STriangle(const Point& A, const Point& B, const Point& C)
{
    return (B - A) ^ (C - A); // AB x AC
}

bool isInTriangle(const Point& A, const Point& B, const Point& C, const Point& P)
{
    double SPAB = STriangle(P, A, B),
           SPBC = STriangle(P, B, C),
           SPCA = STriangle(P, C, A);

    return ((SPAB < 0 && SPBC < 0 && SPCA < 0) || (SPAB > 0 && SPBC > 0 && SPCA > 0));
}

bool isEar(unsigned index1, unsigned index2, unsigned index3, const std::vector<Point>& vertices, const unsigned int n)
{
    if(((vertices[index1] - vertices[index2]) ^ (vertices[index3] - vertices[index2])) < 0)
    {
        return false;
    }

    for(unsigned i = 0; i < n; i++)
    {
        if(i != index1 && i != index2 && i != index3)
        {
            if(isInTriangle(vertices[index1], vertices[index2], vertices[index3], vertices[i]))
            {
                return false;
            }

            double SPCA = STriangle(vertices[i], vertices[index3], vertices[index1]),
                   SPAB = STriangle(vertices[i], vertices[index1], vertices[index2]),
                   SPBC = STriangle(vertices[i], vertices[index2], vertices[index3]);

            if((SPCA == 0 && SPAB < 0 && SPBC < 0) || (SPCA == 0 && SPAB > 0 && SPBC > 0)) // P e AC 
            {
                return false;
            }
        }
    }

    return true;
}

void remove(unsigned int* indexList, unsigned int& n, const unsigned int index)
{
    for(unsigned i = index; i < n - 1; i++)
    {
        indexList[i] = indexList[i + 1];
    }
    n--;
}

void earClipping(const std::vector<Point>& vertices, unsigned int* indexList, unsigned int& n, std::vector<unsigned>& trianglesIndices)
{
    unsigned int i = 0;
    while(n > 3)
    {
        unsigned int index1 = i % n, index2 = (i + 1) % n, index3 = (i + 2) % n;
        if(isEar(indexList[index1], indexList[index2], indexList[index3], vertices, n))
        {
            trianglesIndices.push_back(indexList[index1]);
            trianglesIndices.push_back(indexList[index2]);
            trianglesIndices.push_back(indexList[index3]);

            remove(indexList, n, index2);
        }

        i++;
        i %= n;
    }

    trianglesIndices.push_back(indexList[0]);
    trianglesIndices.push_back(indexList[1]);
    trianglesIndices.push_back(indexList[2]);
}

void printTriangles(const std::vector<unsigned>& trianglesIndices)
{
    unsigned int size = trianglesIndices.size();

    std::cout << std::endl;
    for(unsigned i = 0; i < size; i += 3)
    {
        std::cout << trianglesIndices[i] << ' ' 
                  << trianglesIndices[i + 1] << ' ' 
                  << trianglesIndices[i + 2] << std::endl;
    }
}

int main()
{
    const unsigned int MAX_SIZE = 100;
    unsigned int n;

    do
    {
        std::cout << "Enter n: ";
        std::cin >> n;
    } while(n < 4 || n > MAX_SIZE);

    std::vector<Point> vertices;
    readVertices(vertices, n);

    // IsSimplePolyon?...
    // ContainColinearEdges?...
    // !VerticesAreOrderedClockWise? -> reverse

    unsigned int indexList[MAX_SIZE];
    initIndexList(indexList, n);

    std::vector<unsigned> trianglesIndices;

    earClipping(vertices, indexList, n, trianglesIndices);
    printTriangles(trianglesIndices);
    return 0;
}

/*
n = 9
-4 6
0 2
2 5
7 0
5 -6
3 3
0 -5
-6 0
-2 1

7 triangles:
3 4 5
6 7 8
8 0 1
2 3 5
5 6 8
1 2 5
1 5 8
*/
