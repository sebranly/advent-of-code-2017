#ifndef COORDINATES_H_INCLUDED
#define COORDINATES_H_INCLUDED

typedef struct Coordinates2D Coordinates2D;
struct Coordinates2D
{
    long long x;
    long long y;
};

typedef struct Coordinates3D Coordinates3D;
struct Coordinates3D
{
    long long x;
    long long y;
    long long z;
    long long distanceFromOrigin;
};

long long calculateDistanceFrom3DOrigin(Coordinates3D coordinates);
long long absolute(long long number);
int identicalCoordinates3D(Coordinates3D coordinates1, Coordinates3D coordinates2);

#endif // COORDINATES_H_INCLUDED
