#include <iostream>
#include "../vecta.h"

double S(const vecta::vec2d<double>& A, const vecta::vec2d<double>& B, const vecta::vec2d<double>& C)
{
    return (B - A) ^ (C - A); // AB x AC
}

int main()
{
    vecta::vec2d<double> A, B, C, D;
    std::cin >> A >> B >> C >> D;

    if(((C - B) ^ (D - A)) != 0 && S(A, D, C) * S(A, D, B) < 0 && S(C, B, A) * S(C, B, D) < 0)
    {
        // BC intersects AD -> non-simple quadrilateral
        std::cout << 0;
    }
    else
    {
        // simple quadrilateral
        std::cout << 1;
    }

    std::cout << (((C - A) ^ (D - B)) > 0); // AC x BD > 0 <=> +orientation

    bool convex = S(A, C, D) * S(A, C, B) < 0 && S(D, B, A) * S(D, B, C) < 0;  // AC intersects BD -> convex
    std::cout << convex;

    if(!convex)
    {
        std::cout << 0 << 0 << 0 << std::endl;
        return 0;
    }

    bool parallelogram = ((B - A) ^ (C - D)) == 0 && S(A, B, D) != 0 && len(B - A) == len(C - D);
    std::cout << parallelogram;

    if(!parallelogram)
    {
        std::cout << 0 << 0 << std::endl;
        return 0;
    }

    bool perpendicular = ((D - A) * (B - A)) == 0;
    bool equalSideLen = len(D - A) == len(B - A);

    if(perpendicular && equalSideLen)
    {
        // square
        std::cout << 1 << 1 << std::endl;
        return 0;
    }
    else if(perpendicular && !equalSideLen)
    {
        // rectangle
        std::cout << 1 << 0 << std::endl;
        return 0;
    }
    else
    {
        std::cout << 0 << 0 << std::endl;
        return 0;
    }

    return 0;
}

/*
// square:
1 1
3 1
3 3
1 3
111111
// rectangle:
1 1
4 1
4 3
1 3
111110
// parallelogram:
1 1
3 1
4 3
2 3
111100
// !parallelogram:
1 1
3 0
4 5
2 4
111000
// non-simple quadrilateral:
1 1
3 1
1 4
3 3
000000
*/
