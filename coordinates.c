#include "coordinates.h"

long long calculateDistanceFrom3DOrigin(Coordinates3D coordinates)
{
    return absolute(coordinates.x) + absolute(coordinates.y) + absolute(coordinates.z);
}

long long absolute(long long number)
{
    return (number > 0) ? number : -number;
}

int identicalCoordinates3D(Coordinates3D coordinates1, Coordinates3D coordinates2)
{
    return coordinates1.x == coordinates2.x && coordinates1.y == coordinates2.y && coordinates1.z == coordinates2.z;
}
