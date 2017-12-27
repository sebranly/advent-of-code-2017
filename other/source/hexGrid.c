#include "../header/hexGrid.h"

void addSteps(char * direction, int steps[NUMBER_OF_HEX_AXES])
{
    if (sameStrings(direction, "n"))
        steps[HEX_NORTH]++;
    else if (sameStrings(direction, "ne"))
        steps[HEX_NORTH_EAST]++;
    else if (sameStrings(direction, "se"))
        steps[HEX_SOUTH_EAST]++;
    else if (sameStrings(direction, "s"))
        steps[HEX_NORTH]--;
    else if (sameStrings(direction, "sw"))
        steps[HEX_NORTH_EAST]--;
    else if (sameStrings(direction, "nw"))
        steps[HEX_SOUTH_EAST]--;
}

void minimizeSteps(int steps[NUMBER_OF_HEX_AXES])
{
    if (steps[HEX_NORTH] > 0 && steps[HEX_SOUTH_EAST] > 0)
    {
        steps[HEX_NORTH]--;
        steps[HEX_SOUTH_EAST]--;
        steps[HEX_NORTH_EAST]++;
    }
    else if (steps[HEX_NORTH_EAST] > 0 && steps[HEX_NORTH] < 0)
    {
        steps[HEX_NORTH_EAST]--;
        steps[HEX_NORTH]++;
        steps[HEX_SOUTH_EAST]++;
    }
    else if (steps[HEX_SOUTH_EAST] > 0 && steps[HEX_NORTH_EAST] < 0)
    {
        steps[HEX_SOUTH_EAST]--;
        steps[HEX_NORTH_EAST]++;
        steps[HEX_NORTH]--;
    }
    else if (steps[HEX_NORTH] < 0 && steps[HEX_SOUTH_EAST] < 0)
    {
        steps[HEX_NORTH]++;
        steps[HEX_SOUTH_EAST]++;
        steps[HEX_NORTH_EAST]--;
    }
    else if (steps[HEX_NORTH_EAST] < 0 && steps[HEX_NORTH] > 0)
    {
        steps[HEX_NORTH_EAST]++;
        steps[HEX_NORTH]--;
        steps[HEX_SOUTH_EAST]--;
    }
    else if (steps[HEX_SOUTH_EAST] < 0 && steps[HEX_NORTH_EAST] > 0)
    {
        steps[HEX_SOUTH_EAST]++;
        steps[HEX_NORTH_EAST]--;
        steps[HEX_NORTH]++;
    }
}
