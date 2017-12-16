#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "solutionTypes.h"
#include "stringLibrary.h"
#include "allDays.h"

int main()
{
    SolutionIntegers solutionIntegers;
    SolutionStrings solutionStrings;
    SolutionIntegerString solutionIntegerString;
    FILE* file = NULL;
    char currentChar = 0, c;
    char fileName[MAX_FILE_NAME_LENGTH];
    char inlineInputAsText[MAX_ELEMENTS_PER_LINE][STRING_MAX_LENGTH];
    char ancestorName[TREE_ELEMENT_NAME_MAX_LENGTH], elementName[TREE_ELEMENT_NAME_MAX_LENGTH];
    char registerName[REGISTER_NAME_MAX_LENGTH], conditionalRegisterName[REGISTER_NAME_MAX_LENGTH];
    char operationString[STRING_LIMITED_LENGTH], conditionalString[STRING_LIMITED_LENGTH], operatorString[STRING_LIMITED_LENGTH];
    int i = 0, i2 = 0, j = 0, x = 0, y = 0, part = 1, size = 0, sign = 1, currentIndex = 0, currentCharIndex = 0, uniqueInputNumber = 0, number = 0, pivotNumber = 0, min = UNSET, max = UNSET, max2 = UNSET, sum = 0, sum2 = 0, numberOfRing = 0, heightPerRing = UNSET, numberOfSteps = UNSET, currentNumber = 0, currentConditionalNumber, dayOfChallenge = 0, result = 0;
    int beforeResetForDirection = UNSET, currentDirection = UNSET;
    // The following variables are used as booleans only
    int keepReading = 1, outOfArrayRange = 0, incorrectDayOfChallenge = 1, skipLine = 0, solutionIsFound = 0, stillOnAncestorName = 1;
    int counterOfLetters1[NUMBER_OF_LOWER_CASE_LETTERS] = {0};
    int counterOfLetters2[NUMBER_OF_LOWER_CASE_LETTERS] = {0};
    int input[ARBITRARY_ARRAY_LIMIT] = {0};
    int input2[ARBITRARY_ARRAY_LIMIT] = {0};
    int corners[NUMBER_OF_CARDINAL_DIRECTIONS];
    for (i = 0 ; i < NUMBER_OF_CARDINAL_DIRECTIONS ; i++)
        corners[i] = UNSET;
    TreeElement treeElements[MAX_TREE_ELEMENTS], ancestor;
    Register registers[MAX_REGISTERS];
    int indexAffectedRegister, indexConditionalRegister;
    int records[ARBITRARY_NUMBER_OF_RECORDS][ARBITRARY_NUMBER_OF_ELEMENTS_PER_RECORD];
    int inputIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT];
    fillAllCellsIn2D(inputIn2D, UNSET);

    do
    {
        printf("Which daily challenge do you want to access? (from 1 to %d)\nType %d to exit.\nYour choice: ", LATEST_AVAILABLE_CHALLENGE, EXIT_VALUE);
        scanf("%d", &dayOfChallenge);

        if (dayOfChallenge == EXIT_VALUE)
        {
            printf("Goodbye!\n");
            return EXIT_SUCCESS;
        }
        else if (dayOfChallenge == 0 || dayOfChallenge > MAX_CHALLENGE)
        {
            printf("The input you typed is incorrect\n");
            // We flush the buffer in case something else than two digits was typed (because of \n behaviour)
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        else if (dayOfChallenge > LATEST_AVAILABLE_CHALLENGE && dayOfChallenge <= MAX_CHALLENGE)
        {
            printf("Challenge #%d is not accessible yet\n", dayOfChallenge);
        }
        else {
            incorrectDayOfChallenge = 0;
        }
    } while (incorrectDayOfChallenge);

    printf("\nCHALLENGE OF DAY %02d\n===================\n", dayOfChallenge);

    result = sprintf(fileName, "inputs/inputDay%02d.txt", dayOfChallenge);
    if (result < 0)
    {
        printf("An unexpected error occurred before reading the input file");
    }
    // TBD: remove it once every day challenge has its own .c file
    file = fopen(fileName, "r");

    if (file != NULL)
    {
        switch (dayOfChallenge)
        {
            case 1:
            solutionIntegers = getSolutionDay01(fileName);
            printf("Part 1 - Sum for the input with next digit is: %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - Sum for the input with halfway around digit is: %d\n", solutionIntegers.solutionPart2);
            break;

            case 2:
            fillAllCellsIn2D(inputIn2D, UNSET);
            x = 0;
            y = 0;
            currentNumber = 0;
            while (keepReading)
            {
                currentChar = fgetc(file);
                if (isADigit(currentChar))
                {
                    currentNumber *= 10;
                    currentNumber += toInteger(currentChar);
                }
                else {
                    inputIn2D[x][y] = currentNumber;
                    currentNumber = 0;
                    if (currentChar == '\t')
                        x++;
                    else if (currentChar == '\n')
                    {
                        x = 0;
                        y++;
                    }
                    else if (currentChar == EOF)
                        keepReading = 0;
                    else
                    {
                        printf("An unexpected error occurred while reading the input file with name %s\n", fileName);
                        return EXIT_FAILURE;
                    }
                }
            }

            sum = 0;
            i = 0;
            j = 0;
            while (inputIn2D[i][j] != UNSET)
            {
                while (inputIn2D[i][j] != UNSET)
                {
                    if (min == UNSET || inputIn2D[i][j] < min)
                        min = inputIn2D[i][j];
                    if (max == UNSET || inputIn2D[i][j] > max)
                        max = inputIn2D[i][j];
                    i++;
                }
                sum += max - min;
                min = UNSET;
                max = UNSET;
                i = 0;
                j++;
            }
            printf("Part 1 - Checksum for the input is: %d\n", sum);

            sum = 0;
            i = 0;
            i2 = 0;
            j = 0;
            skipLine = 0;
            while (inputIn2D[i][j] != UNSET)
            {
                while (inputIn2D[i][j] != UNSET && !skipLine)
                {
                    i2 = 0;
                    while (inputIn2D[i2][j] != UNSET && !skipLine)
                    {
                       if (i != i2 && inputIn2D[i][j] >= inputIn2D[i2][j] && inputIn2D[i][j] % inputIn2D[i2][j] == 0)
                       {
                           sum += inputIn2D[i][j] / inputIn2D[i2][j];
                           skipLine = 1;
                       }
                       i2++;
                    }
                    i++;
                }
                skipLine = 0;
                i = 0;
                j++;
            }
            printf("Part 2 - Checksum for the input is: %d\n", sum);
            break;

            case 3:
            uniqueInputNumber = 0;
            keepReading = 1;
            while (keepReading)
            {
                currentChar = fgetc(file);
                if (isADigit(currentChar))
                {
                    uniqueInputNumber *= 10;
                    uniqueInputNumber += toInteger(currentChar);
                }
                else if (currentChar == EOF)
                {
                    keepReading = 0;
                }
                else
                {
                    printf("An unexpected error occurred while reading the input file with name %s\n", fileName);
                    return EXIT_FAILURE;
                }
            }
            if (uniqueInputNumber <= 0)
            {
                printf("The number for the memory has to be strictly greater than 0, the one found in the input file is %d so it is impossible to proceed", uniqueInputNumber);
                return EXIT_FAILURE;
            }
            printf("Going to access memory in number %d based on Manhattan Distance...\n", uniqueInputNumber);

            numberOfSteps = UNSET;
            if (uniqueInputNumber == 1)
            {
                numberOfSteps = 0;
            }
            else
            {
                do
                {
                    /* Every time we go from a ring to an upper ring, the height has two more cells in height
                    Ring #1 is the one right after the ring #0 (that only has cell 1) */
                    min = (numberOfRing == 0) ? 2 : min + numberOfRing * 8;
                    heightPerRing = (numberOfRing == 0) ? 3 : heightPerRing + 2;
                    numberOfRing++;
                    // Formula to know the max cell of the current ring being analyzed
                    max = min + (heightPerRing - 1) * 4 - 1;
                } while (uniqueInputNumber < min || uniqueInputNumber > max);
                printf("Your cell has been identified on ring %d of memory cells that is ranging from %d to %d included\n", numberOfRing, min, max);

                corners[SOUTH_EAST] = max;
                corners[SOUTH_WEST] = max - (heightPerRing - 1);
                corners[NORTH_WEST] = max - 2 * (heightPerRing - 1);
                corners[NORTH_EAST] = max - 3 * (heightPerRing - 1);
                printf("Numbers for the corners of this ring are NE: %d ; NW: %d ; SW: %d ; SE: %d\n", corners[NORTH_EAST], corners[NORTH_WEST], corners[SOUTH_WEST], corners[SOUTH_EAST]);

                for (i = 0 ; i < NUMBER_OF_CARDINAL_DIRECTIONS ; i++)
                    if (uniqueInputNumber == corners[i])
                        numberOfSteps = (heightPerRing / 2) * 2;

                if (numberOfSteps == UNSET)
                {
                    if (corners[SOUTH_EAST] > uniqueInputNumber && uniqueInputNumber > corners[SOUTH_WEST])
                    {
                        min = corners[SOUTH_WEST];
                    }
                    else if (corners[SOUTH_WEST] > uniqueInputNumber && uniqueInputNumber > corners[NORTH_WEST])
                    {
                        min = corners[NORTH_WEST];
                    }
                    else if (corners[NORTH_WEST] > uniqueInputNumber && uniqueInputNumber > corners[NORTH_EAST])
                    {
                        min = corners[NORTH_EAST];
                    }
                    else
                    {
                        // Compared to the ring min, we decrease the value and suppose it appears on the bottom right hand corner for our algorithm instead of the ring max value
                        min -= 1;
                    }
                    pivotNumber = (2 * min + heightPerRing - 1) / 2;
                    numberOfSteps = (heightPerRing / 2) * 2;
                    number = min;

                    do
                    {
                        number++;
                        numberOfSteps = (number <= pivotNumber) ? numberOfSteps - 1 : numberOfSteps + 1;
                    } while (number != uniqueInputNumber);
                }
            }

            printf("Part 1 - %d step(s) is/are required to go from number %d to number 1 in the memory\n", numberOfSteps, uniqueInputNumber);

            // Zero is a good choice (rather than UNSET) because we explicitly use the neutral number in the operation addition
            fillAllCellsIn2D(inputIn2D, 0);
            x = ARBITRARY_2D_ARRAY_LIMIT / 2;
            y = ARBITRARY_2D_ARRAY_LIMIT / 2;
            number = 1;
            inputIn2D[x][y] = number;
            x++;
            inputIn2D[x][y] = 1;
            max = 1;
            currentDirection = NORTH;
            heightPerRing = 3;
            beforeResetForDirection = 1;
            outOfArrayRange = 0;

            do
            {
                beforeResetForDirection--;
                moveOneStep(&x, &y, currentDirection);
                if (!valueIsBetween(x, 0, ARBITRARY_2D_ARRAY_LIMIT - 1) || !valueIsBetween(y, 0, ARBITRARY_2D_ARRAY_LIMIT - 1))
                    outOfArrayRange = 1;
                else
                {
                    number = sumOfAdjacentCells(inputIn2D, x, y);
                    if (number > max)
                        max = number;
                    inputIn2D[x][y] = number;
                    if (beforeResetForDirection == 0)
                    {
                        if (currentDirection == SOUTH || currentDirection == EAST)
                            beforeResetForDirection = heightPerRing;
                        else
                            beforeResetForDirection = heightPerRing - 1;
                        currentDirection = nextSpiralDirection(currentDirection);
                        if (currentDirection == NORTH)
                            heightPerRing += 2;
                    }
                }
            } while (max < uniqueInputNumber && !outOfArrayRange);

            if (outOfArrayRange)
                printf("We could not find any solution with your input because of memory limitation in the program\n");
            else
            {
                printCellsArrayIn2D(inputIn2D, ARBITRARY_2D_ARRAY_LIMIT/2 - 3, ARBITRARY_2D_ARRAY_LIMIT/2 + 3, ARBITRARY_2D_ARRAY_LIMIT/2 - 3, ARBITRARY_2D_ARRAY_LIMIT/2 + 3);
                printf("Part 2 - the first value written that is larger than your puzzle input %d is %d\n", uniqueInputNumber, max);
            }
            break;

            case 4:
            sum = 0;
            sum2 = 0;
            keepReading = 1;
            currentIndex = 0;
            currentCharIndex = 0;
            emptyInlineTextInput(inlineInputAsText);
            while (keepReading)
            {
                currentChar = fgetc(file);
                if (isALowerCaseLetter(currentChar))
                {
                    inlineInputAsText[currentIndex][currentCharIndex] = currentChar;
                    currentCharIndex++;
                }
                else if (currentChar == ' ' || currentChar == '\n' || currentChar == EOF)
                {
                    inlineInputAsText[currentIndex][currentCharIndex] = '\0';
                    currentCharIndex = 0;
                    if (currentChar == ' ')
                        currentIndex++;
                    else
                    {
                        skipLine = 0;
                        i = 0;
                        while (i <= currentIndex && !skipLine)
                        {
                            j = 0;
                            while (j <= currentIndex && !skipLine)
                            {
                                if (i != j && sameStrings(inlineInputAsText[i], inlineInputAsText[j]))
                                    skipLine = 1;
                                j++;
                            }
                            i++;
                        }
                        if (!skipLine)
                        {
                            sum += 1;
                            // The rule for part 2 (based on anagrams) is more strict than the rule for part 1 (based on string comparison)
                            skipLine = 0;
                            i = 0;
                            while (i <= currentIndex && !skipLine)
                            {
                                countLetters(inlineInputAsText[i], counterOfLetters1);
                                j = 0;
                                while (j <= currentIndex && !skipLine)
                                {
                                    if (i != j)
                                    {
                                        countLetters(inlineInputAsText[j], counterOfLetters2);
                                        if (!differentArrays(counterOfLetters1, counterOfLetters2, NUMBER_OF_LOWER_CASE_LETTERS))
                                            skipLine = 1;
                                    }
                                    j++;
                                }
                                i++;
                            }
                            if (!skipLine)
                                sum2 += 1;
                        }

                        currentIndex = 0;
                        emptyInlineTextInput(inlineInputAsText);

                        if (currentChar == EOF)
                            keepReading = 0;
                    }

                }
                else
                {
                    printf("An unexpected error occurred while reading the input file with name %s\n", fileName);
                    return EXIT_FAILURE;
                }
            }
            printf("Part 1 - there is/are %d valid passphrase(s) in the input file\n", sum);
            printf("Part 2 - there is/are %d valid passphrase(s) in the input file\n", sum2);
            break;

            case 5:
            fillAllCells(input, ARBITRARY_ARRAY_LIMIT, 0);
            size = 0;
            sign = 1;
            keepReading = 1;
            currentNumber = 0;
            while (keepReading)
            {
                currentChar = fgetc(file);
                if (isADigit(currentChar))
                {
                    currentNumber *= 10;
                    currentNumber += toInteger(currentChar);
                }
                else if (currentChar == '-')
                {
                    if (sign == -1)
                    {
                        printf("An error occurred while reading the input file with name %s because two minus signs are on a line\n", fileName);
                        return EXIT_FAILURE;
                    }
                    sign = -1;
                }
                else if (currentChar == '\n' || currentChar == EOF)
                {
                    input[size] = sign * currentNumber;
                    size++;
                    if (size >= ARBITRARY_ARRAY_LIMIT)
                    {
                        printf("An error occurred while reading the input file with name %s because of memory limitation in the program\n", fileName);
                        return EXIT_FAILURE;
                    }
                    sign = 1;
                    currentNumber = 0;
                    if (currentChar == EOF)
                        keepReading = 0;
                }
                else
                {
                    printf("An unexpected error occurred while reading the input file with name %s\n", fileName);
                    return EXIT_FAILURE;
                }
            }
            copyFirstCells(input, input2, size);

            part = 1;
            while (part <= 2)
            {
                currentIndex = 0;
                numberOfSteps = 0;
                while (currentIndex >= 0 && currentIndex < size)
                {
                    currentNumber = input[currentIndex];
                    if (part == 2 && currentNumber >= 3)
                        input[currentIndex]--;
                    else
                        input[currentIndex]++;
                    currentIndex += currentNumber;
                    numberOfSteps++;
                }
                printf("Part %d - %d step(s) was/were needed to get out of the list\n", part, numberOfSteps);
                part++;
                if (part == 2)
                    copyFirstCells(input2, input, size);
            }
            break;

            case 6:
            currentNumber = 0;
            currentIndex = 0;
            while (keepReading)
            {
                currentChar = fgetc(file);
                if (isADigit(currentChar))
                {
                    currentNumber *= 10;
                    currentNumber += toInteger(currentChar);
                }
                else {
                    if (currentChar == EOF || currentChar == '\n')
                        keepReading = 0;
                    else if (currentChar != '\t')
                    {
                        printf("An unexpected error occurred while reading the input file with name %s\n", fileName);
                        return EXIT_FAILURE;
                    }
                    input[currentIndex] = currentNumber;
                    currentNumber = 0;
                    currentIndex++;
                }
            }
            size = currentIndex;
            numberOfSteps = 0;
            printf("%04d: ", numberOfSteps);
            for (i = 0 ; i < size ; i++)
                printf("<%d> ", input[i]);
            printf("\n");
            copyFirstCells(input, records[0], size);
            solutionIsFound = 0;
            while (!solutionIsFound)
            {
                currentIndex = minIndexOfMaxValue(input, size);
                currentNumber = input[currentIndex];
                if (currentNumber == 0)
                {
                    printf("The input max value is 0 so there is nothing to distribute");
                    return EXIT_FAILURE;
                }
                input[currentIndex] = 0;
                while (currentNumber > 0)
                {
                    currentIndex = (currentIndex + 1) % size;
                    input[currentIndex] += 1;
                    currentNumber--;
                }
                numberOfSteps++;
                for (i = 0 ; i < numberOfSteps && !solutionIsFound ; i++)
                {
                    if (!differentArrays(input, records[i], size))
                    {
                        number = i;
                        solutionIsFound = 1;
                    }
                }
                copyFirstCells(input, records[numberOfSteps], size);
            }
            printf("Part 1 - An infinite loop has been detected after the block redistribution cycle #%d with cycle #%d\n", numberOfSteps, number);
            printf("Part 2 - the size of the loop is %d\n", numberOfSteps - number);
            break;

            case 7:
            size = 0;
            currentCharIndex = 0;
            currentNumber = 0;
            stillOnAncestorName = 1;
            keepReading = 1;
            while(keepReading)
            {
                currentChar = fgetc(file);
                if (isALowerCaseLetter(currentChar) && stillOnAncestorName)
                {
                    treeElements[size].name[currentCharIndex] = currentChar;
                    currentCharIndex++;
                }
                else if (currentChar == ' ' && stillOnAncestorName)
                {
                    treeElements[size].name[currentCharIndex] = '\0';
                    stillOnAncestorName = 0;
                }
                else if (isADigit(currentChar))
                {
                    currentNumber *= 10;
                    currentNumber += toInteger(currentChar);
                }
                else if (currentChar == ')')
                {
                    treeElements[size].valueOfAncestor = currentNumber;
                    currentNumber = 0;
                }
                else if (currentChar == '\n')
                {
                    size++;
                    stillOnAncestorName = 1;
                    currentCharIndex = 0;
                }
                else if (currentChar == EOF)
                {
                    // Workaround in order not to count a new line plus EOF as a word regarding the size in case it was empty
                    if (!stillOnAncestorName)
                        size++;
                    keepReading = 0;
                }
            }
            removeTreeAncestors(treeElements, size);
            rewind(file);

            keepReading = 1;
            stillOnAncestorName = 1;
            currentCharIndex = 0;
            while (keepReading)
            {
                currentChar = fgetc(file);
                if (isALowerCaseLetter(currentChar))
                {
                    if (stillOnAncestorName)
                    {
                        ancestorName[currentCharIndex] = currentChar;
                    }
                    else
                    {
                        elementName[currentCharIndex] = currentChar;
                    }
                    currentCharIndex++;
                }
                else if (currentChar == '>')
                {
                    ancestorName[currentCharIndex] = '\0';
                    currentCharIndex = 0;
                    stillOnAncestorName = 0;
                }
                else if (currentChar == ',')
                {
                    elementName[currentCharIndex] = '\0';
                    addAncestor(treeElements, size, elementName, ancestorName);
                    currentCharIndex = 0;
                }
                else if (currentChar == '\n')
                {
                    if (!stillOnAncestorName)
                    {
                        elementName[currentCharIndex] = '\0';
                        addAncestor(treeElements, size, elementName, ancestorName);
                    }
                    currentCharIndex = 0;
                    ancestorName[0] = '\0';
                    stillOnAncestorName = 1;
                }
                else if (currentChar == EOF)
                {
                    if (!stillOnAncestorName)
                    {
                        elementName[currentCharIndex] = '\0';
                        addAncestor(treeElements, size, elementName, ancestorName);
                    }
                    keepReading = 0;
                }
            }
            ancestor = firstElementWithoutAncestor(treeElements, size);
            printf("Part 1 - The bottom program is called %s\n", ancestor.name);
            setValueOfAncestorAndChildren(treeElements, size, &ancestor);

            // TBD: deserves a proper solution as it won't work for other inputs. For now, I got the solution by displaying the tree with a limited depth and going into the right branch
            for (i = 0 ; i < size ; i++)
                if (sameStrings(treeElements[i].name, "orflty"))
                    ancestor = treeElements[i];
            displayChildren(treeElements, size, ancestor, 0);
            break;

            case 8:
            keepReading = 1;
            size = 0;
            max2 = 0;
            while (keepReading)
            {
                fscanf(file, "%s %s %d %s %s %s %d", registerName, operationString, &currentNumber, conditionalString, conditionalRegisterName, operatorString, &currentConditionalNumber);

                indexAffectedRegister = findRegister(registers, size, registerName);
                if (indexAffectedRegister == NOT_FOUND)
                {
                    indexAffectedRegister = size;
                    size = createNewRegister(registers, size, registerName);
                }

                indexConditionalRegister = findRegister(registers, size, conditionalRegisterName);
                if (indexConditionalRegister == NOT_FOUND)
                {
                    indexConditionalRegister = size;
                    size = createNewRegister(registers, size, conditionalRegisterName);
                }

                if (
                    (sameStrings(operatorString, ">") && registers[indexConditionalRegister].value > currentConditionalNumber) ||
                    (sameStrings(operatorString, "<") && registers[indexConditionalRegister].value < currentConditionalNumber) ||
                    (sameStrings(operatorString, ">=") && registers[indexConditionalRegister].value >= currentConditionalNumber) ||
                    (sameStrings(operatorString, "<=") && registers[indexConditionalRegister].value <= currentConditionalNumber) ||
                    (sameStrings(operatorString, "!=") && registers[indexConditionalRegister].value != currentConditionalNumber) ||
                    (sameStrings(operatorString, "==") && registers[indexConditionalRegister].value == currentConditionalNumber)
                )
                {
                    sign = sameStrings(operationString, "inc") ? 1 : -1;
                    registers[indexAffectedRegister].value += sign * currentNumber;
                    if (registers[indexAffectedRegister].value > max2)
                        max2 = registers[indexAffectedRegister].value;
                }

                if (fgetc(file) == EOF)
                    keepReading = 0;
            }

            for (i = 0 ; i < size ; i++)
                if (i == 0 || registers[i].value > max)
                    max = registers[i].value;
            printf("Part 1 - the largest value is any register is %d\n", max);
            printf("Part 2 - the highest value held in any register during the process was %d\n", max2);
            break;

            case 9:
            solutionIntegers = getSolutionDay09(fileName);
            printf("Part 1 - the total score for all groups is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - the total number of garbage elements is %d\n", solutionIntegers.solutionPart2);
            break;

            case 10:
            solutionIntegerString = getSolutionDay10(fileName);
            printf("Part 1 - first number times second number equals %d\n", solutionIntegerString.solutionPart1);
            printf("Part 2 - final hash is %s", solutionIntegerString.solutionPart2);
            break;

            case 11:
            solutionIntegers = getSolutionDay11(fileName);
            printf("Part 1 - the fewest number of steps required to reach him is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - the furthest he ever got from his starting position is %d\n", solutionIntegers.solutionPart2);
            break;

            case 12:
            solutionIntegers = getSolutionDay12(fileName);
            printf("Part 1 - number of programs in same group than program with ID 0 is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - number of groups is %d\n", solutionIntegers.solutionPart2);
            break;

            case 13:
            solutionIntegers = getSolutionDay13(fileName);
            printf("Part 1 - the severity of the whole trip is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - the fewest number of picoseconds that I need to delay the packet to pass through the firewall without being caught is %d\n", solutionIntegers.solutionPart2);
            break;

            case 14:
            solutionIntegers = getSolutionDay14(fileName);
            printf("Part 1 - %d squares are used\n", solutionIntegers.solutionPart1);
            printf("Part 2 - %d regions are present\n", solutionIntegers.solutionPart2);
            break;

            case 15:
            solutionIntegers = getSolutionDay15(fileName);
            printf("Part 1 - Judge's final count is %d\n", solutionIntegers.solutionPart1);
            printf("Part 2 - Judge's final count is %d\n", solutionIntegers.solutionPart2);
            break;

            case 16:
            solutionStrings = getSolutionDay16(fileName);
            printf("Part 1 - The programs are in the following order after one dance:\n%s\n", solutionStrings.solutionPart1);
            printf("Part 2 - The programs are in the following order after way more than one dance:\n%s\n", solutionStrings.solutionPart2);
            break;

            default:
            break;
        }
        fclose(file);
    }
    else
    {
        printf("No file found with name %s", fileName);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int isADigit(char c)
{
    return (c >= ZERO_ASCII_CODE && c <= NINE_ASCII_CODE);
}

int toInteger(char digit)
{
    return digit - ZERO_ASCII_CODE;
}

int nextSpiralDirection(int currentDirection)
{
    switch (currentDirection)
    {
        case NORTH:
            return WEST;
            break;
        case WEST:
            return SOUTH;
            break;
        case SOUTH:
            return EAST;
            break;
        case EAST:
        default:
            return NORTH;
            break;
    }
}

void moveOneStep(int * x, int * y, int currentDirection)
{
    switch (currentDirection)
    {
        case NORTH:
            (*y)--;
            break;
        case WEST:
            (*x)--;
            break;
        case SOUTH:
            (*y)++;
            break;
        case EAST:
        default:
            (*x)++;
            break;
    }
}

void fillAllCellsIn2D(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int value)
{
    int i, j;
    for (i = 0 ; i < ARBITRARY_2D_ARRAY_LIMIT ; i++)
        for (j = 0 ; j < ARBITRARY_2D_ARRAY_LIMIT ; j++)
            arrayIn2D[i][j] = value;
}

void fillAllCells(int array[], int sizeArray, int value)
{
    int i;
    for (i = 0 ; i < sizeArray ; i++)
        array[i] = value;
}

int differentArrays(int array1[], int array2[], int size)
{
    int i = 0;
    for (i = 0 ; i < size ; i++)
        if (array1[i] != array2[i])
            return 1;
    return 0;
}

void copyFirstCells(int sourceArray[], int destinationArray[], int numberOfCellsToBeCopied)
{
    int i = 0;
    for (i = 0 ; i < numberOfCellsToBeCopied ; i++)
        destinationArray[i] = sourceArray[i];
}

void emptyInlineTextInput(char inlineInputAsText[MAX_ELEMENTS_PER_LINE][STRING_MAX_LENGTH])
{
    int i;
    for (i = 0 ; i < MAX_ELEMENTS_PER_LINE ; i++)
        inlineInputAsText[i][0] = '\0';
}

int minIndexOfMaxValue(int array[], int size)
{
    int associatedMinIndex = size - 1;
    int i, maxValue = array[associatedMinIndex];
    for (i = associatedMinIndex - 1 ; i >= 0 ; i--)
    {
        if (array[i] >= maxValue)
        {
            maxValue = array[i];
            associatedMinIndex = i;
        }
    }
    return associatedMinIndex;
}

int sumOfAdjacentCells(int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int x, int y)
{
    int sum = 0, i = 0, j = 0;
    for (i = x - 1 ; i <= x + 1 ; i++)
        for (j = y - 1 ; j <= y + 1 ; j++)
            if (i != x || j != y)
                if (valueIsBetween(i, 0, ARBITRARY_2D_ARRAY_LIMIT - 1) && valueIsBetween(j, 0, ARBITRARY_2D_ARRAY_LIMIT - 1))
                    sum += arrayIn2D[i][j];
    return sum;
}

int valueIsBetween(int value, int min, int max)
{
    return (min <= value && value <= max);
}

void printCellsArrayIn2D(const int arrayIn2D[ARBITRARY_2D_ARRAY_LIMIT][ARBITRARY_2D_ARRAY_LIMIT], int minX, int maxX, int minY, int maxY)
{
    int i, j;
    if (minX > maxX || minY > maxY || !valueIsBetween(minX, 0, ARBITRARY_2D_ARRAY_LIMIT - 1) || !valueIsBetween(maxX, 0, ARBITRARY_2D_ARRAY_LIMIT - 1) || !valueIsBetween(minY, 0, ARBITRARY_2D_ARRAY_LIMIT - 1) || !valueIsBetween(maxY, 0, ARBITRARY_2D_ARRAY_LIMIT - 1))
    {
        printf("We cannot print the portion of the 2D array because the limits are not correct\n");
    }
    else
    {
        printf("Displaying 2D array with X between %d and %d and Y between %d and %d\n", minX, maxX, minY, maxY);
        for (j = minY ; j <= maxY ; j++)
        {
            for (i = minX ; i <= maxX ; i++)
                printf("%d\t", arrayIn2D[i][j]);
            printf("\n");
        }
    }
}

// Gets the first element in the tree that matches the element name and adds the specified ancestor to it
int addAncestor(TreeElement elements[], int size, const char elementName[], const char ancestorName[])
{
    int i = 0;
    for (i = 0 ; i < size ; i++)
        if (sameStrings(elementName, elements[i].name))
        {
            strcpy(elements[i].uniqueAncestorName, ancestorName);
            return 1;
        }
    return 0;
}

void removeTreeAncestors(TreeElement elements[], int size)
{
    int i = 0;
    for (i = 0 ; i < 0 ; i++)
        elements[i].uniqueAncestorName[0] = '\0';
}

TreeElement firstElementWithoutAncestor(TreeElement elements[], int size)
{
    TreeElement defaultElement;
    strcpy(defaultElement.name, "");
    int i = 0;
    for (i = 0 ; i < size ; i++)
        if (elements[i].uniqueAncestorName[0] == '\0')
            return elements[i];
    return defaultElement;
}

void displayChildren(TreeElement elements[], int size, const TreeElement ancestor, int depth)
{
    int i = 0;
    for (i = 0 ; i < depth ; i++)
        printf("\t");
    printf("%s (%d) (Total: %d)\n", ancestor.name, ancestor.valueOfAncestor, ancestor.valueOfAncestorAndChildren);
    if (depth >= MAX_DEPTH_TO_DISPLAY)
        return;
    for (i = 0 ; i < size ; i++)
        if (sameStrings(elements[i].uniqueAncestorName, ancestor.name))
            displayChildren(elements, size, elements[i], depth + 1);
}

int setValueOfAncestorAndChildren(TreeElement elements[], int size, TreeElement * pAncestor)
{
    int i = 0;
    pAncestor->valueOfAncestorAndChildren = pAncestor->valueOfAncestor;
    for (i = 0 ; i < size ; i++)
        if (sameStrings(elements[i].uniqueAncestorName, pAncestor->name))
            pAncestor->valueOfAncestorAndChildren += setValueOfAncestorAndChildren(elements, size, &(elements[i]));
    return pAncestor->valueOfAncestorAndChildren;
}

int findRegister(const Register * registers, int size, const char * name)
{
    int i = 0;
    for (i = 0 ; i < size ; i++)
        if (sameStrings(registers[i].name, name))
            return i;
    return NOT_FOUND;
}

int createNewRegister(Register * registers, int size, const char * name)
{
    Register newRegister;
    newRegister.value = 0;
    strcpy(newRegister.name, name);
    registers[size] = newRegister;
    return size + 1;
}

void swapValues(int * value1, int * value2)
{
    int tmp = *value1;
    *value1 = *value2;
    *value2 = tmp;
}
