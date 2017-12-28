# advent-of-code-2017
Advent of Code is a series of small programming puzzles for a variety of skill levels.
More info on: http://adventofcode.com/2017

## Test Suite

In order to run the whole test suite (less than 1 minute), launch the application and type `-2`
All files related to the test suite are under the `test` folder (see "Structure of the codebase" below)

## Structure of the codebase

```
/
	main.c
	main.h
	+ days
		+ source
			dayXY.c
		+ header
			dayXY.h
		+ input
			dayXY.txt
	+ other
		+ source
			<a useful library>.c
		+ header
			<a useful library>.h
	+ test
		test.c
		test.h
		+ days
			+ XY
				input-ABC.txt
				part1-ABC.txt
				part2-ABC.txt
```

XY is ranging from 01 to 25 as there are 25 challenges
ABC is at least 001 (most of the time it's 001 only but there might be more triplets). Each ABC triplet is a test
