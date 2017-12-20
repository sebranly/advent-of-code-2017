#ifndef DAY20_H_INCLUDED
#define DAY20_H_INCLUDED

#define ARBITRARY_SUFFICIENT_ITERATION_NUMBER_BEFORE_STABLE_STATE 100

#include "solutionTypes.h"
#include "fileLibrary.h"
#include "coordinates.h"

enum { NO_FIELD, POSITION_FIELD, VELOCITY_FIELD, ACCELERATION_FIELD };
enum { NO_AXIS, X_AXIS, Y_AXIS, Z_AXIS };

typedef struct Particle Particle;
struct Particle
{
    Coordinates3D position;
    Coordinates3D velocity;
    Coordinates3D acceleration;
    int destroyed;
};

SolutionIntegers getSolutionDay20(const char * inputFilePath);
void populateCorrectParticleField(Particle * particle, int currentFieldIndex, int currentAxisIndex, int currentNumber);
void moveParticle(Particle * particle);

#endif // DAY20_H_INCLUDED
