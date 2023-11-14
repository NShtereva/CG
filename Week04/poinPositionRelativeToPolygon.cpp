#include <iostream>
#include <vector>

#include "../vecta.h"

typedef vecta::vec2d<double> Point;

double S(const Point& A, const Point& B, const Point& C)
{
    return (B - A) ^ (C - A); // AB x AC
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

    Point I(INT_MAX, P.y);
    Point horizontalBeam = (I - P);

    unsigned int crosssings = 0;

    for(unsigned i = 0; i < n; i++)
    {
        double SViVjP = S(vertices[i], vertices[(i + 1) % n], P);

        if((vertices[(i + 1) % n] - vertices[i]) || horizontalBeam)
        {
            if(SViVjP == 0)
            {
                // т.P лежи върху правата през лъча

                if((P.x >= vertices[i].x && P.x <= vertices[i + 1].x) || (P.x >= vertices[i + 1].x && P.x <= vertices[i].x))
                {
                    // т.P лежи върху отсечката на двата върха
                    std::cout << "on the contour" << std::endl;
                    return 0;
                }
            }
        }
        else
        {
            if((P.y - vertices[i].y) * (P.y - vertices[(i + 1) % n].y) <= 0) 
            {
                // Двата върха са в различни полуравнини спрямо хоризонталния лъч от т.P

                if(SViVjP > 0 && P.x < std::min(vertices[i].x, vertices[(i + 1) % n].x))
                {
                    crosssings++;
                }
                else if(SViVjP == 0)
                {
                    std::cout << "on the contour" << std::endl;
                    return 0;
                }
            }
        }
    }

    std::cout << ((crosssings % 2 == 0) ? "external point" : "interior point") << std::endl;
    return 0;
}

/*
Enter n: 7
Enter vertices:
0 0 
10 -5
20 0
20 10 
17 20
14 20
0 10
Enter point: 5 5
interior point

Enter n: 7
Enter vertices:
0 0
10 -5
20 0
20 10 
17 20
14 20
0 10
Enter point: 15 20
on the contour 

Enter n: 7
Enter vertices:
0 0
10 -5
20 0
20 10 
17 20
14 20
0 10
Enter point: 0 0
on the contour

Enter n: 7
Enter vertices:
0 0
10 -5
20 0
20 10
17 20
14 20
0 10
Enter point: 5 -10
external point
*/
