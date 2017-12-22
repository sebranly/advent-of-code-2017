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

typedef struct PositiveCoordinates2D PositiveCoordinates2D;
struct PositiveCoordinates2D
{
    unsigned int x;
    unsigned int y;
};

long long calculateDistanceFrom3DOrigin(Coordinates3D coordinates);
long long absolute(long long number);
int identicalCoordinates3D(Coordinates3D coordinates1, Coordinates3D coordinates2);
int identicalPositiveCoordinates2D(PositiveCoordinates2D coordinates1, PositiveCoordinates2D coordinates2);

#endif // COORDINATES_H_INCLUDED
