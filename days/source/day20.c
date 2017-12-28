#include "../header/day20.h"

SolutionIntegers getSolutionDay20(const char * inputFilePath)
{
    SolutionIntegers solution;
    char currentChar;
    int keepReading = 1;
    int currentNumber = 0, chevronIndex = NO_FIELD, currentLine = 0, axisIndex = NO_AXIS, i, j, iteration;
    int sign = 1;
    unsigned long long minDistanceFromOrigin = 0;
    int idParticleClosestToOrigin = 0;
    int numberOfDestroyedParticles = 0;

    Particle * particles = NULL;
    int numberOfParticles = numberOfNonEmptyLines(inputFilePath);

    FILE* file = NULL;
    file = fopen(inputFilePath, "r");

    if (file != NULL)
    {
        particles = malloc(numberOfParticles * sizeof(Particle));
        if (particles == NULL)
        {
            printf("An error occurred because of memory limitation\n");
            exit(EXIT_FAILURE);
        }

        while (keepReading)
        {
            currentChar = fgetc(file);
            if (currentChar == '<')
            {
                chevronIndex++;
                axisIndex = X_AXIS;
                sign = 1;
                currentNumber = 0;
            }
            else if (isADigit(currentChar))
            {
                currentNumber *= 10;
                currentNumber += toInteger(currentChar);
            }
            else if (currentChar == '-')
                sign = -1;
            else if ((currentChar == ',' || currentChar == '>') && axisIndex <= Z_AXIS)
            {
                currentNumber = sign * currentNumber;
                populateCorrectParticleField(&(particles[currentLine]), chevronIndex, axisIndex, currentNumber);
                axisIndex++;
                currentNumber = 0;
                sign = 1;
            }
            else if (currentChar == EOF || currentChar == '\n')
            {
                if (currentChar == EOF)
                    keepReading = 0;
                currentLine++;
                chevronIndex = NO_FIELD;
            }
        }

        for (i = 0 ; i < numberOfParticles ; i++)
        {
            particles[i].destroyed = 0;
            particles[i].acceleration.distanceFromOrigin = calculateDistanceFrom3DOrigin(particles[i].acceleration);
            if (i == 0)
            {
                idParticleClosestToOrigin = 0;
                minDistanceFromOrigin = particles[0].acceleration.distanceFromOrigin;
            }
            else if (particles[i].acceleration.distanceFromOrigin < minDistanceFromOrigin)
            {
                // In the long term, the only vector that dictates the closest distance from the origin among all particles is the acceleration vector
                idParticleClosestToOrigin = i;
                minDistanceFromOrigin = particles[i].acceleration.distanceFromOrigin;
            }
        }
        solution.solutionPart1 = idParticleClosestToOrigin;

        iteration = 0;
        // TBD: think about how to determine that number in an accurate way
        while (iteration < ARBITRARY_SUFFICIENT_ITERATION_NUMBER_BEFORE_STABLE_STATE)
        {
            for (i = 0 ; i < numberOfParticles ; i++)
                if (!(particles[i].destroyed))
                    moveParticle(&(particles[i]));

            for (i = 0 ; i < numberOfParticles ; i++)
                if (!(particles[i].destroyed))
                    for (j = i + 1 ; j < numberOfParticles ; j++)
                        if (!(particles[j].destroyed) && identicalCoordinates3D(particles[i].position, particles[j].position))
                        {
                            particles[i].destroyed = 1;
                            particles[j].destroyed = 1;
                        }
            iteration++;
        }

        numberOfDestroyedParticles = 0;
        for (i = 0 ; i < numberOfParticles ; i++)
            if (particles[i].destroyed == 1)
                numberOfDestroyedParticles++;

        solution.solutionPart2 = numberOfParticles - numberOfDestroyedParticles;
        free(particles);
        fclose(file);
        return solution;
    }
    else
    {
        printf("The file with name %s could not be opened", inputFilePath);
        exit(EXIT_FAILURE);
    }
}

void populateCorrectParticleField(Particle * particle, int currentFieldIndex, int currentAxisIndex, int currentNumber)
{
    if (currentFieldIndex == POSITION_FIELD)
    {
        if (currentAxisIndex == X_AXIS)
            particle->position.x = currentNumber;
        else if (currentAxisIndex == Y_AXIS)
            particle->position.y = currentNumber;
        else if (currentAxisIndex == Z_AXIS)
            particle->position.z = currentNumber;
    }
    else if (currentFieldIndex == VELOCITY_FIELD)
    {
        if (currentAxisIndex == X_AXIS)
            particle->velocity.x = currentNumber;
        else if (currentAxisIndex == Y_AXIS)
            particle->velocity.y = currentNumber;
        else if (currentAxisIndex == Z_AXIS)
            particle->velocity.z = currentNumber;
    }
    else if (currentFieldIndex == ACCELERATION_FIELD)
    {
        if (currentAxisIndex == X_AXIS)
            particle->acceleration.x = currentNumber;
        else if (currentAxisIndex == Y_AXIS)
            particle->acceleration.y = currentNumber;
        else if (currentAxisIndex == Z_AXIS)
            particle->acceleration.z = currentNumber;
    }
}

void moveParticle(Particle * particle)
{
    particle->velocity.x += particle->acceleration.x;
    particle->velocity.y += particle->acceleration.y;
    particle->velocity.z += particle->acceleration.z;

    particle->position.x += particle->velocity.x;
    particle->position.y += particle->velocity.y;
    particle->position.z += particle->velocity.z;
}
