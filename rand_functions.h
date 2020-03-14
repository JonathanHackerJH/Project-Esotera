#ifndef RAND_FUNCTIONS_H
#define RAND_FUNCTIONS_H

void randomize();
int irandom(const int max);
int irandom_range(const int min, const int max);
double random(const int max);
double random_range(const int min, const int max);
bool chance(const double percent);

#endif // RAND_FUNCTIONS_H
