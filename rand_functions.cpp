#include "rand_functions.h"

#include <stdlib.h>
#include <time.h>

// Function -- Sets the seed to a random seed.
// Must be run at least once to ensure a varied output.
void randomize()
{
    srand(time(0));
}

//Function -- Returns random integer value between 0 and given max.
int irandom(const int max)
{
    int value = rand() % (max + 1);
    return value;
}

// Function -- Returns random integer value between given min and max.
int irandom_range(const int min, const int max)
{
    int value = (rand() % (max - min + 1)) + min;
    return value;
}

// Function -- Returns random decimal value between 0 and given max.
double random(const int max)
{
    int max_new = irandom(max * 100.0);
    double value = max_new / 100.0;
    return value;
}

// Function -- Returns random decimal value between given min and max.
double random_range(const int min, const int max)
{
    int max_new = irandom_range(min * 100.0, max * 100.0);
    double value = max_new / 100.0;
    return value;
}

// Function -- Returns true a given percentage of times executed.
bool chance(const double percent)
{
    double value = random(100);
    return (value < percent);
}
